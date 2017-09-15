#ifndef TRANSITMANAGERXML_H
#define TRANSITMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"

class TransitManagerXml : public AbstractNamedBeanManagerConfigXML
{
 Q_OBJECT
public:
 TransitManagerXml();
 ~TransitManagerXml() {}
 TransitManagerXml(const TransitManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
 /*public*/ QDomElement  store(QObject* o);
 /*public*/ void setStoreElementClass(QDomElement  transits);
 /*public*/ void load(QDomElement  element, QObject* o) throw (Exception);
 /*public*/ bool load(QDomElement  sharedTransits, QDomElement  perNodeTransits);
 /*public*/ void loadTransits(QDomElement  sharedTransits, QDomElement  perNodeTransits);
 /*public*/ int loadOrder();

private:
 Logger* log;
};
Q_DECLARE_METATYPE(TransitManagerXml)
#endif // TRANSITMANAGERXML_H
