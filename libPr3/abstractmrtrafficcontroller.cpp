#include "abstractmrtrafficcontroller.h"
#include "abstractmrlistener.h"
#include "exceptions.h"
//#include "abstractmessage.h"
#include "abstractmrmessage.h"
#include "abstractmrreply.h"
#include <QTime>
#include "connectionstatus.h"
#include <QThread>
#include "abstractnetworkportcontroller.h"

//AbstractMRTrafficController::AbstractMRTrafficController(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Abstract base for TrafficControllers in a Message/Reply protocol.
 * <P>
 * Two threads are used for the actual communication.  The "Transmit"
 * thread handles pushing characters to the port, and also changing
 * the mode.  The "Receive" thread converts characters from the input
 * stream into replies.
 * <P>
 * A third thread is registered by the constructor as a shutdown hook.
 * It triggers the necessary cleanup code
 * <P>
 * "Mode" refers to the state of the command station communications.<br>
 * "State" refers to the internal state machine used to control the mode,
 * e.g. to send commands to change mode.<br>
 * "Idle" is a special case, where there is no communications in process,
 * and the port is waiting to do something.
 *
 * @author          Bob Jacobsen  Copyright (C) 2003
 * @author          Paul Bender Copyright (C) 2004-2010
 * @version         $Revision: 21378 $
 */
//abstract /*public*/ class AbstractMRTrafficController {

/*public*/ AbstractMRTrafficController::AbstractMRTrafficController(QObject *parent) : QObject(parent)
{
 log = new Logger("AbstractMRTrafficController");
 if (log->isDebugEnabled()) log->debug("setting instance: "+QString("%1").arg(this->objectName()));
 mCurrentMode = NORMALMODE;
 mCurrentState = IDLESTATE;
 allowUnexpectedReply=false;
 setInstance();
 selfLock = this;
 //jmri.util.RuntimeUtil.addShutdownHook(new Thread(new CleanupHook(this)));
 cmdListeners = new QVector<AbstractMRListener*>();
 mLastSender = NULL;
  /**
   * Messages to be transmitted
   */
 msgQueue = new QLinkedList<AbstractMRMessage*>();
 listenerQueue = new QLinkedList<AbstractMRListener*>();
 timeoutFlag = false;
 timeouts = 0;
 flushReceiveChars = false;
 mWaitBeforePoll = 100;
 waitTimePoll = 0;
 xmtException = false;
 connectionError=false;
 controller = NULL;
 xmtThread = NULL;
 xmtRunnable = NULL;
 rcvThread = NULL;
 // data members to hold the streams
 istream = NULL;
 ostream = NULL;

 rcvException = false;
 threadStopRequest = false;

 maxRcvExceptionCount = 100;
 // Defined this way to reduce new object creation
 rcvBuffer = new QByteArray(1, '0');
 replyInDispatch = false;          // true when reply has been received but dispatch not completed
 maxDispatchTime = 0;
 warningMessageTime = DISPATCH_WARNING_TIME;
 flushReceiveChars = false;
}

/*public*/ AbstractMRTrafficController* AbstractMRTrafficController::getSelfLock(){ return selfLock; }

// set the instance variable
///*abstract /*protected*/ void AbstractMRTrafficController::setInstance();


/*protected*/ /*synchronized*/ void AbstractMRTrafficController::addListener(AbstractMRListener* l)
{
 // add only if not already registered
 if (l == NULL) throw new NullPointerException();
 if (!cmdListeners->contains(l))
 {
  //cmdListeners->addElement(l);
  cmdListeners->append(l);
 }
}

/*protected*/ /*synchronized*/ void AbstractMRTrafficController::removeListener(AbstractMRListener* l)
{
 if (cmdListeners->contains(l))
 {
  //cmdListeners->removeElement(l);
  cmdListeners->remove(cmdListeners->indexOf(l));
 }
}

/**
 * Forward a Message to registered listeners.
 *
 * @param m Message to be forwarded intact
 * @param notMe One (optional) listener to be skipped, usually
 *              because it's the originating object.
 */
//@SuppressWarnings("unchecked")
/*protected*/ void AbstractMRTrafficController::notifyMessage(AbstractMRMessage* m, AbstractMRListener* notMe)
{
 // make a copy of the listener vector to synchronized not needed for transmit
 QVector<AbstractMRListener*>* v;
 //synchronized(this)
 {
  QMutexLocker locker(&mutex);
  //v = (QVector<AbstractMRListener*>*) cmdListeners->clone();
  for (int i=0; i < cmdListeners->count(); i++)
  {
   AbstractMRListener* l = cmdListeners->at(i);
   v->append(l);
  }
 }
 // forward to all listeners
 int cnt = v->size();
 for (int i=0; i < cnt; i++)
 {
  AbstractMRListener* client = v->at(i);
  if (notMe != client)
  {
   if (log->isDebugEnabled()) log->debug(tr("notify client: ")+client->metaObject()->className());
   try
   {
    forwardMessage(client, m);
   }
   catch (Exception* e)
   {
    log->warn(tr("notify: During message dispatch to ")+client->metaObject()->className()+"\nException "+e->getMessage());
                //e->printStackTrace();
   }
  }
 }
}

/**
 * Implement this to forward a specific message type to a protocol-specific
 * listener interface. This puts the casting into the concrete class.
 */
///*abstract*/ /*protected*/ void AbstractMRTrafficController::forwardMessage(AbstractMRListener client, AbstractMRMessage* m);

/**
 * Invoked if it's appropriate to do low-priority polling of the
 * command station, this should return the next message to send,
 * or NULL if the TC should just sleep.
 */
///*abstract*/ /*protected*/ AbstractMRMessage* AbstractMRTrafficController::pollMessage();
///*abstract*/ /*protected*/ AbstractMRListener* AbstractMRTrafficController::pollReplyHandler();


/*
 * enterProgMode() and enterNormalMode() return any message that
 * needs to be returned to the command station to change modes.
 *
 * If no message is needed, you may return NULL.
 *
 * If the programmerIdle() function returns true, enterNormalMode() is
 * called after a timeout while in IDLESTATE during programming to
 * return the system to normal mode.
 *
 */
///*abstract*/ /*protected*/ AbstractMRMessage* AbstractMRTrafficController::enterProgMode();
///*abstract*/ /*protected*/ AbstractMRMessage* AbstractMRTrafficController::enterNormalMode();

// Use this function to check and see if the programmer is idle
// Override in the system specific code if necessary (see notes for
// enterNormalMode() Above).
/*protected*/ bool AbstractMRTrafficController::programmerIdle() {
    return true;
}

// Allow subclasses to add a delay after enabling the programming track
/*protected*/ int AbstractMRTrafficController::enterProgModeDelayTime() {
    return 0;
}



// Use this function to identify If the command station may send
// messages without a request sent to it
/*protected*/ void AbstractMRTrafficController::setAllowUnexpectedReply(bool expected) {
    allowUnexpectedReply=expected;
}

/**
 * Forward a "Reply" from layout to registered listeners.
 *
 * @param r Reply to be forwarded intact
 * @param dest One (optional) listener to be skipped, usually
 *              because it's the originating object.
 */
//@SuppressWarnings("unchecked")
/*protected*/ void AbstractMRTrafficController::notifyReply(AbstractMRReply* r, AbstractMRListener* dest)
{
    // make a copy of the listener vector to synchronized (not needed for transmit?)
    QVector<AbstractMRListener*>* v;
    //synchronized(this)
    {
     QMutexLocker locker(&mutex);
     //v = (QVector<AbstractMRListener*>) cmdListeners->clone();
     for (int i=0; i < cmdListeners->count(); i++)
     {
      AbstractMRListener* l = cmdListeners->at(i);
      v->append(l);
     }
    }
    // forward to all listeners
    int cnt = v->size();
    for (int i=0; i < cnt; i++) {
        AbstractMRListener* client = v->at(i);
        if (log->isDebugEnabled()) log->debug("notify client: "+client->objectName());
        try {
            //skip dest for now, we'll send the message to there last.
    if(dest!=client)
                forwardReply(client, r);
        }
        catch (Exception* e) {
            log->warn(tr("notify: During reply dispatch to ")+client->metaObject()->className()+"\nException "+e->getMessage());
            //e->printStackTrace();
        }
    }

    // forward to the last listener who send a message
    // this is done _second_ so monitoring can have already stored the reply
    // before a response is sent
    if (dest != NULL) forwardReply(dest, r);
}

/*abstract*/ /*protected*/ void forwardReply(AbstractMRListener* client, AbstractMRReply* m);


/**
 * This is invoked with messages to be forwarded to the port.
 * It queues them, then notifies the transmission thread.
 */
/*synchronized*/ /*protected*/ void AbstractMRTrafficController::sendMessage(AbstractMRMessage* m, AbstractMRListener* reply)
{
  msgQueue->append(m);
  listenerQueue->append(reply);
  //synchronized (xmtRunnable)
  {
 // TODO:  QMutexLocker locker1(&xmtRunnable.mutex);
   if (mCurrentState == IDLESTATE)
   {
    mCurrentState = NOTIFIEDSTATE;
// TODO:    xmtRunnable.notify();
   }
  }
  if(m!=NULL)
        log->debug(tr("just notified transmit thread with message ") +m->toString());
}

/**
 * Permanent loop for the transmit thread.
 */
/*private*/ void AbstractMRTrafficController::transmitLoop()
{
 log->debug("transmitLoop starts");

 // loop forever
 while(!connectionError)
 {
  AbstractMRMessage* m = NULL;
  AbstractMRListener* l = NULL;
  // check for something to do
  //synchronized(selfLock)
  {
   if (msgQueue->size()!=0)
   {
    // yes, something to do
    m = msgQueue->first();
    msgQueue->removeFirst();
    l = listenerQueue->first();
    listenerQueue->removeFirst();
    mCurrentState = WAITMSGREPLYSTATE;
    log->debug("transmit loop has something to do: "+m->toString());
   }  // release lock here to proceed in parallel
  }
  // if a message has been extracted, process it
  if (m!=NULL)
  {
   // check for need to change mode
   if (log->isDebugEnabled()) log->debug("Start msg, state ="+mCurrentMode);
   if (m->getNeededMode()!=mCurrentMode)
   {
    AbstractMRMessage* modeMsg;
    if (m->getNeededMode() == PROGRAMINGMODE )
    {
        // change state to programming mode and send message
        modeMsg = enterProgMode();
        if(modeMsg!=NULL) {
            mCurrentState = WAITREPLYINPROGMODESTATE;
            log->debug("Enter Programming Mode");
            forwardToPort(modeMsg, NULL);
            // wait for reply
            transmitWait(m->getTimeout(), WAITREPLYINPROGMODESTATE, "enter programming mode interrupted");
        }
    } else {
        // change state to normal and send message
        modeMsg = enterNormalMode();
        if(modeMsg!=NULL) {
            mCurrentState = WAITREPLYINNORMMODESTATE;
            log->debug("Enter Normal Mode");
            forwardToPort(modeMsg, NULL);
            // wait for reply
            transmitWait(m->getTimeout(), WAITREPLYINNORMMODESTATE, "enter normal mode interrupted");
        }
    }
    if(modeMsg!=NULL) {
        checkReplyInDispatch();
        if (mCurrentState != OKSENDMSGSTATE){
            handleTimeout(modeMsg,l);
        }
        mCurrentState = WAITMSGREPLYSTATE;
    } else {
          // no mode message required, but the message
          // needs a different mode
          if(log->isDebugEnabled())
             log->debug("Setting mode to: " + m->getNeededMode());
          mCurrentMode=m->getNeededMode();
        }
    }
        forwardToPort(m, l);
    // reply expected?
    if (m->replyExpected()) {
        // wait for a reply, or eventually timeout
        transmitWait(m->getTimeout(), WAITMSGREPLYSTATE, "transmitLoop interrupted");
        checkReplyInDispatch();
        if (mCurrentState == WAITMSGREPLYSTATE) {
            handleTimeout(m,l);
        } else if(mCurrentState == AUTORETRYSTATE) {
             log->error("Message added back to queue: " + m->toString());
             msgQueue->prepend(m);
             listenerQueue->prepend(l);
             //synchronized (xmtRunnable)
             {
                   mCurrentState = IDLESTATE;
             }
        } else {
            resetTimeout(m);
        }
    } // just continue to the next message from here
} else {
    // nothing to do
    if (mCurrentState!=IDLESTATE) {
          log->debug("Setting IDLESTATE");
          log->debug("Current Mode " +mCurrentMode);
          mCurrentState =IDLESTATE;
    }
    // wait for something to send
    if (mWaitBeforePoll > waitTimePoll || mCurrentMode == PROGRAMINGMODE){
        try {
            //long startTime = Calendar.getInstance().getTimeInMillis();
            QTime startTime = QTime::currentTime();
 // TODO:           synchronized(xmtRunnable)
            {
                xmtRunnable->wait(mWaitBeforePoll);
            }
            //long endTime = Calendar.getInstance().getTimeInMillis();
            QTime endTime = QTime::currentTime();
            waitTimePoll = waitTimePoll + endTime.msecsTo(startTime);
        } catch (InterruptedException e) {
            QThread::currentThread()->exit(); // retain if needed later
            log->error("transmitLoop interrupted");
        }
    }
    // once we decide that mCurrentState is in the IDLESTATE and there's an xmt msg we must guarantee
    // the change of mCurrentState to one of the waiting for reply states.  Therefore we need to synchronize.
// TODO:    synchronized(selfLock)
    {
        if (mCurrentState!=NOTIFIEDSTATE && mCurrentState!=IDLESTATE){
            log->error("left timeout in unexpected state: "+mCurrentState);
        }
        if (mCurrentState == IDLESTATE) {
            mCurrentState = POLLSTATE;	// this prevents other transitions from the IDLESTATE
        }
    }
    // went around with nothing to do; leave programming state if in it
    if(mCurrentMode == PROGRAMINGMODE &&
       log->isDebugEnabled() )
           log->debug("Timeout - in service mode");
    if (mCurrentState == POLLSTATE && mCurrentMode == PROGRAMINGMODE && programmerIdle() ) {
        log->debug("timeout causes leaving programming mode");
        mCurrentState = WAITREPLYINNORMMODESTATE;
        AbstractMRMessage* msg = enterNormalMode();
        // if the enterNormalMode() message is NULL, we
        // don't want to try to send it to the port.
        if (msg!=NULL)
        {
            forwardToPort(msg, NULL);
            // wait for reply
            transmitWait(msg->getTimeout(), WAITREPLYINNORMMODESTATE, "interrupted while leaving programming mode");
            checkReplyInDispatch();
            // exit program mode timeout?
            if (mCurrentState == WAITREPLYINNORMMODESTATE){
                // entering normal mode via timeout
                handleTimeout (msg,l);
                mCurrentMode = NORMALMODE;
            }
            // and go around again
        }
    } else if (mCurrentState == POLLSTATE && mCurrentMode == NORMALMODE) {
        // We may need to poll
        AbstractMRMessage* msg = pollMessage();
        if (msg != NULL)
        {
            // yes, send that
            log->debug("Sending poll, wait time "+QString("%1").arg((waitTimePoll)));
            mCurrentState = WAITMSGREPLYSTATE;
                        forwardToPort(msg, pollReplyHandler());
            // wait for reply
            transmitWait(msg->getTimeout(), WAITMSGREPLYSTATE, "interrupted while waiting poll reply");
            checkReplyInDispatch();
            // and go around again
            if (mCurrentState == WAITMSGREPLYSTATE) {
                handleTimeout(msg,l);
     }
     else
     {
      resetTimeout(msg);
     }
    }
    waitTimePoll = 0;
   }
   // no messages, so back to idle
   if (mCurrentState == POLLSTATE){
     mCurrentState =IDLESTATE;
   }
  }
 }
}   // end of transmit loop; go around again

/*protected*/ void AbstractMRTrafficController::transmitWait(int waitTime, int state, QString InterruptMessage)
{
 // wait() can have spurious wakeup!
 // so we protect by making sure the entire timeout time is used
 //long currentTime = Calendar.getInstance().getTimeInMillis();
 QTime currentTime = QTime::currentTime();
 QTime endTime = currentTime.addMSecs(waitTime);
 while (endTime > (currentTime =/* Calendar.getInstance().getTimeInMillis()*/ QTime::currentTime()))
 {
  //long wait = endTime - currentTime;
  long wait = currentTime.msecsTo(endTime);
  try
  {
// TODO:   synchronized(xmtRunnable)
   {
    // Do not wait if the current state has changed since we
    // last set it.
    if (mCurrentState != state)
     return;
    xmtRunnable->wait(wait); // rcvr normally ends this w state change
   }
  }
  catch (InterruptedException e)
  {
   QThread::currentThread()->exit(); // retain if needed later
   log->error(InterruptMessage);
  }
 }
 log->debug("Timeout in transmitWait, mCurrentState:" + mCurrentState);
}


/*private*/ void AbstractMRTrafficController::checkReplyInDispatch()
{
 int loopCount = 0;
 while (replyInDispatch)
 {
  try {
// TODO:            synchronized (xmtRunnable)
            {
                xmtRunnable->wait(DISPATCH_WAIT_INTERVAL);
            }
        } catch (InterruptedException e) {
            QThread::currentThread()->exit(); // retain if needed later
            log->error("transmitLoop interrupted");
        }
        loopCount++;
        int currentDispatchTime = loopCount * DISPATCH_WAIT_INTERVAL;
        if (currentDispatchTime > maxDispatchTime) {
            maxDispatchTime = currentDispatchTime;
            if (currentDispatchTime >= warningMessageTime){
                warningMessageTime = warningMessageTime + WARN_NEXT_TIME;
                log->debug("Max dispatch time is now " + currentDispatchTime);
            }
        }
    }
}

// used to determine if interface is down
/*public*/ bool AbstractMRTrafficController::hasTimeouts(){
    return timeoutFlag;
}

/*protected*/ void AbstractMRTrafficController::handleTimeout(AbstractMRMessage* msg, AbstractMRListener* /*l*/)
{
    //log->debug("Timeout mCurrentState:" + mCurrentState);
    log->warn("Timeout on reply to message: "+msg->toString()+
             tr(" consecutive timeouts = ")+QString("%1").arg(timeouts));
    timeouts++;
    timeoutFlag = true;
    flushReceiveChars = true;
}

/*protected*/ void AbstractMRTrafficController::resetTimeout(AbstractMRMessage* /*msg*/) {
    if (timeouts>0) log->debug(tr("Reset timeout after ")+QString("%1").arg(timeouts)+tr(" timeouts"));
    timeouts=0;
    timeoutFlag = false;
}

/**
 * Add header to the outgoing byte stream.
 * @param msg  The output byte stream
 * @return next location in the stream to fill
 */
/*protected*/ int AbstractMRTrafficController::addHeaderToOutput(QByteArray* /*msg*/, AbstractMRMessage* /*m*/)
{
    return 0;
}


/**
 * Add trailer to the outgoing byte stream.
 * @param msg  The output byte stream
 * @param offset the first byte not yet used
 */
/*protected*/ void AbstractMRTrafficController::addTrailerToOutput(QByteArray* msg, int offset, AbstractMRMessage* m) {
    if (! m->isBinary()){
        msg->replace(offset,0x0d);
    }
}

/**
 * Determine how much many bytes the entire
 * message will take, including space for header and trailer
 * @param m  The message to be sent
 * @return Number of bytes
 */
/*protected*/ int AbstractMRTrafficController::lengthOfByteStream(AbstractMRMessage* m)
{
    int len = m->getNumDataElements();
    int cr = 0;
    if (! m->isBinary()) cr = 1;  // space for return
    return len+cr;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// String + only used for debug, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*protected*/ bool xmtException = false;
/**
 * Actually transmits the next message to the port
 */
 /*synchronized*/ /*protected*/ void AbstractMRTrafficController::forwardToPort(AbstractMRMessage* m, AbstractMRListener* reply)
{
    QMutexLocker locker(&mutex);
    if (log->isDebugEnabled()) log->debug("forwardToPort message: ["+m->toString()+"]");
    // remember who sent this
    mLastSender = reply;

    // forward the message to the registered recipients,
    // which includes the communications monitor, except the sender.
    // Schedule notification via the Swing event queue to ensure order
    Runnable* r = new XmtNotifier(m, mLastSender, this);
// TODO:    javax.swing.SwingUtilities.invokeLater(r);

    // stream to port in single write, as that's needed by serial
    QByteArray* msg = new QByteArray(lengthOfByteStream(m),0);
    // add header
    int offset = addHeaderToOutput(msg, m);

    // add data content
    int len = m->getNumDataElements();
    for (int i=0; i< len; i++)
        msg->replace(i+offset, (char) m->getElement(i));
    // add trailer
    addTrailerToOutput(msg, len+offset, m);
    // and stream the bytes
    try {
        if (ostream != NULL) {
            if (log->isDebugEnabled()) {
                //StringBuilder f = new StringBuilder("formatted message: ");
                QString f("formatted message: ");
                for (int i = 0; i<msg->length(); i++)
                {
                    f.append(QString("%1").arg(0xFF&msg->at(i),0,16));
                    f.append(" ");
                }
                log->debug( QString(f));
            }
            while(m->getRetries()>=0)
            {
                if(portReadyToSend(controller))
                {
// TODO:                    ostream->write(msg);
// TODO:                    ostream->flush();
                    log->debug(tr("written, msg timeout: ")+QString("%1").arg(m->getTimeout())+" mSec");
                    break;
                } else if(m->getRetries()>=0) {
                    if (log->isDebugEnabled()) {
                        //StringBuilder b = new StringBuilder("Retry message: ");
                        QString b("Retry message: ");
                        b.append(m->toString());
                        b.append(" attempts remaining: ");
                        b.append(m->getRetries());
                        log->debug(b);
                    }
                    m->setRetries(m->getRetries() - 1);
                    try {
// TODO:                        synchronized(xmtRunnable)
                        {
                            xmtRunnable->wait(m->getTimeout());
                        }
                    } catch (InterruptedException e) {
                        QThread::currentThread()->quit(); // retain if needed later
                        log->error("retry wait interupted");
                    }
                } else log->warn(tr("sendMessage: port not ready for data sending: ") /*+java.util.Arrays.toString(msg)*/);
            }
        } else {  // ostream is NULL
            // no stream connected
            connectionWarn();
        }
 } catch (Exception e) {
        // TODO Currently there's no port recovery if an exception occurs
        // must restart JMRI to clear xmtException.
        xmtException = true;
        portWarn(e);
    }
 }

/*protected*/ void AbstractMRTrafficController::connectionWarn() {
    log->warn(tr("sendMessage: no connection established for ")+this->metaObject()->className());
// TODO:    new Exception().printStackTrace();
}

/*protected*/ void AbstractMRTrafficController::portWarn(Exception e) {
    log->warn("sendMessage: Exception: port warn "+e.getMessage());
}

/*protected*/ void AbstractMRTrafficController::portWarnTCP(Exception e) {
    log->warn("Exception java net: "+e.getMessage());
    connectionError=true;
}
// methods to connect/disconnect to a source of data in a AbstractPortController

/*public*/ bool AbstractMRTrafficController::status() {
    return (ostream != NULL & istream != NULL);
}


/**
 * Make connection to existing PortController object.
 */
/*public*/ void AbstractMRTrafficController::connectPort(AbstractPortController* p) {
    rcvException=false;
    connectionError=false;
    xmtException=false;
    try {
        istream = p->getInputStream();
        ostream = p->getOutputStream();
        if (controller != NULL)
            log->warn("connectPort: connect called while connected");
        else
            log->debug("connectPort invoked");
        controller = p;
        // and start threads
#if 0 // TODO:
        xmtThread = new QThread(xmtRunnable = new Runnable()
        {
                /*public*/ void run() {
                                    try {
                                        transmitLoop();
                                        } catch (Throwable e) {
                                            log->fatal("Transmit thread terminated prematurely by: "+e, e);
                                        }
                                  }
            });
#endif
        xmtThread = new QThread();
        xmtThread->setObjectName("Transmit");
        XmitWorker* xmitWorker = new XmitWorker(this);
        connect(xmtThread, SIGNAL(started()), xmitWorker, SLOT(run()));
        connect(xmitWorker, SIGNAL(finished()), xmtThread, SLOT(quit()));
        xmitWorker->moveToThread(xmtThread);
        xmtThread->start();

//        rcvThread = new Thread(new Runnable() {
//                /*public*/ void run() { receiveLoop(); }
//            });
        rcvThread = new QThread();
        RcvWorker* rcvWorker = new RcvWorker(this);
        rcvThread->setObjectName("Receive");
        connect(rcvThread, SIGNAL(started()), rcvWorker, SLOT(run()));
        connect(rcvWorker, SIGNAL(finished()), rcvThread, SLOT(quit()));
        rcvWorker->moveToThread(rcvThread);
        int xr = rcvThread->priority();
        xr++;
        rcvThread->setPriority((QThread::Priority)xr);      //bump up the priority
        rcvThread->start();

    } catch (Exception e) {
        log->error("Failed to start up communications. Error was "+e.getMessage());
    }

}
XmitWorker::XmitWorker(AbstractMRTrafficController* amrtc)
{
 this->amrtc = amrtc;
}

/*public*/ void XmitWorker::run()
{
 try
 {
  amrtc->transmitLoop();
 }
 catch (Throwable e)
 {
   //amrtc->log->fatal("Transmit thread terminated prematurely by: "+e.getLocalizedMessage(), e.getMessage());
   amrtc->log->error("Transmit thread terminated prematurely by: "+e.getLocalizedMessage(), e);

   emit finished();
 }
}

/**
 * Get the port name for this connection
 */
/*public*/ QString AbstractMRTrafficController::getPortName(){
    return controller->getCurrentPortName();
}

/**
 * Break connection to existing PortController object. Once broken,
 * attempts to send via "message" member will fail.
 */
/*public*/ void AbstractMRTrafficController::disconnectPort(AbstractPortController* p) {
    istream = NULL;
    ostream = NULL;
    if (controller != p)
        log->warn("disconnectPort: disconnect called from non-connected AbstractPortController");
    controller = NULL;
}

/**
 * Check to see if PortController object can be sent to.
 * returns true if ready, false otherwise
 * May throw an Exception.
 */
/*public*/ bool AbstractMRTrafficController::portReadyToSend(AbstractPortController* p) throw (Exception)
{
    if(p!=NULL && !xmtException && !rcvException) return true;
    else return false;
}


/**
 * Handle incoming characters.  This is a permanent loop,
 * looking for input messages in character form on the
 * stream connected to the PortController via <code>connectPort</code>.
 * Each turn of the loop is the receipt of a single message.
 */
/*public*/ void AbstractMRTrafficController::receiveLoop() {
    log->debug("receiveLoop starts");
    int errorCount = 0;
    while (errorCount<maxRcvExceptionCount) {   // loop permanently, stream close will exit via exception
        try {
            handleOneIncomingReply();
            errorCount=0;
        }
        catch (IOException e) {
            rcvException = true;
            reportReceiveLoopException(e);
            break;
        }
        catch (Exception e1) {
            log->error("Exception in receive loop: "+e1.getMessage());
            //e1.printStackTrace();
            errorCount++;
            if(errorCount==maxRcvExceptionCount){
                rcvException = true;
                reportReceiveLoopException(e1);
            }
        }
     if (!threadStopRequest) { // if e.g. unexpected end
         ConnectionStatus::instance()->setConnectionState(controller->getCurrentPortName(), ConnectionStatus::CONNECTION_DOWN);
         log->error(tr("Exit from rcv loop in %1").arg(this->metaObject()->className()));
         recovery(); // see if you can restart
     }

    }
   // TODO: ConnectionStatus.instance().setConnectionState(controller.getCurrentPortName(), ConnectionStatus.CONNECTION_DOWN);
    log->error("Exit from rcv loop");
    recovery();
}

/*private*/ void AbstractMRTrafficController::recovery(){
    AbstractPortController* adapter = controller;
    disconnectPort(controller);
 // TODO:   adapter->recover();
}

/**
 * Report error on receive loop. Separated so tests can suppress,
 * even though message is asynchronous.
 */
/*protected*/ void AbstractMRTrafficController::reportReceiveLoopException(Exception e) {
    log->error("run: Exception: "+e.getMessage());
    log->error(tr("run: Exception: %1 in %2").arg(e.getMessage()).arg(this->metaObject()->className()).arg(e.getMessage()));
    ConnectionStatus::instance()->setConnectionState(controller->getCurrentPortName(), ConnectionStatus::CONNECTION_DOWN);
    if (qobject_cast<AbstractNetworkPortController*>(controller))
    {
        portWarnTCP(e);
    }
}

///*abstract*/ /*protected*/ AbstractMRReply* AbstractMRTrafficController::newReply();
///*abstract*/ /*protected*/ bool AbstractMRTrafficController::endOfMessage(AbstractMRReply* r);

/**
 * Dummy routine, to be filled by protocols that
 * have to skip some start-of-message characters.
 */
//@SuppressWarnings("unused")
/*protected*/ void AbstractMRTrafficController::waitForStartOfReply(QDataStream* istream) throw (IOException) {}

/**
 * Read a single byte, protecting against various timeouts, etc.
 * <P>
 * When a gnu.io port is set to have a
 * receive timeout (via the enableReceiveTimeout() method),
 * some will return zero bytes or an EOFException at the end of the timeout.
 * In that case, the read should be repeated to get the next real character.
 *
 */
/*protected*/ char AbstractMRTrafficController::readByteProtected(QDataStream* istream) throw (IOException)
{
    while (true) { // loop will repeat until character found
        int nchars;
// TODO:        nchars = istream->read(rcvBuffer, 0, 1);
        if (nchars== -1) {
            // No more bytes can be read from the channel
            throw new IOException("Connection not terminated normally");
        }
        if (nchars>0) return rcvBuffer->at(0);
    }
}


/**
 * Get characters from the input source, and file a message.
 * <P>
 * Returns only when the message is complete.
 * <P>
 * Only used in the Receive thread.
 * <P>
 * Handles timeouts on read by ignoring zero-length reads.
 *
 * @param msg message to fill
 * @param istream character source.
 * @throws IOException when presented by the input source.
 */
/*protected*/ void AbstractMRTrafficController::loadChars(AbstractMRReply* msg, QDataStream* istream)
throw (IOException)
{
    int i;
    for (i = 0; i < msg->maxSize(); i++) {
        char char1 = readByteProtected(istream);
        //if (log->isDebugEnabled()) log->debug("char: "+(char1&0xFF)+" i: "+i);
        // if there was a timeout, flush any char received and start over
        if(flushReceiveChars){
            log->warn("timeout flushes receive buffer: "+ msg->toString());
            msg->flush();
            i = 0;  // restart
            flushReceiveChars = false;
        }
        if (canReceive()) {
            msg->setElement(i, char1);
            if (endOfMessage(msg))
                break;
        } else {
            i--; // flush char
            log->error("unsolicited character received: "+ QString("0x%1").arg((char1,0,16)));
        }
    }
}

/**
 * Override in the system specific code if necessary
 * @return true if it is okay to buffer receive characters
 * into a reply message.  When false, discard char received
 */
/*protected*/ bool AbstractMRTrafficController::canReceive(){
    return true;
}

/**
 * Handle each reply when complete.
 * <P>
 * (This is public for testing purposes)
 * Runs in the "Receive" thread.
 * @throws IOException
 */
/*public*/ void AbstractMRTrafficController::handleOneIncomingReply() throw (IOException)
{
 // we sit in this until the message is complete, relying on
 // threading to let other stuff happen

 // Create message off the right concrete class
 AbstractMRReply* msg = newReply();

 // wait for start if needed
 waitForStartOfReply(istream);

 // message exists, now fill it
 loadChars(msg, istream);

 // message is complete, dispatch it !!
 replyInDispatch = true;
 if (log->isDebugEnabled()) log->debug("dispatch reply of length "+QString("%1").arg(msg->getNumDataElements())+
                                    " contains "+msg->toString()+" state "+QString("%1").arg(mCurrentState));

 // forward the message to the registered recipients,
 // which includes the communications monitor
 // return a notification via the Swing event queue to ensure proper thread
 Runnable* r = new RcvNotifier(msg, mLastSender, this);
 try
 {
 // TODO:       javax.swing.SwingUtilities.invokeAndWait(r);
 } catch (Exception e)
 {
  log->error("Unexpected exception in invokeAndWait:" +e.getMessage());
        //e.printStackTrace();
 }
 if (log->isDebugEnabled()) log->debug("dispatch thread invoked");

 if (!msg->isUnsolicited())
 {
  // effect on transmit:
  switch (mCurrentState)
  {
   case WAITMSGREPLYSTATE:
   {
    // check to see if the response was an error message we want
    // to automatically handle by re-queueing the last sent
    // message, otherwise go on to the next message
    if(msg->isRetransmittableErrorMsg())
    {
     if(log->isDebugEnabled())
      log->debug("Automatic Recovery from Error Message: +msg.toString()");
 // TODO:              synchronized (xmtRunnable)
     {
      mCurrentState = AUTORETRYSTATE;
      replyInDispatch = false;
 // TODO:                 xmtRunnable.notify();
     }
    }
    else
    {
     // update state, and notify to continue
// TODO:               synchronized (xmtRunnable)
     {
      mCurrentState = NOTIFIEDSTATE;
      replyInDispatch = false;
// TODO:      xmtRunnable.notify();
     }
    }
    break;
   }
   case WAITREPLYINPROGMODESTATE:
   {
            // entering programming mode
            mCurrentMode = PROGRAMINGMODE;
            replyInDispatch = false;

            // check to see if we need to delay to allow decoders to become
            // responsive
            int warmUpDelay = enterProgModeDelayTime();
            if (warmUpDelay != 0) {
                try {
// TODO:                    synchronized (xmtRunnable)
                    {
                        xmtRunnable->wait(warmUpDelay);
                    }
                } catch (InterruptedException e) {
                    QThread::currentThread()->exit(); // retain if needed later
                }
            }
            // update state, and notify to continue
// TODO:            synchronized (xmtRunnable)
            {
                mCurrentState = OKSENDMSGSTATE;
 // TODO:               xmtRunnable.notify();
            }
            break;
        }
        case WAITREPLYINNORMMODESTATE: {
            // entering normal mode
            mCurrentMode = NORMALMODE;
            replyInDispatch = false;
            // update state, and notify to continue
// TODO:            synchronized (xmtRunnable)
            {
                mCurrentState = OKSENDMSGSTATE;
// TODO:                xmtRunnable.notify();
            }
            break;
        }
        default: {
            replyInDispatch = false;
            if (allowUnexpectedReply == true) {
                if (log->isDebugEnabled())
                    log->debug(tr("Allowed unexpected reply received in state: ")
                              + mCurrentState   + " was " + msg->toString());
// TODO:               synchronized (xmtRunnable)
               {
                   // The transmit thread sometimes gets stuck
                   // when unexpected replies are received.  Notify
                   // it to clear the block without a timeout.
                   // (do not change the current state)
                   //if(mCurrentState!=IDLESTATE)
// TODO:                      xmtRunnable.notify();
               }
            } else {
                log->error(tr("reply complete in unexpected state: ")
                          + mCurrentState + " was " + msg->toString());
            }
        }
        }
        // Unsolicited message
    } else {
        if(log->isDebugEnabled()) log->debug(tr("Unsolicited Message Received ")
                                           + msg->toString());

        replyInDispatch = false;
    }
}

/*
 * for testing purposes, let us be able to find out
 * what the last sender was
 */
/*public*/ AbstractMRListener* AbstractMRTrafficController::getLastSender()
{
    return mLastSender;
}

// Override the finalize method for this class
// to request termination, which might have happened
// before in any case
/*protected*/ /*final*/ void AbstractMRTrafficController::finalize() throw (Throwable) {
    terminate();
    //super.finalize();
}

/*protected*/ void AbstractMRTrafficController::terminate() {
    if(log->isDebugEnabled()) log->debug("Cleanup Starts");
    if (ostream == NULL) return;    // no connection established
    AbstractMRMessage* modeMsg=enterNormalMode();
    if(modeMsg!=NULL) {
        modeMsg->setRetries(100); // set the number of retries
        // high, just in case the interface
        // is busy when we try to send
            forwardToPort(modeMsg, NULL);
        // wait for reply
        try {
             if (xmtRunnable!=NULL)
// TODO:                 synchronized(xmtRunnable)
                 {
                     xmtRunnable->wait(modeMsg->getTimeout());
                 }
        } catch (InterruptedException e) {
             QThread::currentThread()->exit(); // retain if needed later
             log->error("transmit interrupted");
        }
    }
}

// allow creation of object outside package
/*protected*/ RcvNotifier* newRcvNotifier(AbstractMRReply* pMsg, AbstractMRListener* pDest,
                AbstractMRTrafficController* pTC)
{
 return new RcvNotifier(pMsg, pDest, pTC);
}


//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractMRTrafficController.class.getName());
//}
