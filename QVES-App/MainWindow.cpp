#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QSplitter>
#include <QTabWidget>
#include "DataPanel.h"
#include "MainChart.h"
#include "VESPropertiesPanel.h"
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
    QTabWidget *mainTabs = new QTabWidget;


    DataPanel *dataPanel = new DataPanel;
    VESPropertiesPanel *propertiesPanel = new VESPropertiesPanel;

    MainChart *mainChart = new MainChart;
    mainTabs->addTab(dataPanel, tr("Datos del SEV"));
    mainTabs->addTab(propertiesPanel, tr("Propiedades del SEV"));
    mainTabs->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    QChartView *chartView = new QChartView(mainChart->chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    mainTabs->adjustSize();
    splitter->addWidget(mainTabs);
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
