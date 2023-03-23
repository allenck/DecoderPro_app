#ifndef STRINGACTIONSTRINGIOXML_H
#define STRINGACTIONSTRINGIOXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class StringActionStringIOXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit StringActionStringIOXml(QObject *parent = nullptr);
    ~StringActionStringIOXml() {}
    StringActionStringIOXml(const StringActionStringIOXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(StringActionStringIOXml)
#endif // STRINGACTIONSTRINGIOXML_H
