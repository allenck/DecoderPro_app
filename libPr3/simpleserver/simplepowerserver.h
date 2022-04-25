#ifndef SIMPLEPOWERSERVER_H
#define SIMPLEPOWERSERVER_H
#include "abstractpowerserver.h"
#include <QDataStream>
class QTcpSocket;
class SimplePowerServer : public AbstractPowerServer
{
public:
 /*public*/ SimplePowerServer(QDataStream *inStream, QDataStream *outStream, QObject* parent = nullptr) ;
 /*public*/ SimplePowerServer(QTcpSocket* cnctn);
 /*public*/ void sendStatus(int Status) /*throw (IOException)*/;
 /*public*/ void sendErrorStatus() /*throw (IOException)*/;
 /*public*/ void parseStatus(QString statusString) /*throw (JmriException)*/;
 /*public*/ void sendStatus(QString status) /*throw (IOException)*/;

 QObject* pself() override {return (QObject*)this;}

private:
 QTcpSocket* clientSocket;
 QDataStream* output = nullptr;
 static Logger* log;
 friend class SimpleServer;
};

#endif // SIMPLEPOWERSERVER_H
