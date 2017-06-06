#ifndef LOCATIONDATA_H
#define LOCATIONDATA_H

#include "ves-core_global.h"
#include <QObject>
#include <QString>
#include <QLocale>

class VESCORESHARED_EXPORT LocationData : public QObject
{
    Q_OBJECT

public:
    enum class CoordinateType{GMSDegrees, DecimalDegrees, UTM, Local};
    enum class Hemisphere{North, South};

private:
    QString mGmsLatitude;
    QString mGmsLongitude;
    double mDecimalLatitude;
    double mDecimalLongitude;
    double mUtmX;
    double mUtmY;
    int mUtmZone;
    double mLocalX;
    double mLocalY;
    double mZ;
    QLocale mQLoc;
    LocationData::Hemisphere mHem;
    bool mOnlyLocals;

    double gmsToDecimal(const QString &value);
    QString decimalToGms(const double value, bool isLatitude);
    void geographicToTransverseMercator();
    void transverseMercatorToGeographic();
    void convertCoordinate();

public:
    explicit LocationData(QObject *parent = nullptr);
    explicit LocationData(const QString &lat, const QString &lng, const double z = 0.0, QObject *parent = nullptr);
    explicit LocationData(const double yOrlLat, const double xOrLng, const CoordinateType cType, const double z = 0.0, QObject *parent = nullptr);
    explicit LocationData(const double x, const double y, const int zone, const Hemisphere hem, const double z = 0.0, QObject *parent = nullptr);

    //Getters
    QString gmsLatitude() const;
    QString gmsLongitude() const;
    double decimalLatitude() const;
    double decimalLongitude() const;
    double utmX() const;
    double utmY() const;
    int utmZone() const;
    double localX() const;
    double localY() const;
    double z() const;
    bool onlyLocals() const;
    
    //Setters
    void setGmsLatitude(const QString &value);
    void setGmsLongitude(const QString &value);
    void setDecimalLatitude(const double value);
    void setDecimalLongitude(const double value);
    void setUtmX(const double value);
    void setUtmY(const double value);
    void setUtmZone(const int value);
    void setLocalX(const double value);
    void setLocalY(const double value);
    void setZ(const double value);

    bool isEmpty() const;

signals:

public slots:
};

#endif // LOCATIONDATA_H
