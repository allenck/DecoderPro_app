#ifndef INTERNALREPORTERMANAGERXML_H
#define INTERNALREPORTERMANAGERXML_H
#include "abstractreportermanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT InternalReporterManagerXml : public AbstractReporterManagerConfigXML
{
    Q_OBJECT
public:
    explicit InternalReporterManagerXml(QObject *parent = 0);
 ~InternalReporterManagerXml() {}
 InternalReporterManagerXml(const InternalReporterManagerXml&) : AbstractReporterManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement sensors);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement reporters) throw (Exception);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(InternalReporterManagerXml)
#endif // INTERNALREPORTERMANAGERXML_H
