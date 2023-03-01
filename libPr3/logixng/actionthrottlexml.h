#ifndef ACTIONTHROTTLEXML_H
#define ACTIONTHROTTLEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionThrottleXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionThrottleXml(QObject *parent = nullptr);
    ~ActionThrottleXml() {}
    ActionThrottleXml(const ActionThrottleXml&) :AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) override;

};
Q_DECLARE_METATYPE(ActionThrottleXml)
#endif // ACTIONTHROTTLEXML_H
