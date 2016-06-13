#include "specialport.h"
#include "ui_specialport.h"

SpecialPort::SpecialPort(LocoIOData* data, int port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpecialPort)
{
 ui->setupUi(this);
 Q_ASSERT(port >=1 && port <=4);
 channel = port -1;
 this->data = data;
 bSettingValues = true;
 if(port == 4)
 {
  ui->rbOutput->setVisible(true);
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
 else
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
  else
   ui->rbInput->setChecked(true);
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
  ui->lblOutput->setStyleSheet("QLabel { background-color : yellow; color : black; }");
  break;
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
