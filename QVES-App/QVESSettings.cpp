#include "QVESSettings.h"

QString QVESSettings::lastDirectory() const
{
    return mLastDirectory;
}

void QVESSettings::setLastDirectory(const QString &lastDirectory)
{
    mLastDirectory = lastDirectory;
}

void QVESSettings::appendLastProject(const QString &project)
{
    if(!mLastOpenedProjects.contains(project)){
        mLastOpenedProjects.insert(0, project);
    }
}

QString QVESSettings::VESName() const
{
    return mVESName;
}

void QVESSettings::setVESName(const QString &VESName)
{
    mVESName = VESName;
}

int QVESSettings::zohdyFilter() const
{
    return mZohdyFilter;
}

void QVESSettings::setZohdyFilter(int zohdyFilter)
{
    mZohdyFilter = zohdyFilter;
}

double QVESSettings::autoDarZarroukThreshold() const
{
    return mAutoDarZarroukThreshold;
}

void QVESSettings::setAutoDarZarroukThreshold(double autoDarZarroukThreshold)
{
    mAutoDarZarroukThreshold = autoDarZarroukThreshold;
}

bool QVESSettings::autoDarZarrouk() const
{
    return mAutoDarZarrouk;
}

void QVESSettings::setAutoDarZarrouk(bool autoDarZarrouk)
{
    mAutoDarZarrouk = autoDarZarrouk;
}

double QVESSettings::vFSAInitialTemperature() const
{
    return mVFSAInitialTemperature;
}

void QVESSettings::setVFSAInitialTemperature(double vFSAInitialTemperature)
{
    mVFSAInitialTemperature = vFSAInitialTemperature;
}

int QVESSettings::vFSAIterationsPerTemperature() const
{
    return mVFSAIterationsPerTemperature;
}

void QVESSettings::setVFSAIterationsPerTemperature(int vFSAIterationsPerTemperature)
{
    mVFSAIterationsPerTemperature = vFSAIterationsPerTemperature;
}

int QVESSettings::vFSAMovesPerTemperature() const
{
    return mVFSAMovesPerTemperature;
}

void QVESSettings::setVFSAMovesPerTemperature(int vFSAMovesPerTemperature)
{
    mVFSAMovesPerTemperature = vFSAMovesPerTemperature;
}

int QVESSettings::vFSASolutions() const
{
    return mVFSASolutions;
}

void QVESSettings::setVFSASolutions(int vFSASolutions)
{
    mVFSASolutions = vFSASolutions;
}

int QVESSettings::vFSANumberOfParameters() const
{
    return mVFSANumberOfParameters;
}

void QVESSettings::setVFSANumberOfParameters(int vFSANumberOfParameters)
{
    mVFSANumberOfParameters = vFSANumberOfParameters;
}

int QVESSettings::vFSANumberOfBeds() const
{
    return mVFSANumberOfBeds;
}

void QVESSettings::setVFSANumberOfBeds(int vFSANumberOfBeds)
{
    mVFSANumberOfBeds = vFSANumberOfBeds;
}

double QVESSettings::vFSAMaximunError() const
{
    return mVFSAMaximunError;
}

void QVESSettings::setVFSAMaximunError(double vFSAMaximunError)
{
    mVFSAMaximunError = vFSAMaximunError;
}

double QVESSettings::vFSAMinimunPdf() const
{
    return mVFSAMinimunPdf;
}

void QVESSettings::setVFSAMinimunPdf(double vFSAMinimunPdf)
{
    mVFSAMinimunPdf = vFSAMinimunPdf;
}

int QVESSettings::chartTheme() const
{
    return mChartTheme;
}

void QVESSettings::setChartTheme(int chartTheme)
{
    mChartTheme = chartTheme;
}

double QVESSettings::fieldPointSize() const
{
    return mFieldPointSize;
}

void QVESSettings::setFieldPointSize(double fieldPointSize)
{
    mFieldPointSize = fieldPointSize;
}

QColor QVESSettings::fieldColor() const
{
    return mFieldColor;
}

void QVESSettings::setFieldColor(const QColor &fieldColor)
{
    mFieldColor = fieldColor;
}

int QVESSettings::fieldMarkerType() const
{
    return mFieldMarkerType;
}

void QVESSettings::setFieldMarkerType(int fieldMarkerType)
{
    mFieldMarkerType = fieldMarkerType;
}

bool QVESSettings::showField() const
{
    return mShowField;
}

void QVESSettings::setShowField(bool showField)
{
    mShowField = showField;
}

double QVESSettings::splicePointSize() const
{
    return mSplicePointSize;
}

void QVESSettings::setSplicePointSize(double splicePointSize)
{
    mSplicePointSize = splicePointSize;
}

QColor QVESSettings::spliceColor() const
{
    return mSpliceColor;
}

void QVESSettings::setSpliceColor(const QColor &spliceColor)
{
    mSpliceColor = spliceColor;
}

int QVESSettings::spliceMarkerType() const
{
    return mSpliceMarkerType;
}

void QVESSettings::setSpliceMarkerType(int spliceMarkerType)
{
    mSpliceMarkerType = spliceMarkerType;
}

bool QVESSettings::showSplice() const
{
    return mShowSplice;
}

void QVESSettings::setShowSplice(bool showSplice)
{
    mShowSplice = showSplice;
}

double QVESSettings::calculatedPointSize() const
{
    return mCalculatedPointSize;
}

void QVESSettings::setCalculatedPointSize(double calculatedPointSize)
{
    mCalculatedPointSize = calculatedPointSize;
}

QColor QVESSettings::calculatedColor() const
{
    return mCalculatedColor;
}

void QVESSettings::setCalculatedColor(const QColor &calculatedColor)
{
    mCalculatedColor = calculatedColor;
}

int QVESSettings::calculatedMarkerType() const
{
    return mCalculatedMarkerType;
}

void QVESSettings::setCalculatedMarkerType(int calculatedMarkerType)
{
    mCalculatedMarkerType = calculatedMarkerType;
}

bool QVESSettings::showCalculated() const
{
    return mShowCalculated;
}

void QVESSettings::setShowCalculated(bool showCalculated)
{
    mShowCalculated = showCalculated;
}

double QVESSettings::modelLineWidth() const
{
    return mModelLineWidth;
}

void QVESSettings::setModelLineWidth(double modelLineWidth)
{
    mModelLineWidth = modelLineWidth;
}

QColor QVESSettings::modelColor() const
{
    return mModelColor;
}

void QVESSettings::setModelColor(const QColor &modelColor)
{
    mModelColor = modelColor;
}

bool QVESSettings::showModel() const
{
    return mShowModel;
}

void QVESSettings::setShowModel(bool showModel)
{
    mShowModel = showModel;
}

QStringList QVESSettings::lastOpenedProjects() const
{
    return mLastOpenedProjects;
}

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

    emit settingsLoaded();
}

void QVESSettings::writeSettings() const
{
    writeGeneralSettings();
    writeInversionSettings();
    writeGraphicsSettings();
}
