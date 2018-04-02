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
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //selectionModel = ui->tableView->selectionModel();

    //selectionModel->selectionChanged(selectionModel->selection(), QItemSelection);
    //connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &DataPanel::selectionChanged);
    //connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &DataPanel::selectionChanged2);

    connect(ui->comboBoxCurrentVes, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &DataPanel::currentVESIndexChanged);
    connect(ui->comboBoxVesModel, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &DataPanel::currentVESModelIndexChanged);
}

DataPanel::~DataPanel()
{
    delete ui;
}

void DataPanel::setMyModel(TableModel *mod)
{
    ui->tableView->reset();
    ui->tableView->setModel(mod);
    selectionModel = ui->tableView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &DataPanel::selectionChanged);
    //connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &DataPanel::selectionChanged2);

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
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);
    }else if (ui->radioButtonSplice->isChecked()) {
        mSelectedData = TableModel::DataType::Splice;
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else if (ui->radioButtonCalculated->isChecked()) {
        mSelectedData = TableModel::DataType::Calculated;
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else if (ui->radioButtonModeled->isChecked()) {
        mSelectedData = TableModel::DataType::Model;
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed | QAbstractItemView::AnyKeyPressed);
    }
    emit showedDataChanged(mSelectedData);
}

void DataPanel::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected)
    Q_UNUSED(deselected)

    QList<int> indices;
    int i;
    foreach (const auto &s,  selectionModel->selectedIndexes()) {
        i = s.row();
        if(!(indices.contains(i)))
            indices.append(i);
    }

    emit rowSelectionChanged(indices, mSelectedData);
}


