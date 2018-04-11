#include "DataPanel.h"
#include "ui_DataPanel.h"

DataPanel::DataPanel(QVESModelDelegate *delegate, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataPanel),
    mainDelegate(delegate)
{
    ui->setupUi(this);
    ui->radioButtonField->setChecked(true);
    mResetSelection = false;
    selectionModel = nullptr;
    changeShowedData();
    ui->tableView->setItemDelegate(new TableDelegate);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    connect(ui->comboBoxCurrentVes, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &DataPanel::currentVESIndexChanged);
    connect(ui->comboBoxVesModel, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &DataPanel::currentVESModelIndexChanged);
}

DataPanel::~DataPanel()
{
    delete ui;
}

void DataPanel::setMyModel()
{
    ui->tableView->reset();
    ui->tableView->setModel(mainDelegate->currentModel());

    selectionModel = ui->tableView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &DataPanel::selectionChanged);


    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    loadVESNames();
    loadModelNames();
    if (mResetSelection){
        selectionModel->select(mPreviousIndex, QItemSelectionModel::Select);
        mResetSelection = false;
    }
}

void DataPanel::loadVESNames()
{
    ui->comboBoxCurrentVes->clear();
    ui->comboBoxCurrentVes->addItems(mainDelegate->vesNames());
    ui->comboBoxCurrentVes->blockSignals(true);
    ui->comboBoxCurrentVes->setCurrentIndex(mainDelegate->currentVESIndex());
    ui->comboBoxCurrentVes->blockSignals(false);
}

void DataPanel::loadModelNames()
{
    ui->comboBoxVesModel->clear();
    ui->comboBoxVesModel->addItems(mainDelegate->modelNames());
    ui->comboBoxVesModel->setCurrentIndex(mainDelegate->currentVESModelIndex());
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
    if (selectionModel)
        selectionModel->clearSelection();
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

void DataPanel::restoreSelection(const QModelIndex &index)
{
    mPreviousIndex = index;
    mResetSelection = true;
}
