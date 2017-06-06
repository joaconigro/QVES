#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../VES-Core/BasicData.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BasicData a1(2.0, 53);
    BasicData a2(2.0, 21.0);
    int i;
    if (a1 == a2)
        i = 2;
    else
        i = 3;

}

MainWindow::~MainWindow()
{
    delete ui;
}
