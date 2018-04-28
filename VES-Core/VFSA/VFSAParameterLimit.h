#ifndef VFSAPARAMETERLIMIT_H
#define VFSAPARAMETERLIMIT_H

#include "ves-core_global.h"
#include <QObject>
#include "Serializable.h"

class VESCORESHARED_EXPORT VFSAParameterLimit : public QObject, public Serializable
{
    Q_OBJECT

    double mLower;
    double mUpper;

public:
    explicit VFSAParameterLimit(QObject *parent = nullptr);
    explicit VFSAParameterLimit(const double low, const double upp, QObject *parent = nullptr);
    VFSAParameterLimit(const VFSAParameterLimit &vpf);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    //Getters
    double lower() const;
    double upper() const;

    //Setters
    void setLower(const double value);
    void setUpper(const double value);

    VFSAParameterLimit& operator =(const VFSAParameterLimit &rhs);
    bool operator ==(const VFSAParameterLimit &rhs) const;
    bool operator !=(const VFSAParameterLimit &rhs) const;

    bool isValid() const;

signals:

public slots:
};
Q_DECLARE_METATYPE(VFSAParameterLimit)
#endif // VFSAPARAMETERLIMIT_H
