#include "ModelData.h"

QVariant ModelData::toVariant() const
{
    QVariantMap map;
    map.insert("From", mFrom);
    map.insert("Until", mUntil);
    map.insert("Resistivity", mResistivity);
    map.insert("Thickness", mThickness);
    map.insert("Depth", mDepth);
//    map.insert("mTransverseResistence", mTransverseResistence);
//    map.insert("mLongitudinalConductance", mLongitudinalConductance);
//    map.insert("mProbabilityDensityFunction", mProbabilityDensityFunction);
    return map;
}

void ModelData::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mFrom = map.value("From").toDouble();
    mUntil = map.value("Until").toDouble();
    mResistivity = map.value("Resistivity").toDouble();
    mThickness = map.value("Thickness").toDouble();
    mDepth = map.value("Depth").toDouble();
//    mTransverseResistence = map.value("mTransverseResistence").toDouble();
//    mLongitudinalConductance = map.value("mLongitudinalConductance").toDouble();
//    mProbabilityDensityFunction = map.value("mProbabilityDensityFunction").toDouble();
}

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    mFrom = mUntil = mResistivity = mThickness = mDepth = mTransverseResistence = mLongitudinalConductance = mProbabilityDensityFunction = 0.0;
}

ModelData::ModelData(const ModelData &md)
{
    mFrom = md.from();
    mUntil = md.until();
    mResistivity = md.resistivity();
    mThickness = md.thickness();
    mDepth = md.depth();
    mTransverseResistence = md.transverseResistence();
    mLongitudinalConductance = md.longitudinalConductance();
    mProbabilityDensityFunction = md.probabilityDensityFunction();
    this->setParent(md.parent());
}

ModelData &ModelData::operator=(const ModelData &rhs)
{
    mFrom = rhs.from();
    mUntil = rhs.until();
    mResistivity = rhs.resistivity();
    mThickness = rhs.thickness();
    mDepth = rhs.depth();
    mTransverseResistence = rhs.transverseResistence();
    mLongitudinalConductance = rhs.longitudinalConductance();
    mProbabilityDensityFunction = rhs.probabilityDensityFunction();
    this->setParent(rhs.parent());
    return *this;
}

ModelData::~ModelData()
{

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

double ModelData::probabilityDensityFunction() const
{
    return mProbabilityDensityFunction;
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

void ModelData::setProbabilityDensityFunction(double value)
{
    mProbabilityDensityFunction = value;
}
