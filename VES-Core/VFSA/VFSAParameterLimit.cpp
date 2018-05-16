#include "VFSAParameterLimit.h"

VFSAParameterLimit::VFSAParameterLimit(QObject *parent) : QObject(parent)
{
    mLower = 1.0;
    mUpper = 2.0;
}

VFSAParameterLimit::VFSAParameterLimit(const double low, const double upp, QObject *parent) : QObject(parent)
{
    mLower = low;
    mUpper = upp;
}

VFSAParameterLimit::VFSAParameterLimit(const VFSAParameterLimit &vpf)
{
    mLower = vpf.lower();
    mUpper = vpf.upper();
    this->setParent(vpf.parent());
}

QVariant VFSAParameterLimit::toVariant() const
{
    QVariantMap map;
    map.insert("Lower", mLower);
    map.insert("Upper", mUpper);
    return map;
}

void VFSAParameterLimit::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mLower = map.value("Lower").toDouble();
    mUpper = map.value("Upper").toDouble();
}

double VFSAParameterLimit::lower() const
{
    return mLower;
}

double VFSAParameterLimit::upper() const
{
    return mUpper;
}

void VFSAParameterLimit::setLower(const double value)
{
    mLower = value;
}

void VFSAParameterLimit::setUpper(const double value)
{
    mUpper = value;
}

VFSAParameterLimit &VFSAParameterLimit::operator =(const VFSAParameterLimit &rhs)
{
    mLower = rhs.lower();
    mUpper = rhs.upper();
    this->setParent(rhs.parent());
    return *this;
}

bool VFSAParameterLimit::operator ==(const VFSAParameterLimit &rhs) const
{
    return (mLower == rhs.lower() && mUpper == rhs.upper());
}

bool VFSAParameterLimit::operator !=(const VFSAParameterLimit &rhs) const
{
    return (mLower != rhs.lower() || mUpper != rhs.upper());
}

bool VFSAParameterLimit::isValid() const
{
    return (mLower > 0 && mUpper > 0 && mLower < mUpper);
}
