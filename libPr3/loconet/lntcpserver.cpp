#include "lntcpserver.h"
#include "properties.h"
#include "fileutil.h"
#include "serverlistner.h"
//#include <QThread>
#include <QTextStream>
#include <QTcpSocket>
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"
#include "LnOverTcp/lntcppreferences.h"
#include <QNetworkInterface>
#include "loggerfactory.h"

//Server::Server(QObject *parent) :
//  QObject(parent)
//{
//}
LnTcpServer* LnTcpServer::self = nullptr;
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


/*private*/ LnTcpServer::LnTcpServer(LocoNetSystemConnectionMemo* memo, QObject *parent) :
  QTcpServer(parent)
{
 tc = memo->getLnTrafficController(); // store tc in order to know where to send messages
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
 //connect(pm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 pm->addPropertyChangeListener((PropertyChangeListener*)this);
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

/**
 * Get the default server instance, creating it if necessary.
 *
 * @return the default server instance
 */
/*public*/ /*static*/ /*synchronized*/ LnTcpServer* LnTcpServer::getDefault() {
 LnTcpServer* server = (LnTcpServer*)InstanceManager::getOptionalDefault("LnTcpServer");
 if(server == nullptr)
  server = (LnTcpServer*)InstanceManager::setDefault("LnTcpServer", new LnTcpServer((LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo")));
 return server;
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
 // advertise over Zeroconf/Bonjour
 // need https://github.com/jbagg/QtZeroConf, sudo apt-get install libavahi-client-dev
#if 0
 if (this->service == nullptr) {
     //this->service = ZeroConfService.create("_loconetovertcpserver._tcp.local.", portNumber);
  this->service = new QZeroConf();
  this->service->clearServiceTxtRecords();
 }
 log->info("Starting ZeroConfService _loconetovertcpserver._tcp.local for LocoNetOverTCP Server");
 connect(this->service, SIGNAL(servicePublished()), this, SLOT(servicePublished()));
 connect(this->service, SIGNAL(error(QZeroConf::error_t)), this, SLOT(error(QZeroConf::error_t)));
 this->service->startServicePublish(buildName().toUtf8(), "_loconetovertcpserver._tcp", "local", portNumber);
#else
 // advertise over Zeroconf/Bonjour
 if (this->service == NULL) {
     this->service = ZeroConfService::create("_loconetovertcpserver._tcp.local.", portNumber);
 }
 log->info("Starting ZeroConfService _loconetovertcpserver._tcp.local for LocoNetOverTCP Server");
 this->service->publish();
#endif
 if (this->shutDownTask == nullptr)
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

#ifdef Q_OS_IOS
 #define	OS_NAME		"iOS"
#elif defined(Q_OS_MAC)
 #define	OS_NAME		"Mac"
#elif defined(Q_OS_ANDROID)
 #define	OS_NAME		"Android"
#elif defined(Q_OS_LINUX)
 #define	OS_NAME		"Linux"
#elif defined(Q_OS_WIN)
 #define	OS_NAME		"Windows"
#elif defined(Q_OS_FREEBSD)
 #define	OS_NAME		"FreeBSD"
#else
 #define	OS_NAME		"Some OS"
#endif

QString LnTcpServer::buildName(void)
{
    QString name;

 QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); // now you have interfaces list

 name = list.last().hardwareAddress();
 name.remove(":");
 name.remove(0, 6);
 name+= ')';
 name.prepend("Qt ZeroConf Test - " OS_NAME " (");
    return name;
}

void LnTcpServer::servicePublished()
{
 log->info(tr("ZeroService started"));
}

void LnTcpServer::error(QZeroConf::error_t e)
{
 log->error(tr("Zero conf Service error %1").arg(e));
}

void LnTcpServer::on_newConnection()
{

 QTcpSocket* socket = nextPendingConnection();
 if(socket != nullptr)
 {
  QString remoteAddress = socket->peerAddress().toString();
  ClientRxHandler* rxHandler;
  addClient(rxHandler = new ClientRxHandler(remoteAddress,socket, tc, connectionNbr++));

  log->debug("New connection from "+ remoteAddress);
 }
}

/*public*/ void LnTcpServer::disable()
{
 //if (socketListener != nullptr)
// {
//  socketListener.interrupt();
//  socketListener = NULL;
 try
 {
  if (serverSocket != nullptr) {
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
 if (this->service != nullptr) {
     this->service->stop();
 }

 if (this->shutDownTask != nullptr && static_cast<ShutDownManager*>(InstanceManager::getDefault("ShutDownManager")) != nullptr) {
     static_cast<ShutDownManager*>(InstanceManager::getDefault("ShutDownManager"))->deregister(this->shutDownTask);
 }
 bIsEnabled = false;
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
// if (stateListner != nullptr)
// {
//  stateListner->notifyClientStateChanged(this);
// }
 emit clientStateChanged(this, clients->count());
}
#if 0 // TODO:
/*private*/ void updateServerStateListeners() {
    synchronized (this) {
        this.stateListeners.stream().filter((l) -> (l != null)).forEachOrdered((l) -> {
            l.notifyServerStateChanged(this);
        });
    }
}

/*private*/ void updateClientStateListeners() {
    synchronized (this) {
        this.stateListeners.stream().filter((l) -> (l != null)).forEachOrdered((l) -> {
            l.notifyClientStateChanged(this);
        });
    }
}

/*public*/ void addStateListener(LnTcpServerListener l) {
    this.stateListeners.add(l);
}

/*public*/ bool removeStateListener(LnTcpServerListener* l) {
    return this.stateListeners.remove(l);
}
#endif
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
        serverSocket = nullptr;
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

/*private*/ /*final*/ /*static*/ Logger* LnTcpServer::log = LoggerFactory::getLogger("LnTcpServer");
