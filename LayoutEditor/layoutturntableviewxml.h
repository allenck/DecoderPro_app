#ifndef LAYOUTTURNTABLEVIEWXML_H
#define LAYOUTTURNTABLEVIEWXML_H

#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"
class LIBLAYOUTEDITORSHARED_EXPORT LayoutTurntableViewXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 LayoutTurntableViewXml();
 ~LayoutTurntableViewXml() {}
 LayoutTurntableViewXml(const LayoutTurntableViewXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 Logger* log;
};
Q_DECLARE_METATYPE(LayoutTurntableViewXml)
#endif // LAYOUTTURNTABLEVIEWXML_H
