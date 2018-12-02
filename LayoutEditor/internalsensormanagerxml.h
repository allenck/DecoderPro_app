#ifndef INTERNALSENSORMANAGERXML_H
#define INTERNALSENSORMANAGERXML_H
#include "abstractsensormanagerconfigxml.h"
#include "liblayouteditor_global.h"
class LIBLAYOUTEDITORSHARED_EXPORT InternalSensorManagerXml : public AbstractSensorManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit InternalSensorManagerXml(QObject *parent = 0);
 ~InternalSensorManagerXml() {}
 InternalSensorManagerXml(const InternalSensorManagerXml&) : AbstractSensorManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement sensors) ;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement sensors) throw (JmriConfigureXmlException);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(InternalSensorManagerXml)
#endif // INTERNALSENSORMANAGERXML_H
