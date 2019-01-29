#include "deviceserver.h"
#include "logger.h"
#include "loggerfactory.h"
#include <QTimer>
#include "commandstation.h"
#include "instancemanager.h"
#include "system.h"
#include <QTcpSocket>
#include "withrottlemanager.h"
#include "withrottlepreferences.h"
#include "rosterentry.h"
#include "roster.h"
#include "devicemanager.h"
#include "webserverpreferences.h"
#include "throttlecontroller.h"
#include "trackpowercontroller.h"
#include "turnoutcontroller.h"
#include "routecontroller.h"
#include "multithrottle.h"
#include "consistcontroller.h"
#include "devicelistener.h"
#include "stringutil.h"
#include "sleeperthread.h"
#include "multithrottlecontroller.h"
#include "throttlelistener.h"
#include "userinterface.h"
#include <QJsonDocument>
#include "jsonclienthandler.h"
#include "jsonconnection.h"

//DeviceServer::DeviceServer(QObject *parent) : QObject(parent)
//{

//}
/*private*/ /*static*/ DeviceServer* DeviceServer::_instance = NULL;
/*public*/ /*static*/ DeviceServer* DeviceServer::instance()
{
 if(_instance == NULL)
  throw Exception("Server not created!");
 return _instance;
}

/**
 * WiThrottle
 *
 * @author Brett Hoffman Copyright (C) 2009, 2010
 * @author Created by Brett Hoffman on:
 * @author 7/20/09.
 *
 * Thread with input and output streams for each connected device. Creates an
 * invisible throttle window for each.
 *
 * Sorting codes:
 *  'T'hrottle - sends to throttleController
 *  'S'econdThrottle - sends to secondThrottleController
 *  'C' - Not used anymore except to provide backward compliance, same as 'T'
 *  'N'ame of device
 *  'H' hardware info - followed by:
 *      'U' UDID - unique device identifier
 *  'P' panel - followed by:
 *      'P' track power
 *      'T' turnouts
 *      'R' routes
 *  'R' roster - followed by:
 *      'C' consists
 *  'Q'uit - device has quit, close its throttleWindow
 *  '*' - heartbeat from client device ('*+' starts, '*-' stops)
 *
 * Added in v2.0: 'M'ultiThrottle - forwards to MultiThrottle class, see notes
 * there for use. Followed by id character to create or control appropriate
 * DccThrottle. Stored as HashTable for access to 'T' and 'S' throttles.
 *
 * 'D'irect byte packet to rails Followed by one digit for repeats, then
 * followed by hex pairs, (single spaced) including pair for error byte. D200 90
 * 90 - Send '00 90 90' twice, with error byte '90'
 *
 *
 * Out to client, all newline terminated:
 *
 * Track power: 'PPA' + '0' (off), '1' (on), '2' (unknown) Minimum package
 * length of 4 char.
 *
 * Send Info on routes to devices, not specific to any one route. Format:
 * PRT]\[value}|{routeKey]\[value}|{ActiveKey]\[value}|{InactiveKey Send list of
 * routes Format:
 * PRL]\[SysName}|{UsrName}|{CurrentState]\[SysName}|{UsrName}|{CurrentState
 * States: 1 - UNKNOWN, 2 - ACTIVE, 4 - INACTIVE (based on turnoutsAligned
 * sensor, if used)
 *
 * Send Info on turnouts to devices, not specific to any one turnout. Format:
 * PTT]\[value}|{turnoutKey]\[value}|{closedKey]\[value}|{thrownKey Send list of
 * turnouts Format:
 * PTL]\[SysName}|{UsrName}|{CurrentState]\[SysName}|{UsrName}|{CurrentState
 * States: 1 - UNKNOWN, 2 - CLOSED, 4 - THROWN
 *
 * Web server port: 'PW' + {port#}
 *
 * Roster is sent formatted: ]\[ separates roster entries, }|{ separates info in
 * each entry e.g. RL###]\[RVRR1201}|{1201}|{L]\[Limited}|{8165}|{L]\[
 *
 * Function labels: RF## first throttle, or RS## second throttle, each label
 * separated by ]\[ e.g. RF29]\[Light]\[Bell]\[Horn]\[Short Horn]\[ &etc.
 *
 * RSF 'R'oster 'P'roperties 'F'unctions
 *
 *
 * Heartbeat send '*0' to tell device to stop heartbeat, '*#' # = number of
 * seconds until eStop. This class sends initial to device, but does not start
 * monitoring until it gets a response of '*+' Device should send heartbeat to
 * server in shorter time than eStop
 *
 * Alert message: 'HM' + message to display. Cannot have newlines in body of
 * text, only at end of message.
 *
 */
/*private*/ /*static*/ /*final*/ QString DeviceServer::versionNumber = "2.0";

// /*public*/ class DeviceServer implements Runnable, ThrottleControllerListener, ControllerInterface {

DeviceServer::DeviceServer(int socketPort, DeviceManager* manager, QObject *parent) : QWebSocketServer("JMRI", QWebSocketServer::NonSecureMode, parent) {
 //  Manually increment as features are added

 log->debug("Start DeviceServer");
 cmdStation = (CommandStation*)InstanceManager::getNullableDefault("CommandStation");
 newLine = System::getProperty("line.separator");
 in = NULL;
 out = NULL;
 this->socketPort = socketPort;
 _instance = this;
 listeners = NULL;
 ekg = NULL;
 throttleController = NULL;
 secondThrottleController = NULL;
 multiThrottles = NULL;
 deviceName = "Unknown";

 isUsingHeartbeat = false;
 heartbeat = true;
 pulseInterval = 16; // seconds til disconnect
 clients = new QLinkedList<ServerRxHandler*>();

 trackPower = NULL;
 isTrackPowerAllowed = WiThrottleManager::withrottlePreferencesInstance()->isAllowTrackPower();
 turnoutC = NULL;
 routeC = NULL;
 isTurnoutAllowed = WiThrottleManager::withrottlePreferencesInstance()->isAllowTurnout();
 isRouteAllowed = WiThrottleManager::withrottlePreferencesInstance()->isAllowRoute();
 consistC = NULL;
 //this->device = socket;
 connectionNbr = 0;
 this->manager = manager;
 if (listeners == NULL)
 {
  listeners = new QVector<DeviceListener*>(2);
 }
 qDebug() << "DeviceServer Listening on port " << socketPort;
 listen(QHostAddress::Any, this->socketPort);
 connect(this, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
}

void DeviceServer::on_newConnection()
{
 QWebSocket* socket = nextPendingConnection();
 if(socket != NULL)
 {
  QString remoteAddress = socket->peerAddress().toString();
  QString host = socket->peerName();
  ServerRxHandler* rxHandler;
  addClient(rxHandler = new ServerRxHandler(remoteAddress,socket, connectionNbr++));
  connect(rxHandler, SIGNAL(passMessage(QString)), this, SLOT(handleMessage(QString)));
  connect(rxHandler, SIGNAL(disconnected(QString)), this, SLOT(on_disconnected(QString)));

  ServerTxHandler* txHandler;
  txHandler = new ServerTxHandler(remoteAddress, socket, connectionNbr);
  connect(this, SIGNAL(sendPacket(QString)), txHandler, SLOT(sendMessage(QString)));

  emit deviceConnected(new WiDevice(deviceName, remoteAddress, deviceUDID, this));

  handler = new JsonClientHandler(new JsonConnection(socket));

  log->debug("New connection from "+ remoteAddress);
#if 0
    try {
        if (log->isDebugEnabled()) {
            log->debug("Creating input  stream reader for " + device->peerAddress().toString());//.getRemoteSocketAddress());
        }

        in = new QTextStream(device);//new BufferedReader(new InputStreamReader(device.getInputStream(), "UTF8"));
        if (log->isDebugEnabled()) {
            log->debug("Creating output stream writer for " + device->peerAddress().toString()); //.getRemoteSocketAddress());
        }
        out = new QTextStream(device);//new PrintStream(device.getOutputStream(), true, "UTF8");

    } catch (IOException e) {
        log->error("Stream creation failed (DeviceServer)");
        return;
    }
#endif
    sendPacketToDevice("VN" + getWiTVersion());
    sendPacketToDevice(sendRoster());
    addControllers();
    sendPacketToDevice("PW" + getWebServerPort());

 }
}
#if 1
//@Override
/*public*/ void DeviceServer::run()
{
#if 0
 for (int i = 0; i < listeners->size(); i++)
 {
  DeviceListener* l = listeners->at(i);
  log->debug("Notify Device Add");
  l->notifyDeviceConnected(this);
 }
#else
 emit serverStateChanged(this);

#endif
 QString inPackage = NULL;

 keepReading = true;	//	Gets set to false when device sends 'Q'uit
 int consecutiveErrors = 0;
}

void DeviceServer::on_disconnected( QString address )
{
 emit deviceDisconnected(new WiDevice("", address, "", this));
}

void DeviceServer::handleMessage(QString msg)
{
// do
// {
  try
  {
   inPackage = msg;

   if (inPackage != NULL)
   {
    heartbeat = true;   //  Any contact will keep alive
    consecutiveErrors = 0;  //reset error counter
    if (log->isDebugEnabled())
    {
     QString s = inPackage + "                    "; //pad output so messages form columns
     s = s.mid(0, qMax(inPackage.length(), 20));
//     log->debug("Rcvd: " + s + " from " + getName() + device->peerAddress().toString());
    }

    //switch (inPackage.charAt(0)) {
    QChar c = inPackage.at(0);
    if(c =='T')
    {
      if (throttleController == NULL)
      {
       throttleController = new ThrottleController('T', (ThrottleControllerListener*)this, (ControllerInterface*)this);
      }
      keepReading = throttleController->sort(inPackage.mid(1));
//                        break;
    }
    else if(c =='S')
    {
     if (secondThrottleController == NULL)
     {
         secondThrottleController = new ThrottleController('S', (ThrottleControllerListener*)this, (ControllerInterface*)this);
     }
     keepReading = secondThrottleController->sort(inPackage.mid(1));
     //break;
    }
    else if(c == 'M')
    {  //  MultiThrottle M(id character)('A'ction '+' or '-')(message)
     if (multiThrottles == NULL)
     {
         multiThrottles = new QHash<QChar, MultiThrottle*>(/*1*/);
     }
     QChar id = inPackage.at(1);
     if (!multiThrottles->contains(id))
     {   //  Create a MT if this is a new id
         multiThrottles->insert(id, new MultiThrottle(id, (ThrottleControllerListener*)this, (ControllerInterface*)this));
     }

     // Strips 'M' and id, forwards rest
     multiThrottles->value(id)->handleMessage(inPackage.mid(2));

     //break;
    }
    if(c == 'D')
    {
     if (log->isDebugEnabled()) {
         log->debug("Sending hex packet: " + inPackage.mid(2) + " to command station.");
     }
     int repeats = inPackage.at(1).unicode();//Character.getNumericValue(inPackage.charAt(1));
     QByteArray packet = StringUtil::bytesFromHexString(inPackage.mid(2));
     cmdStation->sendPacket(packet, repeats);
     //break;
    }
    else if(c == '*')
    {  //  Heartbeat only

     if (inPackage.length() > 1)
     {
         //switch (inPackage.get(1)) {
      QChar d = inPackage.at(1);

      if(d == '+')
      {  //  trigger, turns on timed monitoring
       if (!isUsingHeartbeat) {
           startEKG();
       }
       //break;
      }
      else if(d == '-')
      {  //  turns off
       if (isUsingHeartbeat) {
           stopEKG();
       }
       //break;
      }
    }
   //break;
   }    //  end heartbeat block
   else if(c == 'C')
   {  //  Prefix for confirmed package
//                        switch (inPackage.at(1))
//                        {

    QChar d = inPackage.at(1);
    if(d == 'T')
    {
     keepReading = throttleController->sort(inPackage.mid(2));
     //break;
    }
    else
    {
     log->warn("Received unknown network package: " + inPackage);
                    //break;
//                            }
    }
            //break;
   }
   else if(c == 'N')
   {  //  Prefix for deviceName
    deviceName = inPackage.mid(1);
    log->info("Received Name: " + deviceName);
    emit deviceInfoChanged(new WiDevice(deviceName, device->peerAddress().toString(),deviceUDID, this ));

    if (WiThrottleManager::withrottlePreferencesInstance()->isUseEStop())
    {
        pulseInterval = WiThrottleManager::withrottlePreferencesInstance()->getEStopDelay();
        sendPacketToDevice("*" + QString::number(pulseInterval)); //  Turn on heartbeat, if used
    }
            //break;
   }
   else if(c == 'H')
   {  //  Hardware
//                        switch (inPackage.charAt(1)) {
    QChar d = inPackage.at(1);
    if(d == 'U')
    {
     deviceUDID = inPackage.mid(2);
     for (int i = 0; i < listeners->size(); i++)
     {
          DeviceListener* l = listeners->value(i);
          l->notifyDeviceInfoChanged(new WiDevice(deviceName, device->peerAddress().toString(), deviceUDID, this));
     }
     // break;
    }
//                        }
           //break;
   }   //  end hardware block
   else if(c == 'P')
   {  //  Start 'P'anel case
//                        switch (inPackage.charAt(1)) {
    QChar d = inPackage.at(1);
    if(d == 'P')
    {
     if (isTrackPowerAllowed) {
         trackPower->handleMessage(inPackage.mid(2));
     }
     //break;
    }
    else if(d == 'T')
    {
     if (isTurnoutAllowed) {
         turnoutC->handleMessage(inPackage.mid(2));
     }
     //break;
    }
    else if(d == 'R')
    {
     if (isRouteAllowed) {
         routeC->handleMessage(inPackage.mid(2));
     }
     //break;
    }
//                        }
//break;
   }   //  end panel block
   else if(c ==  'R')
   {  //  Start 'R'oster case
//                        switch (inPackage.charAt(1)) {
    QChar d = inPackage.at(1);
    if(d == 'C')
    {
     if (isConsistAllowed) {
         consistC->handleMessage(inPackage.mid(2));
     }
     //break;
    }
//                        }
            //break;
   }   //  end roster block
   else if (c == 'Q')
   {
    keepReading = false;
//     break;
   }
   else
   {
     if(inPackage.startsWith("{"))
     {
      QJsonDocument jdoc = QJsonDocument::fromJson(inPackage.toUtf8());
 //     qDebug() << "compact: " << jdoc.toJson(QJsonDocument::Compact) << " type:" << jdoc.object().value("type").toString();
      handler->onMessage(inPackage);
     }
     else
     {
     //  If an unknown makes it through, do nothing.
            log->warn("Received unknown network package: " + inPackage);
            //break;
      if(inPackage.startsWith("{"))
      {
       QJsonDocument jdoc = QJsonDocument::fromJson(inPackage.toUtf8());
//     qDebug() << "compact: " << jdoc.toJson(QJsonDocument::Compact) << " type:" << jdoc.object().value("type").toString();
       handler->onMessage(inPackage);
      }
     }
   }   //End of charAt(0) switch block

   inPackage = "";
   }
   else
   { //in.readLine() IS NULL
       consecutiveErrors += 1;
       log->warn(tr("NULL readLine() from device '%1', consecutive error # %2").arg(getName()).arg( consecutiveErrors));
   }

  }
  catch (IOException exa)
  {
   consecutiveErrors += 1;
   log->warn(tr("readLine from device '%1' failed, consecutive error # %2").arg(getName()).arg( consecutiveErrors));
 }
 catch (IndexOutOfBoundsException exb)
  {
   log->warn(tr("Bad message '%1' from device '%2'").arg(inPackage).arg(getName()));
  }
  if (consecutiveErrors > 0)
  { //a read error was encountered
   if (consecutiveErrors < 25)
   { //pause thread to give time for reconnection
    try
    {
     //Thread.sleep(200);
     SleeperThread::msleep(200);
    }
    catch (InterruptedException ex){}
   }
   else
   {
    keepReading = false;
    log->error(tr("readLine failure limit exceeded, ending thread run loop for device '%1").arg(getName()));
   }
  }
// } while (keepReading);	//	'til we tell it to stop
// log->debug(tr("Ending thread run loop for device '%1'").arg(getName()));
// closeThrottles();

}
#endif
/*public*/ void DeviceServer::closeThrottles() {
    stopEKG();
    if (throttleController != NULL) {
        throttleController->shutdownThrottle();
        throttleController->removeThrottleControllerListener((ThrottleControllerListener*)this);
        throttleController->removeControllerListener((ControllerInterface*)this);
    }
    if (secondThrottleController != NULL) {
        secondThrottleController->shutdownThrottle();
        secondThrottleController->removeThrottleControllerListener((ThrottleControllerListener*)this);
        secondThrottleController->removeControllerListener((ControllerInterface*)this);
    }
    if (multiThrottles != NULL) {
        foreach (QChar key, multiThrottles->keys()) {
            if (log->isDebugEnabled()) {
                log->debug("Closing throttles for key: " + QString(key) + " for device: " + getName());
            }
            multiThrottles->value(key)->dispose();
        }
    }
    if (multiThrottles != NULL) {
        multiThrottles->clear();
        multiThrottles = NULL;
    }
    throttleController = NULL;
    secondThrottleController = NULL;
    if (trackPower != NULL) {
        trackPower->removeControllerListener((ControllerInterface*)this);
    }
    if (turnoutC != NULL) {
        turnoutC->removeControllerListener((ControllerInterface*)this);
    }
    if (routeC != NULL) {
        routeC->removeControllerListener((ControllerInterface*)this);
    }
    if (consistC != NULL) {
        consistC->removeControllerListener((ControllerInterface*)this);
    }

    closeSocket();
#if 0
    for (int i = 0; i < listeners->size(); i++) {
        DeviceListener* l = listeners->at(i);
        l->notifyDeviceDisconnected(this);

    }
#endif
    emit deviceDisconnected(new WiDevice(deviceName, device->peerAddress().toString(), deviceUDID, this));
    emit finished();
}

/*public*/ void DeviceServer::closeSocket() {

    keepReading = false;
    try {
        if (!device->isOpen()) {
            if (log->isDebugEnabled()) {
                log->debug(tr("device socket ") + getName() + device->peerAddress().toString() + " already closed.");
            }
        } else {
            device->close();
            if (log->isDebugEnabled()) {
                log->debug(tr("device socket ") + getName() + device->peerAddress().toString() + " closed.");
            }
        }
    } catch (IOException e) {
        if (log->isDebugEnabled()) {
            log->error(tr("device socket ") + getName() + device->peerAddress().toString() + " close failed with IOException.");
        }
    }
}

/*public*/ void DeviceServer::startEKG() {
    isUsingHeartbeat = true;
    stopEKGCount = 0;
    ekg = new QTimer();
#if 0 // Done, see below:
    TimerTask task = new TimerTask() {
        @Override
        /*public*/ void run() {  //  Drops on second pass
            if (!heartbeat) {
                stopEKGCount++;
                //  Send eStop to each throttle
                if (log->isDebugEnabled()) {
                    log->debug("Lost signal from: " + getName() + ", sending eStop");
                }
                if (throttleController != NULL) {
                    throttleController->sort("X");
                }
                if (secondThrottleController != NULL) {
                    secondThrottleController->sort("X");
                }
                if (multiThrottles != NULL) {
                    for (char key : multiThrottles.keySet()) {
                        if (log->isDebugEnabled()) {
                            log->debug("Sending eStop to MT key: " + key);
                        }
                        multiThrottles.get(key).eStop();
                    }

                }
                if (stopEKGCount > 2) {
                    closeThrottles();
                }
            }
            heartbeat = false;
        }

    };
#endif
//    TimerTask1* task = new TimerTask1(this);

    //ekg->scheduleAtFixedRate(task, pulseInterval * 900L, pulseInterval * 900L);
    connect(ekg, SIGNAL(timeout()), this, SLOT(timeout()));
    ekg->start(900);
}

void DeviceServer::timeout()
{
 ekg->start(900);

}


TimerTask1::TimerTask1(DeviceServer *deviceServer)
{
 this->deviceServer = deviceServer;
}

void TimerTask1::run()
{
 //  Drops on second pass
 if (!deviceServer->heartbeat)
 {
     deviceServer->stopEKGCount++;
     //  Send eStop to each throttle
     if (deviceServer->log->isDebugEnabled()) {
         deviceServer->log->debug("Lost signal from: " + deviceServer->getName() + ", sending eStop");
     }
     if (deviceServer->throttleController != NULL) {
         deviceServer->throttleController->sort("X");
     }
     if (deviceServer->secondThrottleController != NULL) {
         deviceServer->secondThrottleController->sort("X");
     }
     if (deviceServer->multiThrottles != NULL) {
         foreach (QChar key, deviceServer->multiThrottles->keys()) {
             if (deviceServer->log->isDebugEnabled()) {
                 deviceServer->log->debug("Sending eStop to MT key: " + QString(key));
             }
             deviceServer->multiThrottles->value(key)->eStop();
         }

     }
     if (deviceServer->stopEKGCount > 2) {
         deviceServer->closeThrottles();
     }
 }
 deviceServer->heartbeat = false;
}

/*public*/ void DeviceServer::stopEKG() {
    isUsingHeartbeat = false;
    if (ekg != NULL) {
        //ekg->cancel();
     ekg->stop();
    }

}

/*private*/ void DeviceServer::addControllers()
{
#if 1
    if (isTrackPowerAllowed) {
        trackPower = WiThrottleManager::trackPowerControllerInstance();
        if (trackPower->isValid) {
            if (log->isDebugEnabled()) {
                log->debug("Track Power valid.");
            }
            trackPower->addControllerListener((ControllerInterface*)this);
            trackPower->sendCurrentState();
        }
    }
    if (isTurnoutAllowed) {
        turnoutC = WiThrottleManager::turnoutControllerInstance();
        if (turnoutC->verifyCreation()) {
            if (log->isDebugEnabled()) {
                log->debug("Turnout Controller valid.");
            }
            turnoutC->addControllerListener((ControllerInterface*)this);
            turnoutC->sendTitles();
            turnoutC->sendList();
        }
    }
    if (isRouteAllowed) {
        routeC = WiThrottleManager::routeControllerInstance();
        if (routeC->verifyCreation()) {
            if (log->isDebugEnabled()) {
                log->debug("Route Controller valid.");
            }
            routeC->addControllerListener((ControllerInterface*)this);
            routeC->sendTitles();
            routeC->sendList();
        }
    }

    //  Consists can be selected regardless of pref, as long as there is a ConsistManager.
    consistC = WiThrottleManager::consistControllerInstance();
    if (consistC->verifyCreation()) {
        if (log->isDebugEnabled()) {
            log->debug("Consist Controller valid.");
        }
        isConsistAllowed = WiThrottleManager::withrottlePreferencesInstance()->isAllowConsist();
        consistC->addControllerListener((ControllerInterface*)this);
        consistC->setIsConsistAllowed(isConsistAllowed);
        consistC->sendConsistListType();

        consistC->sendAllConsistData();
    }
#endif
}

/*public*/ QString DeviceServer::getUDID() {
    return deviceUDID;
}

/*public*/ QString DeviceServer::getName() {
    return deviceName;
}

/*public*/ QString DeviceServer::getCurrentAddressString() {
    QString s;// = new StringBuilder("");
#if 1
    if (throttleController != NULL) {
        s.append(throttleController->getCurrentAddressString());
        s.append(" ");
    }
    if (secondThrottleController != NULL) {
        s.append(secondThrottleController->getCurrentAddressString());
        s.append(" ");
    }
    if (multiThrottles != NULL) {
        foreach (MultiThrottle* mt, multiThrottles->values()) {
            if (mt->throttles != NULL) {
                foreach (MultiThrottleController* mtc,  mt->throttles->values()) {
                    s.append(mtc->getCurrentAddressString());
                    s.append(" ");
                }
            }
        }
    }
#endif
    return s;
}

/*public*/ /*static*/ QString DeviceServer::getWiTVersion() {
    return versionNumber;
}

/*public*/ /*static*/ QString DeviceServer::getWebServerPort() {
    return QString::number(WebServerPreferences::getDefault()->getPort());
}

/**
 * Called by various Controllers to send a string message to a connected
 * device. Appends a newline to the end.
 *
 * @param message The string to send.
 */
//@Override
/*public*/ void DeviceServer::sendPacketToDevice(QString message) {
    if (message == NULL) {
        return; //  Do not send a NULL.
    }
#if 1
    //out->println(message + newLine);
    //*out << message + newLine;
    emit sendPacket( message);
    if (log->isDebugEnabled()) {
        QString s = message + "                    "; //pad output so messages form columns
        s = s.mid(0, qMax(message.length(), 20));
        log->debug("Sent: " + s + "  to  " + getName() + device->peerAddress().toString());
    }
#endif
}

/**
 * Add a DeviceListener
 *
 */
/*public*/ void DeviceServer::addDeviceListener(DeviceListener* l) {
#if 0
    if (listeners == NULL) {
        listeners = new QVector<DeviceListener*>(2);
    }
    if (!listeners->contains(l)) {
        listeners->append(l);
    }
#else
 connect(this, SIGNAL(deviceConnected(DeviceServer*)), l, SLOT(notifyDeviceConnected(DeviceServer*)));
 connect(this, SIGNAL(deviceDisconnected(DeviceServer*)), l, SLOT(notifyDeviceDisconnected(DeviceServer*)));
#endif
}

/**
 * Remove a DeviceListener
 *
 */
/*public*/ void DeviceServer::removeDeviceListener(DeviceListener* l) {
#if 0
    if (listeners == NULL) {
        return;
    }
    if (listeners->contains(l)) {
        listeners->removeOne(l);
    }
#else

 disconnect(this, SIGNAL(deviceConnected(DeviceServer*)), l, SLOT(notifyDeviceConnected(DeviceServer*)));
 disconnect(this, SIGNAL(deviceDisconnected(DeviceServer*)), l, SLOT(notifyDeviceDisconnected(DeviceServer*)));
}

//@Override
/*public*/ void DeviceServer::notifyControllerAddressFound(ThrottleController* TC) {
#if 0
    for (int i = 0; i < listeners->size(); i++) {
        DeviceListener* l = listeners->at(i);
        l->notifyDeviceAddressChanged(this);
        if (log->isDebugEnabled()) {
            log->debug(tr("Notify DeviceListener: ") + l->metaObject()->className() + " address: " + TC->getCurrentAddressString());
        }
    }
#else
 emit notifyControllerAddressFound(TC);
#endif

}

//@Override
/*public*/ void DeviceServer::notifyControllerAddressReleased(ThrottleController* TC) {

#if 0
    for (int i = 0; i < listeners->size(); i++) {
        DeviceListener* l = listeners->at(i);
        l->notifyDeviceAddressChanged(this);
        if (log->isDebugEnabled()) {
            log->debug(tr("Notify DeviceListener: ") + l->metaObject()->className() + " address: " + TC->getCurrentAddressString());
        }
    }
#else
 emit controllerAddressReleased(TC);
#endif

}
#endif

/**
 * Format a package to be sent to the device for roster list selections.
 *
 * @return String containing a formatted list of some of each RosterEntry's
 *         info. Include a header with the length of the string to be
 *         received.
 */
/*public*/ QString DeviceServer::sendRoster() {
    QList<RosterEntry*> rosterList;
    rosterList = Roster::getDefault()->getEntriesInGroup(((UserInterface*)manager)->getSelectedRosterGroup());
    QString rosterString;// = new StringBuilder(rosterList.size() * 25);
    foreach (RosterEntry* entry, rosterList) {
        QString entryInfo;// = new StringBuilder(entry.getId()); //  Start with name
        entryInfo.append("}|{");
        entryInfo.append(entry->getDccAddress());
        if (entry->isLongAddress()) { //  Append length value
            entryInfo.append("}|{L");
        } else {
            entryInfo.append("}|{S");
        }

        rosterString.append("]\\[");  //  Put this info in as an item
        rosterString.append(entryInfo);

    }
//    rosterString.trimToSize();

    return ("RL" + rosterList.size() + rosterString);
}


/*public*/ ServerRxHandler::ServerRxHandler(QString newRemoteAddress, QWebSocket* newSocket, int connectionNbr, QObject *parent) :
  QThread(parent)
{
 clientSocket = newSocket;
 //llnmon = new LlnMon();
 //setDaemon(true);
 setPriority(QThread::HighestPriority);
 remoteAddress = newRemoteAddress;
 setObjectName("ServerRxHandler:" + QString(" #%1").arg(connectionNbr));
 bIsInterrupted = false;
 log = new Logger(objectName());
 log->setDebugEnabled(true);
 //lastSentMessage = NULL;
 log->debug(tr("started, connected to ")+ newSocket->peerName() + " " + newRemoteAddress);



 start();

}

//@SuppressWarnings("NULL")
/*public*/ void ServerRxHandler::run()
{

//    try {
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(on_clientSocket_disconnected()));
 //inStream = new QDataStream(clientSocket);

 // pass messages received off of LocoNet to the Tx handler
 //connect(tc, SIGNAL(messageProcessed(QString)),txHandler, SLOT(sendMessage(QString)));

 // pass the message received by the Rx handler to the Tx handler so it can check for ACK
// connect(this, SIGNAL(lastMessageSent(QString)),
//         txHandler, SLOT(on_lastMessage(QString)));
 connect(clientSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(on_textMessageReceived(QString)));
 connect(clientSocket, SIGNAL(disconnected()), this, SLOT(quit()));

 exec();

 //disconnect(tc, SIGNAL(messageProcessed(QString)), this, SLOT(message(QString)));
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

 //DeviceServer::getInstance()->removeClient(this);
 log->info("ServerRxHandler: Exiting");
}

#if 0
void ServerRxHandler::on_readyRead()
{

 while (!isInterrupted()  && clientSocket->isValid() /*&& clientSocket->isOpen()*/ )
 {
  if(log->isDebugEnabled() && clientSocket->bytesAvailable() > 0)
   log->debug(tr("Socket has %1 bytes ready").arg(clientSocket->bytesAvailable()));
  //if(clientSocket->bytesAvailable() > 0)
  {

   QByteArray ba = clientSocket->readLine();
   qDebug() << ba;
   inString = QString(ba);
   if (inString.isEmpty())
   {
//    log->debug("ServerRxHandler: Remote Connection Closed");
//    //interrupt();
//    return;
    return;
   }
   else
   {
    log->debug("ServerRxHandler: Received: " + inString);
    emit passMessage(inString);
   }
  }
 }
}
#endif

void  ServerRxHandler::on_textMessageReceived(QString msg)
{
 //qDebug() << "Rcv: " << msg;
 emit passMessage(msg);
}

/*public*/ void ServerRxHandler::close()
{
 try {
     clientSocket->close();
 } catch (IOException ex1) {
     log->error("close, which closing clientSocket", ex1);
 }
}
void ServerRxHandler::displayError(QAbstractSocket::SocketError socketError)
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

bool ServerRxHandler::isInterrupted() { return bIsInterrupted;}

/*public*/ void ServerRxHandler::message(QString msg)
{
// /*synchronized (msgQueue)*/
// {
////  msgQueue.append(msg);
////  //msgQueue.notify();
////  ((ServerTxHandler*)txThread)->queueCondition->wakeOne();
// }
 emit passMessage(msg);
}
void ServerRxHandler::on_clientSocket_disconnected()
{
 log->warn("client socket disconnected");
 bIsInterrupted = true;
 emit disconnected(remoteAddress);
}

//class ServerTxHandler implements Runnable {

//    LocoNetMessage msg;
//    StringBuffer outBuf;
//    Thread parentThread;

ServerTxHandler::ServerTxHandler(QString newRemoteAddress, QWebSocket* newSocket, int connectionNbr)
{
 //parentThread = creator;
 remoteAddress = newRemoteAddress;
 clientSocket = newSocket;
 setObjectName(QString("ServerTxHandler#%1").arg(connectionNbr));
 log = new Logger(objectName());
 //outStream = new QTextStream(clientSocket);
 //outStream->setVersion(QDataStream::Qt_4_0);
 //queueCondition = new QWaitCondition();
 //mutex = new QMutex();
 //msgQueue = QLinkedList<QString>();
 connect(DeviceServer::instance(), SIGNAL(sendPacket(QString)), this, SLOT(sendMessage(QString)));
 lastSentMessage = "";

 start();

}

/*public*/ void ServerTxHandler::run()
{

 exec();
 // Interrupt the Parent to let it know we are exiting for some reason
 //parentThread.interrupt();
// parentThread->exit();

// parentThread = NULL;
 log->info("ServerTxHandler: Exiting");
}

void ServerTxHandler::sendMessage(QString msg)
{
//    try {
// queueCondition->wait(mutex);
 if(/*!clientSocket->isOpen() ||*/ !clientSocket->isValid())
  exit();

// outBuf = QString("VERSION JMRI Server ");
// outBuf.append(Version::name());
// outBuf.append("\r\n");
// //outStream.write(outBuf.toString().getBytes());
// *outStream << outBuf;

 //if (clientSocket->isOpen())
 {

  if (msg != NULL)
  {
#if 0
   outBuf.clear();
   outBuf.append("RECEIVE ");
   outBuf.append(msg);
   //log->debug("ServerTxHandler: Send: " + outBuf);
   outBuf.append("\r\n");
   // See if we are waiting for an echo of a sent message
   // and if it is append the Ack to the client
   if ((lastSentMessage != "") && lastSentMessage == (msg))
   {
    lastSentMessage = "";
    outBuf.append("SENT OK\r\n");
   }
//   *outStream << outBuf;
//   outStream->flush();
#endif
   clientSocket->sendTextMessage(msg);

  }
 }
 outBuf = "";

}
void ServerTxHandler::on_lastMessage(QString msg)
{
 lastSentMessage = msg;
}

/*protected*/ void DeviceServer::addClient(ServerRxHandler* handler)
{
    /*synchronized (clients) */
 {
  clients->append(handler);
 }
 //updateClientStateListener();
}


/*private*/ /*final*/ /*static*/ Logger* DeviceServer::log = LoggerFactory::getLogger("DeviceServer");
