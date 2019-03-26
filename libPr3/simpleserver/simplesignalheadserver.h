#ifndef SIMPLESIGNALHEADSERVER_H
#define SIMPLESIGNALHEADSERVER_H
#include "abstractsignalheadserver.h"

class SimpleSignalHeadServer : public AbstractSignalHeadServer
{
public:
 SimpleSignalHeadServer(QTcpSocket* connection, QObject* parent = nullptr);
 /*public*/ void sendStatus(QString signalHeadName, int Status) throw (IOException);
 /*public*/ void sendErrorStatus(QString signalHeadName) throw (IOException);
 /*public*/ void parseStatus(QString statusString) throw (JmriException, IOException);

private:
 /*private*/ QDataStream* output;
 /*private*/ QTcpSocket* connection;
 /*private*/ void sendMessage(QString message) throw (IOException);

};

#endif // SIMPLESIGNALHEADSERVER_H
