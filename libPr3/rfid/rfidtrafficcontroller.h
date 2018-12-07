#ifndef RFIDTRAFFICCONTROLLER_H
#define RFIDTRAFFICCONTROLLER_H

#include <QObject>
#include "rfidlistener.h"
#include "abstractmrlistener.h"
#include "rfidsensormanager.h"
#include "rfidreportermanager.h"
#include "abstractmrtrafficcontroller.h"

class AbstractMRMessage;
class AbstractMRReply;
class RfidSystemConnectionMemo;
class RfidSensorManager;
class RfidTrafficController : public AbstractMRTrafficController
{
    Q_OBJECT
public:
    explicit RfidTrafficController(QObject *parent = 0);
    /*public*/ void setAdapterMemo(RfidSystemConnectionMemo* memo);
    /*public*/ RfidSystemConnectionMemo* getAdapterMemo();
    /*public*/ /*synchronized*/ void addRfidListener(RfidListener* l);
    /*public*/ /*synchronized*/ void removeRfidListener(RfidListener* l);
    /*public*/ void sendRfidMessage(RfidMessage* m, RfidListener* reply);
    /*public*/ void setSensorManager(RfidSensorManager* m);
    /*public*/ RfidSensorManager* getSensorManager();
    /*public*/ void setReporterManager(RfidReporterManager* m);
    /*public*/ RfidReporterManager* getReporterManager();
    /*abstract*/ /*public*/ virtual void sendInitString(){}
    /*public*/ QString getRange();


signals:
    
public slots:
private:
    RfidSensorManager* mSensorManager;// = NULL;
    static Logger* log;
    RfidSystemConnectionMemo* adapterMemo;
    RfidReporterManager* mReporterManager = NULL;
    bool sendInterlock = false; // send the 00 interlock when CRC received
    bool expectLength = false;  // next byte is length of read
    bool countingBytes = false; // counting remainingBytes into reply buffer
    int remainingBytes = 0;        // count of bytes _left_

protected:
    /*protected*/ void forwardMessage(AbstractMRListener* client, AbstractMRMessage* m);
    // have several debug statements in tight loops, e.g. every character;
    // only want to check once
    /*protected*/ bool logDebug = false;
    /*protected*/ void forwardReply(AbstractMRListener* client, AbstractMRReply* r);
    /*protected*/ AbstractMRMessage* pollMessage() ;
    /*protected*/ AbstractMRListener* pollReplyHandler();
    /*protected*/ void forwardToPort(AbstractMRMessage* m, AbstractMRListener* reply) ;
    /*protected*/ AbstractMRMessage* enterProgMode();
    /*protected*/ AbstractMRMessage* enterNormalMode();
    /*protected*/ bool endOfMessage(AbstractMRReply* msg);
    /*protected*/ AbstractMRReply* newReply();

    friend class StandaloneTrafficController;
};

#endif // RFIDTRAFFICCONTROLLER_H
