#ifndef MAINCHART_H
#define MAINCHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include "QVESModelDelegate.h"
//#include "ChartDelegate.h"
#include "VES.h"
#include <QVXYModelMapper>

QT_CHARTS_USE_NAMESPACE

class MainChart : public QWidget
{
    Q_OBJECT
    QVESModelDelegate *mDelegate;
    QScatterSeries *mFieldSeries;
    QScatterSeries *mSpliceSeries;
    QScatterSeries *mCalculatedSeries;
    QLineSeries *mModeledSeries;
    QVXYModelMapper *mMapperField;
    QVXYModelMapper *mMapperSplice;
    QVXYModelMapper *mMapperCalculated;
    QVXYModelMapper *mMapperModeled;

    void createFieldSeries();
    void createSpliceSeries();
    void createCalculatedSeries();
    void createModeledSeries();

    void configureXYAxis();
public:

    QChart *chart;

    explicit MainChart(QWidget *parent = nullptr);

signals:

public slots:
   void chartDelegateChanged(QVESModelDelegate *del);
   void modelDelegateChanged();
};

#endif // MAINCHART_H
