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
 /*public*/ void setHostName(QString s) override;
 /*public*/ QString getHostName() override;
 /*public*/ bool getMdnsConfigure() override;
 /*public*/ void _connect(QString host, int port) throw (Exception) override;
 ///*public*/ void _connect(); //throws Exception
 /*public*/  bool status() override;
 /*public*/  void setPort(int p) override;
 /*public*/  void setPort(QString p) override;
 /*public*/  int getPort() override;
 /*public*/ QString getCurrentPortName() override;
 /*public*/  void setMdnsConfigure(bool autoconfig) override;
 /*public*/  void setAdvertisementName(QString AdName) override;
 /*public*/  QString getAdvertisementName() override;
 /*public*/  void setServiceType(QString ServiceType) override;
 /*public*/  QString getServiceType() override;
 /*public*/ QDataStream* getInputStream() override;
 /*public*/ QDataStream* getOutputStream() override;
 /*public*/ void dispose() override;
 /*public*/ void recover() override;
 /*public*/ void reconnect();
 /*public*/ void displayMsg();
 /*public*/ virtual void autoConfigure()  override;

signals:

public slots:
 /*public*/ void _connect() override; //throws Exception

private:
 /*private*/ QString m_HostAddress;// = "";  // Internal IP address for  ZeroConf
 Logger* log;
 QString statetoString(QAbstractSocket::SocketState socketState);
 QMessageBox* msg;
 int connTimeout = 0;

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
 /*protected*/ int m_port = 0;
 // keep the socket provides our connection.
 /*protected*/ QTcpSocket* socketConn= nullptr;
 /*protected*/ AbstractNetworkPortController(SystemConnectionMemo* connectionMemo, QObject *parent = 0);
 /*protected*/ void setHostAddress(QString s);
 /*protected*/ QString getHostAddress();
 /*protected*/ virtual void resetupConnection();
 /*protected*/ void setConnectionTimeout(int t);
 /*protected*/ int getConnectionTimeout();

 friend class Reconnectwait;
 friend class AMRTRcvHandler;
 friend class AMRTXmtHandler;
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
    int count = 0;
    int secondCount = 0;
    int reconnectinterval;
    bool bFirstTime;
    int connTimeout;

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
