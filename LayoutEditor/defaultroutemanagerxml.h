#ifndef DEFAULTROUTEMANAGERXML_H
#define DEFAULTROUTEMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT DefaultRouteManagerXml : public AbstractNamedBeanManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit DefaultRouteManagerXml(QObject *parent = 0);
 ~DefaultRouteManagerXml() {}
 DefaultRouteManagerXml(const DefaultRouteManagerXml&) : AbstractNamedBeanManagerConfigXML(){}
 /*public*/ QDomElement store(QObject* o) override;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception)  override {}
 /*public*/ bool load(QDomElement routes, QDomElement perNodeRoutes) throw (JmriConfigureXmlException) override;
 /*public*/ void loadRoutes(QDomElement routes);
 /*public*/ void setStoreElementClass(QDomElement routes);
 /*public*/ int loadOrder()const override;

signals:

public slots:
private:
 Logger* log;
protected:
 /*protected*/ void replaceRouteManager();

};
Q_DECLARE_METATYPE(DefaultRouteManagerXml)
#endif // DEFAULTROUTEMANAGERXML_H
