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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLabel *rmsStatusLabel;
    Ui::MainWindow *ui;
    DataPanel *mDataPanel;
    VESPropertiesPanel *mPropertiesPanel;
    MainChart *mChart;
    QVESModelDelegate *mDelegate;
    QChartView *chartView;

    QVESSettings* mQVESSettings;
    void createConnections();

    void loadSettings();
    void writeSettings();

    bool userWantsToSave() const;

    void closeEvent(QCloseEvent *event);

private slots:
    void openProject();
    void loadProject();
    void loadVES();
    void modelChanged();
    void saveProject();
    void saveAsProject();
    void modelUpdated();
    void createEmptyModel();
    void exportChartAs();
    void on_actionShowFieldData_triggered();

    void on_actionShowSplices_triggered();

    void on_actionShowCalculatedData_triggered();

    void on_actionShowModels_triggered();

signals:
    void fieldVisibleChanged(const bool value);
    void spliceVisibleChanged(const bool value);
    void calculatedVisibleChanged(const bool value);
    void modeledVisibleChanged(const bool value);

};

#endif // MAINWINDOW_H
