#ifndef TRANSITMANAGERXML_H
#define TRANSITMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"

class TransitManagerXml : public AbstractNamedBeanManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE TransitManagerXml();
 ~TransitManagerXml()  override{}
 TransitManagerXml(const TransitManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
 /*public*/ QDomElement  store(QObject* o) override;
 /*public*/ void setStoreElementClass(QDomElement  transits);
 /*public*/ void load(QDomElement  element, QObject* o) throw (Exception) override;
 /*public*/ bool load(QDomElement  sharedTransits, QDomElement  perNodeTransits) override;
 /*public*/ bool load(QDomElement  sharedTransits) throw (Exception) override;
 /*public*/ void loadTransits(QDomElement  sharedTransits, QDomElement  perNodeTransits);
 /*public*/ int loadOrder()const  override;

private:
 Logger* log;
};
Q_DECLARE_METATYPE(TransitManagerXml)
#endif // TRANSITMANAGERXML_H
