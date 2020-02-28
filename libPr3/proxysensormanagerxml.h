#ifndef PROXYSENSORMANAGERXML_H
#define PROXYSENSORMANAGERXML_H
#include "abstractxmladapter.h"

class ProxySensorManagerXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE ProxySensorManagerXml(QObject* parent = nullptr);
 ~ProxySensorManagerXml()  override{}
 ProxySensorManagerXml(const ProxySensorManagerXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o) override;
 /*public*/ bool load(QDomElement shared, QDomElement perNode)  override;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;

};
Q_DECLARE_METATYPE(ProxySensorManagerXml)
#endif // PROXYSENSORMANAGERXML_H
