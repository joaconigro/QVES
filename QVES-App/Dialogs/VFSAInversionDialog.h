#ifndef VFSAINVERSIONDIALOG_H
#define VFSAINVERSIONDIALOG_H

#include <QDialog>
#include "VFSA/VFSAParameters.h"
#include "VFSA/VFSACalculator.h"
#include "VFSAInversionModel.h"
#include "VES.h"
#include "SpliceData.h"
#include <QList>
#include <QDoubleValidator>

namespace Ui {
class VFSAInversionDialog;
}

class VFSAInversionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VFSAInversionDialog(const VES *currentVES, const VFSAParameters settingsParameters, QWidget *parent = 0);
    ~VFSAInversionDialog();

    QList<VFSAInversionModel *> finalModels() const;

    VFSAParameters currentParameters() const;

private:
    Ui::VFSAInversionDialog *ui;
    VFSAParameters mVESParameters;
    VFSAParameters mSettingsParameters;
    VFSAParameters mCurrentParameters;
    VFSACalculator *mCalculator;
    QList <VFSAInversionModel *> mFinalModels;
    QList <SpliceData> mFieldData;

    QDoubleValidator *mValidator;


    void configureUiParameters();
    void configureTableWidgetLimits();
    void validate();

private slots:
    void selectedParametersChanged();
    void on_temperatureDoubleSpinBox_valueChanged(double arg1);
    void on_iterationsSpinBox_valueChanged(int arg1);
    void on_movesPerTemperatureSpinBox_valueChanged(int arg1);
    void on_solutionsSpinBox_valueChanged(int arg1);
    void on_errorDoubleSpinBox_valueChanged(double arg1);
    void on_bedsSpinBox_valueChanged(int arg1);

    //void onProcessProgressChanged(const int value);
    void onCalculationCompleted();
    void on_processPushButton_clicked();
    //void on_buttonBox_rejected();
};

#endif // VFSAINVERSIONDIALOG_H
