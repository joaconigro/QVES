#include "ZohdyModel.h"
#include <QUuid>
#include <QtMath>

//ZohdyModel::ZohdyModel()
//{

//}

ZohdyModel::ZohdyModel(QObject *parent) : InversionModel(parent)
{
    mUsedAlgorithm = InversionAlgorithm::Zohdy;
    mZohdyFilter = InversionModel::ZohdyFilters::Johansen;
}

ZohdyModel::ZohdyModel(const QString &name, QObject *parent) : InversionModel(name, parent)
{
    mUsedAlgorithm = InversionAlgorithm::Zohdy;
    mZohdyFilter = InversionModel::ZohdyFilters::Johansen;
}

ZohdyModel::ZohdyModel(const QString &name, const InversionModel::ZohdyFilters filter, QObject *parent, const bool applyDarZarrouk, const double darZarroukThreshold) :
    InversionModel(name, parent),
    mZohdyFilter(filter)
{
    mUsedAlgorithm = InversionAlgorithm::Zohdy;
}

ZohdyModel::ZohdyModel(const InversionModel &im) : InversionModel(im)
{
    mZohdyFilter = InversionModel::ZohdyFilters::Johansen;
}

ZohdyModel::ZohdyModel(const ZohdyModel &zm)
{
    mId = QUuid::createUuid().toString();

    mName = zm.name();
    mErrorResult = zm.errorResult();
    mUsedAlgorithm = zm.usedAlgorithm();
    mZohdyFilter = zm.zohdyFilter();
    mCalculatedData = zm.calculatedData();
    mModel = zm.model();
    this->setParent(zm.parent());
}

QVariant ZohdyModel::toVariant() const
{
    QVariantMap map;// = InversionModel::toVariant().toMap();
    //map = InversionModel::toVariant();
    map.insert("mName", mName);
    map.insert("mId", mId);
    map.insert("mErrorResult", mErrorResult);
    map.insert("mErrorString", mErrorString);
    map.insert("mUsedAlgorithm", static_cast<int>(mUsedAlgorithm));
    map.insert("mZohdyFilter", static_cast<int>(mZohdyFilter));

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


void ZohdyModel::fromVariant(const QVariant &variant)
{
    //    InversionModel::fromVariant(variant);
    QVariantMap map = variant.toMap();
    mName = map.value("mName").toString();
    mId = map.value("mId").toString();
    mErrorResult = map.value("mErrorResult").toDouble();
    mErrorString = map.value("mErrorString").toString();
    mUsedAlgorithm = static_cast<InversionModel::InversionAlgorithm>(map.value("mUsedAlgorithm").toInt());
    mZohdyFilter = static_cast<InversionModel::ZohdyFilters>(map.value("mZohdyFilter").toInt());

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




void ZohdyModel::inversion(const QList<SpliceData> &fieldData)
{
    zohdyInversion(fieldData, mZohdyFilter);
}

InversionModel::ZohdyFilters ZohdyModel::zohdyFilter() const
{
    return mZohdyFilter;
}

void ZohdyModel::setZohdyFilter(const InversionModel::ZohdyFilters value)
{
    mZohdyFilter = value;
}

void ZohdyModel::chooseFilter(const InversionModel::ZohdyFilters filter, QVector<double> &a, double &w, double &s, double &dx)
{
    switch (filter) {
    case InversionModel::ZohdyFilters::Johansen:
        w = 40.0;
        s = -1.7239458;
        dx = qLn(10) / 10.0;
        a = {0.00006174, -0.00012484, 0.00012726, -0.00012975, 0.00013231, -0.00013494, 0.00013765, -0.00014043, 0.0001433, -0.00014625,
             0.0001493, -0.00015244, 0.00015567, -0.00015901, 0.00016246, -0.00016602, 0.00016971, -0.00017352, 0.00017746, -0.00018154,
             0.00018577, -0.00019015, 0.00019469, -0.00019941, 0.00020429, -0.00020936, 0.00021463, -0.00022009, 0.00022577, -0.00023166,
             0.00023779, -0.00024416, 0.00025079, -0.00025768, 0.00026487, -0.00027235, 0.00028016, -0.0002883, 0.0002968, -0.00030568,
             0.00031496, -0.00032467, 0.00033484, -0.00034549, 0.00035666, -0.00036838, 0.00038069, -0.00039363, 0.00040724, -0.00042156,
             0.00043666, -0.00045259, 0.0004694, -0.00048717, 0.00050596, -0.00052587, 0.00054697, -0.00056936, 0.00059314, -0.00061845,
             0.0006454, -0.00067414, 0.00070484, -0.00073767, 0.00077284, -0.00081057, 0.00085111, -0.00089475, 0.00094183, -0.00099267,
             0.00104775, -0.00110741, 0.00117248, -0.00124303, 0.00132085, -0.00140461, 0.00149959, -0.00159826, 0.00171917, -0.00182946,
             0.00199955, -0.00209469, 0.00239052, -0.00234543, 0.00304916, -0.00234124, 0.0045399, -0.00106745, 0.00899282, 0.00550573,
             0.02442523, 0.03250077, 0.07926675, 0.13023345, 0.25610307, 0.41150741, 0.64231809, 0.72803988, 0.36118538, -1.00406442,
             -2.42172543, 0.2005246, 4.44506381, -4.89348908, 2.94899398, -1.37791072, 0.61285163, -0.29362551, 0.15817356, -0.09504597,
             0.06226174, -0.04353505, 0.03198475, -0.02441493, 0.0192084, -0.01548505, 0.01273595, -0.01065148, 0.00903512, -0.0077575,
             0.00673079, -0.00589375, 0.00520264, -0.00462558, 0.00413891, -0.00372478, 0.00336951, -0.00306251, 0.00279543, -0.00256168,
             0.00235594, -0.00217394, 0.00201216, -0.00186773, 0.00173826, -0.00162176, 0.00151657, -0.00142126, 0.00133463, -0.00125568,
             0.00060905};

        break;
    case InversionModel::ZohdyFilters::ONeill:
        w = 14.0;
        s = -0.13069;
        dx = qLn(10) / 6.0;
        a = {0.003042, -0.001198, 0.001284, 0.0235, 0.08688, 0.2374, 0.6194, 1.1817, 0.4248, -3.4507,
             2.7044, -1.1324, 0.393, -0.1436, 0.05812, -0.02521, 0.01125, -0.004978, 0.002072, -0.000318};

        break;

    }
}

void ZohdyModel::TRS(const QList<SpliceData> &field, QList<BasicData> &calculated, QList<ModelData> &model, const QVector<double> a, const double w, const double s, const double dx)
{
    //Necessary variables.
    QVector<double> x(a.size());
    QVector<double> T(a.size());

    double sum, aux1, aux2, aux3, L, M;
    int n, nm1;

    aux1 = aux2 = aux3 = L = M = 0.0;
    n = model.count();
    nm1 = n - 1;
    calculated.clear();

    for(int k = 0; k<field.count(); k++){

        //Calculation of the location of points centered on the abscissa.
        for(int j = 0; j<x.count(); j++){
            x[j] = qExp(qLn(field.at(k).ab2Distance()) + s + (j - w) * dx);
        }

        //Calculation of the apparent resistivity transform in the vector x.
        //Calculate the resistivity transforms with the Sunde algorithm.
        for(int j = 0; j<x.count(); j++){
            if(n - 2 < 0){
                return;
            }

            L = (model.at(n - 1).resistivity() - model.at(n - 2).resistivity()) / (model.at(n - 1).resistivity() + model.at(n - 2).resistivity());
            aux1 = L * qExp((-2.0 / x[j]) * model.at(n - 2).thickness());
            M = (1.0 + aux1) / (1.0 - aux1);
            if (nm1 >= 2){
                for (int i = 2; i <= nm1; i++){
                    aux2 = model.at(n - i).resistivity() * M;
                    L = (aux2 - model.at(n - i - 1).resistivity()) / (aux2 + model.at(n - i - 1).resistivity());
                    aux3 = L * qExp((-2.0 / x[j]) * model.at(n - i - 1).thickness());
                    M = (1.0 + aux3) / (1.0 - aux3);
                }
            }
            T[j] = model.at(0).resistivity() * M;
        }

        //Calculation of the convolution between the filter and the resistivity transform,
        //which gives the apparent resistivity curve.
        sum = 0.0;
        for(int j = 0; j<x.count(); j++){
            sum = a[(x.count() - 1) - j] * T[j] + sum;
        }

        //Finally, save resistivity on calculated list.
        BasicData bd;
        bd.setAb2Distance(field.at(k).ab2Distance());
        bd.setResistivity(sum);
        calculated.append(bd);
    }

}

void ZohdyModel::zohdyInversion(const QList<SpliceData> &fieldData, const InversionModel::ZohdyFilters filter)
{
    double w, s, dx;
    const double minErrorTolerance = 0.2;
    QVector<double> a;
    chooseFilter(filter, a, w, s, dx);

    //Make lists of ModelData and BasicData.
    QList<ModelData> tempModel;
    tempModel.clear();
    QList<BasicData> tempCalculated;
    tempCalculated.clear();


    //Take fieldData as true resistivity and depth.
    foreach (const BasicData &bd, fieldData) {
        ModelData md;
        md.setDepth(bd.ab2Distance());
        md.setResistivity(bd.resistivity());
        tempModel.append(md);
    }


    //Calculate thicknesses for proposed model.
    calculateThicknesses(tempModel);

    //Make aux lists of ModelData and BasicData.
    QList<ModelData> tempModel2;
    tempModel2.clear();
    QList<BasicData> tempCalculated2;
    tempCalculated2.clear();

    //Copy original model list to aux.
    tempModel2.append(tempModel);


    //Carry out inversion of proposed model and calculate his error.
    //Then copy calculated data to aux list.
    TRS(fieldData, tempCalculated, tempModel, a, w, s, dx);
    tempCalculated2.append(tempCalculated);
    double error1 = calculateModelError(fieldData, tempCalculated);
    double error2;

    //Inversion loop, reducing thicknesses.
    bool getOut = false;
    while (!getOut) {

        //Reduction of thicknesses.
        for(int i = 0; i<tempModel.count(); i++){
            tempModel[i].setThickness(tempModel.at(i).thickness() * 0.9);
        }

        //Calculate new depths.
        calculateDepths(tempModel);

        //Carry out inversion of proposed model and calculate his error.
        TRS(fieldData, tempCalculated, tempModel, a, w, s, dx);
        error2 = calculateModelError(fieldData, tempCalculated);

        //If new error is lower than previous one, continue with the loop.
        //Else, save the model and exit from loop.
        if (error2 < error1){
            error1 = error2;
            tempCalculated2.clear();
            tempCalculated2.append(tempCalculated);
            tempModel2.clear();
            tempModel2.append(tempModel);
        }else{
            tempCalculated.clear();
            tempCalculated.append(tempCalculated2);
            tempModel.clear();
            tempModel.append(tempModel2);
            getOut = true;

        }
    }

    //Make a new loop changing resistivities.
    getOut = false;
    while (!getOut) {

        //Calculate new resistivities.
        for(int i = 0; i<tempModel.count(); i++){
            tempModel[i].setResistivity(tempModel.at(i).resistivity() * fieldData.at(i).resistivity() / tempCalculated.at(i).resistivity());
        }

        //Carry out inversion of proposed model and calculate his error.
        TRS(fieldData, tempCalculated, tempModel, a, w, s, dx);
        error2 = calculateModelError(fieldData, tempCalculated);

        //If new error is lower than previous one, continue with the loop.
        //Else, save the model and exit from loop.
        if ((error2 < error1) && (error2 > minErrorTolerance)){
            error1 = error2;
            tempCalculated2.clear();
            tempCalculated2.append(tempCalculated);
            tempModel2.clear();
            tempModel2.append(tempModel);
        }else{
            tempCalculated.clear();
            tempCalculated.append(tempCalculated2);
            tempModel.clear();
            tempModel.append(tempModel2);
            getOut = true;
        }
    }

    //Correct last bed.
    tempModel[tempModel.count() - 1].setDepth(qInf());
    tempModel[tempModel.count() - 1].setThickness(qInf());
    tempModel[tempModel.count() - 1].setUntil(qInf());

    //Finally, when error is minumun, save the model and calculated data.
    mModel.clear();
    mModel.append(tempModel);
    mCalculatedData.clear();
    mCalculatedData.append(tempCalculated);
    mErrorResult = error1;
    mZohdyFilter = filter;
}
