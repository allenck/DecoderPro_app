#ifndef STANDALONETRAFFICCONTROLLER_H
#define STANDALONETRAFFICCONTROLLER_H
#include "rfid/rfidtrafficcontroller.h"

class StandaloneTrafficController : public RfidTrafficController
{
public:
 StandaloneTrafficController(RfidSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ void sendInitString();
 /*public*/ RfidMessage* getRfidMessage(int length);
 /*public*/ QString getRange();


private:
 bool sendInterlock = false; // send the 00 interlock when CRC received
 static Logger* log;

protected:
 /*protected*/ void forwardToPort(AbstractMRMessage* m, AbstractMRListener* reply);
 /*protected*/ AbstractMRReply* newReply();
 /*protected*/ bool endOfMessage(AbstractMRReply* msg);

};

#endif // STANDALONETRAFFICCONTROLLER_H
