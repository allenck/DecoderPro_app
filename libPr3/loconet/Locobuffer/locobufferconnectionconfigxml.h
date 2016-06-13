#ifndef LOCOBUFFERCONNECTIONCONFIGXML_H
#define LOCOBUFFERCONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT LocobufferConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
    Q_OBJECT
public:
    explicit LocobufferConnectionConfigXml(QObject *parent = 0);

signals:

public slots:
protected:
    /*protected*/ void getInstance();
    /*protected*/ void getInstance(QObject* object);
    /*protected*/ void _register();
};

#endif // LOCOBUFFERCONNECTIONCONFIGXML_H
