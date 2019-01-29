#ifndef LNOVERTCPPACKETIZER_H
#define LNOVERTCPPACKETIZER_H
#include "lnpacketizer.h"
#include "runnable.h"

class LnTcpRcvHandler;
class LnTcpXmtHandler;
class QTcpSocket;
class LnNetworkPortController;
class LnOverTcpPacketizer : public LnPacketizer
{
 Q_OBJECT
public:
 explicit LnOverTcpPacketizer(QObject *parent = 0);
 /*public*/ LnNetworkPortController* networkController;// = null;
 /*public*/ bool isXmtBusy();
 /*public*/ void connectPort(LnNetworkPortController* p);
 /*public*/ void disconnectPort(LnNetworkPortController* p);

signals:

public slots:

private:
 static /*final*/ QString RECEIVE_PREFIX;// = "RECEIVE";
 static /*final*/ QString SEND_PREFIX;// = "SEND";
 Logger* log;
 friend class LnTcpRcvHandler;
 friend class LnTcpXmtHandler;
};

class LnTcpRcvHandler : public QThread
{
Q_OBJECT
    /**
     * Remember the LnPacketizer object
     */
    LnOverTcpPacketizer* trafficController;
public:
    /*public*/ LnTcpRcvHandler(LnOverTcpPacketizer* lt);
    /*public*/ void run();
signals:
    //void notifyMessage(LocoNetMessage* msg);
    void passMessage(LocoNetMessage*);
 private:
    QTcpSocket* connSocket;
    QTextStream* inText;
    Logger* log;
    QMutex mutex;
private slots:
    void on_ReadyRead();

};

/**
 * Captive class to handle transmission
 */
class LnTcpXmtHandler : public QThread
{
 Q_OBJECT
 LnOverTcpPacketizer* trafficController;
public:
    LnTcpXmtHandler(LnOverTcpPacketizer* trafficController);
    /*public*/ void run();
public slots:
    void sendMessage(LocoNetMessage*);
private:
    QTextStream* outText;
    QTcpSocket* connSocket;
    Logger* log;

};

#endif // LNOVERTCPPACKETIZER_H
