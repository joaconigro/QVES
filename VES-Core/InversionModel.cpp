#include "InversionModel.h"
#include <QUuid>
#include <QtMath>
#include <QLocale>

void InversionModel::calculateDepths(QList<ModelData> &model)
{
    //Calculate the first depth.
    model[0].setFrom(0.0);
    model[0].setUntil(model.at(0).thickness());
    model[0].setDepth(model.at(0).thickness());

    //Calculate all others depths.
    for(int i = 1; i<model.count(); i++){
        model[i].setFrom(model.at(i-1).until());
        model[i].setUntil(model.at(i).from() + model.at(i).thickness());
        model[i].setDepth(model.at(i).until());
    }

    //Set last bed as infinity.
    model[model.count() - 1].setDepth(qInf());
    model[model.count() - 1].setThickness(qInf());
    model[model.count() - 1].setUntil(qInf());
}

void InversionModel::calculateThicknesses(QList<ModelData> &model)
{
    //Calculate the first thickness.
    model[0].setFrom(0.0);
    model[0].setUntil(model.at(0).depth());
    model[0].setThickness(model.at(0).depth());

    //Calculate all others thicknesses.
    for(int i = 1; i<model.count(); i++){
        model[i].setFrom(model.at(i-1).until());
        model[i].setUntil(model.at(i).depth());
        model[i].setThickness(model.at(i).until() - model.at(i).from());
    }

    //Set last bed as infinity.
    model[model.count() - 1].setDepth(qInf());
    model[model.count() - 1].setThickness(qInf());
    model[model.count() - 1].setUntil(qInf());


}


double InversionModel::calculateModelError(const QList<SpliceData> &fieldData, const QList<BasicData> &calculatedData) const
{
    double sum = 0.0;
    double aux;

    //Calcula el error del modelo propuesto y lo guarda en la propiedad RMS del SEV
    for(int i = 0; i<fieldData.count(); i++){
        aux = (fieldData.at(i).resistivity() - calculatedData.at(i).resistivity()) / fieldData.at(i).resistivity();
        sum = aux * aux + sum;
    }

    double finalError = (sqrt(sum / fieldData.count()) * 100.0);
    return finalError;
}

InversionModel::InversionModel(QObject *parent) : QObject(parent)
{
    mId = QUuid::createUuid().toString();
}

InversionModel::InversionModel(const QString &name, QObject *parent) :
    QObject(parent),
    mName(name)
{
    mId = QUuid::createUuid().toString();
}

InversionModel::InversionModel(const InversionModel& im)
{
    mId = QUuid::createUuid().toString();

    mName = im.name();
    mErrorResult = im.errorResult();
    //mErrorString = im.errorString();
    mUsedAlgorithm = im.usedAlgorithm();
    mCalculatedData = im.calculatedData();
    mModel = im.model();
    this->setParent(im.parent());
}


//QVariant InversionModel::toVariant() const
//{
//    QVariantMap map;
//    map.insert("mName", mName);
//    map.insert("mId", mId);
//    map.insert("mErrorResult", mErrorResult);
//    map.insert("mErrorString", mErrorString);
//    map.insert("mUsedAlgorithm", static_cast<int>(mUsedAlgorithm));
////    map.insert("mZohdyFilter", static_cast<int>(mZohdyFilter));


//    QVariantList calculated;
//    for (const auto& cd : mCalculatedData) {
//    calculated.append(cd.toVariant());
//    }
//    map.insert("mCalculatedData", calculated);

//    QVariantList modeled;
//    for (const auto& md : mModel) {
//    modeled.append(md.toVariant());
//    }
//    map.insert("mModel", modeled);

//    return map;
//}

//void InversionModel::fromVariant(const QVariant &variant)
//{
//    QVariantMap map = variant.toMap();
//    mName = map.value("mName").toString();
//    mId = map.value("mId").toString();
//    mErrorResult = map.value("mErrorResult").toDouble();
//    mErrorString = map.value("mErrorString").toString();
//    mUsedAlgorithm = static_cast<InversionModel::InversionAlgorithm>(map.value("mUsedAlgorithm").toInt());
//   // mZohdyFilter = static_cast<InversionModel::ZohdyFilters>(map.value("mZohdyFilter").toInt());

//    QVariantList calculated = map.value("mCalculatedData").toList();
//    for(const QVariant& data : calculated) {
//        BasicData calc;
//        calc.fromVariant(data);
//        mCalculatedData.append(calc);
//    }

//    QVariantList modeled = map.value("mModel").toList();
//    for(const QVariant& data : modeled) {
//        ModelData mod;
//        mod.fromVariant(data);
//        mModel.append(mod);
//    }
//}

QString InversionModel::name() const
{
    return mName;
}

QString InversionModel::id() const
{
    return mId;
}

double InversionModel::errorResult() const
{
    return mErrorResult;
}

QString InversionModel::errorString()
{
    QLocale qLoc;
    mErrorString = "RMS = " + qLoc.toString(mErrorResult, 'g', 3);
    return mErrorString;
}

InversionModel::InversionAlgorithm InversionModel::usedAlgorithm() const
{
    return mUsedAlgorithm;
}

QList<BasicData> InversionModel::calculatedData() const
{
    return mCalculatedData;
}

QList<ModelData> InversionModel::model() const
{
    return mModel;
}

void InversionModel::setName(const QString value)
{
    mName = value;
}

void InversionModel::setUsedAlgorithm(const InversionModel::InversionAlgorithm value)
{
    mUsedAlgorithm = value;
}

void InversionModel::setCalculatedData(const QList<BasicData> &list)
{
    foreach (const BasicData &bd, list) {
        BasicData newBd(bd.ab2Distance(), bd.resistivity(), bd.standardDeviation(), this);
        mCalculatedData.append(newBd);
    }
}

void InversionModel::setModelData(const QList<ModelData> &list)
{
    foreach (const ModelData &md, list) {
        ModelData newMd(md);
        mModel.append(newMd);
    }
}

void InversionModel::inversion(const QList<SpliceData> &fieldData)
{

}

void InversionModel::updateModelError(const QList<SpliceData> &list)
{
    mErrorResult = calculateModelError(list, mCalculatedData);
}

InversionModel &InversionModel::operator =(const InversionModel &rhs)
{
    mId = QUuid::createUuid().toString();

    mName = rhs.name();
    mErrorResult = rhs.errorResult();
    //mErrorString = rhs.errorString();
    mUsedAlgorithm = rhs.usedAlgorithm();
    mCalculatedData = rhs.calculatedData();
    mModel = rhs.model();
    this->setParent(rhs.parent());
    return *this;
}

void InversionModel::updateModeledData(const int row, const int column, const double value)
{
    if (column == 0){
        mModel[row].setDepth(value);
    } else if (column == 1) {
        mModel[row].setResistivity(value);
    } else {
        return;
    }


}
