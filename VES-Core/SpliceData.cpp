#include "SpliceData.h"

SpliceData::SpliceData(QObject *parent) :
    BasicData(parent)
{
    mSection = 1;
}

SpliceData::SpliceData(const double ab2, const double res, const double sd, QObject *parent) :
    BasicData(ab2, res, sd, parent)
{
    mSection = 1;
}

quint8 SpliceData::section() const
{
    return mSection;
}

void SpliceData::setSection(quint8 sect)
{
    mSection = sect;
}
