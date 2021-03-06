#ifndef LNREPORTERMANAGERXML_H
#define LNREPORTERMANAGERXML_H
#include "abstractreportermanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LnReporterManagerXml : public AbstractReporterManagerConfigXML
{
 Q_OBJECT
public:
    Q_INVOKABLE LnReporterManagerXml(QObject* parent = 0);
    ~LnReporterManagerXml()  override{}
    LnReporterManagerXml(const LnReporterManagerXml&) : AbstractReporterManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement sensors)const override;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ bool load(QDomElement reporters) throw (Exception) override;
private:
    Logger* log;
};
Q_DECLARE_METATYPE(LnReporterManagerXml)
#endif // LNREPORTERMANAGERXML_H
