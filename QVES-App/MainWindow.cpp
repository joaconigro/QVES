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
   mainTabs->addTab(dataPanel, tr("Datos del SEV"));

    VESPropertiesPanel *propertiesPanel = new VESPropertiesPanel;
    propertiesPanel->setMaximumWidth(dataPanel->sizeHint().width());
   mainTabs->addTab(propertiesPanel, tr("Propiedades del SEV"));

   mainTabs->setMaximumWidth(mainTabs->sizeHint().width());


    MainChart *mainChart = new MainChart;
    QChartView *chartView = new QChartView(mainChart->chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFrameShape(QFrame::StyledPanel);
    chartView->setFrameShadow(QFrame::Raised);
   // chartView->setRubberBand(QChartView::RectangleRubberBand);


    splitter->addWidget(mainTabs);
    splitter->addWidget(chartView);



    this->setCentralWidget(splitter);

    //borrar
    QVESModelDelegate *del = new QVESModelDelegate(this);
    QString testFile = "proy_nuevo.sev";
    del->openProject(testFile);
    dataPanel->setMyModel(del->model());
    mainChart->chartDelegateChanged(del->chartDelegate());
    dataPanel->loadVESNames(del->vesNames());
    dataPanel->loadModelNames(del->modelNames());
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}
