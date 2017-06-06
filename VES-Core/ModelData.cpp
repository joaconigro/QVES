#include "ModelData.h"

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    mFrom = mUntil = mResistivity = mThickness = mDepth = mTransverseResistence = mLongitudinalConductance = 0.0;
}

double ModelData::from() const
{
    return mFrom;
}

double ModelData::until() const
{
    return mUntil;
}

double ModelData::resistivity() const
{
    return mResistivity;
}

double ModelData::thickness() const
{
    return mThickness;
}

double ModelData::depth() const
{
    return mDepth;
}

double ModelData::transverseResistence() const
{
    return mTransverseResistence;
}

double ModelData::longitudinalConductance() const
{
    return mLongitudinalConductance;
}

void ModelData::setFrom(const double value)
{
    mFrom = value;
}

void ModelData::setUntil(const double value)
{
    mUntil = value;
}

void ModelData::setResistivity(const double value)
{
    mResistivity = value;
}

void ModelData::setThickness(const double value)
{
    mThickness = value;
}

void ModelData::setDepth(const double value)
{
    mDepth = value;
}

void ModelData::setTransverseResistence(const double value)
{
    mTransverseResistence = value;
}

void ModelData::setLongitudinalConductance(const double value)
{
    mLongitudinalConductance = value;
}
