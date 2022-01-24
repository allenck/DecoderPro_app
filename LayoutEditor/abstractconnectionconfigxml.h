#ifndef ABSTRACTCONNECTIONCONFIGXML_H
#define ABSTRACTCONNECTIONCONFIGXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class ConnectionConfig;
class PortAdapter;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractConnectionConfigXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit AbstractConnectionConfigXml(QObject *parent = 0);
//    /*abstract*/ /*public*/ QDomElement store(QObject* o);
    /*abstract*/ /*public*/ bool load(QDomElement e) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ QDomElement store(QObject* o, bool shared);



signals:

public slots:
private:
 static Logger* log;

protected:
    /*abstract*/ /*protected*/ virtual void getInstance();
//    /*abstract*/ /*protected*/ virtual void _register();
    /*protected*/ void storeCommon(QDomElement e,  PortAdapter* adapter);
    /*protected*/ void extendElement(QDomElement e);
    /*protected*/ void loadCommon(QDomElement e, QDomElement perNode, PortAdapter* adapter);
    /*protected*/ void saveOptions(QDomElement e, PortAdapter* adapter);
    /*protected*/ void loadOptions(QDomElement shared, QDomElement perNode, PortAdapter* adapter);
    ///*protected*/ void unpackElement(QDomElement e, );
    /*protected*/ void unpackElement(QDomElement shared, QDomElement perNode);
    /*protected*/ void _register(ConnectionConfig* c);
    QT_DEPRECATED /*protected*/ void checkAndWarnPrefix(QString prefix);

};

#endif // ABSTRACTCONNECTIONCONFIGXML_H
