#include "QVESModelDelegate.h"

QString QVESModelDelegate::projectFileName() const
{
    return mProjectFileName;
}

QString QVESModelDelegate::projectPath() const
{
    return mProjectPath;
}

void QVESModelDelegate::readVESNames()
{
    mVESNames.clear();
    foreach (const VES &ves, mCurrentProject->vess()) {
        mVESNames.append(ves.name());
    }
}

void QVESModelDelegate::readModelNames()
{
    mModelNames.clear();
    foreach (const auto &item, mCurrentVES->models()) {
        mModelNames.append(item.name());
    }
}

QVESModelDelegate::QVESModelDelegate(QObject *parent) : QObject(parent)
{
    mCurrentProject = nullptr;
    mCurrentVES = nullptr;
    mCore = new VESCore(this);
    mTableModel = new TableModel(this);
    mShowedTableData = DataForTable::Field;
    mChartDelegate = new ChartDelegate(this);
    connect(mCore, &VESCore::projectLoaded, this, &QVESModelDelegate::changeCurrentProject);
    mProjectFileName = mProjectPath = "";
}

TableModel *QVESModelDelegate::model()
{
    return mTableModel;
}

QList<ModelDataTable *> QVESModelDelegate::list() const
{
    return mTableList;
}

ChartDelegate *QVESModelDelegate::chartDelegate() const
{
    return mChartDelegate;
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
    disconnect(mCurrentProject, &Project::currentVESChanged, this, &QVESModelDelegate::changeCurrentVES);
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
    mCurrentVES = mCurrentProject->currentVES();
    mCurrentVESModelIndex = mCurrentVES->currentIndexModel();
    readModelNames();
    setDataTableModel();
    mChartDelegate->configureModelsFromVES(mCurrentVES);
    emit vesChanged();
}

void QVESModelDelegate::setDataTableModel()
{
    mTableList.clear();
    switch (mShowedTableData) {
    case DataForTable::Field:
        foreach (const auto &item, mCurrentVES->fieldData()) {
            ModelDataTable *value = new ModelDataTable(item.ab2Distance(), item.resistivity());
            mTableList.append(value);
        }
        break;
    case DataForTable::Splice:
        foreach (const auto &item, mCurrentVES->splices()) {
            ModelDataTable *value = new ModelDataTable(item.ab2Distance(), item.resistivity());
            mTableList.append(value);
        }
        break;
    case DataForTable::Calculated:
        foreach (const auto &item, mCurrentVES->currentModel()->calculatedData()) {
            ModelDataTable *value = new ModelDataTable(item.ab2Distance(), item.resistivity());
            mTableList.append(value);
        }
        break;
    case DataForTable::Model:
        foreach (const auto &item, mCurrentVES->currentModel()->model()) {
            ModelDataTable *value = new ModelDataTable(item.depth(), item.resistivity());
            mTableList.append(value);
        }
        break;
    }

    mTableModel->setTableFromVES(mTableList);
}

//void QVESModelDelegate::setList(QList<ModelDataTable *> list)
//{
//    //if (mList == list)
//    //    return;

//    mTableList = list;
//    emit ListChanged(mTableList);
//}

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

void QVESModelDelegate::showedTableDataChanged(const QVESModelDelegate::DataForTable dt)
{
    mShowedTableData = dt;
    setDataTableModel();
}

QStringList QVESModelDelegate::vesNames() const
{
    return mVESNames;
}

QStringList QVESModelDelegate::modelNames() const
{
    return mModelNames;
}

void QVESModelDelegate::selectedVESChanged(int index)
{
    mCurrentProject->setCurrentIndex(index);
}
