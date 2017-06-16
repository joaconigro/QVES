#include "DataPanel.h"
#include "ui_DataPanel.h"

DataPanel::DataPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataPanel)
{
    ui->setupUi(this);
}

DataPanel::~DataPanel()
{
    delete ui;
}
