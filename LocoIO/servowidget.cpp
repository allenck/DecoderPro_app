#include "servowidget.h"
#include "ui_servowidget.h"
#include <QSignalMapper>

ServoWidget::ServoWidget(LocoIOData* data, /*LnPacketizer* packetizer*/LnTrafficController* tc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServoWidget)
{
 ui->setupUi(this);
 this->data = data;
 //this->packetizer = packetizer;
 this->tc = tc;
 this->parent = parent;
 bHexDisplay = true;
 nbrFormat=16;
 nbrPrefix = "0x";
 bSetting = false;

 NotUsedButtons << ui->rbNotUsed1 << ui->rbNotUsed2 << ui->rbNotUsed3 << ui->rbNotUsed4 << ui->rbNotUsed5 << ui->rbNotUsed6  << ui->rbNotUsed7 << ui->rbNotUsed8;
 ServoButtons << ui->rbS1  << ui->rbS2 << ui->rbS3 << ui->rbS4 << ui->rbS5 << ui->rbS6 << ui->rbS7 << ui->rbS8;
 Pos1Labels << ui->lbl11 << ui->lbl12 << ui->lbl13 << ui->lbl14 << ui->lbl15 << ui->lbl16 << ui->lbl17 << ui->lbl18;
 Pos2Labels << ui->lbl21 << ui->lbl22 << ui->lbl23 << ui->lbl24 << ui->lbl25 << ui->lbl26 << ui->lbl27 << ui->lbl28;
 TestButtons << ui->btnTest1 << ui->btnTest2 << ui->btnTest3 << ui->btnTest4 << ui->btnTest5 << ui->btnTest6 << ui->btnTest7 << ui->btnTest8;
 CenterButtons << ui->btnCenter1 << ui->btnCenter2 << ui->btnCenter3 << ui->btnCenter4 << ui->btnCenter5 << ui->btnCenter6 << ui->btnCenter7 << ui->btnCenter8;

 Pos1SpinBoxes << ui->sbP11 << ui->sbP12 << ui->sbP13 << ui->sbP14 << ui->sbP15 << ui->sbP16 << ui->sbP17 << ui->sbP18;
 Pos2SpinBoxes << ui->sbP21 << ui->sbP22 << ui->sbP23 << ui->sbP24 << ui->sbP25 << ui->sbP26 << ui->sbP27 << ui->sbP28;
 SpeedSpinBoxes << ui->sbS1 << ui->sbS2 << ui->sbS3 << ui->sbS4 << ui->sbS5 << ui->sbS6 << ui->sbS7 << ui->sbS8;

 QSignalMapper* rbSignalMapper = new QSignalMapper(this);
 QSignalMapper* rbServoSignalMapper = new QSignalMapper(this);
 for(int i=0; i < NotUsedButtons.count(); i++)
 {
  rbSignalMapper->setMapping(NotUsedButtons[i],i);
  rbServoSignalMapper->setMapping(ServoButtons[i],i);
  connect(NotUsedButtons[i], SIGNAL(toggled(bool)), rbSignalMapper, SLOT(map()));
  connect(ServoButtons[i],SIGNAL(toggled(bool)), rbServoSignalMapper, SLOT(map()));
  NotUsedButtons[i]->setAutoExclusive(false);
  ServoButtons[i]->setAutoExclusive(false);
  NotUsedButtons[i]->setChecked(true);
 }
 connect(rbSignalMapper, SIGNAL(mapped(int)), this, SLOT(OnRbNotUsed_toggled(int)));
 connect(rbServoSignalMapper, SIGNAL(mapped(int)), this, SLOT(OnRbServo_toggled(int)));
 for(int i= 0; i < 8; i++)
  TestButtons[i]->setEnabled(false);
 for(int i= 0; i < 8; i++)
  CenterButtons[i]->setEnabled(false);
 for(int i= 0; i < 8; i++)
  Pos1SpinBoxes[i]->setEnabled(false);
 for(int i= 0; i < 8; i++)
  Pos2SpinBoxes[i]->setEnabled(false);
 for(int i= 0; i < 8; i++)
  SpeedSpinBoxes[i]->setEnabled(false);

 QSignalMapper* btnTestSignalMapper = new QSignalMapper(this);
 for(int i=0; i < TestButtons.count(); i++)
 {
  btnTestSignalMapper->setMapping(TestButtons[i],i);
  connect(TestButtons[i], SIGNAL(clicked(bool)), btnTestSignalMapper, SLOT(map()));
 }
 connect(btnTestSignalMapper, SIGNAL(mapped(int)), this, SLOT(OnTestButton_clicked(int)));

 QSignalMapper* btnCenterSignalMapper = new QSignalMapper(this);
 for(int i=0; i < CenterButtons.count(); i++)
 {
  btnCenterSignalMapper->setMapping(CenterButtons[i],i);
  connect(CenterButtons[i], SIGNAL(clicked(bool)), btnCenterSignalMapper, SLOT(map()));
 }
 connect(btnCenterSignalMapper, SIGNAL(mapped(int)), this, SLOT(OnCenterButton_clicked(int)));

 QSignalMapper* sbPos1SignalMapper = new QSignalMapper(this);
 for(int i=0; i < Pos1SpinBoxes.count(); i++)
 {
  sbPos1SignalMapper->setMapping(Pos1SpinBoxes[i],i);
  connect(Pos1SpinBoxes[i], SIGNAL(valueChanged(int)), sbPos1SignalMapper, SLOT(map()));
 }
 connect(sbPos1SignalMapper, SIGNAL(mapped(int)), this, SLOT(OnPos1_valueChanged(int)));

 QSignalMapper* sbPos2SignalMapper = new QSignalMapper(this);
 for(int i=0; i < Pos2SpinBoxes.count(); i++)
 {
  sbPos2SignalMapper->setMapping(Pos2SpinBoxes[i],i);
  connect(Pos2SpinBoxes[i], SIGNAL(valueChanged(int)), sbPos2SignalMapper, SLOT(map()));
 }
 connect(sbPos2SignalMapper, SIGNAL(mapped(int)), this, SLOT(OnPos2_valueChanged(int)));

 QSignalMapper* sbSpeedSignalMapper = new QSignalMapper(this);
 for(int i=0; i < SpeedSpinBoxes.count(); i++)
 {
  sbSpeedSignalMapper->setMapping(SpeedSpinBoxes[i],i);
  connect(SpeedSpinBoxes[i], SIGNAL(valueChanged(int)), sbSpeedSignalMapper, SLOT(map()));
 }
 connect(sbSpeedSignalMapper, SIGNAL(mapped(int)), this, SLOT(OnSpeed_valueChanged(int)));

 //connect(data, SIGNAL(AddrChanged(int,int,int,QString)), this, SLOT(onAddrChanged(int,int,int,QString)));
 connect(data, SIGNAL(ServoP1Changed(int,int,int,QString)), this, SLOT(onPos1Changed(int,int,int,QString)));
 connect(data, SIGNAL(ServoP2Changed(int,int,int,QString)), this, SLOT(onPos2Changed(int,int,int,QString)));
 connect(data, SIGNAL(ServoSpeedChanged(int,int,int,QString)), this, SLOT(onSpeedChanged(int,int,int,QString)));

 connect(data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));
 set4PositionServo(false);
}

ServoWidget::~ServoWidget()
{
 delete ui;
}
void ServoWidget::OnRbNotUsed_toggled(int iServo)
{
 if(bSetting)
  return;
 bSetting = true;
 setFields(iServo);
 if(b4PositionServo)
 {
  bSetting = false;
  if(iServo & 0x01 == 1)
  {
   NotUsedButtons[iServo-1]->setChecked(NotUsedButtons[iServo]->isChecked());
   setFields(iServo-1);
  }
  else
  {
   NotUsedButtons[iServo+1]->setChecked(NotUsedButtons[iServo]->isChecked());
   setFields(iServo+1);
  }
 }
 bSetting = false;
}
void ServoWidget::setFields(int iServo)
{
 int channel = iServo + 4;
 if(NotUsedButtons[iServo]->isChecked())
 {
  data->setAddr(channel, 1, data->ssWhite);
  data->setSV(channel, 0, data->ssWhite);
  data->setV1(channel, 0, data->ssPurple);
  data->setV2(channel, 0, data->ssPurple);

  data->setServoP1(iServo, 0, data->ssPurple);
  data->setServoP2(iServo, 0, data->ssPurple);
  data->setServoSpeed(iServo, 0, data->ssPurple);

  for(int i= 0; i < 8; i++)
   TestButtons[i]->setEnabled(false);
  for(int i= 0; i < 8; i++)
   CenterButtons[i]->setEnabled(false);
  for(int i= 0; i < 8; i++)
   Pos1SpinBoxes[i]->setEnabled(false);
  for(int i= 0; i < 8; i++)
   Pos2SpinBoxes[i]->setEnabled(false);
  for(int i= 0; i < 8; i++)
   SpeedSpinBoxes[i]->setEnabled(false);
  ServoButtons[iServo]->setChecked(false);
 }
 else
 {
  for(int i= 0; i < 8; i++)
  {
   TestButtons[i]->setEnabled(true);
   TestButtons[i]->setText("P1");
  }
  for(int i= 0; i < 8; i++)
   CenterButtons[i]->setEnabled(true);
  for(int i= 0; i < 8; i++)
   Pos1SpinBoxes[i]->setEnabled(true);
  for(int i= 0; i < 8; i++)
   Pos2SpinBoxes[i]->setEnabled(true);
  for(int i= 0; i < 8; i++)
   SpeedSpinBoxes[i]->setEnabled(true);
  data->setServoP1(iServo, 1, data->ssWhite);
  data->setServoP2(iServo, 127,data->ssWhite);
  data->setServoSpeed(iServo, 0, data->ssWhite);

  data->setAddr(channel, 1,data->ssWhite);
  data->setSV(channel, 0x80, data->ssWhite);
  data->setV1(channel, 0, data->ssWhite);
  data->setV2(channel, 0x10, data->ssWhite);

//  data->setV1(channel+16, 1, data->ssWhite);
//  data->setV2(channel+16, 127, data->ssWhite);
//  data->setSV(channel+16, 1, data->ssWhite);


  ServoButtons[iServo]->setChecked(true);
 }
 bSetting = false;
}
void ServoWidget::OnRbServo_toggled(int iServo)
{
 NotUsedButtons[iServo]->setChecked(!ServoButtons[iServo]->isChecked());
}

void ServoWidget::OnTestButton_clicked(int iServo)
{
 int channel = iServo + 4;
 QString btnText = TestButtons[iServo]->text();
 LocoNetMessage* msg = new LocoNetMessage(4);
 msg->setOpCode(LnConstants::OPC_SW_REQ);
 msg->setElement(1, data->getV1(channel));
 msg->setElement(2, data->getV2(channel)|(btnText==QString("P2")?0x10:0x30));
 //packetizer->sendLocoNetMessage(msg);
 tc->sendLocoNetMessage(msg);
 if(btnText == "P2")
  TestButtons[iServo]->setText("P1");
 else
  TestButtons[iServo]->setText("P2");
}
void ServoWidget::OnCenterButton_clicked(int iServo)
{
 QString ss = "white";
 Pos1SpinBoxes[iServo]->setValue(63);
 Pos1SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : %1; }").arg(ss));
 Pos2SpinBoxes[iServo]->setValue(64);
 Pos2SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : %1; }").arg(ss));

}
void ServoWidget::OnPos1_valueChanged(int iServo)
{
 if(bSetting)
  return;
 bSetting = true;
 if(iServo >= 0 && iServo < 8)
 {
  int iValue = Pos1SpinBoxes[iServo]->value();
  data->setServoP1(iServo, iValue, data->ssWhite);
 }
 bSetting = false;
}
void ServoWidget::OnPos2_valueChanged(int iServo)
{
 if(bSetting)
  return;
 bSetting = true;
 if(iServo >= 0 && iServo < 8)
 {
  int iValue = Pos2SpinBoxes[iServo]->value();
  data->setServoP2(iServo, iValue, data->ssWhite);
 }
 bSetting = false;
}
void ServoWidget::OnSpeed_valueChanged(int iServo)
{
 if(bSetting)
  return;
 bSetting = true;
 if(iServo >= 0 && iServo < 8)
 {
  int iValue = SpeedSpinBoxes[iServo]->value();
  data->setServoSpeed(iServo, iValue, data->ssWhite);
  if(iValue >= 4)
  {
   data->setServoP1(iServo, 1, data->ssWhite);
   data->setServoP2(iServo, 127, data->ssWhite);
  }
  validateValues(iServo);
 }
 bSetting = false;
}
void ServoWidget::onPos1Changed(int iServo, int /*iOld*/, int iNew, QString ss)
{
 //int iServo = channel-4-16;
 if(NotUsedButtons[iServo]->isChecked()) return;
 if(iServo >= 0 && iServo < 8)
 {
  bSetting = true;
  Pos1SpinBoxes[iServo]->setValue(iNew);
  Pos1SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : %1; }").arg(ss));
  bSetting = false;
  //validateValues(iServo);
 }
}
void ServoWidget::onPos2Changed(int iServo, int /*iOld*/, int iNew, QString ss)
{
 //int iServo = channel-4-16;
 if(NotUsedButtons[iServo]->isChecked()) return;
 if(iServo >= 0 && iServo < 8)
 {
  bSetting=true;
  Pos2SpinBoxes[iServo]->setValue(iNew);
  Pos2SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : %1; }").arg(ss));
  bSetting = false;
  //validateValues(iServo);
 }
}
void ServoWidget::onSpeedChanged(int iServo, int /*iOld*/, int iNew, QString ss)
{
 //int iServo = channel-4-16;
 if(NotUsedButtons[iServo]->isChecked()) return;
 if(iServo >= 0 && iServo < 8)
 {
  bSetting = true;
  SpeedSpinBoxes[iServo]->setValue(iNew);
  SpeedSpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : %1; }").arg(ss));
  if(iNew >= 4 && data->getServoP1(iServo) != 1)
   data->setServoP1(iServo, 1, data->ssWhite);
  bSetting = false;
  if(ss == data->ssGreen && data->getSV(iServo+4)>=0x80)
  {
   TestButtons[iServo]->setEnabled(true);
   CenterButtons[iServo]->setEnabled(true);
  }
  else
  {
   TestButtons[iServo]->setEnabled(false);
   CenterButtons[iServo]->setEnabled(false);
  }
  validateValues(iServo);
 }
}
void ServoWidget::onSVChanged(int channel, int iOld, int iNew, QString ss)
{
 Q_UNUSED(iOld)
 Q_UNUSED(iNew)
 Q_UNUSED(ss)
 if(bSetting)
  return;
 int iServo = channel -4;
 if(iServo >=0 && iServo < 8)
 {
  int sv = data->getSV(channel);
  if(sv == 0x80)
  {

   bSetting = true;
   ServoButtons[iServo]->setChecked(true);
   qDebug()<<QString("Servo %1 v1=%2, v2=%3, sv=%4").arg(iServo).arg(data->getV1(channel+16)).arg(data->getV2(channel+16)).arg(data->getSV(channel+16));
//   Pos1SpinBoxes[iServo]->setValue(data->getV1(channel+32));
//   Pos2SpinBoxes[iServo]->setValue(data->getV2(channel+32));
//   SpeedSpinBoxes[iServo]->setValue(data->getSV(channel+32));
   NotUsedButtons[iServo]->setChecked(false);
   Pos1SpinBoxes[iServo]->setEnabled(true);
   Pos2SpinBoxes[iServo]->setEnabled(true);
   SpeedSpinBoxes[iServo]->setEnabled(true);
  }
  else
  {
   NotUsedButtons[iServo]->setChecked(true);
   Pos1SpinBoxes[iServo]->setEnabled(false);
   Pos1SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : rgb(170, 170, 255);}"));
   Pos2SpinBoxes[iServo]->setEnabled(false);
   Pos2SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : rgb(170, 170, 255);}"));
   SpeedSpinBoxes[iServo]->setEnabled(false);
   SpeedSpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : rgb(170, 170, 255);}"));
  }
  bSetting = false;
  validateValues(iServo);
 }
}
void ServoWidget::set4PositionServo(bool bSet)
{
 b4PositionServo = bSet;
 for(int i=0; i < 8; i++)
 {
  ui->lblServo1->setVisible(!bSet);
  ui->lblServo2->setVisible(!bSet);
  Pos1Labels[i]->setVisible(bSet);
  Pos2Labels[i]->setVisible(bSet);
  if(i & 0x01)
  {
   SpeedSpinBoxes[i]->setEnabled(!bSet);
   SpeedSpinBoxes[i]->setVisible(!bSet);

  }
  else
  {

  }
  if(b4PositionServo)
   SpeedSpinBoxes[i]->setMaximum(3); // speed 0-3!
  else
   SpeedSpinBoxes[i]->setMaximum(5); // speed 0-5!
  validateValues(i);
 }
}

void ServoWidget::validateValues(int iServo)
{
 if(data->getSV(iServo + 4) == 0)
  return; // not used!

 //Pos2SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : rgb(170,255,127);}"));

 if((Pos1SpinBoxes[iServo]->value() > 1) &&  (SpeedSpinBoxes[iServo]->value()>=4))
  Pos1SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : red;}"));
 if(b4PositionServo && (SpeedSpinBoxes[iServo]->value()>=4))
  Pos1SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : red;}"));
 if((Pos1SpinBoxes[iServo]->value()) == (Pos2SpinBoxes[iServo]->value()))
 {
  Pos1SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : red;}"));
  Pos2SpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : red;}"));
 }
 if(b4PositionServo && (SpeedSpinBoxes[iServo]->value()>=4))
  SpeedSpinBoxes[iServo]->setStyleSheet(QString("QSpinBox { background-color : red;}"));
}

int ServoWidget::getColumn(int w, QPoint pt)
{
 Q_UNUSED(w)
 //QRect rect = ui->horizontalLayout->contentsRect();
 QPoint thisPt = mapFromParent(pt);
 int col = (thisPt.x()*8)/this->width();
 qDebug() << QString(" w= %1, pt.x=%2, thisPt=%3, col= %4").arg(this->width()).arg(pt.x()).arg(thisPt.x()).arg(col);
 return col;
}
void ServoWidget::retranslateControls()
{
 ui->retranslateUi(this);
}

void ServoWidget::setName(int col, QString s)
{
 if(col > 3 && col < 12)
  ServoButtons.at(col -4)->setText(s);
}
