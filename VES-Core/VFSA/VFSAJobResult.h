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

    VFSAInversionModel *finalModel() const;
    void setFinalModel(VFSAInversionModel *finalModel);

    QList<VFSAInversionModel *> allModels() const;
    void appendModel(VFSAInversionModel *model);

signals:

public slots:
};

#endif // VFSAJOBRESULT_H
