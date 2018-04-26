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
    mSolutions = parameters->solutions();
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
    for(int limit = 0; limit < mLimits.count(); limit++) {
        auto value = randomData(mLimits.at(limit).lower(), mLimits.at(limit).upper());
        initialModel->addVFSAData(limit, value, mNumberOfBeds);
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
                    delete newModel;
                }
            }
        }

        //Decline temperature
        temperature = mInitialTemperature * qExp(-(pow((double)j, 0.4)));

        //On cancel requested
        if (mAbort.load()) {
            return;
        }

        double partialProgress = ((double)j / (double)mIterationsPerTemperature) * 100.0 / mSolutions;
        emit reportProgress(partialProgress);

    }

    //Take the last model as the best model
    mJobResult->setFinalModel(mJobResult->allModels().last());
    mJobResult->finalModel()->setName("VFSA "+ QString::number(mThreadNumber));

    mJobResult->discardErroneousModels(mMaximunError);

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

void VFSASolutionJob::vfsaInternalError(VFSAInversionModel *model) const
{
    //Invert the model
    model->inversion(mFieldData);

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

    auto parameters = previousModel->getVFSAParameters();
    for(int i = 0; i < parameters.count(); i++){
        double data;
        int tries = 0;
        bool getOut = false;
        double aRandom, ayy, dif, yy, pwr, xmod, lower, upper, value;

        lower = qLn(mLimits.at(i).lower());
        upper = qLn(mLimits.at(i).upper());
        value = qLn(parameters.at(i));
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

        data = qExp(xmod);
        newModel->addVFSAData(i, data, mNumberOfBeds);
    }

    vfsaInternalError(newModel);
    return newModel;
}


