#include "serviceinfoimpl.h"
#include "loggerfactory.h"
#include "level.h"
#include "inetaddress.h"
#include "inet4address.h"
#include "inet6address.h"

// Copyright 2003-2005 Arthur van Hoff, Rick Blair
// Licensed under Apache License version 2.0
// Original license LGPL
//package javax.jmdns.impl;
//import java.io.ByteArrayOutputStream;
//import java.io.IOException;
//import java.io.OutputStream;
//import java.net.Inet4Address;
//import java.net.Inet6Address;
//import java.net.InetAddress;
//import java.util.ArrayList;
//import java.util.Collection;
//import java.util.Collections;
//import java.util.Enumeration;
//import java.util.HashMap;
//import java.util.Hashtable;
//import java.util.LinkedHashSet;
//import java.util.List;
//import java.util.Map;
//import java.util.Set;
//import java.util.Vector;
//import java.util.logging.Level;
//import java.util.logging.Logger;
//import javax.jmdns.ServiceEvent;
//import javax.jmdns.ServiceInfo;
//import javax.jmdns.impl.DNSRecord.Pointer;
//import javax.jmdns.impl.DNSRecord.Service;
//import javax.jmdns.impl.DNSRecord.Text;
//import javax.jmdns.impl.constants.DNSRecordClass;
//import javax.jmdns.impl.constants.DNSRecordType;
//import javax.jmdns.impl.constants.DNSState;
//import javax.jmdns.impl.tasks.DNSTask;
/**
 * JmDNS service information.
 *
 * @author Arthur van Hoff, Jeff Sonstein, Werner Randelshofer
 */
// /*public*/ class ServiceInfoImpl extends ServiceInfo implements DNSListener, DNSStatefulObject {
    /*private*/ /*static*/ Logger*           ServiceInfoImpl::logger =
  LoggerFactory::getLogger("ServiceInfoImpl");
#if 0
    /*public*/ static interface Delegate {
        /*public*/ void textValueUpdated(ServiceInfo target, byte[] value);
    }
#endif
//    /*private*/ final static class ServiceInfoState extends DNSStatefulObject.DefaultImplementation {
//        /*private*/ static final long     serialVersionUID = 1104131034952196820L;
//        /*private*/ final ServiceInfoImpl _info;
        /**
         * @param info
         */
        /*public*/ ServiceInfoState::ServiceInfoState(ServiceInfoImpl* info) {
            //super();
            _info = info;
        }
QString ServiceInfoState::toString() {return "";}
        //@Override
        /*protected*/ void ServiceInfoState::setTask(DNSTask* task) {
            //super.setTask(task);
#if 0
            if ((this->_task == nullptr) && _info->needTextAnnouncing()) {
                this->lock();
                try {
                    if ((this->_task == nullptr) && _info->needTextAnnouncing()) {
                        if (this->_state.isAnnounced()) {
                            this->setState(DNSState.ANNOUNCING_1);
                            if (this->getDns() != null) {
                                this->getDns().startAnnouncer();
                            }
                        }
                        _info->setNeedTextAnnouncing(false);
                    }
                } finally {
                    this->unlock();
                }
            }
#endif
        }
        //@Override
        /*public*/ void ServiceInfoState::setDns(JmDNSImpl* dns) {
            //super.setDns(dns);
        }
//    };

    /**
     * @param type
     * @param name
     * @param subtype
     * @param port
     * @param weight
     * @param priority
     * @param persistent
     * @param text
     * @see javax.jmdns.ServiceInfo#create(String, String, int, int, int, String)
     */
    /*public*/ ServiceInfoImpl::ServiceInfoImpl(QString type, QString name, QString subtype, int port, int weight, int priority, bool persistent, QString text)
    : ServiceInfo()
{
        common(ServiceInfoImpl::decodeQualifiedNameMap(type, name, subtype), port, weight, priority, persistent, QByteArray());
        _server = text;
//        try {
//            ByteArrayOutputStream out = new ByteArrayOutputStream(text.length());
//            writeUTF(out, text);
//            this->_text = out.toByteArray();
//        } catch (IOException e) {
//            throw  RuntimeException("unexpected exception: " + e);
//        }
        this->_text = text.toUtf8();
    }

    /**
     * @param type
     * @param name
     * @param subtype
     * @param port
     * @param weight
     * @param priority
     * @param persistent
     * @param props
     * @see javax.jmdns.ServiceInfo#create(String, String, int, int, int, Map)
     */
    /*public*/ ServiceInfoImpl::ServiceInfoImpl(QString type, QString name, QString subtype, int port, int weight, int priority, bool persistent, QMap<QString, QVariant> props)
    : ServiceInfo()
    {
        common(ServiceInfoImpl::decodeQualifiedNameMap(type, name, subtype), port, weight, priority, persistent, textFromProperties(props));
    }
#if 0
    /**
     * @param type
     * @param name
     * @param subtype
     * @param port
     * @param weight
     * @param priority
     * @param persistent
     * @param text
     * @see javax.jmdns.ServiceInfo#create(String, String, int, int, int, byte[])
     */
    /*public*/ ServiceInfoImpl(String type, String name, String subtype, int port, int weight, int priority, boolean persistent, byte text[]) {
        this(ServiceInfoImpl.decodeQualifiedNameMap(type, name, subtype), port, weight, priority, persistent, text);
    }
    /*public*/ ServiceInfoImpl(Map<Fields, String> qualifiedNameMap, int port, int weight, int priority, boolean persistent, Map<String, ?> props) {
        this(qualifiedNameMap, port, weight, priority, persistent, textFromProperties(props));
    }
#endif
    ServiceInfoImpl::ServiceInfoImpl(QMap<ServiceInfo::Fields, QString> qualifiedNameMap, int port, int weight, int priority, bool persistent, QString text)
        : ServiceInfo()
    {
        common(qualifiedNameMap, port, weight, priority, persistent, QByteArray());
        _server = text;
//        try {
//            ByteArrayOutputStream out = new ByteArrayOutputStream(text.length());
//            writeUTF(out, text);
//            this->_text = out.toByteArray();
        this->_text = text.toUtf8();
//        } catch (IOException e) {
//            throw new RuntimeException("unexpected exception: " + e);
//        }
    }

    void ServiceInfoImpl::common(QMap<ServiceInfo::Fields, QString> qualifiedNameMap, int port, int weight, int priority, bool persistent, QByteArray text)
    {
        QMap<Fields, QString> map = ServiceInfoImpl::checkQualifiedNameMap(qualifiedNameMap);
        this->_domain = map.value(ServiceInfo::Fields::Domain);
        this->_protocol = map.value(ServiceInfo::Fields::Protocol);
        this->_application = map.value(ServiceInfo::Fields::Application);
        this->_name = map.value(ServiceInfo::Fields::Instance);
        this->_subtype = map.value(ServiceInfo::Fields::Subtype);
        this->_port = port;
        this->_weight = weight;
        this->_priority = priority;
        this->_text = text;
        this->setNeedTextAnnouncing(false);
        this->_state = new ServiceInfoState(this);
        this->_persistent = persistent;
#if 0
        this->_ipv4Addresses = Collections.synchronizedSet(new LinkedHashSet<Inet4Address>());
        this->_ipv6Addresses = Collections.synchronizedSet(new LinkedHashSet<Inet6Address>());
#endif
    }

    /**
     * During recovery we need to duplicate service info to reregister them
     *
     * @param info
     */
    ServiceInfoImpl::ServiceInfoImpl(ServiceInfo* info) {
#if 0
        this->_ipv4Addresses = Collections.synchronizedSet(new LinkedHashSet<Inet4Address>());
        this->_ipv6Addresses = Collections.synchronizedSet(new LinkedHashSet<Inet6Address>());
#endif
        if (info != nullptr) {
            this->_domain = info->getDomain();
            this->_protocol = info->getProtocol();
            this->_application = info->getApplication();
            this->_name = info->getName();
            this->_subtype = info->getSubtype();
            this->_port = info->getPort();
            this->_weight = info->getWeight();
            this->_priority = info->getPriority();
            this->_text = info->getTextBytes();
            this->_persistent = info->isPersistent();
#if 0
            Inet6Address[] ipv6Addresses = info.getInet6Addresses();
            for (Inet6Address address : ipv6Addresses) {
                this->_ipv6Addresses.add(address);
            }
            Inet4Address[] ipv4Addresses = info.getInet4Addresses();
            for (Inet4Address address : ipv4Addresses) {
                this->_ipv4Addresses.add(address);
            }
#endif
        }
        this->_state = new ServiceInfoState(this);
    }

    /*public*/ /*static*/ QMap<ServiceInfo::Fields, QString> ServiceInfoImpl::decodeQualifiedNameMap(QString type, QString name, QString subtype) {
        QMap<ServiceInfo::Fields, QString> qualifiedNameMap = decodeQualifiedNameMapForType(type);
        qualifiedNameMap.insert(ServiceInfo::Fields::Instance, name);
        qualifiedNameMap.insert(ServiceInfo::Fields::Subtype, subtype);
        return checkQualifiedNameMap(qualifiedNameMap);
    }

    /*public*/ /*static*/ QMap<ServiceInfo::Fields, QString> ServiceInfoImpl::decodeQualifiedNameMapForType(QString type) {
        int index;
        QString casePreservedType = type;
        QString aType = type.toLower();
        QString application = aType;
        QString protocol = "";
        QString subtype = "";
        QString name = "";
        QString domain = "";
        if (aType.contains("in-addr.arpa") || aType.contains("ip6.arpa")) {
            index = (aType.contains("in-addr.arpa") ? aType.indexOf("in-addr.arpa") : aType.indexOf("ip6.arpa"));
            name = removeSeparators(casePreservedType.mid(0, index));
            domain = casePreservedType.mid(index);
            application = "";
        } else if ((!aType.contains("_")) && aType.contains(".")) {
            index = aType.indexOf('.');
            name = removeSeparators(casePreservedType.mid(0, index));
            domain = removeSeparators(casePreservedType.mid(index));
            application = "";
        } else {
            // First remove the name if it there.
            if (!aType.startsWith("_") || aType.startsWith("_services")) {
                index = aType.indexOf('.');
                if (index > 0) {
                    // We need to preserve the case for the user readable name.
                    name = casePreservedType.mid(0, index);
                    if (index + 1 < aType.length()) {
                        aType = aType.mid(index + 1);
                        casePreservedType = casePreservedType.mid(index + 1);
                    }
                }
            }
            index = aType.lastIndexOf("._");
            if (index > 0) {
                int start = index + 2;
                int end = aType.indexOf('.', start);
                protocol = casePreservedType.mid(start, end-start);
            }
            if (protocol.length() > 0) {
                index = aType.indexOf("_" + protocol.toLower() + ".");
                int start = index + protocol.length() + 2;
                int end = aType.length() - (aType.endsWith(".") ? 1 : 0);
                domain = casePreservedType.mid(start, end-start);
                application = casePreservedType.mid(0, index - 1);
            }
            index = application.toLower().indexOf("._sub");
            if (index > 0) {
                int start = index + 5;
                subtype = removeSeparators(application.mid(0, index));
                application = application.mid(start);
            }
        }
        /*final*/ QMap<ServiceInfo::Fields, QString> qualifiedNameMap = QMap<ServiceInfo::Fields, QString>();
        qualifiedNameMap.insert(ServiceInfo::Fields::Domain, removeSeparators(domain));
        qualifiedNameMap.insert(ServiceInfo::Fields::Protocol, protocol);
        qualifiedNameMap.insert(ServiceInfo::Fields::Application, removeSeparators(application));
        qualifiedNameMap.insert(ServiceInfo::Fields::Instance, name);
        qualifiedNameMap.insert(ServiceInfo::Fields::Subtype, subtype);
        return qualifiedNameMap;
    }
    /*protected*/ /*static*/ QMap<ServiceInfo::Fields, QString> ServiceInfoImpl::checkQualifiedNameMap(QMap<ServiceInfo::Fields, QString> qualifiedNameMap) {
        QMap<ServiceInfo::Fields, QString> checkedQualifiedNameMap = QMap<ServiceInfo::Fields, QString>();
        // Optional domain
        QString domain = (qualifiedNameMap.contains(ServiceInfo::Fields::Domain) ? qualifiedNameMap.value(ServiceInfo::Fields::Domain) : "local");
        if ((domain == "") || (domain.length() == 0)) {
            domain = "local";
        }
        domain = removeSeparators(domain);
        checkedQualifiedNameMap.insert(ServiceInfo::Fields::Domain, domain);
        // Optional protocol
        QString protocol = (qualifiedNameMap.contains(ServiceInfo::Fields::Protocol) ? qualifiedNameMap.value(ServiceInfo::Fields::Protocol) : "tcp");
        if ((protocol == "") || (protocol.length() == 0)) {
            protocol = "tcp";
        }
        protocol = removeSeparators(protocol);
        checkedQualifiedNameMap.insert(ServiceInfo::Fields::Protocol, protocol);
        // Application
        QString application = (qualifiedNameMap.contains(ServiceInfo::Fields::Application) ? qualifiedNameMap.value(ServiceInfo::Fields::Application) : "");
        if ((application == "") || (application.length() == 0)) {
            application = "";
        }
        application = removeSeparators(application);
        checkedQualifiedNameMap.insert(ServiceInfo::Fields::Application, application);
        // Instance
        QString instance = (qualifiedNameMap.contains(ServiceInfo::Fields::Instance) ? qualifiedNameMap.value(ServiceInfo::Fields::Instance) : "");
        if ((instance == "") || (instance.length() == 0)) {
            instance = "";
            // throw new IllegalArgumentException("The instance name component of a fully qualified service cannot be empty.");
        }
        instance = removeSeparators(instance);
        checkedQualifiedNameMap.insert(ServiceInfo::Fields::Instance, instance);
        // Optional Subtype
        QString subtype = (qualifiedNameMap.contains(ServiceInfo::Fields::Subtype) ? qualifiedNameMap.value(ServiceInfo::Fields::Subtype) : "");
        if ((subtype == "") || (subtype.length() == 0)) {
            subtype = "";
        }
        subtype = removeSeparators(subtype);
        checkedQualifiedNameMap.insert(ServiceInfo::Fields::Subtype, subtype);
        return checkedQualifiedNameMap;
    }

    /*private*/ /*static*/ QString ServiceInfoImpl::removeSeparators(QString name) {
        if (name == "") {
            return "";
        }
        QString newName = name.trimmed();
        if (newName.startsWith(".")) {
            newName = newName.mid(1);
        }
        if (newName.startsWith("_")) {
            newName = newName.mid(1);
        }
        if (newName.endsWith(".")) {
            newName = newName.mid(0, newName.length() - 1);
        }
        return newName;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getType() {
        QString domain = this->getDomain();
        QString protocol = this->getProtocol();
        QString application = this->getApplication();
        return (application.length() > 0 ? "_" + application + "." : "") + (protocol.length() > 0 ? "_" + protocol + "." : "") + domain + ".";
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getTypeWithSubtype() {
        QString subtype = this->getSubtype();
        return (subtype.length() > 0 ? "_" + subtype.toLower() + "._sub." : "") + this->getType();
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getName() {
        return (_name != "" ? _name : "");
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getKey() {
        if (this->_key == "") {
            this->_key = this->getQualifiedName().toLower();
        }
        return this->_key;
    }

    /**
     * Sets the service instance name.
     *
     * @param name
     *            unqualified service instance name, such as <code>foobar</code>
     */
    void ServiceInfoImpl::setName(QString name) {
        this->_name = name;
        this->_key = "";
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getQualifiedName() {
        QString domain = this->getDomain();
        QString protocol = this->getProtocol();
        QString application = this->getApplication();
        QString instance = this->getName();
        // String subtype = this->getSubtype();
        // return (instance.length() > 0 ? instance + "." : "") + (application.length() > 0 ? "_" + application + "." : "") + (protocol.length() > 0 ? "_" + protocol + (subtype.length() > 0 ? ",_" + subtype.toLowerCase() + "." : ".") : "") + domain
        // + ".";
        return (instance.length() > 0 ? instance + "." : "") + (application.length() > 0 ? "_" + application + "." : "") + (protocol.length() > 0 ? "_" + protocol + "." : "") + domain + ".";
    }
    /**
     * @see javax.jmdns.ServiceInfo#getServer()
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getServer() {
        return (_server != "" ? _server : "");
    }
    /**
     * @param server
     *            the server to set
     */
    void ServiceInfoImpl::setServer(QString server) {
        this->_server = server;
    }
#if 0
    /**
     * {@inheritDoc}
     */
    @Deprecated
    @Override
    /*public*/ String getHostAddress() {
        String[] names = this->getHostAddresses();
        return (names.length > 0 ? names[0] : "");
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ String[] getHostAddresses() {
        Inet4Address[] ip4Aaddresses = this->getInet4Addresses();
        Inet6Address[] ip6Aaddresses = this->getInet6Addresses();
        String[] names = new String[ip4Aaddresses.length + ip6Aaddresses.length];
        for (int i = 0; i < ip4Aaddresses.length; i++) {
            names[i] = ip4Aaddresses[i].getHostAddress();
        }
        for (int i = 0; i < ip6Aaddresses.length; i++) {
            names[i + ip4Aaddresses.length] = "[" + ip6Aaddresses[i].getHostAddress() + "]";
        }
        return names;
    }
#endif
    /**
     * @param addr
     *            the addr to add
     */
    void ServiceInfoImpl::addAddress(Inet4Address* addr) {
        _ipv4Addresses.insert(addr);
    }
    /**
     * @param addr
     *            the addr to add
     */
    void ServiceInfoImpl::addAddress(Inet6Address* addr) {
        _ipv6Addresses.insert(addr);
    }
#if 0
    /**
     * {@inheritDoc}
     */
    @Deprecated
    @Override
    /*public*/ InetAddress getAddress() {
        return this->getInetAddress();
    }
    /**
     * {@inheritDoc}
     */
    @Deprecated
    @Override
    /*public*/ InetAddress getInetAddress() {
        InetAddress[] addresses = this->getInetAddresses();
        return (addresses.length > 0 ? addresses[0] : null);
    }
    /**
     * {@inheritDoc}
     */
    @Deprecated
    @Override
    /*public*/ Inet4Address getInet4Address() {
        Inet4Address[] addresses = this->getInet4Addresses();
        return (addresses.length > 0 ? addresses[0] : null);
    }
    /**
     * {@inheritDoc}
     */
    @Deprecated
    @Override
    /*public*/ Inet6Address getInet6Address() {
        Inet6Address[] addresses = this->getInet6Addresses();
        return (addresses.length > 0 ? addresses[0] : null);
    }
#endif
    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#getInetAddresses()
     */
    //@Override
    /*public*/ QList<InetAddress*> ServiceInfoImpl::getInetAddresses() {
        QList<InetAddress*> aList = QList<InetAddress*>();//(_ipv4Addresses.size() + _ipv6Addresses.size());
//        aList.addAll(_ipv4Addresses);
        foreach(Inet4Address* ipv4address, _ipv4Addresses)
         aList.append(ipv4address);
//        aList.addAll(_ipv6Addresses);
        foreach(Inet6Address* ipv6address, _ipv6Addresses)
         aList.append(ipv6address);
        //return aList.toArray(new InetAddress[aList.size()]);
        return QList<InetAddress*>(aList);
    }

    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#getInet4Addresses()
     */
    //@Override
    /*public*/ QList<Inet4Address*> ServiceInfoImpl::getInet4Addresses() {
        //return _ipv4Addresses.toArray(new Inet4Address[_ipv4Addresses.size()]);
     return QList<Inet4Address*>(_ipv4Addresses.toList());
    }
    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#getInet6Addresses()
     */
    //@Override
    /*public*/ QList<Inet6Address*> ServiceInfoImpl::getInet6Addresses() {
        //return _ipv6Addresses.toArray(new Inet6Address[_ipv6Addresses.size()]);
     return QList<Inet6Address*>(_ipv6Addresses.toList());

    }

    /**
     * @see javax.jmdns.ServiceInfo#getPort()
     */
    //@Override
    /*public*/ int ServiceInfoImpl::getPort() {
        return _port;
    }

    /**
     * @see javax.jmdns.ServiceInfo#getPriority()
     */
    //@Override
    /*public*/ int ServiceInfoImpl::getPriority() {
        return _priority;
    }
    /**
     * @see javax.jmdns.ServiceInfo#getWeight()
     */
    //@Override
    /*public*/ int ServiceInfoImpl::getWeight() {
        return _weight;
    }

    /**
     * @see javax.jmdns.ServiceInfo#getTextBytes()
     */
    //@Override
    /*public*/ QByteArray ServiceInfoImpl::getTextBytes() {
        return (!this->_text.isNull() && this->_text.length() > 0 ? this->_text : QByteArray());//DNSRecord.EMPTY_TXT);
    }

    /**
     * {@inheritDoc}
     */
    //@Deprecated
    //@Override
    /*public*/ QString ServiceInfoImpl::getTextString() {
        QMap<QString, QByteArray> properties = this->getProperties();
        for (QString key : properties.keys()) {
            QByteArray value = properties.value(key);
            if ((!value.isNull()) && (value.length() > 0)) {
                return key + "=" + QString(value);
            }
            return key;
        }
        return "";
    }
    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#getURL()
     */
    //@Deprecated
    //@Override
    /*public*/ QString ServiceInfoImpl::getURL() {
        return this->getURL("http");
    }
    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#getURLs()
     */
    //@Override
    /*public*/ QStringList ServiceInfoImpl::getURLs() {
        return this->getURLs("http");
    }

    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#getURL(java.lang.String)
     */
    //@Deprecated
    //@Override
    /*public*/ QString ServiceInfoImpl::getURL(QString protocol) {
        QStringList urls = this->getURLs(protocol);
        return (urls.length() > 0 ? urls[0] : protocol + "://null:" + getPort());
    }
    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#getURLs(java.lang.String)
     */
    //@Override
    /*public*/ QStringList ServiceInfoImpl::getURLs(QString protocol) {
        QList<InetAddress*> addresses = this->getInetAddresses();
        QStringList urls = QStringList();//new String[addresses.length];
        for (int i = 0; i < addresses.length(); i++) {
            QString url = protocol + "://" + addresses[i]->getHostAddress() + ":" + getPort();
            QString path = getPropertyString("path");
            if (path != "") {
                if (path.indexOf("://") >= 0) {
                    url = path;
                } else {
                    url += path.startsWith("/") ? path : "/" + path;
                }
            }
            urls[i] = url;
        }
        return urls;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QByteArray ServiceInfoImpl::getPropertyBytes(QString name) {
        return this->getProperties().value(name);
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ /*synchronized*/ QString ServiceInfoImpl::getPropertyString(QString name) {
        QByteArray data = this->getProperties().value(name);
        if (data.isNull()) {
            return QByteArray();
        }
        if (data == NO_VALUE) {
            return "true";
        }
        //return readUTF(data, 0, data.length);
        return QString(data);
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QStringListIterator ServiceInfoImpl::getPropertyNames()
    {
        QMap<QString, QByteArray> properties = this->getProperties();
//        Collection<String> names = (properties != null ? properties.keySet() : Collections.<String> emptySet());
//        return new Vector<String>(names).elements();
        return QStringListIterator(properties.keys());
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getApplication() {
        return (_application != "" ? _application : "");
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getDomain() {
        return (_domain != "" ? _domain : "local");
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getProtocol() {
        return (_protocol != "" ? _protocol : "tcp");
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::getSubtype() {
        return (_subtype != "" ? _subtype : "");
    }
#if 0
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ Map<Fields, String> getQualifiedNameMap() {
        Map<Fields, String> map = new HashMap<Fields, String>(5);
        map.put(ServiceInfo::Fields::Domain, this->getDomain());
        map.put(ServiceInfo::Fields::Protocol, this->getProtocol());
        map.put(ServiceInfo::Fields::Application, this->getApplication());
        map.put(ServiceInfo::Fields::Instance, this->getName());
        map.put(ServiceInfo::Fields::Subtype, this->getSubtype());
        return map;
    }
    /**
     * Write a UTF string with a length to a stream.
     */
    static void writeUTF(OutputStream out, String str) throws IOException {
        for (int i = 0, len = str.length(); i < len; i++) {
            int c = str.charAt(i);
            if ((c >= 0x0001) && (c <= 0x007F)) {
                out.write(c);
            } else {
                if (c > 0x07FF) {
                    out.write(0xE0 | ((c >> 12) & 0x0F));
                    out.write(0x80 | ((c >> 6) & 0x3F));
                    out.write(0x80 | ((c >> 0) & 0x3F));
                } else {
                    out.write(0xC0 | ((c >> 6) & 0x1F));
                    out.write(0x80 | ((c >> 0) & 0x3F));
                }
            }
        }
    }
    /**
     * Read data bytes as a UTF stream.
     */
    String readUTF(byte data[], int off, int len) {
        int offset = off;
        StringBuffer buf = new StringBuffer();
        for (int end = offset + len; offset < end;) {
            int ch = data[offset++] & 0xFF;
            switch (ch >> 4) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    // 0xxxxxxx
                    break;
                case 12:
                case 13:
                    if (offset >= len) {
                        return null;
                    }
                    // 110x xxxx 10xx xxxx
                    ch = ((ch & 0x1F) << 6) | (data[offset++] & 0x3F);
                    break;
                case 14:
                    if (offset + 2 >= len) {
                        return null;
                    }
                    // 1110 xxxx 10xx xxxx 10xx xxxx
                    ch = ((ch & 0x0f) << 12) | ((data[offset++] & 0x3F) << 6) | (data[offset++] & 0x3F);
                    break;
                default:
                    if (offset + 1 >= len) {
                        return null;
                    }
                    // 10xx xxxx, 1111 xxxx
                    ch = ((ch & 0x3F) << 4) | (data[offset++] & 0x0f);
                    break;
            }
            buf.append((char) ch);
        }
        return buf.toString();
    }
#endif
    /*synchronized*/ QMap<QString, QByteArray> ServiceInfoImpl::getProperties() {
        if ((_props.isEmpty()) && (!this->getTextBytes().isNull())) {
           QMap<QString, QByteArray> properties = QMap<QString, QByteArray>();
            try {
                int off = 0;
                while (off < getTextBytes().length()) {
                    // length of the next key value pair
                    int len = getTextBytes()[off++] & 0xFF;
                    if ((len == 0) || (off + len > getTextBytes().length())) {
                        properties.clear();
                        break;
                    }
                    // look for the '='
                    int i = 0;
                    for (; (i < len) && (getTextBytes()[off + i] != '='); i++) {
                        /* Stub */
                    }
                    // get the property name
                    QString name = QString(getTextBytes());//readUTF(getTextBytes(), off, i);
                    if (name == "") {
                        properties.clear();
                        break;
                    }
                    if (i == len) {
                        properties.insert(name, NO_VALUE);
                    } else {
                        QByteArray value = QByteArray(len - ++i,0);//new byte[len - ++i];
                        //System.arraycopy(getTextBytes(), off + i, value, 0, len - i);
                        QByteArray source = getTextBytes();
                        for(int j = 0; j < source.length()-i; j++)
                        {
//                         value.replace(i, source.at(j+off));
                        }
                        properties.insert(name, value);
                        off += len;
                    }
                }
            } catch (Exception exception) {
                // We should get better logging.
//                logger->log(Level::WARNING, "Malformed TXT Field " + exception.getMessage());
            }
            this->_props = properties;
        }
        return (!_props.isEmpty() ? _props : QMap<QString, QByteArray>());//Collections.<String, byte[]> emptyMap());
    }
#if 0
    /**
     * JmDNS callback to update a DNS record.
     *
     * @param dnsCache
     * @param now
     * @param rec
     */
    @Override
    /*public*/ void updateRecord(DNSCache dnsCache, long now, DNSEntry rec) {
        if ((rec instanceof DNSRecord) && !rec.isExpired(now)) {
            boolean serviceUpdated = false;
            switch (rec.getRecordType()) {
                case TYPE_A: // IPv4
                    if (rec.getName().equalsIgnoreCase(this->getServer())) {
                        _ipv4Addresses.add((Inet4Address) ((DNSRecord.Address) rec).getAddress());
                        serviceUpdated = true;
                    }
                    break;
                case TYPE_AAAA: // IPv6
                    if (rec.getName().equalsIgnoreCase(this->getServer())) {
                        _ipv6Addresses.add((Inet6Address) ((DNSRecord.Address) rec).getAddress());
                        serviceUpdated = true;
                    }
                    break;
                case TYPE_SRV:
                    if (rec.getName().equalsIgnoreCase(this->getQualifiedName())) {
                        DNSRecord.Service srv = (DNSRecord.Service) rec;
                        boolean serverChanged = (_server == null) || !_server.equalsIgnoreCase(srv.getServer());
                        _server = srv.getServer();
                        _port = srv.getPort();
                        _weight = srv.getWeight();
                        _priority = srv.getPriority();
                        if (serverChanged) {
                            _ipv4Addresses.clear();
                            _ipv6Addresses.clear();
                            for (DNSEntry entry : dnsCache.getDNSEntryList(_server, DNSRecordType.TYPE_A, DNSRecordClass.CLASS_IN)) {
                                this->updateRecord(dnsCache, now, entry);
                            }
                            for (DNSEntry entry : dnsCache.getDNSEntryList(_server, DNSRecordType.TYPE_AAAA, DNSRecordClass.CLASS_IN)) {
                                this->updateRecord(dnsCache, now, entry);
                            }
                            // We do not want to trigger the listener in this case as it will be triggered if the address resolves.
                        } else {
                            serviceUpdated = true;
                        }
                    }
                    break;
                case TYPE_TXT:
                    if (rec.getName().equalsIgnoreCase(this->getQualifiedName())) {
                        DNSRecord.Text txt = (DNSRecord.Text) rec;
                        _text = txt.getText();
                        _props = null; // set it null for apply update text data
                        serviceUpdated = true;
                    }
                    break;
                case TYPE_PTR:
                    if ((this->getSubtype().length() == 0) && (rec.getSubtype().length() != 0)) {
                        _subtype = rec.getSubtype();
                        serviceUpdated = true;
                    }
                    break;
                default:
                    break;
            }
            if (serviceUpdated && this->hasData()) {
                JmDNSImpl dns = this->getDns();
                if (dns != null) {
                    ServiceEvent event = ((DNSRecord) rec).getServiceEvent(dns);
                    event = new ServiceEventImpl(dns, event.getType(), event.getName(), this);
                    dns.handleServiceResolved(event);
                }
            }
            // This is done, to notify the wait loop in method JmDNS.waitForInfoData(ServiceInfo info, int timeout);
            synchronized (this) {
                this->notifyAll();
            }
        }
    }
    /**
     * Returns true if the service info is filled with data.
     *
     * @return <code>true</code> if the service info has data, <code>false</code> otherwise.
     */
    @Override
    /*public*/ synchronized boolean hasData() {
        return this->getServer() != null && this->hasInetAddress() && this->getTextBytes() != null && this->getTextBytes().length > 0;
        // return this->getServer() != null && (this->getAddress() != null || (this->getTextBytes() != null && this->getTextBytes().length > 0));
    }
    /*private*/ final boolean hasInetAddress() {
        return _ipv4Addresses.size() > 0 || _ipv6Addresses.size() > 0;
    }
    // State machine
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean advanceState(DNSTask task) {
        return _state.advanceState(task);
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean revertState() {
        return _state.revertState();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean cancelState() {
        return _state.cancelState();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean closeState() {
        return this->_state.closeState();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean recoverState() {
        return this->_state.recoverState();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ void removeAssociationWithTask(DNSTask task) {
        _state.removeAssociationWithTask(task);
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ void associateWithTask(DNSTask task, DNSState state) {
        _state.associateWithTask(task, state);
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isAssociatedWithTask(DNSTask task, DNSState state) {
        return _state.isAssociatedWithTask(task, state);
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isProbing() {
        return _state.isProbing();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isAnnouncing() {
        return _state.isAnnouncing();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isAnnounced() {
        return _state.isAnnounced();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isCanceling() {
        return this->_state.isCanceling();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isCanceled() {
        return _state.isCanceled();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isClosing() {
        return _state.isClosing();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean isClosed() {
        return _state.isClosed();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean waitForAnnounced(long timeout) {
        return _state.waitForAnnounced(timeout);
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean waitForCanceled(long timeout) {
        return _state.waitForCanceled(timeout);
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ int hashCode() {
        return getQualifiedName().hashCode();
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ boolean equals(Object obj) {
        return (obj instanceof ServiceInfoImpl) && getQualifiedName().equals(((ServiceInfoImpl) obj).getQualifiedName());
    }
    /**
     * {@inheritDoc}
     */
    @Override
    /*public*/ String getNiceTextString() {
        StringBuffer buf = new StringBuffer();
        for (int i = 0, len = this->getTextBytes().length; i < len; i++) {
            if (i >= 200) {
                buf.append("...");
                break;
            }
            int ch = getTextBytes()[i] & 0xFF;
            if ((ch < ' ') || (ch > 127)) {
                buf.append("\\0");
                buf.append(Integer.toString(ch, 8));
            } else {
                buf.append((char) ch);
            }
        }
        return buf.toString();
    }
#endif
    /*
     * (non-Javadoc)
     * @see javax.jmdns.ServiceInfo#clone()
     */
    //@Override
    /*public*/ ServiceInfoImpl* ServiceInfoImpl::clone() {
        ServiceInfoImpl* serviceInfo = new ServiceInfoImpl(this->getQualifiedNameMap(), _port, _weight, _priority, _persistent, _text);
     #if 0
        Inet6Address[] ipv6Addresses = this->getInet6Addresses();
        for (Inet6Address address : ipv6Addresses) {
            serviceInfo._ipv6Addresses.add(address);
        }
        Inet4Address[] ipv4Addresses = this->getInet4Addresses();
        for (Inet4Address address : ipv4Addresses) {
            serviceInfo._ipv4Addresses.add(address);
        }
#endif
        return serviceInfo;
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ServiceInfoImpl::toString() {
        QString buf;// = new StringBuilder();
//        buf.append("[" + this->getClass().getSimpleName() + "@" + System.identityHashCode(this) + " ");
        buf.append("name: '");
        buf.append((this->getName().length() > 0 ? this->getName() + "." : "") + this->getTypeWithSubtype());
        buf.append("' address: '");
#if 1
        QList<InetAddress*> addresses = this->getInetAddresses();
        if (addresses.length() > 0) {
            for (InetAddress* address : addresses) {
                buf.append(address->toString());
                buf.append(':');
                buf.append(this->getPort());
                buf.append(' ');
            }
        } else {
            buf.append("(null):");
            buf.append(this->getPort());
        }
#endif
        buf.append("' status: '");
        buf.append(_state->toString());
        buf.append(this->isPersistent() ? "' is persistent," : "',");
        buf.append(" has ");
        buf.append(this->hasData() ? "" : "NO ");
        buf.append("data");
        if (this->getTextBytes().length() > 0) {
            // buf.append("\n");
            // buf.append(this->getNiceTextString());
            QMap<QString, QByteArray> properties = this->getProperties();
            if (!properties.isEmpty()) {
                buf.append("\n");
                for (QString key : properties.keys()) {
                    buf.append("\t" + key + ": " +  QString(properties.value(key)) + "\n");
                }
            } else {
                buf.append(" empty");
            }
        }
        buf.append(']');
        return buf;
    }
#if 0
    /*public*/ Collection<DNSRecord> answers(boolean unique, int ttl, HostInfo localHost) {
        List<DNSRecord> list = new ArrayList<DNSRecord>();
        if (this->getSubtype().length() > 0) {
            list.add(new Pointer(this->getTypeWithSubtype(), DNSRecordClass.CLASS_IN, DNSRecordClass.NOT_UNIQUE, ttl, this->getQualifiedName()));
        }
        list.add(new Pointer(this->getType(), DNSRecordClass.CLASS_IN, DNSRecordClass.NOT_UNIQUE, ttl, this->getQualifiedName()));
        list.add(new Service(this->getQualifiedName(), DNSRecordClass.CLASS_IN, unique, ttl, _priority, _weight, _port, localHost.getName()));
        list.add(new Text(this->getQualifiedName(), DNSRecordClass.CLASS_IN, unique, ttl, this->getTextBytes()));
        return list;
    }
#endif
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void ServiceInfoImpl::setText(QByteArray text) throw (IllegalStateException) {
        /*synchronized (this)*/ {
            this->_text = text;
            this->_props = QMap<QString, QByteArray>();
            this->setNeedTextAnnouncing(true);
        }
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void ServiceInfoImpl::setText(QMap<QString, QVariant> props) throw (IllegalStateException) {
        this->setText(textFromProperties(props));
    }
    /**
     * This is used internally by the framework
     *
     * @param text
     */
    void ServiceInfoImpl::_setText(QByteArray text) {
        this->_text = text;
        this->_props = QMap<QString, QByteArray>();
    }

    /*private*/ /*static*/ QByteArray ServiceInfoImpl::textFromProperties(QMap<QString, QVariant> props) {
        QByteArray text;// = null;

        if (!props.isEmpty())
        {
#if 1
//            try {
                //ByteArrayOutputStream out = new ByteArrayOutputStream(256);
          QByteArray out;
                for (QString key : props.keys()) {
                    QVariant val = props.value(key);
//                    ByteArrayOutputStream out2 = new ByteArrayOutputStream(100);
                    QByteArray out2;
//                    writeUTF(out2, key);
                    out2.append(key.toUtf8());
                    if (val.isNull()) {
                        // Skip
                    } else if (val.canConvert(QMetaType::QString)) {
                        //out2.write('=');
                     out2.append(QString("=").toUtf8());
                        //writeUTF(out2, (String) val);
                     out2.append(val.toString().toUtf8());
                    } else if (val.canConvert(QMetaType::QByteArray)) {
//                        byte[] bval = (byte[]) val;
//                        if (bval.length > 0) {
//                            out2.write('=');
//                            out2.write(bval, 0, bval.length);
//                        } else {
//                            val = null;
//                        }
                     out2.append(val.toByteArray());
                    } else {
                        throw  IllegalArgumentException("invalid property value: " + val.toString());
                    }
                    QByteArray data = out2; //.toByteArray();
                    if (data.length() > 255) {
                        throw  IOException("Cannot have individual values larger that 255 chars. Offending value: " + key + (!val.isNull() ? "" : "=" + val.toString()));
                    }
//                    out.write((byte) data.length);
//                    out.write(data, 0, data.length);
                    out.append(data, data.length());
                    out.append( data);
                }
                text = out;//out.toByteArray();
//            } catch (IOException e) {
//                throw RuntimeException("unexpected exception: " + e);
//            }
#endif
        }

        //return (!text.isEmpty() && text.length() > 0 ? text : DNSRecord.EMPTY_TXT);

        return text;
    }

    /*public*/ void ServiceInfoImpl::setDns(JmDNSImpl* dns) {
        this->_state->setDns(dns);
    }
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ JmDNSImpl* ServiceInfoImpl::getDns() {
//        return this->_state->getDns();
     return nullptr;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool ServiceInfoImpl::isPersistent() {
        return _persistent;
    }

    /**
     * @param needTextAnnouncing
     *            the needTextAnnouncing to set
     */
    /*public*/ void ServiceInfoImpl::setNeedTextAnnouncing(bool needTextAnnouncing) {
        this->_needTextAnnouncing = needTextAnnouncing;
        if (this->_needTextAnnouncing) {
            _state->setTask(nullptr);
        }
    }
    /**
     * @return the needTextAnnouncing
     */
    /*public*/ bool ServiceInfoImpl::needTextAnnouncing() {
        return _needTextAnnouncing;
    }
#if 0
    /**
     * @return the delegate
     */
    Delegate getDelegate() {
        return this->_delegate;
    }
    /**
     * @param delegate
     *            the delegate to set
     */
    void setDelegate(Delegate delegate) {
        this->_delegate = delegate;
    }
}
#endif
