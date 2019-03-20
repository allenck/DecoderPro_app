#ifndef JMRISERVER_H
#define JMRISERVER_H

#include <QObject>
#include "runnable.h"
#include "logger.h"
#include <QTcpServer>

class ZeroConfService;
class ShutDownTask;
class QTcpSocket;
class JmriServer : public QTcpServer
{
 Q_OBJECT
public:
 explicit JmriServer(QObject *parent = 0);
 /*public*/ /*synchronized*/ static JmriServer* instance();
 /*public*/ JmriServer(int port, QObject *parent);
 /*public*/ JmriServer(int port, int timeout, QObject* parent);
 /*public*/ virtual void start();
 /*public*/ virtual void stop();

signals:

public slots:

private:
 // /*private*/ Thread listenThread = NULL;
 /*private*/ static JmriServer* _instance;// = NULL;
 void common(int port, int timeout);


protected:
 /*protected*/ int portNo = 3000; // Port to listen to for new clients.
 /*protected*/ int timeout = 0; // Timeout in milliseconds (0 = no timeout).
 /*protected*/ QTcpSocket* connectSocket;
 /*protected*/ ZeroConfService* service = NULL;
 /*protected*/ ShutDownTask* shutDownTask = NULL;
// /*protected*/ ArrayList<ClientListener> connectedClientThreads = new ArrayList<ClientListener>();
 /*protected*/ void advertise();
 /*protected*/ void advertise(QString type);
 /*protected*/ void advertise(QString type, QMap<QString, QVariant> properties);

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
