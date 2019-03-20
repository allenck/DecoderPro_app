#ifndef SIMPLESERVER_H
#define SIMPLESERVER_H
#include "jmriserver.h"

class SimpleTurnoutServer;
class SimpleLightServer;
class SimpleSensorServer;
class SimpleSignalHeadServer;
class SimpleReporterServer;
class SimplePowerServer;
class SimpleOperationsServer;
class JMRIClientTxHandler;
class JMRIClientRxHandler;
class SimpleServer : public JmriServer
{
 Q_OBJECT
public:
 SimpleServer(QObject *parent = nullptr);
 QT_DEPRECATED /*public*/ static JmriServer* instance();
 /*public*/ SimpleServer(int port, QObject *parent = nullptr);
 /*public*/ void stop();
 void start();


public slots:
 void on_newConnection();



private:
 static Logger* log;
 void common(int port);
 QLinkedList<JMRIClientRxHandler*>* clients;
 int connectionNbr = 0;
 QTcpServer* serverSocket;


protected:
 /*protected*/ void advertise();
 /*protected*/ void addClient(JMRIClientRxHandler* handler);
 /*protected*/ void removeClient(JMRIClientRxHandler* handler);

friend class JMRIClientRxHandler;
};

class JMRIClientRxHandler : public QThread
{
 Q_OBJECT
public:
 /*public*/ JMRIClientRxHandler(QString newRemoteAddress, QTcpSocket* newSocket, int connectionNbr, QObject *parent = 0);
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
 JMRIClientTxHandler* txHandler;
 QString inString;
 bool isInterrupted();
 SimplePowerServer* powerServer;// = new SimplePowerServer(inStream, outStream);
 SimpleTurnoutServer* turnoutServer;// = new SimpleTurnoutServer(inStream, outStream);
 SimpleLightServer* lightServer;// = new SimpleLightServer(inStream, outStream);
 SimpleSensorServer* sensorServer;// = new SimpleSensorServer(inStream, outStream);
 SimpleSignalHeadServer* signalHeadServer;// = new SimpleSignalHeadServer(inStream, outStream);
 SimpleReporterServer* reporterServer;// = new SimpleReporterServer(inStream, outStream);
 SimpleOperationsServer* operationsServer;// = new SimpleOperationsServer(inStream, outStream);
 void handleMessage(QString cmd);

};

class JMRIClientTxHandler : public Runnable
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
 JMRIClientTxHandler(QString newRemoteAddress, QTcpSocket* newSocket, int connectionNbr);
 /*public*/ void run();
 //QWaitCondition* queueCondition;

public slots:
 void sendMessage(QString msg);
};
#endif // SIMPLESERVER_H
