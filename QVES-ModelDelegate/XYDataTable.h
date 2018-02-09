#ifndef XYDATATABLE_H
#define XYDATATABLE_H
#include "qves-modeldelegate_global.h"
#include <QObject>
#include <QList>

class QVESMODELDELEGATESHARED_EXPORT XYDataTable : public QObject
{
    Q_OBJECT

    double mX;
    double mY;

public:
    explicit XYDataTable(QObject *parent = nullptr);
    explicit XYDataTable(const double &x, const double &y, QObject *parent = nullptr);
    double x() const;
    double y() const;

    void setX(double x);
    void setY(double y);

signals:


public slots:

};

#endif // XYDATATABLE_H
