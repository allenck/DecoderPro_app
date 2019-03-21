#ifndef ABSTRACTNETWORKCONNECTIONCONFIGXML_H
#define ABSTRACTNETWORKCONNECTIONCONFIGXML_H
#include "abstractconnectionconfigxml.h"
#include "libPr3_global.h"

class NetworkPortAdapter;
class LIBPR3SHARED_EXPORT AbstractNetworkConnectionConfigXml : public AbstractConnectionConfigXml
{
 Q_OBJECT
public:
 explicit AbstractNetworkConnectionConfigXml(QObject *parent = 0);
 /*public*/ QDomElement store(QObject* o, bool shared);
 /*public*/ QDomElement store(QObject* o); //throw (Exception);
 // *public*/ bool load(QDomElement e) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ bool load(QDomElement shared, QDomElement perNode); //throws Exception

signals:

public slots:
private:
 Logger* log;
protected:
 /*protected*/ NetworkPortAdapter* adapter;
 /*abstract*/ /*protected*/ virtual void getInstance();

 /*abstract*/ /*protected*/ virtual void _register();

 /*protected*/ virtual void getInstance(QObject* object);
 /*protected*/ virtual void extendElement(QDomElement e);
 // /*protected*/ void unpackElement(QDomElement e);

};

#endif // ABSTRACTNETWORKCONNECTIONCONFIGXML_H
