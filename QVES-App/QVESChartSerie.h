#ifndef QVESCHARTSERIE_H
#define QVESCHARTSERIE_H

#include <QObject>
#include <QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
//#include "QVESModelDelegate.h"
#include <QVXYModelMapper>

class QVESChartSerie : public QObject
{
public:
    enum class SeriesType{Point, Line};
    enum class MarkerType{Circle, Square, Star, Triangle};

private:
    Q_OBJECT

    SeriesType mType;
    MarkerType mMarker;
    QXYSeries *mSeries;
    QVXYModelMapper *mMapper;

    QImage getStarMarker() const;
    QImage getTriangleMarker() const;

public:
    explicit QVESChartSerie(QObject *parent = nullptr);
    explicit QVESChartSerie(const QString& name, const SeriesType type, QObject *parent = nullptr);


    //Getters
    QString name() const;
    qreal size() const;
    QColor color() const;
    QAbstractSeries* series() const;
    bool isVisible() const;
    QString markerType() const;


    //Setters
    void setSize(qreal size);
    void setColor(QColor color);
    void setVisible(bool value);
    void setModel(QAbstractItemModel* model);
    void setMarkerType(MarkerType type);
    void removeBorderPen();

signals:

public slots:
};

#endif // QVESCHARTSERIE_H
