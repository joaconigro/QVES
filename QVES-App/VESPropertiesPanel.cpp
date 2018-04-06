#include "VESPropertiesPanel.h"
#include "ui_VESPropertiesPanel.h"

VESPropertiesPanel::VESPropertiesPanel(QVESModelDelegate *delegate, QWidget *parent) :
    QToolBox(parent),
    ui(new Ui::VESPropertiesPanel)
{
    ui->setupUi(this);

    mainDelegate = delegate;
}

VESPropertiesPanel::~VESPropertiesPanel()
{
    delete ui;
}

void VESPropertiesPanel::on_lineEditVesName_textEdited(const QString &arg1)
{
    emit VESNameEdited(arg1);
}

void VESPropertiesPanel::loadVES()
{
    ui->lineEditVesName->setText(mainDelegate->currentVES()->name());
    ui->lineEditVesOperator->setText(mainDelegate->currentVES()->fieldOperator());
    ui->lineEditEquipment->setText(mainDelegate->currentVES()->equipment());
}
