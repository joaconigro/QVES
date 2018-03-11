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
    QList<int> mSelectedRows;

    int mZohdyFilter;
    double mAutoDarZarroukThreshold;
    bool mAutoDarZarrouk;

    double mVFSAInitialTemperature;
    int mVFSAIterationsPerTemperature;
    int mVFSAMovesPerTemperature;
    int mVFSASolutions;
    int mVFSANumberOfBeds;
    double mVFSAMaximunError;
    double mVFSAMinimunPdf;

    void readVESNames();
    void readModelNames();
    void selectModelForTable();
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
    QString vesName() const;
    QList<int> selectedRows() const;

    int zohdyFilter() const;
    void setZohdyFilter(int zohdyFilter);

    double autoDarZarroukThreshold() const;
    void setAutoDarZarroukThreshold(double autoDarZarroukThreshold);

    bool autoDarZarrouk() const;
    void setAutoDarZarrouk(bool autoDarZarrouk);

    double vFSAInitialTemperature() const;
    void setVFSAInitialTemperature(double vFSAInitialTemperature);

    int vFSAIterationsPerTemperature() const;
    void setVFSAIterationsPerTemperature(int vFSAIterationsPerTemperature);

    int vFSAMovesPerTemperature() const;
    void setVFSAMovesPerTemperature(int vFSAMovesPerTemperature);

    int vFSASolutions() const;
    void setVFSASolutions(int vFSASolutions);

    int vFSANumberOfBeds() const;
    void setVFSANumberOfBeds(int vFSANumberOfBeds);

    double vFSAMaximunError() const;
    void setVFSAMaximunError(double vFSAMaximunError);

    double vFSAMinimunPdf() const;
    void setVFSAMinimunPdf(double vFSAMinimunPdf);

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
    void updateVESModels(const int newIndex);
    void projectClosed();
    void dataSelectionChanged(const QList<int> indices);
    void currentVESModelModified();
    void currentVESFieldModified();
    void mergeSelectedBeds();
    void createEmptyModel(const int numberOfBeds);
    void onZohdyInversionRequested();

signals:
    void projectChanged();
    void vesChanged();
    void vesCurrentModelChanged();
    void tableModelChanged();
    void carryOutZohdyInversion(const int zohdyFilter, const bool autoDZ, const double autoDZThreshold);
    void carryOutDarZarrouk(const QList<int> beds);
};

#endif // QVESMODELDELEGATE_H
