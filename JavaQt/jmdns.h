#ifndef JMDNS_H
#define JMDNS_H

#include <QObject>
#include "inetaddress.h"

class ServiceInfo;
class JmDNS : public QObject
{
 Q_OBJECT
public:
 explicit JmDNS(QObject *parent = nullptr);
 /*public*/ static JmDNS* create() /*throw (IOException)*/;
 /*public*/ static JmDNS* create(/*final*/ InetAddress* addr) /*throw (IOException)*/;
 /*public*/ static JmDNS* create(/*final*/ QString name) /*throw (IOException)*/ ;
 /*public*/ static JmDNS* create(/*final*/ InetAddress* addr, /*final*/ QString name) /*throw (IOException)*/;
 /*public*/ /*abstract*/ virtual QString getName();
 /*public*/ /*abstract*/ virtual QString getHostName();
 /*public*/ /*abstract*/ virtual InetAddress* getInetAddress() /*throw (IOException)*/;
 /*public*/ /*abstract*/ virtual bool isClosing();
 /*public*/ /*abstract*/ virtual bool isClosed();

 /*public*/ static QString VERSION;
 /*public*/ /*abstract*/ virtual void registerService(ServiceInfo* /*info*/) /*throw (IOException)*/;
 /*public*/ /*abstract*/ virtual void unregisterService(ServiceInfo* info);
 /*public*/ /*abstract*/ virtual void unregisterAllServices();

signals:

public slots:
};

#endif // JMDNS_H
