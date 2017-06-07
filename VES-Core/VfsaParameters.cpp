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
    mMinimunPDF = 0.6825;
    mLimits.clear();
}
