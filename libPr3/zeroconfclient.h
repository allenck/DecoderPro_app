#ifndef ZEROCONFCLIENT_H
#define ZEROCONFCLIENT_H

#include <QObject>
#include "qzeroconf.h"

class NetworkServiceListener;
class QZeroConfService;
class QZeroConf;
class Logger;
class ServiceListener;
class ZeroConfClient : public QObject
{
 Q_OBJECT
public:
 explicit ZeroConfClient(QObject *parent = nullptr);
 /*public*/ void startServiceListener(/*@Nonnull*/ QString service);

signals:

public slots:

private:
 static Logger* log;
 /*private*/ NetworkServiceListener* mdnsServiceListener = nullptr;
 friend class NetworkServiceListener;

};

/*public*/ /*static*/ class NetworkServiceListener : QObject//implements ServiceListener, NetworkTopologyListener
{
Q_OBJECT
    /*private*/ /*final*/ QString service;
    /*private*/ /*final*/ ZeroConfClient* client;
 QZeroConf* zeroConf;
protected:
    /*protected*/ NetworkServiceListener(QString service, ZeroConfClient* client);
public slots:
#if 0
    //@Override
    /*public*/ void inetAddressAdded(NetworkTopologyEvent nte) {
        nte.getDNS().addServiceListener(service, this);
    }

    @Override
    /*public*/ void inetAddressRemoved(NetworkTopologyEvent nte) {
        nte.getDNS().removeServiceListener(service, this);
    }
#endif

    /*public*/ void serviceAdded(QZeroConfService se);
    /*public*/ void serviceRemoved(QZeroConfService se);
#if 0
    @Override
    /*public*/ void serviceResolved(ServiceEvent se) {
        log.debug("Service resolved: {}", se.getInfo().toString());
    }
#endif
 friend class ZeroConfClient;
};
#endif // ZEROCONFCLIENT_H
