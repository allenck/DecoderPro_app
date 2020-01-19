#ifndef LNSENSORMANAGERXML_H
#define LNSENSORMANAGERXML_H
#include "abstractsensormanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LnSensorManagerXml : public AbstractSensorManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LnSensorManagerXml(QObject *parent = 0);
    ~LnSensorManagerXml() {}
    LnSensorManagerXml(const LnSensorManagerXml&) :AbstractSensorManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement sensors);
    /*public*/ void load(QDomElement element, QObject* o) throw (JmriConfigureXmlException) ;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException);

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(LnSensorManagerXml)
#endif // LNSENSORMANAGERXML_H
