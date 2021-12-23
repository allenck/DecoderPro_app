#include "zeroconfservicemanager.h"
#include "loggerfactory.h"
#include "webserverpreferences.h"
#include "instancemanager.h"
#include "nodeidentity.h"
#include "version.h"
#include "qzeroconfservice.h"
#include "inetaddress.h"
#include "inet6address.h"
#include "inet4address.h"

ZeroConfServiceManager::ZeroConfServiceManager(QObject *parent) : QObject(parent)
{
 networkListener = new NetworkListener(this);
 shutDownTask = new ZCSMShutDownTask(this);

}
/**
 * A ZeroConfServiceManager object manages zeroConf network service
 * advertisements.
 * <p>
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
 * the default path (for a web server), a specific protocol version, or other
 * information. Note that all service advertisements include the JMRI version,
 * using the key "version", and the JMRI version numbers in a string
 * "major.minor.test" with the key "jmri"
 * <p>
 * All ZeroConfServices are published with the computer's hostname as the mDNS
 * hostname (unless it cannot be determined by JMRI), as well as the JMRI node
 * name in the TXT record with the key "node".
 * <p>
 * All ZeroConfServices are automatically stopped when the JMRI application
 * shuts down. Use {@link #allServices() } to get a collection of all published
 * ZeroConfService objects.
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 * <p>
 *
 * @author Randall Wood Copyright (C) 2011, 2013, 2018
 * @see javax.jmdns.JmDNS
 * @see javax.jmdns.ServiceInfo
 */
///*public*/ class ZeroConfServiceManager implements InstanceManagerAutoDefault, Disposable {

    // static data objects
    /**
     * There can only be <strong>one</strong> {@link javax.jmdns.JmDNS} object
     * per {@link java.net.InetAddress} per JVM, so this collection of JmDNS
     * objects is static. All access <strong>must</strong> be through
     * {@link #getDNSes() } to ensure this is populated correctly.
     */
    /*protected*/ /*static*/ /*final*/ QHash<InetAddress*, JmDNS*> ZeroConfServiceManager::JMDNS_SERVICES = QHash<InetAddress*, JmDNS*>();
    /*private*/ /*static*/ /*final*/ Logger* ZeroConfServiceManager::log = LoggerFactory::getLogger("ZeroConfServiceManager");
    // class data objects

    /**
     * Create a ZeroConfService with the minimal required settings. This method
     * calls {@link #create(java.lang.String, int, java.util.HashMap)} with an
     * empty props HashMap.
     *
     * @param type The service protocol
     * @param port The port the service runs over
     * @return A new unpublished ZeroConfService, or an existing service
     * @see #create(java.lang.String, java.lang.String, int, int, int,
     * java.util.HashMap)
     */
    /*public*/ ZeroConfService* ZeroConfServiceManager::create(QString type, int port) {
        return create(type, port, new QMap<QString, QString>());
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
     * @return A new unpublished ZeroConfService, or an existing service
     */
    /*public*/ ZeroConfService* ZeroConfServiceManager::create(QString type, int port, QMap<QString, QString>* properties) {
        return create(type, ((WebServerPreferences*)InstanceManager::getDefault("WebServerPreferences"))->getRailroadName(), port, 0, 0, properties);
    }

    /**
     * Create a ZeroConfService. The property <i>version</i> is added or
     * replaced with the current JMRI version as its value. The property
     * <i>jmri</i> is added or replaced with the JMRI major.minor.test version
     * string as its value.
     * <p>
     * If a service with the same getKey as the new service is already
     * published, the original service is returned unmodified.
     *
     * @param type       The service protocol
     * @param name       The name of the JMRI server listed on client devices
     * @param port       The port the service runs over
     * @param weight     Default value is 0
     * @param priority   Default value is 0
     * @param properties Additional information to be listed in service
     *                   advertisement
     * @return A new unpublished ZeroConfService, or an existing service
     */
    /*public*/ ZeroConfService* ZeroConfServiceManager::create(QString type, QString name, int port, int weight, int priority, QMap<QString, QString>* properties) {
        ZeroConfService* s;
        QString _key = key(type, name);
        if (services.contains(_key)) {
            s = services.value(_key);
            log->debug(tr("Using existing ZeroConfService %1").arg(s->key()));
        } else {
            properties->insert("version", Version::name());
            // use the major.minor.test version string for jmri since we have potentially
            // tight space constraints in terms of the number of bytes that properties
            // can use, and there are some unconstrained properties that we would like to use.
            properties->insert("jmri", Version::getCanonicalVersion());
            properties->insert("node", NodeIdentity::networkIdentity());
#if 0
            s = new ZeroConfService(ServiceInfo::create(type, name, port, weight, priority, properties));
#endif
            log->debug(tr("Creating new ZeroConfService %1 with properties %2").arg(s->key()).arg(properties->count()));
        }
        return s;
    }

    /**
     * Generate a ZeroConfService getKey for searching in the HashMap of running
     * services.
     *
     * @param type the service type (usually a protocol name or mapping)
     * @param name the service name (usually the JMRI railroad name or system
     *             host name)
     * @return The combination of the name and type of the service.
     */
    /*protected*/ QString ZeroConfServiceManager::key(QString type, QString name) {
        return (name + "." + type).toLower();
    }

    /**
     * Start advertising the service.
     *
     * @param service The service to publish
     */
    /*public*/ void ZeroConfServiceManager::publish(ZeroConfService* service) {
        if (!isPublished(service)) {
            //get current preference values
            services.insert(service->key(), service);
#if 0
            service->getListeners().stream().forEach((listener) -> {
                listener.serviceQueued(new ZeroConfServiceEvent(service, null));
            });
            for (JmDNS dns : getDNSes().values()) {
                ZeroConfServiceEvent event;
                ServiceInfo info;
                try {
                    /*final*/ InetAddress address = dns.getInetAddress();
                    if (address instanceof Inet6Address && !preferences.isUseIPv6()) {
                        // Skip if address is IPv6 and should not be advertised on
                        log.debug("Ignoring IPv6 address {}", address.getHostAddress());
                        continue;
                    }
                    if (address instanceof Inet4Address && !preferences.isUseIPv4()) {
                        // Skip if address is IPv4 and should not be advertised on
                        log.debug("Ignoring IPv4 address {}", address.getHostAddress());
                        continue;
                    }
                    if (address.isLinkLocalAddress() && !preferences.isUseLinkLocal()) {
                        // Skip if address is LinkLocal and should not be advertised on
                        log.debug("Ignoring link-local address {}", address.getHostAddress());
                        continue;
                    }
                    if (address.isLoopbackAddress() && !preferences.isUseLoopback()) {
                        // Skip if address is loopback and should not be advertised on
                        log.debug("Ignoring loopback address {}", address.getHostAddress());
                        continue;
                    }
                    log.debug("Publishing ZeroConfService for '{}' on {}", service.getKey(), address.getHostAddress());
                    // JmDNS requires a 1-to-1 mapping of getServiceInfo to InetAddress
                    if (!service.containsServiceInfo(address)) {
                        try {
                            info = service.addServiceInfo(address);
                            dns.registerService(info);
                            log.debug("Register service '{}' on {} successful.", service.getKey(), address.getHostAddress());
                        } catch (IllegalStateException ex) {
                            // thrown if the reference getServiceInfo object is in use
                            try {
                                log.debug("Initial attempt to register '{}' on {} failed.", service.getKey(), address.getHostAddress());
                                info = service.addServiceInfo(address);
                                log.debug("Retrying register '{}' on {}.", service.getKey(), address.getHostAddress());
                                dns.registerService(info);
                            } catch (IllegalStateException ex1) {
                                // thrown if service gets registered on interface by
                                // the networkListener before this loop on interfaces
                                // completes, so we only ensure a later notification
                                // is not posted continuing to next interface in list
                                log.debug("'{}' is already registered on {}.", service.getKey(), address.getHostAddress());
                                continue;
                            }
                        }
                    } else {
                        log.debug("skipping '{}' on {}, already in serviceInfos.", service.getKey(), address.getHostAddress());
                    }
                    event = new ZeroConfServiceEvent(service, dns);
                } catch (IOException* ex) {
                    log.error("Unable to publish service for '{}': {}", service.getKey(), ex.getMessage());
                    continue;
                }
                service.getListeners().stream().forEach((listener) -> {
                    listener.servicePublished(event);
                });
            }
#endif
        }
    }

    /**
     * Stop advertising the service.
     *
     * @param service The service to stop advertising
     */
    /*public*/ void ZeroConfServiceManager::stop(ZeroConfService* service) {
        log->debug(tr("Stopping ZeroConfService %1").arg(service->key()));
#if 0
        if (services.containsKey(service.getKey())) {
            getDNSes().values().parallelStream().forEach((dns) -> {
                try {
                    /*final*/ InetAddress address = dns.getInetAddress();
                    try {
                        log.debug("Unregistering {} from {}", service.getKey(), address);
                        dns.unregisterService(service.getServiceInfo(address));
                        service.removeServiceInfo(address);
                        service.getListeners().stream().forEach((listener) -> {
                            listener.serviceUnpublished(new ZeroConfServiceEvent(service, dns));
                        });
                    } catch (NullPointerException* ex) {
                        log.debug("{} already unregistered from {}", service.getKey(), address);
                    }
                } catch (IOException* ex) {
                    log.error("Unable to stop ZeroConfService {}. {}", service.getKey(), ex.getLocalizedMessage());
                }
            });
            services.remove(service.getKey());
        }
#endif
    }

    /**
     * Stop advertising all services.
     */
    /*public*/ void ZeroConfServiceManager::stopAll() {
        stopAll(false);
    }

    /*private*/ void ZeroConfServiceManager::stopAll(/*final*/ bool close) {
        log->debug("Stopping all ZeroConfServices");
#if 0
        CountDownLatch zcLatch = new CountDownLatch(services.size());
        new HashMap<>(services).values().parallelStream().forEach(service -> {
            stop(service);
            zcLatch.countDown();
        });
        try {
            zcLatch.await();
        } catch (InterruptedException ex) {
            log.warn("ZeroConfService stop threads interrupted.", ex);
        }
        CountDownLatch nsLatch = new CountDownLatch(getDNSes().size());
        new HashMap<>(getDNSes()).values().parallelStream().forEach(dns -> {
            new Thread(() -> {
                dns.unregisterAllServices();
                if (close) {
                    try {
                        dns.close();
                    } catch (IOException* ex) {
                        log.debug("jmdns.close() returned IOException: {}", ex.getMessage());
                    }
                }
                nsLatch.countDown();
            }, "dns.close in ZeroConfServiceManager#stopAll").start();
        });
        try {
            zcLatch.await();
        } catch (InterruptedException ex) {
            log.warn("JmDNS unregister threads interrupted.", ex);
        }
        services.clear();
#endif
    }
#if 0
    /**
     * A list of published ZeroConfServices
     *
     * @return Collection of ZeroConfServices
     */
    /*public*/ Collection<ZeroConfService> allServices() {
        return services.values();
    }

    /**
     * The list of JmDNS handlers. This is package private.
     *
     * @return a {@link java.util.HashMap} of {@link javax.jmdns.JmDNS} objects,
     *         accessible by {@link java.net.InetAddress} keys.
     */
    /*synchronized*/ HashMap<InetAddress, JmDNS> getDNSes() {
        if (JMDNS_SERVICES.isEmpty()) {
            log.debug("JmDNS version: {}", JmDNS.VERSION);
            String name = hostName(NodeIdentity.networkIdentity());
            try {
                Enumeration<NetworkInterface> nis = NetworkInterface.getNetworkInterfaces();
                while (nis.hasMoreElements()) {
                    NetworkInterface ni = nis.nextElement();
                    try {
                        if (ni.isUp()) {
                            Enumeration<InetAddress> niAddresses = ni.getInetAddresses();
                            while (niAddresses.hasMoreElements()) {
                                InetAddress address = niAddresses.nextElement();
                                // explicitly pass a valid host name, since null causes a very long lookup on some networks
                                log.debug("Calling JmDNS.create({}, '{}')", address.getHostAddress(), name);
                                try {
                                    JMDNS_SERVICES.put(address, JmDNS.create(address, name));
                                } catch (IOException* ex) {
                                    log.warn("Unable to create JmDNS with error: {}", ex.getMessage(), ex);
                                }
                            }
                        }
                    } catch (SocketException ex) {
                        log.error("Unable to read network interface {}.", ni, ex);
                    }
                }
            } catch (SocketException ex) {
                log.error("Unable to get network interfaces.", ex);
            }
            InstanceManager.getDefault(ShutDownManager.class).register(shutDownTask);
        }
        return new HashMap<>(JMDNS_SERVICES);
    }

    /**
     * Get all addresses that JmDNS instances can be created for excluding
     * loopback addresses.
     *
     * @return the addresses
     * @see #getAddresses(jmri.util.zeroconf.ZeroConfServiceManager.Protocol)
     * @see #getAddresses(jmri.util.zeroconf.ZeroConfServiceManager.Protocol,
     * boolean, boolean)
     */
    @Nonnull
    /*public*/ Set<InetAddress> getAddresses() {
        return getAddresses(Protocol.All);
    }

    /**
     * Get all addresses that JmDNS instances can be created for excluding
     * loopback addresses.
     *
     * @param protocol the Internet protocol
     * @return the addresses
     * @see #getAddresses()
     * @see #getAddresses(jmri.util.zeroconf.ZeroConfServiceManager.Protocol,
     * boolean, boolean)
     */
    @Nonnull
    /*public*/ Set<InetAddress> getAddresses(Protocol protocol) {
        return getAddresses(protocol, true, false);
    }

    /**
     * Get all addresses of a specific IP protocol that JmDNS instances can be
     * created for.
     *
     * @param protocol     the IP protocol addresses to return
     * @param useLinkLocal true to include link-local addresses; false otherwise
     * @param useLoopback  true to include loopback addresses; false otherwise
     * @return the addresses
     * @see #getAddresses()
     * @see #getAddresses(jmri.util.zeroconf.ZeroConfServiceManager.Protocol)
     */
    @Nonnull
    /*public*/ Set<InetAddress> getAddresses(Protocol protocol, boolean useLinkLocal, boolean useLoopback) {
        Set<InetAddress> set = new HashSet<>();
        if (protocol == Protocol.All) {
            set.addAll(getDNSes().keySet());
        } else {
            getDNSes().keySet().forEach((address) -> {
                if (address instanceof Inet4Address && protocol == Protocol.IPv4) {
                    set.add(address);
                }
                if (address instanceof Inet6Address && protocol == Protocol.IPv6) {
                    set.add(address);
                }
            });
        }
        if (!useLinkLocal || !useLoopback) {
            new HashSet<>(set).forEach((address) -> {
                if ((address.isLinkLocalAddress() && !useLinkLocal)
                        || (address.isLoopbackAddress() && !useLoopback)) {
                    set.remove(address);
                }
            });
        }
        return set;
    }

    /**
     * Return an RFC 1123 compliant host name in all lower-case punycode from a
     * given string.
     * <p>
     * RFC 1123 mandates that host names contain only the ASCII characters a-z, digits,
     * minus signs ("-") and that the host name be not longer than 63 characters.
     * <p>
     * Punycode converts non-ASCII characters into an ASCII encoding per RFC 3492, so
     * this method repeatedly converts the name into punycode, shortening the name, until
     * the punycode converted name is 63 characters or less in length.
     * <p>
     * If the input string cannot be converted to puny code, or is an empty string,
     * the input is replaced with {@link jmri.util.node.NodeIdentity#networkIdentity()}.
     * <p>
     * The algorithm for converting the input is:
     * <ol>
     * <li>Convert to lower case using the {@link java.util.Locale#ROOT} locale.</li>
     * <li>Remove any leading whitespace, dots ("."), underscores ("_"), and minus signs ("-")</li>
     * <li>Truncate to 63 characters if necessary</li>
     * <li>Convert whitespace, dots ("."), and underscores ("_") to minus signs ("-")</li>
     * <li>Repeatedly convert to punycode, removing the last character as needed until
     * the punycode is 63 characters or less</li>
     * <li>Repeat process with NodeIdentity#networkIdentity() as input if above never
     * yields a usable host name</li>
     * </ol>
     *
     * @param string String to convert to host name
     * @return An RFC 1123 compliant host name
     */
    @Nonnull
    /*public*/ static String hostName(@Nonnull String string) {
        String puny = null;
        String name = string.toLowerCase(Locale.ROOT);
        name = name.replaceFirst("^[_\\.\\s]+", "");
        if (string.isEmpty()) {
            name = NodeIdentity.networkIdentity();
        }
        if (name.length() > 63) {
            name = name.substring(0, 63);
        }
        name = name.replaceAll("[_\\.\\s]", "-");
        while (puny == null || puny.length() > 63) {
            log.debug("name is \"{}\" prior to conversion", name);
            try {
                puny = IDN.toASCII(name, IDN.ALLOW_UNASSIGNED);
                if (puny.isEmpty()) {
                    name = NodeIdentity.networkIdentity();
                    puny = null;
                }
            } catch (IllegalArgumentException* ex) {
                puny = null;
            }
            if (name.length() > 1) {
                name = name.substring(0, name.length() - 2);
            } else {
                name = NodeIdentity.networkIdentity();
            }
        }
        return puny;
    }

    /**
     * Return the system name or "computer" if the system name cannot be
     * determined. This method returns the first part of the fully qualified
     * domain name from {@link #FQDN}.
     *
     * @param address The {@link java.net.InetAddress} for the host name.
     * @return The hostName associated with the first interface encountered.
     */
    /*public*/ QString hostName(InetAddress address) {
        String hostName = FQDN(address) + ".";
        // we would have to check for the existence of . if we did not add .
        // to the string above.
        return hostName.substring(0, hostName.indexOf('.'));
    }

    /**
     * Return the fully qualified domain name or "computer" if the system name
     * cannot be determined. This method uses the
     * {@link javax.jmdns.JmDNS#getHostName()} method to get the name.
     *
     * @param address The {@link java.net.InetAddress} for the FQDN.
     * @return The fully qualified domain name.
     */
    /*public*/ QString FQDN(InetAddress address) {
        return getDNSes().get(address).getHostName();
    }

    /*public*/ ZeroConfPreferences* getPreferences() {
        return preferences;
    }
#endif
    /*public*/ bool ZeroConfServiceManager::isPublished(ZeroConfService* service) {
        return services.contains(service->key());
    }
    //@Override
    /*public*/ void ZeroConfServiceManager::dispose() {
        dispose(this);
        ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->deregister(shutDownTask);
    }

    /*private*/ /*static*/ void ZeroConfServiceManager::dispose(ZeroConfServiceManager* manager) {
#if 0
        Date start = new Date();
        JmmDNS.Factory.getInstance().removeNetworkTopologyListener(manager.networkListener);
        log.debug("Removed network topology listener in {} milliseconds", new Date().getTime() - start.getTime());
        start = new Date();
        log.debug("Starting to stop services...");
        manager.stopAll(true);
        log.debug("Stopped all services in {} milliseconds", new Date().getTime() - start.getTime());
#endif
    }

//    /*protected*/ static class NetworkListener implements NetworkTopologyListener {

//        /*private*/ /*final*/ ZeroConfServiceManager manager;

//        /*public*/ NetworkListener(ZeroConfServiceManager manager) {
//            this.manager = manager;
//        }

//@Override
/*public*/ void NetworkListener::inetAddressAdded(NetworkTopologyEvent* nte) {
    //get current preference values
    /*final*/ InetAddress* address = nte->getInetAddress();
    if (qobject_cast<Inet6Address*>(address) && !manager->preferences->isUseIPv6()) {
        manager->log->debug(tr("Ignoring IPv6 address %1").arg(address->getHostAddress()));
    } else if (qobject_cast<Inet4Address*>(address) && !manager->preferences->isUseIPv4()) {
        manager->log->debug(tr("Ignoring IPv4 address %1").arg(address->getHostAddress()));
    } else if (address->isLinkLocalAddress() && !manager->preferences->isUseLinkLocal()) {
        manager->log->debug(tr("Ignoring link-local address %1").arg(address->getHostAddress()));
    } else if (address->isLoopbackAddress() && !manager->preferences->isUseLoopback()) {
        manager->log->debug(tr("Ignoring loopback address %1").arg(address->getHostAddress()));
    } else if (!manager->JMDNS_SERVICES.contains(address)) {
        manager->log->debug(tr("Adding address %1").arg(address->getHostAddress()));
//                JmDNS dns = nte.getDNS();
//                JMDNS_SERVICES.put(address, dns);
//                manager.allServices().stream().forEach((service) -> {
//                    try {
//                        if (!service.containsServiceInfo(address)) {
//                            log.debug("Publishing zeroConf service for '{}' on {}", service.getKey(), address.getHostAddress());
//                            dns.registerService(service.addServiceInfo(address));
//                            service.getListeners().stream().forEach((listener) -> {
//                                listener.servicePublished(new ZeroConfServiceEvent(service, dns));
//                            });
//                        }
//                    } catch (IOException* ex) {
//                        log.error(ex.getLocalizedMessage(), ex);
//                    }
//                });
        //for(QZeroConfService* service : QZeroConfService::)
    } else {
        manager->log->debug(tr("Address %1 already known.").arg(address->getHostAddress()));
    }
}

//        @Override
//        /*public*/ void inetAddressRemoved(NetworkTopologyEvent nte) {
//            /*final*/ InetAddress address = nte.getInetAddress();
//            JmDNS dns = nte.getDNS();
//            log.debug("Removing address {}", address);
//            JMDNS_SERVICES.remove(address);
//            dns.unregisterAllServices();
//            manager.allServices().stream().forEach((service) -> {
//                service.removeServiceInfo(address);
//                service.getListeners().stream().forEach((listener) -> {
//                    listener.servicePublished(new ZeroConfServiceEvent(service, dns));
//                });
//            });
//        }

//    }

//    /*protected*/ static class ShutDownTask extends QuietShutDownTask {

//        /*private*/ boolean isComplete = false;
//        /*private*/ /*final*/ ZeroConfServiceManager manager;

//        /*public*/ ShutDownTask(ZeroConfServiceManager manager) {
//            super("Stop ZeroConfServices");
//            this.manager = manager;
//        }

//        @Override
//        /*public*/ boolean execute() {
//            new Thread(() -> {
//                dispose(manager);
//                this.isComplete = true;
//            }, "ZeroConfServiceManager ShutDownTask").start();
//            return true;
//        }

//        @Override
//        /*public*/ boolean isParallel() {
//            return true;
//        }

//        @Override
//        /*public*/ boolean isComplete() {
//            return this.isComplete;
//        }
//    }
