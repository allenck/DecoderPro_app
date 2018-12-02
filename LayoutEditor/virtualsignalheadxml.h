#ifndef VIRTUALSIGNALHEADXML_H
#define VIRTUALSIGNALHEADXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT VirtualSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VirtualSignalHeadXml(QObject *parent = 0);
 ~VirtualSignalHeadXml() {}
 VirtualSignalHeadXml(const VirtualSignalHeadXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement shared, QDomElement perNode);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) ;

signals:

public slots:
private:
    Logger* log;

};
Q_DECLARE_METATYPE(VirtualSignalHeadXml)
#endif // VIRTUALSIGNALHEADXML_H
