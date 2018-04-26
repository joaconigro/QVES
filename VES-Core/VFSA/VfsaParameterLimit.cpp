#include "VfsaParameterLimit.h"

VfsaParameterLimit::VfsaParameterLimit(QObject *parent) : QObject(parent)
{
    mLower = mUpper = 1.0;
}

VfsaParameterLimit::VfsaParameterLimit(const double low, const double upp, QObject *parent) : QObject(parent)
{
    mLower = low;
    mUpper = upp;
}

VfsaParameterLimit::VfsaParameterLimit(const VfsaParameterLimit &vpf)
{
    mLower = vpf.lower();
    mUpper = vpf.upper();
    this->setParent(vpf.parent());
}

QVariant VfsaParameterLimit::toVariant() const
{
    QVariantMap map;
    map.insert("mLower", mLower);
    map.insert("mUpper", mUpper);
    return map;
}

void VfsaParameterLimit::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mLower = map.value("mLower").toDouble();
    mUpper = map.value("mUpper").toDouble();
}

double VfsaParameterLimit::lower() const
{
    return mLower;
}

double VfsaParameterLimit::upper() const
{
    return mUpper;
}

void VfsaParameterLimit::setLower(const double value)
{
    mLower = value;
}

void VfsaParameterLimit::setUpper(const double value)
{
    mUpper = value;
}

VfsaParameterLimit &VfsaParameterLimit::operator =(const VfsaParameterLimit &rhs)
{
    mLower = rhs.lower();
    mUpper = rhs.upper();
    this->setParent(rhs.parent());
    return *this;
}

bool VfsaParameterLimit::operator ==(const VfsaParameterLimit &rhs) const
{
    return (mLower == rhs.lower() && mUpper == rhs.upper());
}

bool VfsaParameterLimit::operator !=(const VfsaParameterLimit &rhs) const
{
    return (mLower != rhs.lower() || mUpper != rhs.upper());
}
