#include "networkdriveradapter.h"
#include "loggerfactory.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclienttrafficcontroller.h"


/**
 * Implements NetworkPortAdapter for the jmriclient system network connection.
 * <P>
 * This connects a JMRI server (daemon) via a telnet connection.
 *
 * @author Paul Bender Copyright (C) 2010
 */
// /*public*/ class NetworkDriverAdapter extends JMRIClientPortController {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrix.jmriclient.JMRIClientConfigurationBundle");

/*public*/ NetworkDriverAdapter::NetworkDriverAdapter(QObject *parent)
 : JMRIClientPortController(new JMRIClientSystemConnectionMemo(), parent)
{
 //super(new JMRIClientSystemConnectionMemo());
 setObjectName("NetworkDriverAdapter");
 setPort(2048); // set the default port on construction
}

/**
 * set up all of the other objects to operate with an JMRI server connected
 * to this port
 */
//@Override
/*public*/ void NetworkDriverAdapter::configure() {
    // connect to the traffic controller
    JMRIClientTrafficController* control = new JMRIClientTrafficController();
    control->connectPort(this);
    ((JMRIClientSystemConnectionMemo*)this->getSystemConnectionMemo())->setJMRIClientTrafficController(control);
    ((JMRIClientSystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagers();
}

//@Override
/*public*/ bool NetworkDriverAdapter::status() {
    return opened;
}


//@Deprecated
/*static*/ /*public*/ NetworkDriverAdapter* NetworkDriverAdapter::instance() {
    log->error("Deprecated method instance Called"/*, new Exception()*/);
    return nullptr;
}


/*
 * Set whether or not this adapter should be
 * configured automatically via MDNS.
 * @param autoconfig boolean value.
 */
//@Override
/*public*/ void NetworkDriverAdapter::setMdnsConfigure(bool autoconfig) {
    log->debug(tr("Setting LIUSB Ethernet adapter autoconfiguration to: ")
            + (autoconfig?"true":"false"));
    mDNSConfigure = autoconfig;
}

/*
 * Get whether or not this adapter is configured
 * to use autoconfiguration via MDNS
 * @return true if configured using MDNS.
 */
//@Override
/*public*/ bool NetworkDriverAdapter::getMdnsConfigure() {
    return mDNSConfigure;
}

/*
 * set the server's host name and port
 * using mdns autoconfiguration.
 */
//@Override
/*public*/ void NetworkDriverAdapter::autoConfigure() {
    log->info("Configuring JMRIClient interface via JmDNS");
    if (getHostName() == (tr("localhost"))) {
        setHostName(""); // reset the hostname to none.
    }
    QString serviceType = tr("_jmri-simple._tcp.local.");
    log->debug("Listening for service: " + serviceType);
#if 0
    if (mdnsClient == nullptr) {
        mdnsClient = new ZeroConfClient();
        mdnsClient.startServiceListener(serviceType);
    }
    try {
        // if there is a hostname set, use the host name (which can
        // be changed) to find the service.
        String qualifiedHostName = m_HostName
                + "." + rb.getString("defaultMDNSDomainName");
        setHostAddress(mdnsClient.getServiceOnHost(serviceType,
                qualifiedHostName).getHostAddresses()[0]);
    } catch (java.lang.NullPointerException npe) {
        // if there is no hostname set, use the service name (which can't
        // be changed) to find the service.
        String qualifiedServiceName = rb.getString("defaultMDNSServiceName")
                + "." + serviceType;
        setHostAddress(mdnsClient.getServicebyAdName(serviceType,
                qualifiedServiceName).getHostAddresses()[0]);
    }
#endif
}

/*
 * Get the ZeroConf/mDNS advertisement name.
 * this value is fixed on the LIUSB-Ethernet, so return the default
 * value.
 */
//@Override
/*public*/ QString NetworkDriverAdapter::getAdvertisementName() {
    return tr("My JMRI Railroad");
}

/*
 * Get the ZeroConf/mDNS service type.
 * this value is fixed on the LIUSB-Ethernet, so return the default
 * value.
 */
//@Override
/*public*/ QString NetworkDriverAdapter::getServiceType() {
    return tr("_jmri-simple._tcp.local.");
}

/*private*/ /*final*/ /*static*/ Logger* NetworkDriverAdapter::log = LoggerFactory::getLogger("NetworkDriverAdapter");

