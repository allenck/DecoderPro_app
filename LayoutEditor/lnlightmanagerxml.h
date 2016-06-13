#ifndef LNLIGHTMANAGERXML_H
#define LNLIGHTMANAGERXML_H
#include "abstractlightmanagerconfigxml.h"

#include <QObject>
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LnLightManagerXml : public AbstractLightManagerConfigXML
{
public:
    LnLightManagerXml(QObject *parent = 0);
    ~LnLightManagerXml();
    LnLightManagerXml(const LnLightManagerXml&) : AbstractLightManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement lights);
    /*public*/ void load(QDomElement element, QObject* o)  throw (Exception);
    /*public*/ bool load(QDomElement lights) throw (Exception);

};
Q_DECLARE_METATYPE(LnLightManagerXml)
#endif // LNLIGHTMANAGERXML_H
