#include "zeroconfclient.h"
#include "loggerfactory.h"
#include "qzeroconf.h"

ZeroConfClient::ZeroConfClient(QObject *parent) : QObject(parent)
{

}

///*public*/ class ZeroConfClient {

/*private*/ /*final*/ /*static*/ Logger* ZeroConfClient::log = LoggerFactory::getLogger("ZeroConfClient");

// mdns related routines.
/*public*/ void ZeroConfClient::startServiceListener(/*@Nonnull*/ QString service) {
    log->debug(tr("StartServiceListener called for service: %1").arg(service));
    if (mdnsServiceListener == nullptr) {
        mdnsServiceListener = new NetworkServiceListener(service, this);
    }
#if 0
    for (JmDNS server : ZeroConfService.netServices().values()) {
        server.addServiceListener(service, mdnsServiceListener);
    }
#endif
}
#if 0
/*public*/ void stopServiceListener(@Nonnull String service) {
    for (JmDNS server : ZeroConfService.netServices().values()) {
        server.removeServiceListener(service, mdnsServiceListener);
    }
}

/**
 * Request the first service of a particular service.
 *
 * @param service string service name
 * @return JmDNS service entry for the first service of a particular
 *         service.
 */
/*public*/ ServiceInfo getService(@Nonnull String service) {
    for (JmDNS server : ZeroConfService.netServices().values()) {
        ServiceInfo[] infos = server.list(service);
        if (infos != null) {
            return infos[0];
        }
    }
    return null;
}

/**
 * Get all servers providing the specified service.
 *
 * @param service the name of service as generated using
 *                {@link ZeroConfService#key(java.lang.String, java.lang.String)}
 * @return A list of servers or an empty list.
 */
@Nonnull
/*public*/ List<ServiceInfo> getServices(@Nonnull String service) {
    ArrayList<ServiceInfo> services = new ArrayList<ServiceInfo>();
    for (JmDNS server : ZeroConfService.netServices().values()) {
        if (server.list(service) != null) {
            services.addAll(Arrays.asList(server.list(service)));
        }
    }
    return services;
}
#endif
#if 0
/**
 * Request the first service of a particular service on a specified host.
 *
 * @param service  string service service
 * @param hostname string host name
 * @return JmDNS service entry for the first service of a particular service
 *         on the specified host..
 */
/*public*/ ServiceInfo getServiceOnHost(/*@Nonnull*/ QString service, /*@Nonnull*/ QString hostname) {
    for (JmDNS server : ZeroConfService.netServices().values()) {
        ServiceInfo[] infos = server.list(service);
        for (ServiceInfo info : infos) {
            if (info.getServer().equals(hostname)) {
                return info;
            }
        }
    }
    return null;
}
#endif
#if 0
/**
 * Request the first service of a particular service with a particular
 * service name.
 *
 * @param service string service service
 * @param adName  string qualified service advertisement name
 * @return JmDNS service entry for the first service of a particular service
 *         on the specified host..
 */
/*public*/ ServiceInfo getServicebyAdName(@Nonnull String service, @Nonnull String adName) {
    for (JmDNS server : ZeroConfService.netServices().values()) {
        ServiceInfo[] infos = server.list(service);
        for (ServiceInfo info : infos) {
            log.debug("Found Name: {}", info.getQualifiedName());
            if (info.getQualifiedName().equals(adName)) {
                return info;
            }
        }
    }
    return null;
}

@Nonnull
/*public*/ String[] getHostList(@Nonnull String service) {
    ArrayList<String> hostlist = new ArrayList<String>();
    for (JmDNS server : ZeroConfService.netServices().values()) {
        ServiceInfo[] infos = server.list(service);
        for (ServiceInfo info : infos) {
            hostlist.add(info.getServer());
        }
    }
    return hostlist.toArray(new String[hostlist.size()]);
}
#endif
///*public*/ static class NetworkServiceListener implements ServiceListener, NetworkTopologyListener {

//    private final String service;
//    private final ZeroConfClient client;

/*protected*/ NetworkServiceListener::NetworkServiceListener(QString service, ZeroConfClient* client) {
    this->service = service;
    this->client = client;
 zeroConf = new QZeroConf();
 connect(zeroConf, SIGNAL(serviceAdded(QZeroConfService)), this, SLOT(serviceAdded(QZeroConfService)));
 connect(zeroConf, SIGNAL(serviceRemoved(QZeroConfService)), this, SLOT(serviceRemoved(QZeroConfService)));

}
#if 0
@Override
/*public*/ void inetAddressAdded(NetworkTopologyEvent nte) {
    nte.getDNS().addServiceListener(service, this);
}

@Override
/*public*/ void inetAddressRemoved(NetworkTopologyEvent nte) {
    nte.getDNS().removeServiceListener(service, this);
}

#endif
//@Override
/*public*/ void NetworkServiceListener::serviceAdded(QZeroConfService se) {
    client->log->debug(tr("Service added: %1").arg(se.name()));
    // notify the client when a service is added.
  #if 0
    /*synchronized(client)*/ {
        client->notifyAll();
    }
#endif
}

//@Override
/*public*/ void NetworkServiceListener::serviceRemoved(QZeroConfService se) {
    client->log->debug(tr("Service removed: %1").arg(se.name()));
}
#if 0
@Override
/*public*/ void serviceResolved(ServiceEvent se) {
    log.debug("Service resolved: {}", se.getInfo().toString());
}

//}
//}
#endif
