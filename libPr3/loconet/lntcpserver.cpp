#include "lntcpserver.h"
#include "properties.h"
#include "fileutil.h"
#include "serverlistner.h"
//#include <QThread>
#include <QTextStream>
#include "clientrxhandler.h"
#include <QTcpSocket>
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"
#include "LnOverTcp/lntcppreferences.h"

//Server::Server(QObject *parent) :
//  QObject(parent)
//{
//}
LnTcpServer* LnTcpServer::self = NULL;
/*static*/ /*final*/ QString LnTcpServer::AUTO_START_KEY = "AutoStart";
/*static*/ /*final*/ QString LnTcpServer::PORT_NUMBER_KEY = "PortNumber";
/*static*/ /*final*/ QString LnTcpServer::SETTINGS_FILE_NAME = "LocoNetOverTcpSettings.ini";


/**
 * Implementation of the LocoNetOverTcp LbServer Server Protocol
 *
 * @author Alex Shepherd Copyright (C) 2006
 * @version	$Revision: 24409 $
 */
// /*public*/ class Server {


/*private*/ LnTcpServer::LnTcpServer(QObject *parent) :
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

 pm = LnTcpPreferences::getDefault();
 portNumber = pm->getPort();
// pm.addPropertyChangeListener((PropertyChangeEvent evt) -> {
//     switch (evt.getPropertyName()) {
//         case LnTcpPreferences.PORT:
//             // only change the port if stopped
//             if (!isEnabled()) {
//                 portNumber = pm.getPort();
//             }
//             break;
//         default:
//             // ignore uninteresting property changes
//             break;
//     }
// });
 connect(pm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

void LnTcpServer::propertyChange(PropertyChangeEvent * evt)
{
 if(evt->getPropertyName() == LnTcpPreferences::PORT)
 {
  // only change the port if stopped
  if (!isEnabled()) {
      portNumber = pm->getPort();
  }
  // ignore uninteresting property changes
 }
}

/*public*/ void LnTcpServer::setStateListner(ServerListner* l) {
 stateListner = l;
}

/**
 * Get the default server instance, creating it if necessary.
 *
 * @return the default server instance
 */
/*public*/ /*static*/ /*synchronized*/ LnTcpServer* LnTcpServer::getDefault() {
 LnTcpServer* server = (LnTcpServer*)InstanceManager::getOptionalDefault("LnTcpServer");
 if(server == NULL)
  server = (LnTcpServer*)InstanceManager::setDefault("LnTcpServer", new LnTcpServer());
 return server;
}

/*public*/ /*static synchronized*/ LnTcpServer* LnTcpServer::getInstance()
{
 LnTcpServer* server = (LnTcpServer*)InstanceManager::getOptionalDefault("LnTcpServer");
 if(server == NULL)
 {
  server = new LnTcpServer();
  (LnTcpServer*)InstanceManager::setDefault("LnTcpServer", server);
 }
 return server;
}
#if 0
/*private*/ void LnTcpServer::loadSettings()
{
 if (!settingsLoaded)
 {
  settingsLoaded = true;
  Properties* settings = new Properties();

  QString settingsFileName = FileUtil::getUserFilesPath() + SETTINGS_FILE_NAME;

  //try {
  log->debug("Server: opening settings file " + settingsFileName);
//      java.io.InputStream settingsStream = new FileInputStream(settingsFileName);
  try
  {
  QFile settingsFile(settingsFileName);
  if(!settingsFile.exists())
   return;
  if(settingsFile.open(QFile::ReadOnly))
  {
   QTextStream settingsStream(&settingsFile);
   settings->load(&settingsStream);
  }
  else
  {
   throw FileNotFoundException(settingsFileName);
  }
//      } finally {
   settingsFile.close();

   QString val = settings->getProperty(AUTO_START_KEY/*, "0"*/);
   autoStart = (val==("1"));
   val = settings->getProperty(PORT_NUMBER_KEY/*, "1234"*/);
   portNumber = val.toInt(0, 10);
  }
  catch (FileNotFoundException ex) {
      log->debug("Server: loadSettings file not found");
  }
//      catch (IOException ex) {
//      log->debug("Server: loadSettings exception: ", ex);
//  }
//  }
  updateServerStateListener();
 }
}


/*public*/ void LnTcpServer::saveSettings()
{
#if 1 // TODO:
    // we can't use the store capabilities of java.util.Properties, as
    // they are not present in Java 1.1.8
    QString settingsFileName = FileUtil::getUserFilesPath() + SETTINGS_FILE_NAME;
    log->debug("Server: saving settings file " + settingsFileName);

    try {
//        OutputStream outStream = new FileOutputStream(settingsFileName);
//        PrintStream settingsStream = new PrintStream(outStream);
     QFile f(settingsFileName);
     if(f.open(QIODevice::WriteOnly))
     {
      QTextStream stream(&f);
        //settingsStream.println("# LocoNetOverTcp Configuration Settings");
      stream << "# LocoNetOverTcp Configuration Settings" << "\n";
//        settingsStream.println(AUTO_START_KEY + " = " + (autoStart ? "1" : "0"));
      stream << AUTO_START_KEY + " = " + (autoStart ? "1" : "0") << "\n";
//        settingsStream.println(PORT_NUMBER_KEY + " = " + portNumber);
      stream << PORT_NUMBER_KEY + " = " + QString::number(portNumber) << "\n";
//        settingsStream.flush();
      stream.flush();
//        settingsStream.close();
      f.close();
        settingsChanged = false;
     }
     else
      throw FileNotFoundException(settingsFileName);
    } catch (FileNotFoundException ex) {
        log->warn("Server: saveSettings exception: "+ ex.getMessage());
    }
#endif
 updateServerStateListener();
}
#endif
/*public*/ bool LnTcpServer::getAutoStart()
{
 return true;
}

/*public*/ void LnTcpServer::setAutoStart(bool start)
{
 // do nothing
}

/*public*/ int LnTcpServer::getPortNumber()
{
 return portNumber;
}

/*public*/ void LnTcpServer::setPortNumber(int port)
{
 if ((port >= 1024) && (port <= 65535))
 {
  portNumber = port;
  settingsChanged = true;
  updateServerStateListener();
 }
}

/*public*/ bool LnTcpServer::isEnabled()
{
 //return (socketListener != NULL) && (socketListener->isRunning());
 return bIsEnabled;
}

/*public*/ bool LnTcpServer::isSettingChanged() {
    return settingsChanged;
}

/*public*/ void LnTcpServer::enable()
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
 log->info(tr("LnTcpServer listening on port %1").arg(portNumber));
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

void LnTcpServer::on_newConnection()
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

/*public*/ void LnTcpServer::disable()
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

/*public*/ void LnTcpServer::updateServerStateListener()
{
//    if (stateListner != NULL) {
//        stateListner->notifyServerStateChanged(this);
//    }
 emit serverStateChanged(this);
}

/*public*/ void LnTcpServer::updateClientStateListener()
{
// if (stateListner != NULL)
// {
//  stateListner->notifyClientStateChanged(this);
// }
 emit clientStateChanged(this, clients->count());
}

/**
 * Get the port this server is using.
 *
 * @return the port
 */
/*public*/ int LnTcpServer::getPort() {
    return this->portNumber;
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
/*protected*/ void LnTcpServer::addClient(ClientRxHandler* handler)
{
    /*synchronized (clients) */
 {
  clients->append(handler);
 }
 updateClientStateListener();
}

/*protected*/ void LnTcpServer::removeClient(ClientRxHandler* handler)
{
    /*synchronized (clients)*/
 {
  clients->removeOne(handler);
 }
 updateClientStateListener();
}

/*public*/ int LnTcpServer::getClientCount()
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
