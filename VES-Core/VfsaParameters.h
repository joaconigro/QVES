#ifndef VFSAPARAMETERS_H
#define VFSAPARAMETERS_H

#include "ves-core_global.h"
#include <QObject>
#include "VfsaParameterLimit.h"
#include <QList>

class VESCORESHARED_EXPORT VfsaParameters : public QObject
{
    Q_OBJECT

    double mInitialTemperature;
    int mIterationsPerTemperature;
    int mMovesPerTemperature;
    int mSolutions;
    int mNumberOfParameters;
    int mNumberOfBeds;
    QList<VfsaParameterLimit> mLimits;
    double mMaximunError;
    double mMinimunPDF;

public:
    explicit VfsaParameters(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VFSAPARAMETERS_H
