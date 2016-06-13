#ifndef PERFORMACTIONPANELXML_H
#define PERFORMACTIONPANELXML_H
#include "abstractxmladapter.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT PerformActionPanelXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit PerformActionPanelXml(QObject *parent = 0);
 ~PerformActionPanelXml() {}
 PerformActionPanelXml(const PerformActionPanelXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement e)  throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(PerformActionPanelXml)
#endif // PERFORMACTIONPANELXML_H
