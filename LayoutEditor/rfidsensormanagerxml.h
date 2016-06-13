#ifndef RFIDSENSORMANAGERXML_H
#define RFIDSENSORMANAGERXML_H
#include "abstractsensormanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT RfidSensorManagerXml : public AbstractSensorManagerConfigXML
{
    Q_OBJECT
public:
    explicit RfidSensorManagerXml(QObject *parent = 0);
    ~RfidSensorManagerXml() {}
    RfidSensorManagerXml(const RfidSensorManagerXml&) : AbstractSensorManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement sensors);
    /*public*/ void load(QDomElement element, QObject* o)throw (Exception) ;
    /*public*/ bool load(QDomElement sensors) throw (JmriConfigureXmlException);

signals:

public slots:
private:
    Logger* log;

};
Q_DECLARE_METATYPE(RfidSensorManagerXml)
#endif // RFIDSENSORMANAGERXML_H
