#include "QVESModelDelegate.h"

QVESModelDelegate::QVESModelDelegate(QObject *parent) : QObject(parent)
{
    //mCore = new VESCore(this);
    mTableModel = new TableModel(this);

    //connect(mCore, &VESCore::projectLoaded, this, &QVESModelDelegate::currentProjectChanged);
}

TableModel *QVESModelDelegate::model()
{
    return mTableModel;
}

QList<ModelDataTable *> QVESModelDelegate::list() const
{
    return mList;
}

void QVESModelDelegate::currentProjectChanged()
{
    //mCurrentProject = mCore->project();
    //mCurrentVES = mCurrentProject->currentVES();
}

void QVESModelDelegate::setDataTableModel()
{
    ModelDataTable *v1 = new ModelDataTable(5.0, 15.0);
//    v1.setX(5.0);
//    v1.setY(15.0);

    ModelDataTable *v2 = new ModelDataTable(25.0, 35.0);
//    v2.setX(25.0);
//    v2.setY(35.0);

    mList << v1 << v2;

    mTableModel->setTableFromVes(mList);
}

void QVESModelDelegate::setList(QList<ModelDataTable *> list)
{
    //if (mList == list)
    //    return;

    mList = list;
    emit ListChanged(mList);
}
