#ifndef QVESSETTINGSDIALOG_H
#define QVESSETTINGSDIALOG_H

#include <QDialog>
#include <QColor>
#include <QStringList>
#include <QColorDialog>
#include "QVESSettings.h"

namespace Ui {
class QVESSettingsDialog;
}

class QVESSettingsDialog : public QDialog
{
    Q_OBJECT


    QVESSettings* mSettings;
    QStringList languages;
    QStringList zohdyFilters;
    QStringList chartThemes;
    QStringList series;
    QStringList markerSymbols;
    QStringList chartAnimationOptions;
    int selectedSeries;

    int mLanguage;
    QString mVESName;

    int mZohdyFilter;
    double mAutoDarZarroukThreshold;
    bool mAutoDarZarrouk;
    int mDefaultNumberOfLayers;

    double mVFSAInitialTemperature;
    int mVFSAIterationsPerTemperature;
    int mVFSAMovesPerTemperature;
    int mVFSASolutions;
    int mVFSANumberOfBeds;
    double mVFSAMaximunError;

    int mChartTheme;
    int mChartAnimation;
    double mFieldPointSize;
    QColor mFieldColor;
    int mFieldMarkerType;
    double mSplicePointSize;
    QColor mSpliceColor;
    int mSpliceMarkerType;
    double mCalculatedPointSize;
    QColor mCalculatedColor;
    int mCalculatedMarkerType;
    double mModelLineWidth;
    QColor mModelColor;
    QColor mHighlightColor;

    void initialize();
    void readSettings();
    void configureUi();
    void configureSelectedSeries();

public:
    explicit QVESSettingsDialog(QVESSettings* settings, int selectedTab = 0, QWidget *parent = nullptr);
    ~QVESSettingsDialog() override;

private slots:
    void on_languageComboBox_currentIndexChanged(int index);
    void on_defaultVESNameLineEdit_textChanged(const QString &arg1);
    void on_clearRecentsPushButton_clicked();
    void on_resetSettingsPushButton_clicked();
    void on_zohdyFiltersComboBox_currentIndexChanged(int index);
    void on_autoDarZarroukCheckBox_clicked();
    void on_thresholdDoubleSpinBox_valueChanged(double arg1);
    void on_buttonBox_accepted();
    void on_vfsaSolutionsSpinBox_valueChanged(int arg1);
    void on_vfsaIterationPerSolutionsSpinBox_valueChanged(int arg1);
    void on_vfsaMovesPerTemperatureSpinBox_valueChanged(int arg1);
    void on_vfsaNumberOfBedSpinBox_valueChanged(int arg1);
    void on_vfsaInitialTemperatureDoubleSpinBox_valueChanged(double arg1);
    void on_vfsaMaxErrorDoubleSpinBox_valueChanged(double arg1);
    void on_chartThemeComboBox_currentIndexChanged(int index);
    void on_seriesListWidget_currentRowChanged(int currentRow);
    void on_sizeDoubleSpinBox_valueChanged(double arg1);
    void on_pointSymbolTypeComboBox_currentIndexChanged(int index);
    void on_colorPushButton_clicked();
    void on_chartAnimationComboBox_currentIndexChanged(int index);
    void on_defautlNumberOfLayersSpinBox_valueChanged(int arg1);

private:
    Ui::QVESSettingsDialog *ui;

signals:
    void settingsChanged();
};

#endif // QVESSETTINGSDIALOG_H
