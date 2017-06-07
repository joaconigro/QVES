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
