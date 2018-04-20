#include "XYData.h"

XYData::XYData(QObject *parent) : QObject(parent)
{

}

XYData::XYData(const double &x, const double &y, QObject *parent) :
    QObject(parent),
    mX(x), mY(y)
{

}

XYData::XYData(const XYData *xy) : QObject(xy->parent())
{
    mX = xy->x();
    mY = xy->y();
}

double XYData::x() const
{
    return mX;
}

double XYData::y() const
{
    return mY;
}

void XYData::setX(double x)
{
    mX = x;
}

void XYData::setY(double y)
{
    mY = y;
}

bool XYData::operator ==(const XYData &rhs) const
{
    return (mX == rhs.x() && mY == rhs.y());
}

bool XYData::operator !=(const XYData &rhs) const
{
    return (mX != rhs.x() || mY != rhs.y());
}

XYData &XYData::operator =(const XYData &rhs)
{
    mX = rhs.x();
    mY = rhs.y();
    this->setParent(rhs.parent());
    return *this;
}

