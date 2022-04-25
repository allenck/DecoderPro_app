#include "specialport.h"
#include "ui_specialport.h"
#include "lnconstants.h"
#include "instancemanager.h"
#include "abstractpowermanager.h"

SpecialPort::SpecialPort(LocoIOData* data, int port, LnTrafficController* tc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpecialPort)
{
 ui->setupUi(this);
 Q_ASSERT(port >=1 && port <=4);
 channel = port -1;
 this->data = data;
 this->tc = tc;
 bSettingValues = true;
 if(port == 4)
 {
  ui->rbOutput->setVisible(false);
  ui->lblOutput->setVisible(true);
  ui->lblInput->setVisible(false);
  ui->rbInput->setVisible(false);
  if(data->getSV(channel) != 194)
  {
   data->setAddr(channel, 1, data->ssWhite);
   data->setV1(channel, 0, data->ssWhite);
   data->setV2(channel, 0, data->ssWhite);
   data->setSV(channel, 194, data->ssWhite);
  }
  else
   ui->rbOutput->setChecked(true);
 }
 else   // Ports 1-3
 {
  ui->rbOutput->setVisible(false);
  ui->lblOutput->setVisible(false);
  ui->lblInput->setVisible(true);
  ui->rbInput->setVisible(true);
  if(data->getSV(channel) != 44 + channel)
  {
   data->setAddr(channel, 1, data->ssWhite);
   data->setV1(channel, 0, data->ssWhite);
   data->setV2(channel, 0, data->ssWhite);
   data->setSV(channel, 44 + channel, data->ssWhite);
  }
//  else
//   ui->rbInput->setChecked(true);
 }
 switch(port)
 {
 case 1:
  ui->lblInput->setText("I\nD\nL\nE\n");
  ui->lblInput->setStyleSheet("QLabel { background-color : pink; color : black; }");
  break;
 case 2:
  ui->lblInput->setText("G\nO\n");
  ui->lblInput->setStyleSheet("QLabel { background-color : green; color : black; }");
  break;
 case 3:
  ui->lblInput->setText("S\nT\nO\nP\n");
  ui->lblInput->setStyleSheet("QLabel { background-color : red; color : black; }");
  break;
 case 4:
  ui->lblOutput->setText("S\nT\nA\nT\nU\nS\n");
  switch( ((AbstractPowerManager*)InstanceManager::getDefault("PowerManager"))->getPower())
  {
  case PowerManager::ON:
   ui->lblOutput->setStyleSheet("QLabel { background-color : green; color : black; }");
      break;
  case PowerManager::OFF:
      ui->lblOutput->setStyleSheet("QLabel { background-color : yellow; red : black; }");
      break;
  default:
  ui->lblOutput->setStyleSheet("QLabel { background-color : yellow; color : black; }");
  break;
  }
 }
 bSettingValues = false;
 connect(data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSvChanged(int,int,int, QString)));
}

SpecialPort::~SpecialPort()
{
 delete ui;
}
void SpecialPort::setStatus(QString ss)
{
 ui->lblOutput->setStyleSheet(QString("QLabel { background-color : %1; color : black; }").arg(ss));
}

void SpecialPort::on_rbInput_toggled(bool bChecked)
{
 Q_UNUSED(bChecked)
 if(bSettingValues)
  return;
 data->setAddr(channel, 1, data->ssWhite);
 data->setV1(channel, 0, data->ssWhite);
 data->setV2(channel, 0, data->ssWhite);
 data->setSV(channel, 44 + channel, data->ssWhite);
}

void SpecialPort::on_rbOutput_toggled(bool bChecked)
{
 Q_UNUSED(bChecked)
 if(bSettingValues)
  return;
 data->setAddr(channel, 1, data->ssWhite);
 data->setV1(channel, 0, data->ssWhite);
 data->setV2(channel, 0, data->ssWhite);
 data->setSV(channel, 194, data->ssWhite);
}
void SpecialPort::onSvChanged(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
 Q_UNUSED(ss)
 bSettingValues = true;
 if(this->channel == channel)
 {
  if(channel >=0 && channel < 3 && iNew == channel+44)
   ui->rbInput->setChecked(true);
  if(channel ==3 && (iNew == 0x82 || iNew == 0xc2))
   ui->rbOutput->setChecked(true);
 }
 bSettingValues = false;
}

void SpecialPort::retranslateControls()
{
 ui->retranslateUi(this);
}

void SpecialPort::resetControls()
{
    qApp->processEvents();

}

void SpecialPort::setValues()
{
    bSettingValues = true;
    //int config = data->getSV(channel);
    int val1 = data->getV1(channel);
    int val2 = data->getV2(channel);
    Q_UNUSED(val1);
    Q_UNUSED(val2);
    resetControls();
    switch(channel)
    {
     case 0:
     {
        LocoNetMessage* msg = new LocoNetMessage(2);
        msg->setOpCode(LnConstants::OPC_IDLE);
        tc->sendLocoNetMessage(msg);
        break;
     }
    }
    data->setLIM(channel);
    setToolTip(data->getMode(channel));
    bSettingValues = false;
}

void SpecialPort::onMessageReceived(LocoNetMessage* msg, bool /*b*/)
{
    int op = msg->getOpCode();
    switch(op)
    {
    case LnConstants::OPC_GPON:
        ui->lblOutput->setStyleSheet(QString("QLineEdit { background-color :  %1}").arg("green"));
        break;
    case LnConstants::OPC_GPOFF:
    case LnConstants::OPC_IDLE:
        ui->lblOutput->setStyleSheet(QString("QLineEdit { background-color :  %1}").arg("red"));
        break;
    }
}
