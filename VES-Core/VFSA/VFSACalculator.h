#ifndef VFSACALCULATOR_H
#define VFSACALCULATOR_H

#include "ves-core_global.h"
#include <QObject>
#include <QList>
#include "VFSASolutionJob.h"
#include "VFSAJobResult.h"
#include "VFSAParameters.h"
#include "../VFSAInversionModel.h"
#include "../SpliceData.h"

class VESCORESHARED_EXPORT VFSACalculator: public QObject
{

    Q_OBJECT

public:
    explicit VFSACalculator(const QList<SpliceData> &fieldData, const VFSAParameters &parameters, QObject *parent = nullptr);
    ~VFSACalculator() override;

    QList<VFSAInversionModel *> getFinalModels() const;

signals:
    void allCalculationsCompleted();
    void abortAllJobs();
    void totalProgressReport(const int percentaje);

public slots:
    void startInversion();
    void process(VFSAJobResult *jobResult);
    void jobProgressChanged(const double value);

private:
    double totalProgress;
    VFSAParameters *mParameters;
    QList<SpliceData> mFieldData;
    QList<VFSAJobResult *> mFinishedJobs;
    QList<VFSAInversionModel *> finalModels;

    VFSASolutionJob *createJob(const int modelNumber);
    void clearJobs();
    VFSAInversionModel* averageModel(const QList<VFSAInversionModel*> models);
    void allJobFinished();

private slots:
    //void allJobFinished();

};

#endif // VFSACALCULATOR_H
