#include "SpliceData.h"

QVariant SpliceData::toVariant() const
{
    QVariantMap map;
    map.insert("mAb2Distance", mAb2Distance);
    map.insert("mResistivity", mResistivity);
    map.insert("mStandardDeviation", mStandardDeviation);
    map.insert("mSection", mSection);
    return map;
}

void SpliceData::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mAb2Distance = map.value("mAb2Distance").toDouble();
    mResistivity = map.value("mResistivity").toDouble();
    mStandardDeviation = map.value("mStandardDeviation").toDouble();
    mSection = map.value("mSection").toInt();
}

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
