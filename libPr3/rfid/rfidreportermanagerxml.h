#ifndef RFIDREPORTERMANAGERXML_H
#define RFIDREPORTERMANAGERXML_H
#include "abstractreportermanagerconfigxml.h"

class RfidReporterManagerXml : public AbstractReporterManagerConfigXML
{
public:
 Q_INVOKABLE RfidReporterManagerXml(QObject* parent = nullptr);
 ~RfidReporterManagerXml() {}
 RfidReporterManagerXml(const RfidReporterManagerXml&) : AbstractReporterManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement sensors);
 /*public*/ void load(QDomElement element, QObject* o) throw  (Exception);
 /*public*/ bool load(QDomElement shared, QDomElement /*perNode*/);

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(RfidReporterManagerXml)
#endif // RFIDREPORTERMANAGERXML_H
