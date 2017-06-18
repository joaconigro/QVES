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
    LocationData mLocation;
    QList<InversionModel> mModels;

public:
    explicit VES(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VES_H
