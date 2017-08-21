#ifndef QVESMODELDELEGATE_H
#define QVESMODELDELEGATE_H

#include <QObject>
#include "qves-modeldelegate_global.h"
#include "VESCore.h"
#include "OldProject.h"
#include "Project.h"
#include <QString>
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
    int mCurrentVESIndex;
    int mCurrentVESModelIndex;
    VESCore *mCore;
    TableModel *mTableModel;
    QList<ModelDataTable*> mTableList;
    DataForTable mShowedTableData;
    ChartDelegate *mChartDelegate;
    QStringList mVESNames;
    QStringList mModelNames;
    QString mProjectFileName;
    QString mProjectPath;

    void readVESNames();
    void readModelNames();

public:
    explicit QVESModelDelegate(QObject *parent);

    TableModel *model();
    QList<ModelDataTable*> list() const;
    ChartDelegate *chartDelegate() const;
    int currentVESIndex() const;
    int currentVESModelIndex() const;
    QString projectFileName() const;
    QString projectPath() const;

public slots:
    void changeCurrentProject();
    void changeCurrentVES();
    void setDataTableModel();
//    void setList(QList<ModelDataTable*> list);
    void openProject(const QString &filename);
    void saveAsProject(const QString &filename);
    void saveProject();
    void showedTableDataChanged(const DataForTable dt = DataForTable::Field);
    QStringList vesNames() const;
    QStringList modelNames() const;

    void selectedVESChanged(int index);

signals:
    //void ListChanged(QList<ModelDataTable*> list);
    void projectChanged();
    void vesChanged();
};

#endif // QVESMODELDELEGATE_H
