#ifndef VFSAINVERSIONMODEL_H
#define VFSAINVERSIONMODEL_H
#include "InversionModel.h"
#include "ves-core_global.h"

class VESCORESHARED_EXPORT VFSAInversionModel : public InversionModel
{
public:
    explicit VFSAInversionModel(QObject *parent = nullptr);
    explicit VFSAInversionModel(const QString &name, QObject *parent = nullptr);
    explicit VFSAInversionModel(const InversionModel& im);
    VFSAInversionModel(const VFSAInversionModel& vm);
    //VFSAInversionModel();

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    void inversion(const QList<SpliceData> &fieldData) override;
};

Q_DECLARE_METATYPE(VFSAInversionModel)

#endif // VFSAINVERSIONMODEL_H
