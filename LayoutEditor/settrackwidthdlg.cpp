#include "settrackwidthdlg.h"
#include "ui_settrackwidthdlg.h"

SetTrackWidthDlg::SetTrackWidthDlg(int sideTrackWidth, int mainlineTrackWidth, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTrackWidthDlg)
{
 ui->setupUi(this);
 ui->sbSidetrack->setValue(sideTrackWidth);
 ui->sbMainline->setValue(mainlineTrackWidth);
}

SetTrackWidthDlg::~SetTrackWidthDlg()
{
 delete ui;
}
int SetTrackWidthDlg::sidetrackWidth()
{
 return ui->sbSidetrack->value();
}
int SetTrackWidthDlg::mainlineTrackWidth()
{
 return ui->sbMainline->value();
}
void SetTrackWidthDlg::on_cancelButton_clicked()
{
    reject();
    close();
}
void SetTrackWidthDlg::on_okButton_clicked()
{
 accept();
 close();
}
