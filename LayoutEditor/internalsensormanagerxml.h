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
    /*public*/ void setStoreElementClass(QDomElement sensors)  override;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement sensors, QDomElement perNodeSensors) /*throw (JmriConfigureXmlException)*/ override;

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(InternalSensorManagerXml)
#endif // INTERNALSENSORMANAGERXML_H
