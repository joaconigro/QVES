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

void DataPanel::setMyModel(TableModel *mod)
{
    ui->tableView->setModel(mod);
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}
