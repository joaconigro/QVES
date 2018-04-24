#include "VFSACalculator.h"

#include <QThreadPool>

VFSACalculator::VFSACalculator(const QList<SpliceData> &fieldData, const VfsaParameters &parameters, QObject *parent) : QObject(parent),
    mFieldData(fieldData)
{
    mParameters = new VfsaParameters(parameters);
}

void VFSACalculator::startInversion()
{
    clearJobs();

    //poner mParameters->solutions() + 1, el 2 es solo para probar un solo thread
    for(int i = 1; i < 2; i++) {
        QThreadPool::globalInstance()->start(createJob(i));
    }

}

void VFSACalculator::process(VFSAJobResult *jobResult)
{
    mFinishedJobs.append(jobResult);

    if (mFinishedJobs.count() < mParameters->solutions()){
       return;
    } else {
        int i = 32;
    }
}

VFSASolutionJob *VFSACalculator::createJob(const int modelNumber)
{
    auto job = new VFSASolutionJob(modelNumber, mFieldData, mParameters, this);

    connect(this, &VFSACalculator::abortAllJobs, job, &VFSASolutionJob::abort);
    connect(job, &VFSASolutionJob::jobCompleted, this, &VFSACalculator::process);

    //Conectar el reportProgress

    return job;
}

void VFSACalculator::clearJobs()
{
    emit abortAllJobs();
    QThreadPool::globalInstance()->clear();
}
