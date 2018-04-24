#ifndef VFSACALCULATOR_H
#define VFSACALCULATOR_H

#include <QObject>
#include <QList>
#include "VFSASolutionJob.h"
#include "VFSAJobResult.h"
#include "VfsaParameters.h"
#include "../VFSAInversionModel.h"
#include "../SpliceData.h"

class VFSACalculator: public QObject
{

    Q_OBJECT

public:
    explicit VFSACalculator(const QList<SpliceData> &fieldData, const VfsaParameters &parameters, QObject *parent = nullptr);

signals:
    void allCalculationsCompleted(QList<VFSAInversionModel *> inversionModels);
    void abortAllJobs();

public slots:
    void startInversion();
    void process(VFSAJobResult *jobResult);

private:
    VfsaParameters *mParameters;
    QList<SpliceData> mFieldData;
    QList<VFSAJobResult *> mFinishedJobs;


    VFSASolutionJob *createJob(const int modelNumber);
    void clearJobs();
};

#endif // VFSACALCULATOR_H
