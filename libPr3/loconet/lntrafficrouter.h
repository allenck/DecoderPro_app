#ifndef LNTRAFFICROUTER_H
#define LNTRAFFICROUTER_H
#include "lntrafficcontroller.h"

class LnTrafficRouter : public LnTrafficController
{
 Q_OBJECT
public:
 QT_DEPRECATED LnTrafficRouter(QObject* parent = nullptr);
 /*public*/ LnTrafficRouter(LocoNetSystemConnectionMemo* m, QObject *parent = nullptr);
 /*public*/ bool status();
 /*public*/ void sendLocoNetMessage(LocoNetMessage* m);
 /*public*/ void connect(LocoNetInterface* i);
 /*public*/ void disconnectPort(LocoNetInterface* i);
 /*public*/ bool isXmtBusy();
public slots:
 /*public*/ void message(LocoNetMessage* m);

private:
 static Logger* log;
 /*private*/ LocoNetInterface* destination = nullptr;
 bool connected = false;

};

#endif // LNTRAFFICROUTER_H
