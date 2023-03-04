#ifndef ACTIONLIGHTINTENSITYXML_H
#define ACTIONLIGHTINTENSITYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionLightIntensityXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionLightIntensityXml(QObject *parent = nullptr);
    ~ActionLightIntensityXml() {}
    ActionLightIntensityXml(const ActionLightIntensityXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(ActionLightIntensityXml)
#endif // ACTIONLIGHTINTENSITYXML_H
