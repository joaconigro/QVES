#ifndef SPLICEDATA_H
#define SPLICEDATA_H

#include "ves-core_global.h"
#include "BasicData.h"

class VESCORESHARED_EXPORT SpliceData : public BasicData
{

    quint8 mSection;

public:
    SpliceData();

    quint8 section() const;

    void setSection(quint8 sect);
};

#endif // SPLICEDATA_H
