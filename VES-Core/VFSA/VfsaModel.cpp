#include "VfsaModel.h"

VfsaModel::VfsaModel(QObject *parent) : QObject(parent)
{
    mVFSAError = 0.0;
}

double VfsaModel::getVFSAError() const
{
    return mVFSAError;
}

void VfsaModel::setVFSAError(double value)
{
    mVFSAError = value;
}

QList<VfsaData> VfsaModel::getParameters() const
{
    return mParameters;
}

void VfsaModel::addVFSAData(const VfsaData &data)
{
    mParameters.append(data);
}

void VfsaModel::addVFSAData(const double &data)
{
    VfsaData newData(data, 0.0, this);
    mParameters.append(newData);
}
