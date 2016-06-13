#ifndef ABSTRACTCONNECTIONCONFIGXML_H
#define ABSTRACTCONNECTIONCONFIGXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class PortAdapter;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractConnectionConfigXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit AbstractConnectionConfigXml(QObject *parent = 0);
    /*abstract*/ /*public*/ QDomElement store(QObject* o);
    /*abstract*/ /*public*/ bool load(QDomElement e) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
protected:
    /*abstract*/ /*protected*/ void getInstance();
    /*abstract*/ /*protected*/ void _register();
    /*protected*/ void storeCommon(QDomElement e,  PortAdapter* adapter);
    /*protected*/ void extendElement(QDomElement e);
    /*protected*/ void loadCommon(QDomElement e, PortAdapter* adapter);
    /*protected*/ void saveOptions(QDomElement e, PortAdapter* adapter);
    /*protected*/ void loadOptions(QDomElement e, PortAdapter* adapter);
    /*protected*/ void unpackElement(QDomElement e);

};

#endif // ABSTRACTCONNECTIONCONFIGXML_H
