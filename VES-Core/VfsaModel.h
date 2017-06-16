#ifndef VFSAMODEL_H
#define VFSAMODEL_H

#include <QObject>
#include "VfsaData.h"
#include <QList>


class VfsaModel : public QObject
{
    Q_OBJECT

public:
    VfsaModel(QObject *parent = nullptr);

    QList<VfsaData> parameters;
    double vfsaError;
};

#endif // VFSAMODEL_H
