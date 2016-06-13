#ifndef PORTALICONXML_H
#define PORTALICONXML_H
#include "positionablelabelxml.h"

class PortalIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit PortalIconXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
 Logger* log;

};

#endif // PORTALICONXML_H
