#ifndef LNPACKETIZER_H
#define LNPACKETIZER_H
#include "lntrafficcontroller.h"
#include "lnportcontroller.h"
//#include "runnable.h"
#include <QDataStream>
#include "exceptions.h"
//#include "masterthread.h"
#include <QtSerialPort/QSerialPort>
//#include "llnmon.h"
#include "sleeperthread.h"

//#define USE_THREAD
/**
 * Converts Stream-based I/O to/from LocoNet messages.  The "LocoNetInterface"
 * side sends/receives LocoNetMessage objects.  The connection to
 * a LnPortController is via a pair of *Streams, which then carry sequences
 * of characters for transmission.
 *<P>
 * Messages come to this via the main GUI thread, and are forwarded back to
 * listeners in that same thread.  Reception and transmission are handled in
 * dedicated threads by RcvHandler and XmtHandler objects.  Those are internal
 * classes defined here. The thread priorities are:
 *<P><UL>
 *<LI>  RcvHandler - at highest available priority
 *<LI>  XmtHandler - down one, which is assumed to be above the GUI
 *<LI>  (everything else)
 *</UL>
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * @author			Bob Jacobsen  Copyright (C) 2001
 * @version 		$Revision: 18943 $
 *
 */
class QWaitCondition;
class LnPortController;
class LIBPR3SHARED_EXPORT LnPacketizer : public LnTrafficController
{
 Q_OBJECT
public:
 LnPacketizer(LocoNetSystemConnectionMemo* m, QObject* parent = 0);
//#ifdef USE_THREAD
 /**
  * Implement abstract method to signal if there's a backlog
  * of information waiting to be sent.
  * @return true if busy, false if nothing waiting to send
  */
 /**
  * Invoked at startup to start the threads needed here.
  */
 void startThreads();
//#endif
 /**
  * Forward a preformatted LocoNetMessage to the actual interface.
  *
  * Checksum is computed and overwritten here, then the message
  * is converted to a byte array and queue for transmission
  * @param m Message to send; will be updated with CRC
  */
  void sendLocoNetMessage(LocoNetMessage* m);

  // data members to hold the streams. These are public so the inner classes defined here
     // can access whem with a Java 1.1 compiler
  QDataStream* istream = nullptr;
  QDataStream* ostream = nullptr;
  //QBuffer* iBuf;
  QByteArray* baStream = nullptr;
  static QWaitCondition* dataAvailable;

  QThread* rcvThread = nullptr;
  QThread* xmtThread = nullptr;
 /*
  * Make connection to existing LnPortController object.
  * @param p Port controller for connected. Save this for a later
  *              disconnect call
  */
 void connectPort(LnPortController* p);
 //    // The methods to implement the LocoNetInterface
 /*public*/ bool status();
#ifdef USE_THREAD
 /**
  * Synchronized list used as a transmit queue.
  * <P>
  * This is public to allow access from the internal class(es) when compiling with Java 1.1
  */
// /*public*/ QLinkedList<QByteArray> xmtList;
 QByteArray xmtBuffer;
#endif
 /**
  * Implement abstract method to signal if there's a backlog
  * of information waiting to be sent.
  * @return true if busy, false if nothing waiting to send
  */
 /*public*/  bool isXmtBusy();
 // methods to connect/disconnect to a source of data in a LnPortController
 // This is public to allow access from the internal class(es) when compiling with Java 1.1
 /*public*/ LnPortController* controller;

 /**
  * Break connection to existing LnPortController object. Once broken,
  * attempts to send via "message" member will fail.
  * @param p previously connected port
  */
 /*public*/ void disconnectPort(LnPortController* p);
 /**
  * Handle incoming characters.  This is a permanent loop,
  * looking for input messages in character form on the
  * stream connected to the LnPortController via <code>connectPort</code>.
  * Terminates with the input stream breaking out of the try block.
  */
// @SuppressWarnings("NULL")
#ifdef USE_THREAD
/*public*/ void run();// throw(LocoNetMessageException, EOFException, IOException, Exception);
#endif
 static QString hexStringFromBytes(const QByteArray &a)
 {
  QString s;
  foreach(char c, a)
  {
   s.append(QString("%1 ").arg((c &0xFF),0,16));
  }
  return s;
 }
// void setThread(MasterThread* thread);
 //void setSerial(QSerialPort* serial);
 /**
  * Synchronized list used as a transmit queue.
  * <P>
  * This is public to allow access from the internal class(es) when compiling with Java 1.1
  */
 /*public*/ QLinkedList<QByteArray*>* xmtList;// = new QLinkedList<QByteArray>();

// MasterThread* thread;
public slots:
 void rcvTerminated();

signals:
 void messageProcessed(LocoNetMessage* msg, bool bOutput =false);
 void sendMessage(LocoNetMessage *);

private:
 /*final*/ /*static*/ bool fulldebug = false;
    bool debug;
    // Defined this way to reduce new object creation
    /*private*/ char rcvBuffer[1];
 Logger* log;
 QSerialPort* serial = nullptr;
 QMutex mutex1; // used for QWaitCondition in RcvHandler
 QMutex mutex2;
 QMutex mutex3;
 LocoNetMessage* priorMsg = nullptr; //=NULL;
 //LlnMon* monitor;
 QObject* parent;
 LocoNetSystemConnectionMemo *memo = nullptr;

private slots:
#ifndef USE_THREAD
 void dataReady();
#endif
 void loconetMsgRcvd(LocoNetMessage* m);
 void msgTransmitted(const QVector<char> &v);
 protected:
    /**
     * true if the external hardware is not echoing messages,
     * so we must
     */
    /*protected*/ bool echo;  // echo messages here, instead of in hardware
#ifdef USE_THREAD
    /**
     * XmtHandler (a local class) object to implement the transmit thread
     */
    /*protected*/ QThread* xmtHandler  = nullptr;

    /**
     * RcvHandler (a local class) object to implement the receive thread
     */
    /*protected*/ QThread* rcvHandler  = nullptr;
    /**
     * Read a single byte, protecting against various timeouts, etc.
     * <P>
     * When a gnu.io port is set to have a
     * receive timeout (via the enableReceiveTimeout() method),
     * some will return zero bytes or an EOFException at the end of the timeout.
     * In that case, the read should be repeated to get the next real character.
     *
     */
 //MasterThread* thread;
protected:
 /*protected*/ char readByteProtected(QDataStream* istream) /*throw(IOException)*/; // throws java.io.IOException
 friend class RcvHandler;
 friend class XmtHandler;
#endif
 friend class PR3Adapter;
 friend class LnOverTcpPacketizer;
 friend class LnTcpDriverAdapter;
 friend class LnPacketizerStrict;
};
//bool LnPacketizer::fulldebug;

#ifdef USE_THREAD
/**
 * Captive class to handle incoming characters.  This is a permanent loop,
 * looking for input messages in character form on the
 * stream connected to the LnPortController via <code>connectPort</code>.
 */
class RcvHandler : public QThread
{
 Q_OBJECT
 public:
 /**
  * Remember the LnPacketizer object
  */
 LnPacketizer* trafficController;
 Logger log;
 /*public*/ RcvHandler(LnPacketizer* lt)
 {
  trafficController = lt;
 }

 //@SuppressWarnings("NULL")
 /*public*/ void run();// throw(LocoNetMessageException, EOFException, IOException, Exception);

signals:
 void passMessage(LocoNetMessage* msg);

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
class XmtHandler : public QThread
{
  Q_OBJECT
public:
 /**
  * Remember the LnPacketizer object
  */
 LnPacketizer* trafficController;
 Logger log;
 /*public*/ XmtHandler(LnPacketizer* lt) {
  trafficController = lt;
 }
 /*public*/ void run();
signals:
public slots:
 void sendMessage(LocoNetMessage* m);

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
//class Echo : QThread
//{
// Q_OBJECT
// public:
// Echo(LnPacketizer* t, LocoNetMessage* m)
// {
//  myTc = t;
//  msgForLater = m;
// }
// LocoNetMessage* msgForLater;
// LnPacketizer* myTc;

// /*public*/ void run() {
//  myTc->notify(msgForLater);
// }
//};
#endif
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnPacketizer.class.getName());

#endif // LNPACKETIZER_H
