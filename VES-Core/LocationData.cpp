#include "LocationData.h"
#include <QStringList>
#include <QtMath>

double LocationData::gmsToDecimal(const QString &value)
{
    QString resultValue;
    QChar signChar;
    QString decimalChar = mQLoc->decimalPoint();
    resultValue.clear();

    //Make a clean QString to convert to number.
    foreach (QChar c, value) {
        if (c.isDigit()){
            resultValue.append(c);
        } else if (c == '.' || c == ',') {
            if (decimalChar == "."){
                resultValue.append(decimalChar);
            } else if (decimalChar == ","){
                resultValue.append(decimalChar);
            }
        } else if (c == 'S' || c == 's' || c == 'W' || c == 'w' || c == 'O' || c == 'o') {
            signChar = '-';
        } else if (c == 'N' || c == 'n' || c == 'E' || c == 'e') {
            signChar = ' ';
        } else {
            resultValue.append(' ');
        }
    }

    //Make a list from previous generated QString.
    QStringList tempList = resultValue.split(' ', Qt::SkipEmptyParts);
    double result = 0.0;

    //Calculate degrees, minutes and seconds.
    for (int i = 0; i < tempList.length(); i++){
        QString tempNumber = tempList.at(i);
        tempNumber = tempNumber.replace('.', decimalChar);
        tempNumber = tempNumber.replace(',', decimalChar);
        result = result + mQLoc->toDouble(tempNumber) / pow(60.0, i);
    }

    //Sign for degrees.
    if (signChar == '-'){
        result = result * (-1.0);
    }

    return result;
}

QString LocationData::decimalToGms(const double value, bool isLatitude)
{
    //Break apart in degrees, minutes y seconds.
    int degrees = trunc(value);
    double minutesWithDecimal = abs(value - degrees) * 60.0;
    int minutes = trunc(minutesWithDecimal);
    double seconds = (minutesWithDecimal - minutes) * 60.0;

    //Check for hemisphere
    QChar letter;
    if (isLatitude) {
        if (degrees >= 0){
            letter = 'N';
        } else {
            letter = 'S';
        }
    } else {
        if (degrees >= 0){
            letter = 'E';
        } else {
            letter = 'W';
        }
    }

    //Make a QString
    QString result = mQLoc->toString(abs(degrees)) + "º " +
            mQLoc->toString(minutes) + "\' " +
            mQLoc->toString(seconds, 'f', 3) + "\'' " + letter;

    return result;
}

void LocationData::geographicToTransverseMercator()
{
    double phi, lambda;
    double phi_0  = 0.0;
    double T, A, C, M, M_0, v;
    double lambda_0, a, ecc, ecc_pri, FN, k, FE;

    //Set conversion parameters
    lambda_0 = (mUtmZone * 6.0 - 183.0) * M_PI / 180.0;
    a = 6378137.0;
    ecc = 0.081819190843;
    ecc_pri = pow(0.082094437950, 2.0);
    switch (mHemisphere) {
    case LocationData::HemisphereType::North:
        FN = 0.0;
        break;
    default:
        FN= 10000000.0;
        break;
    }
    k = 0.9996;
    FE = 500000.0;


    //Convert coordinates
    M_0 = a * ((1.0 - (pow(ecc, 2.0)) / 4.0 - (3.0 / 64.0) * pow(ecc, 4.0) - (5.0 / 256.0) * pow(ecc, 6.0)) * phi_0 - ((3.0 / 8.0) * pow(ecc, 2.0) + (3.0 / 32.0) * pow(ecc, 4.0) + (45.0 / 1024.0) * pow(ecc, 6.0)) * sin(2.0 * phi_0) + ((15.0 / 256.0) * pow(ecc, 4.0) + (45.0 / 1024.0) * pow(ecc, 6.0)) * sin(4.0 * phi_0) - ((35.0 / 3072.0) * pow(ecc, 6.0)) * sin(6.0 * phi_0));
    phi = mDecimalLatitude * M_PI / 180.0;
    lambda = mDecimalLongitude * M_PI / 180.0;
    T = pow((tan(phi)), 2.0);
    C = (pow(ecc, 2.0) * pow((cos(phi)), 2.0)) / (1.0 - pow(ecc, 2.0));
    A = (lambda - lambda_0) * cos(phi);
    v = a / sqrt(1.0 - pow(ecc, 2.0) * pow((sin(phi)), 2.0));
    M = a * ((1.0 - (pow(ecc, 2.0)) / 4.0 - (3.0 / 64.0) * pow(ecc, 4.0) - (5.0 / 256.0) * pow(ecc, 6.0)) * phi - ((3.0 / 8.0) * pow(ecc, 2.0) + (3.0 / 32.0) * pow(ecc, 4.0) + (45.0 / 1024.0) * pow(ecc, 6.0)) * sin(2.0 * phi) + ((15.0 / 256.0) * pow(ecc, 4.0) + (45.0 / 1024.0) * pow(ecc, 6.0)) * sin(4.0 * phi) - ((35.0 / 3072.0) * pow(ecc, 6.0)) * sin(6.0 * phi));
    mUtmX = FE + k * v * (A + (1.0 - T + C) * pow(A, 3.0) / 6.0 + (5.0 - 18.0 * T + pow(T, 2.0) + 72.0 * C - 58.0 * pow(ecc_pri, 2.0)) * pow(A, 5.0) / 120.0);
    mUtmY = FN + k * (M - M_0 + v * tan(phi) * (pow(A, 2.0) / 2.0 + (5.0 - T + 9.0 * C + 4.0 * pow(C, 2.0)) * pow(A, 4.0) / 24.0 + (61.0 - 58.0 * T + pow(T, 2.0) + 600.0 * C - 330.0 * pow(ecc_pri, 2.0)) * pow(A, 6.0) / 720.0));

}

void LocationData::transverseMercatorToGeographic()
{
    double phi, lambda;
    double phi_0  = 0.0;
    double T_1, mu_1, e_1, phi_1, rho, D, C_1, M_1, M_0, v_1;
    double lambda_0, a, ecc, ecc_pri, FN, k, FE;

    //Set conversion parameters
    lambda_0 = (mUtmZone * 6.0 - 183.0) * M_PI / 180.0;
    a = 6378137.0;
    ecc = 0.081819190843;
    ecc_pri = pow(0.082094437950, 2.0);
    switch (mHemisphere) {
    case LocationData::HemisphereType::North:
        FN = 0.0;
        break;
    default:
        FN= 10000000.0;
        break;
    }
    k = 0.9996;
    FE = 500000.0;


    //Convert coordinates
    M_0 = a * ((1.0 - (pow(ecc, 2.0)) / 4.0 - (3.0 / 64.0) * pow(ecc, 4.0) - (5.0 / 256.0) * pow(ecc, 6.0)) * phi_0 - ((3.0 / 8.0) * pow(ecc, 2.0) + (3.0 / 32.0) * pow(ecc, 4.0) + (45.0 / 1024.0) * pow(ecc, 6.0)) * sin(2.0 * phi_0) + ((15.0 / 256.0) * pow(ecc, 4.0) + (45.0 / 1024.0) * pow(ecc, 6.0)) * sin(4.0 * phi_0) - ((35.0 / 3072.0) * pow(ecc, 6.0)) * sin(6.0 * phi_0));
    e_1 = (1.0 - sqrt(1.0 - pow(ecc, 2.0))) / (1.0 + sqrt(1.0 - pow(ecc, 2.0)));
    M_1 = M_0 + (mUtmY - FN) / k;
    mu_1 = M_1 / (a * (1.0 - pow(ecc, 2.0) / 4.0 - (3.0 / 64.0) * pow(ecc, 4.0) - (5.0 / 256.0) * pow(ecc, 6.0)));
    phi_1 = mu_1 + ((3.0 / 2.0) * e_1 - (27.0 / 32.0) * pow(e_1, 3.0)) * sin(2.0 * mu_1) + ((21.0 / 16.0) * pow(e_1, 2.0) - (55.0 / 32.0) * pow(e_1, 4.0)) * sin(4.0 * mu_1) + (151.0 / 96.0) * pow(e_1, 3.0) * sin(6.0 * mu_1) + (1097.0 / 512.0) * pow(e_1, 4.0) * sin(8.0 * mu_1);
    T_1 = pow((tan(phi_1)), 2.0);
    C_1 = ecc_pri * pow((cos(phi_1)), 2.0);
    v_1 = a / sqrt(1.0 - pow(ecc, 2.0) * pow((sin(phi_1)), 2.0));
    rho = a * (1.0 - pow(ecc, 2.0)) / pow((1.0 - pow(ecc, 2.0) * pow((sin(phi_1)), 2.0)), 1.5);
    D = (mUtmX - FE) / (v_1 * k);
    phi = phi_1 - (v_1 * tan(phi_1) / rho) * (pow(D, 2.0) / 2.0 - (5.0 + 3.0 * T_1 + 10.0 * C_1 - 4.0 * pow(C_1, 2.0) - 9.0 * ecc_pri) * pow(D, 4.0) / 24.0 + (61.0 + 90.0 * T_1 + 298.0 * C_1 + 45.0 * pow(T_1, 2.0) - 252.0 * ecc_pri - 3.0 * pow(C_1, 2.0)) * pow(D, 6.0) / 720.0);
    lambda = lambda_0 + (D - (1.0 + 2.0 * T_1 + C_1) * pow(D, 3.0) / 6.0 + (5.0 - 2.0 * C_1 + 28.0 * T_1 - 3.0 * pow(C_1, 2.0) + 8.0 * ecc_pri + 24.0 * pow(T_1, 2.0)) * pow(D, 5.0) / 120.0) / cos(phi_1);

    mDecimalLatitude = phi * 180.0 / M_PI;
    mDecimalLongitude = lambda * 180.0 / M_PI;
}

LocationData::LocationData(QObject *parent) : QObject(parent)
{
    mDecimalLatitude = mDecimalLongitude = mUtmX = mUtmY = mLocalX = mLocalY = mZ = 0.0;
    mUtmZone = 0;
    mHemisphere = LocationData::HemisphereType::South;
    mOnlyLocals = true;
    mGmsLatitude.clear();
    mGmsLongitude.clear();
    mQLoc = new QLocale();
}

LocationData::LocationData(const QString &lat, const QString &lng, const double z, QObject *parent) : QObject(parent)
{
    mGmsLatitude = lat;
    mGmsLongitude = lng;
    mZ = z;

    //Convert lat-lng string to decimal values
    mDecimalLatitude = gmsToDecimal(mGmsLatitude);
    mDecimalLongitude = gmsToDecimal(mGmsLongitude);

    //Convert decimal lat-lng to UTM
    if (mDecimalLatitude < 0.0)
        mHemisphere = LocationData::HemisphereType::South;
    else
        mHemisphere = LocationData::HemisphereType::North;
    mUtmZone = trunc(mDecimalLongitude / 6.0 + 31.0);
    geographicToTransverseMercator();
    mOnlyLocals = false;

    mQLoc = new QLocale();
}

LocationData::LocationData(const double yOrlLat, const double xOrLng, const LocationData::CoordinateType cType, const double z, QObject *parent) : QObject(parent)
{
    switch (cType) {
    case LocationData::CoordinateType::DecimalDegrees:
        mDecimalLatitude = yOrlLat;
        mDecimalLongitude = xOrLng;
        mZ = z;

        //Convert decimal lat-lng to UTM
        if (mDecimalLatitude < 0.0)
            mHemisphere = LocationData::HemisphereType::South;
        else
            mHemisphere = LocationData::HemisphereType::North;
        mUtmZone = trunc(mDecimalLongitude / 6.0 + 31.0);
        geographicToTransverseMercator();

        //Convert decimal lat-lng to strings
        mGmsLatitude = decimalToGms(mDecimalLatitude, true);
        mGmsLongitude = decimalToGms(mDecimalLongitude, false);
        mOnlyLocals = false;
        break;

    case LocationData::CoordinateType::Local:
        mLocalY = yOrlLat;
        mLocalX = xOrLng;
        mZ = z;
        mOnlyLocals = true;
        break;
    }

    mQLoc = new QLocale();
}

LocationData::LocationData(const double x, const double y, const int zone, const LocationData::HemisphereType hem, const double z, QObject *parent) : QObject(parent)
{
    mUtmX = x;
    mUtmY = y;
    mUtmZone = zone;
    mHemisphere = hem;
    mZ = z;

    //Convert UTM to decimal lat-lng
    transverseMercatorToGeographic();

    //Convert decimal lat-lng to strings
    mGmsLatitude = decimalToGms(mDecimalLatitude, true);
    mGmsLongitude = decimalToGms(mDecimalLongitude, false);
    mOnlyLocals = false;

    mQLoc = new QLocale();
}

LocationData::LocationData(const LocationData &ld)
{
    mGmsLatitude = ld.gmsLatitude();
    mGmsLongitude = ld.gmsLongitude();
    mDecimalLatitude = ld.decimalLatitude();
    mDecimalLongitude = ld.decimalLongitude();
    mUtmX = ld.utmX();
    mUtmY = ld.utmY();
    mUtmZone = ld.utmZone();
    mLocalX = ld.localX();
    mLocalY = ld.localY();
    mZ = ld.z();
    mHemisphere = ld.Hemisphere();
    mOnlyLocals = ld.onlyLocals();
    this->setParent(ld.parent());
}

LocationData &LocationData::operator =(const LocationData &rhs)
{
    mGmsLatitude = rhs.gmsLatitude();
    mGmsLongitude = rhs.gmsLongitude();
    mDecimalLatitude = rhs.decimalLatitude();
    mDecimalLongitude = rhs.decimalLongitude();
    mUtmX = rhs.utmX();
    mUtmY = rhs.utmY();
    mUtmZone = rhs.utmZone();
    mLocalX = rhs.localX();
    mLocalY = rhs.localY();
    mZ = rhs.z();
    mHemisphere = rhs.Hemisphere();
    mOnlyLocals = rhs.onlyLocals();
    this->setParent(rhs.parent());
    return *this;
}

QString LocationData::gmsLatitude() const
{
    return mGmsLatitude;
}

QString LocationData::gmsLongitude() const
{
    return mGmsLongitude;
}

double LocationData::decimalLatitude() const
{
    return mDecimalLatitude;
}

double LocationData::decimalLongitude() const
{
    return mDecimalLongitude;
}

double LocationData::utmX() const
{
    return mUtmX;
}

double LocationData::utmY() const
{
    return mUtmY;
}

int LocationData::utmZone() const
{
    return mUtmZone;
}

double LocationData::localX() const
{
    return mLocalX;
}

double LocationData::localY() const
{
    return mLocalY;
}

double LocationData::z() const
{
    return mZ;
}

bool LocationData::onlyLocals() const
{
    return mOnlyLocals;
}

LocationData::HemisphereType LocationData::Hemisphere() const
{
    return mHemisphere;
}

void LocationData::setGmsLatitude(const QString &value)
{
    mGmsLatitude = value;
}

void LocationData::setGmsLongitude(const QString &value)
{
    mGmsLongitude = value;
}

void LocationData::setDecimalLatitude(const double value)
{
    mDecimalLatitude = value;
}

void LocationData::setDecimalLongitude(const double value)
{
    mDecimalLongitude = value;
}

void LocationData::setUtmX(const double value)
{
    mUtmX = value;
}

void LocationData::setUtmY(const double value)
{
    mUtmY = value;
}

void LocationData::setUtmZone(const int value)
{
    mUtmZone = value;
}

void LocationData::setLocalX(const double value)
{
    mLocalX = value;
}

void LocationData::setLocalY(const double value)
{
    mLocalY = value;
}

void LocationData::setZ(const double value)
{
    mZ = value;
}

void LocationData::setHemisphere(const LocationData::HemisphereType value)
{
    mHemisphere = value;
}

bool LocationData::isEmpty() const
{
    return mDecimalLatitude == 0.0 && mDecimalLongitude == 0.0 && mUtmX == 0.0 && mUtmY == 0.0
            && mZ == 0.0 && mLocalX == 0.0 && mLocalY == 0.0 && mGmsLatitude.isEmpty() && mGmsLongitude.isEmpty();
}

QVariant LocationData::toVariant() const
{
    QVariantMap map;
    map.insert("DecimalLatitude", mDecimalLatitude);
    map.insert("DecimalLongitude", mDecimalLongitude);
    map.insert("GmsLatitude", mGmsLatitude);
    map.insert("GmsLongitude", mGmsLongitude);
    map.insert("UtmX", mUtmX);
    map.insert("UtmY", mUtmY);
    map.insert("UtmZone", mUtmZone);
    map.insert("LocalX", mLocalX);
    map.insert("LocalY", mLocalY);
    map.insert("Z", mZ);
    map.insert("Hemisphere", static_cast<int>(mHemisphere));
    map.insert("OnlyLocals", mOnlyLocals);
    return map;
}

void LocationData::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mGmsLatitude = map.value("GmsLatitude").toString();
    mGmsLongitude = map.value("GmsLongitude").toString();
    mDecimalLatitude = map.value("DecimalLatitude").toDouble();
    mDecimalLongitude = map.value("DecimalLongitude").toDouble();
    mUtmX = map.value("UtmX").toDouble();
    mUtmY = map.value("UtmY").toDouble();
    mUtmZone = map.value("UtmZone").toInt();
    mLocalX = map.value("LocalX").toDouble();
    mLocalY = map.value("LocalY").toDouble();
    mZ = map.value("Z").toDouble();
    mOnlyLocals = map.value("OnlyLocals").toBool();
    mHemisphere = static_cast<HemisphereType>(map.value("Hemisphere").toInt());
}
