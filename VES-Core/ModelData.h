#ifndef MODELDATA_H
#define MODELDATA_H

#include "ves-core_global.h"
#include <QObject>

class VESCORESHARED_EXPORT ModelData : public QObject
{
    Q_OBJECT

    double mFrom;
    double mUntil;
    double mResistivity;
    double mThickness;
    double mDepth;
    double mTransverseResistence;
    double mLongitudinalConductance;

public:
    explicit ModelData(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MODELDATA_H
