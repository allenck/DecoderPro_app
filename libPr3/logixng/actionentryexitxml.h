#ifndef ACTIONENTRYEXITXML_H
#define ACTIONENTRYEXITXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionEntryExitXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionEntryExitXml(QObject *parent = nullptr);
    ~ActionEntryExitXml() {}
    ActionEntryExitXml(const ActionEntryExitXml&) :AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;   // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionEntryExitXml)
#endif // ACTIONENTRYEXITXML_H
