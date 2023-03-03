#ifndef ACTIONOBLOCKXML_H
#define ACTIONOBLOCKXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionOBlockXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionOBlockXml(QObject *parent = nullptr);
    ~ActionOBlockXml() {}
    ActionOBlockXml(const ActionOBlockXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;     // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionOBlockXml)
#endif // ACTIONOBLOCKXML_H
