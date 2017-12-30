#ifndef ZEROCONFSERVICE_H
#define ZEROCONFSERVICE_H

#include <QObject>
#include <QHostAddress>

class ZCShutDownTask;
class NetworkListener;
class Logger;
class ZeroConfServiceListener;
class JmDNS;
class ServiceInfo;
class ZeroConfService : public QObject
{
 Q_OBJECT
public:
 explicit ZeroConfService(QObject *parent = 0);
 /*public*/ static /*final*/ QString IPv4;// = "IPv4";
 /*public*/ static /*final*/ QString IPv6;// = "IPv6";

signals:

public slots:

private:
 /*private*/ /*final*/ QMap<QHostAddress, ServiceInfo*>* serviceInfos;// = new QMap<>();
 /*private*/ ServiceInfo* serviceInfo;// = NULL;
 // static data objects
 /*private*/ static /*final*/ QMap<QString, ZeroConfService*>* _services;// = new QMap<>();
 /*private*/ static /*final*/ QMap<QHostAddress, JmDNS*>* netServices;// = new QMap<>();
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(ZeroConfService.class.getName());
#if 0
 /*private*/ static /*final*/ NetworkListener* networkListener;// = new NetworkListener();
 /*private*/ static /*final*/ ZCShutDownTask* shutDownTask;// = new ShutDownTask("Stop ZeroConfServices");
#endif

};

#endif // ZEROCONFSERVICE_H
