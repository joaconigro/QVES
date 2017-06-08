#ifndef BASICDATA_H
#define BASICDATA_H

#include <QObject>
#include "ves-core_global.h"
#include "Serializable.h"

class VESCORESHARED_EXPORT BasicData : public QObject, public Serializable
{
    Q_OBJECT

protected:
    double mAb2Distance;
    double mResistivity;
    double mStandardDeviation;

public:
    explicit BasicData(QObject *parent = nullptr);
    explicit BasicData(const double ab2, const double res, const double sd = 0.0, QObject *parent = nullptr);
    explicit BasicData(const BasicData& bd);
    ~BasicData();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    double ab2Distance() const;
    double resistivity() const;
    double standardDeviation() const;

    void setAb2Distance(const double value);
    void setResistivity(const double value);
    void setStandardDeviation(const double value);

    bool isValid() const;

    bool operator ==(const BasicData &rhs) const;
    bool operator !=(const BasicData &rhs) const;
    bool operator >=(const BasicData &rhs) const;
    bool operator >(const BasicData &rhs) const;
    bool operator <=(const BasicData &rhs) const;
    bool operator <(const BasicData &rhs) const;



signals:

public slots:
};

Q_DECLARE_METATYPE(BasicData)

#endif // BASICDATA_H
