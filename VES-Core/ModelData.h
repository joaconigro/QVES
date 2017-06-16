#ifndef MODELDATA_H
#define MODELDATA_H

#include "ves-core_global.h"
#include <QObject>
#include "Serializable.h"

class VESCORESHARED_EXPORT ModelData : public QObject, public Serializable
{
    Q_OBJECT

    double mFrom;
    double mUntil;
    double mResistivity;
    double mThickness;
    double mDepth;
    double mTransverseResistence;
    double mLongitudinalConductance;

public:
    explicit ModelData(QObject *parent = nullptr);
    explicit ModelData(const ModelData &md);

    ~ModelData();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    double from() const;
    double until() const;
    double resistivity() const;
    double thickness() const;
    double depth() const;
    double transverseResistence() const;
    double longitudinalConductance() const;

    void setFrom(const double value);
    void setUntil(const double value);
    void setResistivity(const double value);
    void setThickness(const double value);
    void setDepth(const double value);
    void setTransverseResistence(const double value);
    void setLongitudinalConductance(const double value);

    ModelData& operator=(const ModelData &rhs);

signals:

public slots:
};

Q_DECLARE_METATYPE(ModelData)

#endif // MODELDATA_H
