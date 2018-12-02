#ifndef LOCOBUFFERUSBCONNECTIONCONFIGXML_H
#define LOCOBUFFERUSBCONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT LocobufferUsbConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LocobufferUsbConnectionConfigXml(QObject *parent = 0);
 ~LocobufferUsbConnectionConfigXml() {}
 LocobufferUsbConnectionConfigXml(const LocobufferUsbConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
signals:

public slots:
protected:
    /*protected*/ void getInstance();
    /*protected*/ void getInstance(QObject* object) ;
    /*protected*/ void _register();

};
Q_DECLARE_METATYPE(LocobufferUsbConnectionConfigXml)
#endif // LOCOBUFFERUSBCONNECTIONCONFIGXML_H
