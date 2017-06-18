#include "VES.h"
#include <QUuid>

VES::VES(QObject *parent) : QObject(parent)
{
    mId = QUuid::createUuid().toString();
}
