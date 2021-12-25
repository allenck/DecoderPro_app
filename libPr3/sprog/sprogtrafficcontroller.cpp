#include "sprogtrafficcontroller.h"
#include "loggerfactory.h"
#include "exceptions.h"
#include "sprogmessage.h"
#include "sprogreply.h"
#include "sprogserialdriveradapter.h"
#include <QDataStream>
#include "sleeperthread.h"
#include <QThread>
#include <QApplication>

using namespace Sprog;
/**
 * Converts Stream-based I/O to/from Sprog messages. The "SprogInterface" side
 * sends/receives message objects. The connection to a SprogPortController is
 * via a pair of *Streams, which then carry sequences of characters for
 * transmission. Note that this processing is handled in an independent thread.
 * <p>
 * Updated January 2010 for gnu io (RXTX) - Andrew Berridge.
 * Removed Runnable implementation and methods for it.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 */
///*public*/ class SprogTrafficController implements SprogInterface, SerialPortEventListener {


/*public*/ SprogTrafficController::SprogTrafficController(SprogSystemConnectionMemo* adaptermemo, QObject* parent)
{
 waitingForReply = false;
 reply = new SprogReply();
 lastSender = NULL;
 sprogState = SprogConstants::SprogState::NORMAL;
 cmdListeners = QVector<SprogListener*>();
 istream = NULL;
 ostream = NULL;
 cmdListeners = QVector<SprogListener*>();
 controller = NULL;

 memo = adaptermemo;
}


//@Override
/*public*/ bool SprogTrafficController::status() {
    return (ostream != NULL && istream != NULL);
}

//@Override
/*public*/ /*synchronized*/ void SprogTrafficController::addSprogListener(SprogListener* l) {
    // add only if not already registered
    if (l == NULL) {
        throw new NullPointerException();
    }
    if (!cmdListeners.contains(l)) {
        cmdListeners.append(l);
        log->debug(tr("SprogListener added to %1 tc").arg(memo->getUserName()));
        if(qobject_cast<SprogCommandStation*>(l))
        connect(this, SIGNAL(do_notifyMessage(SprogMessage*)), (SprogCommandStation*)l, SLOT(notifyMessage(SprogMessage*)));
    }
}

//@Override
/*public*/ /*synchronized*/ void SprogTrafficController::removeSprogListener(SprogListener* l) {
    if (cmdListeners.contains(l)) {
        cmdListeners.removeOne(l);
    }
}

/*public*/ SprogConstants::SprogState SprogTrafficController::getSprogState() {
    return sprogState;
}

/*public*/ void SprogTrafficController::setSprogState(SprogConstants::SprogState s) {
    this->sprogState = s;
    if (s == SprogConstants::SprogState::V4BOOTMODE) {
        // enable flow control - required for sprog v4 bootloader
        getController()->setHandshake(QSerialPort::HardwareControl);//SerialPort::FLOWCONTROL_RTSCTS_IN
//
    } else {
        // disable flow control
        // removed Jan 2010 - this stops SPROG from sending. Could cause problems with
        // serial Sprogs, but I have no way of testing:
        // getController().setHandshake(0);
    }
    log->debug(tr("Setting sprogState %1").arg(s));
}

/*public*/ bool SprogTrafficController::isNormalMode() {
    return sprogState == SprogConstants::SprogState::NORMAL;
}

/*public*/ bool SprogTrafficController::isSIIBootMode() {
    return sprogState == SprogConstants::SprogState::SIIBOOTMODE;
}

/*public*/ bool SprogTrafficController::isV4BootMode() {
    return sprogState == SprogConstants::SprogState::V4BOOTMODE;
}

//@SuppressWarnings("unchecked")
/*private*/ /*synchronized*/ QVector<SprogListener*> SprogTrafficController::getCopyOfListeners() {
    return QVector<SprogListener*> (cmdListeners/*.clone()*/);
}

/*protected*/ /*synchronized*/ void SprogTrafficController::notifyMessage(SprogMessage* m, SprogListener* originator)
{
 for (SprogListener* listener : this->getCopyOfListeners())
 {
  try
  {
   // don't send it back to the originator!
   if (listener != originator)
   {
    // skip forwarding to the last sender for now, we'll get them later
    if (lastSender != listener)
    {
     connect(this, SIGNAL(do_notifyMessage(SprogMessage*)), listener, SLOT(notifyMessage(SprogMessage*)));
        //listener->notifyMessage(m);
     emit do_notifyMessage(m);
     disconnect(this, SIGNAL(do_notifyMessage(SprogMessage*)), listener, SLOT(notifyMessage(SprogMessage*)));

    }
   }
  }
  catch (Exception* e)
  {
      log->warn(tr("notify: During dispatch to %1\nException %2").arg(listener->metaObject()->className()).arg(e->getMessage()));
  }
 }
 // forward to the last listener who sent a message
 // this is done _second_ so monitoring can have already stored the reply
 // before a response is sent
 if (lastSender != NULL && lastSender != originator) {
     lastSender->notifyMessage(m);
 }
}

/*protected*/ /*synchronized*/ void SprogTrafficController::notifyReply(SprogReply* r) {
    for (SprogListener* listener : this->getCopyOfListeners()) {
        try {
            // don't send message back to the originator!
            // skip forwarding to the last sender for now, we'll get them later
            if (lastSender != listener) {
                listener->notifyReply(r);
            }

        } catch (Exception* e) {
            log->warn(tr("notify: During dispatch to %1\nException %2").arg(listener->metaObject()->className()).arg(e->getMessage()));
        }
    }
    // forward to the last listener who sent a message
    // this is done _second_ so monitoring can have already stored the reply
    // before a response is sent
    if (lastSender != NULL) {
        lastSender->notifyReply(r);
    }
}

/*protected*/ /*synchronized*/ void SprogTrafficController::notifyReply(SprogReply* r, SprogListener* lastSender)
{
 log->debug(tr("notifyReply starts last sender: %1").arg(lastSender->metaObject()->className()));
 for (SprogListener* listener : this->getCopyOfListeners())
 {

  try
  {
   //if is message don't send it back to the originator!
   // skip forwarding to the last sender for now, we'll get them later
   if (lastSender != listener)
   {
    log->debug(tr("Notify listener: %1 %2").arg(listener->metaObject()->className()).arg(r->toString()));
    //listener->notifyReply(r);
    connect(this, SIGNAL(on_notifyReply(SprogReply*)), listener, SLOT(notifyReply(SprogReply*)));
    emit on_notifyReply(r);
    disconnect(this, SIGNAL(on_notifyReply(SprogReply*)), listener, SLOT(notifyReply(SprogReply*)));
   }
  }
  catch (Exception* e)
  {
   log->warn(tr("notify: During dispatch to %1\nException: %2").arg(listener->metaObject()->className()).arg(e->getMessage()));
  }
 }

 // forward to the last listener who sent a message
 // this is done _second_ so monitoring can have already stored the reply
 // before a response is sent
 if (lastSender != NULL)
 {
  log->debug(tr("notify last sender: %1%2").arg(lastSender->metaObject()->className()).arg(r->toString()));
  //lastSender->notifyReply(r);
  connect(this, SIGNAL(on_notifyReply(SprogReply*)), lastSender, SLOT(notifyReply(SprogReply*)));
  emit on_notifyReply(r);
  disconnect(this, SIGNAL(on_notifyReply(SprogReply*)), lastSender, SLOT(notifyReply(SprogReply*)));

 }
 r= new SprogReply();
}

/**
 * Forward a preformatted message to the interface.
 *
 * @param m The message to be forwarded
 */
/*public*/ void SprogXmtWorker::sendSprogMessage(SprogMessage* m) {
    // stream to port in single write, as that's needed by serial
#if 0
    try {
#endif
//        if (ostream != NULL) {

         QByteArray bytes = m->getFormattedMessage(myTC->sprogState);
         emit writeData(bytes);
//        } else {
//            // no stream connected
//            myTC->log->warn("sendMessage: no connection established");
//        }
#if 0
    } catch (Exception* e) {
        myTC->log->warn("sendMessage: Exception: " + e->getMessage());
    }
#endif

}

/**
 * Forward a preformatted message to the actual interface (by calling
 * SendSprogMessage(SprogMessage) after notifying any listeners.
 * <p>
 * Notifies listeners.
 *
 * @param m         Message to send
 * @param replyTo   Who is sending the message
 */
//@Override
/*public*/ /*synchronized*/ void SprogTrafficController::sendSprogMessage(SprogMessage* m, SprogListener* replyTo) {

    if (waitingForReply)
    {
     try
     {
      log->debug("Waiting for a reply");
#if 1
      SleeperThread::msleep(100); // Will wait until notify()ed or 100ms timeout/

#endif
     } catch (InterruptedException e) {
         log->debug("waitingForReply interrupted");
     }
    }
    log->debug("Setting waitingForReply");
    waitingForReply = true;

    log->debug(tr("sendSprogMessage message: [%1] id: %2 from %3").arg( m->toString(isSIIBootMode())).arg(m->getId()).arg(replyTo->metaObject()->className()));
    // remember who sent this
    log->debug("Updating last sender {}");
    lastSender = replyTo;
    lastId = m->getId();
    // notify all _other_ listeners
    notifyMessage(m, replyTo);
    //this->sendSprogMessage(m);
    emit sendSprogMessage(m);
}

/**
 * Make connection to existing PortController object.
 *
 * @param p The port controller
 */
/*public*/ void SprogTrafficController::connectPort(AbstractPortController* p) {
    istream = p->getInputStream();
    ostream = p->getOutputStream();
    if (controller != NULL)
    {
     log->warn("connectPort: connect called while connected");
    }
    controller = p;

    // create worker threads
//    SprogRcvWorker* rcvWorker = new SprogRcvWorker(this->reply, this);
//    QThread* rcvThread = new QThread();
//    rcvThread->setObjectName("SprogRcvThread");
//    rcvWorker->moveToThread(rcvThread);
//    connect(this, SIGNAL(readyRead()), rcvWorker, SLOT(handleOneIncomingReply()));
//    connect(rcvWorker, SIGNAL(finished()), rcvThread, SLOT(quit()));
//    connect(rcvWorker, SIGNAL(sendReply(SprogReply*)),this, SLOT(sendreply(SprogReply*)));
//    connect(rcvThread, SIGNAL(started()), rcvWorker, SLOT(process()));
//    rcvThread->start();

    SprogXmtWorker* xmtWorker = new SprogXmtWorker( this);
    QThread* xmtThread = new QThread();
    xmtThread->setObjectName("SprogXmtThread");
    xmtWorker->moveToThread(xmtThread);
    connect(xmtThread, SIGNAL(started()), xmtWorker, SLOT(process()));
    connect(xmtWorker, SIGNAL(finished()), xmtThread, SLOT(quit()));
    connect(this, SIGNAL(sendSprogMessage(SprogMessage*)), xmtWorker, SLOT(sendSprogMessage(SprogMessage*)));
    xmtThread->start();
}

SprogRcvWorker::SprogRcvWorker(SprogReply* reply, SprogTrafficController *myTC)
{
 this->adapter = myTC->getController();
 this->myTC = myTC;
 this->reply = reply;
 //connect(istream->device(), SIGNAL(readyRead()), this, SLOT(handleOneIncomingReply()));

}

SprogXmtWorker::SprogXmtWorker(SprogTrafficController *myTC)
{
 this->myTC = myTC;
 connect(this, SIGNAL(writeData(QByteArray)), (SprogSerialDriverAdapter*) myTC->getController(), SLOT(writeData(QByteArray)));
}

void SprogXmtWorker::process()
{
 //ostream = new QDataStream(activeSerialPort);
}

/**
 * Get the port controller, as a SerialDriverAdapter.
 *
 * @return the port controller
 */
/*protected*/ SprogSerialDriverAdapter* SprogTrafficController::getController(){
   return (SprogSerialDriverAdapter*) controller;
}

/**
 * Break connection to existing SprogPortController object.
 * <p>
 * Once broken, attempts to send via "message" member will fail.
 */
/*public*/ void SprogTrafficController::disconnectPort(AbstractPortController* p) {
    istream = NULL;
    ostream = NULL;
    if (controller != p) {
        log->warn("disconnectPort: disconnect called from non-connected SprogPortController");
    }
    controller = NULL;
}

/**
 * Static function returning the SprogTrafficController instance to use.
 *
 * @return The registered SprogTrafficController instance for general use,
 *         if need be creating one.
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*static*/ /*public*/ SprogTrafficController* SprogTrafficController::instance() {
    return NULL;
}

/*static*/ /*volatile*/ /*protected*/ SprogTrafficController* SprogTrafficController::self = NULL;

/*public*/ void SprogTrafficController::setAdapterMemo(SprogSystemConnectionMemo* adaptermemo) {
    memo = adaptermemo;
}

/*public*/ SprogSystemConnectionMemo* SprogTrafficController::getAdapterMemo() {
    return memo;
}


bool SprogTrafficController::endReply(SprogReply* msg) {
#if 1
    return msg->endNormalReply() || msg->endBootReply()
            || msg->endBootloaderReply(getSprogState());
#endif
}

/**
 * Respond to an event triggered by RXTX.
 * <p>
 * In this case we are only dealing with DATA_AVAILABLE but the other
 * events are left here for reference.
 *
 * @author AJB Jan 2010
 */
//@Override
/*public*/ void SprogTrafficController::serialEvent(SerialPortEvent* event) {
#if 0
    switch (event.getEventType()) {
        case SerialPortEvent.BI:
        case SerialPortEvent.OE:
        case SerialPortEvent.FE:
        case SerialPortEvent.PE:
        case SerialPortEvent.CD:
        case SerialPortEvent.CTS:
        case SerialPortEvent.DSR:
        case SerialPortEvent.RI:
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
            break;
        case SerialPortEvent.DATA_AVAILABLE:
            log->debug("Data Available");
            handleOneIncomingReply();
            break;
        default:
            log->warn("Unhandled serial port event code: {}", event.getEventType());
            break;
    }
#endif
}

/**
 * Handle an incoming reply.
 */
/*public*/ void SprogTrafficController::handleReadyRead()
{
 emit readyRead(); //pass to SprogRcvWorker
}


/*public*/ void SprogRcvWorker::process()
{
 while(true)
 {
  if(adapter->activeSerialPort->isOpen())
  {
   adapter->activeSerialPort->waitForReadyRead(-1);
//   handleOneIncomingReply();
  }
 }
}


/*public*/ void SprogTrafficController::handleOneIncomingReply()
{
 // we get here if data has been received and this method is explicitly invoked
 // fill the current reply with any data received
 int replyCurrentSize = this->reply->getNumDataElements();
 int i;
 for (i = replyCurrentSize; i < SprogReply::maxSize - replyCurrentSize; i++)
 {
  try
  {
   //if (istream->available() == 0)
   if(istream->device()->bytesAvailable() == 0)
   {
       break; // nothing waiting to be read
   }
   //char char1 = istream.readByte();
   char char1;
   istream->device()->read(&char1,1);
   this->reply->setElement(i, char1);
  }
  catch (Exception* e)
  {
   log->warn(tr("Exception in DATA_AVAILABLE state: %1").arg(e->getMessage()));
  }
  if (endReply(this->reply))
  {
   sendreply();
   //emit sendReply(this->reply);
   break;
  }
 }
}

/**
 * Send the current reply - built using data from serialEvent.
 */
/*private*/ void SprogTrafficController::sendreply()
{
 //send the reply
 if (log->isDebugEnabled())
 {
  log->debug(tr("dispatch reply of length %1").arg(this->reply->getNumDataElements()));
 }
#if 1
 {
  /*final*/ SprogReply* thisReply = this->reply;
  /*final*/ SprogListener* thisLastSender = this->lastSender;
  /*final*/ int thisLastId = this->lastId;
  if (unsolicited) {
      log->debug("Unsolicited Reply");
      thisReply->setUnsolicited();
  }
  // Insert the id
  thisReply->setId(thisLastId);
  /*final*/ SprogTrafficController* thisTC = this;
  // return a notification via the queue to ensure end

  //        Runnable r = new Runnable() {
  SprogReply* replyForLater = thisReply;
  SprogListener* lastSenderForLater = thisLastSender;
#if 1
//            SprogTrafficController myTC = thisTC;

//            //@Override
//            /*public*/ void run() {
//                log->debug("Delayed notify starts [{}]", replyForLater.toString());
//                myTC.notifyReply(replyForLater, lastSenderForLater);
//            }
//        };
  ReplyWorker* replyWorker = new ReplyWorker(thisReply, thisLastSender, thisTC);
  QThread* thread = new QThread();
  connect(thread, SIGNAL(started()), replyWorker, SLOT(run()));
  connect(replyWorker, SIGNAL(finished()), thread, SLOT(quit()));
  replyWorker->moveToThread(thread);
  //javax.swing.SwingUtilities.invokeLater(r);
  thread->start();
#else
  qApp->processEvents();
  log->debug(tr("Delayed notify starts [%1]").arg(replyForLater->toString()));
  notifyReply(replyForLater, lastSenderForLater);
#endif
 }

 // Do this after reply is despatched to avoid this->reply and .lastSender
 // being overwritten by a new reply
 //synchronized (this) {
 qApp->processEvents();

     log->debug("Clearing waitingForReply");
     waitingForReply = false;
//        notify();
 //}

 //Create a new reply, ready to be filled
 this->reply = new SprogReply();
#endif
}

ReplyWorker::ReplyWorker(SprogReply *replyForLater, SprogListener *lastSenderForLater, SprogTrafficController *myTC)
{
 this->replyForLater = replyForLater;
 this->lastSenderForLater = lastSenderForLater;
 this->myTC = myTC;
}

void ReplyWorker::run()
{
 myTC->log->debug(tr("Delayed notify starts [%1]").arg(replyForLater->toString()));
 myTC->notifyReply(replyForLater, lastSenderForLater);
 emit finished();
}

int SprogTrafficController::bytesAvailable()
{
 return istream->device()->bytesAvailable();
}

/*private*/ /*final*/ /*static*/ Logger* SprogTrafficController::log = LoggerFactory::getLogger("SprogTrafficController");
