#include "VfsaData.h"

VfsaData::VfsaData(QObject *parent) : QObject(parent)
{
    mValue = mPdf = 0.0;
}

VfsaData::VfsaData(const double value, const double pdf, QObject *parent) : QObject(parent)
{
    mValue = value;
    mPdf = pdf;
}

VfsaData::VfsaData(const VfsaData &vd) : QObject(vd.parent())
{
    mValue = vd.value();
    mPdf = vd.pdf();
    this->setParent(vd.parent());
}

double VfsaData::value() const
{
    return mValue;
}

double VfsaData::pdf() const
{
    return mPdf;
}

void VfsaData::setValue(const double value)
{
    mValue = value;
}

void VfsaData::setPdf(const double value)
{
    mPdf = value;
}
