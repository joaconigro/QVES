#ifndef QVESSETTINGS_H
#define QVESSETTINGS_H

#include <QObject>
#include <QStringList>
#include <QSettings>
#include <QColor>

class QVESSettings : public QObject
{
    Q_OBJECT

    QSettings* mSettings;

    int mLanguage;
    bool mSettingsInitialized;
    QString mLastDirectory;
    QStringList mLastOpenedProjects;
    QString mVESName;


    int mZohdyFilter;
    double mAutoDarZarroukThreshold;
    bool mAutoDarZarrouk;

    double mVFSAInitialTemperature;
    int mVFSAIterationsPerTemperature;
    int mVFSAMovesPerTemperature;
    int mVFSASolutions;
    int mVFSANumberOfBeds;
    double mVFSAMaximunError;
    double mVFSAMinimunPdf;

    int mChartTheme;

    double mFieldPointSize;
    QColor mFieldColor;
    int mFieldMarkerType;
    bool mShowField;

    double mSplicePointSize;
    QColor mSpliceColor;
    int mSpliceMarkerType;
    bool mShowSplice;

    double mCalculatedPointSize;
    QColor mCalculatedColor;
    int mCalculatedMarkerType;
    bool mShowCalculated;

    double mModelLineWidth;
    QColor mModelColor;
    bool mShowModel;


    void defaultGeneralSettings();
    void defaultInversionSettings();
    void defaultGraphicsSettings();

    void readGeneralSettings();
    void readInversionSettings();
    void readGraphicsSettings();

    void writeGeneralSettings() const;
    void writeInversionSettings() const;
    void writeGraphicsSettings() const;

public:
    explicit QVESSettings(QObject *parent = nullptr);

    QString lastDirectory() const;
    void setLastDirectory(const QString &lastDirectory);

    void appendLastProject(const QString &project);

    QString VESName() const;
    void setVESName(const QString &VESName);

    int zohdyFilter() const;
    void setZohdyFilter(int zohdyFilter);

    double autoDarZarroukThreshold() const;
    void setAutoDarZarroukThreshold(double autoDarZarroukThreshold);

    bool autoDarZarrouk() const;
    void setAutoDarZarrouk(bool autoDarZarrouk);

    double vFSAInitialTemperature() const;
    void setVFSAInitialTemperature(double vFSAInitialTemperature);

    int vFSAIterationsPerTemperature() const;
    void setVFSAIterationsPerTemperature(int vFSAIterationsPerTemperature);

    int vFSAMovesPerTemperature() const;
    void setVFSAMovesPerTemperature(int vFSAMovesPerTemperature);

    int vFSASolutions() const;
    void setVFSASolutions(int vFSASolutions);

    int vFSANumberOfBeds() const;
    void setVFSANumberOfBeds(int vFSANumberOfBeds);

    double vFSAMaximunError() const;
    void setVFSAMaximunError(double vFSAMaximunError);

    double vFSAMinimunPdf() const;
    void setVFSAMinimunPdf(double vFSAMinimunPdf);

    int chartTheme() const;
    void setChartTheme(int chartTheme);

    double fieldPointSize() const;
    void setFieldPointSize(double fieldPointSize);

    QColor fieldColor() const;
    void setFieldColor(const QColor &fieldColor);

    int fieldMarkerType() const;
    void setFieldMarkerType(int fieldMarkerType);

    bool showField() const;
    void setShowField(bool showField);

    double splicePointSize() const;
    void setSplicePointSize(double splicePointSize);

    QColor spliceColor() const;
    void setSpliceColor(const QColor &spliceColor);

    int spliceMarkerType() const;
    void setSpliceMarkerType(int spliceMarkerType);

    bool showSplice() const;
    void setShowSplice(bool showSplice);

    double calculatedPointSize() const;
    void setCalculatedPointSize(double calculatedPointSize);

    QColor calculatedColor() const;
    void setCalculatedColor(const QColor &calculatedColor);

    int calculatedMarkerType() const;
    void setCalculatedMarkerType(int calculatedMarkerType);

    bool showCalculated() const;
    void setShowCalculated(bool showCalculated);

    double modelLineWidth() const;
    void setModelLineWidth(double modelLineWidth);

    QColor modelColor() const;
    void setModelColor(const QColor &modelColor);

    bool showModel() const;
    void setShowModel(bool showModel);

    QStringList lastOpenedProjects() const;

    int language() const;
    void setLanguage(int language);

signals:
    void settingsLoaded();

public slots:
    void clearRecentProjects();
    void setSettings(QSettings *settings);
    void restoreDefaultSettings();
    void readSettings();
    void writeSettings() const;

};

#endif // QVESSETTINGS_H
