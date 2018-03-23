#include "QVESChartSerie.h"
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>

QImage QVESChartSerie::getStarMarker() const
{
    QPainterPath starPath;
    starPath.moveTo(28, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(14 + 14 * qCos(0.8 * i * M_PI),
                        15 + 14 * qSin(0.8 * i * M_PI));
    }
    starPath.closeSubpath();

    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(mSeries->color());
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);

    int markerSize = (int)size();
    return star.scaled(markerSize, markerSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QImage QVESChartSerie::getTriangleMarker() const
{
    QPainterPath trianglePath;
    trianglePath.moveTo(4, 26);
    trianglePath.lineTo(26, 26);
    trianglePath.lineTo(15, 4);
    trianglePath.closeSubpath();

    QImage triangle(30, 30, QImage::Format_ARGB32);
    triangle.fill(Qt::transparent);

    QPainter painter(&triangle);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(mSeries->color());
    painter.setBrush(painter.pen().color());
    painter.drawPath(trianglePath);

    int markerSize = (int)size();
    return triangle.scaled(markerSize, markerSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QVESChartSerie::QVESChartSerie(QObject *parent) : QObject(parent)
{
}

QVESChartSerie::QVESChartSerie(const QString &name, const QVESChartSerie::SeriesType type, QObject *parent) : QObject(parent)
{
    mType = type;
    if (mType == SeriesType::Point){
        mSeries = new QScatterSeries(this);
    } else {
        mSeries = new QLineSeries(this);
    }

    mMapper = new QVXYModelMapper(this);

    mSeries->setName(name);

    mMapper->setXColumn(0);
    mMapper->setYColumn(1);
    mMapper->setSeries(mSeries);
}

QString QVESChartSerie::name() const
{
    return mSeries->name();
}

qreal QVESChartSerie::size() const
{
    if (mType == SeriesType::Point){
        return dynamic_cast<QScatterSeries*>(mSeries)->markerSize();
    } else {
        return dynamic_cast<QLineSeries*>(mSeries)->pen().widthF();
    }
}

QColor QVESChartSerie::color() const
{
    return mSeries->color();
}

QAbstractSeries *QVESChartSerie::series() const
{
    return mSeries;
}

bool QVESChartSerie::isVisible() const
{
    return mSeries->isVisible();
}

QString QVESChartSerie::markerType() const
{
    if (mType == SeriesType::Point){
        switch (mMarker) {
        case MarkerType::Circle:
            return tr("Círculo");
            break;
        case MarkerType::Square:
            return tr("Cuadrado");
            break;
        case MarkerType::Star:
            return tr("Estrella");
            break;
        case MarkerType::Triangle:
            return tr("Triángulo");
            break;
        default:
            return "";
            break;
        }
    }
}

void QVESChartSerie::setSize(qreal size)
{
    if (mType == SeriesType::Point){
        static_cast<QScatterSeries*>(mSeries)->setMarkerSize(size);
    } else {
        QPen newPen(mSeries->pen().color(), size);
        mSeries->setPen(newPen);
        //static_cast<QLineSeries*>(mSeries)->setPen(newPen);
        //static_cast<QLineSeries*>(mSeries)->pen().setWidthF(size);
    }
}

void QVESChartSerie::setColor(QColor color)
{
    mSeries->setColor(color);
}

void QVESChartSerie::setVisible(bool value)
{
    mSeries->setVisible(value);
}

void QVESChartSerie::setModel(QAbstractItemModel *model)
{
    mMapper->setModel(model);
}

void QVESChartSerie::setMarkerType(QVESChartSerie::MarkerType type)
{
    if (mType == SeriesType::Point){
        mMarker = type;
        switch (type) {
        case MarkerType::Circle:
            dynamic_cast<QScatterSeries*>(mSeries)->setMarkerShape(QScatterSeries::MarkerShapeCircle);
            break;
        case MarkerType::Square:
            dynamic_cast<QScatterSeries*>(mSeries)->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
            break;
        case MarkerType::Star:
            mSeries->setBrush(getStarMarker());
            //mSeries->setPen(QColor(Qt::transparent));
            break;
        case MarkerType::Triangle:
            mSeries->setBrush(getTriangleMarker());
            //mSeries->setPen(QColor(Qt::transparent));
            break;
        default:
            break;
        }
    }
}

void QVESChartSerie::removeBorderPen()
{
    QPen borderPen(QColor(Qt::transparent), 0.0);
    mSeries->setPen(borderPen);
    //static_cast<QScatterSeries*>(mSeries)->setPen(borderPen);
}
