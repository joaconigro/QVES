#ifndef VES_H
#define VES_H

#include "ves-core_global.h"
#include <QObject>
#include "BasicData.h"
#include "SpliceData.h"
#include "LocationData.h"
#include "InversionModel.h"
#include <QList>
#include "Serializable.h"
#include <QDate>
#include "VfsaParameters.h"

class VESCORESHARED_EXPORT VES : public QObject, public Serializable
{
    Q_OBJECT

private:
    QString mName;
    QString mId;
    QString mFieldOperator;
    QString mEquipment;
    QString mComment;
    QDate mDate;
    QList<BasicData> mFieldData;
    QList<SpliceData> mSplices;
    LocationData *mLocation;
    QList<InversionModel> mModels;
    InversionModel *mCurrentModel;
    VfsaParameters *mPreviousParameters;
    VfsaParameters *mCurrentParameters;

public:
    explicit VES(QObject *parent = nullptr);
    VES(const VES& ve);

    //Getters
    QString name() const;
    QString id() const;
    QString fieldOperator() const;
    QString equipment() const;
    QString comment() const;
    QString date() const;
    QList<BasicData> fieldData() const;
    QList<SpliceData> splices() const;
    LocationData *location() const;
    QList<InversionModel> models() const;
    InversionModel *currentModel() const;
    VfsaParameters *previousParameters() const;
    VfsaParameters *currentParameters() const;

    //Setters
    void setName(const QString name);
    void setFieldOperator(const QString fieldOp);
    void setEquipment(const QString equip);
    void setComment(const QString comm);
    void setDate(const QString stringDate);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;
signals:

public slots:
};

Q_DECLARE_METATYPE(VES)

#endif // VES_H
