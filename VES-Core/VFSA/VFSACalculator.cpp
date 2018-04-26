#include "VFSACalculator.h"

#include <QThreadPool>
#include <QtMath>

VFSACalculator::VFSACalculator(const QList<SpliceData> &fieldData, const VfsaParameters &parameters, QObject *parent) : QObject(parent),
    mFieldData(fieldData)
{
    mParameters = new VfsaParameters(parameters);
}

VFSACalculator::~VFSACalculator()
{
    clearJobs();
}

void VFSACalculator::startInversion()
{
    clearJobs();

    //poner mParameters->solutions() + 1, el 2 es solo para probar un solo thread
    for(int i = 1; i < mParameters->solutions() + 1; i++) {
        QThreadPool::globalInstance()->start(createJob(i));
    }
}

void VFSACalculator::process(VFSAJobResult *jobResult)
{
    mFinishedJobs.append(jobResult);

    if (mFinishedJobs.count() < mParameters->solutions()){
       return;
    } else {
       allJobFinished();
    }
}

void VFSACalculator::jobProgressChanged(const double value)
{
    int partialProgress = value * 100.0 / mParameters->solutions();
}

QList<VFSAInversionModel *> VFSACalculator::getFinalModels() const
{
    return finalModels;
}

VFSASolutionJob *VFSACalculator::createJob(const int modelNumber)
{
    auto job = new VFSASolutionJob(modelNumber, mFieldData, mParameters, this);

    connect(this, &VFSACalculator::abortAllJobs, job, &VFSASolutionJob::abort);
    connect(job, &VFSASolutionJob::jobCompleted, this, &VFSACalculator::process);
    connect(job, &VFSASolutionJob::reportProgress, this, &VFSACalculator::jobProgressChanged);

    return job;
}

void VFSACalculator::clearJobs()
{
    emit abortAllJobs();
    QThreadPool::globalInstance()->clear();

    //Remove jobs.
    while (mFinishedJobs.count() > 0) {
         delete mFinishedJobs.at(0);
         mFinishedJobs.removeAt(0);
    }
}

VFSAInversionModel* VFSACalculator::averageModel(const QList<VFSAInversionModel*> models)
{
    auto model = new VFSAInversionModel();

    for(int i = 0; i < mParameters->numberOfParameters(); i ++){
        double sum = 0.0;
        foreach (auto m, models) {
            sum += m->getVFSAParameters().at(i);
        }
        sum /= mParameters->numberOfParameters();
        model->addVFSAData(i, sum, mParameters->numberOfBeds());
    }

    model->inversion(mFieldData);
    model->updateModelError(mFieldData);
    return model;

}

void VFSACalculator::cleanByPDF()
{
    const int numberOfParameters = mParameters->numberOfParameters();
    QVector<double> maxValues(numberOfParameters);

    double sum, mean, sd, maxPDF;
    int modelCounter = 0;
    for (int i = 0; i < numberOfParameters; i++){

        sum = 0.0;
        foreach (auto job, mFinishedJobs) {
            foreach (auto m, job->allModels()) {
                auto params = m->getVFSAParameters();
                sum += log10(params.at(i));
            }
            modelCounter += job->allModels().count();
        }
        mean = sum / modelCounter;

        sum = 0.0;
        foreach (auto job, mFinishedJobs) {
            foreach (auto m, job->allModels()) {
                auto params = m->getVFSAParameters();
                sum += pow(log10(params.at(i)) - mean, 2.0);
            }
        }
        sd = sqrt(sum / modelCounter);

        maxPDF = 0.0;
        foreach (auto job, mFinishedJobs) {
            foreach (auto m, job->allModels()) {
                auto params = m->getVFSAParameters();
                double pdf = exp(-(pow(log10(params.at(i)) - mean, 2.0) / (2.0 * pow(sd, 2.0)))) / ((params.at(i)) * sd * sqrt(2.0 * M_PI));
                m->setParameterPDF(i, pdf);

                if (pdf > maxPDF){
                    maxPDF = pdf;
                }
            }
        }
        maxValues[i] = maxPDF;
    }


    for (int i = 0; i < numberOfParameters; i++){
        double pdfThreshold = maxValues.at(i) * mParameters->minimunPdf();

        foreach (auto job, mFinishedJobs) {
            job->discardModelsByPDF(pdfThreshold, i);
        }


    }

}

void VFSACalculator::allJobFinished()
{

    foreach (auto job, mFinishedJobs) {
        job->finalModel()->updateModelError(mFieldData);
        finalModels.append(job->finalModel());
    }
    auto meanModel = averageModel(finalModels);
    meanModel->setName(tr("Modelo promedio"));
    finalModels.append(meanModel);

    cleanByPDF();
    QList<VFSAInversionModel*> tempList;
    foreach (auto job, mFinishedJobs) {
        tempList.append(job->allModels());
    }
    auto likelyModel = averageModel(tempList);
    likelyModel->setName(tr("Modelo probable"));
    finalModels.append(likelyModel);


}
