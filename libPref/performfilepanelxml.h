#ifndef PERFORMFILEPANELXML_H
#define PERFORMFILEPANELXML_H
#include "abstractxmladapter.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT PerformFilePanelXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit PerformFilePanelXml(QObject *parent = 0);
 ~PerformFilePanelXml() {}
 PerformFilePanelXml(const PerformFilePanelXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement e) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(PerformFilePanelXml)
#endif // PERFORMFILEPANELXML_H
