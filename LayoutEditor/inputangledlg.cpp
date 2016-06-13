#include "inputangledlg.h"
#include "ui_inputangledlg.h"

InputAngleDlg::InputAngleDlg(int degrees,
                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputAngleDlg)
{
    ui->setupUi(this);
    ui->spinX->setValue(degrees);
    ui->textX->setText(tr("Angle"));
}

InputAngleDlg::~InputAngleDlg()
{
    delete ui;
}
int InputAngleDlg::angle() { return ui->spinX->value();}

void InputAngleDlg::on_okButton_clicked()
{
    accept();
    close();
}
void InputAngleDlg::on_cancelButton_clicked()
{
    reject();
    close();
}
