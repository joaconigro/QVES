#include "MainChart.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

QT_CHARTS_USE_NAMESPACE

MainChart::MainChart(QWidget *parent) : QWidget(parent)
{
    //![1]

        QLineSeries *series = new QLineSeries();
        *series << QPointF(1.0, 1.0) << QPointF(2.0, 73.0) << QPointF(2.0, 268.0) << QPointF(4.0, 268.0)
                << QPointF(4.0, 10.0) << QPointF(6.0, 723.0);
        QScatterSeries *seriesP = new QScatterSeries();
        *seriesP << QPointF(1.0, 1.0) << QPointF(20.0, 73.0) << QPointF(300.0, 268.0) << QPointF(450.0, 17.0)
                << QPointF(500.0, 4325.0) << QPointF(1000.0, 723.0);

        //![1]

        //![2]
        chart = new QChart();
        chart->addSeries(series);
        chart->addSeries(seriesP);
        chart->setTitle("SEV X");
        //![2]

        //![3]
        QLogValueAxis *axisX = new QLogValueAxis();
        axisX->setTitleText(tr("Distancia AB/2 (m)"));
        axisX->setLabelFormat("%g");
        axisX->setBase(10.0);
        axisX->setMinorTickCount(-1);
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->setAxisX(axisX, series);
        chart->setAxisX(axisX, seriesP);
        axisX->setRange(1.0, 1000.0);
        //series->attachAxis(axisX);
        //seriesP->attachAxis(axisX);

        QLogValueAxis *axisY = new QLogValueAxis();
        axisY->setTitleText(tr("Resistividad"));
        axisY->setLabelFormat("%g");
        axisY->setBase(10.0);
        axisY->setMinorTickCount(-1);
        chart->addAxis(axisY, Qt::AlignLeft);
        chart->setAxisY(axisY, series);
        chart->setAxisY(axisY, seriesP);
        axisY->setRange(1.0, 5000.0);
        //series->attachAxis(axisY);
        //seriesP->attachAxis(axisY);
        //![3]

        //![4]
        chart->setAnimationOptions(QChart::AllAnimations);


}
