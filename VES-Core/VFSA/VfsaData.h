#ifndef VFSADATA_H
#define VFSADATA_H

#include "ves-core_global.h"
#include <QObject>

class VESCORESHARED_EXPORT VfsaData : public QObject
{
    Q_OBJECT

    double mValue;
    double mPdf;

public:
    explicit VfsaData(QObject *parent = nullptr);
    explicit VfsaData(const double value, const double pdf = 0.0, QObject *parent = nullptr);
    VfsaData(const VfsaData &vd);

    //Getters
    double value() const;
    double pdf() const;

    //Setters
    void setValue(const double value);
    void setPdf(const double value);

signals:

public slots:
};

#endif // VFSADATA_H
