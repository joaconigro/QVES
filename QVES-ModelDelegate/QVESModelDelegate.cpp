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

QString QVESModelDelegate::vesName() const
{
    return mCurrentVES->name();
}

QList<int> QVESModelDelegate::selectedRows() const
{
    return mSelectedRows;
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
    //disconnect(mCurrentProject, &Project::currentVESChanged, this, &QVESModelDelegate::changeCurrentVES);
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
    emit vesChanged();
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


//    switch (mShowedTableData) {
//    case TableModel::DataType::Field:
//        if (index.column() == 0){
//            mCurrentVES->fieldData()[index.row()].setAb2Distance(mCurrentModel->data(index, Qt::DisplayRole).toDouble());
//        }else if (index.column() == 1){
//            mCurrentVES->fieldData()[index.row()].setResistivity(mCurrentModel->data(index, Qt::DisplayRole).toDouble());
//        } else {
//            return;
//        }

//        break;
//    default:
//        break;
//    }
}

void QVESModelDelegate::selectedVESChanged(int index)
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
    emit vesChanged();
}

void QVESModelDelegate::projectClosed()
{
    mCurrentProject = nullptr;
    mCurrentVES = nullptr;
}

void QVESModelDelegate::dataSelectionChanged(const QList<int> indices)
{
    mSelectedRows.clear();
    mSelectedRows.append(indices);
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
