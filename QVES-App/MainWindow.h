#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataPanel.h"
#include "MainChart.h"
#include "VESPropertiesPanel.h"
#include "QVESModelDelegate.h"
#include "TableModel.h"
#include <QLabel>

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

    void createConnections();

private slots:
    void openProject();
    void loadProject();
    void loadVES();
    void modelChanged();
    void saveProject();
    void saveAsProject();
    void modelUpdated();
};

#endif // MAINWINDOW_H
