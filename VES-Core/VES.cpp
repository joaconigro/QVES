#include "VES.h"
#include <QUuid>

VES::VES(QObject *parent) : QObject(parent)
{
    mId = QUuid::createUuid().toString();
    mName = mFieldOperator = mEquipment = mComment = "";
    mLocation = new LocationData(this);
    mDate = QDate::currentDate();
}

VES::VES(const VES &ve)
{
    mId = QUuid::createUuid().toString();

    mName = ve.name();
    mFieldOperator = ve.fieldOperator();
    mEquipment = ve.equipment();
    mComment = ve.comment();
    QLocale qLoc;
    mDate = qLoc.toDate(ve.date(), "dd/MM/yyyy");
    mFieldData = ve.fieldData();
    mSplices = ve.splices();
    mLocation = ve.location();
    mModels = ve.models();
    mCurrentModel = ve.currentModel();
    mPreviousParameters = ve.previousParameters();
    mCurrentParameters = ve.currentParameters();
    this->setParent(ve.parent());
}

QString VES::name() const
{
    return mName;
}

QString VES::id() const
{
    return mId;
}

QString VES::fieldOperator() const
{
    return mFieldOperator;
}

QString VES::equipment() const
{
    return mEquipment;
}

QString VES::comment() const
{
    return mComment;
}

QString VES::date() const
{
    QLocale qLoc;
    return qLoc.toString(mDate, "dd/MM/yyyy");
}

QList<BasicData> VES::fieldData() const
{
    return mFieldData;
}

QList<SpliceData> VES::splices() const
{
    return mSplices;
}

LocationData *VES::location() const
{
    return mLocation;
}

QList<InversionModel> VES::models() const
{
    return mModels;
}

InversionModel *VES::currentModel() const
{
    return mCurrentModel;
}

VfsaParameters *VES::previousParameters() const
{
    return mPreviousParameters;
}

VfsaParameters *VES::currentParameters() const
{
    return mCurrentParameters;
}

void VES::setName(const QString name)
{
    mName = name;
}

void VES::setFieldOperator(const QString fieldOp)
{
    mFieldOperator = fieldOp;
}

void VES::setEquipment(const QString equip)
{
    mEquipment = equip;
}

void VES::setComment(const QString comm)
{
    mComment = comm;
}

void VES::setDate(const QString stringDate)
{
    QLocale qLoc;
    mDate = qLoc.toDate(stringDate, "dd/MM/yyyy");
}

QVariant VES::toVariant() const
{
    QVariantMap map;
    map.insert("mName", mName);

    return map;
}

void VES::fromVariant(const QVariant &variant)
{

}
