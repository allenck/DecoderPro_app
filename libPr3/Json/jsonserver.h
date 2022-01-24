#ifndef JSONSERVER_H
#define JSONSERVER_H
#include <QTcpServer>
#include "jsonqt.h"
#include "quietshutdowntask.h"
#include "exceptions.h"
#include <qzeroconf.h>

class ZeroConfService;
class JSShutDownTask;
class JsonClientTxHandler;
class JsonClientRxHandler;
class JsonServerPreferences;
class JsonServer : public QTcpServer
{
 Q_OBJECT
public:
 JsonServer(QObject* parent = 0);
 JsonServer(int port, int timeout, QObject* parent = 0);
 /*public*/ static JsonServer* getDefault();
 /*public*/ void start();
 /*public*/ void stop();
 /*public*/ void handleClient(QTextStream* inStream, QTextStream* outStream) /*throw (IOException)*/;
 /*public*/ void stopClient(QTextStream* inStream, QTextStream* outStream) /*throw (IOException)*/;

public slots:
 void on_newConnection();
 void servicePublished();
 void error(QZeroConf::error_t);

private:
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger("JsonServer");
 /*private*/ ObjectMapper mapper;
 void common();
 JSShutDownTask* shutDownTask;
 JsonServerPreferences* settings;
 int port;
 int timeout;
 QLinkedList<JsonClientRxHandler*>* clients;
 QThread* socketListener;
 QTcpServer* serverSocket;
 int connectionNbr;
 QZeroConf* zeroConf;
 QString buildName(void);
 ZeroConfService* service;

protected:
 /*protected*/ void advertise();
 /*protected*/ void advertise(QString type);
 /*protected*/ void advertise(QString type, QMap<QString, QVariant> properties);
 /*protected*/ void removeClient(JsonClientRxHandler* handler);
 /*protected*/ void addClient(JsonClientRxHandler* handler);

friend class JSShutDownTask;
friend class JsonClientRxHandler;
};

class JSShutDownTask : public QuietShutDownTask
{
 Q_OBJECT
 JsonServer* js;

public:
 JSShutDownTask(QString title, JsonServer* js);
 /*public*/ bool execute();
};

class JsonClientRxHandler : public QThread
{
 Q_OBJECT
public:
 /*public*/ JsonClientRxHandler(QString newRemoteAddress, QTcpSocket* newSocket, int connectionNbr, QObject *parent = 0);
 /*public*/ void run();

signals:
 void passMessage(QString msg);

public slots:
 /*public*/ void message(QString msg);
 void displayError(QAbstractSocket::SocketError socketError);
 /*public*/ void close();
 void on_clientSocket_disconnected();
 void on_readyRead();


private:
 QTcpSocket* clientSocket;
 QString remoteAddress;
 QTextStream* inStream;
 Logger* log;
 bool bIsInterrupted;
 JsonClientTxHandler* txHandler;
 QString inString;
 bool isInterrupted();

};

class JsonClientTxHandler : public Runnable
{
 Q_OBJECT
 QString msg;
 QString outBuf;
 //ClientRxHandler* parentThread;
 QTcpSocket* clientSocket;
 QString remoteAddress;
 Logger* log;
 QByteArray block;
 QTextStream* outStream;
 //QMutex* mutex;
 //QLinkedList<LocoNetMessage*> msgQueue;

public:
 JsonClientTxHandler(QString newRemoteAddress, QTcpSocket* newSocket, int connectionNbr);
 /*public*/ void run();
 //QWaitCondition* queueCondition;

public slots:
 void sendMessage(QString msg);
};
#endif // JSONSERVER_H
