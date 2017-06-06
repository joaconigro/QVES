#ifndef SPLICEDATA_H
#define SPLICEDATA_H

#include "ves-core_global.h"
#include "BasicData.h"

class VESCORESHARED_EXPORT SpliceData : public BasicData
{

    quint8 mSection;

public:
    explicit SpliceData(QObject *parent = nullptr);
    explicit SpliceData(const double ab2, const double res, const double sd = 0.0, QObject *parent = nullptr);

    quint8 section() const;

    void setSection(quint8 sect);
};

#endif // SPLICEDATA_H
