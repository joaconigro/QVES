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
    int mVFSANumberOfParameters;
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

signals:

public slots:
    void setSettings(QSettings *settings);
    void restoreDefaultSettings();
    void readSettings();
    void writeSettings() const;

};

#endif // QVESSETTINGS_H
