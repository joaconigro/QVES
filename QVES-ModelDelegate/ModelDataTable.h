#ifndef MODELDATATABLE_H
#define MODELDATATABLE_H
#include "qves-modeldelegate_global.h"
#include <QObject>
#include <QList>

class QVESMODELDELEGATESHARED_EXPORT ModelDataTable : public QObject
{
    Q_OBJECT

    double mX;
    double mY;

public:
    explicit ModelDataTable(QObject *parent = nullptr);
    explicit ModelDataTable(const double &x, const double &y, QObject *parent = nullptr);
    double x() const;
    double y() const;

    void setX(double x);
    void setY(double y);

signals:


public slots:

};

#endif // MODELDATATABLE_H
