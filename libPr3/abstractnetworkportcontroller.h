#ifndef ABSTRACTNETWORKPORTCONTROLLER_H
#define ABSTRACTNETWORKPORTCONTROLLER_H
#include "abstractportcontroller.h"
#include <QThread>
#include <QAbstractSocket>
#include "libPr3_global.h"

class QMessageBox;
class QTimer;
class QTcpSocket;
class LIBPR3SHARED_EXPORT AbstractNetworkPortController : public AbstractPortController
{
 Q_OBJECT
public:
 //explicit AbstractNetworkPortController(QObject *parent = 0);
 /*public*/ virtual void setHostName(QString s);
 /*public*/ virtual QString getHostName();
 /*public*/ virtual bool getMdnsConfigure();
 /*public*/ virtual void _connect(QString host, int port) throw (Exception);
// /*public*/ virtual void _connect(); //throws Exception
 /*public*/ virtual bool status();
 /*public*/ virtual void setPort(int p);
 /*public*/ virtual void setPort(QString p);
 /*public*/ virtual int getPort();
 /*public*/ QString getCurrentPortName();
 /*public*/ virtual void setMdnsConfigure(bool autoconfig);
 /*public*/ virtual void autoConfigure();
 /*public*/ virtual void setAdvertisementName(QString AdName);
 /*public*/ virtual QString getAdvertisementName();
 /*public*/ virtual void setServiceType(QString ServiceType);
 /*public*/ virtual QString getServiceType();
 /*public*/ QDataStream* getInputStream();
 /*public*/ QDataStream* getOutputStream();
 /*public*/ void dispose();
 /*public*/ void recover();
 /*public*/ void reconnect();
 /*public*/ void displayMsg();
 \
signals:

public slots:
 /*public*/ virtual void _connect(); //throws Exception

private:
 /*private*/ QString m_HostAddress;// = "";  // Internal IP address for  ZeroConf
 Logger* log;
 QString statetoString(QAbstractSocket::SocketState socketState);
 QMessageBox* msg;

private slots:
 void on_socketConn_error(QAbstractSocket::SocketError);
 void on_socketConn_hostFound();
 void on_socketConn_connected();
 void on_socketConn_disconnected();
 void st_stateChange(QAbstractSocket::SocketState socketState);

protected:
 // the host name and port number identify what we are
 // talking to.
 /*protected*/ QString m_HostName;// = "";
 // configured clients.
 /*protected*/ int m_port;// = 0;
 // keep the socket provides our connection.
 /*protected*/ QTcpSocket* socketConn;// = NULL;
 /*protected*/ AbstractNetworkPortController(SystemConnectionMemo* connectionMemo, QObject *parent = 0);
 /*protected*/ void setHostAddress(QString s);
 /*protected*/ QString getHostAddress();
 /*protected*/ virtual void resetupConnection();
 friend class Reconnectwait;
};
class Reconnectwait : public QObject
{
 Q_OBJECT
public:
    /*public*/ /*final*/ static int THREADPASS;// = 0;
    /*public*/ /*final*/ static int THREADFAIL;// = 1;
signals:

private:
    int _status;
    AbstractNetworkPortController* self;
    QTimer* timer;
    bool reply;
    int count;// = 0;
    int secondCount;// = 0;
    int reconnectinterval;
    bool bFirstTime;
private slots:
    void checkSocket();
public:
    /*public*/ int status() ;
    /*public*/ Reconnectwait(AbstractNetworkPortController* self) ;
    ///*public*/ void run();
};
#if QT_VERSION < 0x50000
Q_DECLARE_METATYPE(QAbstractSocket::SocketError)
Q_DECLARE_METATYPE(QAbstractSocket::SocketState)
#endif
#endif // ABSTRACTNETWORKPORTCONTROLLER_H
