#ifndef JMRICLIENTSENSORMANAGERXML_H
#define JMRICLIENTSENSORMANAGERXML_H
#include "abstractsensormanagerconfigxml.h"

class JMRIClientSensorManagerXml : public AbstractSensorManagerConfigXML
{
public:
 Q_INVOKABLE JMRIClientSensorManagerXml(QObject* parent = nullptr);
 ~JMRIClientSensorManagerXml() {}
 JMRIClientSensorManagerXml(const JMRIClientSensorManagerXml&) : AbstractSensorManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement sensors);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException);

private:
 static Logger* log;
};

#endif // JMRICLIENTSENSORMANAGERXML_H
