#include "VFSASolutionJob.h"
#include <QTime>
#include <QVector>
#include <QtMath>
#include "../BasicData.h"

VFSASolutionJob::VFSASolutionJob(const int threadNumber, const QList<SpliceData> &fieldData, const VfsaParameters *parameters, QObject *parent) : QObject(parent),
    mAbort(false),
    mFieldData(fieldData),
    mThreadNumber(threadNumber)
{
    mInitialTemperature = parameters->initialTemperature();
    mIterationsPerTemperature = parameters->iterationsPerTemperature();
    mMovesPerTemperature = parameters->movesPerTemperature();
    mNumberOfParameters = parameters->numberOfParameters();
    mNumberOfBeds = parameters->numberOfBeds();
    mLimits = parameters->limits();
    mMaximunError = parameters->maximunError();
    mMinimunPdf = parameters->minimunPdf();

    //int seed = QTime::currentTime().msec();
    randomGenerator = new QRandomGenerator();

}

void VFSASolutionJob::run()
{
    mJobResult = new VFSAJobResult();
    double temperature = mInitialTemperature;

    //Create an initial model with initial temperature
    auto initialModel = new VFSAInversionModel();

    //Create random parameters for initial model
    foreach (auto limit, mLimits) {
        auto value = randomData(limit.lower(), limit.upper());
        initialModel->addVFSAData(value);
    }

    //Calculate internal VFSA error and save the model
    vfsaInternalError(initialModel);
    mJobResult->appendModel(initialModel);

    //Create a copy of initial model
    auto previousModel = new VFSAInversionModel(*initialModel);

    //Iterations per temperature
    for(int j = 1; j < mIterationsPerTemperature + 1; j++){
        //Loop throgh all other temperature levels

        int l = 1;
        int tries = 0;
        while (l < mMovesPerTemperature + 1 && tries < 100) {
            auto newModel = randomModel(previousModel, temperature);

            if (newModel->getVFSAError() < previousModel->getVFSAError()){
                mJobResult->appendModel(newModel);
                previousModel = new VFSAInversionModel(*newModel);
                l += 1;
            } else {
                double de = -(newModel->getVFSAError() - previousModel->getVFSAError());
                double pde = qExp(de / temperature);
                double rr = randomGenerator->generateDouble();
                if (pde > rr) {
                    mJobResult->appendModel(newModel);
                    previousModel = new VFSAInversionModel(*newModel);
                    l += 1;
                } else {
                    tries += 1;
                }
            }
        }

        //Decline temperature
        temperature = mInitialTemperature * qExp(-(pow((double)j, 0.4)));

        //On cancel requested
        if (mAbort.load()) {
            return;
        }

        int progress = j * 100 / mIterationsPerTemperature;
        emit reportProgress(progress);

    }

    //Take the last model as the best model
    mJobResult->setFinalModel(mJobResult->allModels().last());
    mJobResult->finalModel()->setName("VFSA "+ QString::number(mThreadNumber));
    emit jobCompleted(mJobResult);

}

void VFSASolutionJob::abort()
{
    mAbort.store(true);
}

double VFSASolutionJob::randomData(const double min, const double max) const
{
    double difference = max - min;
    double result;
    double iRand = randomGenerator->generateDouble();

    //Generate a random parameter between min and max values.
    do{
        result = min + iRand * difference;
    }while(result > max || result < min);

    return result;
}

void VFSASolutionJob::calculateResistivity(VFSAInversionModel *model) const
{
    //Necessary variables.
    QVector<double> rho(mNumberOfBeds);
    QVector<double> thicknesses(mNumberOfBeds - 1);
    int m;
    double ep;
    int nn;
    QVector<double> t(mNumberOfBeds);
    QVector<double> tt(14);
    double xx;
    double appRes;

    for(int i = 0; i < mNumberOfBeds; i++){
        rho[i] = model->getVFSAParameters().at(i).value();
    }
    for(int i = mNumberOfBeds; i < model->getVFSAParameters().count(); i++){
        thicknesses[i - mNumberOfBeds] = model->getVFSAParameters().at(i).value();
    }
    thicknesses.append(std::numeric_limits<int>::max());

    //Schlumberger device (MM, MP, MN, DS, SHIFT, AJ)
    const QVector<double> AJ = {0.014, 0.0282, 0.0838, 0.2427, 0.6217, 1.1877, 0.3954, -3.4531, 2.7568, -1.2075, 0.4595, -0.1975, 0.1042, -0.0359};
    const int MM = 3;
    const int MP = 10;
    const int MN = 13;
    const double DS = qLn(10) / 6.0;
    const double SHIFT = 0.1343115;


    foreach (auto item, mFieldData) {
        BasicData pCalc;
        pCalc.setAb2Distance(item.ab2Distance());
        m = -MP;

        do{
            nn = mNumberOfBeds - 1;
            ep = item.ab2Distance() * exp(m * DS - SHIFT);
            t[nn] = rho.at(nn);

            do{
                xx = thicknesses.at(nn - 1) / ep;
                t[nn - 1] = (t[nn] + rho[nn - 1] * tanh(xx)) / (1 + t[nn] * tanh(xx) / rho[nn - 1]);
                nn -= 1;
            } while (nn >= 1);

            tt[m + MP] = t.at(nn);
            m += 1;

        } while (m <= MM);

        appRes = 0.0;
        for(int j = 0; j<AJ.count(); j++){
            appRes += tt.at(MN - j) * AJ.at(j);
        }
        pCalc.setResistivity(appRes);
        model->appendCalculatedData(pCalc);
        //model->calculatedData().append(pCalc);
    }
}

void VFSASolutionJob::vfsaInternalError(VFSAInversionModel *model) const
{
    calculateResistivity(model);

    double finalError = 0.0;
    for(int i = 0; i < mFieldData.count(); i++){
        finalError += pow((log10(mFieldData.at(i).resistivity()) - log10(model->calculatedData().at(i).resistivity())), 2.0);
    }
    finalError /= mFieldData.count();
    model->setVFSAError(finalError);
}

VFSAInversionModel *VFSASolutionJob::randomModel(const VFSAInversionModel *previousModel, const double temperature)
{
    auto newModel = new VFSAInversionModel();

    for(int i = 0; i < previousModel->getVFSAParameters().count(); i++){
        VfsaData data;
        int tries = 0;
        bool getOut = false;
        double aRandom, ayy, dif, yy, pwr, xmod, lower, upper, value;

        lower = qLn(mLimits.at(i).lower());
        upper = qLn(mLimits.at(i).upper());
        value = qLn(previousModel->getVFSAParameters().at(i).value());
        do {
            aRandom = randomGenerator->generateDouble();
            ayy = 0.0;
            dif = aRandom - 0.5;
            if (dif < 0.0){
                ayy = -1.0;
            } else if (dif > 0.0) {
                ayy = 1.0;
            }
            pwr = qAbs(2.0 * aRandom - 1.0);
            yy = ayy * temperature * (pow(1.0 + 1.0 / temperature,  pwr) - 1.0);
            xmod = value + yy * (upper - lower);
            if ((xmod < lower) || (xmod > upper)){
                tries +=1;
            } else {
               getOut = true;
            }

        } while (tries < 100 && !getOut);

        data.setValue(qExp(xmod));
        newModel->addVFSAData(data);
    }

    vfsaInternalError(newModel);
    return newModel;
}


