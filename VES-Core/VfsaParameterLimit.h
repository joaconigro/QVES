#ifndef VFSAPARAMETERLIMIT_H
#define VFSAPARAMETERLIMIT_H

#include "ves-core_global.h"
#include <QObject>
#include "Serializable.h"

class VESCORESHARED_EXPORT VfsaParameterLimit : public QObject, public Serializable
{
    Q_OBJECT

    double mLower;
    double mUpper;

public:
    explicit VfsaParameterLimit(QObject *parent = nullptr);
    explicit VfsaParameterLimit(const double low, const double upp, QObject *parent = nullptr);
    VfsaParameterLimit(const VfsaParameterLimit &vpf);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    //Getters
    double lower() const;
    double upper() const;

    //Setters
    void setLower(const double value);
    void setUpper(const double value);

    VfsaParameterLimit& operator =(const VfsaParameterLimit &rhs);

signals:

public slots:
};
Q_DECLARE_METATYPE(VfsaParameterLimit)
#endif // VFSAPARAMETERLIMIT_H
