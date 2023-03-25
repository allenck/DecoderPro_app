#ifndef DOSTRINGACTIONXML_H
#define DOSTRINGACTIONXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DoStringActionXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DoStringActionXml(QObject *parent = nullptr);
    ~DoStringActionXml() {}
    DoStringActionXml(const DoStringActionXml&) : AbstractNamedBeanManagerConfigXML() {}

    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(DoStringActionXml)
#endif // DOSTRINGACTIONXML_H
