#include "serviceinfo.h"
#include "serviceinfoimpl.h"
#include "loggerfactory.h"
ServiceInfo::ServiceInfo(QObject *parent) : QObject(parent)
{

}
// Copyright 2003-2005 Arthur van Hoff, Rick Blair
// Licensed under Apache License version 2.0
// Original license LGPL
//package javax.jmdns;
//import java.net.Inet4Address;
//import java.net.Inet6Address;
//import java.net.InetAddress;
//import java.util.Enumeration;
//import java.util.Map;
//import javax.jmdns.impl.ServiceInfoImpl;
/**
 * <p>
 * The fully qualified service name is build using up to 5 components with the following structure:
 *
 * <pre>
 *            &lt;app&gt;.&lt;protocol&gt;.&lt;servicedomain&gt;.&lt;parentdomain&gt;.<br/>
 * &lt;Instance&gt;.&lt;app&gt;.&lt;protocol&gt;.&lt;servicedomain&gt;.&lt;parentdomain&gt;.<br/>
 * &lt;sub&gt;._sub.&lt;app&gt;.&lt;protocol&gt;.&lt;servicedomain&gt;.&lt;parentdomain&gt;.
 * </pre>
 *
 * <ol>
 * <li>&lt;servicedomain&gt;.&lt;parentdomain&gt;: This is the domain scope of the service typically "local.", but this can also be something similar to "in-addr.arpa." or "ip6.arpa."</li>
 * <li>&lt;protocol&gt;: This is either "_tcp" or "_udp"</li>
 * <li>&lt;app&gt;: This define the application protocol. Typical example are "_http", "_ftp", etc.</li>
 * <li>&lt;Instance&gt;: This is the service name</li>
 * <li>&lt;sub&gt;: This is the subtype for the application protocol</li>
 * </ol>
 * </p>
 */
///*public*/ /*abstract*/ class ServiceInfo implements Cloneable {
/**
 * This is the no value text byte. According top the specification it is one byte with 0 value.
 */

/*public*/ /*static*/ /*final*/ QByteArray ServiceInfo::NO_VALUE = QByteArray();

/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param port
 *            the local port on which the service runs
 * @param text
 *            string describing the service
 * @return new service info
 */
/*public*/ /*static*/ ServiceInfo* create(/*final*/ QString type, /*final*/ QString name, /*final*/ int port, /*final*/ QString text) {
    return (ServiceInfo*)new ServiceInfoImpl(type, name, "", port, 0, 0, false, text);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param subtype
 *            service subtype see draft-cheshire-dnsext-dns-sd-06.txt chapter 7.1 Selective Instance Enumeration
 * @param port
 *            the local port on which the service runs
 * @param text
 *            string describing the service
 * @return new service info
 */
/*public*/ /*static*/ ServiceInfo* ServiceInfo::create(/*final*/ QString type, /*final*/ QString name, /*final*/ QString subtype, /*final*/ int port, /*final*/ QString text) {
    return (ServiceInfo*)new ServiceInfoImpl(type, name, subtype, port, 0, 0, false, text);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param text
 *            string describing the service
 * @return new service info
 */
/*public*/ /*static*/ ServiceInfo* ServiceInfo::create(/*final*/ QString type, /*final*/ QString name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ QString text) {
    return (ServiceInfo*)new ServiceInfoImpl(type, name, "", port, weight, priority, false, text);
}

/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param subtype
 *            service subtype see draft-cheshire-dnsext-dns-sd-06.txt chapter 7.1 Selective Instance Enumeration
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param text
 *            String describing the service
 * @return new service info
 */
/*public*/ /*static*/ ServiceInfo* ServiceInfo::create(/*final*/ QString type, /*final*/ QString name, /*final*/ QString subtype, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ QString text) {
    return (ServiceInfo*)new ServiceInfoImpl(type, name, subtype, port, weight, priority, false, text);
}
/**
 * Construct a service description for registering with JmDNS. The properties hashtable must map property names to either Strings or byte arrays describing the property values.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param props
 *            properties describing the service
 * @return new service info
 */
/*public*/ /*static*/ ServiceInfo* ServiceInfo::create(/*final*/ QString type, /*final*/ QString name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ QMap</*final*/QString, QVariant> props)
{
 ServiceInfoImpl* simpl =   new ServiceInfoImpl(type, name, "", port, weight, priority, false, props);
 simpl->logger->info(simpl->toString());
return (ServiceInfo*)simpl;
}
#if 0
/**
 * Construct a service description for registering with JmDNS. The properties hashtable must map property names to either Strings or byte arrays describing the property values.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param subtype
 *            service subtype see draft-cheshire-dnsext-dns-sd-06.txt chapter 7.1 Selective Instance Enumeration
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param props
 *            properties describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ /*final*/ subtype, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ Map</*final*/, ?> props) {
    return new ServiceInfoImpl(type, name, subtype, port, weight, priority, false, props);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param text
 *            bytes describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ byte[] text) {
    return new ServiceInfoImpl(type, name, "", port, weight, priority, false, text);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param subtype
 *            service subtype see draft-cheshire-dnsext-dns-sd-06.txt chapter 7.1 Selective Instance Enumeration
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param text
 *            bytes describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ /*final*/ subtype, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ byte[] text) {
    return new ServiceInfoImpl(type, name, subtype, port, weight, priority, false, text);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param persistent
 *            if <code>true</code> ServiceListener.resolveService will be called whenever new new information is received.
 * @param text
 *            string describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ bool persistent, /*final*/ /*final*/ text) {
    return new ServiceInfoImpl(type, name, "", port, weight, priority, persistent, text);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param subtype
 *            service subtype see draft-cheshire-dnsext-dns-sd-06.txt chapter 7.1 Selective Instance Enumeration
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param persistent
 *            if <code>true</code> ServiceListener.resolveService will be called whenever new new information is received.
 * @param text
 *            string describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ /*final*/ subtype, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ bool persistent, /*final*/ /*final*/ text) {
    return new ServiceInfoImpl(type, name, subtype, port, weight, priority, persistent, text);
}
/**
 * Construct a service description for registering with JmDNS. The properties hashtable must map property names to either Strings or byte arrays describing the property values.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param persistent
 *            if <code>true</code> ServiceListener.resolveService will be called whenever new new information is received.
 * @param props
 *            properties describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ bool persistent, /*final*/ Map</*final*/, ?> props) {
    return new ServiceInfoImpl(type, name, "", port, weight, priority, persistent, props);
}
/**
 * Construct a service description for registering with JmDNS. The properties hashtable must map property names to either Strings or byte arrays describing the property values.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param subtype
 *            service subtype see draft-cheshire-dnsext-dns-sd-06.txt chapter 7.1 Selective Instance Enumeration
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param persistent
 *            if <code>true</code> ServiceListener.resolveService will be called whenever new new information is received.
 * @param props
 *            properties describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ /*final*/ subtype, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ bool persistent, /*final*/ Map</*final*/, ?> props) {
    return new ServiceInfoImpl(type, name, subtype, port, weight, priority, persistent, props);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param persistent
 *            if <code>true</code> ServiceListener.resolveService will be called whenever new new information is received.
 * @param text
 *            bytes describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ bool persistent, /*final*/ byte[] text) {
    return new ServiceInfoImpl(type, name, "", port, weight, priority, persistent, text);
}
/**
 * Construct a service description for registering with JmDNS.
 *
 * @param type
 *            fully qualified service type name, such as <code>_http._tcp.local.</code>.
 * @param name
 *            unqualified service instance name, such as <code>foobar</code>
 * @param subtype
 *            service subtype see draft-cheshire-dnsext-dns-sd-06.txt chapter 7.1 Selective Instance Enumeration
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param persistent
 *            if <code>true</code> ServiceListener.resolveService will be called whenever new new information is received.
 * @param text
 *            bytes describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ /*final*/ type, /*final*/ /*final*/ name, /*final*/ /*final*/ subtype, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ bool persistent, /*final*/ byte[] text) {
    return new ServiceInfoImpl(type, name, subtype, port, weight, priority, persistent, text);
}
/**
 * Construct a service description for registering with JmDNS. The properties hashtable must map property names to either Strings or byte arrays describing the property values.
 *
 * @param qualifiedNameMap
 *            dictionary of values to build the fully qualified service name. Mandatory keys are Application and Instance. The Domain default is local, the Protocol default is tcp and the subtype default is none.
 * @param port
 *            the local port on which the service runs
 * @param weight
 *            weight of the service
 * @param priority
 *            priority of the service
 * @param persistent
 *            if <code>true</code> ServiceListener.resolveService will be called whenever new new information is received.
 * @param props
 *            properties describing the service
 * @return new service info
 */
/*public*/ static ServiceInfo create(/*final*/ Map<Fields, /*final*/> qualifiedNameMap, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ bool persistent, /*final*/ Map</*final*/, ?> props) {
    return new ServiceInfoImpl(qualifiedNameMap, port, weight, priority, persistent, props);
}
#endif
/**
 * Returns true if the service info is filled with data.
 *
 * @return <code>true</code> if the service info has data, <code>false</code> otherwise.
 */
/*public*/ /*abstract*/ bool ServiceInfo::hasData() {return false;}
/**
 * Fully qualified service type name, such as <code>_http._tcp.local.</code>
 *
 * @return service type name
 */
/*public*/ /*abstract*/ QString ServiceInfo::getType() {return "";}
/**
 * Fully qualified service type name with the subtype if appropriate, such as <code>_printer._sub._http._tcp.local.</code>
 *
 * @return service type name
 */
/*public*/ /*abstract*/ QString ServiceInfo::getTypeWithSubtype() {return "";}
/**
 * Unqualified service instance name, such as <code>foobar</code> .
 *
 * @return service name
 */
/*public*/ /*abstract*/ QString ServiceInfo::getName() {return "";}
/**
 * The key is used to retrieve service info in hash tables.<br/>
 * The key is the lower case qualified name.
 *
 * @return the key
 */
/*public*/ /*abstract*/ QString ServiceInfo::getKey() {return "";}
/**
 * Fully qualified service name, such as <code>foobar._http._tcp.local.</code> .
 *
 * @return qualified service name
 */
/*public*/ /*abstract*/ QString ServiceInfo::getQualifiedName() {return "";}
/**
 * Get the name of the server.
 *
 * @return server name
 */
/*public*/ /*abstract*/ QString ServiceInfo::getServer() {return "";}
/**
 * Returns the host IP address string in textual presentation.<br/>
 * <b>Note:</b> This can be either an IPv4 or an IPv6 representation.
 *
 * @return the host raw IP address in a string format.
 * @deprecated since 3.2.3
 * @see #getHostAddresses()
 */
//@Deprecated
/*public*/ /*abstract*/ QString ServiceInfo::getHostAddress() {return "";}
/**
 * Returns the host IP addresses string in textual presentation.
 *
 * @return list of host raw IP address in a string format.
 */
/*public*/ /*abstract*/ QStringList ServiceInfo::getHostAddresses() {return QStringList();}
#if 0
/**
 * Get the host address of the service.<br/>
 *
 * @return host Internet address
 * @deprecated since 3.1.8
 * @see #getInetAddresses()
 */
//@Deprecated
/*public*/ /*abstract*/ InetAddress getAddress();
/**
 * Get the InetAddress of the service. This will return the IPv4 if it exist, otherwise it return the IPv6 if set.<br/>
 * <b>Note:</b> This return null if the service IP address cannot be resolved.
 *
 * @return Internet address
 * @deprecated since 3.2.3
 * @see #getInetAddresses()
 */
@Deprecated
/*public*/ /*abstract*/ InetAddress getInetAddress();
/**
 * Get the IPv4 InetAddress of the service.<br/>
 * <b>Note:</b> This return null if the service IPv4 address cannot be resolved.
 *
 * @return Internet address
 * @deprecated since 3.2.3
 * @see #getInet4Addresses()
 */
@Deprecated
/*public*/ /*abstract*/ Inet4Address getInet4Address();
/**
 * Get the IPv6 InetAddress of the service.<br/>
 * <b>Note:</b> This return null if the service IPv6 address cannot be resolved.
 *
 * @return Internet address
 * @deprecated since 3.2.3
 * @see #getInet6Addresses()
 */
@Deprecated
/*public*/ /*abstract*/ Inet6Address getInet6Address();
#endif
/**
 * Returns a list of all InetAddresses that can be used for this service.
 * <p>
 * In a multi-homed environment service info can be associated with more than one address.
 * </p>
 *
 * @return list of InetAddress objects
 */
/*public*/ /*abstract*/ QList<InetAddress*> ServiceInfo::getInetAddresses() {return QList<InetAddress*>();}

/**
 * Returns a list of all IPv4 InetAddresses that can be used for this service.
 * <p>
 * In a multi-homed environment service info can be associated with more than one address.
 * </p>
 *
 * @return list of InetAddress objects
 */
/*public*/ /*abstract*/ QList<Inet4Address *> ServiceInfo::getInet4Addresses() {return QList<Inet4Address*>();}
/**
 * Returns a list of all IPv6 InetAddresses that can be used for this service.
 * <p>
 * In a multi-homed environment service info can be associated with more than one address.
 * </p>
 *
 * @return list of InetAddress objects
 */
/*public*/ /*abstract*/ QList<Inet6Address*> ServiceInfo::getInet6Addresses() {return QList<Inet6Address*>();}


/**
 * Get the port for the service.
 *
 * @return service port
 */
/*public*/ /*abstract*/ int ServiceInfo::getPort() {return 0;}

/**
 * Get the priority of the service.
 *
 * @return service priority
 */
/*public*/ /*abstract*/ int ServiceInfo::getPriority() {return -1;}
/**
 * Get the weight of the service.
 *
 * @return service weight
 */
/*public*/ /*abstract*/ int ServiceInfo::getWeight() {return 0;}

/**
 * Get the text for the service as raw bytes.
 *
 * @return raw service text
 */
/*public*/ /*abstract*/ QByteArray ServiceInfo::getTextBytes() {return QByteArray();}

/**
 * Get the text for the service. This will interpret the text bytes as a UTF8 encoded string. Will return null if the bytes are not a valid UTF8 encoded string.<br/>
 * <b>Note:</b> Do not use. This method make the assumption that the TXT record is one string. This is false. The TXT record is a series of key value pairs.
 *
 * @return service text
 * @see #getPropertyNames()
 * @see #getPropertyBytes(String)
 * @see #getPropertyString(String)
 * @deprecated since 3.1.7
 */
//@Deprecated
/*public*/ /*abstract*/ QString ServiceInfo::getTextString() {return "";}

/**
 * Get the URL for this service. An http URL is created by combining the address, port, and path properties.
 *
 * @return service URL
 * @deprecated since 3.2.3
 * @see #getURLs()
 */
//@Deprecated
/*public*/ /*abstract*/ QString ServiceInfo::getURL() {return "";}
/**
 * Get the list of URL for this service. An http URL is created by combining the address, port, and path properties.
 *
 * @return list of service URL
 */
/*public*/ /*abstract*/ QStringList ServiceInfo::getURLs() {return QStringList();}

/**
 * Get the URL for this service. An URL is created by combining the protocol, address, port, and path properties.
 *
 * @param protocol
 *            requested protocol
 * @return service URL
 * @deprecated since 3.2.3
 * @see #getURLs()
 */
//@Deprecated
/*public*/ /*abstract*/ QString ServiceInfo::getURL(QString /*protocol*/) {return "";}
/**
 * Get the list of URL for this service. An URL is created by combining the protocol, address, port, and path properties.
 *
 * @param protocol
 *            requested protocol
 * @return list of service URL
 */
/*public*/ /*abstract*/ QStringList ServiceInfo::getURLs(QString /*protocol*/) {return QStringList();}

/**
 * Get a property of the service. This involves decoding the text bytes into a property list. Returns null if the property is not found or the text data could not be decoded correctly.
 *
 * @param name
 *            property name
 * @return raw property text
 */

/*public*/ /*abstract*/ QByteArray ServiceInfo::getPropertyBytes(/*final*/ QString /*name*/) {return QByteArray();}
/**
 * Get a property of the service. This involves decoding the text bytes into a property list. Returns null if the property is not found, the text data could not be decoded correctly, or the resulting bytes are not a valid UTF8 string.
 *
 * @param name
 *            property name
 * @return property text
 */
 /*public*/ /*abstract*/ QString ServiceInfo::getPropertyString(/*final*/ QString /*name*/) {return "";}
/**
 * Enumeration of the property names.
 *
 * @return property name enumeration
 */
/*public*/ /*abstract*/ QStringListIterator ServiceInfo::getPropertyNames() {return QStringListIterator(QStringList());}

/**
 * Returns a description of the service info suitable for printing.
 *
 * @return service info description
 */
/*public*/ /*abstract*/ QString ServiceInfo::getNiceTextString() {return "";}
/**
 * Set the text for the service. Setting the text will fore a re-announce of the service.
 *
 * @param text
 *            the raw byte representation of the text field.
 * @exception IllegalStateException
 *                if attempting to set the text for a non persistent service info.
 */
/*public*/ /*abstract*/ void ServiceInfo::setText(/*final*/ QByteArray /*text*/) throw (IllegalStateException) {}
/**
 * Set the text for the service. Setting the text will fore a re-announce of the service.
 *
 * @param props
 *            a key=value map that will be encoded into raw bytes.
 * @exception IllegalStateException
 *                if attempting to set the text for a non persistent service info.
 */
/*public*/ /*abstract*/ void ServiceInfo::setText(/*final*/ QMap<QString, QVariant> /*props*/) throw (IllegalStateException) {}

/**
 * Returns <code>true</code> if ServiceListener.resolveService will be called whenever new new information is received.
 *
 * @return the persistent
 */
/*public*/ /*abstract*/ bool ServiceInfo::isPersistent() {return false;}
/**
 * Returns the domain of the service info suitable for printing.
 *
 * @return service domain
 */
/*public*/ /*abstract*/ QString ServiceInfo::getDomain() {return "";}
/**
 * Returns the protocol of the service info suitable for printing.
 *
 * @return service protocol
 */
/*public*/ /*abstract*/ QString ServiceInfo::getProtocol() {return "";}
/**
 * Returns the application of the service info suitable for printing.
 *
 * @return service application
 */
/*public*/ /*abstract*/ QString ServiceInfo::getApplication() {return "";}
/**
 * Returns the sub type of the service info suitable for printing.
 *
 * @return service sub type
 */
/*public*/ /*abstract*/ QString ServiceInfo::getSubtype() {return "";}
/**
 * Returns a dictionary of the fully qualified name component of this service.
 *
 * @return dictionary of the fully qualified name components
 */
/*public*/ /*abstract*/ QMap<ServiceInfo::Fields, QString> ServiceInfo::getQualifiedNameMap() {return QMap<ServiceInfo::Fields, QString>();}
/*
 * (non-Javadoc)
 * @see java.lang.Object#clone()
 */
//@Override

/*public*/ ServiceInfo* ServiceInfo::clone() {
//        try {
//            return (ServiceInfo*) super.clone();
//        } catch (CloneNotSupportedException exception) {
//            // clone is supported
//            return null;
//        }
    ServiceInfo* si = new ServiceInfo(* this);
 return si;
}

