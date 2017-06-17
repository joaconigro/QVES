#include "VESPropertiesPanel.h"
#include "ui_VESPropertiesPanel.h"

VESPropertiesPanel::VESPropertiesPanel(QWidget *parent) :
    QToolBox(parent),
    ui(new Ui::VESPropertiesPanel)
{
    ui->setupUi(this);
}

VESPropertiesPanel::~VESPropertiesPanel()
{
    delete ui;
}
