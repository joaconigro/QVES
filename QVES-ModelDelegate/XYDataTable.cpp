#include "XYDataTable.h"

XYDataTable::XYDataTable(QObject *parent) : QObject(parent)
{

}

XYDataTable::XYDataTable(const double &x, const double &y, QObject *parent) :
    QObject(parent),
    mX(x), mY(y)
{

}

double XYDataTable::x() const
{
    return mX;
}

double XYDataTable::y() const
{
    return mY;
}

void XYDataTable::setX(double x)
{
    mX = x;
}

void XYDataTable::setY(double y)
{
    mY = y;
}

