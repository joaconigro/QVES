#ifndef VFSASOLUTIONJOB_H
#define VFSASOLUTIONJOB_H

#include <QObject>
#include <QRunnable>
#include <QAtomicInteger>
#include <QRandomGenerator>
#include <QList>
#include "VFSAJobResult.h"
#include "VfsaParameters.h"
#include "VfsaParameterLimit.h"
#include "../SpliceData.h"
#include "../VFSAInversionModel.h"

class VFSASolutionJob : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit VFSASolutionJob(const int threadNumber, const QList<SpliceData> &fieldData, const VfsaParameters *parameters, QObject *parent = nullptr);
    void run() override;

signals:
    void jobCompleted(VFSAJobResult *jobResult);
    void reportProgress(double progress);

public slots:
    void abort();

private:
    QAtomicInteger<bool> mAbort;
    int mSolutions;
    double mInitialTemperature;
    int mIterationsPerTemperature;
    int mMovesPerTemperature;
    int mNumberOfParameters;
    int mNumberOfBeds;
    QList<VfsaParameterLimit> mLimits;
    double mMaximunError;
    double mMinimunPdf;
    QRandomGenerator *randomGenerator;
    QList<SpliceData> mFieldData;
    VFSAJobResult *mJobResult;
    int mThreadNumber;

    double randomData(const double min, const double max) const;
    //void calculateResistivity(VFSAInversionModel *model) const;
    void vfsaInternalError(VFSAInversionModel *model) const;
    VFSAInversionModel *randomModel(const VFSAInversionModel *previousModel, const double temperature);
};

#endif // VFSASOLUTIONJOB_H
