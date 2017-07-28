#include "ModelDataTable.h"

ModelDataTable::ModelDataTable(QObject *parent) : QObject(parent)
{

}

ModelDataTable::ModelDataTable(const double &x, const double &y, QObject *parent) :
    QObject(parent),
    mX(x), mY(y)
{

}

double ModelDataTable::x() const
{
    return mX;
}

double ModelDataTable::y() const
{
    return mY;
}

void ModelDataTable::setX(double x)
{
    mX = x;
}

void ModelDataTable::setY(double y)
{
    mY = y;
}

