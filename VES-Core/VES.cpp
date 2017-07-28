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
    map.insert("mId", mId);
    map.insert("mFieldOperator", mFieldOperator);
    map.insert("mEquipment", mEquipment);
    map.insert("mComment", mComment);
    map.insert("mDate", date());
    map.insert("mLocation", &mLocation);
    map.insert("mCurrentModel", &mCurrentModel);
    map.insert("mPreviousParameters", &mPreviousParameters);
    map.insert("mCurrentParameters", &mCurrentParameters);

    QVariantList basic;
    for (const auto& cd : mFieldData) {
    basic.append(cd.toVariant());
    }
    map.insert("mFieldData", basic);

    QVariantList spli;
    for (const auto& cd : mSplices) {
    spli.append(cd.toVariant());
    }
    map.insert("mSplices", spli);

    QVariantList modeled;
    for (const auto& md : mModels) {
    modeled.append(md.toVariant());
    }
    map.insert("mModels", modeled);

    return map;
}

void VES::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mName = map.value("mName").toString();
    mId = map.value("mId").toString();
    mFieldOperator = map.value("mFieldOperator").toString();
    mEquipment = map.value("mEquipment").toString();
    mComment = map.value("mComment").toString();
    setDate(map.value("mDate").toString());
    mLocation = new LocationData(this);
    mLocation->fromVariant(map.value("mLocation"));

    mCurrentModel = new InversionModel(this);
    mCurrentModel->fromVariant(map.value("mCurrentModel"));

    mPreviousParameters = new VfsaParameters(this);
    mPreviousParameters->fromVariant(map.value("mPreviousParameters"));

    mCurrentParameters = new VfsaParameters(this);
    mCurrentParameters->fromVariant(map.value("mCurrentParameters"));


    QVariantList basic = map.value("mFieldData").toList();
    for(const QVariant& data : basic) {
        BasicData calc;
        calc.fromVariant(data);
        mFieldData.append(calc);
    }

    QVariantList spli = map.value("mSplices").toList();
    for(const QVariant& data : spli) {
        SpliceData calc;
        calc.fromVariant(data);
        mSplices.append(calc);
    }

    QVariantList modeled = map.value("mModels").toList();
    for(const QVariant& data : modeled) {
        InversionModel mod;
        mod.fromVariant(data);
        mModels.append(mod);
    }
}

VES &VES::operator =(const VES &rhs)
{
    mId = QUuid::createUuid().toString();

    mName = rhs.name();
    mFieldOperator = rhs.fieldOperator();
    mEquipment = rhs.equipment();
    mComment = rhs.comment();
    QLocale qLoc;
    mDate = qLoc.toDate(rhs.date(), "dd/MM/yyyy");
    mFieldData = rhs.fieldData();
    mSplices = rhs.splices();
    mLocation = rhs.location();
    mModels = rhs.models();
    mCurrentModel = rhs.currentModel();
    mPreviousParameters = rhs.previousParameters();
    mCurrentParameters = rhs.currentParameters();
    this->setParent(rhs.parent());
    return *this;
}
