#ifndef VIRTUALSIGNALMASTXML_H
#define VIRTUALSIGNALMASTXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"

class VirtualSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VirtualSignalMastXml(QObject *parent = 0);
 ~VirtualSignalMastXml()  override{}
 VirtualSignalMastXml(const VirtualSignalMastXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception) override;
    /*public*/ void load(QDomElement element, QObject* o)  throw (Exception) override;

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(VirtualSignalMastXml)
#endif // VIRTUALSIGNALMASTXML_H
