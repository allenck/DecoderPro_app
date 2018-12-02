#ifndef POSITIONABLEPOINTXML_H
#define POSITIONABLEPOINTXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT PositionablePointXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit PositionablePointXml(QObject *parent = 0);
 ~PositionablePointXml() {}
 PositionablePointXml(const PositionablePointXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(PositionablePointXml)
#endif // POSITIONABLEPOINTXML_H
