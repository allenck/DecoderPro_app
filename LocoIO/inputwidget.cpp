#include "inputwidget.h"
#include "ui_inputwidget.h"
#include "llnmon.h"

InputWidget::InputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QButtonGroup* group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputWidget)
{
 ui->setupUi(this);
 Q_ASSERT(port >=1 && port <=16);
 this->data = data;
 this->port = port;
 //this->packetizer = packetizer;
 this->tc = tc;
 channel = port-1;
 bSettingValues = false;
 ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssLtBlue));
 ui->edStatus->setEnabled(false);
 group->addButton(ui->rbNotUsed);
 group->addButton(ui->rbBlockDetectionActiveHigh);
 group->addButton(ui->rbBlockDetectionActiveLow);
 group->addButton(ui->rbToggleSwitch);
 group->addButton(ui->rbPushButtonActiveLow);
 group->addButton(ui->rbPushButtonActiveHigh);
 group->addButton(ui->rbSwitchPointFeedback);
 group->addButton(ui->rbContact1PointFeedback);
 group->addButton(ui->rbContact2PointFeedback);
 group->addButton(ui->rbDoubleInput);
 data->setLIM(channel);
 if(port & 1) //Odd or even?
 {
  ui->lblDoubleInputDisabled->setVisible(true);
  ui->rbDoubleInput->setVisible(false);
  ui->rbDoubleInput->setDisabled(true);
 }
 else
 {
  ui->lblDoubleInputDisabled->setVisible(false);
  ui->rbDoubleInput->setVisible(true);
  ui->rbDoubleInput->setDisabled(false);
 }

 //setValues();
 //connect(data, SIGNAL(firePropertyChange(QString,QVariant,QVariant)), this, SLOT(onPropertyChange(QString,QVariant,QVariant)));
 connect(data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));
 connect(tc, SIGNAL(messageProcessed(LocoNetMessage*,bool)), this, SLOT(onMessageReceived(LocoNetMessage*,bool)));
}

void InputWidget::resetControls()
{
 ui->rbNotUsed->setChecked(false);
// ui->rbBlockDetectionActiveLow->setChecked(false);
// ui->rbBlockDetectionActiveHigh->setChecked(false);
 ui->chkBlockDetectionDelay->setChecked(false);
// ui->rbToggleSwitch->setChecked(false);
// ui->rbPushButtonActiveLow->setChecked(false);
// ui->rbPushButtonActiveHigh->setChecked(false);
 ui->chkDirectControl->setChecked(false);
// ui->rbSwitchPointFeedback->setChecked(false);
// ui->rbContact1PointFeedback->setChecked(false);
// ui->rbContact2PointFeedback->setChecked(false);
 qApp->processEvents();
}

void InputWidget::setValues()
{
 bSettingValues = true;
 int config = data->getSV(channel);
 int val1 = data->getV1(channel);
 int val2 = data->getV2(channel);
 Q_UNUSED(val1);
 Q_UNUSED(val2);
 resetControls();

// if(!(port& 0x1) &&((data->getSV(channel-1)< 0x80)&& ((data->getSV(channel-1) !=0))))
// {
//  ui->rbDoubleInput->setEnabled(true);
//  //ui->edStatus->setPalette(*data->pGray);
//  ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssGray));
// }
 //if((data->getSV(channel-1)< 0x80)&& ((data->getSV(channel-1) !=0)))
 if((data->getSV(channel)< 0x80)&& ((data->getSV(channel) !=0)))
 {
  if(!(port &0x01)) // odd or even?
  {
   ui->rbDoubleInput->setEnabled(true);
   ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssGray));
  }
  else
   ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssGray));
 }
 else
  ui->rbDoubleInput->setEnabled(false);
 ui->rbNotUsed->setChecked(false);
 if(config >= 0x80) // is Output?
 {
  bSettingValues = false;
  ui->edStatus->setEnabled(false);
  return;
 }
 ui->edStatus->setEnabled(true);
 //emit isInput(port);  // reset all outout controls
 ui->chkDirectControl->setChecked(false);

 switch(config)
 {
 // not used
 case 0:
     ui->rbNotUsed->setChecked(true);
     ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssLtBlue));
     break;
 // Inputs
 case 0x07:
  if(val2 == 0x10)
  {
   ui->rbToggleSwitch->setChecked(true); // "Toggle Switch, Indirect Control"
   ui->chkDirectControl->setEnabled(true);
   break;
  }
  break;
 case 0x0f:
  if(val2 == 0x00)
  {
   ui->rbToggleSwitch->setChecked(true); // Toggle Switch, LocoIO 1.3.2
   ui->chkDirectControl->setEnabled(false);
   break;
  }
  if(val2 == 0x10)
  {
   ui->rbToggleSwitch->setChecked(true); // "Toggle Switch, Direct Control"
   ui->chkDirectControl->setEnabled(true);
   ui->chkDirectControl->setChecked(true);
   break;
  }
  break;
 case 0x17:
  if(val2 == 0x70 | val2 == 0x71)
  {
   ui->rbSwitchPointFeedback->setChecked(true); // Turnout Feedback, single sensor"
   ui->chkDirectControl->setEnabled(false);
   break;
  }
  break;
 case 0x1f:
 case 0x1b:
  if((val2 &0x10) == 0x10)
  {
   ui->rbBlockDetectionActiveLow->setChecked(true);    // "Block Detector, Active Low"
   ui->chkDirectControl->setEnabled(false);
   ui->chkBlockDetectionDelay->setChecked((!(config&0x04)));
   break;
  }
  break;
 case 0x27:
  if(val2 == 0x10)
  {
   ui->rbPushButtonActiveLow->setChecked(true);  // Push Button, Active Low, Indirect Control
   ui->chkDirectControl->setChecked(false);
   ui->chkDirectControl->setEnabled(true);
   break;
  }
  break;
 case 0x2f:
  if(val2 == 0x10)
  {
   ui->rbPushButtonActiveLow->setChecked(true);  //Push Button, Active Low, Direct Control
   ui->chkDirectControl->setChecked(true);
   ui->chkDirectControl->setEnabled(true);
   break;
  }
  break;
 case 0x37:
  if(val2 == 0x70 | val2 == 0x71)
  {
   ui->rbContact1PointFeedback->setChecked(true); // Turnout Feedback, dual sensor, #1"
   ui->chkDirectControl->setEnabled(false);
   break;
  }
  if(val2 == 0x60)
  {
   ui->rbContact2PointFeedback->setChecked(true); // Turnout Feedback, dual sensor, #2"
   ui->chkDirectControl->setEnabled(false);
   break;
  }
  break;
// case 0x3f:
//  ui->chkDirectControl->setChecked(true);
//  break;
 case 0x5f:
 case 0x5b:
  if(val2 == 0x00 || val2 == 0x20)
  {
   ui->chkDirectControl->setChecked(false);
   ui->rbBlockDetectionActiveHigh->setChecked(true); // "Block Detector, Active High "
   ui->chkDirectControl->setEnabled(false);
   ui->chkBlockDetectionDelay->setChecked((!(config&0x04)));
   break;
  }
  break;
 case 0x3f:             // double input
  ui->chkDirectControl->setChecked(false);
  ui->chkDirectControl->setEnabled(false);
  ui->rbDoubleInput->setChecked(true);
  break;
 case 0x67:
  if(val2 == 0x00)
  {
   ui->rbPushButtonActiveHigh->setChecked(true); // Push Button, Active High, Indirect
   ui->chkDirectControl->setEnabled(true);
   break;
  }
  break;
 case 0x6f:
  if(val2 == 0x00)
  {
   ui->chkDirectControl->setChecked(true);
   ui->rbPushButtonActiveHigh->setChecked(true); // "Push Button, Active High, Direct
   ui->chkDirectControl->setEnabled(true);
   break;
  }
  if(val2 == 0x10)
  {
   ui->rbPushButtonActiveHigh->setChecked(true);
   ui->chkDirectControl->setEnabled(true);
   break;
  }
  break;
 default:
  break;
 }
 if((port & 1) && (ui->rbSwitchPointFeedback->isChecked()|| ui->rbContact1PointFeedback->isChecked() ||ui->rbContact2PointFeedback->isChecked()))
  setDoubleInputEnabled(channel+1, true);
 else
  setDoubleInputEnabled(channel+1, false);

 data->setLIM(channel);
 setToolTip(data->getMode(channel));
 bSettingValues = false;
}

InputWidget::~InputWidget()
{
    delete ui;
}
void InputWidget::onPropertyChange(QString propertyName, QVariant oldVal, QVariant newVal)
{
 Q_UNUSED(oldVal)
 if(propertyName == "PortChange" && channel == newVal.toInt())
 {
  if(data->getSV(channel)>= 0xB0)
  {
   resetControls();
   return;
  }
  setValues();
 }
}
void InputWidget::onSVChanged(int channel, int iOld, int iNew,QString ss)
{
 Q_UNUSED(iOld)
 Q_UNUSED(iNew)
 Q_UNUSED(ss)
 if(this->channel == channel)
 {
  if(bSettingValues) {return;}
  bSettingValues = true;
  resetControls();
  setValues();
 }
}

void InputWidget::on_rbNotUsed_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 data->setAddr(channel,0,data->ssWhite);
 data->setV1(channel,0, data->ssWhite);
 data->setV2(channel,0, data->ssWhite);
 data->setSV(channel,0, data->ssWhite);
 data->setV1(channel+16, 0, data->ssWhite); // set Extra opcodes 'not used'
 data->setV2(channel+16, 0, data->ssWhite);
 data->setSV(channel+16, 0, data->ssWhite);
 data->setX2V1(channel, 0, data->ssWhite); // set Extra2 opcodes 'not used'
 data->setX2V2(channel, 0, data->ssWhite);
 data->setX2SV(channel, 0, data->ssWhite);

}

void InputWidget::on_rbBlockDetectionActiveHigh_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 ui->chkDirectControl->setEnabled(false);
 ui->chkBlockDetectionDelay->setEnabled(true);
 bSettingValues = true;
 data->setV2(channel,0x00, data->ssWhite);
 if(!ui->chkBlockDetectionDelay->isChecked())
  data->setSV(channel, 0x5f, data->ssWhite); // no delay
 else
   data->setSV(channel, 0x5B, data->ssWhite); // w/delay

 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::on_rbBlockDetectionActiveLow_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 ui->chkDirectControl->setEnabled(false);
 ui->chkBlockDetectionDelay->setEnabled(true);
 bSettingValues = true;
 data->setV2(channel,0x10, data->ssWhite);
 if(!ui->chkBlockDetectionDelay->isChecked())
  data->setSV(channel, 0x1F, data->ssWhite);
 else
   data->setSV(channel, 0x1B, data->ssWhite);
 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::on_rbToggleSwitch_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x10, data->ssWhite);
 if(ui->chkDirectControl->isChecked())
  data->setSV(channel, 0x0F, data->ssWhite);
 else
  data->setSV(channel, 0x07, data->ssWhite);
 ui->chkDirectControl->setEnabled(true);
 ui->chkBlockDetectionDelay->setEnabled(false);
 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::on_rbPushButtonActiveHigh_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x00, data->ssWhite);
 if(ui->chkDirectControl->isChecked())
  data->setSV(channel, 0x6F, data->ssWhite);
 else
  data->setSV(channel, 0x67, data->ssWhite);
 ui->chkDirectControl->setEnabled(true);
 ui->chkBlockDetectionDelay->setEnabled(false);
 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::on_rbPushButtonActiveLow_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x10, data->ssWhite);
 if(ui->chkDirectControl->isChecked())
  data->setSV(channel, 0x2F, data->ssWhite);
 else
  data->setSV(channel, 0x27, data->ssWhite);
 ui->chkDirectControl->setEnabled(true);
 ui->chkBlockDetectionDelay->setEnabled(false);
 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::on_chkDirectControl_toggled(bool bChecked)
{
 if(bSettingValues) {return;}
 int config = data->getSV(channel);
 if(config == 0x0f || config == 0x07) // toggle switch
 {
   bSettingValues = true;
   if(bChecked)
    data->setSV(channel, 0x0F, data->ssWhite);
   else
    data->setSV(channel, 0x07, data->ssWhite);
   bSettingValues = false;
  return;
 }
 if(config == 0x6f || config == 0x67) // Push Button Active high
 {
  bSettingValues = true;
  if(bChecked)
   data->setSV(channel, 0x6F, data->ssWhite);
  else
   data->setSV(channel, 0x67, data->ssWhite);
  bSettingValues = false;
  return;
 }
 if(config == 0x2f || config == 0x27) // Push Button Active high
 {
   bSettingValues = true;
  if(bChecked)
   data->setSV(channel, 0x2F, data->ssWhite);
  else
   data->setSV(channel, 0x27, data->ssWhite);
  bSettingValues = false;
  return;
 }
 ui->chkDirectControl->setEnabled(false);
 ui->chkDirectControl->setChecked(false);
}
void InputWidget::on_rbSwitchPointFeedback_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x70, data->ssWhite);
 data->setSV(channel, 0x17, data->ssWhite);
 ui->chkDirectControl->setEnabled(false);
 ui->chkDirectControl->setChecked(false);
 ui->chkBlockDetectionDelay->setEnabled(false);
 ui->chkBlockDetectionDelay->setChecked(false);
 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::on_rbContact1PointFeedback_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x70, data->ssWhite);
 data->setSV(channel, 0x37, data->ssWhite);
 ui->chkDirectControl->setEnabled(false);
 ui->chkDirectControl->setChecked(false);
 ui->chkBlockDetectionDelay->setEnabled(false);
 ui->chkBlockDetectionDelay->setChecked(false);
 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::on_rbContact2PointFeedback_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 data->setV2(channel,0x60, data->ssWhite);
 data->setSV(channel, 0x37, data->ssWhite);
 ui->chkDirectControl->setEnabled(false);
 ui->chkDirectControl->setChecked(false);
 ui->chkBlockDetectionDelay->setEnabled(false);
 ui->chkBlockDetectionDelay->setChecked(false);
 LocoIOMode* lim = data->getLIM(channel);
 int newAddr = data->getAddr(channel);
 data->setV1(channel, lim, newAddr, data->ssWhite);
 data->setV2(channel,lim,newAddr, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::onMessageReceived(LocoNetMessage *msg, bool b)
{
 Q_UNUSED(b)
 QPalette p;
 int config = data->getSV(channel);
 if(config >= 0x80)
  return;
// LocoIOMode* mode = data->getLIM(channel);
// if(mode == NULL)
//  return;
// int opc = mode->getOpcode();
 int opc = 0;
 if(ui->rbDoubleInput->isChecked())
  return;
 if(ui->rbNotUsed->isChecked())
     return;
 if(!msg->checkParity()) return;
 int in1 = msg->getElement(1);
 int in2 = msg->getElement(2);
 QString sColor = "lightGray";
 if(msg->getOpCode()== LnConstants::OPC_INPUT_REP &&(ui->rbBlockDetectionActiveHigh->isChecked() || ui->rbBlockDetectionActiveLow->isChecked()))
 {
  opc = LnConstants::OPC_INPUT_REP;
  if(msg->getOpCode() != opc)
   return;
  int addr = ((LlnMon::SENSOR_ADR(in1,in2)-1)*2+((in2 & LnConstants::OPC_INPUT_REP_SW)!=0?2:1));
  if(addr != data->getAddr(channel)) return;
  if((in2 & LnConstants::OPC_SW_REP_HI) == 0)
   //p.setColor(QPalette::Base, Qt::red);
   sColor = data->ssRed;
  else
   //p.setColor(QPalette::Base, Qt::green);
   sColor = "green";
  ui->edStatus->setStyleSheet(QString("QLineEdit { background-color :  %1}").arg(sColor));
  return;
 }

 if(msg->getOpCode()== LnConstants::OPC_SW_REQ &&(ui->rbToggleSwitch->isChecked() || ui->rbPushButtonActiveHigh->isChecked()||ui->rbPushButtonActiveLow->isChecked()))
 {
   int sensor = LlnMon::SENSOR_ADR(in1, in2);
   if(sensor != data->getAddr(channel)) return;

   if((in2 & LnConstants::OPC_SW_REP_HI) == 0)
    //p.setColor(QPalette::Base, Qt::red);
    sColor = data->ssRed;
   else
    //p.setColor(QPalette::Base, Qt::green);
    sColor = "green";
   ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(sColor));
   return;
 }

  if((msg->getOpCode()== LnConstants::OPC_SW_REP) && (ui->rbSwitchPointFeedback->isChecked() || ui->rbContact1PointFeedback->isChecked() || ui->rbContact2PointFeedback->isChecked()))
  {
      int sensor = LlnMon::SENSOR_ADR(in1, in2);
      if(sensor != data->getAddr(channel)) return;

      if((in2 & LnConstants::OPC_SW_REP_HI) == 0)
       //p.setColor(QPalette::Base, Qt::red);
       sColor = "lightGray";
      else
       //p.setColor(QPalette::Base, Qt::green);
       sColor = "green";
      ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(sColor));
      return;
  }
}
void InputWidget::on_rbDoubleInput_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 //ui->edStatus->setPalette(*data->ssGray);
 if(bSettingValues) {return;}
 ui->edStatus->setStyleSheet(QString("QLineEdit {background-color : %1").arg(data->ssGray));
 bSettingValues = true;
 data->setAddr(channel, data->getAddr(channel-1), data->ssWhite);
 data->setV1(channel, data->getV1(channel-1),data->ssWhite);
 data->setV2(channel, 0, data->ssWhite);
 data->setSV(channel, 0x3f, data->ssWhite);
 ui->chkBlockDetectionDelay->setChecked(false);
 ui->chkBlockDetectionDelay->setEnabled(false);
 ui->chkBlockDetectionDelay->setChecked(false);
 ui->chkDirectControl->setEnabled(false);
 bSettingValues = false;
}
//bool InputWidget::event(QEvent *e)
//{
// if(e->type() == QEvent::ToolTip)
// {
//  data->setLIM(channel);
//  setToolTip(data->getMode(channel));
//  e->accept();
//  //return true;
// }
// return true;
//}
void InputWidget::on_chkBlockDetectionDelay_toggled(bool bChecked)
{
// if(bChecked)
//  return;
 if(bSettingValues) {return;}
 bSettingValues = true;
 int val = bChecked?0x0:04;
 data->setSV(channel, (data->getSV(channel)& 0xFB) | val, data->ssWhite);
 bSettingValues = false;
}
void InputWidget::setDoubleInputEnabled(int channel, bool b)
{
 if(this->channel != channel)
  return;
 if(data->getSV(channel) < 0x80)
  ui->rbDoubleInput->setEnabled(b);
}
void InputWidget::retranslateControls()
{
 ui->retranslateUi(this);
 setToolTip(data->getMode(channel));

}
