#include "lnpacketizer.h"
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//                    justification="Only used during system initialization")
//    public LnPacketizer() {
//    	self=this;
//    	debug = log->isDebugEnabled();
//   	}
QWaitCondition* LnPacketizer::dataAvailable = new QWaitCondition();

LnPacketizer::LnPacketizer(QObject* parent)
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
 self=this;
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
}
//// The methods to implement the LocoNetInterface
//void LnPacketizer::setThread(MasterThread *thread)
//{
// this->thread = thread;
// connect(this->thread, SIGNAL(dataWritten(QVector<char>)), this, SLOT(msgTransmitted(QVector<char>)));
//}
#if 0
void LnPacketizer::setSerial(QSerialPort* serial)
{
 //thread->setSerial(serial);
 this->serial = serial;
#ifndef USE_THREAD
 istream = new QDataStream(serial);
 ostream = new QDataStream(serial);
 connect(this->serial, SIGNAL(readyRead()), this,SLOT(dataReady()) );
#else
istream = controller->getInputStream();
ostream = controller->getOutputStream();
#endif
}
#endif

/*public*/ bool LnPacketizer::status() { return ((ostream != NULL) & (istream != NULL)); }
#ifndef USE_THREAD

void LnPacketizer::dataReady() // [slot]
{
 int iDebug = 2;  // 2 = display all messages, 1 = display only formatted message.
 //mutex1.lock();
 QByteArray ba = serial->readAll();
 foreach(int c, ba)
  baStream->append(c);
 if(iDebug > 1)
  qDebug() << QString("baStream->size = %1").arg(baStream->size());
 int msgLength=0;
 int count = ba.count();
 int currOpcode = 0;
 int nextElement = -1;
 //int i=0;
 if(iDebug > 1)
 {
  QString s;
  foreach(char c, ba)
   s.append(QString("%1 ").arg(c&0xff,0,16));
  qDebug()<< QString("data received %1 bytes: %2").arg(count).arg(s);
 }
 LocoNetMessage* msg;
 int data;

 while(baStream->size()>1)
 {
   ba = serial->readAll();  // get any additional characters that may have arrived.
   foreach(int c, ba)
     baStream->append(c);
   currOpcode = baStream->at(0)&0xff;
   nextElement = baStream->at(1);

  switch(currOpcode & 0xE0)
  {
  case 0x80: // 2 byte message
   msg = new LocoNetMessage(2);
   break;
  case 0xA0: // 4 byte message
   msg = new LocoNetMessage(4);
   break;
  case 0xC0: // 6 byte message
   msg = new LocoNetMessage(6);
   break;
  case 0xE0: // variable length message.
   msg= new LocoNetMessage(nextElement);
   break;
  default:
   baStream->remove(0,1);
   continue;
  }
  msg->setOpCode(currOpcode);
  msg->setElement(1, nextElement);
  msgLength = msg->getNumDataElements();
  if(baStream->count() >= msgLength) // are there enough chars in buffer?
  {
   baStream->remove(0,2); // remove opcode and first element already read from buffer.
   for(int i=2; i < msgLength; i++)
   {
    data = baStream->at(0)&0xff;
    //    // check for message-blocking error
    if (fulldebug) log->debug("char "+QString("%1").arg(i)+" is: "+QString("%1").arg(data,0,16));
    if ( (data&0x80) != 0)
    {
     log->warn("LocoNet message with opCode: "
                       +QString("%1").arg(currOpcode,0,16)
                       +" ended early. Expected length: "+QString("%1").arg(msgLength)
                       +" seen length: "+QString("%1").arg(i)
                       +" unexpected byte: "
                       +QString("%1").arg(data,0,16));
    //      opCode = b;
    //      throw new LocoNetMessageException();
     continue;
    }
    baStream->remove(0,1);
    msg->setElement(i, data);
   }
   if(msg->checkParity())
   {
    emit messageProcessed(msg,false);
    emit LnTrafficController::messageProcessed(msg);
    emit LocoNetInterface::messageProcessed(msg);
//    if(iDebug > 0)
//     qDebug()<< QString("message received: "+msg->toString() + "-> " + monitor->displayMessage(*msg));
    continue;
   }
   else
    log->warn("Ignore Loconet packet with bad checksum: "+msg->toString());
   continue;
  }
  break;
 }
 mutex1.unlock();
}
#endif
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
 QMutexLocker locker(&mutex2);

 // update statistics
 transmittedMsgCount++;

 // set the error correcting code byte(s) before transmittal
 m->setParity();
#if 0
#ifndef USE_THREAD

 if(!(serial->isOpen()))
 {
  log->error(QString("Serial port '%1' not  open, returned error: ").arg(serial->portName()) +serial->errorString());
  return;
 }
 //mutex2.lock();
 qint64 bw = serial->write(m->toCharArray().constData(),m->getNumDataElements());
 log->debug(tr("%1 bytes of %2 written").arg(bw).arg(m->getNumDataElements()));
#endif
#ifdef USE_THREAD
 // stream to port in single write, as that's needed by serial
 int len = m->getNumDataElements();
 for(int i = 0; i < len; i++)

 {
  mutex3.lock();
  xmtBuffer.append(m->getElement(i));
  mutex3.unlock();
 }
 if (debug) log->debug("queue LocoNet packet: "+m->toString());
// // in an atomic operation, queue the request and wake the xmit thread
// try
// {
////     synchronized(xmtHandler) {
    mutex3.lock();
    xmtList->append(&xmtBuffer);
//      //xmtHandler->notify();
//   xmtHandler->start();
    mutex3.unlock();
////     }
// }
// catch (Exception e) {
//     log->warn("passing to xmit: unexpected exception: "+e.getMessage());
// }
 emit messageProcessed(m, true);

#else
 if (serial->waitForBytesWritten(100))
 {
  // data successfully written!
  emit messageProcessed(m, true);
  log->debug(m->toString());
#ifdef Q_WS_WIN
   serial->waitForReadyRead(100);
#endif
 }
 else
 {
  QString errmsg = tr("Wait write request timeout %1 '%2' port %3").arg(QTime::currentTime().toString()).arg(serial->errorString()).arg(serial->portName());
//     emit timeout(errmsg);
  qDebug() << errmsg;
 }
#endif
 //mutex2.unlock();
#endif
 emit sendMessage(m);
}
/**
 * Break connection to existing LnPortController object. Once broken,
 * attempts to send via "message" member will fail.
 * @param p previously connected port
 */
/*public*/ void LnPacketizer::disconnectPort(LnPortController* p) {
 istream = NULL;
 ostream = NULL;
 if (controller != p)
     log->warn("disconnectPort: disconnect called from non-connected LnPortController");
 controller = NULL;
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
    //QThread* xmtThread = new QThread(this);//QThread(xmtHandler, "LocoNet transmit handler");
    log->debug(QString("Xmt thread (%2) starts at priority %1").arg(xmtpriority).arg(xmtHandler->objectName()));
    //xmtThread.setDaemon(true);
    //connect(xmtThread, SIGNAL(started()), xmtHandler, SLOT(run()));
    //connect(xmtThread, SIGNAL(finished()), xmtHandler, SLOT(deleteLater()));
    XmtHandler* outHandler = (XmtHandler*)xmtHandler;
    connect(this, SIGNAL(sendMessage(LocoNetMessage*)), outHandler, SLOT(sendMessage(LocoNetMessage*)));

//    xmtHandler->setPriority(QThread::HighPriority); // Highest -1
    xmtHandler->start(QThread::HighPriority);

    // start the RcvHandler in a thread of its own
    if( rcvHandler == NULL )
      rcvHandler = new RcvHandler(this) ;
    //QThread* rcvThread = new QThread(this); //(rcvHandler, "LocoNet receive handler");
    int rcvpriority = QThread::HighestPriority;
    log->debug(QString("rcv thread (%2) starts at priority %1").arg(rcvpriority).arg(rcvHandler->objectName()));
    //rcvThread.setDaemon(true);
   // connect(rcvThread, SIGNAL(started()), rcvHandler, SLOT(run));
    //connect(rcvThread, SIGNAL(finished()), rcvHandler, SLOT(deleteLater()));
    RcvHandler* handler = (RcvHandler*)rcvHandler;
//    connect(handler, SIGNAL(notifyMessage(LocoNetMessage*)), this, SLOT(loconetMsgRcvd(LocoNetMessage*)));

//    if(objectName() == "LnPacketizer")
     connect(handler, SIGNAL(passMessage(LocoNetMessage*)), this, SLOT(loconetMsgRcvd(LocoNetMessage*)));
//    else
//     connect(handler, SIGNAL(notifyMessage(LocoNetMessage*)), this, SLOT(loconetMsgRcvd(LocoNetMessage*)));

    connect(handler, SIGNAL(finished()), this, SLOT(rcvTerminated()));
    //rcvHandler->setPriority(QThread::HighestPriority);
    //connect(serial, SIGNAL(readyRead()), handler, SLOT(dataAvailable()));
    if (istream != NULL)
      rcvHandler->start(QThread::HighestPriority);
}
#else
void LnPacketizer::startThreads() {} // dummy routine
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
//  while(!trafficController->istream->atEnd())
//  {
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
//   /*final*/ LocoNetMessage* thisMsg = msg;
//   /*final*/ LnPacketizer* thisTC = trafficController;
//   // return a notification via the queue to ensure end
//     Runnable* r = new Runnable() {
//      LocoNetMessage* msgForLater = thisMsg;
//      LnPacketizer* myTC = thisTC;
//      /*public*/ void run() {
//       myTC->notify(msgForLater);
//      }
//     }
//     invokeLater(r);
   emit passMessage(msg);
  }
  msg = NULL;
  // done with this one
//  }
//  catch (LocoNetMessageException e) {
//   // just let it ride for now
//         log.warn("run: unexpected LocoNetMessageException: "+e.getMessage());
//  }
//  catch (EOFException e) {
//   // posted from idle port when enableReceiveTimeout used
//   if (trafficController->fulldebug) log.debug("EOFException, is LocoNet serial I/O using timeouts?");
//  }
//  catch (IOException e) {
//   // fired when write-end of HexFile reaches end
//   if (trafficController->debug) log.debug("IOException, should only happen with HexFile: "+e.msg);
//   log.info("End of file");
//   trafficController->disconnectPort(trafficController->controller);
//   return;
//  }
//  // normally, we don't catch the unnamed Exception, but in this
//  // permanently running loop it seems wise.
//  catch (Exception e) {
//   log.warn("run: unexpected Exception: "+e.msg);
//  }
//  } // end while ! at end
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

// while (true)
// { // loop permanently
   // any input?
//   try
//   {
   // get content; failure is a NoSuchElementException
//    if (trafficController->fulldebug) log.debug("check for input");
//    char msg[1];
//    QMutex mutex1;
//    //synchronized (this)
//    {
//     if(trafficController->xmtList.count()>0)
//     {
//      mutex1.lock();
//      msg[0] = trafficController->xmtList.first();
//      trafficController->xmtList.removeFirst();
//      mutex1.unlock();
//     }
//    }
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
      //if (trafficController->debug) log.debug("start write to stream  : "+LnPacketizer::hexStringFromBytes(trafficController->xmtBuffer));
//      trafficController->ostream->writeRawData(msg,1);
      QMutex mutex3;
      mutex3.lock();
      //trafficController->ostream->writeRawData(trafficController->xmtBuffer,1);
      trafficController->ostream->writeBytes(m->toCharArray().constData(),m->getNumDataElements());      //trafficController->xmtBuffer.remove(0,1);
      mutex3.unlock();
      if(trafficController->serial != NULL) //HexFile won't have a serial object!
       trafficController->serial->flush();
      //if (trafficController->fulldebug) log.debug("end write to stream: "+LnPacketizer::hexStringFromBytes(trafficController->xmtBuffer));
      //messageTransmitted(trafficController->xmtBuffer);
      messageTransmitted(m->toCharArray().constData());
     }
    }
    else
    {
     // no stream connected
     log.warn("sendLocoNetMessage: no connection established");
    }
//    }
//    catch (IOException e)
//    {
//     log.warn("sendLocoNetMessage: IOException: "+e.msg);
//    }
//   }
//   catch (NoSuchElementException e)
//   {
//    // message queue was empty, wait for input
//    if (trafficController->fulldebug) log.debug("start wait");

//    //new WaitHandler(this);  // handle synchronization, spurious wake, interruption

//    if (trafficController->fulldebug) log.debug("end wait");
//   }
// }
}
#endif
