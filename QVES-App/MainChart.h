#ifndef MAINCHART_H
#define MAINCHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include "QVESModelDelegate.h"
#include "QVESChartSerie.h"
#include "VES.h"
#include <QVXYModelMapper>

QT_CHARTS_USE_NAMESPACE

class MainChart : public QWidget
{
    Q_OBJECT
    QVESModelDelegate *mDelegate;
    QVESChartSerie *mFieldSeries;
    QVESChartSerie *mSpliceSeries;
    QVESChartSerie *mCalculatedSeries;
    QVESChartSerie *mModeledSeries;
    QLogValueAxis *axisX;
    QLogValueAxis *axisY;

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
   void setFieldVisible(const bool value);
   void setSpliceVisible(const bool value);
   void setCalculatedVisible(const bool value);
   void setModeledVisible(const bool value);
   void chartDelegateChanged(QVESModelDelegate *del);
   void modelDelegateChanged();
};

#endif // MAINCHART_H
