#ifndef LOCONETTHROTTLEDTRANSMITTER_H
#define LOCONETTHROTTLEDTRANSMITTER_H
//#include "loconetinterface.h"
#include "lntrafficcontroller.h"
#include <QObject>
#include "logger.h"
#include "timeunit.h"

class ServiceThread;
//class DelayQueue;
class Memo;

/**
 * Delay LocoNet messages that need to be throttled.
 * <p>
 * A LocoNetThrottledTransmitter object sits in front of a LocoNetInterfaceLnTrafficController
 * (e.g. TrafficHandler) and meters out specific LocoNet messages.
 *
 * <p>
 * The internal Memo class is used to hold the pending
 * message and the time it's to be sent. Time computations
 * are in units of milliseconds, as that's all the
 * accuracy that's needed here.
 *
 * @author Bob Jacobsen Copyright (C) 2009
 * @version $Revision: 20788 $
 */
class LocoNetThrottledTransmitter : virtual public /*LocoNetInterface*/LnTrafficController
{
 Q_OBJECT
public:
 explicit LocoNetThrottledTransmitter(/*LocoNetInterface*/LnTrafficController* controller, bool mTurnoutExtraSpace, QObject *parent = 0);
    /**
     * Cease operation, no more messages can be sent
     */
    /*public*/ void dispose();
    // Forward methods to underlying interface
    /*public*/ virtual void addLocoNetListener(int mask, LocoNetListener* listener);
    /*public*/ virtual  void removeLocoNetListener(int mask, LocoNetListener* listener);
    /*public*/ bool status();
    /**
     * Accept a message to be sent after suitable delay.
     */
    /*public*/ void sendLocoNetMessage(LocoNetMessage* msg);
    long calcSendTimeMSec();
#if 1 // TODO:
    //DelayQueue<Memo> queue;// = new DelayQueue<Memo>();
    QQueue<Memo*>* queue = nullptr;
#endif
    // a separate method to ease testing by stopping clock
    long nowMSec();

signals:
    
public slots:
private:
 bool mTurnoutExtraSpace;
 bool disposed;
 bool running;

 // interface being shadowed
 /*LocoNetInterface*/LnTrafficController* controller;
private:
 // minimum time in msec between messages
 long minInterval;

 long lastSendTimeMSec;// = 0;
 Logger log;
 /*private*/ void attachServiceThread();
#if 1 // TODO:
 ServiceThread* theServiceThread;
#endif
 friend class ServiceThread;
 friend class Memo;
};
class Memo //: public QObject //Delayed
{
 //Q_OBJECT
public:
    /*public*/ Memo(LocoNetMessage* msg, long endTime, TimeUnit::TIMEUNIT unit, LocoNetThrottledTransmitter* parent, bool bRequestShutdown = false);
    LocoNetMessage* getMessage();
    bool requestsShutDown();
private:
    LocoNetThrottledTransmitter* parent;
    long endTimeMsec;
    LocoNetMessage* msg;
    TimeUnit::TIMEUNIT unit;
    bool bRequestShutdown;

    /*public*/ long getDelay(TimeUnit::TIMEUNIT unit);
    /*public*/ int compareTo(TimeUnit::TIMEUNIT d);
    // ensure consistent with compareTo
    /*public*/ bool equals( QObject* o );
    /*public*/ int hashCode();
    friend class ServiceThread;
};
class ServiceThread : public QThread
{
    Q_OBJECT
    ServiceThread(LocoNetThrottledTransmitter* parent);
public:
    /*public*/ void run();
private:
    LocoNetThrottledTransmitter* parent;
    Logger* log;
    friend class LocoNetThrottledTransmitter;
};
#endif // LOCONETTHROTTLEDTRANSMITTER_H
