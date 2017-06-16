#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QSplitter>
#include "DataPanel.h"
#include "MainChart.h"
#include <QtCharts/QChartView>

//#include "../VES-Core/SpliceData.h"
//#include "../VES-Core/BasicData.h"
//#include "../VES-Core/XmlSerializer.h"
//#include "../VES-Core/Serializer.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSplitter *splitter = new QSplitter(this);
    DataPanel *dataPanel = new DataPanel;
    MainChart *mainChart = new MainChart;
    QChartView *chartView = new QChartView(mainChart->chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    splitter->addWidget(dataPanel);
    splitter->addWidget(chartView);

    this->setCentralWidget(splitter);

//    SpliceData a1(3.0, 18.2);
//    a1.setSection(9);
//    a1.setStandardDeviation(3.0);

//    BasicData a2(4.6, 99.1);
//    XmlSerializer mSerializer;
//    mSerializer.save(a1, "D:/a2.xml", "SpliceData");

//    SpliceData a3;
//    mSerializer.load(a3, "D:/a1.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}
