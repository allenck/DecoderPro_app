#include "lnovertcppacketizer.h"
#include "lnnetworkportcontroller.h"
#include "stringtokenizer.h"
#include <QTcpSocket>

//LnOverTcpPacketizer::LnOverTcpPacketizer(QObject *parent) :
//  LnPacketizer(parent)
//{
//}

/**
 * Converts Stream-based I/O to/from LocoNet messages. The "LocoNetInterface"
 * side sends/receives LocoNetMessage objects. The connection to a
 * LnPortnetworkController is via a pair of *Streams, which then carry sequences
 * of characters for transmission.
 * <P>
 * Messages come to this via the main GUI thread, and are forwarded back to
 * listeners in that same thread. Reception and transmission are handled in
 * dedicated threads by RcvHandler and XmtHandler objects. Those are internal
 * classes defined here. The thread priorities are:
 * <P>
 * <UL>
 * <LI> RcvHandler - at highest available priority
 * <LI> XmtHandler - down one, which is assumed to be above the GUI
 * <LI> (everything else)
 * </UL>
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Alex Shepherd Copyright (C) 2003, 2006
 * @version $Revision: 28771 $
 *
 */
///*public*/ class LnOverTcpPacketizer extends LnPacketizer {

/*static*/ /*final*/ QString LnOverTcpPacketizer::RECEIVE_PREFIX = "RECEIVE";
/*static*/ /*final*/ QString LnOverTcpPacketizer::SEND_PREFIX = "SEND";

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "Only used during system initialization")
/*public*/ LnOverTcpPacketizer::LnOverTcpPacketizer(LocoNetSystemConnectionMemo* m, QObject *parent) : LnPacketizer(m, parent)
{
 setObjectName("LnOverTcpPacketizer");
 networkController = NULL;
 log = new Logger("LnOverTcpPacketizer");
 log->setDebugEnabled(false);

// xmtHandler = new LnTcpXmtHandler(this);
// rcvHandler = new LnTcpRcvHandler(this);
}


//@Override
/*public*/ bool LnOverTcpPacketizer::isXmtBusy()
{
 if (networkController == NULL)
 {
  return false;
 }

 return true;
}

/**
 * Make connection to existing LnPortnetworkController object.
 *
 * @param p Port networkController for connected. Save this for a later
 *          disconnect call
 */
/*public*/ void LnOverTcpPacketizer::connectPort(LnNetworkPortController* p)
{

// istream = p->getInputStream();
// istream->setVersion(QDataStream::Qt_4_0);

// ostream = p->getOutputStream();
// ostream->setVersion(QDataStream::Qt_4_0);
 if (networkController != NULL)
 {
  log->warn("connectPort: connect called while connected");
 }
 networkController = p;

 p->getSocket()->waitForConnected();

 xmtHandler = new LnTcpXmtHandler(this);
 rcvHandler = new LnTcpRcvHandler(this);
}


/**
 * Break connection to existing LnPortnetworkController object. Once broken,
 * attempts to send via "message" member will fail.
 *
 * @param p previously connected port
 */
/*public*/ void LnOverTcpPacketizer::disconnectPort(LnNetworkPortController* p)
{
 istream = NULL;
 ostream = NULL;
 if(xmtHandler != NULL)
 {
  xmtHandler->exit();
  xmtHandler->wait();
  xmtHandler = NULL;
 }
 if(rcvHandler != NULL)
 {
  rcvHandler->exit();
  rcvHandler->wait();
  rcvHandler = NULL;
 }
 if (networkController != p)
 {
  log->warn("disconnectPort: disconnect called from non-connected LnPortnetworkController");
 }
 networkController = NULL;
 log->debug("port disconnected;");
}

/**
 * Captive class to handle incoming characters. This is a permanent loop,
 * looking for input messages in character form on the stream connected to
 * the LnPortnetworkController via <code>connectPort</code>.
 */
//class RcvHandler implements Runnable {

//    /**
//     * Remember the LnPacketizer object
//     */
//    LnOverTcpPacketizer trafficController;

/*public*/ LnTcpRcvHandler::LnTcpRcvHandler(LnOverTcpPacketizer* lt) : QThread()
{
 trafficController = lt;
 setObjectName("LnTcpRcvHandler");
 log = new Logger("LnTcpRcvHandler");
 log->setDebugEnabled(false);

 start();
}

// readline is deprecated, but there are no problems
// with multi-byte characters here.
//@SuppressWarnings({"deprecation", "NULL"})
/*public*/ void LnTcpRcvHandler::run()
{
 bool debug = log->isDebugEnabled();
 if(log->isDebugEnabled() )
  log->debug("LnTcpRcvHandler starts");
 connSocket = trafficController->networkController->getSocket();
// trafficController->istream = new QDataStream(connSocket);
// trafficController->istream->setVersion(QDataStream::Qt_4_0);
 //connect(connSocket, SIGNAL(disconnected()), this, SLOT(quit()));
 inText = new QTextStream(connSocket);
 //connSocket->waitForReadyRead();
 connect(connSocket, SIGNAL(readyRead()), this, SLOT(on_ReadyRead()));

 exec();

 log->debug("LnTcpRcvHandler exiting!");

}

void LnTcpRcvHandler::on_ReadyRead()
{
 QString rxLine;
 bool debug = log->isDebugEnabled();

 while (true)
 {   // loop permanently, program close will exit
  //try {

//  if(log->isDebugEnabled() && connSocket->bytesAvailable() > 0)
//   log->debug(tr("bytes available: %1").arg(connSocket->bytesAvailable()));

  //if(connSocket->bytesAvailable() > 0 )
  {
   // start by looking for a complete line
   if(connSocket == NULL || !connSocket->isValid())
    return;
   mutex.lock();
   rxLine = inText->readLine(75);
   mutex.unlock();

   if (rxLine.isEmpty())
   {
//    log->warn("run: input stream returned empty line, will wait");
    //QByteArray ba = connSocket->peek(64);
//    connSocket->waitForReadyRead();
//    continue;
    return;
   }

   if (debug)
   {
    if(!rxLine.startsWith("VERSION"))
     log->debug("Received: " + rxLine);
   }

   StringTokenizer* st = new StringTokenizer(rxLine);
   if (st->nextToken()==(trafficController->RECEIVE_PREFIX))
   {
    LocoNetMessage* msg = NULL;
    int opCode = st->nextToken().toInt(0, 16);
    int byte2 = st->nextToken().toInt(0, 16);

    // Decide length
    switch ((opCode & 0x60) >> 5)
    {
     default:  // not really possible, but this closes selection for FindBugs
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

     if (byte2 < 2)
     {
       log->error("LocoNet message length invalid: " + QString::number(byte2)
                 + " opcode: " + QString::number(opCode,16));
     }
     msg = new LocoNetMessage(byte2);
     break;
    }

    // message exists, now fill it
    msg->setOpCode(opCode);
    msg->setElement(1, byte2);
    int len = msg->getNumDataElements();
    //log->debug("len: "+len);

    for (int i = 2; i < len; i++)
    {
     // check for message-blocking error
     int b = st->nextToken().toInt(0, 16);
     //log->debug("char "+i+" is: "+Integer.toHexString(b));
     if ((b & 0x80) != 0)
     {

      log->warn("LocoNet message with opCode: "
                 + QString::number(opCode, 16)
                 + " ended early. Expected length: " + len
                 + " seen length: " + i
                 + " unexpected byte: "
                 + QString::number(b,16));
      opCode = b;
 //        throw new LocoNetMessageException();
     }
     msg->setElement(i, b);
    }

    // message is complete, dispatch it !!
//    if (log->isDebugEnabled())
//    {
//     log->debug("queue message for notification");
//    }
#if 0
    /*final*/ LocoNetMessage* thisMsg = msg;
    /*final*/ LnPacketizer* thisTC = trafficController;
    // return a notification via the queue to ensure end
    Runnable r = new Runnable() {
        LocoNetMessage msgForLater = thisMsg;
        LnPacketizer myTC = thisTC;

        /*public*/ void run() {
            myTC.notify(msgForLater);
        }
    };
 #endif
    //javax.swing.SwingUtilities.invokeLater(r);'
    //emit notifyMessage(msg);
    emit passMessage(msg);

  }
  // done with this one
  rxLine = "";

//     } catch (LocoNetMessageException e) {
//         // just let it ride for now
//         log->warn("run: unexpected LocoNetMessageException: " + e);
//     } catch (java.io.EOFException e) {
//         // posted from idle port when enableReceiveTimeout used
//         if (debug) {
//             log->debug("EOFException, is LocoNet serial I/O using timeouts?");
//         }
//     } catch (java.io.IOException e) {
//         // fired when write-end of HexFile reaches end
//         if (debug) {
//             log->debug("IOException, should only happen with HexFIle: " + e);
//         }
//         log->info("End of file");
////                    disconnectPort(networkController);
//         return;
//     } // normally, we don't catch the unnamed Exception, but in this
//     // permanently running loop it seems wise.
//     catch (Exception e) {
//         log->warn("run: unexpected Exception: " + e);
//     }
  }
//  else
//  {
//   if(!connSocket->waitForReadyRead())
//   {
//    if(connSocket->error() != QAbstractSocket::SocketTimeoutError)
//     log->error(connSocket->errorString());
//   }
//  }
 } // end of permanent loop
 //log->debug("LnTcpRcvHandler exiting!");
}
//};

/**
* Captive class to handle transmission
*/
//class XmtHandler implements Runnable {

LnTcpXmtHandler::LnTcpXmtHandler(LnOverTcpPacketizer* lt) : QThread()
{
 this->trafficController = lt;
 setObjectName("LnTcpXmtHandler");
 log = new Logger("LnTcpXmtHandler");
 log->setDebugEnabled(false);
}

/*public*/ void LnTcpXmtHandler::run()
{
 connSocket = trafficController->networkController->getSocket();
 outText = new QTextStream(connSocket);
 //connect(connSocket, SIGNAL(disconnected()), this, SLOT(quit()));

 exec();
}

// while (true)
// {   // loop permanently
//  // any input?
////     try {
//  // get content; failure is a NoSuchElementException
//  if (debug) {
//      log->debug("check for input");
//  }
//  QByteArray* msg = NULL;
//  /*synchronized (this)*/
//  //if(!trafficController->xmtList->isEmpty())
//  {
//   trafficController->mutex->lock();
//   msg = trafficController->xmtList->first();
//   trafficController->xmtList->removeFirst();
//   trafficController->mutex->unlock();
//  }
//  else
//   continue;
void LnTcpXmtHandler::sendMessage(LocoNetMessage *msg)
{
 bool debug = log->isDebugEnabled();
 if(debug)
  log->debug("send message");

  // input - now send
//  try {
 if (outText != NULL)
 {
         //Commented out as the origianl LnPortnetworkController always returned true.
         //if (!networkController.okToSend()) log->warn("LocoNet port not ready to receive"); // TCP, not RS232, so message is a real warning
//  if (debug)
//  {
//   log->debug("start write to stream");
//  }
  QString packet;// = new StringBuffer(msg.length * 3 + SEND_PREFIX.length() + 2);
  packet.append(trafficController->SEND_PREFIX);
  QString hexString;
  for (int Index = 0; Index < msg->getNumDataElements(); Index++)
  {
   packet.append(' ');
   hexString = QString::number(msg->getElement(Index) & 0xFF,16).toUpper();
   if (hexString.length() == 1) {
       packet.append('0');
   }
   packet.append(hexString);
  }
  if (debug)
  {
   log->debug("Write to LbServer: " + packet/*.toString()*/);
  }
  packet.append("\r\n");
  //ostream.write(packet.toString().getBytes());
  //*trafficController->ostream << packet;
  *outText << packet;
  outText->flush();
//  if (debug)
//  {
//   log->debug("end write to stream");
//  }
 }
 else
 {
  // no stream connected
  log->warn("sendLocoNetMessage: no connection established");
 }
//   } catch (IOException e) {
//       log->warn("sendLocoNetMessage: IOException: " + e.toString());
//   }
//     } catch (NoSuchElementException e) {
//         // message queue was empty, wait for input
//         if (debug) {
//             log->debug("start wait");
//         }

//   new WaitHandler(this);  // handle synchronization, spurious wake, interruption

//   if (debug) {
//       log->debug("end wait");
//   }
}

//}
//};

