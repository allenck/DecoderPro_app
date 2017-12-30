#include "registerswidget.h"
#include "ui_registerswidget.h"
//#include <QColorGroup>
#include <QList>
#include "locoiodialog.h"
#include "turnoutdlg.h"
#include "proxysensormanager.h"
#include <QListWidget>
#include "instancemanager.h"
#include "proxylightmanager.h"
#include "abstractlightmanager.h"

RegistersWidget::RegistersWidget(LocoIOData* data, int port, portType type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistersWidget)
{
 ui->setupUi(this);
 this->data = data;
 this->port = port;
 setPortType(type);
 channel = port-1;
 //bServo = false;
 bHexDisplay = true;
 nbrFormat=16;
 nbrPrefix = "0x";
 iState = -1;
 ui->edCfg->setReadOnly(false);
 ui->edVal1->setReadOnly(false);
 ui->edVal2->setReadOnly(false);
 validNormalCfg << 0x07 << 0x0f << 0x10 << 0x17 << 0x1b << 0x1f <<0x27 << 0x2F <<0x37 << 0x3F << 0x60 << 0x5b << 0x5F << 0x63 << 0x67 << 0x6F ; // inputs
 validNormalCfg << 0x80 << 0xB0 << 0x81 << 0xB1 << 0x88 << 0x8C << 0x90 << 0xA0 << 0x91 << 0xA1 << 0xC0 << 0xD0; // outputs

 connect(data, SIGNAL(AddrChanged(int,int,int, QString)), this, SLOT(onAddrChanged(int,int,int, QString)));
 connect(data, SIGNAL(SVChanged(int,int,int, QString)), this, SLOT(onSVChanged(int,int,int, QString)));
 connect(data, SIGNAL(V1Changed(int,int,int, QString)), this, SLOT(onV1Changed(int,int,int, QString)));
 connect(data, SIGNAL(V2Changed(int,int,int, QString)), this, SLOT(onV2Changed(int,int,int, QString)));
 connect(data, SIGNAL(IOComplete(QList<int>*)), this, SLOT(OnIOComplete(QList<int>*)));
 connect(data, SIGNAL(IOCompleteX2(QList<int>*)), this, SLOT(OnIOComplete(QList<int>*)));
 connect(data, SIGNAL(IOCompleteServo()), this, SLOT(OnIOComplete()));
 if(type == SERVO)
 {
  connect(data, SIGNAL(ServoP1Changed(int,int,int,QString)), this, SLOT(onServoValuesChanged(int,int,int,QString)));
  connect(data, SIGNAL(ServoP2Changed(int,int,int,QString)), this, SLOT(onServoValuesChanged(int,int,int,QString)));
  connect(data, SIGNAL(ServoSpeedChanged(int,int,int,QString)), this, SLOT(onServoValuesChanged(int,int,int,QString)));
 }
}
void RegistersWidget::setValues()
{
 if(bSetting)
  return;
 int addr = data->getAddr(channel);
 int config = data->getSV(channel);
 ui->btnEditVal->setEnabled(config >0);
 int val1 = data->getV1(channel);
 int val2 = data->getV2(channel);
 ui->edAddr->setText(QString("%1%2").arg("").arg(addr,0,10));
 ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssWhite));
 ui->edCfg->setText(QString("%1%2").arg(nbrPrefix).arg(config,0,nbrFormat));
 ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssGreen));
 ui->edVal1->setText(QString("%1%2").arg(nbrPrefix).arg(val1,0,nbrFormat));
 ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssGreen));
 ui->edVal2->setText(QString("%1%2").arg(nbrPrefix).arg(val2,0,nbrFormat));
 ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssGreen));



}

RegistersWidget::~RegistersWidget()
{
 delete ui;
}

void RegistersWidget::on_btnRead_clicked()
{
 iState = 0;
 setCursor(Qt::WaitCursor);
 data->readValues(channel);
 //data->setDirty(channel, false);
}

void RegistersWidget::OnIOComplete(QList<int>*)
{
 int iServo = channel-4;
 switch(iState)
 {
 case 0:
  iState = 1;
  data->readValues(channel+16);
  //data->setDirty(channel+16, false);
  break;
 case 1:
  iState = 2;
  data->readX2Values(channel);
 //data->setX2Dirty(channel+32, false);
  break;
 case 2:
  if(type == SERVO && (iServo >=0 && iServo < 8))
  {
   iState = 3;
   data->readServoValues(iServo);
  }
  else
  {
   iState = -1;
  }
  break;
 default:
 case 3:
  iState = -1;
  break;
 case 10:
  iState = 11;
  qDebug()<<QString("channel %1 0x%2").arg(channel+16).arg(data->getSV(channel+16),0,nbrFormat);
  data->writeValues(channel+16);
  break;
 case 11:
  iState = 12;
  data->writeX2Values(channel);
  break;
 case 12:
  if(channel == 0 && this->type == SPECIAL)
  {
   iState = 13;
   data->writeValues(channel+1);
  }
  else if(SERVO && (iServo >=0 && iServo < 8))
  {
   iState = 20;
   data->writeServoValues(iServo);
  }
  else
   iState=-1;
  break;
 case 13:
  iState = 14;
  data->writeValues(channel+2);
  break;
 case 14:
  iState = 15;
  data->writeValues(channel+3);
  break;
 case 15:
  iState = 16;
  data->writeValues(channel+1 +16);
 case 16:
  iState = 17;
  data->writeValues(channel+2 +16);
 case 17:
  iState = 18;
  data->writeX2Values(channel+1 );
 case 18:
  iState = 19;
  data->writeX2Values(channel+2 );
  break;
 case 19:
  if(SERVO)
  {
   iState = 0;
   if(SERVO && (iServo >=0 && iServo < 8))
   {
    data->readServoValues(iServo);
    break;
   }
  }
  iState=-1;
  break;
 }
 if(iState == -1)
     setCursor(Qt::ArrowCursor);
}

void RegistersWidget::on_btnWrite_clicked()
{
 iState = 10;
 setCursor(Qt::WaitCursor);
 data->writeValues(channel);
}

int RegistersWidget::decodeText(QLineEdit *ctl)
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

void RegistersWidget::on_edAddr_editingFinished()
{
 if(bSetting)
  return;
 // 1-2048 for points and switches
 // 1-4096 for blocks
 int config = data->getSV(channel);
 int newAddr = decodeText(ui->edAddr);
 if(config == 0x1f || config == 0x5f || config == 0xc0 || config == 0xd0)
 {
  if(newAddr <1 || newAddr > 4096) // block number ranges
  {
   ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
   return;
  }
 }
 else
 {
  if(newAddr < 1 || newAddr > 2048)
  {
   ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
   return;
  }
 }
 //ui->edAddr->setPalette(*data->pWhite);
 /*int currV2 =*/ data->getV2(channel);
// int currCfg = data->getSV(channel);
 //data->setAddr(channel,val,data->ssWhite);
 LocoIOMode* lim = data->getLIM(channel);
// LocoIOModeList l;
// if(lim  != NULL)
//   data->setV1(channel, l->addressToValue1(lim,val),data->ssWhite);
// else
//  data->setV1(channel, (val-1)/2,data->ssWhite);
// int newV2=0;
// switch(currCfg)
// {
// case 0x1b: // 27
// case 0x1F: // 31
//   if(val&1)  // odd address
//     newV2 = 0x10; // 16
//   else
//     newV2  = 0x30; // 48
//   break;
// case 0x5b: // 91
// case 0x5F: // 95
//   if(val&1)  // odd address
//    newV2 = 0x00; // 00
//   else
//    newV2  = 0x20; // 32
//   break;
//  default:
//    goto exit;
// }
// if(newV2 != currV2)
// {
////  if(lim  != NULL)
////   data->setV2(channel, l.addressToValue2(lim,newV2),data->ssWhite);
////  else
//   data->setV2(channel,newV2, data->ssWhite);
// }
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 data->setAddr(channel,newAddr,data->ssWhite);

 /*exit:*/ return;
}
void RegistersWidget::on_edCfg_editingFinished()
{
 if(bSetting)
  return;
 if(ui->edCfg->isReadOnly())
  return;
 int config = data->getSV(channel);
 int val = decodeText(ui->edCfg);
 if(val == config)
  return;
 if(val < 1 || val >= 0xFF)
 {
  ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
  return;
 }
 QList<int> validCVs;
 validCVs <<0x07<<0x0f<<0x17<<0x1f<<0x27<<0x2f<<0x37<<0x5f<<0x60<<0xf5<<0x67<<0x6f
         <<0x80<<0xB0<<0x81<<0xB1<<0x88<<0x8c<<0x90<<0xa0<<0x91<<0xa1<<0xC0<<0xd0;
 if(!validCVs.contains(config))
 {
  ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
  return;
 }
 //ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssWhite));
 data->setSV(channel,val,data->ssWhite);
}
void RegistersWidget::on_edVal1_editingFinished()
{
 if(bSetting)
  return;
 if(ui->edVal1->isReadOnly())
  return;
 int val = decodeText(ui->edVal1);
 if(val < 1 || val >= 256)
 {
  ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
  return;
 }
 //ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssWhite));
 data->setV1(channel, val,data->ssWhite);
 data->setAddr(channel, val+1,data->ssWhite);
}
void RegistersWidget::on_edVal2_editingFinished()
{
 if(bSetting)
  return;
 if(ui->edVal2->isReadOnly())
  return;
 int val = decodeText(ui->edVal2);
 if(val < 1 || val >= 256)
 {
  ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
  return;
 }
 //ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssWhite));
 data->setV2(channel,val,data->ssWhite);
}
void RegistersWidget::onPropertyChange(QString propertyName, QVariant oldVal, QVariant newVal)
{
 Q_UNUSED(oldVal)
 if(propertyName == "PortChange" && newVal.toInt()==channel)
 {
  setValues();
 }
}
void RegistersWidget::onAddrChanged(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
 if(this->channel == channel)
 {
  bSetting = true;
  ui->edAddr->setText(QString("%1%2").arg("").arg(iNew,0,10));
  if(type == SERVO &&(channel >=4 && channel < 12))
  {
   if(checkDups(channel-4,iNew))
    ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
   else
    ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssBlueGreen));
  }
  else
   ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
  bSetting = false;

  labelCheck(channel);
 }
}
void RegistersWidget::labelCheck(int channel)
{

 LocoIOModeList* modelist = data->getLocoIOModeList();
 LocoIOMode* mode = modelist->getLocoIOModeFor(data->getSV(channel), data->getV1(channel), data->getV2(channel));
 if(mode != NULL && (mode->getOpcode() == LnConstants::OPC_INPUT_REP))
 {
  Manager* mgr = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->mgrs->at(0);
  QStringList l = mgr->getSystemNameList();
  QString heading = QString::number(port);
  foreach (QString s, l)
  {
   QString text = ui->edAddr->text();
   if(s.mid(2) == text)
   {
    heading = s;
    break;
   }
  }
  emit name(channel, heading);
 }
 else if(mode != NULL && (mode->getOpcode() == LnConstants::OPC_SW_REQ))
 {
  Manager* mgr = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->mgrs->at(0);
  QStringList l = mgr->getSystemNameList();
  Manager* mgr2 = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->mgrs->at(0);
  QStringList l2 = mgr2->getSystemNameList();
  foreach (QString s, l2)
  {
   l.append(s);
  }
  QString heading = QString::number(port);
  foreach (QString s, l)
  {
   QString text = ui->edAddr->text();
   if(s.mid(2) == text)
   {
    heading = s;
    break;
   }
  }
  emit name(channel, heading);
 }
}

void RegistersWidget::onSVChanged(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
 if(this->channel == channel)
 {
     if(iNew == 0xd0)
     {
      int v = iOld;
     }
  bSetting = true;
  ui->edCfg->setText(QString("%1%2").arg(nbrPrefix).arg(iNew,0,nbrFormat));
  ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
  data->setLIM(channel);
  LocoIOMode* lim = data->getLIM(channel);
  QString mode = "<None>";
  if(lim != NULL)
   mode = data->getLIM(channel)->getMode();
  data->setMode(channel,mode);
  if(type == SERVO && channel >=4 && channel < 12)
  {
   int p1 = data->getServoP1(channel-4);
   int p2 = data->getServoP2(channel-4);
   int speed = data->getServoSpeed(channel-4);
   QString tip;
   if(speed < 4)
    tip = QString(tr("Servo, pos1 = %1, pos2=%2, speed=%3").arg(p1).arg(p2).arg(speed));
   else
    tip = QString(tr("Alternating Servo, pos1 = %1, pos2=%2, speed=%3").arg(p1).arg(p2).arg(speed));
    setToolTip(tip);
  }
  else
   setToolTip(mode);
  ui->btnEditVal->setEnabled(iNew > 0);
  if(iNew == 0)
  {
   ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssPurple));
   ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssPurple));
   bSetting = false;
   return;
  }
  switch(type)
  {
  case NORMAL:
   if(!validNormalCfg.contains(iNew))
    ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
   break;
  case SERVO:
   if(iNew != 0x80)
    ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
   break;
  case SPECIAL:
   switch(iNew)
   {
   case 44:
    if(channel == 0)
     break;
   case 45:
    if(channel == 1)
     break;
   case 46:
    if(channel == 2)
     break;
   case 0x82:
   case 0xc2:
    if(channel == 3)
     break;
   default:
    ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
    break;
   }
   break;
  case BOOSTER_IN:
   if(iNew == 0x1F )
    break;
   ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
   break;
  case BOOSTER_OUT:
   if( iNew == 0x81 )
    break;
   ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
  default:
   ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(data->ssRed));
  }
 }
 bSetting = false;
 //checkSpecialPorts(channel, iNew);
}
void RegistersWidget::onV1Changed(int channel, int iOld, int iNew, QString ss)
{
    Q_UNUSED(iOld)
 if(this->channel == channel)
 {
  bSetting = true;
  ui->edVal1->setText(QString("%1%2").arg(nbrPrefix).arg(iNew,0,nbrFormat));
  ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
  bSetting = false;
 }
}
void RegistersWidget::onV2Changed(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
 if(this->channel == channel)
 {
  bSetting = true;
  if(ss != data->ssGreen && channel == 14)
      qDebug() << "break";
  ui->edVal2->setText(QString("%1%2").arg(nbrPrefix).arg(iNew,0,nbrFormat));
  ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
  bSetting = false;
 }
}
bool RegistersWidget::displayFormat() {return bHexDisplay;}
void RegistersWidget::setHexDisplay(bool bHex)
{
 if(bHex == bHexDisplay) return;
 bHexDisplay = bHex;
 nbrFormat = bHex?16:10;
 nbrPrefix = bHex?"0x":"";
 bSetting = true;
 int addr = data->getAddr(channel);
 int sv = data->getSV(channel);
 int v1 = data->getV1(channel);
 int v2 = data->getV2(channel);
// ui->edAddr->setText(QString("%1%2").arg("").arg(decodeText(ui->edAddr),0,10));
// ui->edCfg->setText(QString("%1%2").arg(nbrPrefix).arg(decodeText(ui->edCfg),0,nbrFormat));
// ui->edVal1->setText(QString("%1%2").arg(nbrPrefix).arg(decodeText(ui->edVal1),0,nbrFormat));
// ui->edVal2->setText(QString("%1%2").arg(nbrPrefix).arg(decodeText(ui->edVal2),0,nbrFormat));
 ui->edAddr->setText(QString("%1%2").arg("").arg(addr,0,10));
 ui->edCfg->setText(QString("%1%2").arg(nbrPrefix).arg(sv,0,nbrFormat));
 ui->edVal1->setText(QString("%1%2").arg(nbrPrefix).arg(v1,0,nbrFormat));
 ui->edVal2->setText(QString("%1%2").arg(nbrPrefix).arg(v2,0,nbrFormat));
 bSetting = false;
}
void RegistersWidget::onAllowEdit(bool bChecked)
{
 ui->edCfg->setReadOnly(!bChecked);
 ui->edVal1->setReadOnly(!bChecked);
 ui->edVal2->setReadOnly(!bChecked);
 bAllowEdit = bChecked;
}
void RegistersWidget::on_btnEditVal_clicked()
{
 if(data->getSV(channel)==0)
  return;
 TurnoutDlg dlg(data, channel);
 if(dlg.exec() == QDialog::Accepted)
 {
  data->setV1(channel, dlg.getV1(), data->ssWhite);
  data->setV2(channel, dlg.getV2(), data->ssWhite);
 }
}
//void RegistersWidget::setServo(bool bServo)
//{
// this->bServo = bServo;
//}
bool RegistersWidget::checkDups(int iServo, int thisAddr)
{
 QList<int> addresses;
 for(int i = 4; i < 12; i++)
 {
  addresses << data->getAddr(i);
 }
 for(int i=0; i<8; i++)
 {
  if(i == iServo || addresses[i] == 0)
   continue;
  if(addresses.at(i) == thisAddr)
   return true;
 }
 return false;
}
//void RegistersWidget::checkSpecialPorts(int channel, int value)
//{
// if(channel == 0 && value == 44)
// {
//  bSpecialPorts = true;
// }
// else
// {
//  bSpecialPorts = false;
// }
//void RegistersWidget::setSpecialPort()
//{
// bSpecialPorts =true;
// if( channel >= 0 && channel < 4)
// {
//  if(channel > 0)
//   ui->btnWrite->setEnabled(false);
//  ui->edAddr->setReadOnly(true);
//  ui->edCfg->setReadOnly(true);
//  ui->edVal1->setReadOnly(true);
//  ui->edVal2->setReadOnly(true);
//  ui->btnEditVal->setEnabled(false);
//  //ui->btnEditVal->setVisible(false);
// }
//}
void RegistersWidget::setPortType(portType type)
{
 this->type = type;
 switch(this->type)
 {
 case SPECIAL:
  if( channel >= 0 && channel < 4)
  {
   if(channel > 0)
    ui->btnWrite->setEnabled(false);
   ui->edAddr->setReadOnly(true);
   ui->edCfg->setReadOnly(true);
   ui->edVal1->setReadOnly(true);
   ui->edVal2->setReadOnly(true);
   ui->btnEditVal->setEnabled(false);
       //ui->btnEditVal->setVisible(false);
   break;
   }
 default:
  ui->btnWrite->setEnabled(true);
  ui->edAddr->setReadOnly(false);
  ui->edCfg->setReadOnly(false);
  ui->edVal1->setReadOnly(false);
  ui->edVal2->setReadOnly(false);
  ui->btnEditVal->setEnabled(true);
  break;
 }
}
void RegistersWidget::setSpecialPort()
{
 //setPortType(SPECIAL);
}
void RegistersWidget::onServoValuesChanged(int iServo, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iServo)
 Q_UNUSED(iOld)
 Q_UNUSED(iNew)
 Q_UNUSED(ss)

 int p1 = data->getServoP1(channel-4);
 int p2 = data->getServoP2(channel-4);
 int speed = data->getServoSpeed(channel-4);
 QString tip;
 if(speed < 4)
  tip = QString(tr("Servo, pos1 = %1, pos2=%2, speed=%3").arg(p1).arg(p2).arg(speed));
 else
  tip = QString(tr("Alternating Servo, pos1 = %1, pos2=%2, speed=%3").arg(p1).arg(p2).arg(speed));
 setToolTip(tip);
}
void RegistersWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
