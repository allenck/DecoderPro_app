#ifndef ABSTRACTMRTRAFFICCONTROLLER_H
#define ABSTRACTMRTRAFFICCONTROLLER_H

#include <QObject>
#include "logger.h"
#include <QVector>
#include <QMutex>
#include "exceptions.h"
#include "abstractportcontroller.h"
#include "runnable.h"
#include <QLinkedList>
#include "rfid/rfidinterface.h"

class AMRTXmtHandler;
class AMRTRcvHandler;
class AbstractMRListener;
class AbstractMRMessage;
class AbstractMRReply;
class AbstractMRTrafficController : public RfidInterface
{
    Q_OBJECT
public:
    //explicit AbstractMRTrafficController(QObject *parent = 0);
    /*public*/ AbstractMRTrafficController(QObject *parent = 0);
    /*public*/ AbstractMRTrafficController* getSelfLock();
    /*public*/ static /*final*/ const int NORMALMODE=1;
    /*public*/ static /*final*/ const int PROGRAMINGMODE=4;
    /*public*/ static /*final*/ const int IDLESTATE = 10;        // nothing happened
    /*public*/ static /*final*/ const int NOTIFIEDSTATE = 15;    // xmt notified, will next wake
    /*public*/ static /*final*/ const int WAITMSGREPLYSTATE = 25;  // xmt has sent, await reply to message
    /*public*/ static /*final*/ const int WAITREPLYINPROGMODESTATE = 30;  // xmt has done mode change, await reply
    /*public*/ static /*final*/ const int WAITREPLYINNORMMODESTATE = 35;  // xmt has done mode change, await reply
    /*public*/ static /*final*/ const int OKSENDMSGSTATE = 40;        // mode change reply here, send original msg
    /*public*/ static /*final*/ const int AUTORETRYSTATE = 45;        // received message where automatic recovery may occur with a retransmission, re-send original msg
    /*public*/ static /*final*/ const int POLLSTATE = 50;			// Send program mode or poll message
    /*public*/ bool hasTimeouts();
    /*public*/ AbstractPortController* controller;// = NULL;
    /*public*/ virtual bool status();
    /*public*/ virtual void connectPort(AbstractPortController* p);
    /*public*/ virtual QString getPortName();
    /*public*/ virtual void disconnectPort(AbstractPortController* p);
    /*public*/ virtual bool portReadyToSend(AbstractPortController* p) throw (Exception);
    /*public*/ virtual void receiveLoop();
    /*public*/ virtual void handleOneIncomingReply() throw (IOException);
    /*public*/ AbstractMRListener* getLastSender();

    
signals:
 void messageProcessed(AbstractMRMessage* msg, bool bOutput =false);
 void sendMessage(AbstractMRMessage*);
 void replyRcvd(AbstractMRMessage* );
 void messageSent(AbstractMRMessage*);

private:
 static Logger* log;
 // this is a local variable, used here only;
 // it's not the instance() variable, which is static
 // and done in individual subclasses.
 /*private*/ AbstractMRTrafficController* selfLock;  // this is needed for synchronization
 QMutex mutex;
 /**
  * Messages to be transmitted
  */
 QLinkedList<AbstractMRMessage*>* msgQueue;// = new QLinkedList<AbstractMRMessage*>();
 QLinkedList<AbstractMRListener*>* listenerQueue;// = new QLinkedList<AbstractMRListener*>();
 /*private*/ void transmitLoop();
 // Dispatch control and timer
 /*protected*/ bool replyInDispatch;// = false;          // true when reply has been received but dispatch not completed
 /*private*/ int maxDispatchTime;// = 0;
 /*private*/ int warningMessageTime;// = DISPATCH_WARNING_TIME;
 /*private*/ static /*final*/ const int DISPATCH_WAIT_INTERVAL = 100;
 /*private*/ static /*final*/ const int DISPATCH_WARNING_TIME = 12000; // report warning when max dispatch time exceeded
 /*private*/ static /*final*/ const int WARN_NEXT_TIME = 1000;         // report every second
 /*private*/ bool timeoutFlag;// = false;
 /*private*/ int timeouts;// = 0;
 bool connectionError;//=false;
 /*private*/ void recovery();
 // Defined this way to reduce new object creation
 /*private*/ QByteArray* rcvBuffer;// = new byte[1];
 /*private*/ void checkReplyInDispatch();
 void startThreads();
 AMRTXmtHandler* xmtHandler = nullptr;
 AMRTRcvHandler* rcvHandler = nullptr;
 bool fulldebug = true;
 bool debug = true;
 bool echo = true;

private slots:
 void msgRcvd(AbstractMRMessage** m);
 void msgTransmitted(AbstractMRMessage*);


protected:

 /**
  * Flag that threads should terminate as soon as they can.
  */
 /*protected*/ volatile bool threadStopRequest;/// = false;
 // set the instance variable
 /*abstract*/virtual  /*protected*/ void setInstance() {}

 // The methods to implement the abstract Interface

 /*protected*/ QVector<AbstractMRListener*>* cmdListeners;// = new Vector<AbstractMRListener>();

 /*protected*/ /*synchronized*/ void addListener(AbstractMRListener* l);
 /*protected*/ /*synchronized*/ void removeListener(AbstractMRListener* l);
 /*protected*/ void notifyMessage(AbstractMRMessage* m, AbstractMRListener* notMe);
 /*abstract*/ /*protected*/ virtual void forwardMessage(AbstractMRListener* client, AbstractMRMessage* m) = 0;
 /*abstract*/ /*protected*/ virtual AbstractMRMessage* pollMessage() {return NULL;}
 /*abstract*/ /*protected*/ virtual AbstractMRListener* pollReplyHandler() {return NULL;}
 /*protected*/ AbstractMRListener* mLastSender;// = NULL;

 volatile /*protected*/ int mCurrentMode;
 /*abstract*/ /*protected*/ virtual AbstractMRMessage* enterProgMode() {return NULL;}
 /*abstract*/ /*protected*/  virtual AbstractMRMessage* enterNormalMode()  {return NULL;}
 /*protected*/ bool programmerIdle();
 /*protected*/ int enterProgModeDelayTime();
 volatile /*protected*/ int mCurrentState;
 /*protected*/ bool allowUnexpectedReply;
 /*protected*/ void setAllowUnexpectedReply(bool expected);
 /*protected*/ void notifyReply(AbstractMRReply* r, AbstractMRListener* dest);
 /*abstract*/ /*protected*/ virtual void forwardReply(AbstractMRListener* client, AbstractMRReply* m) {}
 /*synchronized*/ /*protected*/ void sendMessage(AbstractMRMessage* m, AbstractMRListener* reply);
 /*protected*/ void transmitWait(int waitTime, int state, QString InterruptMessage);
 /*protected*/ bool flushReceiveChars = false;
 /*protected*/ virtual void handleTimeout(AbstractMRMessage* msg,AbstractMRListener* l);
 /*protected*/ virtual void resetTimeout(AbstractMRMessage* msg);
 /*protected*/ virtual int addHeaderToOutput(QByteArray* msg, AbstractMRMessage* m);
 /*protected*/ int mWaitBeforePoll;// = 100;
 /*protected*/ long waitTimePoll;// = 0;
 /*protected*/ virtual void addTrailerToOutput(QByteArray* msg, int offset, AbstractMRMessage* m);
 /*protected*/ virtual int lengthOfByteStream(AbstractMRMessage* m);
 //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
 // String + only used for debug, so inefficient String processing not really a problem
 // though it would be good to fix it if you're working in this area
 /*protected*/ bool xmtException = false;
 /*synchronized*/ /*protected*/ virtual void forwardToPort(AbstractMRMessage* m, AbstractMRListener* reply);
 /*protected*/ virtual void connectionWarn() ;
 /*protected*/ virtual void portWarn(Exception e);
 /*protected*/ virtual void portWarnTCP(Exception e);
 QThread* xmtThread = nullptr;
 /*protected*/ Runnable* xmtRunnable = nullptr;
 QThread* rcvThread;// = NULL;
 // data members to hold the streams
 /*protected*/ QDataStream* istream = nullptr;
 /*protected*/ QDataStream* ostream = nullptr;

 /*protected*/ bool rcvException = false;

 /*protected*/ int maxRcvExceptionCount;// = 100;
 /*protected*/ virtual void reportReceiveLoopException(Exception e);
 /*abstract*/ /*protected*/ virtual AbstractMRReply* newReply(){return NULL;}
 /*abstract*/ /*protected*/ virtual bool endOfMessage(AbstractMRReply* /*r*/) {return false;}
 /*protected*/ virtual void waitForStartOfReply(QDataStream* istream) throw (IOException);
 /*protected*/ char readByteProtected(QDataStream* istream) throw (IOException);
 /*protected*/ virtual void loadChars(AbstractMRReply* msg, QDataStream* istream) throw (IOException);
 /*protected*/ virtual bool canReceive();
 /*protected*/ /*final*/ virtual void finalize() throw (Throwable);
 /*protected*/ virtual void terminate();
// friend class RcvNotifier;
// friend class XmtNotifier;
// friend class CleanupHook;
// friend class XmitWorker;
// friend class RcvWorker;
 friend class AMRTXmtHandler;
 friend class AMRTRcvHandler;
};

#if 0
/**
 * Internal class to remember the Reply object and destination
 * listener with a reply is received.
 */
/*protected*/ /*static*/ class RcvNotifier : public Runnable
{
 AbstractMRReply* mMsg;
 AbstractMRListener* mDest;
 AbstractMRTrafficController* mTC;
public:
 RcvNotifier(AbstractMRReply* pMsg, AbstractMRListener* pDest, AbstractMRTrafficController* pTC, QObject* parent = 0) : Runnable(parent)
 {
  mMsg = pMsg;
  mDest = pDest;
  mTC = pTC;
 }
 Logger log;
 /*public*/ void run()
 {
  log.debug("Delayed rcv notify starts");
   mTC->notifyReply(mMsg, mDest);
 }
 friend class AbstractMRTrafficController;
}; // end RcvNotifier

/**
 * Internal class to remember the Message object and destination
 * listener when a message is queued for notification.
 */
/*protected*/ /*static*/ class XmtNotifier : public Runnable
{
    AbstractMRMessage* mMsg;
    AbstractMRListener* mDest;
    AbstractMRTrafficController* mTC;
    Logger log;
public:

    /*public*/ XmtNotifier(AbstractMRMessage* pMsg, AbstractMRListener* pDest, AbstractMRTrafficController* pTC, QObject* parent = 0) : Runnable(parent)
    {
        mMsg = pMsg;
        mDest = pDest;
        mTC = pTC;
    }
    /*public*/ void run() {
        log.debug("Delayed xmt notify starts");
        mTC->notifyMessage(mMsg, mDest);
    }
};  // end XmtNotifier

/**
 * Internal class to handle traffic controller cleanup.
 * the primary task of this thread is to make sure the DCC system has
 * exited service mode when the program exits.
 */
/*static*/ class CleanupHook : public  Runnable
{
    AbstractMRTrafficController* mTC;

    CleanupHook(AbstractMRTrafficController* pTC, QObject* parent) : Runnable(parent)
    {
        mTC = pTC;
    }
public:
    /*public*/ void run() {
        mTC->terminate();
    }
}; // end cleanUpHook

class XmitWorker : public QObject
{
 Q_OBJECT
 AbstractMRTrafficController* amrtc;
public:
 XmitWorker(AbstractMRTrafficController* amrtc);

public slots:
 void run();

signals:
 void finished();

};

class RcvWorker : public QObject
{
 Q_OBJECT
 AbstractMRTrafficController* amrtc;
public:
 RcvWorker( AbstractMRTrafficController* amrtc) { this->amrtc = amrtc;}
public slots:
 void run()
 {
  amrtc->receiveLoop();
  emit finished();
 }

signals:
 void finished();


};
#endif
/**
 * Captive class to handle incoming characters.  This is a permanent loop,
 * looking for input messages in character form on the
 * stream connected to the LnPortController via <code>connectPort</code>.
 */
class AMRTRcvHandler : public QThread
{
 Q_OBJECT
 public:
 /**
  * Remember the LnPacketizer object
  */
 AbstractMRTrafficController* trafficController;
 Logger log;
 /*public*/ AMRTRcvHandler(AbstractMRTrafficController* lt)
 {
  trafficController = lt;
 }

 //@SuppressWarnings("NULL")
 /*public*/ void run();// throw(LocoNetMessageException, EOFException, IOException, Exception);

signals:
 void passMessage(Message* msg);

public slots:
 //void dataAvailable();
 /**
  * Read a single byte, protecting against various timeouts, etc.
  * <P>
  * When a gnu.io port is set to have a
  * receive timeout (via the enableReceiveTimeout() method),
  * some will return zero bytes or an EOFException at the end of the timeout.
  * In that case, the read should be repeated to get the next real character.
  *false
  */
protected:
};


/**
 * Captive class to handle transmission
 */
class AMRTXmtHandler : public QThread
{
  Q_OBJECT
public:
 /**
  * Remember the LnPacketizer object
  */
 AbstractMRTrafficController* trafficController;
 Logger log;
 /*public*/ AMRTXmtHandler(AbstractMRTrafficController* lt) {
  trafficController = lt;
 }
 /*public*/ void run();
signals:
public slots:
 void sendMessage(AbstractMRMessage *m);

protected:
 /**
  * When a message is finally transmitted, forward it
  * to listeners if echoing is needed
  *
  */
 /*protected*/ void messageTransmitted(const char */*msg*/) {
  if (trafficController->debug) log.debug(tr("message transmitted"));
  if (!trafficController->echo) return;
  // message is queued for transmit, echo it when needed
  // return a notification via the queue to ensure end
  //invokeLater(new Echo(this, new LocoNetMessage(msg)));
 }

};
#endif // ABSTRACTMRTRAFFICCONTROLLER_H
