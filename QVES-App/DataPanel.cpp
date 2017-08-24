#include "DataPanel.h"
#include "ui_DataPanel.h"

DataPanel::DataPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataPanel)
{
    ui->setupUi(this);
    ui->radioButtonField->setChecked(true);
    changeShowedData();
    ui->tableView->setItemDelegate(new TableDelegate);

    connect(ui->comboBoxCurrentVes, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &DataPanel::currentVESIndexChanged);
}

DataPanel::~DataPanel()
{
    delete ui;
}

void DataPanel::setMyModel(TableModel *mod)
{
    ui->tableView->reset();
    ui->tableView->setModel(mod);
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}

void DataPanel::loadVESNames(const QStringList &list, const int index)
{
    ui->comboBoxCurrentVes->clear();
    ui->comboBoxCurrentVes->addItems(list);
    ui->comboBoxCurrentVes->setCurrentIndex(index);
}

void DataPanel::loadModelNames(const QStringList &list, const int index)
{
    ui->comboBoxVesModel->clear();
    ui->comboBoxVesModel->addItems(list);
    ui->comboBoxVesModel->setCurrentIndex(index);
}

void DataPanel::changeShowedData()
{
    if(ui->radioButtonField->isChecked()){
        mSelectedData = TableModel::DataType::Field;
        ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    }else if (ui->radioButtonSplice->isChecked()) {
        mSelectedData = TableModel::DataType::Splice;
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else if (ui->radioButtonCalculated->isChecked()) {
        mSelectedData = TableModel::DataType::Calculated;
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else if (ui->radioButtonModeled->isChecked()) {
        mSelectedData = TableModel::DataType::Model;
        ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    }
    emit showedDataChanged(mSelectedData);
}


