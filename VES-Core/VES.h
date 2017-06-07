#ifndef VES_H
#define VES_H

#include "ves-core_global.h"
#include <QObject>
#include "BasicData.h"
#include "SpliceData.h"
#include "LocationData.h"
#include "InversionModel.h"
#include <QList>

class VESCORESHARED_EXPORT VES : public QObject
{
    Q_OBJECT
public:
    explicit VES(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VES_H
