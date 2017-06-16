#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <QWidget>

namespace Ui {
class DataPanel;
}

class DataPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DataPanel(QWidget *parent = 0);
    ~DataPanel();

private:
    Ui::DataPanel *ui;
};

#endif // DATAPANEL_H
