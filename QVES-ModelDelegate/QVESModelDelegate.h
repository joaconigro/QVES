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
//#include "ChartDelegate.h"
#include <QStringList>


class QVESMODELDELEGATESHARED_EXPORT QVESModelDelegate: public QObject
{

    Q_OBJECT

    Project *mCurrentProject;
    VES *mCurrentVES;
    int mCurrentVESIndex;
    int mCurrentVESModelIndex;
    VESCore *mCore;
    TableModel *mCurrentModel;
    TableModel *mFieldModel;
    TableModel *mSpliceModel;
    TableModel *mCalculatedModel;
    TableModel *mTableModeledModel;
    TableModel *mChartModeledModel;
    TableModel::DataType mShowedTableData;
//    ChartDelegate *mChartDelegate;
    QStringList mVESNames;
    QStringList mModelNames;
    QString mProjectFileName;
    QString mProjectPath;
    double mChartMinX;
    double mChartMinY;
    double mChartMaxX;
    double mChartMaxY;
    QString mVESName;

    void readVESNames();
    void readModelNames();
    void selectModelForTable();

public:
    explicit QVESModelDelegate(QObject *parent);

    TableModel *currentModel();
    TableModel *fieldModel();
    TableModel *spliceModel();
    TableModel *calculatedModel();
    TableModel *tableModeledModel();
    TableModel *chartModeledModel();
    int currentVESIndex() const;
    int currentVESModelIndex() const;
    QString projectFileName() const;
    QString projectPath() const;
    QString modelError() const;
    double chartMinX() const;
    double chartMinY() const;
    double chartMaxX() const;
    double chartMaxY() const;
    QString vesName() const;

public slots:
    void changeCurrentProject();
    void changeCurrentVES();
    void setDataTableModel();
    void openProject(const QString &filename);
    void saveAsProject(const QString &filename);
    void saveProject();
    void showedTableDataChanged(const TableModel::DataType dt = TableModel::DataType::Field);
    QStringList vesNames() const;
    QStringList modelNames() const;
    void updateVESData(const QModelIndex &index) const;
    void selectedVESChanged(int index);
    void changeCurrentModel(int index);
    void updateVESModels();

signals:
    void projectChanged();
    void vesChanged();
    void tableModelChanged();
    void carryOutZohdyInversion();
};

#endif // QVESMODELDELEGATE_H
