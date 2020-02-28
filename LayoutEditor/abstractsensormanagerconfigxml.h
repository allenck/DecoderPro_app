#ifndef ABSTRACTSENSORMANAGERCONFIGXML_H
#define ABSTRACTSENSORMANAGERCONFIGXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractSensorManagerConfigXML : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit AbstractSensorManagerConfigXML(QObject *parent = 0);
    ~AbstractSensorManagerConfigXML();
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ QDomElement store(QObject* o, QDomElement sensors);
    /*abstract*/ /*public*/virtual void setStoreElementClass(QDomElement sensors) = 0;
    /*abstract*/ /*public*/ virtual bool load(QDomElement /*sensors*/) throw (JmriConfigureXmlException) {}
    /*public*/ bool loadSensors(QDomElement sensors) throw (JmriConfigureXmlException);
    /*public*/ int loadOrder()const override;

signals:

public slots:
private:
 Logger* log;
};

#endif // ABSTRACTSENSORMANAGERCONFIGXML_H
