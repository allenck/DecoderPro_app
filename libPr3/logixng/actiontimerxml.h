#ifndef ACTIONTIMERXML_H
#define ACTIONTIMERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionTimerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionTimerXml(QObject *parent = nullptr);\
    ~ActionTimerXml() {}
    ActionTimerXml(const ActionTimerXml&) : AbstractNamedBeanManagerConfigXML() {}
};
Q_DECLARE_METATYPE(ActionTimerXml)
#endif // ACTIONTIMERXML_H
