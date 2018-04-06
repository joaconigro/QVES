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
#include "QVESSettings.h"

QT_CHARTS_USE_NAMESPACE

class MainChart : public QWidget
{
    Q_OBJECT
    QVESModelDelegate *mDelegate;
    QVESChartSerie *mFieldSeries;
    QVESChartSerie *mSpliceSeries;
    QVESChartSerie *mCalculatedSeries;
    QVESChartSerie *mModeledSeries;
    QVESChartSerie *mHighlightedPointSeries;
    QVESChartSerie *mHighlightedLineSeries;
    QLogValueAxis *axisX;
    QLogValueAxis *axisY;
    QChart::ChartTheme mTheme;

    void createFieldSeries();
    void createSpliceSeries();
    void createCalculatedSeries();
    void createModeledSeries();
    void createHighlightedSeries();

    void configureHighlightedSeries();
    void configureXYAxis();
public:

    QChart *chart;

    explicit MainChart(QVESModelDelegate *delegate, QWidget *parent = nullptr);

signals:

public slots:
   void setChartTitle();
   void setFieldVisible(const bool value);
   void setSpliceVisible(const bool value);
   void setCalculatedVisible(const bool value);
   void setModeledVisible(const bool value);
   void modelDelegateChanged();
   void loadQVESSettings(const QVESSettings* settings);
   void onSelectionChanged(const int dataType);
   void hideHighlightedSeries();
};

#endif // MAINCHART_H
