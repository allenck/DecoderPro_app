#ifndef ACTIONUPDATESLOTSXML_H
#define ACTIONUPDATESLOTSXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionUpdateSlotsXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionUpdateSlotsXml(QObject *parent = nullptr);
    ~ActionUpdateSlotsXml() {}
    ActionUpdateSlotsXml(const ActionUpdateSlotsXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionUpdateSlotsXml)
#endif // ACTIONUPDATESLOTSXML_H
