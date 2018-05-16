#include "SpliceData.h"

QVariant SpliceData::toVariant() const
{
    QVariantMap map;
    map.insert("Ab2Distance", mAb2Distance);
    map.insert("Resistivity", mResistivity);
    map.insert("StandardDeviation", mStandardDeviation);
    map.insert("Section", mSection);
    return map;
}

void SpliceData::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mAb2Distance = map.value("Ab2Distance").toDouble();
    mResistivity = map.value("Resistivity").toDouble();
    mStandardDeviation = map.value("StandardDeviation").toDouble();
    mSection = map.value("Section").toInt();
}

SpliceData::SpliceData(QObject *parent) :
    BasicData(parent)
{
    mSection = 1;
}

SpliceData::SpliceData(const BasicData &bd) :
    BasicData(bd)
{
     mSection = 1;
}

SpliceData::SpliceData(const double ab2, const double res, const double sd, QObject *parent) :
    BasicData(ab2, res, sd, parent)
{
    mSection = 1;
}

int SpliceData::section() const
{
    return mSection;
}

void SpliceData::setSection(int sect)
{
    mSection = sect;
}
