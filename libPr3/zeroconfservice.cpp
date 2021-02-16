#include "zeroconfservice.h"
#include "loggerfactory.h"
#include "preferences.h"
#include "profileutils.h"
#include "profilemanager.h"
#include "webserverpreferences.h"
#include "instancemanager.h"
#include <QMap>
#include "version.h"
#include "nodeidentity.h"
#include "serviceinfo.h"
#include "jmdns.h"
#include "inetaddress.h"
#include <qhostinfo.h>
#include "serviceinfo.h"
#include "profileutils.h"

/**
 * ZeroConfService objects manage a zeroConf network service advertisement.
 * <P>
 * ZeroConfService objects encapsulate zeroConf network services created using
 * JmDNS, providing methods to start and stop service advertisements and to
 * query service state. Typical usage would be:
 * <pre>
 * ZeroConfService myService = ZeroConfService.create("_withrottle._tcp.local.", port);
 * myService.publish();
 * </pre> or, if you do not wish to retain the ZeroConfService object:
 * <pre>
 * ZeroConfService.create("_http._tcp.local.", port).publish();
 * </pre> ZeroConfService objects can also be created with a HashMap of
 * properties that are included in the TXT record for the service advertisement.
 * This HashMap should remain small, but it could include information such as
 * the XMLIO path (for a web server), the default path (also for a web server),
 * a specific protocol version, or other information. Note that all service
 * advertisements include the JMRI version, using the key "version", and the
 * JMRI version numbers in a string "major.minor.test" with the key "jmri"
 * <P>
 * All ZeroConfServices are published with the computer's hostname as the mDNS
 * hostname (unless it cannot be determined by JMRI), as well as the JMRI node
 * name in the TXT record with the key "node".
 * <p>
 * All ZeroConfServices are automatically stopped when the JMRI application
 * shuts down. Use {@link #allServices() } to get a collection of all published
 * ZeroConfService objects.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 * <P>
 *
 * @author Randall Wood Copyright (C) 2011, 2013
 * @see javax.jmdns.JmDNS
 * @see javax.jmdns.ServiceInfo
 */
///*public*/ class ZeroConfService {

    // static data objects
    /*private*/ /*static*/ /*final*/ QMap<QString, ZeroConfService*> ZeroConfService::_services = QMap<QString, ZeroConfService*>();
    /*private*/ /*static*/ /*final*/ QMap<InetAddress*, JmDNS*> ZeroConfService::_netServices = QMap<InetAddress*, JmDNS*>();
//    /*private*/ /*final*/ List<ZeroConfServiceListener> listeners = new ArrayList<>();
    /*private*/ /*static*/ /*final*/ Logger* ZeroConfService::log = LoggerFactory::getLogger("ZeroConfService");
//    /*private*/ static /*final*/ NetworkListener networkListener = new NetworkListener();
    /*private*/ /*static*/ /*final*/ ShutDownTask* ZeroConfService::shutDownTask = new ZCSShutDownTask("Stop ZeroConfServices");

    /*public*/ /*static*/ /*final*/ QString ZeroConfService::IPv4 = "IPv4";
    /*public*/ /*static*/ /*final*/ QString ZeroConfService::IPv6 = "IPv6";

    /*private*/ /*static*/ /*final*/ Preferences* ZeroConfService::zeroConfPrefs = nullptr;//ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(),
//"ZeroConfService",
//false);

/**
 * Create a ZeroConfService with the minimal required settings. This method
 * calls {@link #create(java.lang.String, int, java.util.HashMap)} with an
 * empty props HashMap.
 *
 * @param type The service protocol
 * @param port The port the service runs over
 * @return An unpublished ZeroConfService
 * @see #create(java.lang.String, java.lang.String, int, int, int,
 * java.util.HashMap)
 */
/*public*/ /*static*/ ZeroConfService* ZeroConfService::create(QString type, int port) {
    return create(type, port, QMap<QString, QVariant>());
}

/**
 * Create a ZeroConfService with an automatically detected server name. This
 * method calls
 * {@link #create(java.lang.String, java.lang.String, int, int, int, java.util.HashMap)}
 * with the default weight and priority, and with the result of
 * {@link jmri.web.server.WebServerPreferences#getRailroadName()}
 * reformatted to replace dots and dashes with spaces.
 *
 * @param type       The service protocol
 * @param port       The port the service runs over
 * @param properties Additional information to be listed in service
 *                   advertisement
 * @return An unpublished ZeroConfService
 */
/*public*/ /*static*/ ZeroConfService* ZeroConfService::create(QString type, int port, QMap<QString, QVariant> properties) {
    return create(type, static_cast<WebServerPreferences*>(InstanceManager::getDefault("WebServerPreferences"))->getRailroadName() +
          + "_" + QHostInfo::localHostName() + "_" + QString::number(port), port, 0, 0, properties);
}

/**
 * Create a ZeroConfService. The property <i>version</i> is added or
 * replaced with the current JMRI version as its value. The property
 * <i>jmri</i> is added or replaced with the JMRI major.minor.test version
 * string as its value.
 * <p>
 * If a service with the same key as the new service is already published,
 * the original service is returned unmodified.
 *
 * @param type       The service protocol
 * @param name       The name of the JMRI server listed on client devices
 * @param port       The port the service runs over
 * @param weight     Default value is 0
 * @param priority   Default value is 0
 * @param properties Additional information to be listed in service
 *                   advertisement
 * @return An unpublished ZeroConfService
 */
/*public*/ /*static*/ ZeroConfService* ZeroConfService::create(QString type, QString name, int port, int weight, int priority, QMap<QString, QVariant> properties) {
    ZeroConfService* s;
    if (ZeroConfService::_services.contains(ZeroConfService::key(type, name))) {
        s = ZeroConfService::_services.value(ZeroConfService::key(type, name));
        log->debug(tr("Using existing ZeroConfService %1").arg(s->key()));
    } else {
        properties.insert("version", Version::name());
        // use the major.minor.test version string for jmri since we have potentially
        // tight space constraints in terms of the number of bytes that properties
        // can use, and there are some unconstrained properties that we would like to use.
        properties.insert("jmri", Version::getCanonicalVersion());
        properties.insert("node", NodeIdentity::networkIdentity());
        s = new ZeroConfService( ServiceInfo::create(type, name, port, weight, priority, properties));
        log->debug(tr("Creating new ZeroConfService %1 with properties %2").arg(s->key()).arg(properties.keys().at(0)));

    }
    return s;
}

/**
 * Create a ZeroConfService object.
 *
 * @param service the JmDNS service information
 */
/*protected*/ ZeroConfService::ZeroConfService(ServiceInfo* service) {
    this->_serviceInfo = service;
 serviceInfos = QMap<InetAddress*, ServiceInfo*>();

 QObjectList* list = InstanceManager::getList("QZeroConf");
 if(list->isEmpty())
 {
  zeroConf = new QZeroConf();
  InstanceManager::store(zeroConf, "QZeroConf");
 }
 else
  zeroConf = static_cast<QZeroConf*>(list->at(list->size()-1));
 if(zeroConfPrefs == nullptr)
  zeroConfPrefs = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(),
                                               "ZeroConfService",
                                               false);
}

/**
 * Get the key of the ZeroConfService object. The key is fully qualified
 * name of the service in all lowercase, jmri._http.local.
 *
 * @return The fully qualified name of the service.
 */
/*public*/ QString ZeroConfService::key() {
    return this->serviceInfo()->getKey();
}

/**
 * Generate a ZeroConfService key for searching in the HashMap of running
 * services.
 *
 * @param type the service type (usually a protocol name or mapping)
 * @param name the service name (usually the JMRI railroad name or system
 *             host name)
 * @return The combination of the name and type of the service.
 */
/*protected*/ /*static*/ QString ZeroConfService::key(QString type, QString name) {
    return (name + "." + type).toLower();
}

/**
 * Get the name of the ZeroConfService object. The name can only be set when
 * creating the object.
 *
 * @return The service name as reported by the
 *         {@link javax.jmdns.ServiceInfo} object.
 */
/*public*/ QString ZeroConfService::name() {
    return this->serviceInfo()->getName();
}

/**
 * Get the type of the ZeroConfService object. The type can only be set when
 * creating the object.
 *
 * @return The service type as reported by the
 *         {@link javax.jmdns.ServiceInfo} object.
 */
/*public*/ QString ZeroConfService::type() {
    return this->serviceInfo()->getType();
}
#if 1
/*private*/ ServiceInfo* ZeroConfService::addServiceInfo(JmDNS* DNS) throw (IOException) {
    if (!this->serviceInfos.contains(DNS->getInetAddress())) {
        this->serviceInfos.insert(DNS->getInetAddress(), this->serviceInfo()->clone());
    }
    return this->serviceInfos.value(DNS->getInetAddress());
}
#endif
/**
 * Get the reference ServiceInfo for the object. This is the JmDNS
 * implementation of a zeroConf service. The reference ServiceInfo is never
 * actually registered with a JmDNS service.
 *
 * @return The serviceInfo object.
 */
/*public*/ ServiceInfo* ZeroConfService::serviceInfo() {
    return this->_serviceInfo;
}

/**
 * Get the state of the service.
 *
 * @return True if the service is being advertised, and false otherwise.
 */
/*public*/ bool ZeroConfService::isPublished() {
    return ZeroConfService::_services.contains(key());
}

/**
 * Start advertising the service.
 */
/*public*/ void ZeroConfService::publish() {
    if (!isPublished()) {
        //get current preference values
        bool useIPv4 = zeroConfPrefs->getBoolean(IPv4, true);
        bool useIPv6 = zeroConfPrefs->getBoolean(IPv6, true);
        ZeroConfService::_services.insert(this->key(), this);
#if 0
        this.listeners.stream().forEach((listener) -> {
            listener.serviceQueued(new ZeroConfServiceEvent(this, null));
        });
        for (JmDNS netService : ZeroConfService.netServices().values()) {
            ZeroConfServiceEvent event;
            ServiceInfo info;
            try {
                if (netService.getInetAddress() instanceof Inet6Address && !useIPv6) {
                    // Skip if address is IPv6 and should not be advertised on
                    log->debug("Ignoring IPv6 address {}", netService.getInetAddress().getHostAddress());
                    continue;
                }
                if (netService.getInetAddress() instanceof Inet4Address && !useIPv4) {
                    // Skip if address is IPv4 and should not be advertised on
                    log->debug("Ignoring IPv4 address {}", netService.getInetAddress().getHostAddress());
                    continue;
                }
                try {
                    log->debug("Publishing ZeroConfService for '{}' on {}", key(), netService.getInetAddress().getHostAddress());
                } catch (IOException ex) {
                    log->debug("Publishing ZeroConfService for '{}' with IOException {}", key(), ex.getLocalizedMessage(), ex);
                }
                // JmDNS requires a 1-to-1 mapping of serviceInfo to InetAddress
                if (!this.serviceInfos.containsKey(netService.getInetAddress())) {
                    try {
                        info = this.serviceInfo();
                        netService.registerService(info);
                        log->debug("Register service '{}' on {} successful.", this.key(), netService.getInetAddress().getHostAddress());
                    } catch (IllegalStateException ex) {
                        // thrown if the reference serviceInfo object is in use
                        try {
                            log->debug("Initial attempt to register '{}' on {} failed.", this.key(), netService.getInetAddress().getHostAddress());
                            info = this.addServiceInfo(netService);
                            log->debug("Retrying register '{}' on {}.", this.key(), netService.getInetAddress().getHostAddress());
                            netService.registerService(info);
                        } catch (IllegalStateException ex1) {
                            // thrown if service gets registered on interface by
                            // the networkListener before this loop on interfaces
                            // completes, so we only ensure a later notification
                            // is not posted continuing to next interface in list
                            log->debug("'{}' is already registered on {}.", this.key(), netService.getInetAddress().getHostAddress());
                            continue;
                        }
                    }
                } else {
                    log->debug("skipping '{}' on {}, already in serviceInfos.", this.key(), netService.getInetAddress().getHostAddress());
                }
                event = new ZeroConfServiceEvent(this, netService);
            } catch (IOException ex) {
                log->error("Unable to publish service for '{}': {}", key(), ex.getMessage());
                continue;
            }
            this.listeners.stream().forEach((listener) -> {
                listener.servicePublished(event);
            });
        }
#endif

        QStringListIterator iter = this->_serviceInfo->getPropertyNames();
        while(iter.hasNext())
        {
         QString propertyName = iter.next();
         zeroConf->addServiceTxtRecord(propertyName, this->_serviceInfo->getPropertyBytes(propertyName));
        }
        connect(this->zeroConf, SIGNAL(servicePublished()), this, SLOT(servicePublished()));
        connect(this->zeroConf, SIGNAL(error(QZeroConf::error_t)), this, SLOT(error(QZeroConf::error_t)));
        connect(this->zeroConf, SIGNAL(serviceAdded(QZeroConfService)), this, SLOT(addService(QZeroConfService)));
        log->debug(tr("startServicePublish: name = '%1', type= '%2', port = '%3'").arg(serviceInfo()->getName()).arg(serviceInfo()->getType()).arg(serviceInfo()->getPort()));
         zeroConf->clearServiceTxtRecords();
        if(serviceInfo()->getPropertyNames().hasNext())
        {
         QString name = serviceInfo()->getPropertyNames().next();
         if(name.isEmpty())
           this->zeroConf->addServiceTxtRecord(this->serviceInfo()->getTextString());
           else
         this->zeroConf->addServiceTxtRecord(name, this->serviceInfo()->getPropertyString(name));
        }
        QString type = serviceInfo()->getType();
        QString application = serviceInfo()->getApplication();
        QString protocol = serviceInfo()->getProtocol();
        QString domain = serviceInfo()->getDomain();
        currentType = "_" +application+ "._"+protocol;
        this->zeroConf->startServicePublish(this->_serviceInfo->getName().toUtf8(), currentType.toUtf8(), domain.toUtf8(), this->_serviceInfo->getPort());

    }
}
void ZeroConfService::servicePublished()
{
 log->info(tr("published %1").arg(_serviceInfo->getName()));
 if (!this->zeroConf->browserExists())
  zeroConf->startBrowser(currentType);
}

//void ZeroConfService::on_servicePublished(ZeroConfServiceEvent* e)
//{
// log->info(tr("published %1").arg(e->getService()->serviceInfo()->getName()));
// if (!this->zeroConf->browserExists())
//  zeroConf->startBrowser(currentType);
//}

void ZeroConfService::error(QZeroConf::error_t e)
{
 QString msg;
 switch(e)
 {
 default:
  msg = "unknown error";
    break;
 case QZeroConf::noError:
  msg = "no error";
  break;
 case QZeroConf::serviceRegistrationFailed:
  msg = "service registration failed";
  break;
 case QZeroConf::serviceNameCollision:
  msg = "service name collision";
  break;
 case QZeroConf::browserFailed:
  msg = "broser failed";
  break;
 }
 log->error(tr("ZeroConf error %1 for %2").arg(msg).arg(_serviceInfo->getName()));
}

void ZeroConfService::addService(QZeroConfService zcs)
{
 log->info(tr("added service %1, host:%3 ip %2, application: %4").arg(zcs.name()).arg(zcs.ip().toString()).arg(zcs.host()).arg(zcs.type()));
 InetAddress* inetAddress = new InetAddress(zcs.ip());
 JmDNS* _DNS = JmDNS::create(inetAddress);
 inetAddressAdded(inetAddress, _DNS);
}

/**
 * Stop advertising the service.
 */
/*public*/ void ZeroConfService::stop() {
    log->debug(tr("Stopping ZeroConfService %1").arg(this->key()));
    if (ZeroConfService::services().contains(this->key()))
    {
//        ZeroConfService.netServices().values().stream().forEach((netService) -> {
//            try {
//                try {
//                    log->debug("Unregistering {} from {}", this.key(), netService.getInetAddress());
//                    netService.unregisterService(this.serviceInfos.get(netService.getInetAddress()));
//                    this.serviceInfos.remove(netService.getInetAddress());
//                    this.listeners.stream().forEach((listener) -> {
//                        listener.serviceUnpublished(new ZeroConfServiceEvent(this, netService));
//                    });
//                } catch (NullPointerException ex) {
//                    log->debug(tr("%1 already unregistered from %2").arg(this->key()).arg( netService.getInetAddress()));
//                }
//            } catch (IOException ex) {
//                log->error(tr("Unable to stop ZeroConfService {}. {}", this.key(), ex.getLocalizedMessage());
//            }
//        });

        ZeroConfService::services().remove(key());
    }
}

/**
 * Stop advertising all services.
 */
/*public*/ /*static*/ void ZeroConfService::stopAll() {
    ZeroConfService::stopAll(false);
}

/*private*/ /*static*/ void ZeroConfService::stopAll(/*final*/ bool close) {
    log->debug("Stopping all ZeroConfServices");
#if 0
    CountDownLatch zcLatch = new CountDownLatch(ZeroConfService.services().size());
    new HashMap<>(ZeroConfService.services()).values().parallelStream().forEach(service -> {
        service.stop();
        zcLatch.countDown();
    });
    try {
        zcLatch.await();
    } catch (InterruptedException ex) {
        log->warn("ZeroConfService stop threads interrupted.", ex);
    }
    CountDownLatch nsLatch = new CountDownLatch(ZeroConfService.netServices().size());
    new HashMap<>(ZeroConfService.netServices()).values().parallelStream().forEach((netService) -> {
        new Thread(() -> {
            netService.unregisterAllServices();
            if (close) {
                try {
                    netService.close();
                } catch (IOException ex) {
                    log->debug("jmdns.close() returned IOException: {}", ex.getMessage());
                }
            }
            nsLatch.countDown();
        }).start();
    });
    try {
        zcLatch.await();
    } catch (InterruptedException ex) {
        log->warn("JmDNS unregister threads interrupted.", ex);
    }
    ZeroConfService.services().clear();
#endif
}

/**
 * A list of published ZeroConfServices
 *
 * @return Collection of ZeroConfServices
 */
/*public*/ /*static*/ QList<ZeroConfService*> ZeroConfService::allServices() {
    return ZeroConfService::services().values();
}

/* return a list of published services */
/*private*/ /*static*/ QMap<QString, ZeroConfService*> ZeroConfService::services() {
    return ZeroConfService::_services;
}

/**
 * The list of JmDNS handlers.
 *
 * @return a {@link java.util.HashMap} of {@link javax.jmdns.JmDNS} objects,
 *         accessible by {@link java.net.InetAddress} keys.
 */
/*synchronized*/ /*public*/ /*static*/ QMap<InetAddress*, JmDNS*> ZeroConfService::netServices() {
    if (ZeroConfService::_netServices.isEmpty()) {
        log->debug(tr("JmDNS version: %1").arg(JmDNS::VERSION));
        try {
            for (InetAddress* address : hostAddresses()) {
                // explicitly pass a valid host name, since null causes a very long lookup on some networks
                log->debug(tr("Calling JmDNS.create(%1, '%2')").arg(address->getHostAddress()).arg(address->getHostAddress()));
                ZeroConfService::_netServices.insert(address, JmDNS::create(address, address->getHostAddress()));
            }
        } catch (IOException ex) {
            log->warn(tr("Unable to create JmDNS with error: %1").arg(ex.getMessage())/*, ex*/);
        }
        if(InstanceManager::getOptionalDefault("ShutDownManager"))
        {
           ShutDownManager* manager = static_cast<ShutDownManager*>(InstanceManager::getOptionalDefault("ShutDownManager"));
            manager->_register(ZeroConfService::shutDownTask);
        };//);
    }
    return QMap<InetAddress*, JmDNS*>(ZeroConfService::_netServices);
}

 /* Return the system name or "computer" if the system name cannot be
 * determined. This method returns the first part of the fully qualified
 * domain name from {@link #FQDN}.
 *
 * @param address The {@link java.net.InetAddress} for the host name.
 * @return The hostName associated with the first interface encountered.
 */
/*public*/ /*static*/ QString ZeroConfService::hostName(InetAddress* address) {
    QString hostName = ZeroConfService::FQDN(address) + ".";
    // we would have to check for the existance of . if we did not add .
    // to the string above.
    return hostName.mid(0, hostName.indexOf('.'));
}

/**
 * Return the fully qualified domain name or "computer" if the system name
 * cannot be determined. This method uses the
 * {@link javax.jmdns.JmDNS#getHostName()} method to get the name.
 *
 * @param address The {@link java.net.InetAddress} for the FQDN.
 * @return The fully qualified domain name.
 */
/*public*/ /*static*/ QString ZeroConfService::FQDN(InetAddress* address) {
    return ZeroConfService::netServices().value(address)->getHostName();
}

/**
 * A list of the non-loopback, non-link-local IP addresses of the host, or
 * null if none found. The UseIPv4 and UseIPv6 preferences are also applied.
 *
 * @return The non-loopback, non-link-local IP addresses on the host, of the allowed type(s).
 */
/*public*/ /*static*/ QList<InetAddress*> ZeroConfService::hostAddresses() {
    QList<InetAddress*> addrList = QList<InetAddress*>();
#if 0
    Enumeration<NetworkInterface> IFCs = null;
    //get current preference values
    boolean useIPv4 = zeroConfPrefs.getBoolean(IPv4, true);
    boolean useIPv6 = zeroConfPrefs.getBoolean(IPv6, true);

    try {
        IFCs = NetworkInterface.getNetworkInterfaces();
    } catch (SocketException ex) {
        log->error("Unable to get network interfaces.", ex);
    }
    if (IFCs != null) {
        while (IFCs.hasMoreElements()) {
            NetworkInterface IFC = IFCs.nextElement();
            try {
                if (IFC.isUp()) {
                    Enumeration<InetAddress> addresses = IFC.getInetAddresses();
                    while (addresses.hasMoreElements()) {
                        InetAddress address = addresses.nextElement();
                        //add only if a valid address type
                        if (!address.isLoopbackAddress() && !address.isLinkLocalAddress() &&
                                ((address instanceof Inet4Address && useIPv4) ||
                                        (address instanceof Inet6Address && useIPv6))) {
                            addrList.add(address);
                        }
                    }
                }
            } catch (SocketException ex) {
                log->error("Unable to read network interface {}.", IFC, ex);
            }
        }
    }
#endif
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> addresses = hostInfo.addresses();
    bool useIPv4 = zeroConfPrefs->getBoolean(IPv4, true);
    bool useIPv6 = zeroConfPrefs->getBoolean(IPv6, true);
    foreach (QHostAddress hostAddr, addresses)
    {
     if(hostAddr.isLoopback())
      continue;
     QAbstractSocket::NetworkLayerProtocol protocol = hostAddr.protocol();
     if(useIPv4 && protocol == QAbstractSocket::IPv4Protocol)
     {
      qint32 inet4Address = hostAddr.toIPv4Address();
      addrList.append(new InetAddress(hostAddr));
     }
     if(useIPv6 && protocol == QAbstractSocket::IPv6Protocol)
     {
      Q_IPV6ADDR inet6Address = hostAddr.toIPv6Address();
      addrList.append(new InetAddress(hostAddr));
     }
    }
    return addrList;
}

/*public*/ void ZeroConfService::addEventListener(ZeroConfServiceListener* l) {
//    this.listeners.add(l);
// connect(this, SIGNAL(servicePublished(ZeroConfServiceEvent*)), l, SLOT(on_servicePublished(ZeroConfServiceEvent*)));
// connect(this, SIGNAL(serviceUnpublished(ZeroConfServiceEvent*)), l, SLOT(on_serviceUnpublished(ZeroConfServiceEvent*)));

}

/*public*/ void ZeroConfService::removeEventListener(ZeroConfServiceListener* l) {
//    this.listeners.remove(l);
// disconnect(this, SIGNAL(servicePublished(ZeroConfServiceEvent*)), l, SLOT(servicePublished(ZeroConfServiceEvent*)));
// disconnect(this, SIGNAL(serviceUnpublished(ZeroConfServiceEvent*)), l, SLOT(serviceUnpublished(ZeroConfServiceEvent*)));

}
#if 1
// /*private*/ static class NetworkListener implements NetworkTopologyListener {

//    @Override
//    /*public*/ void inetAddressAdded(NetworkTopologyEvent nte)
/*public*/ void ZeroConfService::inetAddressAdded(InetAddress* inetAddress, JmDNS* _DNS)
{
        //get current preference values
        bool useIPv4 = zeroConfPrefs->getBoolean(IPv4, true);
        bool useIPv6 = zeroConfPrefs->getBoolean(IPv6, true);
        //if (inetAddress instanceof Inet6Address
        if(inetAddress->getQHostAddress().protocol() == QAbstractSocket::IPv6Protocol
                && !useIPv6 ) {
            log->debug(tr("Ignoring IPv6 address %1").arg(inetAddress->getHostAddress()));
            return;
        }
        //if (inetAddress instanceof Inet4Address
        if(inetAddress->getQHostAddress().protocol() == QAbstractSocket::IPv4Protocol
                && !useIPv4) {
            log->debug(tr("Ignoring IPv4 address %1").arg(inetAddress->getHostAddress()));
            return;
        }
        if (!ZeroConfService::_netServices.contains(inetAddress)) {
            log->debug(tr("Adding address %1").arg(inetAddress->getHostAddress()));
            ZeroConfService::_netServices.insert(inetAddress, _DNS);
            //ZeroConfService.allServices().stream().forEach((service) ->
            foreach(ZeroConfService* service, ZeroConfService::allServices())
            {
                try {
                    if (!service->serviceInfos.contains(_DNS->getInetAddress())) {
                        log->debug(tr("Publishing zeroConf service for '%1' on %2").arg(service->key()).arg( inetAddress->getHostAddress()));
                        _DNS->registerService(service->addServiceInfo(_DNS));
//                        service.listeners.stream().forEach((listener) -> {
//                            listener.servicePublished(new ZeroConfServiceEvent(service, _DNS));
//                        });
                        emit servicePublished(new ZeroConfServiceEvent(service, _DNS));
                    }
                } catch (IOException ex) {
                    log->error(ex.getLocalizedMessage() + ex.getMessage());
                }
            };//);
        } else {
            log->debug(tr("Address %1 already known.").arg(inetAddress->getHostAddress()));
        }
    }

    //@Override
//    /*public*/ void inetAddressRemoved(NetworkTopologyEvent nte)
/*public*/ void ZeroConfService::inetAddressRemoved(InetAddress* inetAddress, JmDNS* _DNS)
{
        log->debug(tr("Removing address %1").arg(inetAddress->getQHostAddress().toString()));
        ZeroConfService::_netServices.remove(inetAddress);
        _DNS->unregisterAllServices();
        //ZeroConfService.allServices().stream().map((service) ->
        foreach (ZeroConfService* service, ZeroConfService::allServices()) {
        {
            service->serviceInfos.remove(inetAddress);
            //return service;
        };//).forEach((service) -> {
//            service.listeners.stream().forEach((listener) -> {
//                listener.servicePublished(new ZeroConfServiceEvent(service, _DNS));
//            });
         emit serviceUnpublished(new ZeroConfServiceEvent(service, _DNS));

        };//);
    }

//};
#endif
///*private*/ static class ShutDownTask extends QuietShutDownTask {

//    /*private*/ boolean isComplete = false;

    /*public*/ ZCSShutDownTask::ZCSShutDownTask(QString name) : QuietShutDownTask(name,this){
        //super(name);
 this->zcs = zcs;
    }

    //@Override
    /*public*/ bool ZCSShutDownTask::execute()
{
#if 0
        new Thread(() -> {
            Date start = new Date();
            log->debug("Starting to stop services...");
            ZeroConfService.stopAll(true);
            log->debug("Stopped all services in {} milliseconds", new Date().getTime() - start.getTime());
            start = new Date();
            JmmDNS.Factory.getInstance().removeNetworkTopologyListener(ZeroConfService.networkListener);
            log->debug("Removed network topology listener in {} milliseconds", new Date().getTime() - start.getTime());
            this.isComplete = true;
        }).start();
#endif
        return true;
    }

    //@Override
    /*public*/ bool ZCSShutDownTask::isParallel() {
        return true;
    }

    //@Override
    /*public*/ bool ZCSShutDownTask::isComplete() {
        return this->_isComplete;
    }
//};

