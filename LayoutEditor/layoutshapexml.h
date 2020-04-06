#ifndef LAYOUTSHAPEXML_H
#define LAYOUTSHAPEXML_H
#include "abstractxmladapter.h"

class LayoutShapeXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE LayoutShapeXml(QObject *parent = nullptr);
 ~LayoutShapeXml() {}
 LayoutShapeXml(const LayoutShapeXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement shared, QDomElement perNode);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(LayoutShapeXml)
#endif // LAYOUTSHAPEXML_H
