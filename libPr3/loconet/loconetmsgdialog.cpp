#include "loconetmsgdialog.h"
#include "ui_loconetmsgdialog.h"
#include "llnmon.h"
#include "instancemanager.h"
#include <QWidget>
#include <QRegExpValidator>
#include <qregexp.h>

LocoNetMsgDialog::LocoNetMsgDialog(QWidget *parent) :
    JmriPanel(parent),
    ui(new Ui::LocoNetMsgDialog)
{
 ui->setupUi(this);
 this->setObjectName("LocoNetMsgDialog");
 //setWindowTitle(tr("Send LocoNet Packet"));
// msg = nullptr;
 for(int i=LnConstants::OPC_GPBUSY; i < LnConstants::OPC_WR_SL_DATA; i++)
 {
  QString text = LnConstants::OPC_NAME(i);
  if(text != "<unknown>")
  {
   ui->cbOpcode->addItem(text + " 0x" + QString("%1").arg(i,0,16),i);
  }
 }
}

LocoNetMsgDialog::~LocoNetMsgDialog()
{
 delete ui;
}
void LocoNetMsgDialog::on_cbOpcode_currentIndexChanged(int i)
{
 opCode = ui->cbOpcode->itemData(i).toInt();
 ui->lineEdit->setText(QString("%1").arg(opCode,0,16));
 ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("/[0-9a-f]+/i"),this));
 setMaxSize();
 //ui->lineEdit->setMaxLength(maxSize*2);
 ui->btnOk->setEnabled(false);
}

void  LocoNetMsgDialog::setMaxSize()
{
 switch(opCode)
 {
 case LnConstants::OPC_IDLE:
 case LnConstants::OPC_GPON:
 case LnConstants::OPC_GPOFF:
 case LnConstants::OPC_GPBUSY:
  maxSize = 2;
  break;
 case LnConstants::OPC_LOCO_ADR:
 case LnConstants::OPC_SW_ACK:
 case LnConstants::OPC_SW_STATE:
 case LnConstants::OPC_RQ_SL_DATA:
 case LnConstants::OPC_MOVE_SLOTS:
 case LnConstants::OPC_LINK_SLOTS:
 case LnConstants::OPC_UNLINK_SLOTS:
 case LnConstants::OPC_CONSIST_FUNC:
 case LnConstants::OPC_SLOT_STAT1:
 case LnConstants::OPC_LONG_ACK:
 case LnConstants::OPC_INPUT_REP:
 case LnConstants::OPC_SW_REQ:
 case LnConstants::OPC_SW_REP:
 case LnConstants::OPC_LOCO_SND:
 case LnConstants::OPC_LOCO_DIRF:
 case LnConstants::OPC_LOCO_SPD:
  maxSize = 4;
  break;
 default:
  maxSize = 64;
  break;
 }

}

void LocoNetMsgDialog::on_lineEdit_textEdited(QString text)
{
 if(ui->lineEdit->text().length()>= 2)
 {
  QString sOpcode = ui->lineEdit->text().mid(0,2);
  bool bOk;
  int iOpcode = sOpcode.toInt(&bOk, 16);
  if(bOk)
  {
   opCode = iOpcode;
   QString cbtext = LnConstants::OPC_NAME(opCode)
    + " 0x" + QString("%1").arg(opCode,0,16);
   ui->cbOpcode->setCurrentIndex(ui->cbOpcode->findText(cbtext));
   ui->lineEdit->setText(text.trimmed());
  }
  setMaxSize();
 }
 int len = ui->lineEdit->text().trimmed().length();
 if((len == maxSize*2 - 2) ||( maxSize == 64 && len >6))
  ui->btnOk->setEnabled(true);
 buildMsg();
}

void LocoNetMsgDialog::on_btnOk_clicked()
{
 if(buildMsg())
 {
  //accept();
  LocoNetSystemConnectionMemo* memo = (LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo");
  memo->getLnTrafficController()->sendLocoNetMessage(msg);
  ((QWidget*)parent())->close();
 }
}

LocoNetMessage* LocoNetMsgDialog::locoNetMessage() { return msg;}

bool LocoNetMsgDialog::buildMsg()
{
 QString text = ui->lineEdit->text().trimmed();
 int msgLength = text.count()/2;
 msg = new LocoNetMessage(msgLength + 1);
 msg->setOpCode(opCode);
 int element = 1;
 for(int i = 2; i < text.length(); i+=2)
 {
  bool bOk=false;
  msg->setElement(element++, text.mid(i,2).toInt(&bOk,16));
  if(!bOk)
   return false;
 }
 LlnMon* mon = new LlnMon();
 mon->setLocoNetTurnoutManager((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"));
 ui->lblMsg->setText(mon->displayMessage(*msg));
 return true;
}

QString LocoNetMsgDialog::getTitle() {return this->windowTitle();}
