#ifndef RFIDSENSORMANAGERXML_H
#define RFIDSENSORMANAGERXML_H
#include "abstractsensormanagerconfigxml.h"


class RfidSensorManagerXml : public AbstractSensorManagerConfigXML
{
public:
 Q_INVOKABLE RfidSensorManagerXml(QObject *parent= nullptr);
 ~RfidSensorManagerXml() {}
 RfidSensorManagerXml(const RfidSensorManagerXml&) : AbstractSensorManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement sensors);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException);

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(RfidSensorManagerXml)
#endif // RFIDSENSORMANAGERXML_H
