#ifndef QVESMODELDELEGATE_H
#define QVESMODELDELEGATE_H

#include <QObject>
#include "qves-modeldelegate_global.h"
#include "../VES-Core/VESCore.h"
#include "../VES-Core/Project.h"
#include "../VES-Core/VES.h"
#include "TableModel.h"
#include <QList>
#include "ModelDataTable.h"


class QVESMODELDELEGATESHARED_EXPORT QVESModelDelegate: public QObject
{
    Q_OBJECT

    //Project *mCurrentProject;
    //VES *mCurrentVES;
    //VESCore *mCore;
    TableModel *mTableModel;
    QList<ModelDataTable*> mList;

public:
    explicit QVESModelDelegate(QObject *parent);

    TableModel *model();
    QList<ModelDataTable*> list() const;

public slots:
    void currentProjectChanged();
    void setDataTableModel();
    void setList(QList<ModelDataTable*> list);

signals:
    void ListChanged(QList<ModelDataTable*> list);
};

#endif // QVESMODELDELEGATE_H
