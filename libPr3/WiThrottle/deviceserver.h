#ifndef DEVICESERVER_H
#define DEVICESERVER_H

#include <QWebSocket>
#include <QWebSocketServer>
#include "runnable.h"
#include "logger.h"

class DeviceServer;
class JsonClientHandler;
class ServerRxHandler;
class ServerTxHandler;
class QTimer;
class TrackPowerController;
class TurnoutController;
class RouteController;
class ConsistController;
class MultiThrottle;
class ThrottleController;
class CommandStation;
class DeviceManager;
class DeviceListener;
//class Logger;
struct WiDevice
{
 QString name;
 QString address;
 QString deviceUDID;
 DeviceServer* deviceServer;
 inline WiDevice(QString name, QString address, QString deviceUDID, DeviceServer* deviceServer)
 {
  this->name = name;
  this->address = address;
  this->deviceUDID = deviceUDID;
  this->deviceServer = deviceServer;
 }
 inline bool operator ==(WiDevice* dev) {return this->address == dev->address;}
};

class DeviceServer : public QWebSocketServer
{
 Q_OBJECT
public:
 //explicit DeviceServer(QObject *parent = 0);
 DeviceServer(int socket, DeviceManager* manager, QObject *parent = 0);
 /*public*/ static QString getWiTVersion();
 /*public*/ static QString getWebServerPort();
 /*public*/ void sendPacketToDevice(QString message);
 /*public*/ QString sendRoster();
 /*public*/ QString getUDID();
 /*public*/ QString getName();
 /*public*/ QString getCurrentAddressString();
 /*public*/ void closeThrottles();
 /*public*/ void closeSocket();
 /*public*/ void startEKG();
 /*public*/ void stopEKG();
 /*public*/ void addDeviceListener(DeviceListener* l);
 /*public*/ void removeDeviceListener(DeviceListener* l);
 /*public*/ void notifyControllerAddressFound(ThrottleController* TC);
 /*public*/ void notifyControllerAddressReleased(ThrottleController* TC);
 /*public*/ void run();
 /*public*/ static DeviceServer* instance();

signals:
 void controllerAddressFound(ThrottleController*);
 void controllerAddressReleased(ThrottleController*);
 void deviceConnected(WiDevice*);
 void deviceDisconnected(WiDevice*);
 void deviceInfoChanged(WiDevice*);
 void finished();
 void sendPacket(QString);
 void serverStateChanged(DeviceServer*);


public slots:
 void timeout();
 void on_newConnection();
 void handleMessage(QString message);
 void on_disconnected(QString);


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(DeviceServer.class.getName());
 //  Manually increment as features are added
 /*private*/ static /*final*/ QString versionNumber;// = "2.0";

 /*private*/ QTcpSocket* device;
 /*private*/ CommandStation* cmdStation;// = InstanceManager::getNullableDefault("CommandStation");
 QString newLine;// = System::getProperty("line.separator");
 /*BufferedReader*/QTextStream* in = NULL;
 /*PrintStream*/QTextStream* out = NULL;
 QVector<DeviceListener*>* listeners;
 QString deviceName;// = "Unknown";
 QString deviceUDID;

 ThrottleController* throttleController;
 ThrottleController* secondThrottleController;
 QHash<QChar, MultiThrottle*>* multiThrottles;
 /*private*/ bool keepReading;
 /*private*/ bool isUsingHeartbeat;// = false;
 /*private*/ bool heartbeat;// = true;
 /*private*/ int pulseInterval;// = 16; // seconds til disconnect
 /*private*/ QTimer* ekg;
 /*private*/ int stopEKGCount;

 /*private*/ TrackPowerController* trackPower = NULL;
 /*final*/ bool isTrackPowerAllowed;// = WiThrottleManager.withrottlePreferencesInstance().isAllowTrackPower();
 /*private*/ TurnoutController* turnoutC;// = NULL;
 /*private*/ RouteController* routeC;// = NULL;
 /*final*/ bool isTurnoutAllowed;// = WiThrottleManager.withrottlePreferencesInstance().isAllowTurnout();
 /*final*/ bool isRouteAllowed;// = WiThrottleManager.withrottlePreferencesInstance().isAllowRoute();
 /*private*/ ConsistController* consistC;// = NULL;
 /*private*/ bool isConsistAllowed;

 /*private*/ DeviceManager* manager;
 /*private*/ void addControllers();
 int socketPort;
 static DeviceServer* _instance;
 int connectionNbr;
 QString inPackage;
 int consecutiveErrors;
 QLinkedList<ServerRxHandler*>* clients;
 JsonClientHandler* handler;

protected:
 /*protected*/ void addClient(ServerRxHandler* handler);

 friend class TimerTask1;

};

class TimerTask1 : public QObject
{
 DeviceServer* deviceServer;
public:
 TimerTask1(DeviceServer* deviceServer);
 void run();

signals:

public slots:
};

class ServerRxHandler : public QThread
{
 Q_OBJECT
public:
 //explicit ClientRxHandler(QObject *parent = 0);
 /*public*/ ServerRxHandler(QString newRemoteAddress, QWebSocket* newSocket, int connectionNbr, QObject *parent = 0);
 /*public*/ void run();

signals:
 void passMessage(QString msg);
 void lastMessageSent(QString msg);
 void disconnected(QString);

public slots:
 /*public*/ void message(QString msg);
 void displayError(QAbstractSocket::SocketError socketError);
 /*public*/ void close();
 void on_clientSocket_disconnected();
 //void on_readyRead();
 void on_textMessageReceived(QString msg);

private:
 QWebSocket* clientSocket;
 QString remoteAddress;
 QDataStream* inStream;
 //QThread* txThread;
 QString inString;
 //LnTrafficController* tc;
 bool bIsInterrupted;
 bool isInterrupted();
 Logger* log;
 //LlnMon* llnmon;
 QString lastSentMessage;
 ServerTxHandler* txHandler;


 friend class ServerTxHandler;
};

class ServerTxHandler : public Runnable
{
 Q_OBJECT
 QString msg;
 QString outBuf;
 //ClientRxHandler* parentThread;
 QWebSocket* clientSocket;
 QString remoteAddress;
 Logger* log;
 QByteArray block;
 QTextStream* outStream;
 //QMutex* mutex;
 //QLinkedList<LocoNetMessage*> msgQueue;
 QString lastSentMessage;

public:
 ServerTxHandler(QString newRemoteAddress, QWebSocket* newSocket, int connectionNbr);
 /*public*/ void run();
 //QWaitCondition* queueCondition;

public slots:
 void sendMessage(QString);
 void on_lastMessage(QString msg);
};
#endif // DEVICESERVER_H
