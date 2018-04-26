#ifndef VFSAINVERSIONMODEL_H
#define VFSAINVERSIONMODEL_H
#include "InversionModel.h"
#include "ves-core_global.h"

class VESCORESHARED_EXPORT VFSAInversionModel : public InversionModel
{
    Q_OBJECT

    double mVFSAError;
    QList<double> mParameterPDFs;

public:
    explicit VFSAInversionModel(QObject *parent = nullptr);
    explicit VFSAInversionModel(const QString &name, QObject *parent = nullptr);
    explicit VFSAInversionModel(const InversionModel& im);
    VFSAInversionModel(const VFSAInversionModel& vm);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;

    void inversion(const QList<SpliceData> &fieldData) override;
    void updateInversionModelEdited(const QList<SpliceData> &fieldData) override;


    QList<double> getVFSAParameters() const;
    double getVFSAError() const;
    void setVFSAError(double getVFSAError);

    void addVFSAData(int index, const double data, const int numberOfBeds);
    bool getRemoveByPDF() const;
    void setRemoveByPDF(const bool removeByPDF);
    QList<double> getParameterPDFs() const;
    void setParameterPDF(const int index, const double value);
};

Q_DECLARE_METATYPE(VFSAInversionModel)

#endif // VFSAINVERSIONMODEL_H
