#ifndef DOANALOGACTIONXML_H
#define DOANALOGACTIONXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DoAnalogActionXml : public AbstractNamedBeanManagerConfigXML
{
   Q_OBJECT
public:
    Q_INVOKABLE explicit DoAnalogActionXml(QObject *parent = nullptr);
    ~DoAnalogActionXml() {}
    DoAnalogActionXml(const DoAnalogActionXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(DoAnalogActionXml)
#endif // DOANALOGACTIONXML_H
