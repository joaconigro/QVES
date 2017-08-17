#ifndef QVESMODELDELEGATE_H
#define QVESMODELDELEGATE_H

#include <QObject>
#include "qves-modeldelegate_global.h"
#include "VESCore.h"
#include "Project.h"
#include "VES.h"
#include "TableModel.h"
#include <QList>
#include "ModelDataTable.h"
#include "ChartDelegate.h"
#include <QStringList>


class QVESMODELDELEGATESHARED_EXPORT QVESModelDelegate: public QObject
{
public:
    enum class DataForTable{Field, Splice, Calculated, Model};

private:
    Q_OBJECT

    Project *mCurrentProject;
    VES *mCurrentVES;
    VESCore *mCore;
    TableModel *mTableModel;
    QList<ModelDataTable*> mTableList;
    DataForTable mShowedTableData;
    ChartDelegate *mChartDelegate;
    QStringList mVESNames;
    QStringList mModelNames;

    void readVESNames();
    void readModelNames();

public:
    explicit QVESModelDelegate(QObject *parent);

    TableModel *model();
    QList<ModelDataTable*> list() const;
    ChartDelegate *chartDelegate() const;

public slots:
    void currentProjectChanged();
    void setDataTableModel();
    void setList(QList<ModelDataTable*> list);
    void openProject(const QString &filename);
    void showedTableDataChanged(const DataForTable dt = DataForTable::Field);
    QStringList vesNames() const;
    QStringList modelNames() const;

signals:
    void ListChanged(QList<ModelDataTable*> list);
};

#endif // QVESMODELDELEGATE_H
