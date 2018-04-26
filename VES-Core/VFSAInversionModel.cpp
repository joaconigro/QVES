#include "VFSAInversionModel.h"
#include <QUuid>
#include <QtMath>

//VFSAInversionModel::VFSAInversionModel()
//{

//}

QList<double> VFSAInversionModel::getVFSAParameters() const
{
    QList<double> list;
    foreach (auto md, mModel) {
        list.append(md.resistivity());
    }
    for(int i = 0; i < mModel.count() -1; i++) {
        list.append(mModel.at(i).thickness());
    }

    return list;
}

double VFSAInversionModel::getVFSAError() const
{
    return mVFSAError;
}

void VFSAInversionModel::setVFSAError(double vFSAError)
{
    mVFSAError = vFSAError;
}

void VFSAInversionModel::addVFSAData(int index, const double data, const int numberOfBeds)
{
    if (index >= numberOfBeds)
        index -= numberOfBeds;

    if (index <= mModel.count()-1){
            mModel[index].setThickness(data);
    } else {
        ModelData md;
            md.setResistivity(data);
        mModel.insert(index, md);
    }
}

QList<double> VFSAInversionModel::getParameterPDFs() const
{
    return mParameterPDFs;
}

void VFSAInversionModel::setParameterPDF(const int index, const double value)
{
    mParameterPDFs.insert(index, value);
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
    calculateDepths(mModel);
    calculateThicknesses(mModel);

    int numberOfBeds = mModel.count();
    //Necessary variables.
    int m;
    double ep;
    int nn;
    QVector<double> t(numberOfBeds);
    QVector<double> tt(14);
    double xx;
    double appRes;

    //Schlumberger device (MM, MP, MN, DS, SHIFT, AJ)
    const QVector<double> AJ = {0.014, 0.0282, 0.0838, 0.2427, 0.6217, 1.1877, 0.3954, -3.4531, 2.7568, -1.2075, 0.4595, -0.1975, 0.1042, -0.0359};
    const int MM = 3;
    const int MP = 10;
    const int MN = 13;
    const double DS = qLn(10) / 6.0;
    const double SHIFT = 0.1343115;

    mCalculatedData.clear();
    foreach (auto item, fieldData) {
        BasicData pCalc;
        pCalc.setAb2Distance(item.ab2Distance());
        m = -MP;

        do{
            nn = numberOfBeds - 1;
            ep = item.ab2Distance() * exp(m * DS - SHIFT);
            t[nn] = mModel.at(nn).resistivity();

            do{
                xx = mModel.at(nn - 1).thickness() / ep;
                t[nn - 1] = (t[nn] + mModel.at(nn - 1).resistivity() * tanh(xx)) / (1 + t[nn] * tanh(xx) / mModel.at(nn - 1).resistivity());
                nn -= 1;
            } while (nn >= 1);

            tt[m + MP] = t.at(nn);
            m += 1;

        } while (m <= MM);

        appRes = 0.0;
        for(int j = 0; j<AJ.count(); j++){
            appRes += tt.at(MN - j) * AJ.at(j);
        }
        pCalc.setResistivity(appRes);
        mCalculatedData.append(pCalc);
    }
}

void VFSAInversionModel::updateInversionModelEdited(const QList<SpliceData> &fieldData)
{

}
