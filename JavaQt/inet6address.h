#ifndef INET6ADDRESS_H
#define INET6ADDRESS_H
#include "inetaddress.h"
#include <QNetworkInterface>
#include "exceptions.h"

class UnknownHostException : public Exception
{
public:
 UnknownHostException() {}
};

class Inet6AddressHolder;
class QNetworkInterface;
class Inet6Address : public InetAddress
{
 Q_OBJECT
public:
 Inet6Address();
 Inet6Address(QString hostName, QByteArray addr, int scope_id);
 Inet6Address(QString hostName, QByteArray addr);

private:
 /*final*/ static int INADDRSZ;// = 16;
 /*
  * cached scope_id - for link-local address use only.
  */
 /*private*/ /*transient*/ int cached_scope_id;  // 0
 /*private*/ /*final*/ /*transient*/ Inet6AddressHolder* holder6;
 /*private*/ static /*final*/ long FIELDS_OFFSET;
// /*private*/ static /*final*/ sun.misc.Unsafe UNSAFE;
 /*private*/ void initif(QString hostName,QByteArray addr, QNetworkInterface nif) throw (UnknownHostException);
 /*private*/ /*final*/ static int INT16SZ;// = 2;
 static QString numericToTextFormat(QByteArray src);

 friend class Inet6AddressHolder;
};

/*private*/ class Inet6AddressHolder : public QObject{
Q_OBJECT
    /*private*/ Inet6AddressHolder();
    /*private*/ Inet6AddressHolder( QByteArray ipaddress, int scope_id, bool scope_id_set,
 QNetworkInterface ifname, bool scope_ifname_set);

    QByteArray ipaddress;

    /**
     * scope_id. The scope specified when the object is created. If the object
     * is created with an interface name, then the scope_id is not determined
     * until the time it is needed.
     */
    int scope_id;  // 0

    /**
     * This will be set to true when the scope_id field contains a valid
     * integer scope_id.
     */
    bool scope_id_set;  // false

    /**
     * scoped interface. scope_id is derived from this as the scope_id of the first
     * address whose scope is the same as this address for the named interface.
     */
    QNetworkInterface scope_ifname;  // null

    /**
     * set if the object is constructed with a scoped
     * interface instead of a numeric scope id.
     */
    bool scope_ifname_set; // false;

    void setAddr(QByteArray addr) ;
    void init(QByteArray addr, int scope_id);
    void init(QByteArray addr, QNetworkInterface nif) throw (UnknownHostException);
    QString getHostAddress();
    /*public*/ bool equals(QObject* o);
    /*public*/ int hashCode();
    bool isIPv4CompatibleAddress();
    bool isMulticastAddress();
    bool isAnyLocalAddress();
    bool isLoopbackAddress();
    bool isLinkLocalAddress();
    bool isSiteLocalAddress();
    bool isMCGlobal();
    bool isMCNodeLocal();
    bool isMCLinkLocal();
    bool isMCSiteLocal();
    bool isMCOrgLocal();
    friend class Inet6Address;
};

#endif // INET6ADDRESS_H
