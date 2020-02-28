#ifndef ABSTRACTREPORTERMANAGERCONFIGXML_H
#define ABSTRACTREPORTERMANAGERCONFIGXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractReporterManagerConfigXML : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit AbstractReporterManagerConfigXML(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool loadReporters(QDomElement reporters);
    /*public*/ int loadOrder()const override;
    /*abstract*/ /*public*/ virtual void setStoreElementClass(QDomElement reporters)const ;
    /*abstract*/ /*public*/ virtual bool load(QDomElement reporters) throw (Exception);

signals:

public slots:
private:
    Logger* log;
};

#endif // ABSTRACTREPORTERMANAGERCONFIGXML_H
