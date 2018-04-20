#ifndef XYDATATABLE_H
#define XYDATATABLE_H
#include "qves-modeldelegate_global.h"
#include <QObject>
#include <QList>

class QVESMODELDELEGATESHARED_EXPORT XYData : public QObject
{
    Q_OBJECT

    double mX;
    double mY;

public:
    explicit XYData(QObject *parent = nullptr);
    explicit XYData(const double &x, const double &y, QObject *parent = nullptr);
    explicit XYData(const XYData *xy);
    double x() const;
    double y() const;

    void setX(double x);
    void setY(double y);

    bool operator ==(const XYData &rhs) const;
    bool operator !=(const XYData &rhs) const;
    XYData& operator =(const XYData &rhs);
signals:


public slots:

};

#endif // XYDATATABLE_H
