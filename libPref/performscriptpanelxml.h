#ifndef PERFORMSCRIPTPANELXML_H
#define PERFORMSCRIPTPANELXML_H
#include "abstractxmladapter.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT PerformScriptPanelXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit PerformScriptPanelXml(QObject *parent = 0);
 ~PerformScriptPanelXml() {}
 PerformScriptPanelXml(const PerformScriptPanelXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o)throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(PerformScriptPanelXml)
#endif // PERFORMSCRIPTPANELXML_H
