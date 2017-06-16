#include "ModelData.h"

QVariant ModelData::toVariant() const
{
    QVariantMap map;
    map.insert("mFrom", mFrom);
    map.insert("mUntil", mUntil);
    map.insert("mResistivity", mResistivity);
    map.insert("mThickness", mThickness);
    map.insert("mDepth", mDepth);
    map.insert("mTransverseResistence", mTransverseResistence);
    map.insert("mLongitudinalConductance", mLongitudinalConductance);
    return map;
}

void ModelData::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mFrom = map.value("mFrom").toDouble();
    mUntil = map.value("mUntil").toDouble();
    mResistivity = map.value("mResistivity").toDouble();
    mThickness = map.value("mThickness").toDouble();
    mDepth = map.value("mDepth").toDouble();
    mTransverseResistence = map.value("mTransverseResistence").toDouble();
    mLongitudinalConductance = map.value("mLongitudinalConductance").toDouble();
}

ModelData::ModelData(QObject *parent) : QObject(parent)
{
    mFrom = mUntil = mResistivity = mThickness = mDepth = mTransverseResistence = mLongitudinalConductance = 0.0;
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
