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
    ~VFSACalculator() override;

    QList<VFSAInversionModel *> getFinalModels() const;

signals:
    void allCalculationsCompleted(QList<VFSAInversionModel *> inversionModels);
    void abortAllJobs();
    void totalProgressReport(const int percentaje);

public slots:
    void startInversion();
    void process(VFSAJobResult *jobResult);
    void jobProgressChanged(const double value);

private:
    VfsaParameters *mParameters;
    QList<SpliceData> mFieldData;
    QList<VFSAJobResult *> mFinishedJobs;
    QList<VFSAInversionModel *> finalModels;

    VFSASolutionJob *createJob(const int modelNumber);
    void clearJobs();
    VFSAInversionModel* averageModel(const QList<VFSAInversionModel*> models);
    void cleanByPDF();
    void allJobFinished();

};

#endif // VFSACALCULATOR_H
