#include "VES.h"
#include <QUuid>

int VES::searchSections()
{
    int section = 1;
    int repeaterCounter = 0;
    double auxAB = mSplices.at(0).ab2Distance();

    //This loops finds all sections on field data
    //There must be two splices by section, to work well
    for (int i = 1; i < mSplices.count(); i++){
        if (auxAB == mSplices.at(i).ab2Distance()){
            repeaterCounter++;
            if (repeaterCounter == 1){
                mSplices[i].setSection(section + 1);
            } else if (repeaterCounter == 2) {
                section++;
                repeaterCounter = 0;
                mSplices[i].setSection(section);
            }
        } else {
            mSplices[i].setSection(section);
            auxAB = mSplices.at(i).ab2Distance();
        }
    }
    return section;
}

void VES::correctSplices(int maxSections)
{
    double correctFactor, auxAB;
    double auxFactor = 1.0;
    bool alredyCalculated;

    while (maxSections > 0) {
        alredyCalculated = false;
        correctFactor = auxFactor;
        for (int i = mSplices.count() - 1; i > 0 ; i--){
            if (mSplices.at(i).section() == maxSections){
                mSplices[i].setResistivity(mSplices.at(i).resistivity() * correctFactor);
                auxAB = mSplices.at(i).ab2Distance();
            }
            if ((mSplices.at(i).section() == maxSections-1) && (mSplices.at(i).ab2Distance() == auxAB)){
                if (alredyCalculated == false){
                    auxFactor = mSplices.at(i+1).resistivity() / mSplices.at(i).resistivity();
                    alredyCalculated = true;
                }
            }
        }
        --maxSections;
    }
}

void VES::cleanDuplicatedSplices()
{
//    bool remove = true;
//    while (remove) {
        for (int i = mSplices.count() - 1; i > 0 ; i--){
            if (mSplices.at(i).ab2Distance() == mSplices.at(i-1).ab2Distance()){
                mSplices.removeAt(i-1);
            }
        }
//    }
}

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

int VES::currentIndexModel() const
{
    return mCurrentIndexModel;
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

void VES::setLocation(LocationData *loc)
{
    loc->setParent(this);
    mLocation = loc;
}

void VES::setCurrentIndexModel(const int value)
{
    if (mCurrentIndexModel != value){
        mCurrentIndexModel = value;
        mCurrentModel = &(mModels[mCurrentIndexModel]);
    }
}

void VES::setFieldData(const QList<BasicData> &list)
{
    foreach (const BasicData &bd, list) {
        BasicData newBd(bd.ab2Distance(), bd.resistivity(), bd.standardDeviation(), this);
        mFieldData.append(newBd);
    }
}

void VES::setModels(const QList<InversionModel> &list)
{
    foreach (const InversionModel &im, list) {
        InversionModel newIm = im;
        mModels.append(newIm);
    }
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

void VES::createSplices()
{
    mSplices.clear();

    foreach (const BasicData &bd, mFieldData) {
        SpliceData sd(bd);
        mSplices.append(sd);
    }

    int maxSection = searchSections();
    correctSplices(maxSection);
    cleanDuplicatedSplices();

}
