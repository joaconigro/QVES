#ifndef SPLICEDATA_H
#define SPLICEDATA_H

#include "ves-core_global.h"
#include "BasicData.h"
#include "Serializable.h"

class VESCORESHARED_EXPORT SpliceData : public BasicData
{

    int mSection;

public:
    explicit SpliceData(QObject *parent = nullptr);
    explicit SpliceData(const BasicData &bd);
    explicit SpliceData(const double ab2, const double res, const double sd = 0.0, QObject *parent = nullptr);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    int section() const;

    void setSection(int sect);
};

Q_DECLARE_METATYPE(SpliceData)

#endif // SPLICEDATA_H
