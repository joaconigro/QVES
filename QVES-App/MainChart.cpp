#include "MainChart.h"
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QVXYModelMapper>
#include <QLegend>

QT_CHARTS_USE_NAMESPACE

void MainChart::createFieldSeries()
{
    mFieldSeries->setName(tr("Datos de campo"));
    mFieldSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    mFieldSeries->setMarkerSize(8.0);

    mMapperField->setXColumn(0);
    mMapperField->setYColumn(1);
    mMapperField->setSeries(mFieldSeries);
    mMapperField->setModel(mDelegate->fieldChartModel());
}

void MainChart::createSpliceSeries()
{
    mSpliceSeries->setName(tr("Datos empalmados"));
    mSpliceSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    mSpliceSeries->setMarkerSize(8.0);

    mMapperSplice->setXColumn(0);
    mMapperSplice->setYColumn(1);
    mMapperSplice->setSeries(mSpliceSeries);
    mMapperSplice->setModel(mDelegate->spliceChartModel());
}

void MainChart::createCalculatedSeries()
{
    mCalculatedSeries->setName(tr("Datos calculados"));
    mCalculatedSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    mCalculatedSeries->setMarkerSize(8.0);

    mMapperCalculated->setXColumn(0);
    mMapperCalculated->setYColumn(1);
    mMapperCalculated->setSeries(mCalculatedSeries);
    mMapperCalculated->setModel(mDelegate->calculatedChartModel());
}

void MainChart::createModeledSeries()
{
    mModeledSeries->setName(tr("Datos modelados"));

    mMapperModeled->setXColumn(0);
    mMapperModeled->setYColumn(1);
    mMapperModeled->setSeries(mModeledSeries);
    mMapperModeled->setModel(mDelegate->modeledChartModel());
}

void MainChart::configureXYAxis()
{
    QLogValueAxis *axisX = new QLogValueAxis();
    axisX->setTitleText(tr("Distancia AB/2 (m)"));
    axisX->setLabelFormat("%g");
    axisX->setBase(10.0);
    axisX->setMinorTickCount(-1);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->setAxisX(axisX, mFieldSeries);
    chart->setAxisX(axisX, mSpliceSeries);
    chart->setAxisX(axisX, mCalculatedSeries);
    chart->setAxisX(axisX, mModeledSeries);
    axisX->setRange(mDelegate->chartMinX(), mDelegate->chartMaxX());

    QLogValueAxis *axisY = new QLogValueAxis();
    axisY->setTitleText(tr("Resistividad"));
    axisY->setLabelFormat("%g");
    axisY->setBase(10.0);
    axisY->setMinorTickCount(-1);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setAxisY(axisY, mFieldSeries);
    chart->setAxisY(axisY, mSpliceSeries);
    chart->setAxisY(axisY, mCalculatedSeries);
    chart->setAxisY(axisY, mModeledSeries);
    axisY->setRange(mDelegate->chartMinY(), mDelegate->chartMaxY());
}

MainChart::MainChart(QWidget *parent) : QWidget(parent)
{
    chart = new QChart();

    mDelegate = new ChartDelegate(this);

    mFieldSeries = new QScatterSeries(this);
    mMapperField = new QVXYModelMapper(this);
    createFieldSeries();
    chart->addSeries(mFieldSeries);

    mSpliceSeries = new QScatterSeries(this);
    mMapperSplice = new QVXYModelMapper(this);
    createSpliceSeries();
    chart->addSeries(mSpliceSeries);

    mCalculatedSeries = new QScatterSeries(this);
    mMapperCalculated = new QVXYModelMapper(this);
    createCalculatedSeries();
    chart->addSeries(mCalculatedSeries);

    mModeledSeries = new QLineSeries(this);
    mMapperModeled = new QVXYModelMapper(this);
    createModeledSeries();
    chart->addSeries(mModeledSeries);

    connect(mDelegate, &ChartDelegate::modelsChanged, this, &MainChart::modelDelegateChanged);

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
}

void MainChart::chartDelegateChanged(ChartDelegate *del)
{
    mDelegate = del;
    modelDelegateChanged();
}

void MainChart::modelDelegateChanged()
{
    chart->series().clear();
    createFieldSeries();
    createSpliceSeries();
    createCalculatedSeries();
    createModeledSeries();

    configureXYAxis();
    chart->setTitle(mDelegate->vesName());
}
