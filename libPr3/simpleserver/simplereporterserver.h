#ifndef SIMPLEREPORTERSERVER_H
#define SIMPLEREPORTERSERVER_H
#include "abstractreporterserver.h"
#include "exceptions.h"
class Logger;
class QTcpSocket;
class SimpleReporterServer : public AbstractReporterServer
{
 Q_OBJECT
public:
 SimpleReporterServer(QTcpSocket* connection, QObject* parent = nullptr);
 /*public*/ void sendReport(QString reporterName, QVariant r) /*throw (IOException)*/;
 /*public*/ void sendErrorStatus(QString reporterName) /*throw (IOException)*/;
 /*public*/ void parseStatus(QString statusString) throw (JmriException, IOException);

private:
 static Logger* log;
 /*private*/ QDataStream* output;
 /*private*/ QTcpSocket* connection;
 /*private*/ void sendMessage(QString message) /*throw (IOException)*/;

};

#endif // SIMPLEREPORTERSERVER_H
