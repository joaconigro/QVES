#include "VFSAParameters.h"

VFSAParameters::VFSAParameters(QObject *parent) : QObject(parent)
{
    //Default parameters
    mInitialTemperature = 0.01;
    mIterationsPerTemperature = 1000;
    mMovesPerTemperature = 20;
    mSolutions = 10;
    mNumberOfParameters = 5;
    mNumberOfBeds = 3;
    mMaximunError = 0.001;
    mMinimunPdf = 0.6825;
    mLimits.clear();
}

VFSAParameters::VFSAParameters(const VFSAParameters &vp)
{
    mInitialTemperature = vp.initialTemperature();
    mIterationsPerTemperature = vp.iterationsPerTemperature();
    mMovesPerTemperature = vp.movesPerTemperature();
    mSolutions = vp.solutions();
    mNumberOfParameters = vp.numberOfParameters();
    mNumberOfBeds = vp.numberOfBeds();
    mMaximunError = vp.maximunError();
    mMinimunPdf = vp.minimunPdf();
    mLimits.append(vp.limits());
    this->setParent(vp.parent());
}

VFSAParameters &VFSAParameters::operator =(const VFSAParameters &rhs)
{
    mInitialTemperature = rhs.initialTemperature();
    mIterationsPerTemperature = rhs.iterationsPerTemperature();
    mMovesPerTemperature = rhs.movesPerTemperature();
    mSolutions = rhs.solutions();
    mNumberOfParameters = rhs.numberOfParameters();
    mNumberOfBeds = rhs.numberOfBeds();
    mMaximunError = rhs.maximunError();
    mMinimunPdf = rhs.minimunPdf();
    mLimits.append(rhs.limits());
    this->setParent(rhs.parent());
    return *this;
}

QVariant VFSAParameters::toVariant() const
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

void VFSAParameters::fromVariant(const QVariant &variant)
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
        VFSAParameterLimit calc;
        calc.fromVariant(data);
        mLimits.append(calc);
    }

}

double VFSAParameters::initialTemperature() const
{
    return mInitialTemperature;
}

int VFSAParameters::iterationsPerTemperature() const
{
    return mIterationsPerTemperature;
}

int VFSAParameters::movesPerTemperature() const
{
    return mMovesPerTemperature;
}

int VFSAParameters::solutions() const
{
    return mSolutions;
}

int VFSAParameters::numberOfParameters() const
{
    return mNumberOfParameters;
}

int VFSAParameters::numberOfBeds() const
{
    return mNumberOfBeds;
}

QList<VFSAParameterLimit> VFSAParameters::limits() const
{
    return mLimits;
}

double VFSAParameters::maximunError() const
{
    return mMaximunError;
}

double VFSAParameters::minimunPdf() const
{
    return mMinimunPdf;
}

void VFSAParameters::setInitialTemperature(const double &value)
{
    mInitialTemperature = value;
}

void VFSAParameters::setIterationsPerTemperature(const int &value)
{
    mIterationsPerTemperature = value;
}

void VFSAParameters::setMovesPerTemperature(const int &value)
{
    mMovesPerTemperature = value;
}

void VFSAParameters::setSolutions(const int &value)
{
    mSolutions = value;
}

void VFSAParameters::setNumberOfParameters(const int &value)
{
    mNumberOfParameters = value;
}

void VFSAParameters::setNumberOfBeds(const int &value)
{
    mNumberOfBeds = value;
}

void VFSAParameters::setLimits(const QList<VFSAParameterLimit> &value)
{
    mLimits = value;
}

void VFSAParameters::setMaximunError(const double &value)
{
    mMaximunError = value;
}

void VFSAParameters::setMinimunPdf(const double &value)
{
    mMinimunPdf = value;
}

bool VFSAParameters::isValid() const
{
    bool result = mSolutions > 0 && mInitialTemperature > 0.0 && mIterationsPerTemperature > 0 && mMovesPerTemperature > 0
            && mMaximunError > 0.0 && mMinimunPdf > 0.0 && mNumberOfBeds > 0 && mNumberOfParameters > 0 && mLimits.count() > 0;

    bool limitsResult = true;
    foreach (auto limit, mLimits) {
        if (!limit.isValid())
            limitsResult = false;
    }

    return result && limitsResult;
}
