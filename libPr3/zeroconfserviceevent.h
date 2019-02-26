#ifndef ZEROCONFSERVICEEVENT_H
#define ZEROCONFSERVICEEVENT_H
#include "eventobject.h"
#include "inetaddress.h"
#include "jmdns.h"

class ZeroConfService;
class JmDNS;
class Logger;
class ZeroConfServiceEvent : public EventObject
{
public:
 //ZeroConfServiceEvent();
 /*public*/ ZeroConfService* getService();
 /*public*/ JmDNS* getDNS();
/*public*/ InetAddress *getAddress();
private:
 static Logger* log;
 /*private*/ /*final*/ ZeroConfService* service;
 /*private*/ /*final*/ JmDNS* dns;

protected:
 /*protected*/ ZeroConfServiceEvent(ZeroConfService* service, JmDNS* dns);
 friend class ZeroConfService;
};

#endif // ZEROCONFSERVICEEVENT_H
