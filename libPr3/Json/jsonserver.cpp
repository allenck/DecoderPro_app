#include "jsonserver.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "jsonserverpreferences.h"
#include "jsonconnection.h"
#include "jsonclienthandler.h"
#include "sleeperthread.h"
#include "json.h"
#include <QNetworkInterface>
#include "zeroconfservice.h"

/**
 * This is an implementation of a JSON server for JMRI. See
 * {@link jmri.server.json} for more details.
 *
 * @author Paul Bender Copyright (C) 2010
 * @author Randall Wood Copyright (C) 2016
 */
///*public*/ class JsonServer extends JmriServer {

/*private*/ /*static*/ /*final*/ Logger* JsonServer::log = LoggerFactory::getLogger("JsonServer");

/**
 * Get the default JsonServer, creating it if needed.
 *
 * @return the default JsonServer instance.
 */
/*public*/ /*static*/ JsonServer* JsonServer::getDefault() {
//        return InstanceManager.getOptionalDefault("JsonServer".class).orElseGet(() -> {
//            return InstanceManager.setDefault(JsonServer.class, new JsonServer());
//        });
if(InstanceManager::getOptionalDefault("JsonServer") == NULL)
  return (JsonServer*)InstanceManager::setDefault("JsonServer", new JsonServer());
else
 return (JsonServer*)InstanceManager::getOptionalDefault("JsonServer");
}

/**
 * Create a new server using the default port.
 */
/*public*/ JsonServer::JsonServer(QObject* parent) : QTcpServer(parent)
{
 common();
}

/**
 * Create a new server.
 *
 * @param port    the port to listen on
 * @param timeout the timeout before closing unresponsive connections
 */
/*public*/ JsonServer::JsonServer(int port, int timeout, QObject* parent) : QTcpServer(parent) {
    //super(port, timeout);
 common();
 this->port = port;
 this->timeout = timeout;
}
void JsonServer::common()
{
    this->mapper = ObjectMapper();//new ObjectMapper().configure(Feature.AUTO_CLOSE_SOURCE, false);
    shutDownTask = new JSShutDownTask("Stop JSON Server", this); // { // NOI18N
//        //@Override
//        /*public*/ boolean execute() {
//            try {
//                JsonServer.this->stop();
//            } catch (Exception ex) {
//                log.warn("ERROR shutting down JSON Server: {}" + ex.getMessage());
//                log.debug("Details follow: ", ex);
//            }
//            return true;
//        }
//    };
    settings = JsonServerPreferences::getDefault();
    port = settings->getPort();
    timeout = settings->getHeartbeatInterval();
    clients = new QLinkedList<JsonClientRxHandler*>();
    setProperty("InstanceManagerAutoDefault", "yes");

}

JSShutDownTask::JSShutDownTask(QString title, JsonServer* js) :QuietShutDownTask(title, js)
{
      this->js = js;
}

#if 0
bool JSShutDownTask::eventFilter(QObject *watched, QEvent *event)
{
 try {
     js->stop();
 } catch (Exception ex) {
     js->log->warn("ERROR shutting down JSON Server: {}" + ex.getMessage());
     js->log->debug("Details follow: " + ex.getMessage());
 }
 return true;
}
#endif
/*public*/ bool JSShutDownTask::execute()
{
  try {
      js->stop();
  } catch (Exception ex) {
      js->log->warn(tr("ERROR shutting down JSON Server: %1").arg(ex.getMessage()));
      js->log->debug("Details follow: " + ex.getMessage());
  }
  return true;

}
//@Override
/*public*/ void JsonServer::start() {
    log->info(tr("Starting JSON Server on port %1").arg(this->port));
    //JmriServer::start();
    listen(QHostAddress::Any, port);
    connect(this, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
}

// Advertise the service with ZeroConf
//protected void advertise() {
//    this.advertise("_jmri._tcp.local.");
//}

/*protected*/ void JsonServer::advertise(QString type) {
    this->advertise(type, QMap<QString, QVariant>());
}

/*protected*/ void JsonServer::advertise(QString type, QMap<QString, QVariant> properties) {
    if (this->service == nullptr) {
        this->service = ZeroConfService::create(type, this->port, properties);
    }
    this->service->publish();
}

//@Override
/*public*/ void JsonServer::stop() {
    log->info("Stopping JSON Server.");
    //JmriServer::stop();
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
    QLinkedList<JsonClientRxHandler*> clientsArray;
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

//@Override
/*protected*/ void JsonServer::advertise() {
    QMap<QString, QVariant> properties = QMap<QString, QVariant>();
    properties.insert(JSON::_JSON, JSON::JSON_PROTOCOL_VERSION);
    this->advertise(JSON::ZEROCONF_SERVICE_TYPE, properties);
}

void JsonServer::servicePublished()
{
 log->info(tr("JsonServer: ZeroService started"));
}

void JsonServer::error(QZeroConf::error_t e)
{
 log->error(tr("JsonServer: Zero conf Service error %1").arg(e));
}
#if 0
// Handle communication to a client through inStream and outStream
//@Override
/*public*/ void JsonServer::handleClient(QDataStream* inStream, QDataStream* outStream) throw (IOException)
{

    ObjectReader reader = this->mapper.reader();
    JsonClientHandler* handler = new JsonClientHandler(new JsonConnection(outStream));

    // Start by sending a welcome message
    handler->onMessage(JsonClientHandler::HELLO_MSG);

    while (true) {
        try {
            handler->onMessage(reader.readTree(inStream));
            // Read the command from the client
        } catch (IOException e) {
            // attempt to close the connection and throw the exception
            handler->dispose();
            throw e;
        } catch (NoSuchElementException nse) {
            // we get an NSE when we are finished with this client
            // so break out of the loop
            break;
        }
    }
    handler->dispose();
}
#endif

//@Override
/*public*/ void JsonServer::stopClient(QTextStream* inStream, QTextStream* outStream) throw (IOException) {
#if 0
    outStream.writeBytes(this->mapper.writeValueAsString(this->mapper.createObjectNode().put(TYPE, GOODBYE)));
    try {
        // without this delay, the output stream could be closed before the
        // preparing to disconnect message is sent
        //TimeUnit.MILLISECONDS.sleep(100);
     SleeperThread::msleep(100);
    } catch (InterruptedException ex) {
        // log for debugging only, since we are most likely shutting down the
        // server or the program entirely at this point, so it doesn't matter
        log->debug("Wait to send clean shutdown message interrupted.");
    }
#endif
}

/*protected*/ void JsonServer::removeClient(JsonClientRxHandler* handler)
{
    /*synchronized (clients)*/
 {
  clients->removeOne(handler);
 }
 //updateClientStateListener();
}


void JsonServer::on_newConnection()
{
 QTcpSocket* socket = nextPendingConnection();
 if(socket != NULL)
 {
  QString remoteAddress = socket->peerAddress().toString();
  JsonClientRxHandler* rxHandler;
  addClient(rxHandler = new JsonClientRxHandler(remoteAddress,socket, connectionNbr++));

  log->debug("New connection from "+ remoteAddress);
 }
}
/*protected*/ void JsonServer::addClient(JsonClientRxHandler* handler)
{
    /*synchronized (clients) */
 {
  clients->append(handler);
 }
// updateClientStateListener();
}


JsonClientRxHandler::JsonClientRxHandler(QString newRemoteAddress, QTcpSocket *newSocket, int connectionNbr, QObject *parent)
{
 clientSocket = newSocket;
 setPriority(QThread::HighestPriority);
 remoteAddress = newRemoteAddress;
 setObjectName("JsonClientRxHandler:" + QString(" #%1").arg(connectionNbr));
 bIsInterrupted = false;
 log = new Logger(objectName());
 log->setDebugEnabled(true);
 //lastSentMessage = NULL;
 log->debug(tr("started, connected to ") + newRemoteAddress);

 txHandler = new JsonClientTxHandler(remoteAddress, newSocket, connectionNbr);
}

void JsonClientRxHandler::run()
{
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(on_clientSocket_disconnected()));
 inStream = new QTextStream(clientSocket);
 connect(clientSocket, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(quit()));
 exec();
 inStream = NULL;
 clientSocket->close();
 JsonServer::getDefault()->removeClient(this);
 log->info("JsonClientRxHandler: Exiting");
}

void JsonClientRxHandler::on_readyRead()
{

 while (!isInterrupted()  && clientSocket->isValid() && clientSocket->isOpen() )
 {
  if(log->isDebugEnabled() && clientSocket->bytesAvailable() > 0)
   log->debug(tr("Socket has %1 bytes ready").arg(clientSocket->bytesAvailable()));
  inString = inStream->readLine();
  if (inString.isEmpty())
  {
   //log->debug("ClientRxHandler: Remote Connection Closed");
   //interrupt();
   return;
  }
  else
  {
   log->debug("JsonClientRxHandler: Received: " + inString);
   emit passMessage(inString);
  }
 }
}

bool JsonClientRxHandler::isInterrupted()
{
 return bIsInterrupted;
}

void JsonClientRxHandler::on_clientSocket_disconnected()
{

}

void JsonClientRxHandler::close()
{

}

void JsonClientRxHandler::message(QString msg)
{
 emit message(msg);
}
/*public*/ void JsonClientTxHandler::run()
{


 exec();
 // Interrupt the Parent to let it know we are exiting for some reason
 //parentThread.interrupt();
// parentThread->exit();

// parentThread = NULL;
 log->info("JsonClientTxHandler: Exiting");
}
void JsonClientRxHandler::displayError(QAbstractSocket::SocketError)
{

}

void JsonClientTxHandler::sendMessage(QString msg)
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
JsonClientTxHandler::JsonClientTxHandler(QString newRemoteAddress, QTcpSocket *newSocket, int connectionNbr)
{
 Q_UNUSED(newRemoteAddress);
 Q_UNUSED(newSocket);
 Q_UNUSED(connectionNbr);
 log->debug("JsonClientTxHandler called");
}
