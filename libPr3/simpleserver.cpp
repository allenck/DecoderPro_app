#include "simpleserver.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "simpleservermanager.h"
#include <QTcpSocket>
#include "simpleserver/simplepowerserver.h"
#include "simpleserver/simplesensorserver.h"
#include "simpleserver/simpleturnoutserver.h"
#include "version.h"
#include "webserverpreferences.h"
#include "nodeidentity.h"
#include "simpleserver/simplelightserver.h"
#include "simpleserver/simplesignalheadserver.h"
#include "simpleserver/simplereporterserver.h"

/**
 * This is an implementation of a simple server for JMRI. There is currently no
 * handshaking in this server. You may just start sending commands.
 *
 * @author Paul Bender Copyright (C) 2010
 *
 */
// /*public*/ class SimpleServer extends JmriServer {

    //static ResourceBundle rb = ResourceBundle.getBundle("jmri.jmris.simpleserver.SimpleServerBundle");

/*
 * @deprecated since 4.7.1 use @link{InstanceManager.getDefault()} instead.
 */
//@Deprecated  // will be removed when superclass method is removed due to //@Override
//@SuppressWarnings("deprecation")  // temporary implementation of method
/*public*/ /*static*/ JmriServer* SimpleServer::instance() {
    if (InstanceManager::getNullableDefault("SimpleServer") == nullptr) {
        InstanceManager::store(new SimpleServer(),"SimpleServer");
    }
    return (JmriServer*)InstanceManager::getDefault("SimpleServer");
}

// Create a new server using the default port
/*public*/ SimpleServer::SimpleServer(QObject* parent ) : JmriServer(2048, parent){
    //this((tr("SimpleServerPort")));
 common(2048);
}

/*public*/ SimpleServer::SimpleServer(int port, QObject *parent) : JmriServer(port, parent){
 common(port);
}
void SimpleServer::common(int port)
{
    //super(port);
    InstanceManager::setDefault("SimpleServer",this);
    log->setDebugEnabled(true);
    log->info("JMRI SimpleServer started on port " + QString::number(port));
    clients = new QLinkedList<JMRIClientRxHandler*>();
}

//@Override
/*protected*/ void SimpleServer::advertise() {
    JmriServer::advertise(QString("_jmri-simple._tcp.local."));
}

/*protected*/ void SimpleServer::removeClient(JMRIClientRxHandler* handler)
{
    /*synchronized (clients)*/
 {
  clients->removeOne(handler);
 }
 //updateClientStateListener();
}

void SimpleServer::on_newConnection()
{
 QTcpSocket* socket = nextPendingConnection();
 QString remoteAddress = socket->peerAddress().toString();
 log->debug("New connection from "+ remoteAddress);
 if(socket != NULL)
 {
  JMRIClientRxHandler* rxHandler;
  addClient(rxHandler = new JMRIClientRxHandler(remoteAddress,socket, connectionNbr++));
 }
}

/*protected*/ void SimpleServer::addClient(JMRIClientRxHandler *handler)
{
    /*synchronized (clients) */
 {
  clients->append(handler);
 }
// updateClientStateListener();
}

//@Override
/*public*/ void SimpleServer::stop() {
    log->info("Stopping Simple Server.");
    try
    {
     if (serverSocket != NULL) {
         serverSocket->close();
     }
    }
    catch (IOException* ex) {
    }

//    updateServerStateListener();

    // Now close all the client connections
    QLinkedList<JMRIClientRxHandler*> clientsArray;
    /*synchronized (clients)*/
    {
     clientsArray = *clients;
  //  }
  //  for (int i = 0; i < clientsArray.size(); i++)
  //  {
  //   ((ClientRxHandler*) clientsArray[i])->close();
  //  }
     while(!clientsArray.isEmpty())
     {
      clientsArray.takeFirst()->close();
     }
    }
}
JMRIClientRxHandler::JMRIClientRxHandler(QString newRemoteAddress, QTcpSocket *newSocket, int connectionNbr, QObject *parent)
{
 clientSocket = newSocket;
 setPriority(QThread::HighestPriority);
 remoteAddress = newRemoteAddress;
 setObjectName("JMRIClientRxHandler:" + QString(" #%1").arg(connectionNbr));
 bIsInterrupted = false;
 log = new Logger(objectName());
 log->setDebugEnabled(true);
 //lastSentMessage = NULL;
 log->debug(tr("started, connected to ") + newRemoteAddress);
 powerServer = new SimplePowerServer(clientSocket);
 turnoutServer = new SimpleTurnoutServer(clientSocket);
 //SimpleLightServer* lightServer;// = new SimpleLightServer(inStream, outStream);
 sensorServer = new SimpleSensorServer(clientSocket);
// SimpleSignalHeadServer* signalHeadServer;// = new SimpleSignalHeadServer(inStream, outStream);
// SimpleReporterServer* reporterServer;// = new SimpleReporterServer(inStream, outStream);
// SimpleOperationsServer* operationsServer;// = new SimpleOperationsServer(inStream, outStream);
 connect(newSocket, SIGNAL(readyRead()), this, SLOT(on_readyRead()));


 txHandler = new JMRIClientTxHandler(remoteAddress, newSocket, connectionNbr);
}

void JMRIClientRxHandler::run()
{
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(on_clientSocket_disconnected()));
 inStream = new QTextStream(clientSocket);
 connect(clientSocket, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(quit()));
 exec();
 inStream = NULL;
 clientSocket->close();
 //SimpleServer::getDefault()->removeClient(this
 SimpleServerManager::getSimpleServer()->removeClient(this);
 log->info("JMRIClientRxHandler: Exiting");
}

void JMRIClientRxHandler::on_readyRead()
{

 while (!isInterrupted()  && clientSocket->isValid() && clientSocket->isOpen() )
 {
  if(log->isDebugEnabled() && clientSocket->bytesAvailable() > 0)
   log->debug(tr("Socket has %1 bytes ready").arg(clientSocket->bytesAvailable()));
  inStream = new QTextStream(clientSocket);
  inString = inStream->readLine();
  if (inString.isEmpty())
  {
   //log->debug("ClientRxHandler: Remote Connection Closed");
   //interrupt();
   return;
  }
  else
  {
   log->debug("JMRIClientRxHandler: Received: " + inString);
   emit passMessage(inString);
   handleMessage(inString);
  }
 }
}

bool JMRIClientRxHandler::isInterrupted()
{
 return bIsInterrupted;
}

void JMRIClientRxHandler::on_clientSocket_disconnected()
{

}

void JMRIClientRxHandler::close()
{

}

void JMRIClientRxHandler::message(QString msg)
{
 emit message(msg);
}
/*public*/ void JMRIClientTxHandler::run()
{


 exec();
 // Interrupt the Parent to let it know we are exiting for some reason
 //parentThread.interrupt();
// parentThread->exit();

// parentThread = NULL;
 log->info("JMRIClientTxHandler: Exiting");
}
void JMRIClientRxHandler::displayError(QAbstractSocket::SocketError)
{

}

void JMRIClientTxHandler::sendMessage(QString msg)
{
//    try {
// queueCondition->wait(mutex);
 if(!clientSocket->isOpen() || !clientSocket->isValid())
  exit();

// outBuf = QString("VERSION JMRI Server ");
// outBuf.append(Version::name());
// outBuf.append("\r\n");
// //outStream.write(outBuf.toString().getBytes());
// *outStream << outBuf;

 if (clientSocket->isOpen())
 {


  if (msg != NULL)
  {
   outBuf.clear();
//   outBuf.append("RECEIVE ");
   outBuf.append(msg/*toString()*/);
   //log->debug("ClientTxHandler: Send: " + outBuf);
   outBuf.append("\r\n");
   *outStream << outBuf;
   outStream->flush();
   //mutex->unlock();

  }
 }
//    } catch (IOException* ex) {
//        log->error("ClientTxHandler: IO Exception");
//    } catch (InterruptedException ex) {
//        //Thread.currentThread().interrupt(); // retain if needed later
//        log->debug("ClientTxHandler: Interrupted Exception");
//    }
 outBuf = "";

}
JMRIClientTxHandler::JMRIClientTxHandler(QString newRemoteAddress, QTcpSocket *newSocket, int connectionNbr)
{
 Q_UNUSED(newRemoteAddress);
 Q_UNUSED(newSocket);
 Q_UNUSED(connectionNbr);
 log = new Logger("JMRIClientTxHandler");
 log->debug("JMRIClientTxHandler called");
 // Start by sending a welcome message
#if 1
 newSocket->write(QString("JMRI " + Version::name() + " \n").toLocal8Bit());
 newSocket->write(QString("RAILROAD " + static_cast<WebServerPreferences*>(InstanceManager::getDefault("WebServerPreferences"))->getRailroadName() + " \n").toLocal8Bit());
 newSocket->write(QString("NODE " + NodeIdentity::networkIdentity() + " \n").toLocal8Bit());
#endif

}
#if 0
// Handle communication to a client through inStream and outStream
//@Override
/*public*/ void handleClient(DataInputStream inStream, DataOutputStream outStream) throws IOException {
    Scanner inputScanner = new Scanner(new InputStreamReader(inStream, "UTF-8"));
    // Listen for commands from the client until the connection closes
    String cmd;

    // interface components
    SimplePowerServer powerServer = new SimplePowerServer(inStream, outStream);
    SimpleTurnoutServer turnoutServer = new SimpleTurnoutServer(inStream, outStream);
    SimpleLightServer lightServer = new SimpleLightServer(inStream, outStream);
    SimpleSensorServer sensorServer = new SimpleSensorServer(inStream, outStream);
    SimpleSignalHeadServer signalHeadServer = new SimpleSignalHeadServer(inStream, outStream);
    SimpleReporterServer reporterServer = new SimpleReporterServer(inStream, outStream);
    SimpleOperationsServer operationsServer = new SimpleOperationsServer(inStream, outStream);

    // Start by sending a welcome message
    outStream.writeBytes("JMRI " + jmri.Version.name() + " \n");
    outStream.writeBytes("RAILROAD " + InstanceManager.getDefault(WebServerPreferences.class).getRailroadName() + " \n");
    outStream.writeBytes("NODE " + NodeIdentity.identity() + " \n");

    while (true) {
        inputScanner.skip("[\r\n]*");// skip any stray end of line characters.
        // Read the command from the client
        try {
            cmd = inputScanner.nextLine();
        } catch (NoSuchElementException nse) {
            // we get an nse when we are finished with this client
            // so break out of the loop.
            break;
        }
#endif
    void JMRIClientRxHandler::handleMessage(QString cmd)
    {
        if (log->isDebugEnabled()) {
            log->debug("Received from client: " + cmd);
        }
        if (cmd.startsWith("POWER")) {
            try {
                powerServer->parseStatus(cmd);
                powerServer->sendStatus(static_cast<PowerManager*>(InstanceManager::getDefault("PowerManager"))->getPower());
            } catch (JmriException* je) {
                //outStream.writeBytes("not supported\n");
          powerServer->sendStatus("not supported");

            }
        } else if (cmd.startsWith("TURNOUT")) {
            try {
                turnoutServer->parseStatus(cmd);
            } catch (JmriException* je) {
                //outStream.writeBytes("not supported\n");
          turnoutServer->sendErrorStatus("not supported");
            }
        }
#if 1
        else if (cmd.startsWith("LIGHT")) {
            try {
                lightServer->parseStatus(cmd);
            } catch (JmriException* je) {
                //outStream.writeBytes("not supported\n");
          lightServer->sendErrorStatus("not supported");
            }
        }
#endif
        else if (cmd.startsWith("SENSOR")) {
            try {
                sensorServer->parseStatus(cmd);
            } catch (JmriException* je) {
                //outStream.writeBytes("not supported\n");
          sensorServer->sendErrorStatus("not supported");
            }
        }

        else if (cmd.startsWith("SIGNALHEAD")) {
            try {
                signalHeadServer->parseStatus(cmd);
            } catch (JmriException* je) {
                signalHeadServer->sendErrorStatus("not supported\n");
            }
        } else if (cmd.startsWith("REPORTER")) {
            try {
                reporterServer->parseStatus(cmd);
            } catch (JmriException* je) {
                reporterServer->sendErrorStatus("not supported\n");
            }
        }
#if 0
        else if (cmd.startsWith(SimpleOperationsServer.OPERATIONS)) {
            try {
                operationsServer.parseStatus(cmd);
            } catch (JmriException* je) {
                outStream.writeBytes("not supported\n");
            }
        }
#endif
        else {
            //outStream.writeBytes("Unknown Command " + cmd + "\n");
         clientSocket->write(QString("Unknown Command " + cmd + "\n").toLocal8Bit());
        }
//    }
//    inputScanner.close();

}

void SimpleServer::start()
{
 JmriServer::start();
 log->info(tr("SimpleServer started, listening on port %1").arg(portNo));

}

/*private*/ /*final*/ /*static*/ Logger* SimpleServer::log = LoggerFactory::getLogger("SimpleServer");
