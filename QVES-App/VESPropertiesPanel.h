#ifndef VESPROPERTIESPANEL_H
#define VESPROPERTIESPANEL_H

#include <QToolBox>

namespace Ui {
class VESPropertiesPanel;
}

class VESPropertiesPanel : public QToolBox
{
    Q_OBJECT

public:
    explicit VESPropertiesPanel(QWidget *parent = 0);
    ~VESPropertiesPanel();

private:
    Ui::VESPropertiesPanel *ui;
};

#endif // VESPROPERTIESPANEL_H
