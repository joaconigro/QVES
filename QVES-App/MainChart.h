#ifndef MAINCHART_H
#define MAINCHART_H

#include <QWidget>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class MainChart : public QWidget
{
    Q_OBJECT
public:

    QChart *chart;

    explicit MainChart(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINCHART_H
