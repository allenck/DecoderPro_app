#include "loconetthrottledtransmitter.h"
#include "exceptions.h"

/**
 * Delay LocoNet messages that need to be throttled.
 * <p>
 * A LocoNetThrottledTransmitter object sits in front of a LocoNetInterface/LnTrafficController
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
LocoNetThrottledTransmitter::LocoNetThrottledTransmitter(/*LocoNetInterface*/LnTrafficController* controller, bool mTurnoutExtraSpace, QObject *parent)
    :
    /*LocoNetInterface*/LnTrafficController()
{
    disposed = false;
    running = false;

    this->controller = controller;
    this->mTurnoutExtraSpace = mTurnoutExtraSpace;

    //queue = new DelayQueue<Memo>();
    queue = new QQueue<Memo*>();

    // calculation is needed time to send on DCC:
    // msec*nBitsInPacket*packetRepeat/bitRate*safetyFactor
    minInterval = 1000*(18+3*10)*3/16000*2;

    if (mTurnoutExtraSpace) minInterval = minInterval * 4;

    attachServiceThread();

}



/**
 * Cease operation, no more messages can be sent
 */
/*public*/ void LocoNetThrottledTransmitter::dispose() {
    disposed = true;
#if 1 // TODO:
    // put a shutdown request on the queue after any existing
    Memo* m =  new Memo(NULL, calcSendTimeMSec(), TimeUnit::MILLISECONDS, this, true);
//    {
//                    bool requestsShutDown() { return true; }
//    };
    queue->append(m);
#endif
}


// Forward methods to underlying interface

/*public*/ void LocoNetThrottledTransmitter::addLocoNetListener(int mask, LocoNetListener* listener) {
    if(controller != NULL)
 controller->addLocoNetListener(mask, listener);
}

/*public*/ void LocoNetThrottledTransmitter::removeLocoNetListener(int mask, LocoNetListener* listener) {
    controller->removeLocoNetListener(mask, listener);
}

/*public*/ bool LocoNetThrottledTransmitter::status() {
    return controller->status();
}

/**
 * Accept a message to be sent after suitable delay.
 */
/*public*/ void LocoNetThrottledTransmitter::sendLocoNetMessage(LocoNetMessage* msg) {
    if (disposed) {
        log.error("Message sent after queue disposed");
        return;
    }

    long sendTime = calcSendTimeMSec();
#if 1 // TODO:
    Memo* m = new Memo(msg, sendTime, TimeUnit::MILLISECONDS,this);
    queue->append(m);
#endif
}


long LocoNetThrottledTransmitter::calcSendTimeMSec() {
    // next time is at least now or minInterval after latest so far
#if 1 // TODO:
    lastSendTimeMSec = qMax(nowMSec(), minInterval+lastSendTimeMSec);
#endif
    return lastSendTimeMSec;
}


/*private*/ void LocoNetThrottledTransmitter::attachServiceThread() {
#if 1 // TODO:
    theServiceThread = new ServiceThread(this);
    theServiceThread->setObjectName("LocoNetThrottledTransmitter");
    //theServiceThread.setDaemon(true);
    theServiceThread->start();
    theServiceThread->setPriority(QThread::NormalPriority);
#endif
}


//class ServiceThread : public QThread
//{
ServiceThread::ServiceThread(LocoNetThrottledTransmitter *parent)
{
 this->parent = parent;
 log = new Logger("ServiceThread");
}

/*public*/ void ServiceThread::run()
{
 parent->running = true;
 while (true)
 {
  try
  {
   if(parent->queue->size()>0)
   {
    Memo* m = parent->queue->takeFirst();

     // check for request to shutdown
    if (m->requestsShutDown())
    {
     log->debug("item requests shutdown");
     break;
    }

    // normal request
    if (log->isDebugEnabled())
        log->debug(tr("forwarding message: ")+m->getMessage()->toString());
    if(parent->controller != NULL)
    parent->controller->sendLocoNetMessage(m->getMessage());
  }
        // and go round again
  } catch (Exception* e)
  {
   // just report error and continue
   log->error("Exception in ServiceThread: "+e->getMessage());
   //e.printStackTrace();
  }
 }
 parent->running = false;
}
//};

// a separate method to ease testing by stopping clock
long LocoNetThrottledTransmitter::nowMSec() {
    return QDateTime::currentMSecsSinceEpoch();
}
#if 1 // TODO:
//class Memo : public Delayed {
/*public*/ Memo::Memo(LocoNetMessage* msg, long endTime, TimeUnit::TIMEUNIT unit, LocoNetThrottledTransmitter* parent,bool bRequestShutdown)
{
 this->parent = parent;
 this->msg = msg;
 this->unit = unit;
 this->bRequestShutdown = bRequestShutdown;
 //this->endTimeMsec = unit.toMillis(endTime);
 switch(unit)
 {
  case TimeUnit::MILLISECONDS:
    this->endTimeMsec = endTime;
    break;
 }
}

LocoNetMessage* Memo::getMessage() { return msg; }

bool Memo::requestsShutDown() { return /*false*/bRequestShutdown; }

//    long endTimeMsec;
//    LocoNetMessage msg;

/*public*/ long Memo::getDelay(TimeUnit::TIMEUNIT unit) {
    long delay = endTimeMsec - parent->nowMSec();
    //return unit.convert(delay, TimeUnit::MILLISECONDS);
    return delay;
}

/*public*/ int Memo::compareTo(TimeUnit::TIMEUNIT d) {
    // -1 means this is less than m
    long delay;
    switch(d)
    {
    case TimeUnit::MILLISECONDS:
     delay = getDelay(d);
     break;
    default:
     break;
    }

    long delta = this->getDelay(TimeUnit::MILLISECONDS)
                    - /*d.getDelay(TimeUnit::MILLISECONDS)*/delay;
    if (delta > 0 ) return 1;
    else if (delta < 0 ) return -1;
    else return 0;
}
// ensure consistent with compareTo
/*public*/ bool Memo::equals( QObject* o ) {
    if (o == NULL) return false;
//        if (o instanceof Delayed)
//            return (compareTo((Delayed)o) == 0);
    else return false;
}
/*public*/ int Memo::hashCode() {
  return (int)(this->getDelay(TimeUnit::MILLISECONDS)&0xFFFFFF);
}
//};
#endif
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoNetThrottledTransmitter.class.getName());
