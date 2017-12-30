#ifndef ABSTRACTSERIALCONNECTIONCONFIGXML_H
#define ABSTRACTSERIALCONNECTIONCONFIGXML_H
#include "abstractconnectionconfigxml.h"
#include "liblayouteditor_global.h"

class SerialPortAdapter;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractSerialConnectionConfigXml : public AbstractConnectionConfigXml
{
    Q_OBJECT
public:
    explicit AbstractSerialConnectionConfigXml(QObject *parent = 0);
    ~AbstractSerialConnectionConfigXml() {}
    AbstractSerialConnectionConfigXml(const AbstractSerialConnectionConfigXml&) : AbstractConnectionConfigXml() {}
    QDomElement store(QObject* o, bool shared);
    /*public*/ QDomElement store(QObject* object);
    /*public*/ bool load(QDomElement shared, QDomElement perNode);// //throws Exception

signals:

public slots:

private:
    Logger* log;
protected:
    /*protected*/ SerialPortAdapter* adapter;
    virtual /*abstract*/ /*protected*/ void getInstance();
    virtual /*abstract*/ /*protected*/ void _register();
    virtual /*protected*/ void getInstance(QObject* object);
    /*protected*/ void extendElement(QDomElement e);
//    /*protected*/ void unpackElement(QDomElement e);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
};

#endif // ABSTRACTSERIALCONNECTIONCONFIGXML_H
