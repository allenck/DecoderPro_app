#ifndef ZEROCONFSERVICE_H
#define ZEROCONFSERVICE_H

#include <QObject>
#include <qzeroconf.h>
#include "quietshutdowntask.h"
#include "serviceinfoimpl.h"
#include "zeroconfeventlistener.h"
#include "jmdns.h"
#include "inetaddress.h"
#include "exceptions.h"

class Preferences;
class Logger;
class ZeroConfService : public QObject
{
 Q_OBJECT
public:
 /*public*/ static /*final*/ QString IPv4;// = "IPv4";
 /*public*/ static /*final*/ QString IPv6;// = "IPv6";
 /*public*/ static ZeroConfService* create(QString type, int port);
 /*public*/ static ZeroConfService* create(QString type, int port, QMap<QString, QVariant> properties);
 /*public*/ static ZeroConfService* create(QString type, QString name, int port, int weight, int priority, QMap<QString, QVariant> properties);
 /*public*/ QString key();
 /*public*/ QString name();
 /*public*/ QString type();
 /*public*/ ServiceInfo* serviceInfo();
 /*public*/ bool isPublished();
 /*public*/ void publish();
 /*public*/ void addEventListener(ZeroConfServiceListener* l);
 /*public*/ void removeEventListener(ZeroConfServiceListener* l);
 /*public*/ void stop();
 /*public*/ static void stopAll();
 /*public*/ static QList<ZeroConfService*> allServices();
 /*synchronized*/ /*public*/ static QMap<InetAddress*, JmDNS*> netServices();
 /*public*/ static QString hostName(InetAddress* address);
 /*public*/ static QString FQDN(InetAddress* address);
 /*public*/ static QList<InetAddress*> hostAddresses();
 /*public*/ void inetAddressAdded(InetAddress* inetAddress, JmDNS* _DNS);
 /*public*/ void inetAddressRemoved(InetAddress* inetAddress, JmDNS* _DNS);


signals:
 /*public*/  void serviceQueued(ZeroConfServiceEvent* se);

 /*public*/  void servicePublished(ZeroConfServiceEvent* se);

 /*public*/  void serviceUnpublished(ZeroConfServiceEvent* se);


public slots:
 void error(QZeroConf::error_t);
 void servicePublished();
 //void on_servicePublished(ZeroConfServiceEvent* e);
 /*private*/ static QMap<QString, ZeroConfService *> services();
 void addService(QZeroConfService zcs);

private:
 QZeroConf* zeroConf;

 // internal data members
 /*private*/ /*final*/ QMap<InetAddress*, ServiceInfo*> serviceInfos;// = new HashMap<>();
 /*private*/ ServiceInfo* _serviceInfo = nullptr;

 // static data objects
 /*private*/ static /*final*/ QMap<QString, ZeroConfService*> _services;// = new HashMap<>();
 /*private*/ static /*final*/ QMap<InetAddress*, JmDNS*> _netServices;// = new HashMap<>();
// /*private*/ /*final*/ List<ZeroConfServiceListener> listeners = new ArrayList<>();
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(ZeroConfService.class);
// /*private*/ static /*final*/ NetworkListener networkListener = new NetworkListener();
 /*private*/ static /*final*/ ShutDownTask* shutDownTask;// = new ShutDownTask("Stop ZeroConfServices");

 /*private*/ static /*final*/ Preferences* zeroConfPrefs;// = ProfileUtils.getPreferences(ProfileManager.getDefault().getActiveProfile(),
//         ZeroConfService.class,
//         false);
 /*private*/ static void stopAll(/*final*/ bool close);
 /*private*/ ServiceInfo* addServiceInfo(JmDNS* DNS) /*throw (IOException)*/;
 QString currentType;

 protected:
 /**
  * Create a ZeroConfService object.
  *
  * @param service the JmDNS service information
  */
 /*protected*/ ZeroConfService(ServiceInfo* service);
 /*protected*/ static QString key(QString type, QString name);

};
class ZCSShutDownTask : public QuietShutDownTask
{
 Q_OBJECT
 ZeroConfService* zcs;
 /*private*/ bool _isComplete = false;

 public:
 ZCSShutDownTask(QString s);
 /*public*/ bool execute();
 /*public*/ bool isParallel();
 /*public*/ bool isComplete();

};
#endif // ZEROCONFSERVICE_H
