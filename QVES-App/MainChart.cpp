#include "MainChart.h"
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QVXYModelMapper>
#include <QLegend>

QT_CHARTS_USE_NAMESPACE

void MainChart::createFieldSeries()
{
    mFieldSeries = new QVESChartSerie(tr("Datos de campo"), QVESChartSerie::SeriesType::Point, this);
    mFieldSeries->setSize(8.0);
    mFieldSeries->setMarkerType(QVESChartSerie::MarkerType::Circle);
    mFieldSeries->setModel(mDelegate->fieldModel());
}

void MainChart::createSpliceSeries()
{
    mSpliceSeries = new QVESChartSerie(tr("Datos empalmados"), QVESChartSerie::SeriesType::Point, this);
    mSpliceSeries->setSize(8.0);
    mSpliceSeries->setMarkerType(QVESChartSerie::MarkerType::Square);
    mSpliceSeries->setModel(mDelegate->spliceModel());
}

void MainChart::createCalculatedSeries()
{
    mCalculatedSeries = new QVESChartSerie(tr("Datos calculados"), QVESChartSerie::SeriesType::Point, this);
    mCalculatedSeries->setSize(10.0);
    mCalculatedSeries->setMarkerType(QVESChartSerie::MarkerType::Triangle);
    mCalculatedSeries->setModel(mDelegate->calculatedModel());
}

void MainChart::createModeledSeries()
{
    mModeledSeries = new QVESChartSerie(tr("Datos modelados"), QVESChartSerie::SeriesType::Line, this);
    mModeledSeries->setSize(2.0);
    mModeledSeries->setModel(mDelegate->chartModeledModel());
}

void MainChart::configureXYAxis()
{
    axisX = new QLogValueAxis();
    if(mModeledSeries->isVisible()){
        axisX->setTitleText(tr("Distancia AB/2 - Profundidad (m)"));
    } else {
        axisX->setTitleText(tr("Distancia AB/2 (m)"));
    }
    QBrush brush(Qt::gray);
    QPen minorGridPen(brush, 0.2, Qt::DashLine);

    axisX->setLabelFormat("%g");
    axisX->setBase(10.0);
    axisX->setMinorTickCount(-1);
    axisX->setMinorGridLinePen(minorGridPen);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->setAxisX(axisX, mFieldSeries->series());
    chart->setAxisX(axisX, mSpliceSeries->series());
    chart->setAxisX(axisX, mCalculatedSeries->series());
    chart->setAxisX(axisX, mModeledSeries->series());
    axisX->setRange(mDelegate->chartMinX(), mDelegate->chartMaxX());

    axisY = new QLogValueAxis();
    axisY->setTitleText(tr("Resistividad (Ohm.m)"));
    axisY->setLabelFormat("%g");
    axisY->setBase(10.0);
    axisY->setMinorTickCount(-1);
    axisY->setMinorGridLinePen(minorGridPen);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setAxisY(axisY, mFieldSeries->series());
    chart->setAxisY(axisY, mSpliceSeries->series());
    chart->setAxisY(axisY, mCalculatedSeries->series());
    chart->setAxisY(axisY, mModeledSeries->series());
    axisY->setRange(mDelegate->chartMinY(), mDelegate->chartMaxY());
}

MainChart::MainChart(QWidget *parent) : QWidget(parent)
{
    chart = new QChart();
    axisX = new QLogValueAxis();
    axisY = new QLogValueAxis();

    mDelegate = new QVESModelDelegate(this);

    createFieldSeries();
    chart->addSeries(mFieldSeries->series());

    createSpliceSeries();
    chart->addSeries(mSpliceSeries->series());

    createCalculatedSeries();
    chart->addSeries(mCalculatedSeries->series());

    createModeledSeries();
    chart->addSeries(mModeledSeries->series());

    connect(mDelegate, &QVESModelDelegate::tableModelChanged, this, &MainChart::modelDelegateChanged);

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
}

void MainChart::setFieldVisible(const bool value)
{
    mFieldSeries->setVisible(value);
}

void MainChart::setSpliceVisible(const bool value)
{
    mSpliceSeries->setVisible(value);
}

void MainChart::setCalculatedVisible(const bool value)
{
    mCalculatedSeries->setVisible(value);
}

void MainChart::setModeledVisible(const bool value)
{
    mModeledSeries->setVisible(value);
    if(mModeledSeries->isVisible()){
        axisX->setTitleText(tr("Distancia AB/2 - Profundidad (m)"));
    } else {
        axisX->setTitleText(tr("Distancia AB/2 (m)"));
    }
}

void MainChart::chartDelegateChanged(QVESModelDelegate *del)
{
    mDelegate = del;
    modelDelegateChanged();
}

void MainChart::modelDelegateChanged()
{
    chart->series().clear();
    mFieldSeries->setModel(mDelegate->fieldModel());
    mSpliceSeries->setModel(mDelegate->spliceModel());
    mCalculatedSeries->setModel(mDelegate->calculatedModel());
    mModeledSeries->setModel(mDelegate->chartModeledModel());

    configureXYAxis();
    chart->setTitle(mDelegate->vesName());
}

void MainChart::loadQVESSettings(const QVESSettings *settings)
{
    mTheme = static_cast<QChart::ChartTheme>(settings->chartTheme());
    chart->setTheme(mTheme);
}


