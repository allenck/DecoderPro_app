#ifndef SERVICEINFO_H
#define SERVICEINFO_H

#include <QObject>
#include <QVariant>
#include <qzeroconf.h>
#include "exceptions.h"
class InetAddress;
class Inet4Address;
class Inet6Address;
class ServiceInfo : public QObject
{
 Q_OBJECT
public:
 explicit ServiceInfo(QObject *parent = nullptr);
    ~ServiceInfo() {}
    ServiceInfo(const ServiceInfo&) :QObject() {}
 /*public*/ static /*final*/ QByteArray NO_VALUE;// = new byte[0];
 /* Fields for the fully qualified map.
 */
/*public*/ enum Fields {
    /**
     * Domain Field.
     */
    Domain,
    /**
     * Protocol Field.
     */
    Protocol,
    /**
     * Application Field.
     */
    Application,
    /**
     * Instance Field.
     */
    Instance,
    /**
     * Subtype Field.
     */
    Subtype
};
 /*public*/ static ServiceInfo* create(/*final*/ QString type, /*final*/ QString name, /*final*/ QString subtype, /*final*/ int port, /*final*/ QString text);
 /*public*/ static ServiceInfo* create(/*final*/ QString type, /*final*/ QString name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ QString text);
 /*public*/ static ServiceInfo* create(/*final*/ QString type, /*final*/ QString name, /*final*/ QString subtype, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/QString text);
 /*public*/ static ServiceInfo* create(/*final*/ QString type, /*final*/ QString name, /*final*/ int port, /*final*/ int weight, /*final*/ int priority, /*final*/ QMap</*final*/QString, QVariant> props);


 /*public*/ /*abstract*/ virtual bool hasData();
 /*public*/ /*abstract*/ virtual QString getType();
 /*public*/ /*abstract*/ virtual QString getTypeWithSubtype();
 /*public*/ /*abstract*/ virtual QString getName();
 /*public*/ /*abstract*/ virtual QString getKey();
 /*public*/ /*abstract*/ virtual QString getQualifiedName();
 /*public*/ /*abstract*/ virtual QString getServer();
 QT_DEPRECATED
 /*public*/ /*abstract*/ virtual QString getHostAddress();
 /*public*/ /*abstract*/ virtual QStringList getHostAddresses();
#if 0
 QT_DEPRECATED
 /*public*/ /*abstract*/ virtual InetAddress getAddress();
 QT_DEPRECATED
 /*public*/ /*abstract*/ virtual InetAddress getInetAddress();
 QT_DEPRECATED
 /*public*/ /*abstract*/ virtual Inet4Address getInet4Address();
 QT_DEPRECATED
 /*public*/ /*abstract*/ virtual Inet6Address getInet6Address();
#endif
 /*public*/ /*abstract*/ virtual QList<InetAddress*> getInetAddresses();
 /*public*/ /*abstract*/ virtual QList<Inet4Address*> getInet4Addresses();
 /*public*/ /*abstract*/ virtual QList<Inet6Address*> getInet6Addresses();
 /*public*/ /*abstract*/ virtual int getPort();
 /*public*/ /*abstract*/ virtual int getPriority();
 /*public*/ /*abstract*/ virtual int getWeight();
 /*public*/ /*abstract*/ virtual QByteArray getTextBytes();
 QT_DEPRECATED /*public*/ /*abstract*/ virtual QString getTextString();
 QT_DEPRECATED
 /*public*/ /*abstract*/ virtual QString getURL();
 /*public*/ /*abstract*/ virtual QStringList getURLs();
 QT_DEPRECATED
 /*public*/ /*abstract*/ virtual QString getURL(QString protocol);
 /*public*/ /*abstract*/ virtual QStringList getURLs(QString protocol);
 /*public*/ /*abstract*/ virtual QByteArray getPropertyBytes(/*final*/ QString name);
 /*public*/ /*abstract*/ virtual QString getPropertyString(/*final*/ QString name);
 /*public*/ /*abstract*/ virtual QStringListIterator getPropertyNames();
 /*public*/ /*abstract*/ virtual QString getNiceTextString();
 /*public*/ /*abstract*/ virtual void setText(/*final*/ QByteArray text) /*throw (IllegalStateException)*/;
 /*public*/ /*abstract*/ virtual void setText(/*final*/ QMap<QString, QVariant> props) /*throw (IllegalStateException)*/;
 /*public*/ /*abstract*/ virtual bool isPersistent();
 /*public*/ /*abstract*/ virtual QString getDomain();
 /*public*/ /*abstract*/ virtual QString getProtocol();
 /*public*/ /*abstract*/ virtual QString getApplication();
 /*public*/ /*abstract*/ virtual QString getSubtype();
 /*public*/ /*abstract*/ virtual QMap<Fields, QString> getQualifiedNameMap();
 /*public*/ virtual QString toString() {return "";}
 /*public*/ virtual ServiceInfo* clone();

signals:

public slots:
};

#endif // SERVICEINFO_H
