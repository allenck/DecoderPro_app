#ifndef ZEROCONFSERVICEMANAGER_H
#define ZEROCONFSERVICEMANAGER_H

#include <QObject>

#include "inetaddress.h"
#include "jmdns.h"
#include "zeroconfservice.h"
#include "networktopologylistener.h"
#include "networktopologyevent.h"
#include "zeroconfpreferences.h"
#include "profilemanager.h"

class NetworkListener;
class ZCSMShutDownTask;
class Logger;
class ZeroConfServiceManager : public QObject
{
 Q_OBJECT
public:
 explicit ZeroConfServiceManager(QObject *parent = nullptr);
 /*public*/ enum Protocol {
     IPv4, IPv6, All
 };
 /*public*/ ZeroConfService* create(QString type, int port);
 /*public*/ ZeroConfService* create(QString type, int port, QMap<QString, QString>* properties);
 /*public*/ ZeroConfService* create(QString type, QString name, int port, int weight, int priority, QMap<QString, QString>* properties);
 /*public*/ void publish(ZeroConfService* service);
 /*public*/ void stop(ZeroConfService* service);
 /*public*/ void stopAll();
 /*public*/ void dispose();
 /*public*/ bool isPublished(ZeroConfService* service);

signals:

public slots:

private:
 static Logger* log;
 /*private*/ void stopAll(/*final*/ bool close);
 /*private*/ static void dispose(ZeroConfServiceManager* manager);
protected:
 /*protected*/ static /*final*/ QHash<InetAddress*, JmDNS*> JMDNS_SERVICES;// = new HashMap<>();
 /*protected*/ /*final*/ QMap<QString, ZeroConfService*> services = QMap<QString, ZeroConfService*>();
 /*protected*/ /*final*/ NetworkListener* networkListener;// = new NetworkListener(this);
 /*protected*/ /*final*/ ShutDownTask* shutDownTask;// = new ZCSMShutDownTask(this);

 /*protected*/ /*final*/ ZeroConfPreferences* preferences = new ZeroConfPreferences(ProfileManager::getDefault()->getActiveProfile());
 /*protected*/ QString key(QString type, QString name);

 friend class NetworkListener;
};
/*protected*/ /*static*/ class NetworkListener : public QObject, public NetworkTopologyListener {
 Q_OBJECT
 Q_INTERFACES(NetworkTopologyListener)
        /*private*/ /*final*/ ZeroConfServiceManager* manager;
public:
        /*public*/ NetworkListener(ZeroConfServiceManager* manager) {
            this->manager = manager;
        }

        //@Override
        /*public*/ void inetAddressAdded(NetworkTopologyEvent* nte);
        //@Override
        /*public*/ void inetAddressRemoved(NetworkTopologyEvent* nte) {
            /*final*/ InetAddress* address = nte->getInetAddress();
#if 0 // TODO:
            JmDNS dns = nte.getDNS();
            log.debug("Removing address {}", address);
            JMDNS_SERVICES.remove(address);
            dns.unregisterAllServices();
            manager.allServices().stream().forEach((service) -> {
                service.removeServiceInfo(address);
                service.getListeners().stream().forEach((listener) -> {
                    listener.servicePublished(new ZeroConfServiceEvent(service, dns));
                });
            });
#endif
        }
 QObject* self() {return (QObject*)this;}
    };
/*protected*/ /*static*/ class ZCSMShutDownTask : public QuietShutDownTask {
Q_OBJECT
    /*private*/ bool _isComplete = false;
    /*private*/ /*final*/ ZeroConfServiceManager* manager;
public:
    /*public*/ ZCSMShutDownTask(ZeroConfServiceManager* manager) : QuietShutDownTask("Stop ZeroConfServices"){
        //super("Stop ZeroConfServices");
        this->manager = manager;
    }

    //@Override
    /*public*/ bool execute() {
#if 0 // TODO
        new Thread(() -> {
            dispose(manager);
            this._isComplete = true;
        }, "ZeroConfServiceManager ShutDownTask").start();
#endif
        return true;
    }

    //@Override
    /*public*/ bool isParallel() {
        return true;
    }

    //@Override
    /*public*/ bool isComplete() {
        return this->_isComplete;
    }
};

#endif // ZEROCONFSERVICEMANAGER_H
