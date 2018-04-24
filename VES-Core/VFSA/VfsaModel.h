#ifndef VFSAMODEL_H
#define VFSAMODEL_H

#include <QObject>
#include "VfsaData.h"
#include <QList>


class VfsaModel : public QObject
{
    Q_OBJECT

    QList<VfsaData> mParameters;
    double mVFSAError;

public:
    VfsaModel(QObject *parent = nullptr);

    void addVFSAData(const VfsaData &data);
    void addVFSAData(const double &data);

    QList<VfsaData> getParameters() const;
    double getVFSAError() const;
    void setVFSAError(double value);
};

#endif // VFSAMODEL_H
