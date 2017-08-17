#ifndef MAINCHART_H
#define MAINCHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include "ChartDelegate.h"
#include "VES.h"

QT_CHARTS_USE_NAMESPACE

class MainChart : public QWidget
{
    Q_OBJECT
    ChartDelegate *mDelegate;
    QScatterSeries *mFieldSeries;
    QScatterSeries *mSpliceSeries;
    QScatterSeries *mCalculatedSeries;
    QLineSeries *mModeledSeries;

    void updateFieldSeries(TableModel *table);
    void updateSpliceSeries(TableModel *table);
    void updateCalculatedSeries(TableModel *table);
    void updateModeledSeries(TableModel *table);

    void configureXYAxis();
public:

    QChart *chart;

    explicit MainChart(QWidget *parent = nullptr);

signals:

public slots:
   void chartDelegateChanged(ChartDelegate *del);
   void modelDelegateChanged();
};

#endif // MAINCHART_H
