#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <QWidget>
#include "TableModel.h"
#include <QStringList>
#include "TableDelegate.h"
#include "QItemSelectionModel"

namespace Ui {
class DataPanel;
}

class DataPanel : public QWidget
{
    Q_OBJECT

    TableModel::DataType  mSelectedData;
    TableDelegate *myDelegate;
    QItemSelectionModel *selectionModel;

public:
    explicit DataPanel(QWidget *parent = 0);
    ~DataPanel();

    void setMyModel(TableModel *mod);

private:
    Ui::DataPanel *ui;

public slots:
    void loadVESNames(const QStringList &list, const int index);
    void loadModelNames(const QStringList &list, const int index);
    void changeShowedData();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

signals:
    void currentVESIndexChanged(int index);
    void currentVESModelIndexChanged(int index);
    void showedDataChanged(const TableModel::DataType dataType);
    void rowSelectionChanged(const QList<int> indices, TableModel::DataType dataType);
};

#endif // DATAPANEL_H
