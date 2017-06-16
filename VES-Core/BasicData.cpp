#include "BasicData.h"

QVariant BasicData::toVariant() const
{
    QVariantMap map;
    map.insert("mAb2Distance", mAb2Distance);
    map.insert("mResistivity", mResistivity);
    map.insert("mStandardDeviation", mStandardDeviation);
    return map;
}

void BasicData::fromVariant(const QVariant &variant)
{
     QVariantMap map = variant.toMap();
     mAb2Distance = map.value("mAb2Distance").toDouble();
     mResistivity = map.value("mResistivity").toDouble();
     mStandardDeviation = map.value("mStandardDeviation").toDouble();
}

BasicData::BasicData(QObject *parent) : QObject(parent)
{
    mAb2Distance = 0.0;
    mResistivity = 0.0;
    mStandardDeviation = 0.0;
}

BasicData::BasicData(const double ab2, const double res, const double sd, QObject *parent) : QObject(parent)
{
    mAb2Distance = ab2;
    mResistivity = res;
    mStandardDeviation = sd;
}

BasicData::BasicData(const BasicData &bd)
{
    mAb2Distance = bd.ab2Distance();
    mResistivity = bd.resistivity();
    mStandardDeviation = bd.standardDeviation();
    this->setParent(bd.parent());
}

BasicData::~BasicData()
{

}

double BasicData::ab2Distance() const
{
    return mAb2Distance;
}

double BasicData::resistivity() const
{
    return mResistivity;
}

double BasicData::standardDeviation() const
{
    return mStandardDeviation;
}

void BasicData::setAb2Distance(const double value)
{
    mAb2Distance = value;
}

void BasicData::setResistivity(const double value)
{
    mResistivity = value;
}

void BasicData::setStandardDeviation(const double value)
{
    mStandardDeviation = value;
}

bool BasicData::isValid() const
{
    return (mAb2Distance > 0.0 && mResistivity > 0.0);
}

bool BasicData::operator ==(const BasicData &rhs) const
{
    return (mAb2Distance == rhs.mAb2Distance);
}

bool BasicData::operator !=(const BasicData &rhs) const
{
    return (mAb2Distance != rhs.mAb2Distance);
}

bool BasicData::operator >=(const BasicData &rhs) const
{
    return (mAb2Distance >= rhs.mAb2Distance);
}

bool BasicData::operator >(const BasicData &rhs) const
{
    return (mAb2Distance > rhs.mAb2Distance);
}

bool BasicData::operator <=(const BasicData &rhs) const
{
    return (mAb2Distance <= rhs.mAb2Distance);
}

bool BasicData::operator <(const BasicData &rhs) const
{
    return (mAb2Distance < rhs.mAb2Distance);
}

BasicData &BasicData::operator =(const BasicData &rhs)
{
    mAb2Distance = rhs.ab2Distance();
    mResistivity = rhs.resistivity();
    mStandardDeviation = rhs.standardDeviation();
    this->setParent(rhs.parent());
    return *this;
}


