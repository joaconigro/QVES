#include "MainChart.h"
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QVXYModelMapper>
#include <QLegend>

QT_CHARTS_USE_NAMESPACE

void MainChart::updateFieldSeries(TableModel *table)
{
    mFieldSeries->setName(tr("Datos de campo"));

    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(mFieldSeries);
    mapper->setModel(table);
    chart->addSeries(mFieldSeries);
}

void MainChart::updateSpliceSeries(TableModel *table)
{
    mSpliceSeries->setName(tr("Datos empalmados"));

    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(mSpliceSeries);
    mapper->setModel(table);
    chart->addSeries(mSpliceSeries);
}

void MainChart::updateCalculatedSeries(TableModel *table)
{
    mCalculatedSeries->setName(tr("Datos calculados"));

    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(mCalculatedSeries);
    mapper->setModel(table);
    chart->addSeries(mCalculatedSeries);
}

void MainChart::updateModeledSeries(TableModel *table)
{
    mModeledSeries->setName(tr("Datos modelados"));

    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(mModeledSeries);
    mapper->setModel(table);
    chart->addSeries(mModeledSeries);
}

void MainChart::configureXYAxis()
{
    //![3]
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
    //series->attachAxis(axisX);
    //seriesP->attachAxis(axisX);

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
    //series->attachAxis(axisY);
    //seriesP->attachAxis(axisY);
    //![3]
}

MainChart::MainChart(QWidget *parent) : QWidget(parent)
{
    mDelegate = new ChartDelegate(this);

    mFieldSeries = new QScatterSeries(this);
    mFieldSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    mFieldSeries->setMarkerSize(8.0);
    //mFieldSeries->setUseOpenGL(true);

    mSpliceSeries = new QScatterSeries(this);
    mSpliceSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    mSpliceSeries->setMarkerSize(8.0);
    //mSpliceSeries->setUseOpenGL(true);

    mCalculatedSeries = new QScatterSeries(this);
    mCalculatedSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    mCalculatedSeries->setMarkerSize(8.0);
    //mCalculatedSeries->setUseOpenGL(true);

    mModeledSeries = new QLineSeries(this);
    //mModeledSeries->setUseOpenGL(true);

    connect(mDelegate, &ChartDelegate::modelsChanged, this, &MainChart::modelDelegateChanged);

    chart = new QChart();
    chart->setAnimationOptions(QChart::AllAnimations);
}

void MainChart::chartDelegateChanged(ChartDelegate *del)
{
    mDelegate = del;
    modelDelegateChanged();
}

void MainChart::modelDelegateChanged()
{
    chart->series().clear();
    updateFieldSeries(mDelegate->fieldChartModel());
    updateSpliceSeries(mDelegate->spliceChartModel());
    updateCalculatedSeries(mDelegate->calculatedChartModel());
    updateModeledSeries(mDelegate->modeledChartModel());

    configureXYAxis();
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    chart->setTitle(mDelegate->vesName());
}
