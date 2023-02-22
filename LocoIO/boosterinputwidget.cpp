#include "boosterinputwidget.h"
#include "ui_boosterinputwidget.h"
#include "loconetmessageinterpret.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include "lntrafficcontroller.h"

BoosterInputWidget::BoosterInputWidget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoosterInputWidget)
{
 ui->setupUi(this);
 this->data = data;
 this->port = port;
 channel = port-1;
 //this->packetizer = packetizer;
 this->tc = tc;
 connect(this->tc, SIGNAL(messageProcessed(LocoNetMessage*,bool)), this, SLOT(onMessageReceived(LocoNetMessage*,bool)));
 connect(data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));

 Sensor* sensor = (Sensor*)((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("LS"+QString::number(data->getAddr(channel)));
 if(sensor)
  ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg((sensor->getKnownState()==Sensor::ACTIVE) ? "black" : "yellow"));

}

BoosterInputWidget::~BoosterInputWidget()
{
    delete ui;
}
void BoosterInputWidget::on_rbBlockDetectionActiveLow_toggled(bool bChecked)
{
 if(!bChecked)
  return;
 if(bSettingValues)
  return;
// ui->chkDirectControl->setEnabled(false);
// ui->chkBlockDetectionDelay->setEnabled(true);
 data->setAddr(channel, 100, data->ssWhite);
 data->setV2(channel,0x10, data->ssWhite);
 data->setSV(channel, 0x1f, data->ssWhite);
}

void BoosterInputWidget::onMessageReceived(LocoNetMessage *msg, bool b)
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
// if(ui->rbDoubleInput->isChecked())
//  return;
 int in1 = msg->getElement(1);
 int in2 = msg->getElement(2);

 if(msg->getOpCode() == LnConstants::OPC_INPUT_REP)
 {
     int contactNum = ((LocoNetMessageInterpret::SENSOR_ADR(in1, in2) - 1) * 2 + ((in2 & LnConstants::OPC_INPUT_REP_SW) != 0 ? 2 : 1));
     int addr1 = data->getAddr(channel);
     if(contactNum != addr1)
         return;
     ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(in2 & ((LnConstants::OPC_INPUT_REP_HI) != 0)
             ? "black" : "yellow"));
 }

 if(ui->rbBlockDetectionActiveLow->isChecked() )
  opc = LnConstants::OPC_INPUT_REP;
 if(msg->checkParity())
 {
  if(msg->getOpCode() != opc)
   return;
  if(!(msg->getElement(1) == data->getV1(channel)))
  //if(msg->getElement(1)!= 0x31)
   return;
 }
// if(ui->rbNotUsed->isChecked())
//     return;
 if(ui->rbBlockDetectionActiveLow->isChecked())
 {
  if(msg->getElement(2) == 0x70)
   p.setColor(QPalette::Base, Qt::yellow);
  else
   p.setColor(QPalette::Base, Qt::black);
 }
 ui->edStatus->setPalette(p);
}

void BoosterInputWidget::onPropertyChange(QString propertyName, QVariant oldVal, QVariant newVal)
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
void BoosterInputWidget::onSVChanged(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
 Q_UNUSED(iNew)
 Q_UNUSED(ss)
 if(this->channel == channel)
 {
  resetControls();
  setValues();
 }
}
void BoosterInputWidget::resetControls()
{
 qApp->processEvents();
}

void BoosterInputWidget::setValues()
{
 bSettingValues = true;
 int config = data->getSV(channel);
 int val1 = data->getV1(channel);
 int val2 = data->getV2(channel);
 resetControls();

// if(!(port& 0x1) &&((data->getSV(channel-1)< 0x80)&& ((data->getSV(channel-1) !=0))))
// {
//  ui->rbDoubleInput->setEnabled(true);
//  //ui->edStatus->setPalette(*data->pGray);
//  ui->edStatus->setStyleSheet(QString("QLineEdit { background-color : %1}").arg(data->ssGray));
// }
// else
//  ui->rbDoubleInput->setEnabled(false);
// ui->rbNotUsed->setChecked(false);
 if(config >= 0x80)
 {
  bSettingValues = false;
  return;
 }
 //emit isInput(port);  // reset all outout controls
// ui->chkDirectControl->setChecked(false);

 switch(config)
 {
 // Inputs
// case 0x07:
//  if(val2 == 0x10)
//  {
//   ui->rbToggleSwitch->setChecked(true); // "Toggle Switch, Indirect Control"
//   ui->chkDirectControl->setEnabled(true);
//   break;
//  }
//  break;
// case 0x0f:
//  if(val2 == 0x00)
//  {
//   ui->rbToggleSwitch->setChecked(true); // Toggle Switch, LocoIO 1.3.2
//   ui->chkDirectControl->setEnabled(false);
//   break;
//  }
//  if(val2 == 0x10)
//  {
//   ui->rbToggleSwitch->setChecked(true); // "Toggle Switch, Direct Control"
//   ui->chkDirectControl->setEnabled(true);
//   ui->chkDirectControl->setChecked(true);
//   break;
//  }
//  break;
// case 0x17:
//  if(val2 == 0x70)
//  {
//   ui->rbSwitchPointFeedback->setChecked(true); // Turnout Feedback, single sensor"
//   ui->chkDirectControl->setEnabled(false);
//   break;
//  }
//  break;
 default:
 case 0x1f:
  if((val2 &0x10) == 0x10)
  {
   ui->rbBlockDetectionActiveLow->setChecked(true);    // "Block Detector, Active Low"
//   ui->chkDirectControl->setEnabled(false);
   data->setAddr(channel, 100, data->ssWhite);
   break;
  }
  break;
// case 0x27:
//  if(val2 == 0x10)
//  {
//   ui->rbPushButtonActiveLow->setChecked(true);  // Push Button, Active Low, Indirect Control
//   ui->chkDirectControl->setChecked(false);
//   ui->chkDirectControl->setEnabled(true);
//   break;
//  }
//  break;
// case 0x2f:
//  if(val2 == 0x10)
//  {
//   ui->rbPushButtonActiveLow->setChecked(true);  //Push Button, Active Low, Direct Control
//   ui->chkDirectControl->setChecked(true);
//   ui->chkDirectControl->setEnabled(true);
//   break;
//  }
//  break;
// case 0x37:
//  if(val2 == 0x70)
//  {
//   ui->rbContact1PointFeedback->setChecked(true); // Turnout Feedback, dual sensor, #1"
//   ui->chkDirectControl->setEnabled(false);
//   break;
//  }
//  if(val2 == 0x60)
//  {
//   ui->rbContact2PointFeedback->setChecked(true); // Turnout Feedback, dual sensor, #2"
//   ui->chkDirectControl->setEnabled(false);
//   break;
//  }
//  break;
// case 0x5f:
//  if(val2 == 0x00 || val2 == 0x20)
//  {
//   ui->chkDirectControl->setChecked(true);
//   ui->rbBlockDetectionActiveHigh->setChecked(true); // "Block Detector, Active High "
//   ui->chkDirectControl->setEnabled(false);
//   break;
//  }
//  break;
// case 0x63:             // double input
//  ui->chkDirectControl->setChecked(false);
//  ui->chkDirectControl->setEnabled(false);
//  ui->rbDoubleInput->setChecked(true);
//  break;
// case 0x67:
//  if(val2 == 0x00)
//  {
//   ui->rbPushButtonActiveHigh->setChecked(true); // Push Button, Active High, Indirect
//   ui->chkDirectControl->setEnabled(true);
//   break;
//  }
//  break;
// case 0x6f:
//  if(val2 == 0x00)
//  {
//   ui->chkDirectControl->setChecked(true);
//   ui->rbPushButtonActiveHigh->setChecked(true); // "Push Button, Active High, Direct
//   ui->chkDirectControl->setEnabled(true);
//   break;
//  }
//  if(val2 == 0x10)
//  {
//   ui->rbPushButtonActiveHigh->setChecked(true);
//   ui->chkDirectControl->setEnabled(true);
//   break;
//  }
//  break;
// default:
//  break;
 }
 data->setLIM(channel);
 setToolTip(data->getMode(channel));
 bSettingValues = false;
}
void BoosterInputWidget::retranslateControls()
{
 ui->retranslateUi(this);
}
