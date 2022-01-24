#ifndef INTERNALLIGHTMANAGERXML_H
#define INTERNALLIGHTMANAGERXML_H
#include "abstractlightmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT InternalLightManagerXml : public AbstractLightManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit InternalLightManagerXml(QObject *parent = 0);
 ~InternalLightManagerXml()  override{}
 InternalLightManagerXml(const InternalLightManagerXml&) : AbstractLightManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement lights) override;
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception) override;
 /*public*/ void load(QDomElement shared, QObject* o) throw (Exception) override {}

signals:

public slots:

};
Q_DECLARE_METATYPE(InternalLightManagerXml)
#endif // INTERNALLIGHTMANAGERXML_H
