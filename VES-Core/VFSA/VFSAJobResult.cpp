#include "VFSAJobResult.h"

VFSAInversionModel *VFSAJobResult::finalModel() const
{
    return mFinalModel;
}

void VFSAJobResult::setFinalModel(const int modelNumber)
{
    mFinalModel = new VFSAInversionModel(*(mAllModels.last()));
    mFinalModel->setName("VFSA "+ QString::number(modelNumber));
}

QList<VFSAInversionModel *> VFSAJobResult::allModels() const
{
    return mAllModels;
}

void VFSAJobResult::appendModel(VFSAInversionModel *model)
{
    mAllModels.append(model);
}

void VFSAJobResult::clearModels()
{
    qDeleteAll(mAllModels);
    mAllModels.clear();
//    //Remove models with error greater than tolerance.
//    int index = 0;
//    do {
//        if (mAllModels.at(index)->getVFSAError() > maxError){
//            delete mAllModels.at(index);
//            mAllModels.removeAt(index);
//        } else {
//            index += 1;
//        }
//    } while (index < mAllModels.count());
}

VFSAJobResult::VFSAJobResult(QObject *parent) : QObject(parent)
{
    
}

VFSAJobResult::~VFSAJobResult()
{
    //Remove models.
    while (mAllModels.count() > 0) {
         delete mAllModels.at(0);
         mAllModels.removeAt(0);
    }
}
