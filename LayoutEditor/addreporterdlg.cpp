#include "addreporterdlg.h"
#include "ui_addreporterdlg.h"

AddReporterDlg::AddReporterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddReporterDlg)
{
 ui->setupUi(this);
}

AddReporterDlg::~AddReporterDlg()
{
 delete ui;
}
QString AddReporterDlg::getName()
{
 return ui->edReporterName->text();
}
void AddReporterDlg::on_okButton_clicked()
{
 accept();
 close();
}
void AddReporterDlg::on_cancelButton_clicked()
{
 reject();
 close();
}
QPoint AddReporterDlg::getLoc()
{
 return QPoint(ui->edX->text().toInt(), ui->edY->text().toInt());
}
