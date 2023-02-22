#include "boosteroutputwidget.h"
#include "lntrafficcontroller.h"
#include "ui_boosteroutputwidget.h"

BoosterOutputWidget::BoosterOutputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoosterOutputWidget)
{
 ui->setupUi(this);
 this->data = data;
 this->port = port;
 //this->packetizer = packetizer;
 this->tc  = tc;
 channel = port-1;
 ui->label_2->setVisible(true);
 ui->tbPower->setVisible(false);
 connect(this->data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));

}

BoosterOutputWidget::~BoosterOutputWidget()
{
 delete ui;
}
void BoosterOutputWidget::on_rb1On_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues)
  return;
 bSettingValues = true;
  data->setSV(channel, 0x81,data->ssWhite);
  bSettingValues = false;
}
void BoosterOutputWidget::on_rb1Off_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues)
  return;
 bSettingValues = true;
 data->setV2(channel,0x10, data->ssWhite);
  data->setSV(channel, 0x80,data->ssWhite);
  bSettingValues = false;
}

void BoosterOutputWidget::on_rb2On_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues)
  return;
 bSettingValues = true;
 data->setV2(channel,0x30, data->ssWhite);
 data->setSV(channel, 0x81,data->ssWhite);
 bSettingValues = false;
}

void BoosterOutputWidget::on_rb2Off_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues)
  return;
 bSettingValues = true;
 data->setV2(channel,0x30, data->ssWhite);
 data->setSV(channel,0x80,data->ssWhite);
 bSettingValues = false;
}
void BoosterOutputWidget::onSVChanged(int channel, int iOld, int iNew,QString ss)
{
    Q_UNUSED(iOld)
    Q_UNUSED(iNew)
 if(this->channel == channel)
 {
 if(ss== data->ssGreen)
 {
  ui->label_2->setVisible(false);
  ui->tbPower->setVisible(true);
 }
 else
 {
  ui->label_2->setVisible(true);
  ui->tbPower->setVisible(false);
 }
 setValues(ss);
 }
}
void BoosterOutputWidget::resetControls()
{
 qApp->processEvents();
}

void BoosterOutputWidget::setValues(QString ss)
{
    Q_UNUSED(ss)
 bSettingValues = true;
 int config = data->getSV(channel);
 int val1 = data->getV1(channel);
 int val2 = data->getV2(channel);
 resetControls();
 if(config < 0x80)
 {
  bSettingValues = false;
  return;
 }
// ui->chkBlinking->setChecked((config & 0x10) !=0);
 //ui->chk4WayPort->setChecked((config & 0x20) !=0);

 switch(config)
 {
 case 0x80:
 //case 0xB0:
//  ui->chk4WayPort->setEnabled(true);
//  ui->chk4WayPort->setChecked((config & 0x20) !=0);
  if((val2 & 0x30) == 0x10)
  {
   ui->rb1Off->setChecked(true); // Steady State, single output, Off at Power up
   break;
  }
//  if((val2 & 0x30) == 0x30)
//  {
//   ui->rb2Off->setChecked(true); // Steady State, paired output, Off at Power up
//   break;
//  }
  data->setAddr(channel, 100, data->ssWhite);
  break;
 case 0x81:
 //case 0xB1:
//  ui->chk4WayPort->setEnabled(true);
//  ui->chk4WayPort->setChecked((config & 0x20) !=0);
  if((val2 & 0x30) == 0x10)
  {
   ui->rb1On->setChecked(true); // Steady State, single output, On at Power up
   break;
  }
//  if((val2 & 0x30) == 0x30)
//  {
//   ui->rb2On->setChecked(true); // Steady State, paired output, On at Power up
//   break;
//  }
  data->setAddr(channel, 100, data->ssWhite);
  break;
 default:
  break;
 }

 data->setLIM(channel);
 setToolTip(data->getMode(channel));
 bSettingValues = false;
}

void BoosterOutputWidget::on_tbPower_clicked()
{
 QString btnText = ui->tbPower->text();
 LocoNetMessage* msg = new LocoNetMessage(4);
 msg->setOpCode(LnConstants::OPC_SW_REQ);
 msg->setElement(1, data->getV1(channel));
 //msg->setElement(2, data->getV2(channel)|(btnText==QString("On")?0x10:0x30));
 msg->setElement(2, (btnText==QString("On")?0x10:0x30));
 //packetizer->sendLocoNetMessage(msg);
 tc->sendLocoNetMessage(msg);

 //SleeperThread::msleep(1000);

 LocoNetMessage* msg2 = new LocoNetMessage(4);
 msg2->setOpCode(LnConstants::OPC_SW_REQ);
 msg2->setElement(1, data->getV1(channel));
 //msg2->setElement(2, (data->getV2(channel) ^ 0x10)|(btnText==QString("On")?0x00:0x20));
 msg2->setElement(2, (btnText==QString("On")?0x00:0x20));
 //packetizer->sendLocoNetMessage(msg2);
 tc->sendLocoNetMessage(msg2);

 if(btnText == "On")
  ui->tbPower->setText("Off");
 else
  ui->tbPower->setText("On");
}

void BoosterOutputWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
