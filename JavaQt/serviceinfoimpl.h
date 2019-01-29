#ifndef SERVICEINFOIMPL_H
#define SERVICEINFOIMPL_H

#include <QObject>
#include "serviceinfo.h"
#include <QMap>
#include <QByteArray>

class ServiceInfoState;
class JmDNSImpl;
class DNSTask;
class Logger;
class ServiceInfoImpl : public ServiceInfo
{
 Q_OBJECT
public:
 /*public*/ ServiceInfoImpl(QString type, QString name, QString subtype, int port, int weight, int priority, bool persistent, QString text);
 /*public*/ ServiceInfoImpl(QString type, QString name, QString subtype, int port, int weight, int priority, bool persistent, QMap<QString, QVariant> props);

 ServiceInfoImpl(QMap<Fields, QString> qualifiedNameMap, int port, int weight, int priority, bool persistent, QString text);
 /*public*/ static QMap<ServiceInfo::Fields, QString> decodeQualifiedNameMap(QString type, QString name, QString subtype);
 /*public*/ static QMap<ServiceInfo::Fields, QString> decodeQualifiedNameMapForType(QString type);
 ServiceInfoImpl(ServiceInfo* info);
 /*public*/ QString getType();
 /*public*/ QString getTypeWithSubtype() ;
 /*public*/ QString getName();
 /*public*/ QString getKey();
 /*public*/ QList<InetAddress*> getInetAddresses();
 /*public*/ QString getQualifiedName();
 /*public*/ QString getServer();
 /*public*/ int getPort();
 /*public*/ int getPriority();
 /*public*/ int getWeight();
 /*public*/ QByteArray getTextBytes();
 /*public*/ QString getTextString();
 /*public*/ QString getURL();
 /*public*/ QStringList getURLs();
 /*public*/ QString getURL(QString protocol);
 /*public*/ QStringList getURLs(QString protocol);
 /*public*/ QByteArray getPropertyBytes(QString name);
 /*public*/ /*synchronized*/ QString getPropertyString(QString name) ;
 /*public*/ QStringListIterator getPropertyNames();
 /*public*/ QString getApplication();
 /*public*/ QString getDomain();
 /*public*/ QString getProtocol() ;
 /*public*/ QString getSubtype();
 /*public*/ ServiceInfoImpl* clone();
 /*public*/ QString toString();

 /*public*/ void setNeedTextAnnouncing(bool needTextAnnouncing);
 /*public*/ bool needTextAnnouncing();
 /*public*/ void setDns(JmDNSImpl* dns);
 /*public*/ JmDNSImpl* getDns() ;
 /*public*/ bool isPersistent();
 /*public*/ void setText(QByteArray text) throw (IllegalStateException);
 /*public*/ void setText(QMap<QString, QVariant> props) throw (IllegalStateException);
 /*public*/ QList<Inet4Address*> getInet4Addresses() ;
 /*public*/ QList<Inet6Address*> getInet6Addresses();

signals:

public slots:

private:
 /*private*/ static Logger*           logger;// = Logger.getLogger(ServiceInfoImpl.class.getName());
 /*private*/ QString                  _domain;
 /*private*/ QString                  _protocol;
 /*private*/ QString                  _application;
 /*private*/ QString                  _name;
 /*private*/ QString                  _subtype;
 /*private*/ QString                  _server;
 /*private*/ int                     _port;
 /*private*/ int                     _weight;
 /*private*/ int                     _priority;
 /*private*/ QByteArray                    _text;
 /*private*/ QMap<QString, QByteArray>     _props;
 /*private*/ /*final*/ QSet<Inet4Address*> _ipv4Addresses;
 /*private*/ /*final*/ QSet<Inet6Address*> _ipv6Addresses;
 /*private*/ /*transient*/ QString        _key;
 /*private*/ bool                _persistent;
 /*private*/ bool                 _needTextAnnouncing;
 /*private*/ /*final*/ ServiceInfoState*  _state;
// /*private*/ Delegate                _delegate;
 /*private*/ static QString removeSeparators(QString name);
 void common(QMap<ServiceInfo::Fields, QString> qualifiedNameMap, int port, int weight, int priority, bool persistent, QByteArray text);
 /*private*/ static QByteArray textFromProperties(QMap<QString, QVariant> props);
 void setName(QString name);
 void setServer(QString server);
 void addAddress(Inet4Address* addr);
 void addAddress(Inet6Address* addr);
 /*synchronized*/ QMap<QString, QByteArray> getProperties();
 void _setText(QByteArray text);

protected:
 /*protected*/ static QMap<ServiceInfo::Fields, QString> checkQualifiedNameMap(QMap<ServiceInfo::Fields, QString> qualifiedNameMap);
friend class ServiceInfo;
friend class JmDNSImpl;
};

/*private*/ /*final*/ /*static*/ class ServiceInfoState : public QObject // extends DNSStatefulObject.DefaultImplementation
{
 Q_OBJECT
    /// *private*/ static /*final*/ long     serialVersionUID = 1104131034952196820L;
    /*private*/ /*final*/ ServiceInfoImpl* _info;
public:
    /**
     * @param info
     */
    /*public*/ ServiceInfoState(ServiceInfoImpl* info);
    QString toString();
protected:
    //@Override
    /*protected*/ void setTask(DNSTask *task);
    //@Override
    /*public*/ void setDns(JmDNSImpl* dns);

 friend class ServiceInfoImpl;
};

#endif // SERVICEINFOIMPL_H
