#ifndef LAYOUTTURNOUTXML_H
#define LAYOUTTURNOUTXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutTurnoutXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit LayoutTurnoutXml(QObject *parent = 0);
 ~LayoutTurnoutXml() {}
 LayoutTurnoutXml(const LayoutTurnoutXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(LayoutTurnoutXml)
#endif // LAYOUTTURNOUTXML_H
