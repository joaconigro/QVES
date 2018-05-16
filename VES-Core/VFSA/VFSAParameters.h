#ifndef VFSAPARAMETERS_H
#define VFSAPARAMETERS_H

#include "ves-core_global.h"
#include <QObject>
#include "VFSAParameterLimit.h"
#include <QList>
#include "Serializable.h"

class VESCORESHARED_EXPORT VFSAParameters : public QObject, public Serializable
{
    Q_OBJECT

    double mInitialTemperature;
    int mIterationsPerTemperature;
    int mMovesPerTemperature;
    int mSolutions;
    int mNumberOfParameters;
    int mNumberOfBeds;
    QList<VFSAParameterLimit> mLimits;
    double mMaximunError;

public:
    explicit VFSAParameters(QObject *parent = nullptr);
    VFSAParameters(const VFSAParameters &vp);
    VFSAParameters& operator =(const VFSAParameters &rhs);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    //Getters
    double initialTemperature() const;
    int iterationsPerTemperature() const;
    int movesPerTemperature() const;
    int solutions() const;
    int numberOfParameters() const;
    int numberOfBeds() const;
    QList<VFSAParameterLimit> limits() const;
    double maximunError() const;

    //Setters
    void setInitialTemperature(const double &value);
    void setIterationsPerTemperature(const int &value);
    void setMovesPerTemperature(const int &value);
    void setSolutions(const int &value);
    void setNumberOfParameters(const int &value);
    void setNumberOfBeds(const int &value);
    void setLimits(const QList<VFSAParameterLimit> &value);
    void setMaximunError(const double &value);

    bool isValid() const;
    VFSAParameterLimit limitAt(const int index) const;

    //void copyWithoutLimits(const VFSAParameters &rhs);
signals:

public slots:
};
Q_DECLARE_METATYPE(VFSAParameters)

#endif // VFSAPARAMETERS_H
