#include "NewCustomModelDialog.h"
#include "ui_NewCustomModelDialog.h"
#include <QPushButton>

NewCustomModelDialog::NewCustomModelDialog(const int beds, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCustomModelDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Aceptar"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));

    mNumberOfBeds = beds;
    ui->spinBoxNumberOfBeds->setValue(beds);
}

NewCustomModelDialog::~NewCustomModelDialog()
{
    delete ui;
}

void NewCustomModelDialog::on_spinBoxNumberOfBeds_valueChanged(int arg1)
{
    mNumberOfBeds = arg1;
}

void NewCustomModelDialog::on_buttonBox_accepted()
{
    emit numberOfBedSelected(mNumberOfBeds);
}
