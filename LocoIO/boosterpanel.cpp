#include "boosterpanel.h"
#include "ui_boosterpanel.h"
#include "lnconstants.h"
#include "loconetmessageinterpret.h"

BoosterPanel::BoosterPanel(LocoIOData* data, int port, LnTrafficController* tc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoosterPanel)
{
    ui->setupUi(this);
    this->data = data;
    this->port = port;
    //this->packetizer = packetizer;
    this->tc  = tc;
    channel = port-1;
    connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(onMessageReceived(LocoNetMessage*, bool)));

}

BoosterPanel::~BoosterPanel()
{
 delete ui;
}

void BoosterPanel::retranslateControls()
{
 ui->retranslateUi(this);
}

void BoosterPanel::onMessageReceived(LocoNetMessage * msg, bool)
{
 int in1 = msg->getElement(1);
 int in2 = msg->getElement(2);

 if(msg->getOpCode() == LnConstants::OPC_GPOFF)
 {
  ui->lblBoosterStatus->setText("STOP/IDLE mode");
  ui->lblBoosterStatus->setStyleSheet("QLabel {color:red}");
 }
 if(msg->getOpCode() == LnConstants::OPC_INPUT_REP)
 {
     int contactNum = ((LocoNetMessageInterpret::SENSOR_ADR(in1, in2) - 1) * 2 + ((in2 & LnConstants::OPC_INPUT_REP_SW) != 0 ? 2 : 1));
     int addr1 = data->getAddr(channel);
     if(contactNum != addr1)
         return;
     if(in2 & ((LnConstants::OPC_INPUT_REP_HI)==0))
     {
         ui->lblBoosterStatus->setText("Short circuit\nor\nWrong Railsync\nor\nNot connected to Loconet-B");
         ui->lblBoosterStatus->setStyleSheet("QLabel {color:red}");
     }
 }
}
