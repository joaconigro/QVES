#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSplitter>
#include <QTabWidget>
#include <QtCharts/QChartView>
#include <QFileDialog>
#include <QLabel>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSplitter *splitter = new QSplitter(this);
    QTabWidget *mainTabs = new QTabWidget(splitter);
    mDelegate = new QVESModelDelegate(this);
    mDataPanel = new DataPanel;
    mPropertiesPanel = new VESPropertiesPanel;
    mChart = new MainChart;

    createConnections();

    ui->statusBar->addPermanentWidget(new QLabel(ui->statusBar));

    mDataPanel->setMaximumWidth(mDataPanel->sizeHint().width());
    mainTabs->addTab(mDataPanel, tr("Datos del SEV"));
    mPropertiesPanel->setMaximumWidth(mDataPanel->sizeHint().width());
    mainTabs->addTab(mPropertiesPanel, tr("Propiedades del SEV"));
    mainTabs->setMaximumWidth(mainTabs->sizeHint().width());



    QChartView *chartView = new QChartView(mChart->chart);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFrameShape(QFrame::StyledPanel);
    chartView->setFrameShadow(QFrame::Raised);


    splitter->addWidget(mainTabs);
    splitter->addWidget(chartView);
    this->setCentralWidget(splitter);
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createConnections()
{
    connect(mDataPanel, &DataPanel::currentVESIndexChanged, mDelegate, &QVESModelDelegate::selectedVESChanged);
    connect(mDelegate, &QVESModelDelegate::projectChanged, this, &MainWindow::loadProject);
    connect(mDelegate, &QVESModelDelegate::vesChanged, this, &MainWindow::loadVES);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openProject);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveProject);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveAsProject);
    connect(mDataPanel, &DataPanel::showedDataChanged, mDelegate, &QVESModelDelegate::showedTableDataChanged);
}

void MainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir proyecto..."),
                                                    "",
                                                    tr("Proyectos QVS (*.qvs);; Proyectos antiguos de SEVs (*.sev)"));
    if (!fileName.isNull()){
        mDelegate->openProject(fileName);
    }
}

void MainWindow::loadProject()
{
    mDataPanel->loadVESNames(mDelegate->vesNames(), mDelegate->currentVESIndex());
}

void MainWindow::loadVES()
{
    mDataPanel->setMyModel(mDelegate->model());
    mChart->chartDelegateChanged(mDelegate->chartDelegate());
    mDataPanel->loadModelNames(mDelegate->modelNames(), mDelegate->currentVESModelIndex());
    ui->statusBar->showMessage(mDelegate->modelError(), 0);
}

void MainWindow::saveProject()
{
    if (mDelegate->projectFileName().isEmpty()){
        saveAsProject();
    } else {
        mDelegate->saveProject();
    }

}

void MainWindow::saveAsProject()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar proyecto como..."),
                                                    mDelegate->projectPath(),
                                                    tr("Proyectos QVS (*.qvs)"));
    if (!fileName.isNull()){
        mDelegate->saveAsProject(fileName);
    }
}
