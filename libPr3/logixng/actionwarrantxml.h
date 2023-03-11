#ifndef ACTIONWARRANTXML_H
#define ACTIONWARRANTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionWarrantXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
public:
    Q_INVOKABLE explicit ActionWarrantXml(QObject *parent = nullptr);
    ~ActionWarrantXml() {}
    ActionWarrantXml(const ActionWarrantXml& ) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionWarrantXml)
#endif // ACTIONWARRANTXML_H
