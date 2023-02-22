#include "commentsdialog.h"
#include "locoiomode.h"
#include "ui_commentsdialog.h"
#include "QSqlField"

CommentsDialog::CommentsDialog(int port, LocoIOData* data, Sql* sql, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommentsDialog)
{
 ui->setupUi(this);
 this->data = data;
 this->sql = sql;
 this->port = port;
 this->sql->setData(data);
 ui->lblDisplayUnitAddress->setText(QString("0x%1/%2 (%3/%4)").arg(data->getUnitAddress(),0,16).arg(data->getUnitSubAddress(),0,16).arg(data->getUnitAddress(),0,10).arg(data->getUnitSubAddress(),0,10));
 if(data->getModuleType() == "LocoServo" && (port >= 5 && port <=12))
 {
  ui->lblPort->setText("Servo:");
  ui->lblDisplayPort->setText(QString("%1").arg(port-4));
 }
 else
  ui->lblDisplayPort->setText(QString("%1").arg(port));
 ui->lblDisplayType->setText(data->getModuleType());
 ui->lblDisplayAddress->setText(QString("%1").arg(data->getAddr(port-1)));
 LocoIOMode* lim = data->getLIM(port-1);
 int isOutput = -1;
 if(lim != NULL)
  isOutput = lim->getOutput();
 QString sOutput;
 switch(isOutput)
 {
 case 0:
  sOutput = tr("Input");
  break;
 case 1:
  sOutput = tr("Output");
  break;
 default:
  sOutput = tr("Not Used");
  break;
 }
 ui->lblDisplayOutput->setText(sOutput);
 ui->lblDisplayMode->setText(((lim!=NULL)?lim->getFullMode():"None"));
 if(sql->commentRecordExists(port))
 {
  QSqlRecord rec = sql->getComments(port);
  for(int i=0; i <rec.count(); i++)
   qDebug() << QString("field %1, name %2, value %3").arg(i).arg(rec.fieldName(i)).arg(rec.value(i).toString());
  ui->edTitle->setText(rec.value("title").toString());
  ui->edTextEdit->setPlainText(rec.value("description").toString());
 }
 if(!sql->commentRecordExists(port))
  ui->btnDelete->setEnabled(false);
}

CommentsDialog::~CommentsDialog()
{
    delete ui;
}
void CommentsDialog::on_btnCancel_clicked()
{
 reject();
 close();
}
void CommentsDialog::on_btnDelete_clicked()
{
 sql->deleteComment(port);
 accept();
 close();
}
void CommentsDialog::on_btnUpdate_clicked()
{
    sql->updateComment(port, data->getModuleType(),ui->edTitle->text(), ui->edTextEdit->toPlainText());
 accept();
 close();
}
