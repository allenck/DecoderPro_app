#ifndef PROXYSENSORMANAGERXML_H
#define PROXYSENSORMANAGERXML_H
#include "abstractxmladapter.h"

class ProxySensorManagerXml : public AbstractXmlAdapter
{
public:
 ProxySensorManagerXml(QObject* parent = nullptr);
 ~ProxySensorManagerXml() {}
 ProxySensorManagerXml(const ProxySensorManagerXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement shared, QDomElement perNode) ;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

};
Q_DECLARE_METATYPE(ProxySensorManagerXml)
#endif // PROXYSENSORMANAGERXML_H
