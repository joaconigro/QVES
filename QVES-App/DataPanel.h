#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <QWidget>
#include "../QVES-ModelDelegate/TableModel.h"

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
};

#endif // DATAPANEL_H
