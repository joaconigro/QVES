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

double VfsaData::Value() const
{
    return mValue;
}

double VfsaData::Pdf() const
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
