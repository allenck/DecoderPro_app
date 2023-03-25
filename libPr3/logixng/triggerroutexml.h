#ifndef TRIGGERROUTEXML_H
#define TRIGGERROUTEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class TriggerRouteXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TriggerRouteXml(QObject *parent = nullptr);
    ~TriggerRouteXml() {}
    TriggerRouteXml(const TriggerRouteXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(TriggerRouteXml)
#endif // TRIGGERROUTEXML_H
