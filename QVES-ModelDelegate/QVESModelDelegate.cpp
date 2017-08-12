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

QVESModelDelegate::QVESModelDelegate(QObject *parent) : QObject(parent)
{
    //mCore = new VESCore(this);
    mTableModel = new TableModel(this);

    //connect(mCore, &VESCore::projectLoaded, this, &QVESModelDelegate::currentProjectChanged);

    //Borrar
    OldProject *old;
    old = new OldProject;
//    QString testFile = "patron.sev";
//    Project *newProj = old->readOldProject(testFile);
//   SpliceData a1(3.5, 12.1);
//    a1.setSection(9);
//    a1.setStandardDeviation(3.0);

//    BasicData a2(4.6, 99.1);
//    XmlSerializer mSerializer;
//    mSerializer.save(a1, "a1.xml", "SpliceData");

//    SpliceData a3;
//    mSerializer.load(a3, "a1.xml");
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
