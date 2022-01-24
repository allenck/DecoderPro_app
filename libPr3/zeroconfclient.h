#ifndef ZEROCONFCLIENT_H
#define ZEROCONFCLIENT_H

#include <QObject>
#include "../../../../Projects/QtZeroConf-master/qzeroconf.h"
//#include "qzeroconf.h"
#include "networktopologyevent.h"

class ServiceInfo;
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
 /*public*/ ServiceInfo *getServiceOnHost(QString serviceType, QString Address);
 /*public*/ ServiceInfo* getServicebyAdName(QString serviceType, QString Address);
 /*public*/ QList<QZeroConfService> getServices();

signals:
 void serviceAdded(QString hostname);

public slots:
 void addService(QZeroConfService se);
 void removeService(QZeroConfService se);

private:
 static Logger* log;
 /*private*/ NetworkServiceListener* mdnsServiceListener = nullptr;
 friend class NetworkServiceListener;
 QList<QZeroConfService> services;
};

/*public*/ /*static*/ class NetworkServiceListener : QObject//implements ServiceListener, NetworkTopologyListener
{
Q_OBJECT
    /*private*/ /*final*/ QString service;
    /*private*/ /*final*/ ZeroConfClient* client = nullptr;
 QZeroConf* zeroConf = nullptr;
protected:
    /*protected*/ NetworkServiceListener(QString service, ZeroConfClient* client);
public slots:

#if 1
    //@Override
    /*public*/ void inetAddressAdded(NetworkTopologyEvent* nte) {
//        nte->getDNS()->addServiceListener(service, this);
    }

    //@Override
    /*public*/ void inetAddressRemoved(NetworkTopologyEvent* nte) {
//        nte->getDNS()->removeServiceListener(service, this);
    }
#endif

    /*public*/ void serviceAdded(QZeroConfService se);
    /*public*/ void serviceRemoved(QZeroConfService se);
    /*public*/ void serviceUpdated(QZeroConfService se);
    /*public*/ void error(QZeroConf::error_t);
#if 0
    @Override
    /*public*/ void serviceResolved(ServiceEvent se) {
        log.debug("Service resolved: {}", se.getInfo().toString());
    }
#endif
 friend class ZeroConfClient;
};
#endif // ZEROCONFCLIENT_H
