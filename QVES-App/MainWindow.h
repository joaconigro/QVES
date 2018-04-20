#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataPanel.h"
#include "MainChart.h"
#include "VESPropertiesPanel.h"
#include "QVESModelDelegate.h"
#include "TableModel.h"
#include <QLabel>
#include "QVESSettings.h"
#include "Commands/CommandsManager.h"
#include "PanelsDelegateMediator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *rmsStatusLabel;
    QMenu *recentProjectsMenu;
    Ui::MainWindow *ui;
    DataPanel *mDataPanel;
    VESPropertiesPanel *mPropertiesPanel;
    MainChart *mChart;
    QVESModelDelegate *mDelegate;
    QChartView *chartView;
    CommandsManager *mCommandManager;
    PanelsDelegateMediator *mMediator;

    QString mLastDirectory;
    QVESSettings* mQVESSettings;
    void createConnections();

    void loadSettings();
    void writeSettings();

    bool userWantsToSave() const;

    void closeEvent(QCloseEvent *event);

private slots:
    void openProject(const QString filename);
    void loadProject();
    void loadVES();
    void modelChanged();
    void saveProject();
    void saveAsProject();
    void createEmptyModel();
    void exportChartAs();
    void on_actionShowFieldData_triggered();

    void on_actionShowSplices_triggered();

    void on_actionShowCalculatedData_triggered();

    void on_actionShowModels_triggered();
    void onSettingsLoaded();

    void on_actionOpen_triggered();

    void on_actionInversionOptions_triggered();

    void on_actionChartOptions_triggered();

    void on_actionGeneralOptions_triggered();



//    void on_actionZohdy_triggered();

//    void on_actionUndo_triggered();

//    void on_actionRedo_triggered();
//    void currentVESChanged(const int index);
//    void onVESNameEdited(const QString& name);
//    void onVESDataChanged(const QModelIndex &index, const int dataType, const double oldValue, const double newValue) const;

signals:
    void fieldVisibleChanged(const bool value);
    void spliceVisibleChanged(const bool value);
    void calculatedVisibleChanged(const bool value);
    void modeledVisibleChanged(const bool value);


};

#endif // MAINWINDOW_H
