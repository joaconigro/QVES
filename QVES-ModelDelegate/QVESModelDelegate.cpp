#include "QVESModelDelegate.h"


//borrar
#include "OldProject.h"
//#include "Project.h"
#include <QString>
//#include "SpliceData.h"
//#include "../VES-Core/SpliceData.h"
//#include "../VES-Core/BasicData.h"
//#include "../VES-Core/XmlSerializer.h"
//#include "../VES-Core/Serializer.h"

void QVESModelDelegate::readVESNames()
{
    foreach (const VES &ves, mCurrentProject->vess()) {
        mVESNames.append(ves.name());
    }
}

void QVESModelDelegate::readModelNames()
{
    foreach (const auto &item, mCurrentVES->models()) {
        mModelNames.append(item.name());
    }
}

QVESModelDelegate::QVESModelDelegate(QObject *parent) : QObject(parent)
{
    mCore = new VESCore(this);
    mTableModel = new TableModel(this);
    mShowedTableData = DataForTable::Field;
    mChartDelegate = new ChartDelegate(this);
    connect(mCore, &VESCore::projectLoaded, this, &QVESModelDelegate::currentProjectChanged);

    //Borrar
//    QString testFile = "proy_nuevo.sev"; //"patron.sev";
//    OldProject *old = new OldProject;
//    mCurrentProject = old->readOldProject(testFile);
//    XmlSerializer ser;
//    ser.save(*mCurrentProject, "newProj.qvs", "Project");
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

void QVESModelDelegate::currentProjectChanged()
{
    mCurrentProject = mCore->project();
    mCurrentVES = mCurrentProject->currentVES();
    readVESNames();
    readModelNames();
    setDataTableModel();
    mChartDelegate->configureModelsFromVES(mCurrentVES);
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

void QVESModelDelegate::setList(QList<ModelDataTable *> list)
{
    //if (mList == list)
    //    return;

    mTableList = list;
    emit ListChanged(mTableList);
}

void QVESModelDelegate::openProject(const QString &filename)
{
    mCore->openProject(filename);

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
