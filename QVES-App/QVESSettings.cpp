#include "QVESSettings.h"

void QVESSettings::defaultGeneralSettings()
{
    mLastDirectory = "";
    QStringList l;
    mLastOpenedProjects = l;
    mVESName = "";
}

void QVESSettings::defaultInversionSettings()
{
    mZohdyFilter = 0;
    mAutoDarZarroukThreshold = 0.12;
    mAutoDarZarrouk = true;

    mVFSAInitialTemperature = 0.01;
    mVFSAIterationsPerTemperature = 1000;
    mVFSAMovesPerTemperature = 20;
    mVFSASolutions = 10;
    mVFSANumberOfParameters = 5;
    mVFSANumberOfBeds = 3;
    mVFSAMaximunError = 0.0001;
    mVFSAMinimunPdf = 0.6825;
}

void QVESSettings::defaultGraphicsSettings()
{
    mChartTheme = 0;

    mFieldPointSize = 8.0;
    mFieldColor = QColor::fromRgb(32, 159, 223);
    mFieldMarkerType = 0;
    mShowField = true;

    mSplicePointSize = 8.0;
    mSpliceColor = QColor::fromRgb(153, 202, 83);
    mSpliceMarkerType = 1;
    mShowSplice = true;

    mCalculatedPointSize = 10.0;
    mCalculatedColor = QColor::fromRgb(246, 166, 37);
    mCalculatedMarkerType = 3;
    mShowCalculated = true;

    mModelLineWidth = 2.0;
    mModelColor = QColor::fromRgb(109, 95, 213);
    mShowModel = true;
}

void QVESSettings::readGeneralSettings()
{
    mSettingsInitialized = mSettings->value("SettingsInitialized").toBool();
    mLastDirectory = mSettings->value("LastDirectory").toString();
    mLastOpenedProjects = mSettings->value("LastOpenedProjects").toStringList();
    mVESName = mSettings->value("VESName").toString();
}

void QVESSettings::readInversionSettings()
{
    mZohdyFilter = mSettings->value("ZohdyFilter").toInt();
    mAutoDarZarroukThreshold = mSettings->value("AutoDarZarroukThreshold").toDouble();
    mAutoDarZarrouk = mSettings->value("AutoDarZarrouk").toBool();

    mVFSAInitialTemperature = mSettings->value("AutoDarZarroukThreshold").toDouble();
    mVFSAIterationsPerTemperature = mSettings->value("VFSAIterationsPerTemperature").toInt();
    mVFSAMovesPerTemperature = mSettings->value("VFSAMovesPerTemperature").toInt();
    mVFSASolutions = mSettings->value("VFSASolutions").toInt();
    mVFSANumberOfParameters = mSettings->value("VFSANumberOfParameters").toInt();
    mVFSANumberOfBeds = mSettings->value("VFSANumberOfBeds").toInt();
    mVFSAMaximunError = mSettings->value("VFSAMaximunError").toDouble();
    mVFSAMinimunPdf = mSettings->value("VFSAMinimunPdf").toDouble();
}

void QVESSettings::readGraphicsSettings()
{
    mChartTheme = mSettings->value("ChartTheme").toInt();

    mFieldPointSize = mSettings->value("FieldPointSize").toDouble();
    mFieldColor = mSettings->value("FieldColor").value<QColor>();
    mFieldMarkerType = mSettings->value("FieldMarkerType").toInt();
    mShowField = mSettings->value("ShowField").toBool();

    mSplicePointSize = mSettings->value("SplicePointSize").toDouble();
    mSpliceColor = mSettings->value("SpliceColor").value<QColor>();
    mSpliceMarkerType = mSettings->value("SpliceMarkerType").toInt();
    mShowSplice = mSettings->value("ShowSplice").toBool();

    mCalculatedPointSize = mSettings->value("CalculatedPointSize").toDouble();
    mCalculatedColor = mSettings->value("CalculatedColor").value<QColor>();
    mCalculatedMarkerType = mSettings->value("CalculatedMarkerType").toInt();
    mShowCalculated = mSettings->value("ShowCalculated").toBool();

    mModelLineWidth = mSettings->value("ModelLineWidth").toDouble();
    mModelColor = mSettings->value("ModelColor").value<QColor>();
    mShowModel = mSettings->value("ShowModel").toBool();
}

void QVESSettings::writeGeneralSettings() const
{
    mSettings->setValue("SettingsInitialized", mSettingsInitialized);
    mSettings->setValue("LastDirectory", mLastDirectory);
    mSettings->setValue("LastOpenedProjects", mLastOpenedProjects);
    mSettings->setValue("VESName", mVESName);
}

void QVESSettings::writeInversionSettings() const
{
    mSettings->setValue("ZohdyFilter", mZohdyFilter);
    mSettings->setValue("AutoDarZarroukThreshold", mAutoDarZarroukThreshold);
    mSettings->setValue("AutoDarZarrouk", mAutoDarZarrouk);

    mSettings->setValue("AutoDarZarroukThreshold", mVFSAInitialTemperature);
    mSettings->setValue("VFSAIterationsPerTemperature", mVFSAIterationsPerTemperature);
    mSettings->setValue("VFSAMovesPerTemperature", mVFSAMovesPerTemperature);
    mSettings->setValue("VFSASolutions", mVFSASolutions);
    mSettings->setValue("VFSANumberOfParameters", mVFSANumberOfParameters);
    mSettings->setValue("VFSANumberOfBeds", mVFSANumberOfBeds);
    mSettings->setValue("VFSAMaximunError", mVFSAMaximunError);
    mSettings->setValue("VFSAMinimunPdf", mVFSAMinimunPdf);
}

void QVESSettings::writeGraphicsSettings() const
{
    mSettings->setValue("ChartTheme", mChartTheme);

    mSettings->setValue("FieldPointSize", mFieldPointSize);
    mSettings->setValue("FieldColor", mFieldColor);
    mSettings->setValue("FieldMarkerType", mFieldMarkerType);
    mSettings->setValue("ShowField", mShowField);

    mSettings->setValue("SplicePointSize", mSplicePointSize);
    mSettings->setValue("SpliceColor", mSpliceColor);
    mSettings->setValue("SpliceMarkerType", mSpliceMarkerType);
    mSettings->setValue("ShowSplice", mShowSplice);

    mSettings->setValue("CalculatedPointSize", mCalculatedPointSize);
    mSettings->setValue("CalculatedColor", mCalculatedColor);
    mSettings->setValue("CalculatedMarkerType", mCalculatedMarkerType);
    mSettings->setValue("ShowCalculated", mShowCalculated);

    mSettings->setValue("ModelLineWidth", mModelLineWidth);
    mSettings->setValue("ModelColor", mModelColor);
    mSettings->setValue("ShowModel", mShowModel);
}

QVESSettings::QVESSettings(QObject *parent) : QObject(parent)
{

}

void QVESSettings::setSettings(QSettings *settings)
{
    mSettings = settings;
}

void QVESSettings::restoreDefaultSettings()
{
    defaultGeneralSettings();
    defaultInversionSettings();
    defaultGraphicsSettings();
}

void QVESSettings::readSettings()
{
    readGeneralSettings();
    readInversionSettings();
    readGraphicsSettings();

    if(!mSettingsInitialized){
        restoreDefaultSettings();
        mSettingsInitialized = true;
    }
}

void QVESSettings::writeSettings() const
{
    writeGeneralSettings();
    writeInversionSettings();
    writeGraphicsSettings();
}
