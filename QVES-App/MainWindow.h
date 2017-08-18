#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataPanel.h"
#include "MainChart.h"
#include "VESPropertiesPanel.h"
#include "QVESModelDelegate.h"
#include "TableModel.h"

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
    Ui::MainWindow *ui;
    DataPanel *mDataPanel;
    VESPropertiesPanel *mPropertiesPanel;
    MainChart *mChart;
    QVESModelDelegate *mDelegate;

private slots:
    void openProject();
    void loadProject();
    void loadVES();
};

#endif // MAINWINDOW_H
