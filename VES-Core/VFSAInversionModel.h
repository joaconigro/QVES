#ifndef VFSAINVERSIONMODEL_H
#define VFSAINVERSIONMODEL_H
#include "InversionModel.h"
#include "ves-core_global.h"
#include "VFSA/VfsaData.h"

class VESCORESHARED_EXPORT VFSAInversionModel : public InversionModel
{
    Q_OBJECT

    QList<VfsaData> mVFSAParameters;
    double mVFSAError;

public:
    explicit VFSAInversionModel(QObject *parent = nullptr);
    explicit VFSAInversionModel(const QString &name, QObject *parent = nullptr);
    explicit VFSAInversionModel(const InversionModel& im);
    VFSAInversionModel(const VFSAInversionModel& vm);
    //VFSAInversionModel();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    void inversion(const QList<SpliceData> &fieldData) override;
    void updateInversionModelEdited(const QList<SpliceData> &fieldData) override;


    QList<VfsaData> getVFSAParameters() const;
    double getVFSAError() const;
    void setVFSAError(double getVFSAError);

    void addVFSAData(const VfsaData &data);
    void addVFSAData(const double &data);
};

Q_DECLARE_METATYPE(VFSAInversionModel)

#endif // VFSAINVERSIONMODEL_H
