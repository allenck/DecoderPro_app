#ifndef SIMPLESENSORSERVER_H
#define SIMPLESENSORSERVER_H
#include "abstractsensorserver.h"

class QTcpSocket;
class JmriConnection;
class Logger;
class SimpleSensorServer : public AbstractSensorServer
{
 Q_OBJECT
public:
 /*public*/ SimpleSensorServer(QTcpSocket* clientSocket, QObject* parent = nullptr);
 /*public*/ SimpleSensorServer(QDataStream* inStream, QDataStream* outStream, QObject* parent= nullptr);
 /*public*/ void sendStatus(QString sensorName, int Status) /*throw (IOException)*/;
 /*public*/ void sendErrorStatus(QString sensorName) /*throw (IOException)*/;
 /*public*/ void parseStatus(QString statusString) /*throw (JmriException, IOException)*/;


private:
 static Logger* log;
 QTcpSocket* clientSocket;
 QDataStream* output;
 /*private*/ void sendMessage(QString message) /*throw (IOException)*/;


protected:
};

#endif // SIMPLESENSORSERVER_H
