#include "VFSACalculator.h"

#include <QThreadPool>
#include <QtMath>
#include <QMutex>
#include <QMutexLocker>
#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

VFSACalculator::VFSACalculator(const QList<SpliceData> &fieldData, const VFSAParameters &parameters, QObject *parent) : QObject(parent),
    mFieldData(fieldData)
{
    mParameters = new VFSAParameters(parameters);
}

VFSACalculator::~VFSACalculator()
{
    clearJobs();
}

void VFSACalculator::startInversion()
{
    clearJobs();
    totalProgress = 0.0;
    emit totalProgressReport((int)totalProgress);

    //poner mParameters->solutions() + 1, el 2 es solo para probar un solo thread
    for(int i = 1; i < mParameters->solutions() + 1; i++) {
        QThreadPool::globalInstance()->start(createJob(i));
    }
}

void VFSACalculator::process(VFSAJobResult *jobResult)
{
    QMutex mutex;
    QMutexLocker locker(&mutex);

    mFinishedJobs.append(jobResult);

    if (mFinishedJobs.count() < mParameters->solutions()){
       return;
    } else {
//        QFutureWatcher<void> watcher;
//        connect(&watcher, &QFutureWatcher::finished, this, &VFSACalculator::allCalculationsCompleted);

//        QFuture<void> future = QtConcurrent::run([=](){this->allJobFinished();});
//        future.waitForFinished();

allJobFinished();

        emit allCalculationsCompleted();
        //watcher.setFuture(future);

       //allJobFinished();
    }
}

void VFSACalculator::jobProgressChanged(const double value)
{
    QMutex mutex;
    QMutexLocker locker(&mutex);

    totalProgress += value;

    emit totalProgressReport((int)totalProgress);
    //int partialProgress = value * 100.0 / mParameters->solutions();
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
    connect(job, &VFSASolutionJob::jobCompleted, job, &VFSASolutionJob::deleteLater);

    job->setAutoDelete(false);
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
        sum /= models.count();
        model->addVFSAData(i, sum, mParameters->numberOfBeds());
    }

    model->inversion(mFieldData);
    model->updateModelError(mFieldData);
    return model;

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
}
