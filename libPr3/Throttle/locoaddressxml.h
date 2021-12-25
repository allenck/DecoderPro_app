#ifndef LOCOADDRESSXML_H
#define LOCOADDRESSXML_H
#include "abstractxmladapter.h"

class LocoAddress;
class LocoAddressXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 LocoAddressXml(QObject* parent = 0);
 ~LocoAddressXml() {}
 LocoAddressXml(const LocoAddressXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement shared, QDomElement perNode);
 /*public*/ LocoAddress* getAddress(QDomElement element);
 /*public*/ void load(QDomElement element, QObject* o) /*throw (Exception)*/;

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("DccLocoAddressXml");
};
Q_DECLARE_METATYPE(LocoAddressXml)
#endif // LOCOADDRESSXML_H
