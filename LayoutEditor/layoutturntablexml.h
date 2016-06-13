#ifndef LAYOUTTURNTABLEXML_H
#define LAYOUTTURNTABLEXML_H

#include "abstractxmladapter.h"
class LayoutTurntableXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 LayoutTurntableXml();
 ~LayoutTurntableXml() {}
 LayoutTurntableXml(const LayoutTurntableXml&) {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 Logger* log;
};
Q_DECLARE_METATYPE(LayoutTurntableXml)
#endif // LAYOUTTURNTABLEXML_H
