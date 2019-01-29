#ifndef LNTCPSERVER_H
#define LNTCPSERVER_H

#include <QObject>
#include <QLinkedList>
#include "logger.h"
#include <QTcpServer>
#include "quietshutdowntask.h"
#include "propertychangeevent.h"
//#include <QtZeroConf/qzeroconf.h>
#include "zeroconfservice.h"


class LnTcpPreferences;
class QZeroConf;
class QuietShutDownTask;
class ServerListner;
//class QTcpServer;
class ClientRxHandler;

class LnTcpServer : public QTcpServer
{
 Q_OBJECT
public:
 explicit LnTcpServer(QObject *parent = 0);
 QT_DEPRECATED
 QT_DEPRECATED /*public*/ void setStateListner(ServerListner* l);
 QT_DEPRECATED /*public*/ static /*synchronized*/ LnTcpServer* getInstance();
 QT_DEPRECATED /*public*/ bool getAutoStart() ;
 QT_DEPRECATED /*public*/ void setAutoStart(bool start);
 QT_DEPRECATED /*public*/ int getPortNumber() ;
 QT_DEPRECATED /*public*/ void setPortNumber(int port);
 /*public*/ bool isEnabled();
 /*public*/ bool isSettingChanged();
 /*public*/ void enable();
 /*public*/ void disable();
 /*public*/ void updateServerStateListener();
 /*public*/ void updateClientStateListener();
 // /*public*/ void saveSettings();
 /*public*/ int getClientCount();
 /*public*/ int getPort();
 /*public*/ static /*synchronized*/ LnTcpServer* getDefault();


signals:
 void serverStateChanged(LnTcpServer*);
 void error(QAbstractSocket::SocketError);
 void clientStateChanged(LnTcpServer*, int );

public slots:
 void on_newConnection();
 void propertyChange(PropertyChangeEvent*);
 void servicePublished();
 void error(QZeroConf::error_t);

private:
 static LnTcpServer* self;
 QLinkedList<ClientRxHandler*>* clients;
 QThread* socketListener;
 QTcpServer* serverSocket;
 bool settingsLoaded;// = false;
 ServerListner* stateListner;
 bool settingsChanged;// = false;
 QuietShutDownTask* shutDownTask;
 //QZeroConf* service;// = null;
 ZeroConfService* service = nullptr;
 static /*final*/ QString AUTO_START_KEY;// = "AutoStart";
 static /*final*/ QString PORT_NUMBER_KEY;// = "PortNumber";
 static /*final*/ QString SETTINGS_FILE_NAME;// = "LocoNetOverTcpSettings.ini";
 /*private*/ bool autoStart;
 // /*private*/ void loadSettings();
 int connectionNbr;
 LnTcpPreferences* pm;

 Logger* log;
 /*private*/ int portNumber;// = 1234;
 bool bIsEnabled;
 QString buildName(void);

protected:
 /*protected*/ void addClient(ClientRxHandler* handler) ;
 /*protected*/ void removeClient(ClientRxHandler* handler);
 //void incomingConnection(int socketDescriptor);

 friend class ClientRxHandler;
};

class ServerQuietShutDownTask : public QuietShutDownTask
{
 Q_OBJECT
 LnTcpServer* server;
public:
 ServerQuietShutDownTask(QString name, LnTcpServer* server) : QuietShutDownTask(name) { this->server = server;}
 /*public*/ bool execute()
 {
  LnTcpServer::getInstance()->disable();
  return true;
 }
};

#endif // LNTCPSERVER_H
