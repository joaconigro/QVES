#include "VFSAJobResult.h"

VFSAInversionModel *VFSAJobResult::finalModel() const
{
    return mFinalModel;
}

void VFSAJobResult::setFinalModel(VFSAInversionModel *finalModel)
{
    mFinalModel = finalModel;
}

QList<VFSAInversionModel *> VFSAJobResult::allModels() const
{
    return mAllModels;
}

void VFSAJobResult::appendModel(VFSAInversionModel *model)
{
    mAllModels.append(model);
}

VFSAJobResult::VFSAJobResult(QObject *parent) : QObject(parent)
{
    
}
