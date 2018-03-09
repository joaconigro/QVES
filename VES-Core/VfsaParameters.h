#ifndef VFSAPARAMETERS_H
#define VFSAPARAMETERS_H

#include "ves-core_global.h"
#include <QObject>
#include "VfsaParameterLimit.h"
#include <QList>
#include "Serializable.h"

class VESCORESHARED_EXPORT VfsaParameters : public QObject, public Serializable
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
    double mMinimunPdf;

public:
    explicit VfsaParameters(QObject *parent = nullptr);
    VfsaParameters(const VfsaParameters &vp);
    VfsaParameters& operator =(const VfsaParameters &rhs);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    //Getters
    double initialTemperature() const;
    int iterationsPerTemperature() const;
    int movesPerTemperature() const;
    int solutions() const;
    int numberOfParameters() const;
    int numberOfBeds() const;
    QList<VfsaParameterLimit> limits() const;
    double maximunError() const;
    double minimunPdf() const;

    //Setters
    void setInitialTemperature(const double &value);
    void setIterationsPerTemperature(const int &value);
    void setMovesPerTemperature(const int &value);
    void setSolutions(const int &value);
    void setNumberOfParameters(const int &value);
    void setNumberOfBeds(const int &value);
    void setLimits(const QList<VfsaParameterLimit> &value);
    void setMaximunError(const double &value);
    void setMinimunPdf(const double &value);

signals:

public slots:
};
Q_DECLARE_METATYPE(VfsaParameters)

#endif // VFSAPARAMETERS_H
