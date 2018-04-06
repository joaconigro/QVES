#include "MainChart.h"
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLegendMarker>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QVXYModelMapper>
#include <QLegend>
#include <QtMath>

QT_CHARTS_USE_NAMESPACE

void MainChart::createFieldSeries()
{
    mFieldSeries = new QVESChartSerie(tr("Datos de campo"), QVESChartSerie::SeriesType::Point, this);
    mFieldSeries->setSize(8.0);
    mFieldSeries->setMarkerType(QVESChartSerie::MarkerType::Circle);
    mFieldSeries->setModel(mDelegate->fieldModel());
    mFieldSeries->removeBorderPen();
}

void MainChart::createSpliceSeries()
{
    mSpliceSeries = new QVESChartSerie(tr("Datos empalmados"), QVESChartSerie::SeriesType::Point, this);
    mSpliceSeries->setSize(8.0);
    mSpliceSeries->setMarkerType(QVESChartSerie::MarkerType::Square);
    mSpliceSeries->setModel(mDelegate->spliceModel());
    mSpliceSeries->removeBorderPen();
}

void MainChart::createCalculatedSeries()
{
    mCalculatedSeries = new QVESChartSerie(tr("Datos calculados"), QVESChartSerie::SeriesType::Point, this);
    mCalculatedSeries->setSize(10.0);
    mCalculatedSeries->setMarkerType(QVESChartSerie::MarkerType::Triangle);
    mCalculatedSeries->setModel(mDelegate->calculatedModel());
    mCalculatedSeries->removeBorderPen();
}

void MainChart::createModeledSeries()
{
    mModeledSeries = new QVESChartSerie(tr("Datos modelados"), QVESChartSerie::SeriesType::Line, this);
    mModeledSeries->setSize(2.0);
    mModeledSeries->setModel(mDelegate->chartModeledModel());
}

void MainChart::createHighlightedSeries()
{
    mHighlightedPointSeries = new QVESChartSerie(tr("Selección"), QVESChartSerie::SeriesType::Point, this);
    mHighlightedPointSeries->setMarkerType(QVESChartSerie::MarkerType::Circle);
    mHighlightedPointSeries->removeBorderPen();

    mHighlightedLineSeries = new QVESChartSerie(tr("Selección"), QVESChartSerie::SeriesType::Line, this);

    hideHighlightedSeries();
}

void MainChart::configureHighlightedSeries()
{
    qreal maxPointSize = 0.0;
    maxPointSize = qMax(maxPointSize, mFieldSeries->size());
    maxPointSize = qMax(maxPointSize, mSpliceSeries->size());
    maxPointSize = qMax(maxPointSize, mCalculatedSeries->size());
    maxPointSize += 2.0;
    mHighlightedPointSeries->setSize(maxPointSize);

    mHighlightedLineSeries->setSize(mModeledSeries->size() + 2.0);
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
    chart->setAxisX(axisX, mHighlightedLineSeries->series());
    chart->setAxisX(axisX, mHighlightedPointSeries->series());
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
    chart->setAxisY(axisY, mHighlightedLineSeries->series());
    chart->setAxisY(axisY, mHighlightedPointSeries->series());
    axisY->setRange(mDelegate->chartMinY(), mDelegate->chartMaxY());
}

MainChart::MainChart(QVESModelDelegate *delegate, QWidget *parent) : QWidget(parent),
  mDelegate(delegate)
{
    chart = new QChart();
    axisX = new QLogValueAxis();
    axisY = new QLogValueAxis();

    createFieldSeries();
    chart->addSeries(mFieldSeries->series());

    createSpliceSeries();
    chart->addSeries(mSpliceSeries->series());

    createCalculatedSeries();
    chart->addSeries(mCalculatedSeries->series());

    createModeledSeries();
    chart->addSeries(mModeledSeries->series());

    createHighlightedSeries();
    chart->addSeries(mHighlightedLineSeries->series());
    chart->addSeries(mHighlightedPointSeries->series());



    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    chart->legend()->markers(mHighlightedLineSeries->series()).first()->setVisible(false);
    chart->legend()->markers(mHighlightedPointSeries->series()).first()->setVisible(false);
}

void MainChart::setChartTitle()
{
    chart->setTitle(mDelegate->currentVES()->name());
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

void MainChart::modelDelegateChanged()
{
    chart->series().clear();
    mFieldSeries->setModel(mDelegate->fieldModel());
    mSpliceSeries->setModel(mDelegate->spliceModel());
    mCalculatedSeries->setModel(mDelegate->calculatedModel());
    mModeledSeries->setModel(mDelegate->chartModeledModel());
    hideHighlightedSeries();

    configureXYAxis();
    chart->setTitle(mDelegate->currentVES()->name());
}

void MainChart::loadQVESSettings(const QVESSettings *settings)
{
    mTheme = static_cast<QChart::ChartTheme>(settings->chartTheme());
    chart->setTheme(mTheme);
    chart->setAnimationOptions(static_cast<QChart::AnimationOption>(settings->chartAnimation()));

    QBrush brush(Qt::gray);
    QPen minorGridPen(brush, 0.2, Qt::DashLine);
    axisX->setMinorGridLinePen(minorGridPen);
    axisY->setMinorGridLinePen(minorGridPen);


    mFieldSeries->setColor(settings->fieldColor());
    mFieldSeries->setSize(settings->fieldPointSize());
    mFieldSeries->setMarkerType(static_cast<QVESChartSerie::MarkerType>(settings->fieldMarkerType()));
    mFieldSeries->removeBorderPen();

    mSpliceSeries->setColor(settings->spliceColor());
    mSpliceSeries->setSize(settings->splicePointSize());
    mSpliceSeries->setMarkerType(static_cast<QVESChartSerie::MarkerType>(settings->spliceMarkerType()));
    mSpliceSeries->removeBorderPen();

    mCalculatedSeries->setColor(settings->calculatedColor());
    mCalculatedSeries->setSize(settings->calculatedPointSize());
    mCalculatedSeries->setMarkerType(static_cast<QVESChartSerie::MarkerType>(settings->calculatedMarkerType()));
    mCalculatedSeries->removeBorderPen();

    mModeledSeries->setColor(settings->modelColor());
    mModeledSeries->setSize(settings->modelLineWidth());

    mHighlightedLineSeries->setColor(settings->highlightColor());
    mHighlightedPointSeries->setColor(settings->highlightColor());
    configureHighlightedSeries();
}

void MainChart::onSelectionChanged(const int dataType)
{
    hideHighlightedSeries();
    if (dataType == 3) {
        mHighlightedLineSeries->setVisible(true);
        mHighlightedLineSeries->setModel(mDelegate->selectionModel());
    } else {
        mHighlightedPointSeries->setVisible(true);
        mHighlightedPointSeries->setModel(mDelegate->selectionModel());
    }
    chart->legend()->markers(mHighlightedLineSeries->series()).first()->setVisible(false);
    chart->legend()->markers(mHighlightedPointSeries->series()).first()->setVisible(false);
}

void MainChart::hideHighlightedSeries()
{
    mHighlightedLineSeries->setVisible(false);
    mHighlightedPointSeries->setVisible(false);
}


