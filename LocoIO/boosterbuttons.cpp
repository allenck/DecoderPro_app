#include "boosterbuttons.h"
#include "ui_boosterbuttons.h"
#include <QPushButton>

BoosterButtons::BoosterButtons(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoosterButtons)
{
    ui->setupUi(this);
    this->data = data;
    this->port = port;
    channel = port-1;
    //this->packetizer = packetizer;
    this->tc = tc;
    connect(this->tc, SIGNAL(messageProcessed(LocoNetMessage*,bool)), this, SLOT(onMessageReceived(LocoNetMessage*,bool)));
    connect(data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));
    connect(ui->goPushButton, SIGNAL(clicked()), this, SLOT(onGoClicked()));
    connect(ui->stopPushButton, SIGNAL(clicked()), this, SLOT(onStopClicked()));

}

BoosterButtons::~BoosterButtons()
{
    delete ui;
}

void BoosterButtons::onMessageReceived(LocoNetMessage */*msg*/, bool /*b*/)
{
}

void BoosterButtons::onSVChanged(int /*channel*/, int /*iOld*/, int /*iNew*/, QString /*ss*/)
{

}

void BoosterButtons::onGoClicked()
{
    LocoNetMessage* msg = new LocoNetMessage(2);
    msg->setOpCode(LnConstants::OPC_GPON);
    tc->sendLocoNetMessage(msg);

    ui->goPushButton->setStyleSheet("background-color: Green");
    ui->stopPushButton->setStyleSheet("background-color: rgb(184, 0, 0)");

}

void BoosterButtons::onStopClicked()
{
    LocoNetMessage* msg = new LocoNetMessage(2);
    msg->setOpCode(LnConstants::OPC_GPOFF);
    tc->sendLocoNetMessage(msg);

    ui->goPushButton->setStyleSheet("background-color: lightGreen");
    ui->stopPushButton->setStyleSheet("background-color: rgb(100, 0, 0)"); //rgb(248, 192, 192)

}
