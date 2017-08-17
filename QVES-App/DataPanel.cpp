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

void DataPanel::loadVESNames(const QStringList &list)
{
    ui->comboBoxCurrentVes->clear();
    ui->comboBoxCurrentVes->addItems(list);
}

void DataPanel::loadModelNames(const QStringList &list)
{
    ui->comboBoxVesModel->clear();
    ui->comboBoxVesModel->addItems(list);
}

void DataPanel::on_comboBoxCurrentVes_currentIndexChanged(int index)
{

}
