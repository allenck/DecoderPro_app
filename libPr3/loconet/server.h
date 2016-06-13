#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QLinkedList>
#include "logger.h"
#include <QTcpServer>
#include "quietshutdowntask.h"

class ZeroConfService;
class QuietShutDownTask;
class ServerListner;
//class QTcpServer;
class ClientRxHandler;

class Server : public QTcpServer
{
 Q_OBJECT
public:
 explicit Server(QObject *parent = 0);
 /*public*/ void setStateListner(ServerListner* l);
 /*public*/ static /*synchronized*/ Server* getInstance();
 /*public*/ bool getAutoStart() ;
 /*public*/ void setAutoStart(bool start);
 /*public*/ int getPortNumber() ;
 /*public*/ void setPortNumber(int port);
 /*public*/ bool isEnabled();
 /*public*/ bool isSettingChanged();
 /*public*/ void enable();
 /*public*/ void disable();
 /*public*/ void updateServerStateListener();
 /*public*/ void updateClientStateListener();
 /*public*/ void saveSettings();
 /*public*/ int getClientCount();

signals:
 void serverStateChanged(Server*);
 void error(QAbstractSocket::SocketError);
 void clientStateChanged(Server*, int );

public slots:
 void on_newConnection();

private:
 static Server* self;
 QLinkedList<ClientRxHandler*>* clients;
 QThread* socketListener;
 QTcpServer* serverSocket;
 bool settingsLoaded;// = false;
 ServerListner* stateListner;
 bool settingsChanged;// = false;
 QuietShutDownTask* shutDownTask;
 ZeroConfService* service;// = null;
 static /*final*/ QString AUTO_START_KEY;// = "AutoStart";
 static /*final*/ QString PORT_NUMBER_KEY;// = "PortNumber";
 static /*final*/ QString SETTINGS_FILE_NAME;// = "LocoNetOverTcpSettings.ini";
 /*private*/ bool autoStart;
 /*private*/ void loadSettings();
 int connectionNbr;

 Logger* log;
 /*private*/ int portNumber;// = 1234;
 bool bIsEnabled;

protected:
 /*protected*/ void addClient(ClientRxHandler* handler) ;
 /*protected*/ void removeClient(ClientRxHandler* handler);
 //void incomingConnection(int socketDescriptor);

 friend class ClientRxHandler;
};
class ServerQuietShutDownTask : public QuietShutDownTask
{
 Q_OBJECT
 Server* server;
public:
 ServerQuietShutDownTask(QString name, Server* server) : QuietShutDownTask(name) { this->server = server;}
 /*public*/ bool execute()
 {
  Server::getInstance()->disable();
  return true;
 }

};

#endif // SERVER_H
