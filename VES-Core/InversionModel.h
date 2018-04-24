#ifndef INVERSIONMODEL_H
#define INVERSIONMODEL_H

#include "ves-core_global.h"
#include <QObject>
#include "BasicData.h"
#include "SpliceData.h"
#include "ModelData.h"
#include "VFSA/VfsaParameters.h"
#include <QList>
#include "Serializable.h"
#include <QVector>

class VESCORESHARED_EXPORT InversionModel : public QObject, public Serializable
{
    Q_OBJECT

public:
    enum class InversionAlgorithm{Zohdy, Vfsa, Manual, Unkown};
    enum class ZohdyFilters{Johansen, ONeill};

protected:
    QString mName;
    QString mId;
    double mErrorResult;
    QString mErrorString;
    InversionAlgorithm mUsedAlgorithm;
    QList<BasicData> mCalculatedData;
    QList<ModelData> mModel;



    void calculateDepths(QList<ModelData> &model);
    void calculateThicknesses(QList<ModelData> &model);
    double calculateModelError(const QList<SpliceData> &fieldData, const QList<BasicData> &calculatedData) const;

public:
    explicit InversionModel(QObject *parent = nullptr);
    explicit InversionModel(const QString &name, QObject *parent = nullptr);
    InversionModel(const InversionModel& im);

    virtual QVariant toVariant() const override = 0;
    virtual void fromVariant(const QVariant& variant) override = 0;

    //Getters
    QString name() const;
    QString id() const;
    double errorResult() const;
    QString errorString();
    InversionAlgorithm usedAlgorithm() const;
    QList<BasicData> calculatedData() const;
    QList<ModelData> model() const;

    //Setters
    void setName(const QString value);
    void setUsedAlgorithm(const InversionAlgorithm value);
    void setCalculatedData(const QList<BasicData> &list);
    void appendCalculatedData(const BasicData &data);
    void setModelData(const QList<ModelData> &list);

    //Inversion functions
    virtual void inversion(const QList<SpliceData> &fieldData) = 0;
    virtual void updateInversionModelEdited(const QList<SpliceData> &fieldData) = 0;
    void updateModelError(const QList<SpliceData> &list);
    void darZarrouk(const QList<int> bedIndices);

    InversionModel& operator =(const InversionModel &rhs);

signals:

public slots:
    void updateModeledData(const int row, const int column, const double value);
};

//Q_DECLARE_METATYPE(InversionModel)

#endif // INVERSIONMODEL_H
