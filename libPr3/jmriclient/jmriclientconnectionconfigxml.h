#ifndef JMRICLIENTCONNECTIONCONFIGXML_H
#define JMRICLIENTCONNECTIONCONFIGXML_H
#include "abstractnetworkconnectionconfigxml.h"

class JMRIClientConnectionConfigXml : public AbstractNetworkConnectionConfigXml
{
 Q_OBJECT
public:
 Q_INVOKABLE JMRIClientConnectionConfigXml(QObject* parent = nullptr);
 ~JMRIClientConnectionConfigXml() {}
 JMRIClientConnectionConfigXml(const JMRIClientConnectionConfigXml&) : AbstractNetworkConnectionConfigXml() {}
protected:
 /*protected*/ void getInstance();
 /*protected*/ void getInstance(QObject* object);
 /*protected*/ void _register();
 /*protected*/ void extendElement(QDomElement e);
 /*protected*/ void unpackElement(QDomElement shared, QDomElement perNode);
 /*protected*/ QString javaClass();

};
Q_DECLARE_METATYPE(JMRIClientConnectionConfigXml)
#endif // JMRICLIENTCONNECTIONCONFIGXML_H
