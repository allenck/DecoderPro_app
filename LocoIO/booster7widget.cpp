#include "booster7widget.h"
#include "ui_booster7widget.h"
#include "powermanager.h"
#include "instancemanager.h"
#include "lnconstants.h"
#include "lnturnout.h"
#include "proxyturnoutmanager.h"

Booster7Widget::Booster7Widget(LocoIOData* data, int port, /*LnPacketizer* packetizer*/LnTrafficController* tc,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Booster7Widget)
{
    ui->setupUi(this);
    this->data = data;
    this->port = port;
    channel = port-1;
    //this->packetizer = packetizer;
    this->tc = tc;
#if 1
    switch( ((PowerManager*)InstanceManager::getDefault("PowerManager"))->getPower())
    {
    case PowerManager::ON:
    {
     //ui->edStatus->setStyleSheet("QLabel { background-color : lightGreen; color : black; }");
     LocoNetMessage* msg = new LocoNetMessage(2);
     msg->setOpCode(LnConstants::OPC_GPON);
     tc->sendLocoNetMessage(msg);
     break;
    }
    case PowerManager::OFF:
        ui->edStatus->setStyleSheet("QLabel { background-color : yellow; red : black; }");
        break;
    default:
        ui->edStatus->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    break;
    }
#endif
    ui->edStatus->setStyleSheet("QLineEdit { background-color : yellow; }");

    Turnout* t =(Turnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getBySystemName("LT"+QString::number(data->getAddr(channel)));
    if(t)
    {
     switch(t->getKnownState())
     {
      case LnTurnout::THROWN:
         ui->edStatus->setStyleSheet("QLineEdit { background-color : lightGreen;  }");
         break;
     case LnTurnout::CLOSED:
         ui->edStatus->setStyleSheet("QLineEdit { background-color : lightGreen; }");
         break;
     default:
         ui->edStatus->setStyleSheet("QLineEdit { background-color : yellow;}");
         break;
     }
    }
    connect(this->tc, SIGNAL(messageProcessed(LocoNetMessage*,bool)), this, SLOT(onMessageReceived(LocoNetMessage*,bool)));
    connect(data, SIGNAL(SVChanged(int,int,int,QString)), this, SLOT(onSVChanged(int,int,int,QString)));
}

Booster7Widget::~Booster7Widget()
{
    delete ui;
}

void Booster7Widget::onMessageReceived(LocoNetMessage *msg, bool /*b*/)
{
    int op = msg->getOpCode();
    switch(op)
    {
    case LnConstants::OPC_GPON:
        ui->edStatus->setStyleSheet(QString("QLineEdit { background-color :  %1}").arg("lightGreen"));
        break;
    case LnConstants::OPC_GPOFF:
    case LnConstants::OPC_IDLE:
        ui->edStatus->setStyleSheet(QString("QLineEdit { background-color :  %1}").arg("red"));
        break;
    }
}

void Booster7Widget::onSVChanged(int /*channel*/, int /*iOld*/, int /*iNew*/, QString /*ss*/)
{

}
