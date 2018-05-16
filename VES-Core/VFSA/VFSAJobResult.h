#ifndef VFSAJOBRESULT_H
#define VFSAJOBRESULT_H

#include <QObject>
#include <QList>
#include "../VFSAInversionModel.h"

class VFSAJobResult : public QObject
{
    Q_OBJECT

    VFSAInversionModel *mFinalModel;
    QList<VFSAInversionModel*> mAllModels;

public:
    explicit VFSAJobResult(QObject *parent = nullptr);
    ~VFSAJobResult() override;

    VFSAInversionModel *finalModel() const;
    void setFinalModel(const int modelNumber);

    QList<VFSAInversionModel *> allModels() const;
    void appendModel(VFSAInversionModel *model);

    void clearModels();

signals:

public slots:
};

#endif // VFSAJOBRESULT_H
