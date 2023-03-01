#ifndef ACTIONTURNOUTLOCKXML_H
#define ACTIONTURNOUTLOCKXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionTurnoutLockXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ActionTurnoutLockXml(QObject *parent = nullptr);
    ~ActionTurnoutLockXml() {}
    ActionTurnoutLockXml(const ActionTurnoutLockXml&) :AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;     // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionTurnoutLockXml)
#endif // ACTIONTURNOUTLOCKXML_H
