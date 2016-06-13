#include "outputwidget.h"
#include "ui_outputwidget.h"
#include "lnpacketizer.h"
#include "instancemanager.h"
#include "proxysensormanager.h"

OutputWidget::OutputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QButtonGroup* group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWidget)
{
 ui->setupUi(this);
 this->port = port;
 this->data = data;
 channel = port-1;
 bSettingValues = false;
 //this->packetizer = packetizer;
 this->tc = tc;
 group->addButton(ui->rbBlockOccupancy);
 group->addButton(ui->rb1On);
 group->addButton(ui->rb1Off);
 group->addButton(ui->rb2On);
 group->addButton(ui->rb2Off);
 group->addButton(ui->rb1SoftReset);
 group->addButton(ui->rb1HardReset);
 group->addButton(ui->rb2SoftReset);
 group->addButton(ui->rb2HardReset);

 connect(this->data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));
}
void OutputWidget::resetControls()
{
 ui->btnTest->setEnabled(false);
 ui->chkBlinking->setChecked(false);
 ui->chk4WayPort->setChecked(false);
 ui->chk4WayPort->setEnabled(true);

 qApp->processEvents();
}

void OutputWidget::setValues(QString ss)
{
 bSettingValues = true;
 int config = data->getSV(channel);
 int val1 = data->getV1(channel);
 int val2 = data->getV2(channel);
 resetControls();
 if(config < 0x80)
 {
  bSettingValues = false; // is an input
  return;
 }
 data->setV1(channel+16, 0, data->ssWhite); // set Extra opcodes 'not used'
 data->setV2(channel+16, 0, data->ssWhite);
 data->setSV(channel+16, 0, data->ssWhite);
 data->setX2V1(channel, 0, data->ssWhite); // set Extra2 opcodes 'not used'
 data->setX2V2(channel, 0, data->ssWhite);
 data->setX2SV(channel, 0, data->ssWhite);

 ui->chkBlinking->setChecked((config & 0x10) !=0);
 //ui->chk4WayPort->setChecked((config & 0x20) !=0);

 switch(config)
 {
 case 0x80:
 case 0xB0:
  ui->chk4WayPort->setEnabled(true);
  ui->chk4WayPort->setChecked((config & 0x20) !=0);
  if((val2 & 0x30) == 0x10)
  {
   ui->rb1Off->setChecked(true); // Steady State, single output, Off at Power up
   break;
  }
  if((val2 & 0x30) == 0x30)
  {
   ui->rb2Off->setChecked(true); // Steady State, paired output, Off at Power up
   break;
  }
  break;
 case 0x81:
 case 0xB1:
  ui->chk4WayPort->setEnabled(true);
  ui->chk4WayPort->setChecked((config & 0x20) !=0);
  if((val2 & 0x30) == 0x10)
  {
   ui->rb1On->setChecked(true); // Steady State, single output, On at Power up
   break;
  }
  if((val2 & 0x30) == 0x30)
  {
   ui->rb2On->setChecked(true); // Steady State, paired output, On at Power up
   break;
  }
  break;
 case 0x88:
  ui->chk4WayPort->setEnabled(false);
  if((val2 & 0x20) == 0x20)
  {
   ui->rb1SoftReset->setChecked(true); // Pulsed, software controlled on time, single output
   break;
  }
  if((val2 & 0x20) == 0)
  {
   ui->rb2SoftReset->setChecked(true); // Pulsed, software controlled on time, paired output
   break;
  }
  break;
 case 0x8C:
  ui->chk4WayPort->setEnabled(false);
  if((val2 & 0x20) == 0x20)
  {
   ui->rb1HardReset->setChecked(true); // Pulsed, firmware controlled on time, single output
   break;
  }
  if((val2 & 0x20) == 0)
  {
   ui->rb2HardReset->setChecked(true); // Pulsed, software controlled on time, paired output
   break;
  }
  break;
 case 0x90:
 case 0xA0:
  ui->chk4WayPort->setEnabled(true);
  ui->chk4WayPort->setChecked((config & 0x20) !=0);
  if((val2 & 0x30) == 0x10)
  {
   ui->rb1Off->setChecked(true); // Steady State, single output, Off at Power up, Blinking
   break;
  }
  if((val2 & 0x30) == 0x30)
  {
   ui->rb2Off->setChecked(true);
   break;
  }
  break;
 case 0x91:
 case 0xA1:
  ui->chk4WayPort->setEnabled(true);
  ui->chk4WayPort->setChecked((config & 0x20) !=0);
  if((val2 & 0x30) == 0x10)
  {
   ui->rb1On->setChecked(true);
   break;
  }
  if((val2 & 0x30) == 0x30)
  {
   ui->rb2On->setChecked(true);
   break;
  }
  break;
 case 0xC0:
  ui->chk4WayPort->setEnabled(false);
  //if(val2 == 0x00)
  {
   ui->rbBlockOccupancy->setChecked(true); // Block Occupied Indication
   break;
  }
  break;
 case 0xD0:
  ui->chk4WayPort->setEnabled(false);
  //if(val2 == 0x00)
  {
   ui->rbBlockOccupancy->setChecked(true); // Block Occupied Indication, Blinking
   break;
  }
  break;
 default:
  break;
 }
 ui->chk4WayPort->setChecked((config & 0x20) !=0);
 int v = config & 0x4c; // block detect & pulse
 //if((p == data->pGreen || p == data->pYellow) && v ==0)
 if((ss == data->ssGreen || ss == data->ssLightYellow) && v == 0)
  ui->btnTest->setEnabled(true);
 else
  ui->btnTest->setEnabled(false);

 data->setLIM(channel);
 setToolTip(data->getMode(channel));

 bSettingValues = false;
}

OutputWidget::~OutputWidget()
{
    delete ui;
}
void OutputWidget::on_btnTest_clicked()
{
 // generate an appropriate loconetmessage to trigger this output
 QString btnText = ui->btnTest->text();
 LocoIOModeList* modelist = data->getLocoIOModeList();
 LocoIOMode* mode = modelist->getLocoIOModeFor(data->getSV(channel), data->getV1(channel), data->getV2(channel));
 if(mode != 0)
 {
  switch (mode->getOpcode())
  {
  case LnConstants::OPC_INPUT_REP: // Block occupied
  {
   LocoNetMessage* msg = new LocoNetMessage(4);
   msg->setOpCode(LnConstants::OPC_INPUT_REP);
   msg->setElement(1, data->getAddr(channel));
   msg->setElement(2, data->getV2(channel)|(btnText==QString("On")?0x40:0x00));
   //packetizer->sendLocoNetMessage(msg);
   tc->sendLocoNetMessage(msg);
   if(btnText == "On")
    ui->btnTest->setText("Off");
   else
    ui->btnTest->setText("On");
   break;
  }
  case LnConstants::OPC_SW_REQ:    // switch
  {
   LocoNetMessage* msg = new LocoNetMessage(4);
   msg->setOpCode(LnConstants::OPC_SW_REQ);
   msg->setElement(1, data->getV1(channel));
   msg->setElement(2, data->getV2(channel)|(btnText==QString("On")?0x10:0x00));
   //packetizer->sendLocoNetMessage(msg);
   tc->sendLocoNetMessage(msg);
   if(btnText == "On")
    ui->btnTest->setText("Off");
   else
    ui->btnTest->setText("On");
   break;
  }
  default:
   break;
  }
 }
}
void OutputWidget::onSVChanged(int channel, int iOld, int iNew,QString ss)
{
 Q_UNUSED(iOld)
 Q_UNUSED(iNew)
 if(this->channel == channel)
 {
  bSettingValues = true;
  setValues(ss);
 }
}

void OutputWidget::on_rbBlockOccupancy_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 ui->chk4WayPort->setEnabled(false);
 data->setV2(channel,0x00, data->ssWhite);
 if(ui->chkBlinking->isChecked())
  data->setSV(channel, 0xd0,data->ssWhite);
 else
  data->setSV(channel, 0xc0,data->ssWhite);
 ui->chkBlinking->setEnabled(true);
 bSettingValues = false;
}
void OutputWidget::on_rb1On_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 bSettingValues = true;
 data->setV2(channel,0x10, data->ssWhite);
 if(!ui->chkBlinking->isChecked())
  data->setSV(channel, 0x81,data->ssWhite);
 else
  data->setSV(channel, 0x91,data->ssWhite);
 ui->btnTest->setText("On");
}
void OutputWidget::on_rb1Off_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 data->setV2(channel,0x10, data->ssWhite);
 if(!ui->chkBlinking->isChecked())
  data->setSV(channel, 0x80,data->ssWhite);
 else
  data->setSV(channel, 0x90,data->ssWhite);
 ui->chk4WayPort->setEnabled(true);
 ui->btnTest->setText("Off");
 bSettingValues = false;
}
void OutputWidget::on_rb2On_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x30, data->ssWhite);
 if(!ui->chkBlinking->isChecked())
  data->setSV(channel, 0x81,data->ssWhite);
 else
  data->setSV(channel, 0x91,data->ssWhite);
 ui->chk4WayPort->setEnabled(true);
 ui->btnTest->setText("On");
 bSettingValues = false;
}
void OutputWidget::on_rb2Off_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x30, data->ssWhite);
 if(!ui->chkBlinking->isChecked())
  data->setSV(channel, 0x80,data->ssWhite);
 else
  data->setSV(channel,0x90,data->ssWhite);
 ui->chk4WayPort->setEnabled(true);
 ui->btnTest->setText("Off");
 bSettingValues = false;
}
void OutputWidget::on_rb1SoftReset_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 bSettingValues = true;
 ui->chk4WayPort->setEnabled(false);
 data->setV2(channel, 0x20,data->ssWhite);
 data->setSV(channel, 0x88,data->ssWhite);
 bSettingValues = false;
}
void OutputWidget::on_rb1HardReset_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 ui->chk4WayPort->setEnabled(false);
 data->setV2(channel, 0x20,data->ssWhite);
 data->setSV(channel, 0x8c,data->ssWhite);
 bSettingValues = false;
}
void OutputWidget::on_rb2SoftReset_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 ui->chk4WayPort->setEnabled(false);
 data->setV2(channel, 0x00,data->ssWhite);
 data->setSV(channel, 0x88,data->ssWhite);
 bSettingValues = false;
}
void OutputWidget::on_rb2HardReset_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 ui->chk4WayPort->setEnabled(false);
 data->setV2(channel, 0x00,data->ssWhite);
 data->setSV(channel, 0x8c,data->ssWhite);
 bSettingValues = false;
}
void OutputWidget::on_chkBlinking_toggled(bool bChecked)
{
 if(bSettingValues)
  return;
 int config = data->getSV(channel);
 if(bChecked)
  config = config | 0x10;
 else
  config = config & 0xef;
 bSettingValues = true;
 data->setSV(channel, config,data->ssWhite);
 bSettingValues = false;
}
void OutputWidget::on_chk4WayPort_toggled(bool bChecked)
{
 if(bSettingValues)
  return;
 int config = data->getSV(channel);

 // 4 way bit is 0x20
 int val = config & 0xDF;
 if(bChecked)
  val |= 0x20;
 bSettingValues = true;
 data->setSV(channel, val, data->ssWhite);
 bSettingValues = false;
}
void OutputWidget::retranslateControls()
{
 ui->retranslateUi(this);
 setToolTip(data->getMode(channel));
}
