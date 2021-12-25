#ifndef SIMPLELIGHTSERVER_H
#define SIMPLELIGHTSERVER_H
#include "abstractlightserver.h"

class QTcpSocket;
class SimpleLightServer : public AbstractLightServer
{
public:
 SimpleLightServer(QTcpSocket* connection, QObject* parent = nullptr);
 /*public*/ void sendStatus(QString lightName, int Status) /*throw (IOException)*/;
 /*public*/ void sendErrorStatus(QString lightName) /*throw (IOException)*/;
 /*public*/ void parseStatus(QString statusString) throw (JmriException, IOException);

private:
 /*private*/ QDataStream* output = nullptr;
 /*private*/ QTcpSocket* connection = nullptr;
 /*private*/ void sendMessage(QString message) /*throw (IOException)*/;
 static Logger* log;

};

#endif // SIMPLELIGHTSERVER_H
