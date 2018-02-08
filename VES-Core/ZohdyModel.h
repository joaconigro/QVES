#ifndef ZOHDYMODEL_H
#define ZOHDYMODEL_H
#include "InversionModel.h"
#include "ves-core_global.h"

class VESCORESHARED_EXPORT ZohdyModel : public InversionModel
{

private:

    ZohdyFilters mZohdyFilter;

    //Zohdy inversion functions
    void chooseFilter(const ZohdyFilters filter, QVector<double> &a, double &w, double &s, double &dx);
    void TRS(const QList<SpliceData> &field, QList<BasicData> &calculated, QList<ModelData> &model, const QVector<double> a, const double w, const double s, const double dx);
    void zohdyInversion(const QList<SpliceData> &fieldData, const ZohdyFilters filter);

public:
    explicit ZohdyModel(QObject *parent = nullptr);
    explicit ZohdyModel(const QString &name, QObject *parent = nullptr);
    explicit ZohdyModel(const QString &name, const ZohdyFilters filter, QObject *parent = nullptr, const bool applyDarZarrouk = true, const double darZarroukThreshold = 0.12);
    explicit ZohdyModel(const InversionModel& im);
    ZohdyModel(const ZohdyModel& zm);
    //ZohdyModel();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    //Getters
    ZohdyFilters zohdyFilter() const;

    //Setters
    void setZohdyFilter(const ZohdyFilters value);

    void inversion(const QList<SpliceData> &fieldData) override;
};

Q_DECLARE_METATYPE(ZohdyModel)

#endif // ZOHDYMODEL_H
