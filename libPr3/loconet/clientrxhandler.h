#ifndef CLIENTRXHANDLER_H
#define CLIENTRXHANDLER_H

#include <QObject>
#include <QLinkedList>
#include "runnable.h"
#include "logger.h"
#include <QAbstractSocket>

class ClientTxHandler;
class LlnMon;
class QWaitCondition;
class QReadWriteLock;
class LnTrafficController;
class LocoNetMessage;
class QTcpSocket;
class ClientRxHandler : public QThread
{
 Q_OBJECT
public:
 //explicit ClientRxHandler(QObject *parent = 0);
 /*public*/ ClientRxHandler(QString newRemoteAddress, QTcpSocket* newSocket, LnTrafficController* tc, int connectionNbr, QObject *parent = 0);
 /*public*/ void run();

signals:
 void passMessage(LocoNetMessage* msg);
 void lastMessageSent(LocoNetMessage* msg);

public slots:
 /*public*/ void message(LocoNetMessage* msg);
 void displayError(QAbstractSocket::SocketError socketError);
 /*public*/ void close();
 void on_clientSocket_disconnected();
 void on_readyRead();


private:
 QTcpSocket* clientSocket;
 QString remoteAddress;
 QTextStream* inStream;
 //QThread* txThread;
 QString inString;
 LnTrafficController* tc;
 bool bIsInterrupted;
 bool isInterrupted();
 Logger* log;
 LlnMon* llnmon;
 LocoNetMessage* lastSentMessage;
 ClientTxHandler* txHandler;


 friend class ClientTxHandler;
};
class ClientTxHandler : public Runnable
{
 Q_OBJECT
 LocoNetMessage* msg;
 QString outBuf;
 //ClientRxHandler* parentThread;
 QTcpSocket* clientSocket;
 QString remoteAddress;
 Logger* log;
 QByteArray block;
 QTextStream* outStream;
 //QMutex* mutex;
 //QLinkedList<LocoNetMessage*> msgQueue;
 LocoNetMessage* lastSentMessage;

public:
 ClientTxHandler(QString newRemoteAddress, QTcpSocket* newSocket, int connectionNbr);
 /*public*/ void run();
 //QWaitCondition* queueCondition;

public slots:
 void sendMessage(LocoNetMessage*);
 void on_lastMessage(LocoNetMessage* msg);
};

#endif // CLIENTRXHANDLER_H
