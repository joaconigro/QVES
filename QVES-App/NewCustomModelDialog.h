#ifndef NEWCUSTOMMODELDIALOG_H
#define NEWCUSTOMMODELDIALOG_H

#include <QDialog>

namespace Ui {
class NewCustomModelDialog;
}

class NewCustomModelDialog : public QDialog
{
    Q_OBJECT

    int mNumberOfBeds;

public:
    explicit NewCustomModelDialog(QWidget *parent = 0);
    ~NewCustomModelDialog();

private slots:
    void on_spinBoxNumberOfBeds_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::NewCustomModelDialog *ui;

signals:
    void numberOfBedSelected(int value);
};

#endif // NEWCUSTOMMODELDIALOG_H
