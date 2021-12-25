#ifndef JMDNSIMPL_H
#define JMDNSIMPL_H
#include "jmdns.h"
#include "inetaddress.h"
#include <QSet>
#include <QMap>
#include "serviceinfoimpl.h"
#include <QHostInfo>

class Logger;
class JmDNSImpl : public JmDNS
{
 Q_OBJECT
public:
 /*public*/ JmDNSImpl(InetAddress* address, QString name) /*throw (IOException)*/;

 /*public*/ enum Operation {
     Remove, Update, Add, RegisterServiceType, Noop
 };
 /*public*/ QString getName();
 /*public*/ QString getHostName();
 /*public*/ QHostInfo getLocalHost();
 /*public*/ InetAddress* getInetAddress() /*throw (IOException)*/;
 /*public*/ bool isClosing();
 /*public*/ bool isClosed();

 /*public*/ void registerService(ServiceInfo* infoAbstract) /*throw (IOException)*/;
 /*public*/ void unregisterService(ServiceInfo* infoAbstract);
 /*public*/ void close();


private:
 static Logger* logger;
 /**
  * This is the multicast group, we are listening to for multicast DNS messages.
  */
 /*private*/ volatile InetAddress*     _group;
#if 0
 /**
  * This is our multicast socket.
  */
 /*private*/ volatile MulticastSocket _socket;

 /**
  * Holds instances of JmDNS.DNSListener. Must by a synchronized collection, because it is updated from concurrent threads.
  */
 /*private*/ final List<DNSListener> _listeners;

 /**
  * Holds instances of ServiceListener's. Keys are Strings holding a fully qualified service type. Values are LinkedList's of ServiceListener's.
  */
 /* default */ final ConcurrentMap<String, List<ServiceListenerStatus>> _serviceListeners;

 /**
  * Holds instances of ServiceTypeListener's.
  */
 /*private*/ final Set<ServiceTypeListenerStatus> _typeListeners;

 /**
  * Cache for DNSEntry's.
  */
 /*private*/ final DNSCache _cache;
#endif
 /**
  * This hashtable holds the services that have been registered. Keys are instances of String which hold an all lower-case version of the fully qualified service name. Values are instances of ServiceInfo.
  */
 /*private*/ /*final*/ QMap<QString, ServiceInfo*> _services;
#if 0
 /**
  * This hashtable holds the service types that have been registered or that have been received in an incoming datagram.<br/>
  * Keys are instances of String which hold an all lower-case version of the fully qualified service type.<br/>
  * Values hold the fully qualified service type.
  */
 /*private*/ final ConcurrentMap<String, ServiceTypeEntry> _serviceTypes;

 /*/*private*/*/ volatile Delegate _delegate;
#endif
 /**
  * Handle on the local host
  */
 /*private*/ QHostInfo _localHost;/*private*/
 /*final*/ QSet<QMap<QString, QString> > _entrySet;

 /*private*/ /*final*/ QString _type;
 /*private*/ /*final*/ QString _name;

};

#endif // JMDNSIMPL_H
