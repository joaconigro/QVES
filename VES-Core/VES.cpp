#include "VES.h"
#include <QUuid>
#include "QtMath"
#include "VFSA/VFSACalculator.h"

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
        for (int i = mSplices.count() - 1; i >= 0 ; --i){
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
    for (int i = mSplices.count() - 1; i > 0 ; --i){
        if (mSplices.at(i).ab2Distance() == mSplices.at(i-1).ab2Distance()){
            mSplices.removeAt(i-1);
        }
    }
}

VES::VES(QObject *parent) : QObject(parent)
{
    mId = QUuid::createUuid().toString();
    mName = mFieldOperator = mEquipment = mComment = "";
    mDate = QDate::currentDate();
    mCurrentIndexModel = -1;
    mMinX = mMinY = mMaxX = mMaxY = 0.0;
}

VES::VES(const VES &ve)
{
    mId = QUuid::createUuid().toString();

    mName = ve.name();
    mFieldOperator = ve.fieldOperator();
    mEquipment = ve.equipment();
    mComment = ve.comment();
    mCurrentIndexModel = ve.currentIndexModel();
    mMinX = ve.minX();
    mMinY = ve.minY();
    mMaxX = ve.maxX();
    mMaxY = ve.maxY();
    QLocale qLoc;
    mDate = qLoc.toDate(ve.date(), "dd/MM/yyyy");
    mFieldData = ve.fieldData();
    mSplices = ve.splices();
    mLocation = ve.location();
    mModels = ve.models();
    mCurrentModel = ve.currentModel();
    //mPreviousParameters = ve.previousParameters();
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

LocationData VES::location() const
{
    return mLocation;
}

QList<InversionModel *> VES::models() const
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

//VFSAParameters VES::previousParameters() const
//{
//    return mPreviousParameters;
//}

VFSAParameters VES::currentParameters() const
{
    return mCurrentParameters;
}

double VES::minX() const
{
    return mMinX;
}

double VES::minY() const
{
    return mMinY;
}

double VES::maxX() const
{
    return mMaxX;
}

double VES::maxY() const
{
    return mMaxY;
}

void VES::setName(const QString name)
{
    if (mName != name){
        mName = name;
        emit nameChanged();
    }
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

void VES::setLocation(LocationData loc)
{
    loc.setParent(this);
    mLocation = loc;
}

void VES::setCurrentIndexModel(const int value)
{
    if (value >= 0 && value < mModels.count()){
        if (mCurrentIndexModel != value){
            mCurrentIndexModel = value;
            mCurrentModel = mModels[mCurrentIndexModel];
            findMaxAndMin();
        }
    } else {
        mCurrentModel = nullptr;
    }
    emit selectedModelChanged(value);
}

void VES::setFieldData(const QList<BasicData> &list)
{
    foreach (const BasicData &bd, list) {
        BasicData newBd(bd.ab2Distance(), bd.resistivity(), bd.standardDeviation(), this);
        mFieldData.append(newBd);
    }
}

void VES::setModels(const QList<InversionModel *> &list)
{
    for(int i = 0; i < list.count(); i++){
        InversionModel *newIm = list[i];
        newIm->setParent(this);
        mModels.append(newIm);
    }
}

void VES::setCurrentParameters(const VFSAParameters &paramters)
{
    mCurrentParameters = paramters;
}

QVariant VES::toVariant() const
{
    QVariantMap map;
    map.insert("Name", mName);
    map.insert("Id", mId);
    map.insert("FieldOperator", mFieldOperator);
    map.insert("Equipment", mEquipment);
    map.insert("Comment", mComment);
    map.insert("Date", date());
    map.insert("Location", mLocation.toVariant());
    map.insert("CurrentIndexModel", mCurrentIndexModel);
    //map.insert("mPreviousParameters", mPreviousParameters.toVariant());
    map.insert("CurrentParameters", mCurrentParameters.toVariant());

    QVariantList basic;
    for (const auto& cd : mFieldData) {
    basic.append(cd.toVariant());
    }
    map.insert("FieldData", basic);

    QVariantList spli;
    for (const auto& cd : mSplices) {
    spli.append(cd.toVariant());
    }
    map.insert("Splices", spli);

    QVariantList modeled;
    for (const auto& md : mModels) {
        modeled.append(md->toVariant());
    }
    map.insert("Models", modeled);

    return map;
}

void VES::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mName = map.value("Name").toString();
    mId = map.value("Id").toString();
    mFieldOperator = map.value("FieldOperator").toString();
    mEquipment = map.value("Equipment").toString();
    mComment = map.value("Comment").toString();
    setDate(map.value("Date").toString());
    mLocation.fromVariant(map.value("Location"));
    //mPreviousParameters.fromVariant(map.value("mPreviousParameters"));
    mCurrentParameters.fromVariant(map.value("CurrentParameters"));

    QVariantList basic = map.value("FieldData").toList();
    for(const QVariant& data : basic) {
        BasicData calc;
        calc.fromVariant(data);
        mFieldData.append(calc);
    }

    QVariantList spli = map.value("Splices").toList();
    for(const QVariant& data : spli) {
        SpliceData calc;
        calc.fromVariant(data);
        mSplices.append(calc);
    }

    QVariantList modeled = map.value("Models").toList();
    for(const QVariant& data : modeled) {
        if (data.toMap().contains("ZohdyFilter")){
             auto* mod = new ZohdyModel(this);
             mod->fromVariant(data);
             mModels.append(mod);
        } else {
            auto* mod = new VFSAInversionModel(this);
            mod->fromVariant(data);
            mModels.append(mod);
        }       
    }

    setCurrentIndexModel(map.value("CurrentIndexModel").toInt());
}

VES &VES::operator =(const VES &rhs)
{
    mId = QUuid::createUuid().toString();

    mName = rhs.name();
    mFieldOperator = rhs.fieldOperator();
    mEquipment = rhs.equipment();
    mComment = rhs.comment();
    mCurrentIndexModel = rhs.currentIndexModel();
    mMinX = rhs.minX();
    mMinY = rhs.minY();
    mMaxX = rhs.maxX();
    mMaxY = rhs.maxY();
    QLocale qLoc;
    mDate = qLoc.toDate(rhs.date(), "dd/MM/yyyy");
    mFieldData = rhs.fieldData();
    mSplices = rhs.splices();
    mLocation = rhs.location();
    mModels = rhs.models();
    mCurrentModel = rhs.currentModel();
    //mPreviousParameters = rhs.previousParameters();
    mCurrentParameters = rhs.currentParameters();
    this->setParent(rhs.parent());
    return *this;
}

void VES::findMaxAndMin()
{
    mMinX = mMinY = 1000000.0;
    mMaxX = mMaxY = -1.0;

    foreach (const auto &item, mFieldData) {
        mMinX = qMin(mMinX, item.ab2Distance());
        mMaxX = qMax(mMaxX, item.ab2Distance());
        mMinY = qMin(mMinY, item.resistivity());
        mMaxY = qMax(mMaxY, item.resistivity());
    }

    foreach (const auto &item, mSplices) {
        mMinX = qMin(mMinX, item.ab2Distance());
        mMaxX = qMax(mMaxX, item.ab2Distance());
        mMinY = qMin(mMinY, item.resistivity());
        mMaxY = qMax(mMaxY, item.resistivity());
    }

    if (mCurrentModel){
        foreach (const auto &item, mCurrentModel->calculatedData()) {
            mMinX = qMin(mMinX, item.ab2Distance());
            mMaxX = qMax(mMaxX, item.ab2Distance());
            mMinY = qMin(mMinY, item.resistivity());
            mMaxY = qMax(mMaxY, item.resistivity());
        }

        for (int i = 0; i < mCurrentModel->model().count(); ++i) {
            if (i>0){
                mMinX = qMin(mMinX, mCurrentModel->model().at(i).from());
           }
            if (i < mCurrentModel->model().count() - 1){
                mMaxX = qMax(mMaxX, mCurrentModel->model().at(i).until());
           }
            mMinY = qMin(mMinY, mCurrentModel->model().at(i).resistivity());
            mMaxY = qMax(mMaxY, mCurrentModel->model().at(i).resistivity());
        }
    }

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

void VES::dataEdited(const int dataType, const int row, const int column, const double value)
{
    switch (dataType) {
    case 0:
        updateFieldData(row, column, value);
        break;
    case 3:
        updateModeledData(row, column, value);
        break;
    default:
        break;
    }
}

void VES::updateModeledData(const int row, const int column, const double value)
{
    mCurrentModel->updateModeledData(row, column, value);
    mCurrentModel->updateInversionModelEdited(splices());
    emit currentModelModified();
}


void VES::updateFieldData(const int row, const int column, const double value)
{
    if (column == 0){
        mFieldData[row].setAb2Distance(value);
    } else if (column == 1) {
        mFieldData[row].setResistivity(value);
    } else {
        return;
    }

    createSplices();
    emit fieldDataModified();

    if(mModels.count()>0){
        foreach (auto& model, mModels) {
            model->updateModelError(splices());
        }
        emit currentModelModified();
    }

}

ZohdyModel* VES::zohdyInversion(const int zohdyFilter, const bool autoDZ, const double autoDZThreshold)
{
    int zohdyCounter = 0;
    foreach (const InversionModel *im, mModels) {
        if (im->usedAlgorithm() == InversionModel::InversionAlgorithm::Zohdy){
            ++zohdyCounter;
        }
    }

    InversionModel::ZohdyFilters selectedFilter = static_cast<InversionModel::ZohdyFilters>(zohdyFilter);

    ZohdyModel* zm = new ZohdyModel("Zohdy "+ QString::number(zohdyCounter), selectedFilter, this, autoDZ, autoDZThreshold);
    zm->setIsSmoothing(false);
    zm->inversion(splices());

    QList<SpliceData> calcData;
    for (const auto& cd : zm->calculatedData()) {
        calcData.append(SpliceData(cd.ab2Distance(), cd.resistivity()));
    }
    zm->setIsSmoothing(true);
    zm->inversion(calcData);
    zm->updateModelError(splices());
    return zm;
}

void VES::VFSAInversion()
{
    auto vfsaCalculator = new VFSACalculator(mSplices, mCurrentParameters, this);
    vfsaCalculator->startInversion();
//    foreach (auto model, vfsaCalculator->getFinalModels()) {
//        mModels.append(new VFSAInversionModel(*model));
//    }
//    delete vfsaCalculator;
}

void VES::selectModel(const int modelIndex)
{
    setCurrentIndexModel(modelIndex);
}

void VES::darZarrouk(const QList<int>& bedIndices)
{
    if (mCurrentModel && bedIndices.count()>1){
        mCurrentModel->darZarrouk(bedIndices);
        mCurrentModel->updateInversionModelEdited(mSplices);
        mCurrentModel->updateModelError(mSplices);
        emit currentModelModified();
    }
}

void VES::newZohdyModel(const int numberOfBeds)
{
    int zohdyCounter = 0;
    foreach (const InversionModel *im, mModels) {
        if (im->usedAlgorithm() == InversionModel::InversionAlgorithm::Zohdy){
            ++zohdyCounter;
        }
    }

    ZohdyModel* zm = new ZohdyModel("Zohdy "+ QString::number(zohdyCounter), numberOfBeds, this);
    mModels.append(zm);
    setCurrentIndexModel(mModels.indexOf(zm));
}

void VES::addInversionModel(InversionModel *model)
{
    model->setParent(this);
    mModels.append(model);
    setCurrentIndexModel(mModels.indexOf(model));
}

void VES::removeInversionModel(InversionModel *model, const int newModelIndex)
{
    int modelIndex = mModels.indexOf(model);
    mModels.removeAt(modelIndex);
    setCurrentIndexModel(newModelIndex);
}
