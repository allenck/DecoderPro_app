#ifndef PROXYTURNOUTMANAGERXML_H
#define PROXYTURNOUTMANAGERXML_H
#include "abstractxmladapter.h"

class ProxyTurnoutManagerXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE ProxyTurnoutManagerXml(QObject* parent = nullptr);
 ~ProxyTurnoutManagerXml() {}
 ProxyTurnoutManagerXml(const ProxyTurnoutManagerXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement shared, QDomElement perNode) ;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

};
Q_DECLARE_METATYPE(ProxyTurnoutManagerXml)
#endif // PROXYTURNOUTMANAGERXML_H
