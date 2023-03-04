#ifndef LOGLOCALVARIABLESXML_H
#define LOGLOCALVARIABLESXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class LogLocalVariablesXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LogLocalVariablesXml(QObject *parent = nullptr);
    ~LogLocalVariablesXml() {}
    LogLocalVariablesXml(const LogLocalVariablesXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) override;

};
Q_DECLARE_METATYPE(LogLocalVariablesXml)
#endif // LOGLOCALVARIABLESXML_H
