#ifndef SIMPLETURNOUTSERVER_H
#define SIMPLETURNOUTSERVER_H
#include "abstractturnoutserver.h"

class QTcpSocket;
class SimpleTurnoutServer : public AbstractTurnoutServer
{
 Q_OBJECT
public:
 SimpleTurnoutServer(QTcpSocket* clientSocket, QObject* parent = nullptr) ;
 /*public*/ SimpleTurnoutServer(QDataStream* inStream, QDataStream* outStream, QObject* parent= nullptr);
 /*public*/ void sendStatus(QString turnoutName, int Status) /*throw (IOException)*/;
 /*public*/ void sendErrorStatus(QString turnoutName) /*throw (IOException)*/ ;
 /*public*/ void parseStatus(QString statusString) throw (JmriException, IOException);
 /*private*/ void sendMessage(QString message) /*throw (IOException)*/;

private:
 static Logger* log;
 /*private*/ QDataStream* output;
 /*private*/ QTcpSocket* clientSocket;

protected:


};

#endif // SIMPLETURNOUTSERVER_H
