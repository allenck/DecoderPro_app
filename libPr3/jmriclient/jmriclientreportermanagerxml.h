#ifndef JMRICLIENTREPORTERMANAGERXML_H
#define JMRICLIENTREPORTERMANAGERXML_H
#include "abstractreportermanagerconfigxml.h"

class JMRIClientReporterManagerXml : public AbstractReporterManagerConfigXML
{
public:
 JMRIClientReporterManagerXml(QObject* parent = nullptr);
 /*public*/ void setStoreElementClass(QDomElement reporters);
 /*public*/ void load(QDomElement QDomElement, QObject* o) throw (JmriConfigureXmlException);
 /*public*/ bool load(QDomElement shared, QDomElement perNode);

private:
 static Logger* log;
};

#endif // JMRICLIENTREPORTERMANAGERXML_H
