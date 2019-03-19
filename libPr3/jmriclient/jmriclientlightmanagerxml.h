#ifndef JMRICLIENTLIGHTMANAGERXML_H
#define JMRICLIENTLIGHTMANAGERXML_H
#include "abstractlightmanagerconfigxml.h"

class JMRIClientLightManagerXml : public AbstractLightManagerConfigXML
{
public:
 JMRIClientLightManagerXml(QObject* parent = nullptr);
 /*public*/ void setStoreElementClass(QDomElement lights);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ bool load(QDomElement shared, QDomElement perNode);

private:
 static Logger* log;
};

#endif // JMRICLIENTLIGHTMANAGERXML_H
