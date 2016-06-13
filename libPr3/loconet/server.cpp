#include "server.h"
#include "properties.h"
#include "fileutil.h"
#include "serverlistner.h"
#include <QThread>
#include <QTextStream>
#include "clientrxhandler.h"
#include <QTcpSocket>
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"

//Server::Server(QObject *parent) :
//  QObject(parent)
//{
//}
Server* Server::self = NULL;
/*static*/ /*final*/ QString Server::AUTO_START_KEY = "AutoStart";
/*static*/ /*final*/ QString Server::PORT_NUMBER_KEY = "PortNumber";
/*static*/ /*final*/ QString Server::SETTINGS_FILE_NAME = "LocoNetOverTcpSettings.ini";


/**
 * Implementation of the LocoNetOverTcp LbServer Server Protocol
 *
 * @author Alex Shepherd Copyright (C) 2006
 * @version	$Revision: 24409 $
 */
// /*public*/ class Server {


/*private*/ Server::Server(QObject *parent) :
  QTcpServer(parent)
{
 settingsLoaded = false;
 settingsChanged = false;
 service = NULL;
 clients = new QLinkedList<ClientRxHandler*>();
 log = new Logger("Server");
 portNumber = 1234;
 stateListner = NULL;
 socketListener = NULL;
 bIsEnabled = false;
 connectionNbr = 1;
 serverSocket = NULL;

}

/*public*/ void Server::setStateListner(ServerListner* l) {
 stateListner = l;
}

/*public*/ /*static synchronized*/ Server* Server::getInstance()
{
 if (self == NULL)
 {
  self = new Server();
  if (self->getAutoStart())
  {
   self->enable();
  }
 }
 return self;
}
/*private*/ void Server::loadSettings()
{
 if (!settingsLoaded)
 {
  settingsLoaded = true;
  Properties* settings = new Properties();

  QString settingsFileName = FileUtil::getUserFilesPath() + SETTINGS_FILE_NAME;

  //try {
  log->debug("Server: opening settings file " + settingsFileName);
//      java.io.InputStream settingsStream = new FileInputStream(settingsFileName);
//      try {
  QFile settingsFile(settingsFileName);
  if(!settingsFile.exists())
   return;
  if(settingsFile.open(QFile::ReadOnly))
  {
   QTextStream settingsStream(&settingsFile);
   settings->load(&settingsStream);
//      } finally {
   settingsFile.close();

   QString val = settings->getProperty(AUTO_START_KEY/*, "0"*/);
   autoStart = (val==("1"));
   val = settings->getProperty(PORT_NUMBER_KEY/*, "1234"*/);
   portNumber = val.toInt(0, 10);
//  } catch (FileNotFoundException ex) {
//      log->debug("Server: loadSettings file not found");
//  } catch (IOException ex) {
//      log->debug("Server: loadSettings exception: ", ex);
//  }
  }
  updateServerStateListener();
 }
}


/*public*/ void Server::saveSettings()
{
#if 0 // TODO:
    // we can't use the store capabilities of java.util.Properties, as
    // they are not present in Java 1.1.8
    QString settingsFileName = FileUtil.getUserFilesPath() + SETTINGS_FILE_NAME;
    log->debug("Server: saving settings file " + settingsFileName);

    try {
        OutputStream outStream = new FileOutputStream(settingsFileName);
        PrintStream settingsStream = new PrintStream(outStream);
        settingsStream.println("# LocoNetOverTcp Configuration Settings");
        settingsStream.println(AUTO_START_KEY + " = " + (autoStart ? "1" : "0"));
        settingsStream.println(PORT_NUMBER_KEY + " = " + portNumber);

        settingsStream.flush();
        settingsStream.close();
        settingsChanged = false;
    } catch (FileNotFoundException ex) {
        log->warn("Server: saveSettings exception: ", ex);
    }
#endif
 updateServerStateListener();
}

/*public*/ bool Server::getAutoStart()
{
 loadSettings();
 return autoStart;
}

/*public*/ void Server::setAutoStart(bool start)
{
 loadSettings();
 autoStart = start;
 settingsChanged = true;
 updateServerStateListener();
}

/*public*/ int Server::getPortNumber()
{
 loadSettings();
 return portNumber;
}

/*public*/ void Server::setPortNumber(int port)
{
 loadSettings();
 if ((port >= 1024) && (port <= 65535))
 {
  portNumber = port;
  settingsChanged = true;
  updateServerStateListener();
 }
}

/*public*/ bool Server::isEnabled()
{
 //return (socketListener != NULL) && (socketListener->isRunning());
 return bIsEnabled;
}

/*public*/ bool Server::isSettingChanged() {
    return settingsChanged;
}

/*public*/ void Server::enable()
{
#if 0
    if (socketListener == NULL) {
        socketListener = new Thread(new ClientListener());
        socketListener.setDaemon(true);
        socketListener.setName("LocoNetOverTcpServer");
        log->info("Starting new LocoNetOverTcpServer listener on port " + portNumber);
        socketListener.start();
        updateServerStateListener();
        // advertise over Zeroconf/Bonjour
        if (this.service == NULL) {
            this.service = ZeroConfService.create("_loconetovertcpserver._tcp.local.", portNumber);
        }
        log->info("Starting ZeroConfService _loconetovertcpserver._tcp.local for LocoNetOverTCP Server");
        this.service.publish();
        if (this.shutDownTask == NULL) {
            this.shutDownTask = new QuietShutDownTask("LocoNetOverTcpServer") {
                @Override
                /*public*/ bool execute() {
                    Server.getInstance().disable();
                    return true;
                }
            };
        }
        if (this.shutDownTask != NULL && InstanceManager.shutDownManagerInstance() != NULL) {
            InstanceManager.shutDownManagerInstance().register(this.shutDownTask);
        }
    }
#endif
 listen(QHostAddress::Any, portNumber);
 connect(this, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
 updateServerStateListener();
 if (this->shutDownTask == NULL)
 {
//  this.shutDownTask = new QuietShutDownTask("LocoNetOverTcpServer") {
//         @Override
//         /*public*/ bool execute() {
//             Server.getInstance().disable();
//             return true;
//         }
//     };
  this->shutDownTask = new ServerQuietShutDownTask("LocoNetOverTcpServer", this);
 }
 bIsEnabled = true;
}

void Server::on_newConnection()
{

 QTcpSocket* socket = nextPendingConnection();
 if(socket != NULL)
 {
  QString remoteAddress = socket->peerAddress().toString();
  ClientRxHandler* rxHandler;
  addClient(rxHandler = new ClientRxHandler(remoteAddress,socket, connectionNbr++));

  log->debug("New connection from "+ remoteAddress);
 }
}

/*public*/ void Server::disable()
{
#if 1 // TODO:
 //if (socketListener != NULL)
// {
//  socketListener.interrupt();
//  socketListener = NULL;
  try
  {
   if (serverSocket != NULL) {
       serverSocket->close();
   }
  }
  catch (IOException ex) {
  }

  updateServerStateListener();

  // Now close all the client connections
  QLinkedList<ClientRxHandler*> clientsArray;

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
// this->service.stop();
 if (this->shutDownTask != NULL && InstanceManager::shutDownManagerInstance() != NULL) {
     InstanceManager::shutDownManagerInstance()->deregister(this->shutDownTask);
 }
 bIsEnabled = false;
#endif
}

/*public*/ void Server::updateServerStateListener()
{
//    if (stateListner != NULL) {
//        stateListner->notifyServerStateChanged(this);
//    }
 emit serverStateChanged(this);
}

/*public*/ void Server::updateClientStateListener()
{
// if (stateListner != NULL)
// {
//  stateListner->notifyClientStateChanged(this);
// }
 emit clientStateChanged(this, clients->count());
}
#if 0
class ClientListener implements Runnable {

    /*public*/ void run() {
        Socket newClientConnection;
        String remoteAddress;
        try {
            serverSocket = new ServerSocket(getPortNumber());
            SocketUtil.setReuseAddress(serverSocket, true);
            while (!socketListener.isInterrupted()) {
                newClientConnection = serverSocket.accept();
                remoteAddress = SocketUtil.getRemoteSocketAddress(newClientConnection);
                log->info("Server: Connection from: " + remoteAddress);
                addClient(new ClientRxHandler(remoteAddress, newClientConnection));
            }
            serverSocket.close();
        } catch (IOException ex) {
            if (ex.toString().indexOf("socket closed") == -1) {
                log->error("Server: IO Exception: ", ex);
            }
        }
        serverSocket = NULL;
    }
};
#endif
/*protected*/ void Server::addClient(ClientRxHandler* handler)
{
    /*synchronized (clients) */
 {
  clients->append(handler);
 }
 updateClientStateListener();
}

/*protected*/ void Server::removeClient(ClientRxHandler* handler)
{
    /*synchronized (clients)*/
 {
  clients->removeOne(handler);
 }
 updateClientStateListener();
}

/*public*/ int Server::getClientCount()
{
    /*synchronized (clients)*/
 {
  return clients->size();
 }
}
#if 0
void Server::incomingConnection(int socketDescriptor)
{
 QTcpSocket* tcpSocket;
 if (!tcpSocket->setSocketDescriptor(socketDescriptor))
 {
  emit error(tcpSocket->error());
  return;
 }
 ClientRxHandler* clientRxHandler = new ClientRxHandler(tcpSocket->peerAddress().toString(), tcpSocket);
 Server::addClient(clientRxHandler);
}
#endif
