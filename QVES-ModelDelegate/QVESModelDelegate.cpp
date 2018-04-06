#include "QVESModelDelegate.h"
#include <QtMath>

QString QVESModelDelegate::projectFileName() const
{
    return mProjectFileName;
}

QString QVESModelDelegate::projectPath() const
{
    return mProjectPath;
}

QString QVESModelDelegate::modelError() const
{
    if (mCurrentVES->currentModel()){
        return mCurrentVES->currentModel()->errorString();
    } else {
        return "";
    }
}

double QVESModelDelegate::chartMinX() const
{
    return mChartMinX;
}

double QVESModelDelegate::chartMinY() const
{
    return mChartMinY;
}

double QVESModelDelegate::chartMaxX() const
{
    return mChartMaxX;
}

double QVESModelDelegate::chartMaxY() const
{
    return mChartMaxY;
}

QList<int> QVESModelDelegate::selectedRows() const
{
    return mSelectedRows;
}

TableModel *QVESModelDelegate::selectionModel() const
{
    return mSelectionModel;
}

void QVESModelDelegate::createSelectionModel(const QList<int> &indices, const TableModel::DataType selectedData)
{
    if (indices.count()>0){
        QList<XYDataTable *> tempTable;
        switch (selectedData) {
        case TableModel::DataType::Field:
            foreach (auto i, indices) {
                auto item = mCurrentVES->fieldData().at(i);
                XYDataTable *value = new XYDataTable(item.ab2Distance(), item.resistivity());
                tempTable.append(value);
            }
            break;
        case TableModel::DataType::Splice:
            foreach (auto i, indices) {
                auto item = mCurrentVES->splices().at(i);
                XYDataTable *value = new XYDataTable(item.ab2Distance(), item.resistivity());
                tempTable.append(value);
            }
            break;
        case TableModel::DataType::Calculated:
            foreach (auto i, indices) {
                auto item = mCurrentVES->currentModel()->calculatedData().at(i);
                XYDataTable *value = new XYDataTable(item.ab2Distance(), item.resistivity());
                tempTable.append(value);
            }
            break;
        case TableModel::DataType::Model:
            foreach (auto i, indices) {
                auto item = mCurrentVES->currentModel()->model().at(i);
                if (item.from() == 0.0){
                    XYDataTable *value1 = new XYDataTable(mChartMinX, item.resistivity());
                    tempTable.append(value1);
                } else {
                    XYDataTable *value1 = new XYDataTable(item.from(), item.resistivity());
                    tempTable.append(value1);
                }
                if (item.until() == qInf()){
                    XYDataTable *value2 = new XYDataTable(mChartMaxX, item.resistivity());
                    tempTable.append(value2);
                } else {
                    XYDataTable *value2 = new XYDataTable(item.until(), item.resistivity());
                    tempTable.append(value2);
                }
            }
            break;
        default:
            break;
        }
        mSelectionModel->setTableFromVES(tempTable, TableModel::DataType::Field);
    }
}

VES *QVESModelDelegate::currentVES() const
{
    return mCurrentVES;
}

void QVESModelDelegate::setCurrentVES(VES *currentVES)
{
    mCurrentVES = currentVES;
}

Project *QVESModelDelegate::currentProject() const
{
    return mCurrentProject;
}

void QVESModelDelegate::setCurrentProject(Project *currentProject)
{
    mCurrentProject = currentProject;
}

void QVESModelDelegate::readVESNames()
{
    mVESNames.clear();
    foreach (const auto &ves, mCurrentProject->vess()) {
        mVESNames.append(ves->name());
    }
}

void QVESModelDelegate::readModelNames()
{
    mModelNames.clear();
    foreach (const auto &item, mCurrentVES->models()) {
        mModelNames.append(item->name());
    }
}

void QVESModelDelegate::selectModelForTable()
{
    switch (mShowedTableData) {
    case TableModel::DataType::Field:
        mCurrentModel = mFieldModel;
        break;
    case TableModel::DataType::Splice:
        mCurrentModel = mSpliceModel;
        break;
    case TableModel::DataType::Calculated:
       mCurrentModel = mCalculatedModel;
        break;
    case TableModel::DataType::Model:
       mCurrentModel = mTableModeledModel;
        break;
    }

    connect(mCurrentModel, &TableModel::myTableChanged, this, &QVESModelDelegate::updateVESData);
    emit tableModelChanged();
}

void QVESModelDelegate::fillFieldModel()
{
    QList<XYDataTable *> tempTable;
    foreach (const auto &item, mCurrentVES->fieldData()) {
        XYDataTable *value = new XYDataTable(item.ab2Distance(), item.resistivity());
        tempTable.append(value);
    }
    mFieldModel->setTableFromVES(tempTable, TableModel::DataType::Field);
}

void QVESModelDelegate::fillSpliceModel()
{
    QList<XYDataTable *> tempTable;
    foreach (const auto &item, mCurrentVES->splices()) {
        XYDataTable *value = new XYDataTable(item.ab2Distance(), item.resistivity());
        tempTable.append(value);
    }
    mSpliceModel->setTableFromVES(tempTable, TableModel::DataType::Splice);
}

void QVESModelDelegate::fillCalculatedModel()
{
    QList<XYDataTable *> tempTable;
    foreach (const auto &item, mCurrentVES->currentModel()->calculatedData()) {
        XYDataTable *value = new XYDataTable(item.ab2Distance(), item.resistivity());
        tempTable.append(value);
    }
    mCalculatedModel->setTableFromVES(tempTable, TableModel::DataType::Calculated);
}

void QVESModelDelegate::fillModeledModels()
{
    QList<XYDataTable *> tempTable;
    QList<XYDataTable *> tempTable2;

    foreach (const auto &item, mCurrentVES->currentModel()->model()) {
        XYDataTable *value0 = new XYDataTable(item.depth(), item.resistivity());
        tempTable2.append(value0);

        if (item.from() == 0.0){
            XYDataTable *value1 = new XYDataTable(mChartMinX, item.resistivity());
            tempTable.append(value1);
        } else {
            XYDataTable *value1 = new XYDataTable(item.from(), item.resistivity());
            tempTable.append(value1);
        }
        if (item.until() == qInf()){
            XYDataTable *value2 = new XYDataTable(mChartMaxX, item.resistivity());
            tempTable.append(value2);
        } else {
            XYDataTable *value2 = new XYDataTable(item.until(), item.resistivity());
            tempTable.append(value2);
        }
    }
    mTableModeledModel->setTableFromVES(tempTable2, TableModel::DataType::Model);
    mChartModeledModel->setTableFromVES(tempTable, TableModel::DataType::Model);
}

void QVESModelDelegate::resetTableModels()
{
    mCurrentModel = new TableModel(this);
    mFieldModel = new TableModel(this);
    mSpliceModel = new TableModel(this);
    mCalculatedModel = new TableModel(this);
    mTableModeledModel = new TableModel(this);
    mChartModeledModel = new TableModel(this);
    mSelectionModel = new TableModel(this);
}

QVESModelDelegate::QVESModelDelegate(QObject *parent) : QObject(parent)
{
    mCurrentProject = nullptr;
    mCurrentVES = nullptr;
    mCore = new VESCore(this);
    mCurrentModel = new TableModel(this);
    mShowedTableData = TableModel::DataType::Field;

    mProjectFileName = mProjectPath = "";
    mFieldModel = nullptr;
    mSpliceModel = nullptr;
    mCalculatedModel = nullptr;
    mTableModeledModel = nullptr;
    mChartModeledModel = nullptr;
    mSelectionModel = nullptr;

    connect(mCore, &VESCore::projectLoaded, this, &QVESModelDelegate::changeCurrentProject);
    connect(mCore, &VESCore::projectClosed, this, &QVESModelDelegate::projectClosed);
}

TableModel *QVESModelDelegate::currentModel()
{
    return mCurrentModel;
}

TableModel *QVESModelDelegate::fieldModel()
{
    return mFieldModel;
}

TableModel *QVESModelDelegate::spliceModel()
{
    return mSpliceModel;
}

TableModel *QVESModelDelegate::calculatedModel()
{
    return mCalculatedModel;
}

TableModel *QVESModelDelegate::tableModeledModel()
{
    return mTableModeledModel;
}

TableModel *QVESModelDelegate::chartModeledModel()
{
    return mChartModeledModel;
}

int QVESModelDelegate::currentVESIndex() const
{
    return mCurrentVESIndex;
}

int QVESModelDelegate::currentVESModelIndex() const
{
    return mCurrentVESModelIndex;
}

void QVESModelDelegate::changeCurrentProject()
{
    mCurrentProject = mCore->project();
    connect(mCurrentProject, &Project::currentVESChanged, this, &QVESModelDelegate::changeCurrentVES);
    mCurrentVESIndex = mCurrentProject->currentIndex();
    mProjectFileName = mCore->projectFileName();
    mProjectPath = mCore->projectPath();
    readVESNames();
    emit projectChanged();
    changeCurrentVES();
}

void QVESModelDelegate::changeCurrentVES()
{
    if (mCurrentVES){
        disconnect(this, &QVESModelDelegate::carryOutZohdyInversion, mCurrentVES, &VES::zohdyInversion);
        disconnect(this, &QVESModelDelegate::carryOutDarZarrouk, mCurrentVES, &VES::darZarrouk);
        disconnect(mCurrentVES, &VES::selectedModelChanged, this, &QVESModelDelegate::updateVESModels);
        disconnect(mCurrentVES, &VES::currentModelModified, this, &QVESModelDelegate::currentVESModelModified);
        disconnect(mCurrentVES, &VES::fieldDataModified, this, &QVESModelDelegate::currentVESFieldModified);
        disconnect(mCurrentVES, &VES::nameChanged, this, &QVESModelDelegate::onCurrentVESNameChanged);
    }
    mCurrentVES = mCurrentProject->currentVES();
    mCurrentVES->findMaxAndMin();
    mCurrentVESModelIndex = mCurrentVES->currentIndexModel();
    readModelNames();
    setDataTableModel();
    connect(this, &QVESModelDelegate::carryOutZohdyInversion, mCurrentVES, &VES::zohdyInversion);
    connect(this, &QVESModelDelegate::carryOutDarZarrouk, mCurrentVES, &VES::darZarrouk);
    connect(mCurrentVES, &VES::selectedModelChanged, this, &QVESModelDelegate::updateVESModels);
    connect(mCurrentVES, &VES::currentModelModified, this, &QVESModelDelegate::currentVESModelModified);
    connect(mCurrentVES, &VES::fieldDataModified, this, &QVESModelDelegate::currentVESFieldModified);
    connect(mCurrentVES, &VES::nameChanged, this, &QVESModelDelegate::onCurrentVESNameChanged);
    emit VESChanged();
}

void QVESModelDelegate::setDataTableModel()
{
    double exponent = log10(mCurrentVES->minX());
    exponent = (fmod(exponent, 1.0) != 0) ? floor(exponent) : exponent - 1.0;
    mChartMinX = pow(10, exponent);

    exponent = log10(mCurrentVES->minY());
    exponent = (fmod(exponent, 1.0) != 0) ? floor(exponent) : exponent - 1.0;
    mChartMinY = pow(10, exponent);

    exponent = log10(mCurrentVES->maxX());
    exponent = (fmod(exponent, 1.0) != 0) ? ceil(exponent) : exponent + 1.0;
    mChartMaxX = pow(10, exponent);

    exponent = log10(mCurrentVES->maxY());
    exponent = (fmod(exponent, 1.0) != 0) ? ceil(exponent) : exponent + 1.0;
    mChartMaxY = pow(10, exponent);

    resetTableModels();
    fillFieldModel();
    fillSpliceModel();
    if (mCurrentVES->models().count() > 0 && (mCurrentVES->currentModel())){
        fillCalculatedModel();
        fillModeledModels();
    }
    selectModelForTable();
}

void QVESModelDelegate::openProject(const QString &filename)
{
    mCore->openProject(filename);
}

void QVESModelDelegate::saveAsProject(const QString &filename)
{
    mCore->saveProject(filename);
}

void QVESModelDelegate::saveProject()
{
    mCore->saveProject();
}

void QVESModelDelegate::showedTableDataChanged(const TableModel::DataType dt)
{
    mShowedTableData = dt;
    selectModelForTable();
}

QStringList QVESModelDelegate::vesNames() const
{
    return mVESNames;
}

QStringList QVESModelDelegate::modelNames() const
{
    return mModelNames;
}

void QVESModelDelegate::updateVESData(const QModelIndex &index) const
{
    double tempValue = mCurrentModel->data(index, Qt::DisplayRole).toDouble();
    int dt = static_cast<int>(mShowedTableData);

    mCore->changeDataForCurrentVES(index.row(), index.column(), dt, tempValue);

}

void QVESModelDelegate::selectedVESChanged(int index) const
{
    mCurrentProject->setCurrentIndex(index);
}

void QVESModelDelegate::changeCurrentModel(int index)
{
    mCurrentVES->selectModel(index);
    emit vesCurrentModelChanged();
}

void QVESModelDelegate::updateVESModels(const int newIndex)
{
    mCurrentVESModelIndex = newIndex;
    readModelNames();
    setDataTableModel();
    emit VESChanged();
}

void QVESModelDelegate::projectClosed()
{
    mCurrentProject = nullptr;
    mCurrentVES = nullptr;
}

void QVESModelDelegate::onSelectionChanged(const QList<int> indices, TableModel::DataType dataType)
{
    mSelectedRows.clear();
    mSelectedRows.append(indices);
    createSelectionModel(indices, dataType);
    emit selectionChanged(static_cast<int>(dataType));
}

void QVESModelDelegate::currentVESModelModified()
{
    fillCalculatedModel();
    fillModeledModels();
    emit tableModelChanged();
    emit vesCurrentModelChanged();
}

void QVESModelDelegate::currentVESFieldModified()
{
    fillFieldModel();
    fillSpliceModel();
    emit tableModelChanged();
}

void QVESModelDelegate::mergeSelectedBeds()
{
    if (mShowedTableData == TableModel::DataType::Model){
        if(mSelectedRows.count()>1)
            emit carryOutDarZarrouk(mSelectedRows);
    }
}

void QVESModelDelegate::createEmptyModel(const int numberOfBeds)
{
    if (mCurrentVES){
        mCurrentVES->newZohdyModel(numberOfBeds);
    }
}

void QVESModelDelegate::onCurrentVESNameChanged()
{
    readVESNames();
    emit currentVESNameChanged();
}

