#ifndef INTERNALLIGHTMANAGERXML_H
#define INTERNALLIGHTMANAGERXML_H
#include "abstractlightmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT InternalLightManagerXml : public AbstractLightManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit InternalLightManagerXml(QObject *parent = 0);
 ~InternalLightManagerXml() {}
 InternalLightManagerXml(const InternalLightManagerXml&) : AbstractLightManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement lights);
 /*public*/ void load(QDomElement element, QObject* o)  throw (Exception);
 /*public*/ bool load(QDomElement lights)throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(InternalLightManagerXml)
#endif // INTERNALLIGHTMANAGERXML_H
