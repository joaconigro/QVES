#include "MainWindow.h"
#include "ui_MainWindow.h"

//#include "../VES-Core/BasicData.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
