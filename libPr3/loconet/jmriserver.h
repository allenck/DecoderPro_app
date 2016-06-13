#ifndef JMRISERVER_H
#define JMRISERVER_H

#include <QObject>
#include "runnable.h"
#include "logger.h"

class QTcpSocket;
class JmriServer : public QObject
{
 Q_OBJECT
public:
 explicit JmriServer(QObject *parent = 0);

signals:

public slots:

};
#if 0
// Internal class to handle a client
/*protected*/ class ClientListener :public  Runnable
{
 Q_OBJECT
    QTcpSocket* clientSocket = null;
    QDataStream* inStream = null;
    QDataStream* outStream = null;
    QThread* clientThread = null;
    Logger* log;
 public:
    /*public*/ ClientListener(QTcpSocket* socket);
    /*public*/ void start();
    /*public*/ void run();
}; // end of ClientListener class.
#endif

#endif // JMRISERVER_H
