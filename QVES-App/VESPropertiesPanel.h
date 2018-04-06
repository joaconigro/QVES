#ifndef VESPROPERTIESPANEL_H
#define VESPROPERTIESPANEL_H

#include <QToolBox>
#include "QVESModelDelegate.h"
namespace Ui {
class VESPropertiesPanel;
}

class VESPropertiesPanel : public QToolBox
{
    Q_OBJECT

public:
    explicit VESPropertiesPanel(QVESModelDelegate *delegate, QWidget *parent = 0);
    ~VESPropertiesPanel();

private slots:
    void on_lineEditVesName_textEdited(const QString &arg1);

private:
    Ui::VESPropertiesPanel *ui;
    QVESModelDelegate *mainDelegate;

public slots:
    void loadVES();

signals:
    void VESNameEdited(const QString name);
};

#endif // VESPROPERTIESPANEL_H
