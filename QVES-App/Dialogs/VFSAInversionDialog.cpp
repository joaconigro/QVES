#include "VFSAInversionDialog.h"
#include "ui_VFSAInversionDialog.h"
#include <QtMath>
#include <QTableWidgetItem>


VFSAInversionDialog::VFSAInversionDialog(const VES *currentVES, const VFSAParameters settingsParameters, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VFSAInversionDialog),
    mVESParameters(currentVES->currentParameters()),
    mSettingsParameters(settingsParameters),
    mFieldData(currentVES->splices())
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Aceptar"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));

    for (int c = 0; c < ui->bedsTableWidget->horizontalHeader()->count(); ++c)
    {
        ui->bedsTableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }

    ui->bedsTableWidget->setRowCount(mSettingsParameters.numberOfBeds());
    mCalculator = nullptr;
    mValidator = new QDoubleValidator(0.01, qInf(), 2, this);
    configureUiParameters();
    //validate();

//    connect(ui->buttonBox->button(QDialogButtonBox::Cancel)->clicked,
//            mCalculator, &VFSACalculator::abortAllJobs);
//    connect(mCalculator, &VFSACalculator::allCalculationsCompleted, this, &VFSAInversionDialog::onCalculationCompleted);
//    connect(mCalculator, &VFSACalculator::totalProgressReport, this->ui->processProgressBar, &QProgressBar::setValue);
}

VFSAInversionDialog::~VFSAInversionDialog()
{
    if (mCalculator)
        delete mCalculator;
    delete ui;
}

QList<VFSAInversionModel *> VFSAInversionDialog::finalModels() const
{
    return mFinalModels;
}

VFSAParameters VFSAInversionDialog::currentParameters() const
{
    return mCurrentParameters;
}

void VFSAInversionDialog::configureUiParameters()
{
    ui->temperatureDoubleSpinBox->setValue(mCurrentParameters.initialTemperature());
    ui->iterationsSpinBox->setValue(mCurrentParameters.iterationsPerTemperature());
    ui->movesPerTemperatureSpinBox->setValue(mCurrentParameters.movesPerTemperature());
    ui->solutionsSpinBox->setValue(mCurrentParameters.solutions());
    ui->errorDoubleSpinBox->setValue(mCurrentParameters.maximunError());

    ui->bedsSpinBox->setValue(mCurrentParameters.numberOfBeds());
    configureTableWidgetLimits();
    validate();
}

void VFSAInversionDialog::configureTableWidgetLimits()
{
    ui->bedsTableWidget->setRowCount(mCurrentParameters.numberOfBeds());
    int resistivityLimit = qCeil(mCurrentParameters.numberOfParameters() / 2.0);

    for (int i = 0; i < resistivityLimit; i++) {
        //Lower resistivity limit
        QTableWidgetItem *lowerLimitCell = ui->bedsTableWidget->item(i, 2);
        if(!lowerLimitCell)
        {
            lowerLimitCell = new QTableWidgetItem;
            ui->bedsTableWidget->setItem(i, 2, lowerLimitCell);
        }
        lowerLimitCell->setData(Qt::EditRole, mCurrentParameters.limitAt(i).lower());
        lowerLimitCell->setTextAlignment(Qt::AlignRight);

        //Upper resistivity limit
        QTableWidgetItem *upperLimitCell = ui->bedsTableWidget->item(i, 3);
        if(!upperLimitCell)
        {
            upperLimitCell = new QTableWidgetItem;
            ui->bedsTableWidget->setItem(i, 3, upperLimitCell);
        }
        upperLimitCell->setData(Qt::EditRole, mCurrentParameters.limitAt(i).upper());
        upperLimitCell->setTextAlignment(Qt::AlignRight);
    }

    for (int i = resistivityLimit; i < mCurrentParameters.numberOfParameters(); i++) {
        //Lower thickness limit
        QTableWidgetItem *lowerThicknessLimitCell = ui->bedsTableWidget->item(i - resistivityLimit, 0);
        if(!lowerThicknessLimitCell)
        {
            lowerThicknessLimitCell = new QTableWidgetItem;
            ui->bedsTableWidget->setItem(i - resistivityLimit, 0, lowerThicknessLimitCell);
        }
        lowerThicknessLimitCell->setData(Qt::EditRole, mCurrentParameters.limitAt(i).lower());
        lowerThicknessLimitCell->setTextAlignment(Qt::AlignRight);

        //Upper thickness limit
        QTableWidgetItem *upperThicknessLimitCell = ui->bedsTableWidget->item(i - resistivityLimit, 1);
        if(!upperThicknessLimitCell)
        {
            upperThicknessLimitCell = new QTableWidgetItem;
            ui->bedsTableWidget->setItem(i - resistivityLimit, 1, upperThicknessLimitCell);
        }
        upperThicknessLimitCell->setData(Qt::EditRole, mCurrentParameters.limitAt(i).upper());
        upperThicknessLimitCell->setTextAlignment(Qt::AlignRight);
    }


    //Infinite thickness limit
    QTableWidgetItem *lowerThicknessLimitCell = ui->bedsTableWidget->item(resistivityLimit - 1, 0);
    if(!lowerThicknessLimitCell)
    {
        lowerThicknessLimitCell = new QTableWidgetItem;
        ui->bedsTableWidget->setItem(resistivityLimit - 1, 0, lowerThicknessLimitCell);
    }
    lowerThicknessLimitCell->setData(Qt::DisplayRole, qInf());
    lowerThicknessLimitCell->setTextAlignment(Qt::AlignRight);

    //Infinite thickness limit
    QTableWidgetItem *upperThicknessLimitCell = ui->bedsTableWidget->item(resistivityLimit - 1, 1);
    if(!upperThicknessLimitCell)
    {
        upperThicknessLimitCell = new QTableWidgetItem;
        ui->bedsTableWidget->setItem(resistivityLimit - 1, 1, upperThicknessLimitCell);
    }
    upperThicknessLimitCell->setData(Qt::DisplayRole, qInf());
    upperThicknessLimitCell->setTextAlignment(Qt::AlignRight);

}

void VFSAInversionDialog::validate()
{
    ui->processPushButton->setEnabled(mCurrentParameters.isValid());
}

void VFSAInversionDialog::selectedParametersChanged()
{
    if (ui->defaultParametersRadioButton->isChecked()){
        mCurrentParameters = mSettingsParameters;
        ui->parametersFrame->setEnabled(false);
    } else if (ui->customParametersRadioButton->isChecked()) {
        mCurrentParameters = mVESParameters;
        ui->parametersFrame->setEnabled(true);
    }

    configureUiParameters();
}

void VFSAInversionDialog::on_temperatureDoubleSpinBox_valueChanged(double arg1)
{
    mCurrentParameters.setInitialTemperature(arg1);
    validate();
}

void VFSAInversionDialog::on_iterationsSpinBox_valueChanged(int arg1)
{
    mCurrentParameters.setIterationsPerTemperature(arg1);
    validate();
}

void VFSAInversionDialog::on_movesPerTemperatureSpinBox_valueChanged(int arg1)
{
    mCurrentParameters.setMovesPerTemperature(arg1);
    validate();
}

void VFSAInversionDialog::on_solutionsSpinBox_valueChanged(int arg1)
{
    mCurrentParameters.setSolutions(arg1);
    validate();
}

void VFSAInversionDialog::on_errorDoubleSpinBox_valueChanged(double arg1)
{
    mCurrentParameters.setMaximunError(arg1);
    validate();
}

void VFSAInversionDialog::on_bedsSpinBox_valueChanged(int arg1)
{
    mCurrentParameters.setNumberOfBeds(arg1);
    mCurrentParameters.setNumberOfParameters(arg1 * 2 - 1);
    configureTableWidgetLimits();
    validate();
}

//void VFSAInversionDialog::onProcessProgressChanged(const int value)
//{
//    ui->processProgressBar->setValue(value);
//}

void VFSAInversionDialog::onCalculationCompleted()
{
    auto list = mCalculator->getFinalModels();
    foreach (auto m, list) {
        mFinalModels.append(new VFSAInversionModel(*m));
    }
}

void VFSAInversionDialog::on_processPushButton_clicked()
{
    if (mCurrentParameters.isValid()){
        if (mCalculator)
            delete mCalculator;

        mCalculator = new VFSACalculator(mFieldData, mCurrentParameters, this);

//        connect(this->ui->buttonBox->button(QDialogButtonBox::Cancel)->clicked,
//                mCalculator, &VFSACalculator::abortAllJobs);
        connect(mCalculator, &VFSACalculator::allCalculationsCompleted, this, &VFSAInversionDialog::onCalculationCompleted);
        connect(mCalculator, &VFSACalculator::totalProgressReport, this->ui->processProgressBar, &QProgressBar::setValue);
        //connect(mCalculator, &VFSACalculator::totalProgressReport, this, &VFSAInversionDialog::onProcessProgressChanged);

        mCalculator->startInversion();

    }
}

//void VFSAInversionDialog::on_buttonBox_rejected()
//{
//    if (mCalculator)
//        mCalculator->abortAllJobs();
//        delete mCalculator;
//}
