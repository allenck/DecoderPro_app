#ifndef SHUTDOWNCOMPUTERXML_H
#define SHUTDOWNCOMPUTERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ShutdownComputerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit ShutdownComputerXml(QObject *parent = nullptr);
    ~ShutdownComputerXml() {}
    ShutdownComputerXml(const ShutdownComputerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(ShutdownComputerXml)
#endif // SHUTDOWNCOMPUTERXML_H
