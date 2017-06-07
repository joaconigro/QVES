#ifndef VFSAPARAMETERLIMIT_H
#define VFSAPARAMETERLIMIT_H

#include "ves-core_global.h"
#include <QObject>

class VESCORESHARED_EXPORT VfsaParameterLimit : public QObject
{
    Q_OBJECT

    double mLower;
    double mUpper;

public:
    explicit VfsaParameterLimit(QObject *parent = nullptr);
    explicit VfsaParameterLimit(const double low, const double upp, QObject *parent = nullptr);

    //Getters
    double lower() const;
    double upper() const;

    //Setters
    void setLower(const double value);
    void setUpper(const double value);
signals:

public slots:
};

#endif // VFSAPARAMETERLIMIT_H
