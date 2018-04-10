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
#include "XYDataTable.h"
#include "QItemSelection"
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
    TableModel *mSelectionModel;
    TableModel::DataType mShowedTableData;
    QStringList mVESNames;
    QStringList mModelNames;
    QString mProjectFileName;
    QString mProjectPath;
    double mChartMinX;
    double mChartMinY;
    double mChartMaxX;
    double mChartMaxY;

    QList<int> mSelectedRows;


    void readVESNames();
    void readModelNames();
    void selectModelForTable(const bool emitSignal = true);
    void fillFieldModel();
    void fillSpliceModel();
    void fillCalculatedModel();
    void fillModeledModels();
    void resetTableModels();

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
    QList<int> selectedRows() const;


    TableModel *selectionModel() const;
    void createSelectionModel(const QList<int>& indices, const TableModel::DataType selectedData);


    VES *currentVES() const;
    void setCurrentVES(VES *currentVES);

    Project *currentProject() const;
    void setCurrentProject(Project *currentProject);

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
    void updateVESData(const QModelIndex &index, const int dataType, const double newValue) const;
    void selectedVESChanged(int index) const;
    void changeCurrentModel(int index);
    void updateVESModels(const int newIndex);
    void projectClosed();
    void onSelectionChanged(const QList<int> indices, TableModel::DataType dataType);
    void currentVESModelModified();
    void currentVESFieldModified();
    void mergeSelectedBeds();
    void createEmptyModel(const int numberOfBeds);

    void onCurrentVESNameChanged();

signals:
    void currentVESNameChanged();
    void projectChanged();
    void VESChanged();
    void vesCurrentModelChanged();
    void tableModelChanged();
    //void carryOutZohdyInversion(const int zohdyFilter, const bool autoDZ, const double autoDZThreshold);
    void carryOutDarZarrouk(const QList<int> beds);
    void selectionChanged(const int dataType);
    void onVESDataChanged(const QModelIndex &index, const int dataType, const double oldValue, const double newValue);
};

#endif // QVESMODELDELEGATE_H
