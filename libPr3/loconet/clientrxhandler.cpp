#include "clientrxhandler.h"
#include <QTcpSocket>
#include <QThread>
#include "lntrafficcontroller.h"
#include "version.h"
#include "lntcpserver.h"
#include "clientrxhandler.h"
#include <QMessageBox>
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"
#include "lntrafficcontroller.h"
#include "stringtokenizer.h"
#include <QWaitCondition>
#include <QReadWriteLock>
#include "llnmon.h"
#include <QAbstractSocket>

//ClientRxHandler::ClientRxHandler(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Implementation of the LocoNetOverTcp LbServer Server Protocol
 *
 * @author Alex Shepherd Copyright (C) 2006
 * @version	$Revision: 28746 $
 */
///*public*/ final class ClientRxHandler extends Thread implements LocoNetListener {


/*public*/ ClientRxHandler::ClientRxHandler(QString newRemoteAddress, QTcpSocket* newSocket, LnTrafficController *tc, int connectionNbr, QObject *parent) :
  QThread(parent)
{
 clientSocket = newSocket;
 //llnmon = new LlnMon();
 //setDaemon(true);
 setPriority(QThread::HighestPriority);
 remoteAddress = newRemoteAddress;
 setObjectName("ClientRxHandler:" + QString(" #%1").arg(connectionNbr));
 //connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

 //tc = ((LocoNetSystemConnectionMemo*)InstanceManager::getDefault("SystemConnectionMemo"))->getLnTrafficController();
// QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
// foreach (QObject* memo, *list)
// {
//  if(qobject_cast<LocoNetSystemConnectionMemo*>(memo) != NULL)
//  {
//   LocoNetSystemConnectionMemo* connectionMemo = (LocoNetSystemConnectionMemo*)memo;
//   tc = connectionMemo->getLnTrafficController();
//   break;
//  }
// }
 this->tc = tc;
 bIsInterrupted = false;
 log = new Logger(objectName());
 log->setDebugEnabled(false);
 //lastSentMessage = NULL;
 log->debug(tr("started, connected to ") + newRemoteAddress);

 txHandler = new ClientTxHandler(remoteAddress, newSocket, connectionNbr);

 start();

}

//@SuppressWarnings("NULL")
/*public*/ void ClientRxHandler::run()
{

//    try {
        //inStream = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
 //connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(on_clientSocket_disconnected()));
 inStream = new QTextStream(clientSocket);

//        outStream = clientSocket.getOutputStream();

//        LnTrafficController::instance().addLocoNetListener(~0, this);
 // pass messages received off of LocoNet to the Tx handler
 connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)),txHandler, SLOT(sendMessage(LocoNetMessage*)));

 // pass the message received by the Rx handler to the Tx handler so it can check for ACK
 connect(this, SIGNAL(lastMessageSent(LocoNetMessage*)),
         txHandler, SLOT(on_lastMessage(LocoNetMessage*)));
 connect(clientSocket, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(quit()));

 exec();

 disconnect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 //txThread->interrupt();

 //txThread = NULL;
 inStream = NULL;
 //outStream = NULL;
 //msgQueue.clear();
 //msgQueue = NULL;

 //try {
  clientSocket->close();
  //} catch (IOException ex1) {
  //}

 LnTcpServer::getDefault()->removeClient(this);
 log->info("ClientRxHandler: Exiting");
}

// txThread = new ClientTxHandler(this);
// //txThread.setDaemon(true);
// txThread->setObjectName("ClientTxHandler:" + remoteAddress);
// txThread->start();
// txThread->setPriority(QThread::HighestPriority);
void ClientRxHandler::on_readyRead()
{

 while (!isInterrupted()  && clientSocket->isValid() && clientSocket->isOpen() )
 {
  if(log->isDebugEnabled() && clientSocket->bytesAvailable() > 0)
   log->debug(tr("Socket has %1 bytes ready").arg(clientSocket->bytesAvailable()));
  //if(clientSocket->bytesAvailable() > 0)
  {
   inString = inStream->readLine();
   if (inString.isEmpty())
   {
    //log->debug("ClientRxHandler: Remote Connection Closed");
    //interrupt();
    return;
   }
   else
   {
    log->debug("ClientRxHandler: Received: " + inString);

    StringTokenizer st =  StringTokenizer(inString);
    if (st.nextToken() == ("SEND"))
    {
     LocoNetMessage* msg = NULL;
     int opCode = st.nextToken().toInt(0, 16);
     int byte2 = st.nextToken().toInt(0, 16);

     // Decide length
     switch ((opCode & 0x60) >> 5)
     {
      case 0: /* 2 byte message */

          msg = new LocoNetMessage(2);
          break;

      case 1: /* 4 byte message */

          msg = new LocoNetMessage(4);
          break;

      case 2: /* 6 byte message */

          msg = new LocoNetMessage(6);
          break;

      case 3: /* N byte message */

          if (byte2 < 2)
          {
           log->error(tr("ClientRxHandler: LocoNet message length invalid: ")
                   + byte2 + " opcode: "
                   + QString::number(opCode,16));
          }
          msg = new LocoNetMessage(byte2);
          break;
     }
     if (msg == NULL)
     {
      log->error("msg is NULL!");
      return;
     }
     // message exists, now fill it
     msg->setOpCode(opCode);
     msg->setElement(1, byte2);
     int len = msg->getNumDataElements();
     //log->debug("len: "+len);

     for (int i = 2; i < len; i++)
     {
      int b = st.nextToken().toInt(0, 16);
      msg->setElement(i, b);
     }
//     if(log->isDebugEnabled())
//     {
//      log->debug(msg->toString());
//      log->debug("Encoded message: " + llnmon->displayMessage(*msg));
//     }
     if(tc == NULL) return;
     tc->sendLocoNetMessage(msg);
     // Keep the message we just sent so we can ACK it when we hear
     // the echo from the LocoBuffer
     lastSentMessage = msg;
     emit lastMessageSent(lastSentMessage);
    }
   }
  }
//  else
//  {
//   if(!clientSocket->waitForReadyRead())
//   {
//    if(clientSocket->error() != QAbstractSocket::SocketTimeoutError)
//     displayError(clientSocket->error());
//   }
//  }
 }
//    } catch (IOException ex) {
//        log->debug("ClientRxHandler: IO Exception: ", ex);
//    }
 //LnTrafficController.instance().removeLocoNetListener(~0, this);
// disconnect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
// //txThread->interrupt();

// //txThread = NULL;
// inStream = NULL;
// //outStream = NULL;
// //msgQueue.clear();
// //msgQueue = NULL;

// //try {
//  clientSocket->close();
//  //} catch (IOException ex1) {
//  //}

// Server::getInstance()->removeClient(this);
// log->info("ClientRxHandler: Exiting");
}

/*public*/ void ClientRxHandler::close()
{
 try {
     clientSocket->close();
 } catch (IOException ex1) {
     log->error("close, which closing clientSocket", ex1);
 }
}
void ClientRxHandler::displayError(QAbstractSocket::SocketError socketError)
{
 switch (socketError)
 {
 case QAbstractSocket::RemoteHostClosedError:
  log->warn("remote host closed");
  bIsInterrupted = true;
     break;
 case QAbstractSocket::HostNotFoundError:
//     QMessageBox::information(NULL, tr("Server Client"),
//                              tr("The host was not found. Please check the "
//                                 "host name and port settings."));
  log->error(tr("The host was not found. Please check the "
                "host name and port settings."));
     break;
 case QAbstractSocket::ConnectionRefusedError:
     //QMessageBox::information(NULL, tr("Server Client"),
  log->error(
                              tr("The connection was refused by the peer. "));
     break;
 default:
//     QMessageBox::information(NULL, tr("Server Client"),
  log->error(
                              tr("The following error occurred: %1.")
                              .arg(clientSocket->errorString()));
 }
}

bool ClientRxHandler::isInterrupted() { return bIsInterrupted;}

/*public*/ void ClientRxHandler::message(LocoNetMessage* msg)
{
// /*synchronized (msgQueue)*/
// {
////  msgQueue.append(msg);
////  //msgQueue.notify();
////  ((ClientTxHandler*)txThread)->queueCondition->wakeOne();
// }
 emit passMessage(msg);
}
void ClientRxHandler::on_clientSocket_disconnected()
{
 log->warn("client socket disconnected");
 bIsInterrupted = true;
}

//class ClientTxHandler implements Runnable {

//    LocoNetMessage msg;
//    StringBuffer outBuf;
//    Thread parentThread;

ClientTxHandler::ClientTxHandler(QString newRemoteAddress, QTcpSocket* newSocket, int connectionNbr)
{
 //parentThread = creator;
 remoteAddress = newRemoteAddress;
 clientSocket = newSocket;
 setObjectName(QString("ClientTxHandler#%1").arg(connectionNbr));
 log = new Logger(objectName());
 outStream = new QTextStream(clientSocket);
 //outStream->setVersion(QDataStream::Qt_4_0);
 //queueCondition = new QWaitCondition();
 //mutex = new QMutex();
 //msgQueue = QLinkedList<LocoNetMessage*>();

 lastSentMessage = NULL;

 start();

}

/*public*/ void ClientTxHandler::run()
{

 exec();
 // Interrupt the Parent to let it know we are exiting for some reason
 //parentThread.interrupt();
// parentThread->exit();

// parentThread = NULL;
 log->info("ClientTxHandler: Exiting");
}
void ClientTxHandler::sendMessage(LocoNetMessage * msg)
{
//    try {
// queueCondition->wait(mutex);
 if(!clientSocket->isOpen() || !clientSocket->isValid())
  exit();

 outBuf = QString("VERSION JMRI Server ");
 outBuf.append(Version::name());
 outBuf.append("\r\n");
 //outStream.write(outBuf.toString().getBytes());
 *outStream << outBuf;

 if (clientSocket->isOpen())
 {

//  msg = NULL;

//  /*synchronized (msgQueue)*/
//  {
//   mutex->lock();

//   if (msgQueue.isEmpty())
//   {
//      // msgQueue.wait();
//    queueCondition->wait(mutex);
//   }

//   msg = msgQueue.first();
//   msgQueue.removeFirst();
//  }

  if (msg != NULL)
  {
   outBuf.clear();
   outBuf.append("RECEIVE ");
   outBuf.append(msg->toString());
   //log->debug("ClientTxHandler: Send: " + outBuf);
   outBuf.append("\r\n");
   // See if we are waiting for an echo of a sent message
   // and if it is append the Ack to the client
   if ((lastSentMessage != NULL) && lastSentMessage->equals(msg))
   {
    lastSentMessage = NULL;
    outBuf.append("SENT OK\r\n");
   }
//                outStream.write(outBuf.toString().getBytes());
//                outStream.flush();
   *outStream << outBuf;
   outStream->flush();
   //mutex->unlock();

  }
 }
//    } catch (IOException ex) {
//        log->error("ClientTxHandler: IO Exception");
//    } catch (InterruptedException ex) {
//        //Thread.currentThread().interrupt(); // retain if needed later
//        log->debug("ClientTxHandler: Interrupted Exception");
//    }
 outBuf = "";

}
void ClientTxHandler::on_lastMessage(LocoNetMessage *msg)
{
 lastSentMessage = msg;
}

//};

