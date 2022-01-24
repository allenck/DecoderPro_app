#include "lnpacketizer.h"
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include "lnprogrammermanager.h"

//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//                    justification="Only used during system initialization")
//    public LnPacketizer() {
//    	self=this;
//    	debug = log->isDebugEnabled();
//   	}
QWaitCondition* LnPacketizer::dataAvailable = new QWaitCondition();

LnPacketizer::LnPacketizer(LocoNetSystemConnectionMemo *m, QObject* parent)
{
 this->parent = parent;
 setObjectName("LnPacketizer");
 log = new Logger("LnPacketizer", this);
 //monitor = new LlnMon(this);
 //thread = NULL;
 serial = NULL;
 fulldebug = false;
 debug = true;
 echo = false;  // echo messages here, instead of in hardware
 debug = log->isDebugEnabled();
 controller = NULL;
 istream = NULL;
 ostream = NULL;
 baStream = new QByteArray();
#ifdef USE_THREAD
 //xmtList = new QLinkedList<char>();
 xmtHandler = NULL;
 rcvHandler = NULL;
 //rcvBuffer = new QByteArray;
 xmtList = new QLinkedList<QByteArray*>();
#endif
 priorMsg=NULL;
 // set the memo to point here
  memo = m;
  m->setLnTrafficController(this);
}
// The methods to implement the LocoNetInterface

/*public*/ bool LnPacketizer::status()
{
 bool returnVal = ( /*ostream != nullptr && istream != nullptr
         &&*/ xmtThread != nullptr && xmtThread->isRunning() && xmtHandler != nullptr
         && rcvThread != nullptr && rcvThread->isRunning() && rcvHandler != nullptr
         );
 return returnVal;

}

void LnPacketizer::connectPort(LnPortController* p)
{
 istream = p->getInputStream();
 ostream = p->getOutputStream();
 serial = p->getSerialPort();
 if (controller != NULL)
  log->warn("connectPort: connect called while connected");
 controller = p;
#ifdef USE_THREAD
 startThreads();
#endif
}
bool LnPacketizer::isXmtBusy()
{
 if (controller == NULL) return false;
 return (!controller->okToSend());
}

void LnPacketizer::sendLocoNetMessage(LocoNetMessage* m)
{
 //LnProgrammerManager* mgr = qobject_cast<LnProgrammerManager*>(memo->programmerManager);
 QMutexLocker locker(&mutex2);

 // update statistics
 transmittedMsgCount++;

 // set the error correcting code byte(s) before transmittal
 m->setParity();
 LocoNetMessage* msgcopy = new LocoNetMessage(*m);
 emit sendMessage(msgcopy);
 //mgr = qobject_cast<LnProgrammerManager*>(memo->programmerManager);

}
/**
 * Break connection to existing LnPortController object. Once broken,
 * attempts to send via "message" member will fail.
 * @param p previously connected port
 */
/*public*/ void LnPacketizer::disconnectPort(LnPortController* p) {
 istream = nullptr;
 ostream = nullptr;
 if (controller != p)
     log->warn("disconnectPort: disconnect called from non-connected LnPortController");
 controller = nullptr;
}
#ifdef USE_THREAD
 /**
  * Invoked at startup to start the threads needed here.
  */
 void LnPacketizer::startThreads()
 {
    int priority = QThread::currentThread()->priority();
    log->debug("startThreads current priority = "+QString("%1").arg(priority)+
              " max available = "+QString("%1").arg(QThread::HighestPriority)+
              " default = "+QString("%1").arg(QThread::NormalPriority)+
              " min available = "+QString("%1").arg(QThread::LowestPriority));

    // make sure that the xmt priority is no lower than the current priority
    int xmtpriority = (QThread::HighestPriority-1 > priority ? QThread::HighestPriority-1 : QThread::HighestPriority);
    // start the XmtHandler in a thread of its own
    if( xmtHandler == NULL )
      xmtHandler = new XmtHandler(this);
    log->debug(QString("Xmt thread (%2) starts at priority %1").arg(xmtpriority).arg(xmtHandler->objectName()));
    XmtHandler* outHandler = (XmtHandler*)xmtHandler;
    connect(this, SIGNAL(sendMessage(LocoNetMessage*)), outHandler, SLOT(sendMessage(LocoNetMessage*)));

//    xmtHandler->setPriority(QThread::HighPriority); // Highest -1
    xmtHandler->start(QThread::HighPriority);
    xmtThread = xmtHandler;

    // start the RcvHandler in a thread of its own
    if( rcvHandler == NULL )
      rcvHandler = new RcvHandler(this) ;
    int rcvpriority = QThread::HighestPriority;
    log->debug(QString("rcv thread (%2) starts at priority %1").arg(rcvpriority).arg(rcvHandler->objectName()));
    RcvHandler* handler = (RcvHandler*)rcvHandler;
     connect(handler, SIGNAL(passMessage(LocoNetMessage*)), this, SLOT(loconetMsgRcvd(LocoNetMessage*)));

    connect(handler, SIGNAL(finished()), this, SLOT(rcvTerminated()));
    if (istream != NULL)
      rcvHandler->start(QThread::HighestPriority);
    rcvThread = rcvHandler;

}
#endif
void LnPacketizer::loconetMsgRcvd(LocoNetMessage *m)    // [slot]
{
 emit messageProcessed(m, false);
 //emit LnTrafficController::messageProcessed(m);
}
void LnPacketizer::rcvTerminated()
{
 log->error(QString("RcvHandler %1 has terminated").arg(QString(this->metaObject()->className())));
}

void LnPacketizer::msgTransmitted(const QVector<char> &v)   // [slot]
{
 QMutexLocker locker(&mutex3);
  LocoNetMessage* m= new LocoNetMessage(v);
  emit messageProcessed(m, true);
}
#ifdef USE_THREAD
/*public*/ void RcvHandler:: run() //throw(LocoNetMessageException, EOFException, IOException, Exception)
{
 while (true)
 {   // loop permanently, program close will exit
  int opCode=0;
  // start by looking for command -  skip if bit not set
  while ( ((opCode = (trafficController->readByteProtected(trafficController->istream)&0xFF)) & 0x80) == 0 )
  {
   if (trafficController->fulldebug) log.debug("Skipping: "+QString("%1").arg(opCode,0,16));
  }
  // here opCode is OK. Create output message
  if (trafficController->fulldebug) log.debug(" (RcvHandler) Start message with opcode: "+QString("0x%1").arg(opCode,0,16));
  LocoNetMessage* msg = NULL;
  while (msg == NULL)
  {
//    try
//    {
     // Capture 2nd byte, always present
   int byte2 = trafficController->readByteProtected(trafficController->istream)&0xFF;
   if (trafficController->fulldebug) log.debug("Byte2: "+QString("0x%1").arg(byte2,0,16));
   // Decide length
   switch((opCode & 0x60) >> 5)
   {
   case 0:     /* 2 byte message */
    msg = new LocoNetMessage(2);
    break;

   case 1:     /* 4 byte message */
    msg = new LocoNetMessage(4);
    break;

   case 2:     /* 6 byte message */
    msg = new LocoNetMessage(6);
    break;

   case 3:     /* N byte message */
    if (byte2<2)
     log.error("LocoNet message length invalid: "+QString("%1").arg(byte2)
                              +" opcode: "+QString("0x%1").arg(opCode,0,16));
    if(byte2 >= 2)
     msg = new LocoNetMessage(byte2);
    break;
   }
   if(msg == NULL)
    continue;
   // message exists, now fill it
   msg->setOpCode(opCode);
   msg->setElement(1, byte2);
   int len = msg->getNumDataElements();
   if (trafficController->fulldebug) log.debug("len: "+QString("%1").arg(len));
   for (int i = 2; i < len; i++)
   {
    // check for message-blocking error
    int b = trafficController->readByteProtected(trafficController->istream)&0xFF;
    if (trafficController->fulldebug) log.debug("char "+QString("%1").arg(i)+" is: "+QString("0x%1").arg(b,0,16));
    if ( (b&0x80) != 0) // new opcode?
    {
     log.warn("LocoNet message with opCode: "
                    +QString("%1").arg(opCode,0,16)
                    +" ended early. Expected length: "+QString("%1").arg(len)
                    +" seen length: "+QString("%1").arg(i)
                    +" unexpected byte: "
                    +QString("%1").arg(b,0,16));
     opCode = b;
     //throw new LocoNetMessageException();
     msg = NULL;
     break;
    }
    msg->setElement(i, b);
   } // end of for loop
  } // end of while (msg == NULL)
  if(msg == NULL)
   continue;
  // check parity
  if (!msg->checkParity())
  {
    log.warn("Ignore Loconet packet with bad checksum: "+msg->toString());
    //throw new LocoNetMessageException();
  }
  else
  // message is complete, dispatch it !!
  {
   if (trafficController->debug) log.debug("queue message for notification: "+msg->toString());
   emit passMessage(msg);
  }
  msg = NULL;
  // done with this one
 } // end of permanent loop
}
/*protected*/ char LnPacketizer::readByteProtected(QDataStream *istream)
{
 while (true )
 { // loop will repeat until character found

  int nchars = 0;
  nchars = istream->readRawData(rcvBuffer, 1);

  if (nchars>0)
  {
   return rcvBuffer[0];
  }
  mutex1.lock();
  dataAvailable->wait(&mutex1);
  mutex1.unlock();
 }
}

/*public*/ void XmtHandler::run() //throw(LocoNetMessageException, EOFException, IOException, Exception)
{
 bool debug = log.isDebugEnabled();

  exec();
 }
void XmtHandler::sendMessage(LocoNetMessage* m) // SLOT[]
{

   // input - now send
//    try
//    {
    if (trafficController->ostream != NULL )
    {
     //if( trafficController->xmtBuffer.count() > 0)
     {
      if (!trafficController->controller->okToSend())
      {
       log.debug("LocoNet port not ready to receive");
       return;
      }
      QMutex mutex3;
      mutex3.lock();
      trafficController->ostream->writeBytes(m->toCharArray().constData(),m->getNumDataElements());      //trafficController->xmtBuffer.remove(0,1);
      mutex3.unlock();
      if(trafficController->serial != NULL) //HexFile won't have a serial object!
       trafficController->serial->flush();
      messageTransmitted(m->toCharArray().constData());
     }
    }
    else
    {
     // no stream connected
     log.warn("sendLocoNetMessage: no connection established");
    }
//} catch (NoSuchElementException e) {
//    // message queue was empty, wait for input
//    log.trace("start wait"); // NOI18N

//    new jmri.util.WaitHandler(this); // handle synchronization, spurious wake, interruption

//    log.trace("end wait"); // NOI18N
//}
}
#endif
