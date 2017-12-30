#include "zeroconfservice.h"
#include "loggerfactory.h"
#include <QMap>

ZeroConfService::ZeroConfService(QObject *parent) : QObject(parent)
{

}

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
 * </pre> ZeroConfService objects can also be created with a QMap of
 * properties that are included in the TXT record for the service advertisement.
 * This QMap should remain small, but it could include information such as
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
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Randall Wood Copyright (C) 2011, 2013
 * @see javax.jmdns.JmDNS
 * @see javax.jmdns.ServiceInfo
 */
///*public*/ class ZeroConfService {

// internal data members
// static data objects
/*private*/ /*static*/ /*final*/ QMap<QString, ZeroConfService*>* ZeroConfService::_services = new QMap<QString, ZeroConfService*>();
/*private*/ /*static*/ /*final*/ QMap<QHostAddress, JmDNS*>* ZeroConfService::netServices = new QMap<QHostAddress, JmDNS*>;
/*private*/ /*static*/ /*final*/ Logger* ZeroConfService::log = LoggerFactory::getLogger("ZeroConfService");
#if 0
/*private*/ /*static*/ /*final*/ NetworkListener* ZeroConfService::networkListener = new NetworkListener();
/*private*/ /*static*/ /*final*/ ZCShutDownTask* ZeroConfService::shutDownTask = new ZCShutDownTask("Stop ZeroConfServices", ZeroConfService* zcs);
#endif

/*public*/ /*static*/ /*final*/ QString IPv4 = "IPv4";
/*public*/ /*static*/ /*final*/ QString IPv6 = "IPv6";
#if 0
/**
 * Create a ZeroConfService with the minimal required settings. This method
 * calls {@link #create(java.lang.String, int, java.util.QMap)} with an
 * empty props QMap.
 *
 * @param type The service protocol
 * @param port The port the service runs over
 * @return An unpublished ZeroConfService
 * @see #create(java.lang.String, java.lang.String, int, int, int,
 * java.util.QMap)
 */
/*public*/ static ZeroConfService create(String type, int port) {
    return create(type, port, new QMap<>());
}

/**
 * Create a ZeroConfService with an automatically detected server name. This
 * method calls
 * {@link #create(java.lang.String, java.lang.String, int, int, int, java.util.QMap)}
 * with the default weight and priority, and with the result of
 * {@link jmri.web.server.WebServerPreferences#getRailRoadName()}
 * reformatted to replace dots and dashes with spaces.
 *
 * @param type       The service protocol
 * @param port       The port the service runs over
 * @param properties Additional information to be listed in service
 *                   advertisement
 * @return An unpublished ZeroConfService
 */
/*public*/ static ZeroConfService create(String type, int port, QMap<String, String> properties) {
    return create(type, WebServerPreferences.getDefault().getRailRoadName(), port, 0, 0, properties);
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
/*public*/ static ZeroConfService create(String type, String name, int port, int weight, int priority, QMap<String, String> properties) {
    ZeroConfService s;
    if (ZeroConfService.services().containsKey(ZeroConfService.key(type, name))) {
        s = ZeroConfService.services().get(ZeroConfService.key(type, name));
        log->debug("Using existing ZeroConfService {}", s.key());
    } else {
        properties.put("version", jmri.Version.name());
        // use the major.minor.test version string for jmri since we have potentially
        // tight space constraints in terms of the number of bytes that properties
        // can use, and there are some unconstrained properties that we would like to use.
        properties.put("jmri", jmri.Version.getCanonicalVersion());
        properties.put("node", NodeIdentity.identity());
        s = new ZeroConfService(ServiceInfo.create(type, name, port, weight, priority, properties));
        log->debug("Creating new ZeroConfService {} with properties {}", s.key(), properties);
    }
    return s;
}

/**
 * Create a ZeroConfService object.
 *
 * @param service the JmDNS service information
 */
/*protected*/ ZeroConfService(ServiceInfo* service) {
serviceInfos = new QMap<QHostAddress, ServiceInfo*>);
serviceInfo = NULL;
listeners = new QList<ZeroConfServiceListener*>()

    this->serviceInfo = service;
}

/**
 * Get the key of the ZeroConfService object. The key is fully qualified
 * name of the service in all lowercase, jmri._http.local.
 *
 * @return The fully qualified name of the service.
 */
/*public*/ String key() {
    return this->serviceInfo().getKey();
}

/**
 * Generate a ZeroConfService key for searching in the QMap of running
 * services.
 *
 * @param type the service type (usually a protocol name or mapping)
 * @param name the service name (usually the JMRI railroad name or system
 *             host name)
 * @return The combination of the name and type of the service.
 */
protected static String key(String type, String name) {
    return (name + "." + type).toLowerCase();
}

/**
 * Get the name of the ZeroConfService object. The name can only be set when
 * creating the object.
 *
 * @return The service name as reported by the
 *         {@link javax.jmdns.ServiceInfo} object.
 */
/*public*/ String name() {
    return this->serviceInfo().getName();
}

/**
 * Get the type of the ZeroConfService object. The type can only be set when
 * creating the object.
 *
 * @return The service type as reported by the
 *         {@link javax.jmdns.ServiceInfo} object.
 */
/*public*/ String type() {
    return this->serviceInfo().getType();
}

/*private*/ ServiceInfo addServiceInfo(JmDNS DNS) throws IOException {
    if (!this->serviceInfos.containsKey(DNS.getQHostAddress())) {
        this->serviceInfos.put(DNS.getQHostAddress(), this->serviceInfo().clone());
    }
    return this->serviceInfos.get(DNS.getQHostAddress());
}

/**
 * Get the reference ServiceInfo for the object. This is the JmDNS
 * implementation of a zeroConf service. The reference ServiceInfo is never
 * actually registered with a JmDNS service.
 *
 * @return The serviceInfo object.
 */
/*public*/ ServiceInfo serviceInfo() {
    return this->serviceInfo;
}

/**
 * Get the state of the service.
 *
 * @return True if the service is being advertised, and false otherwise.
 */
/*public*/ Boolean isPublished() {
    return ZeroConfService.services().containsKey(key());
}

/**
 * Start advertising the service.
 */
/*public*/ void publish() {
    if (!isPublished()) {
        ZeroConfService.services.put(this->key(), this);
        this->listeners.stream().forEach((listener) -> {
            listener.serviceQueued(new ZeroConfServiceEvent(this, NULL));
        });
        bool useIPv4 = ProfileUtils.getPreferences(ProfileManager.getDefault().getActiveProfile(),
                ZeroConfService.class,
                false)
                .getBoolean(ZeroConfService.IPv4, true);
        bool useIPv6 = ProfileUtils.getPreferences(ProfileManager.getDefault().getActiveProfile(),
                ZeroConfService.class,
                false)
                .getBoolean(ZeroConfService.IPv6, true);
        for (JmDNS netService : ZeroConfService.netServices().values()) {
            ZeroConfServiceEvent event;
            ServiceInfo info;
            try {
                if (netService.getQHostAddress() instanceof Inet6Address && !useIPv6) {
                    // Skip if address is IPv6 and should not be advertised on
                    log->debug("Ignoring IPv6 address {}", netService.getQHostAddress().getHostAddress());
                    continue;
                }
                if (netService.getQHostAddress() instanceof Inet4Address && !useIPv4) {
                    // Skip if address is IPv4 and should not be advertised on
                    log->debug("Ignoring IPv4 address {}", netService.getQHostAddress().getHostAddress());
                    continue;
                }
                try {
                    log->debug("Publishing ZeroConfService for '{}' on {}", key(), netService.getQHostAddress().getHostAddress());
                } catch (IOException ex) {
                    log->debug("Publishing ZeroConfService for '{}' with IOException {}", key(), ex.getLocalizedMessage(), ex);
                }
                // JmDNS requires a 1-to-1 mapping of serviceInfo to QHostAddress
                if (!this->serviceInfos.containsKey(netService.getQHostAddress())) {
                    try {
                        info = this->serviceInfo();
                        netService.registerService(info);
                        log->debug("Register service '{}' on {} successful.", this->key(), netService.getQHostAddress().getHostAddress());
                    } catch (IllegalStateException ex) {
                        // thrown if the reference serviceInfo object is in use
                        try {
                            log->debug("Initial attempt to register '{}' on {} failed.", this->key(), netService.getQHostAddress().getHostAddress());
                            info = this->addServiceInfo(netService);
                            log->debug("Retrying register '{}' on {}.", this->key(), netService.getQHostAddress().getHostAddress());
                            netService.registerService(info);
                        } catch (IllegalStateException ex1) {
                            // thrown if service gets registered on interface by
                            // the networkListener before this loop on interfaces
                            // completes, so we only ensure a later notification
                            // is not posted continuing to next interface in list
                            log->debug("'{}' is already registered on {}.", this->key(), netService.getQHostAddress().getHostAddress());
                            continue;
                        }
                    }
                } else {
                    log->debug("skipping '{}' on {}, already in serviceInfos.", this->key(), netService.getQHostAddress().getHostAddress());
                }
                event = new ZeroConfServiceEvent(this, netService);
            } catch (IOException ex) {
                log->error("Unable to publish service for '{}': {}", key(), ex.getMessage());
                continue;
            }
            this->listeners.stream().forEach((listener) -> {
                listener.servicePublished(event);
            });
        }
    }
}

/**
 * Stop advertising the service.
 */
/*public*/ void stop() {
    log->debug("Stopping ZeroConfService {}", this->key());
    if (ZeroConfService.services().containsKey(this->key())) {
        ZeroConfService.netServices().values().stream().forEach((netService) -> {
            try {
                try {
                    log->debug("Unregistering {} from {}", this->key(), netService.getQHostAddress());
                    netService.unregisterService(this->serviceInfos.get(netService.getQHostAddress()));
                    this->serviceInfos.remove(netService.getQHostAddress());
                    this->listeners.stream().forEach((listener) -> {
                        listener.serviceUnpublished(new ZeroConfServiceEvent(this, netService));
                    });
                } catch (NullPointerException ex) {
                    log->debug("{} already unregistered from {}", this->key(), netService.getQHostAddress());
                }
            } catch (IOException ex) {
                log->error("Unable to stop ZeroConfService {}. {}", this->key(), ex.getLocalizedMessage());
            }
        });
        ZeroConfService.services().remove(key());
    }
}

/**
 * Stop advertising all services.
 */
/*public*/ static void stopAll() {
    ZeroConfService.stopAll(false);
}

/*private*/ static void stopAll(/*final*/ bool close) {
    log->debug("Stopping all ZeroConfServices");
    CountDownLatch zcLatch = new CountDownLatch(ZeroConfService.services().size());
    new QMap<>(ZeroConfService.services()).values().parallelStream().forEach(service -> {
        service.stop();
        zcLatch.countDown();
    });
    try {
        zcLatch.await();
    } catch (InterruptedException ex) {
        log->warn("ZeroConfService stop threads interrupted.", ex);
    }
    CountDownLatch nsLatch = new CountDownLatch(ZeroConfService.netServices().size());
    new QMap<>(ZeroConfService.netServices()).values().parallelStream().forEach((netService) -> {
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
}

/**
 * A list of published ZeroConfServices
 *
 * @return Collection of ZeroConfServices
 */
/*public*/ static Collection<ZeroConfService> allServices() {
    return ZeroConfService.services().values();
}

/* return a list of published services */
/*private*/ static QMap<String, ZeroConfService> services() {
    return ZeroConfService.services;
}

/**
 * The list of JmDNS handlers.
 *
 * @return a {@link java.util.QMap} of {@link javax.jmdns.JmDNS} objects,
 *         accessible by {@link java.net.QHostAddress} keys.
 */
synchronized /*public*/ static QMap<QHostAddress, JmDNS> netServices() {
    if (ZeroConfService.netServices.isEmpty()) {
        log->debug("JmDNS version: {}", JmDNS.VERSION);
        try {
            for (QHostAddress address : hostAddresses()) {
                // explicitly passing NULL since newer versions of JmDNS use passed in host
                // as hostname instead of using passed in host as fallback if real hostname
                // cannot be determined
                log->debug("Calling JmDNS.create({}, NULL)", address.getHostAddress());
                ZeroConfService.netServices.put(address, JmDNS.create(address, NULL));
            }
        } catch (IOException ex) {
            log->warn("Unable to create JmDNS with error: {}", ex.getMessage(), ex);
        }
        InstanceManager.getOptionalDefault(ShutDownManager.class).ifPresent(manager -> {
            manager.register(ZeroConfService.shutDownTask);
        });
    }
    return new QMap<>(ZeroConfService.netServices);
}

/**
 * Return the system name or "computer" if the system name cannot be
 * determined. This method returns the first part of the fully qualified
 * domain name from {@link #FQDN}.
 *
 * @param address The {@link java.net.QHostAddress} for the host name.
 * @return The hostName associated with the first interface encountered.
 */
/*public*/ static String hostName(QHostAddress address) {
    String hostName = ZeroConfService.FQDN(address) + ".";
    // we would have to check for the existance of . if we did not add .
    // to the string above.
    return hostName.substring(0, hostName.indexOf('.'));
}

/**
 * Return the fully qualified domain name or "computer" if the system name
 * cannot be determined. This method uses the
 * {@link javax.jmdns.JmDNS#getHostName()} method to get the name.
 *
 * @param address The {@link java.net.QHostAddress} for the FQDN.
 * @return The fully qualified domain name.
 */
/*public*/ static String FQDN(QHostAddress address) {
    return ZeroConfService.netServices().get(address).getHostName();
}

/**
 * A list of the non-loopback, non-link-local IP addresses of the host, or
 * NULL if none found.
 *
 * @return The non-loopback, non-link-local IP addresses on the host.
 */
/*public*/ static List<QHostAddress> hostAddresses() {
    List<QHostAddress> addrList = new ArrayList<>();
    Enumeration<NetworkInterface> IFCs = NULL;
    try {
        IFCs = NetworkInterface.getNetworkInterfaces();
    } catch (SocketException ex) {
        log->error("Unable to get network interfaces.", ex);
    }
    if (IFCs != NULL) {
        while (IFCs.hasMoreElements()) {
            NetworkInterface IFC = IFCs.nextElement();
            try {
                if (IFC.isUp()) {
                    Enumeration<QHostAddress> addresses = IFC.getQHostAddresses();
                    while (addresses.hasMoreElements()) {
                        QHostAddress address = addresses.nextElement();
                        if (!address.isLoopbackAddress() && !address.isLinkLocalAddress()) {
                            addrList.add(address);
                        }
                    }
                }
            } catch (SocketException ex) {
                log->error("Unable to read network interface {}.", IFC.toString(), ex);
            }
        }
    }
    return addrList;
}

/*public*/ void addEventListener(ZeroConfServiceListener l) {
    this->listeners.add(l);
}

/*public*/ void removeEventListener(ZeroConfServiceListener l) {
    this->listeners.remove(l);
}

/*private*/ static class NetworkListener implements NetworkTopologyListener {

    //@Override
    /*public*/ void inetAddressAdded(NetworkTopologyEvent nte) {
        if (nte.getQHostAddress() instanceof Inet6Address
                && !ProfileUtils.getPreferences(ProfileManager.getDefault().getActiveProfile(),
                        ZeroConfService.class,
                        false)
                .getBoolean(ZeroConfService.IPv6, true)) {
            log->debug("Ignoring IPv6 address {}", nte.getQHostAddress().getHostAddress());
            return;
        }
        if (nte.getQHostAddress() instanceof Inet4Address
                && !ProfileUtils.getPreferences(ProfileManager.getDefault().getActiveProfile(),
                        ZeroConfService.class,
                        false)
                .getBoolean(ZeroConfService.IPv4, true)) {
            log->debug("Ignoring IPv4 address {}", nte.getQHostAddress().getHostAddress());
            return;
        }
        if (!ZeroConfService.netServices.containsKey(nte.getQHostAddress())) {
            log->debug("Adding address {}", nte.getQHostAddress().getHostAddress());
            ZeroConfService.netServices.put(nte.getQHostAddress(), nte.getDNS());
            ZeroConfService.allServices().stream().forEach((service) -> {
                try {
                    if (!service.serviceInfos.containsKey(nte.getDNS().getQHostAddress())) {
                        log->debug("Publishing zeroConf service for '{}' on {}", service.key(), nte.getQHostAddress().getHostAddress());
                        nte.getDNS().registerService(service.addServiceInfo(nte.getDNS()));
                        service.listeners.stream().forEach((listener) -> {
                            listener.servicePublished(new ZeroConfServiceEvent(service, nte.getDNS()));
                        });
                    }
                } catch (IOException ex) {
                    log->error(ex.getLocalizedMessage(), ex);
                }
            });
        } else {
            log->debug("Address {} already known.", nte.getQHostAddress().getHostAddress());
        }
    }

    //@Override
    /*public*/ void inetAddressRemoved(NetworkTopologyEvent nte) {
        log->debug("Removing address {}", nte.getQHostAddress().toString());
        ZeroConfService.netServices.remove(nte.getQHostAddress());
        nte.getDNS().unregisterAllServices();
        ZeroConfService.allServices().stream().map((service) -> {
            service.serviceInfos.remove(nte.getQHostAddress());
            return service;
        }).forEach((service) -> {
            service.listeners.stream().forEach((listener) -> {
                listener.servicePublished(new ZeroConfServiceEvent(service, nte.getDNS()));
            });
        });
    }

}

/*private*/ static class ShutDownTask extends QuietShutDownTask {

    /*private*/ bool isComplete = false;

    /*public*/ ShutDownTask(String name) {
        super(name);
    }

    //@Override
    /*public*/ bool execute() {
        new Thread(() -> {
            Date start = new Date();
            log->debug("Starting to stop services...");
            ZeroConfService.stopAll(true);
            log->debug("Stopped all services in {} milliseconds", new Date().getTime() - start.getTime());
            start = new Date();
            JmmDNS.Factory.getInstance().removeNetworkTopologyListener(ZeroConfService.networkListener);
            log->debug("Removed network topology listener in {} milliseconds", new Date().getTime() - start.getTime());
            this->isComplete = true;
        }).start();
        return true;
    }

    //@Override
    /*public*/ bool isParallel() {
        return true;
    }

    //@Override
    /*public*/ bool isComplete() {
        return this->isComplete;
    }
}
}
#endif
