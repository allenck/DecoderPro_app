#ifndef INETADDRESS_H
#define INETADDRESS_H

#include <QObject>
#include <QHostAddress>
#include "exceptions.h"
#include <QNetworkInterface>

class InetAddressHolder;
class InetAddress : public QObject
{
 Q_OBJECT
public:
 explicit InetAddress();
 InetAddress(QHostAddress hostAddress);
 /*public*/ QString getHostAddress();
 QHostAddress getQHostAddress();
 /*public*/ bool isMulticastAddress();
 /*public*/ bool isAnyLocalAddress();
 /*public*/ bool isLoopbackAddress();
 /*public*/ bool isLinkLocalAddress();
 /*public*/ bool isSiteLocalAddress();
 /*public*/ bool isMCGlobal();
 /*public*/ bool isMCNodeLocal();
 /*public*/ bool isMCLinkLocal();
 /*public*/ bool isMCSiteLocal();
 /*public*/ bool isMCOrgLocal();
 /*public*/ bool isReachable(int timeout) throw (IOException);
 /*public*/ bool isReachable(QNetworkInterface netif, int ttl,
                            int timeout) throw (IOException) ;
 /*public*/ QString getHostName();
 QString getHostName(bool check);
 /*public*/ QString getCanonicalHostName();
 /*public*/ QByteArray getAddress();
 /*public*/ int hashCode();
 /*public*/ bool equals(QObject* obj);
 /*public*/ QString toString();

signals:

public slots:
private:
 QHostAddress hostAddress;
 /* Used to store the serializable fields of InetAddress */
 /*final*/ /*transient*/ InetAddressHolder* _holder;
 InetAddressHolder* holder();
 static /*final*/ int IPv4;// = 1;
 static /*final*/ int IPv6;// = 2;
 /*private*/ static QString getHostFromNameService(InetAddress* addr, bool check);
 /*private*/ /*transient*/ QString canonicalHostName;// = null;

 friend class Inet4Address;
 friend class Inet6Address;
};

/* Specify address family preference */
/*static*/ class InetAddressHolder {
 static /*transient*/ bool preferIPv6Address;// = false;

    /**
     * Reserve the original application specified hostname.
     *
     * The original hostname is useful for domain-based endpoint
     * identification (see RFC 2818 and RFC 6125).  If an address
     * was created with a raw IP address, a reverse name lookup
     * may introduce endpoint identification security issue via
     * DNS forging.
     *
     * Oracle JSSE provider is using this original hostname, via
     * sun.misc.JavaNetAccess, for SSL/TLS endpoint identification.
     *
     * Note: May define a new public method in the future if necessary.
     */
    QString originalHostName;

    InetAddressHolder();
    InetAddressHolder(QString hostName, int address, int family);
    void init(QString hostName, int family) ;
    QString hostName;
    QString getHostName() ;
    QString getOriginalHostName() ;
    int address;
    int getAddress();
    int family;
    int getFamily();
    /* Used to store the best available hostname */

    friend class Inet4Address;
    friend class Inet6Address;
friend class InetAddress;
};
#endif // INETADDRESS_H
