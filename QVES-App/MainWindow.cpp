#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QSplitter>
#include <QTabWidget>
#include "DataPanel.h"
#include "MainChart.h"
#include "VESPropertiesPanel.h"
#include <QtCharts/QChartView>

#include "../QVES-ModelDelegate/QVESModelDelegate.h"
#include "../QVES-ModelDelegate/TableModel.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSplitter *splitter = new QSplitter(this);
    QTabWidget *mainTabs = new QTabWidget(splitter);


    DataPanel *dataPanel = new DataPanel;
    dataPanel->setMaximumWidth(dataPanel->sizeHint().width());
    VESPropertiesPanel *propertiesPanel = new VESPropertiesPanel;
    propertiesPanel->setMaximumWidth(dataPanel->sizeHint().width());

    MainChart *mainChart = new MainChart;
    mainTabs->addTab(dataPanel, tr("Datos del SEV"));
    mainTabs->addTab(propertiesPanel, tr("Propiedades del SEV"));

    mainTabs->setMaximumWidth(mainTabs->sizeHint().width());
    QChartView *chartView = new QChartView(mainChart->chart);
    chartView->setRenderHint(QPainter::Antialiasing);



    splitter->addWidget(mainTabs);
    splitter->addWidget(chartView);



    this->setCentralWidget(splitter);


    QVESModelDelegate *del = new QVESModelDelegate(this);
    del->setDataTableModel();
    dataPanel->setMyModel(del->model());


}

MainWindow::~MainWindow()
{
    delete ui;
}
