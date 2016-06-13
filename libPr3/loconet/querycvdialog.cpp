#include "querycvdialog.h"
#include "ui_querycvdialog.h"
#include "instancemanager.h"

QueryCvDialog::QueryCvDialog(QWidget* parent) : QWidget(parent),
  ui(new Ui::QueryCvDialog)
{
 ui->setupUi(this);
 LocoNetSystemConnectionMemo* memo = (LocoNetSystemConnectionMemo*)InstanceManager::getDefault("SystemConnectionMemo");
 this->data = new LocoIOData(0x51,1, memo->getLnTrafficController());
 //this->locobufferadapter = memo->getLnTrafficController();
 this->bHex = true;
 rxHex.setPattern("^[0-9a-f]{1,3}\\/[0-9a-f]{1,2}");
 rxHex.setCaseSensitivity(Qt::CaseInsensitive);
 rxDec.setPattern("^[0-9]{1,3}\\/[0-9]{1,3}");
 rv = new  AddressValidator(rxHex);
 rv->setRelaxed(true);
 ui->edAddress->setValidator(rv);
 ui->chkHex->setChecked(bHex);
}

QueryCvDialog::QueryCvDialog(LocoIOData* data, LocoBufferAdapter* locobufferadapter, bool bHex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryCvDialog)
{
 ui->setupUi(this);
 this->data = data;
 this->locobufferadapter = locobufferadapter;
 this->bHex = bHex;
 rxHex.setPattern("^[0-9a-f]{1,3}\\/[0-9a-f]{1,2}");
 rxHex.setCaseSensitivity(Qt::CaseInsensitive);
 rxDec.setPattern("^[0-9]{1,3}\\/[0-9]{1,3}");
 rv = new  AddressValidator(rxHex);
 rv->setRelaxed(true);
 ui->edAddress->setValidator(rv);
 ui->chkHex->setChecked(bHex);

}

QueryCvDialog::~QueryCvDialog()
{
    delete ui;
}
int QueryCvDialog::decodeText(QLineEdit *ctl)
{
 QString text = ctl->text();
 bool bOk=false;
 int val;
 if(text.startsWith("0x",Qt::CaseInsensitive))
  val = text.mid(2).toInt(&bOk,16);
 else
  val = text.toInt(&bOk,10);
 if(!bOk)
  return -1;
 return val;
}
void QueryCvDialog::on_edAddress_textChanged(QString text)
{
 addr=0;
 subAddr=0;
 int pos=0;
 bool bOk;
 switch(rv->validate(text, pos))
 {
 case QValidator::Acceptable:
   break;
 case QValidator::Intermediate:
  return;
 case QValidator::Invalid:
   return;
 }

 int iBase = ui->chkHex->isChecked()?16:10;
 QStringList sl = text.split("/");
 addr = sl.at(0).toInt(&bOk,iBase);
 subAddr = sl.at(1).toInt(&bOk, iBase);
}
void QueryCvDialog::on_chkHex_toggled(bool bChecked)
{
 //emit displayFormat(bChecked);
 if(bChecked)
 {
  ui->lblUnitAddr->setText(tr("Unit Address 0x"));
  rv->setRegExp(rxHex);
 }
 else
 {
  ui->lblUnitAddr->setText(tr("Unit Address"));
  rv->setRegExp(rxDec);
 }
}
void QueryCvDialog::on_edCv_editingFinished()
{
 cv = decodeText(ui->edCv);
}
void QueryCvDialog::on_btnOK_clicked()
{
 data->sendReadCommand(addr, subAddr,cv);
}
void QueryCvDialog::on_btnCancel_clicked()
{
 this->close();
}
