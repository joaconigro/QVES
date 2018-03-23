#include "QVESSettingsDialog.h"
#include "ui_QVESSettingsDialog.h"

void QVESSettingsDialog::initialize()
{
    languages.append(tr("Español"));
    languages.append(tr("Inglés"));
    ui->languageComboBox->addItems(languages);

    zohdyFilters.append("Johansen");
    zohdyFilters.append("O'Neill");
    ui->zohdyFiltersComboBox->addItems(zohdyFilters);

    chartThemes.append(tr("Claro (por defecto)"));
    chartThemes.append(tr("Azul claro"));
    chartThemes.append(tr("Oscuro"));
    chartThemes.append(tr("Arena marrón"));
    ui->chartThemeComboBox->addItems(chartThemes);

    series.append(tr("Campo"));
    series.append(tr("Empalmes"));
    series.append(tr("Calculados"));
    series.append(tr("Modelos"));
    series.append(tr("Resaltados"));
    ui->seriesListWidget->addItems(series);

    markerSymbols.append(tr("Círculo"));
    markerSymbols.append(tr("Cuadrado"));
    markerSymbols.append(tr("Estrella"));
    markerSymbols.append(tr("Triángulo"));
    ui->pointSymbolTypeComboBox->addItems(markerSymbols);

}

void QVESSettingsDialog::readSettings()
{
    mLanguage = mSettings->language();
    mVESName = mSettings->VESName();

    mZohdyFilter = mSettings->zohdyFilter();
    mAutoDarZarroukThreshold = mSettings->autoDarZarroukThreshold();
    mAutoDarZarrouk = mSettings->autoDarZarrouk();

    mVFSAInitialTemperature = mSettings->vFSAInitialTemperature();
    mVFSAIterationsPerTemperature = mSettings->vFSAIterationsPerTemperature();
    mVFSAMovesPerTemperature = mSettings->vFSAMovesPerTemperature();
    mVFSASolutions = mSettings->vFSASolutions();
    mVFSANumberOfBeds = mSettings->vFSANumberOfBeds();
    mVFSAMaximunError = mSettings->vFSAMaximunError();
    mVFSAMinimunPdf = mSettings->vFSAMinimunPdf();

    mChartTheme = mSettings->chartTheme();
    mFieldPointSize = mSettings->fieldPointSize();
    mFieldColor = mSettings->fieldColor();
    mFieldMarkerType = mSettings->fieldMarkerType();
    mSplicePointSize = mSettings->splicePointSize();
    mSpliceColor = mSettings->spliceColor();
    mSpliceMarkerType = mSettings->spliceMarkerType();
    mCalculatedPointSize = mSettings->calculatedPointSize();
    mCalculatedColor = mSettings->calculatedColor();
    mCalculatedMarkerType = mSettings->calculatedMarkerType();
    mModelLineWidth = mSettings->modelLineWidth();
    mModelColor = mSettings->modelColor();
}

void QVESSettingsDialog::configureUi()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Aceptar"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));


    ui->languageComboBox->setCurrentIndex(mLanguage);

    ui->defaultVESNameLineEdit->setText(mVESName);


    ui->zohdyFiltersComboBox->setCurrentIndex(mZohdyFilter);
    ui->autoDarZarroukCheckBox->setChecked(mAutoDarZarrouk);
    ui->thresholdDoubleSpinBox->setValue(mAutoDarZarroukThreshold);

    ui->vfsaInitialTemperatureDoubleSpinBox->setValue(mVFSAInitialTemperature);
    ui->vfsaIterationPerSolutionsSpinBox->setValue(mVFSAIterationsPerTemperature);
    ui->vfsaMaxErrorDoubleSpinBox->setValue(mVFSAMaximunError);
    ui->vfsaMinPDFDoubleSpinBox->setValue(mVFSAMinimunPdf);
    ui->vfsaMovesPerTemperatureSpinBox->setValue(mVFSAMovesPerTemperature);
    ui->vfsaNumberOfBedSpinBox->setValue(mVFSANumberOfBeds);
    ui->vfsaSolutionsSpinBox->setValue(mVFSASolutions);


    ui->chartThemeComboBox->setCurrentIndex(mChartTheme);
    configureSelectedSeries();

}

void QVESSettingsDialog::configureSelectedSeries()
{
    switch (selectedSeries) {
    case -1:
        ui->colorPushButton->setVisible(false);
        ui->pointSymbolTypeComboBox->setVisible(false);
        ui->pointSymbolTypeLabel->setVisible(false);
        ui->sizeDoubleSpinBox->setVisible(false);
        ui->sizeLabel->setVisible(false);
        break;
    case 3:
        ui->colorPushButton->setVisible(true);
        ui->pointSymbolTypeComboBox->setVisible(false);
        ui->pointSymbolTypeLabel->setVisible(false);
        ui->sizeDoubleSpinBox->setVisible(true);
        ui->sizeDoubleSpinBox->setValue(mModelLineWidth);
        ui->sizeLabel->setVisible(true);
        break;
    case 4:
        ui->colorPushButton->setVisible(true);
        ui->pointSymbolTypeComboBox->setVisible(false);
        ui->pointSymbolTypeLabel->setVisible(false);
        ui->sizeDoubleSpinBox->setVisible(false);
        ui->sizeLabel->setVisible(false);
        break;
    default:
        ui->colorPushButton->setVisible(true);
        ui->pointSymbolTypeComboBox->setVisible(true);
        ui->pointSymbolTypeLabel->setVisible(true);
        ui->sizeDoubleSpinBox->setVisible(true);
        ui->sizeLabel->setVisible(true);

        switch (selectedSeries) {
        case 0:
            ui->pointSymbolTypeComboBox->setCurrentIndex(mFieldMarkerType);
            ui->sizeDoubleSpinBox->setValue(mFieldPointSize);
            break;
        case 1:
            ui->pointSymbolTypeComboBox->setCurrentIndex(mSpliceMarkerType);
            ui->sizeDoubleSpinBox->setValue(mSplicePointSize);
            break;
        case 2:
            ui->pointSymbolTypeComboBox->setCurrentIndex(mCalculatedMarkerType);
            ui->sizeDoubleSpinBox->setValue(mCalculatedPointSize);
            break;
        default:
            break;
        }
        break;
    }
}

QVESSettingsDialog::QVESSettingsDialog(QVESSettings *settings, int selectedTab, QWidget *parent) :
    QDialog(parent),
    mSettings(settings),
    ui(new Ui::QVESSettingsDialog)
{
    ui->setupUi(this);
    selectedSeries = -1;

    ui->tabWidget->setCurrentIndex(selectedTab);
    initialize();
    readSettings();
    configureUi();
}

QVESSettingsDialog::~QVESSettingsDialog()
{
    delete ui;
}

void QVESSettingsDialog::on_languageComboBox_currentIndexChanged(int index)
{
    mLanguage = index;
}

void QVESSettingsDialog::on_defaultVESNameLineEdit_textChanged(const QString &arg1)
{
    mVESName = arg1;
}

void QVESSettingsDialog::on_clearRecentsPushButton_clicked()
{
    mSettings->clearRecentProjects();
}

void QVESSettingsDialog::on_resetSettingsPushButton_clicked()
{
    mSettings->restoreDefaultSettings();
    readSettings();
    configureUi();
}

void QVESSettingsDialog::on_zohdyFiltersComboBox_currentIndexChanged(int index)
{
    mZohdyFilter = index;
}

void QVESSettingsDialog::on_autoDarZarroukCheckBox_clicked()
{
    mAutoDarZarrouk = ui->autoDarZarroukCheckBox->isChecked();
    ui->thresholdDoubleSpinBox->setEnabled(mAutoDarZarrouk);
}

void QVESSettingsDialog::on_thresholdDoubleSpinBox_valueChanged(double arg1)
{
    mAutoDarZarroukThreshold = arg1;
}

void QVESSettingsDialog::on_buttonBox_accepted()
{
    mSettings->setLanguage(mLanguage);
    mSettings->setVESName(mVESName);

    mSettings->setZohdyFilter(mZohdyFilter);
    mSettings->setAutoDarZarroukThreshold(mAutoDarZarroukThreshold);
    mSettings->setAutoDarZarrouk(mAutoDarZarrouk);

    mSettings->setVFSAInitialTemperature(mVFSAInitialTemperature);
    mSettings->setVFSAIterationsPerTemperature(mVFSAIterationsPerTemperature);
    mSettings->setVFSAMovesPerTemperature(mVFSAMovesPerTemperature);
    mSettings->setVFSASolutions(mVFSASolutions);
    mSettings->setVFSANumberOfBeds(mVFSANumberOfBeds);
    mSettings->setVFSAMaximunError(mVFSAMaximunError);
    mSettings->setVFSAMinimunPdf(mVFSAMinimunPdf);


    mSettings->setChartTheme(mChartTheme);

    mSettings->setFieldPointSize(mFieldPointSize);
    mSettings->setFieldColor(mFieldColor);
    mSettings->setFieldMarkerType(mFieldMarkerType);

    mSettings->setSplicePointSize(mSplicePointSize);
    mSettings->setSpliceColor(mSpliceColor);
    mSettings->setSpliceMarkerType(mSpliceMarkerType);

    mSettings->setCalculatedPointSize(mCalculatedPointSize);
    mSettings->setCalculatedColor(mCalculatedColor);
    mSettings->setCalculatedMarkerType(mCalculatedMarkerType);

    mSettings->setModelLineWidth(mModelLineWidth);
    mSettings->setModelColor(mModelColor);

    emit mSettings->settingsLoaded();
}

void QVESSettingsDialog::on_vfsaSolutionsSpinBox_valueChanged(int arg1)
{
    mVFSASolutions = arg1;
}

void QVESSettingsDialog::on_vfsaIterationPerSolutionsSpinBox_valueChanged(int arg1)
{
    mVFSAIterationsPerTemperature = arg1;
}

void QVESSettingsDialog::on_vfsaMovesPerTemperatureSpinBox_valueChanged(int arg1)
{
    mVFSAMovesPerTemperature = arg1;
}

void QVESSettingsDialog::on_vfsaNumberOfBedSpinBox_valueChanged(int arg1)
{
    mVFSANumberOfBeds = arg1;
}

void QVESSettingsDialog::on_vfsaInitialTemperatureDoubleSpinBox_valueChanged(double arg1)
{
    mVFSAInitialTemperature = arg1;
}

void QVESSettingsDialog::on_vfsaMaxErrorDoubleSpinBox_valueChanged(double arg1)
{
    mVFSAMaximunError = arg1;
}

void QVESSettingsDialog::on_vfsaMinPDFDoubleSpinBox_valueChanged(double arg1)
{
    mVFSAMinimunPdf = arg1;
}

void QVESSettingsDialog::on_chartThemeComboBox_currentIndexChanged(int index)
{
    mChartTheme = index;
}

void QVESSettingsDialog::on_seriesListWidget_currentRowChanged(int currentRow)
{
    selectedSeries = currentRow;
    configureSelectedSeries();
}

void QVESSettingsDialog::on_sizeDoubleSpinBox_valueChanged(double arg1)
{
    switch (selectedSeries) {
    case 0:
        mFieldPointSize = arg1;
        break;
    case 1:
        mSplicePointSize = arg1;
        break;
    case 2:
        mCalculatedPointSize = arg1;
        break;
    case 3:
        mModelLineWidth = arg1;
        break;
    default:
        break;
    }
}

void QVESSettingsDialog::on_pointSymbolTypeComboBox_currentIndexChanged(int index)
{
    switch (selectedSeries) {
    case 0:
        mFieldMarkerType = index;
        break;
    case 1:
        mSpliceMarkerType = index;
        break;
    case 2:
        mCalculatedMarkerType = index;
        break;
    default:
        break;
    }
}

void QVESSettingsDialog::on_colorPushButton_clicked()
{
    QColor seriesColor;
    switch (selectedSeries) {
    case 0:
        seriesColor = mFieldColor;
        break;
    case 1:
        seriesColor = mSpliceColor;
        break;
    case 2:
        seriesColor = mCalculatedColor;
        break;
    case 3:
        seriesColor = mModelColor;
        break;
    default:
        break;
    }

    QColor selectedColor = QColorDialog::getColor(seriesColor, this, tr("Seleccione un color"));

    switch (selectedSeries) {
    case 0:
        mFieldColor = selectedColor;
        break;
    case 1:
        mSpliceColor = selectedColor;
        break;
    case 2:
        mCalculatedColor = selectedColor;
        break;
    case 3:
        mModelColor = selectedColor;
        break;
    default:
        break;
    }
}
