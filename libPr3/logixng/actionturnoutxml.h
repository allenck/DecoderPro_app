#ifndef ACTIONTURNOUTXML_H
#define ACTIONTURNOUTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionTurnoutXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionTurnoutXml(QObject *parent = nullptr);
    ~ActionTurnoutXml() {}
    ActionTurnoutXml(const ActionTurnoutXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;   // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionTurnoutXml)
#endif // ACTIONTURNOUTXML_H
