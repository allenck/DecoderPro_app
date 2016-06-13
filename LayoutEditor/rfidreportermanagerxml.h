#ifndef RFIDREPORTERMANAGERXML_H
#define RFIDREPORTERMANAGERXML_H
#include "abstractreportermanagerconfigxml.h"

class RfidReporterManagerXml : public AbstractReporterManagerConfigXML
{
    Q_OBJECT
public:
    explicit RfidReporterManagerXml(QObject *parent = 0);
    /*public*/ void setStoreElementClass(QDomElement sensors);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) ;
    /*public*/ bool load(QDomElement reporters) throw (Exception);

signals:

public slots:
private:
    Logger* log;

};

#endif // RFIDREPORTERMANAGERXML_H
