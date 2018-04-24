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
    mUsedAlgorithm = im.usedAlgorithm();
    mCalculatedData.append(im.calculatedData());
    mModel.append(im.model());
    this->setParent(im.parent());
}

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

void InversionModel::appendCalculatedData(const BasicData &data)
{
    mCalculatedData.append(data);
}

void InversionModel::setModelData(const QList<ModelData> &list)
{
    foreach (const ModelData &md, list) {
        ModelData newMd(md);
        mModel.append(newMd);
    }
}

void InversionModel::updateModelError(const QList<SpliceData> &list)
{
    mErrorResult = calculateModelError(list, mCalculatedData);
}

void InversionModel::darZarrouk(const QList<int> bedIndices)
{
    int insertPoint = *std::min_element(bedIndices.begin(), bedIndices.end());

    //Calculate Transverse Resistence and Longitudinal Conductance for selected beds.
    foreach (const auto &i, bedIndices) {
        if(mModel.at(i).depth() == qInf()){
            mModel[i].setTransverseResistence(std::numeric_limits<int>::max() * mModel.at(i).resistivity());
            mModel[i].setLongitudinalConductance(std::numeric_limits<int>::max() / mModel.at(i).resistivity());
        } else {
            mModel[i].setTransverseResistence(mModel.at(i).thickness() * mModel.at(i).resistivity());
            mModel[i].setLongitudinalConductance(mModel.at(i).thickness() / mModel.at(i).resistivity());
        }
    }

    double sumTR, sumLC;
    sumLC = sumTR = 0.0;
    foreach (const auto &i, bedIndices) {
          sumTR += mModel.at(i).transverseResistence();
          sumLC += mModel.at(i).longitudinalConductance();
    }

    //Calculate parametres for a new bed.
    double newResistivity, newThickness;
    newResistivity = qSqrt(sumTR / sumLC);
    newThickness = qSqrt(sumTR * sumLC);
    ModelData newData;
    newData.setResistivity(newResistivity);
    newData.setThickness(newThickness);

    //Delete old beds and insert the new one.
    for(auto it = bedIndices.rbegin(); it != bedIndices.rend(); it++){
        mModel.removeAt(*it);
    }
    mModel.insert(insertPoint, newData);

    //Calculate new depths.
    calculateDepths(mModel);



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
