#ifndef LNLIGHTMANAGERXML_H
#define LNLIGHTMANAGERXML_H
#include "abstractlightmanagerconfigxml.h"

#include <QObject>
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LnLightManagerXml : public AbstractLightManagerConfigXML
{
 Q_OBJECT
public:
    Q_INVOKABLE LnLightManagerXml(QObject *parent = 0);
    ~LnLightManagerXml();
    LnLightManagerXml(const LnLightManagerXml&) : AbstractLightManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement lights) override;
    /*public*/ void load(QDomElement element, QObject* o)  throw (Exception);
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception) override;

};
Q_DECLARE_METATYPE(LnLightManagerXml)
#endif // LNLIGHTMANAGERXML_H
