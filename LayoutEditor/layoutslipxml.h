#ifndef LAYOUTSLIPXML_H
#define LAYOUTSLIPXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutSlipXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit LayoutSlipXml(QObject *parent = 0);
 ~LayoutSlipXml() {}
 LayoutSlipXml(const LayoutSlipXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception) ;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
 QString getElement(QDomElement el, QString child);

};
Q_DECLARE_METATYPE(LayoutSlipXml)
#endif // LAYOUTSLIPXML_H
