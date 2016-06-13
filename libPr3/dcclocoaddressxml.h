#ifndef DCCLOCOADDRESSXML_H
#define DCCLOCOADDRESSXML_H

#include <QObject>
#include <QtXml>
#include "dcclocoaddress.h"
#include "logger.h"

class DccLocoAddressXml : public QObject
{
    Q_OBJECT
public:
    explicit DccLocoAddressXml(QObject *parent = 0);
    /*public*/ QDomElement store(QDomDocument doc, QObject* o);
    /*public*/ bool load(QDomElement element);
    /*public*/ DccLocoAddress* getAddress(QDomElement element);
    /*public*/ void load(QDomElement element, QObject* o);

signals:
    
public slots:
    
private:
 Logger log;
};

#endif // DCCLOCOADDRESSXML_H
