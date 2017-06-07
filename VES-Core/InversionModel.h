#ifndef INVERSIONMODEL_H
#define INVERSIONMODEL_H

#include "ves-core_global.h"
#include <QObject>
#include "BasicData.h"
#include "ModelData.h"
#include "VfsaParameters.h"
#include <QList>

class VESCORESHARED_EXPORT InversionModel : public QObject
{
    Q_OBJECT

public:
    enum class InversionAlgorithm{Zohdy, Vfsa, Manual, Unkown};
    enum class ZohdyFilters{Johansen, ONeill};

private:
    QString mName;
    QString mId;
    double mErrorResult;
    QString mErrorString;
    InversionAlgorithm mUsedAlgorithm;
    ZohdyFilters mZohdyFilter;
    QList<BasicData> mCalculatedData;
    QList<ModelData> mModel;
    VfsaParameters mPreviousParameters;
    VfsaParameters mCurrentParameters;



public:
    explicit InversionModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // INVERSIONMODEL_H
