#include "BasicData.h"

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

bool BasicData::operator ==(const BasicData rhs) const
{
    return (this->ab2Distance() == rhs.ab2Distance());
}

bool BasicData::operator !=(const BasicData rhs) const
{
    return (this->ab2Distance() != rhs.ab2Distance());
}


