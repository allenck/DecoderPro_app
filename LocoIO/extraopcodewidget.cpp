#include "extraopcodewidget.h"
#include "ui_extraopcodewidget.h"
#include <QPainter>

ExtraOpcodeWidget::ExtraOpcodeWidget(LocoIOData* data, int port, int extra, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtraOpcodeWidget)
{
 ui->setupUi(this);
 this->data = data;
 this->port = port;
 this->extra = extra;
 Q_ASSERT(extra>0 && extra < 3);
 if(extra == 1)
  channel = port-1 + 16;
 else
  channel = port-1;
 //channelMax = channel+15;
 channelBase = port-1;
 bHexDisplay = true;
 nbrFormat=16;
 nbrPrefix = "0x";
 bSetting = true;

 group = new QButtonGroup(this);
 group2 = new QButtonGroup(this);
 group->addButton(ui->rbOff);
 group->addButton(ui->rbDirect);
 group->addButton(ui->rbIndirect);
 group2->addButton(ui->rbContact1);
 group2->addButton(ui->rbContact2);
 if(this->extra == 1)
 {
  connect(this->data, SIGNAL(AddrChanged(int,int,int,QString)), this, SLOT(onAddrChanged(int,int,int,QString)));
  connect(this->data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));
  connect(this->data, SIGNAL(V1Changed(int,int,int,QString)), this, SLOT(onV1Changed(int,int,int,QString)));
  connect(this->data, SIGNAL(V2Changed(int,int,int,QString)), this, SLOT(onV2Changed(int,int,int,QString)));
 }
 else
 {
  connect(this->data, SIGNAL(X2AddrChanged(int,int,int,QString)), this, SLOT(onAddrChanged(int,int,int,QString)));
  connect(this->data, SIGNAL(X2SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));
  connect(this->data, SIGNAL(X2V1Changed(int,int,int,QString)), this, SLOT(onV1Changed(int,int,int,QString)));
  connect(this->data, SIGNAL(X2V2Changed(int,int,int,QString)), this, SLOT(onV2Changed(int,int,int,QString)));
 }
 ui->rbOff->setVisible(false);
 ui->rbDirect->setVisible(false);
 ui->rbIndirect->setVisible(false);
 ui->rbContact1->setVisible(false);
 ui->rbContact2->setVisible(false);
 ui->edAddr->setVisible(false);
 ui->edCfg->setVisible(false);
 ui->edVal1->setVisible(false);
 ui->edVal2->setVisible(false);
 ui->lblBigRedX->setVisible(true);
 if(this->extra == 1)
 {
  this->setStyleSheet("QWidget {background : rgb(137,255,236); font-size : 7pt; }");
  ui->lblBigRedX->setStyleSheet("QLabel {background : rgb(137,255,236); font-size : 24pt; }");
  }
 else
 {
  this->setStyleSheet("QWidget {background : rgb(255,170,127); font-size : 7pt; }");
  ui->lblBigRedX->setStyleSheet("QLabel {background : rgb(255,170,127); font-size : 24pt; }");
 }
 bSetting = false;
}

ExtraOpcodeWidget::~ExtraOpcodeWidget()
{
 delete ui;
}
void ExtraOpcodeWidget::onAddrChanged(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
 if(this->channel == channel)
 {
  if(data->getSV(channelBase) >= 0x80 || data->getSV(channelBase)==0)
   return;  // base channel is output

  ui->edAddr->setText(QString("%1%2").arg(nbrPrefix).arg(iNew,0,nbrFormat));
  //ui->edAddr->setPalette(*p);
  ui->edAddr->setStyleSheet(QString("QLineEdit { background : %1; }").arg(ss));
 }
}
void ExtraOpcodeWidget::onSVChanged(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
// if(extra == 2 && channel == 0)
//     qDebug() << QString("extra2 channel %1").arg(channel);
 //if(channel == channelBase && ((iNew >= 0x80) || (iNew == 0)))
 int cfg = data->getSV(channelBase);
 if(this->channel == channel && (cfg >= 0x80 || cfg ==0))
 {
  // base channel is output or not used
  ui->rbOff->setVisible(false);
  ui->rbDirect->setVisible(false);
  ui->rbIndirect->setVisible(false);
  ui->rbContact1->setVisible(false);
  ui->rbContact2->setVisible(false);
  ui->edAddr->setVisible(false);
  ui->edCfg->setVisible(false);
  ui->edVal1->setVisible(false);
  ui->edVal2->setVisible(false);
  ui->lblBigRedX->setVisible(true);
  return;
 }

 if(extra == 1 && channel < 16)
   return;
 if(this->channel != channel)
   return;
 if(this->channel == channel)
 {
  bSetting = true;
  if(data->getSV(channelBase) >= 0x80 || data->getSV(channelBase)==0)
    return;  // base channel is output
  ui->edCfg->setText(QString("%1%2").arg(nbrPrefix).arg(iNew,0,nbrFormat));
  ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
//  if(data->getSV(channelBase)< 0x80)
//  {
//   ui->rbOff->setChecked(true);
//   ui->rbContact1->setChecked(false);
//   ui->rbContact2->setChecked(false);
//   ui->edAddr->setEnabled(false);
//   ui->edCfg->setEnabled(false);
//   ui->edVal1->setEnabled(false);
//   ui->edVal2->setEnabled(false);
//  }
//  else
  //{
   ui->edAddr->setEnabled(true);
   ui->edCfg->setEnabled(true);
   ui->edVal1->setEnabled(true);
   ui->edVal2->setEnabled(true);
   if(iNew == 0xB0)
    ui->rbDirect->setChecked(true);
   if(iNew == 0xB1)
    ui->rbIndirect->setChecked(true);

   ui->rbOff->setVisible(true);
   ui->rbDirect->setVisible(true);
   ui->rbIndirect->setVisible(true);
   ui->rbContact1->setVisible(true);
   ui->rbContact2->setVisible(true);
   ui->edAddr->setVisible(true);
   ui->edCfg->setVisible(true);
   ui->edVal1->setVisible(true);
   ui->edVal2->setVisible(true);
   ui->lblBigRedX->setVisible(false);
  //}
   bSetting = false;
 }
}
void ExtraOpcodeWidget::onV1Changed(int channel, int iOld, int iNew, QString ss)
{
    Q_UNUSED(iOld)
 if(this->channel == channel)
 {
  if(data->getSV(channelBase) >= 0x80 || data->getSV(channelBase)==0)
   return;  // base channel is output
  bSetting = true;
  ui->edVal1->setText(QString("%1%2").arg(nbrPrefix).arg(iNew,0,nbrFormat));
  ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
  bSetting = false;
 }
}
void ExtraOpcodeWidget::onV2Changed(int channel, int iOld, int iNew, QString ss)
{
    Q_UNUSED(iOld)
 if(this->channel == channel)
 {
  if(data->getSV(channelBase) >= 0x80 || data->getSV(channelBase)==0)
   return;  // base channel is output

  bSetting = true;
  ui->edVal2->setText(QString("%1%2").arg(nbrPrefix).arg(iNew,0,nbrFormat));
  ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1; }").arg(ss));
  if(iNew == 0x10)
   ui->rbContact1->setChecked(true);
  if(iNew == 0x30)
   ui->rbContact2->setChecked(true);
  bSetting = false;
 }
}
void ExtraOpcodeWidget::on_rbOff_toggled(bool bChecked)
{
 if(bSetting) {return;}
 if(!bChecked)
 {
  if(data->getSV(channelBase)>= 0x80)
  {
   ui->rbOff->setChecked(true);
   return;
  }
  ui->edAddr->setEnabled(true);
  ui->edCfg->setEnabled(true);
  ui->edVal1->setEnabled(true);
  ui->edVal2->setEnabled(true);
  return;
 }
 if(extra == 1)
 {
  data->setAddr(channel, 0, data->ssWhite);
  data->setSV(channel,0, data->ssWhite);
  data->setV1(channel,0, data->ssWhite);
  data->setV2(channel, 0, data->ssWhite);
 }
 else
 {
  data->setX2Addr(channel, 0, data->ssWhite);
  data->setX2SV(channel,0, data->ssWhite);
  data->setX2V1(channel,0, data->ssWhite);
  data->setX2V2(channel, 0, data->ssWhite);
 }
 ui->edAddr->setEnabled(false);
 ui->edCfg->setEnabled(false);
 ui->edVal1->setEnabled(false);
 ui->edVal2->setEnabled(false);

}
void ExtraOpcodeWidget::on_rbDirect_toggled(bool bChecked)
{
 if(bSetting) {return;}
 if(!bChecked)
  return;
 if(extra == 1)
  data->setSV(channel,0xB0, data->ssWhite);
 else
  data->setX2SV(channel,0xB0, data->ssWhite);

}
void ExtraOpcodeWidget::on_rbIndirect_toggled(bool bChecked)
{
 if(bSetting) {return;}
 if(!bChecked)
  return;
 if(extra == 1)
 data->setSV(channel,0xB1, data->ssWhite);
else
 data->setX2SV(channel,0xB1, data->ssWhite);
}
void ExtraOpcodeWidget::on_rbContact1_toggled(bool bChecked)
{
 if(bSetting) {return;}
 if(!bChecked)
  return;
 if(extra == 1)
  data->setV2(channel,0x10, data->ssWhite);
 else
  data->setX2V2(channel,0x10, data->ssWhite);
}
void ExtraOpcodeWidget::on_rbContact2_toggled(bool bChecked)
{
 if(bSetting) {return;}
 if(!bChecked)
  return;
 if(extra == 1)
  data->setV2(channel,0x30, data->ssWhite);
 else
  data->setX2V2(channel,0x30, data->ssWhite);
}
int ExtraOpcodeWidget::decodeText(QLineEdit *ctl)
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
void ExtraOpcodeWidget::on_edAddr_editingFinished()
{
 // 1-2048 for points and switches
 // 1-4096 for blocks
 int config = data->getSV(channel);
 int val = decodeText(ui->edAddr);
 if(config == 0x1f || config == 0x5f || config == 0xc0 || config == 0xd0)
 {
  if(val <1 || val > 4096)
  {
   ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssRed));
   return;
  }
 }
 else
 {
  if(val < 1 || val > 2048)
  {
   ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssRed));
   return;
  }
 }
 ui->edAddr->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssWhite));
 if(extra == 1)
 {
  data->setAddr(channel,val, data->ssWhite);
  data->setV1(channel, val-1, data->ssWhite);
 }
 else
 {
  data->setX2Addr(channel,val, data->ssWhite);
  data->setX2V1(channel, val-1, data->ssWhite);

 }
}
void ExtraOpcodeWidget::on_edCfg_editingFinished()
{
 int config;
 if(extra == 1)
  config = data->getSV(channel);
 else
  config = data->getX2SV(channel);
 int val = decodeText(ui->edCfg);
 if(val < 1 || val >= 0xFF)
 {
  ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssRed));
  return;
 }
 QList<int> validCVs;
 validCVs <<0xB0<<0xB1;
 if(!validCVs.contains(config))
 {
  ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssRed));
  return;
 }
 ui->edCfg->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssWhite));
 data->setSV(channel,val, data->ssWhite);
}
void ExtraOpcodeWidget::on_edVal1_editingFinished()
{
 int val = decodeText(ui->edVal1);
 if(val < 1 || val >= 256)
 {
  ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssRed));
  return;
 }
 ui->edVal1->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssWhite));
 if(extra == 1)
 {
  data->setV1(channel, val, data->ssWhite);
  data->setAddr(channel, val+1, data->ssWhite);
 }
 else
 {
  data->setX2V1(channel, val, data->ssWhite);
  data->setX2Addr(channel, val+1, data->ssWhite);
 }
}
void ExtraOpcodeWidget::on_edVal2_editingFinished()
{
 int val = decodeText(ui->edVal2);
 if(val < 1 || val >= 256)
 {
  ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssRed));
  return;
 }
 ui->edVal2->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssWhite));
 if(extra == 1)
  data->setV2(channel,val, data->ssWhite);
 else
  data->setX2V2(channel,val, data->ssWhite);
}
bool ExtraOpcodeWidget::displayFormat() {return bHexDisplay;}
void ExtraOpcodeWidget::setHexDisplay(bool bHex)
{
 if(bHex == bHexDisplay) return;
 bHexDisplay = bHex;
 nbrFormat = bHex?16:10;
 nbrPrefix = bHex?"0x":"";
 ui->edAddr->setText(QString("%1%2").arg(nbrPrefix).arg(decodeText(ui->edAddr),0,nbrFormat));
 ui->edCfg->setText(QString("%1%2").arg(nbrPrefix).arg(decodeText(ui->edCfg),0,nbrFormat));
 ui->edVal1->setText(QString("%1%2").arg(nbrPrefix).arg(decodeText(ui->edVal1),0,nbrFormat));
 ui->edVal2->setText(QString("%1%2").arg(nbrPrefix).arg(decodeText(ui->edVal2),0,nbrFormat));
}
void ExtraOpcodeWidget::onAllowEdit(bool bChecked)
{
 ui->edCfg->setReadOnly(!bChecked);
 ui->edVal1->setReadOnly(!bChecked);
 ui->edVal2->setReadOnly(!bChecked);
}
void ExtraOpcodeWidget::paintEvent(QPaintEvent *)
{
 QStyleOption opt;
 opt.init(this);
 QPainter p(this);
 style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ExtraOpcodeWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
