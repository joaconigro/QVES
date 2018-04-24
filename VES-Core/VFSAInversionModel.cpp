#include "VFSAInversionModel.h"
#include <QUuid>
#include <QtMath>

//VFSAInversionModel::VFSAInversionModel()
//{

//}

QList<VfsaData> VFSAInversionModel::getVFSAParameters() const
{
    return mVFSAParameters;
}

double VFSAInversionModel::getVFSAError() const
{
    return mVFSAError;
}

void VFSAInversionModel::setVFSAError(double vFSAError)
{
    mVFSAError = vFSAError;
}

void VFSAInversionModel::addVFSAData(const VfsaData &data)
{
    mVFSAParameters.append(data);
}

void VFSAInversionModel::addVFSAData(const double &data)
{
    VfsaData newData(data, 0.0, this);
    mVFSAParameters.append(newData);
}

VFSAInversionModel::VFSAInversionModel(QObject *parent): InversionModel(parent)
{
    mUsedAlgorithm = InversionAlgorithm::Vfsa;
}

VFSAInversionModel::VFSAInversionModel(const QString &name, QObject *parent) : InversionModel(name, parent)
{
    mUsedAlgorithm = InversionAlgorithm::Vfsa;
}

VFSAInversionModel::VFSAInversionModel(const InversionModel &im): InversionModel(im)
{
    mUsedAlgorithm = InversionAlgorithm::Vfsa;
}

VFSAInversionModel::VFSAInversionModel(const VFSAInversionModel &vm)
{
    mId = QUuid::createUuid().toString();

    mName = vm.name();
    mErrorResult = vm.errorResult();
    mUsedAlgorithm = vm.usedAlgorithm();
    mCalculatedData.append(vm.calculatedData());
    mModel.append(vm.model());
    mVFSAError = vm.getVFSAError();
    mVFSAParameters.append(vm.getVFSAParameters());
    this->setParent(vm.parent());
}

QVariant VFSAInversionModel::toVariant() const
{
    QVariantMap map;
    map.insert("mName", mName);
    map.insert("mId", mId);
    map.insert("mErrorResult", mErrorResult);
    map.insert("mErrorString", mErrorString);
    map.insert("mUsedAlgorithm", static_cast<int>(mUsedAlgorithm));

    QVariantList calculated;
    for (const auto& cd : mCalculatedData) {
        calculated.append(cd.toVariant());
    }
    map.insert("mCalculatedData", calculated);

    QVariantList modeled;
    for (const auto& md : mModel) {
        modeled.append(md.toVariant());
    }
    map.insert("mModel", modeled);

    return map;
}


void VFSAInversionModel::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mName = map.value("mName").toString();
    mId = map.value("mId").toString();
    mErrorResult = map.value("mErrorResult").toDouble();
    mErrorString = map.value("mErrorString").toString();
    mUsedAlgorithm = static_cast<InversionModel::InversionAlgorithm>(map.value("mUsedAlgorithm").toInt());

    QVariantList calculated = map.value("mCalculatedData").toList();
    for(const QVariant& data : calculated) {
        BasicData calc;
        calc.fromVariant(data);
        mCalculatedData.append(calc);
    }

    QVariantList modeled = map.value("mModel").toList();
    for(const QVariant& data : modeled) {
        ModelData mod;
        mod.fromVariant(data);
        mModel.append(mod);
    }
}

void VFSAInversionModel::inversion(const QList<SpliceData> &fieldData)
{

}

void VFSAInversionModel::updateInversionModelEdited(const QList<SpliceData> &fieldData)
{

}
