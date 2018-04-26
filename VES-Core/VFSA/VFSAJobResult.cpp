#include "VFSAJobResult.h"

VFSAInversionModel *VFSAJobResult::finalModel() const
{
    return mFinalModel;
}

void VFSAJobResult::setFinalModel(VFSAInversionModel *finalModel)
{
    mFinalModel = new VFSAInversionModel(*finalModel);
}

QList<VFSAInversionModel *> VFSAJobResult::allModels() const
{
    return mAllModels;
}

void VFSAJobResult::appendModel(VFSAInversionModel *model)
{
    mAllModels.append(model);
}

void VFSAJobResult::discardErroneousModels(const double maxError)
{
    //Remove models with error greater than tolerance.
    int index = 0;
    do {
        if (mAllModels.at(index)->getVFSAError() > maxError){
            delete mAllModels.at(index);
            mAllModels.removeAt(index);
        } else {
            index += 1;
        }
    } while (index < mAllModels.count());
}

void VFSAJobResult::discardModelsByPDF(const double threshold, const int pdfIndex)
{
    //Remove models with pdf lower than tolerance.
    int index = 0;
    do {
        if (mAllModels.at(index)->getParameterPDFs().at(pdfIndex) < threshold){
            delete mAllModels.at(index);
            mAllModels.removeAt(index);
        } else {
            index += 1;
        }
    } while (index < mAllModels.count());
}

VFSAJobResult::VFSAJobResult(QObject *parent) : QObject(parent)
{
    
}

VFSAJobResult::~VFSAJobResult()
{
    //Remove models.
    do {
         delete mAllModels.at(0);
         mAllModels.removeAt(0);
    } while (mAllModels.count() > 0);
}
