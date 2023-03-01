#ifndef ENABLELOGIXXML_H
#define ENABLELOGIXXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class EnableLogixXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit EnableLogixXml(QObject *parent = nullptr);
    ~EnableLogixXml() {}
    EnableLogixXml(const EnableLogixXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;   // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(EnableLogixXml)
#endif // ENABLELOGIXXML_H
