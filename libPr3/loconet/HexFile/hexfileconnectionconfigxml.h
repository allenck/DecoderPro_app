#ifndef HEXFILECONNECTIONCONFIGXML_H
#define HEXFILECONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT HexFileConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit HexFileConnectionConfigXml(QObject *parent = 0);
    ~HexFileConnectionConfigXml() {}
    HexFileConnectionConfigXml(const HexFileConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement shared, QDomElement perNode);

signals:

public slots:
protected:
    /*protected*/ void getInstance(QObject* object);
    /*protected*/ void getInstance();
    /*protected*/ void _register();
};

#endif // HEXFILECONNECTIONCONFIGXML_H
