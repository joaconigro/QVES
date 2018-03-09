#include "VfsaParameters.h"

VfsaParameters::VfsaParameters(QObject *parent) : QObject(parent)
{
    //Parámetros por defecto
    mInitialTemperature = 0.01;
    mIterationsPerTemperature = 1000;
    mMovesPerTemperature = 20;
    mSolutions = 10;
    mNumberOfParameters = 5;
    mNumberOfBeds = 3;
    mMaximunError = 0.0001;
    mMinimunPdf = 0.6825;
    mLimits.clear();
}

VfsaParameters::VfsaParameters(const VfsaParameters &vp)
{
    mInitialTemperature = vp.initialTemperature();
    mIterationsPerTemperature = vp.iterationsPerTemperature();
    mMovesPerTemperature = vp.movesPerTemperature();
    mSolutions = vp.solutions();
    mNumberOfParameters = vp.numberOfParameters();
    mNumberOfBeds = vp.numberOfBeds();
    mMaximunError = vp.maximunError();
    mMaximunError = vp.minimunPdf();
    mLimits = vp.limits();
}

VfsaParameters &VfsaParameters::operator =(const VfsaParameters &rhs)
{
    mInitialTemperature = rhs.initialTemperature();
    mIterationsPerTemperature = rhs.iterationsPerTemperature();
    mMovesPerTemperature = rhs.movesPerTemperature();
    mSolutions = rhs.solutions();
    mNumberOfParameters = rhs.numberOfParameters();
    mNumberOfBeds = rhs.numberOfBeds();
    mMaximunError = rhs.maximunError();
    mMinimunPdf = rhs.minimunPdf();
    mLimits = rhs.limits();
    this->setParent(rhs.parent());
    return *this;
}

QVariant VfsaParameters::toVariant() const
{
    QVariantMap map;
    map.insert("mInitialTemperature", mInitialTemperature);
    map.insert("mIterationsPerTemperature", mIterationsPerTemperature);
    map.insert("mMovesPerTemperature", mMovesPerTemperature);
    map.insert("mSolutions", mSolutions);
    map.insert("mNumberOfParameters", mNumberOfParameters);
    map.insert("mNumberOfBeds", mNumberOfBeds);
    map.insert("mMaximunError", mMaximunError);
    map.insert("mMinimunPdf", mMinimunPdf);

    QVariantList list;
    for (const auto& cd : mLimits) {
    list.append(cd.toVariant());
    }
    map.insert("mLimits", list);

    return map;
}

void VfsaParameters::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mInitialTemperature = map.value("mInitialTemperature").toDouble();
    mIterationsPerTemperature = map.value("mIterationsPerTemperature").toInt();
    mMovesPerTemperature = map.value("mMovesPerTemperature").toInt();
    mSolutions = map.value("mSolutions").toInt();
    mNumberOfParameters = map.value("mNumberOfParameters").toInt();
    mNumberOfBeds = map.value("mNumberOfBeds").toInt();
    mMaximunError = map.value("mMaximunError").toDouble();
    mMinimunPdf = map.value("mMinimunPdf").toDouble();

    QVariantList list = map.value("mLimits").toList();
    for(const QVariant& data : list) {
        VfsaParameterLimit calc;
        calc.fromVariant(data);
        mLimits.append(calc);
    }

}

double VfsaParameters::initialTemperature() const
{
    return mInitialTemperature;
}

int VfsaParameters::iterationsPerTemperature() const
{
    return mIterationsPerTemperature;
}

int VfsaParameters::movesPerTemperature() const
{
    return mMovesPerTemperature;
}

int VfsaParameters::solutions() const
{
    return mSolutions;
}

int VfsaParameters::numberOfParameters() const
{
    return mNumberOfParameters;
}

int VfsaParameters::numberOfBeds() const
{
    return mNumberOfBeds;
}

QList<VfsaParameterLimit> VfsaParameters::limits() const
{
    return mLimits;
}

double VfsaParameters::maximunError() const
{
    return mMaximunError;
}

double VfsaParameters::minimunPdf() const
{
    return mMinimunPdf;
}

void VfsaParameters::setInitialTemperature(const double &value)
{
    mInitialTemperature = value;
}

void VfsaParameters::setIterationsPerTemperature(const int &value)
{
    mIterationsPerTemperature = value;
}

void VfsaParameters::setMovesPerTemperature(const int &value)
{
    mMovesPerTemperature = value;
}

void VfsaParameters::setSolutions(const int &value)
{
    mSolutions = value;
}

void VfsaParameters::setNumberOfParameters(const int &value)
{
    mNumberOfParameters = value;
}

void VfsaParameters::setNumberOfBeds(const int &value)
{
    mNumberOfBeds = value;
}

void VfsaParameters::setLimits(const QList<VfsaParameterLimit> &value)
{
    mLimits = value;
}

void VfsaParameters::setMaximunError(const double &value)
{
    mMaximunError = value;
}

void VfsaParameters::setMinimunPdf(const double &value)
{
    mMinimunPdf = value;
}
