#ifndef CONNECTIONCONFIGXML_H
#define CONNECTIONCONFIGXML_H
#include "../../../LayoutEditor/abstractserialconnectionconfigxml.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT  ConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
    Q_OBJECT
public:
    explicit ConnectionConfigXml(QObject *parent = 0);
    ~ConnectionConfigXml() {}
    ConnectionConfigXml(const ConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
signals:

public slots:
protected:
    /*protected*/ void getInstance();
    /*protected*/ void getInstance(QObject* object);
    /*protected*/ void _register();

};
Q_DECLARE_METATYPE(ConnectionConfigXml)
#endif // CONNECTIONCONFIGXML_H
