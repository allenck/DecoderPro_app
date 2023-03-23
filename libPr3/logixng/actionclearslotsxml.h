#ifndef ACTIONCLEARSLOTSXML_H
#define ACTIONCLEARSLOTSXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionClearSlotsXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionClearSlotsXml(QObject *parent = nullptr);
    ~ActionClearSlotsXml() {}
    ActionClearSlotsXml(const ActionClearSlotsXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionClearSlotsXml)
#endif // ACTIONCLEARSLOTSXML_H
