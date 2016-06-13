#ifndef LNREPORTERMANAGERXML_H
#define LNREPORTERMANAGERXML_H
#include "abstractreportermanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LnReporterManagerXml : public AbstractReporterManagerConfigXML
{
public:
    LnReporterManagerXml(QObject* parent = 0);
    ~LnReporterManagerXml() {}
    LnReporterManagerXml(const LnReporterManagerXml&) : AbstractReporterManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement sensors);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement reporters) throw (Exception);
private:
    Logger* log;
};
Q_DECLARE_METATYPE(LnReporterManagerXml)
#endif // LNREPORTERMANAGERXML_H
