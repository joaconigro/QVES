#include "SpliceData.h"

SpliceData::SpliceData()
{

}

quint8 SpliceData::section() const
{
    return mSection;
}

void SpliceData::setSection(quint8 sect)
{
    mSection = sect;
}
