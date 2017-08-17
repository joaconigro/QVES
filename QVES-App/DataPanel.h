#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <QWidget>
#include "TableModel.h"
#include <QStringList>

namespace Ui {
class DataPanel;
}

class DataPanel : public QWidget
{
    Q_OBJECT


public:
    explicit DataPanel(QWidget *parent = 0);
    ~DataPanel();

    void setMyModel(TableModel *mod);

private:
    Ui::DataPanel *ui;

public slots:
    void loadVESNames(const QStringList &list);
    void loadModelNames(const QStringList &list);
private slots:
    void on_comboBoxCurrentVes_currentIndexChanged(int index);
};

#endif // DATAPANEL_H
