#ifndef DCCSIGNALHEADXML_H
#define DCCSIGNALHEADXML_H
#include "abstractnamedbeanmanagerconfigxml.h"

class DccSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
public:
 Q_INVOKABLE DccSignalHeadXml(QObject *parent = nullptr);
 ~DccSignalHeadXml() {}
 DccSignalHeadXml(const DccSignalHeadXml&) : AbstractNamedBeanManagerConfigXML() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement shared, QDomElement perNode);
 /*public*/ void load(QDomElement, QObject*) throw (Exception);

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(DccSignalHeadXml)
#endif // DCCSIGNALHEADXML_H
