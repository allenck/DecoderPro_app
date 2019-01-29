#ifndef LOCOBUFFER_CONNECTIONCONFIG_H
#define LOCOBUFFER_CONNECTIONCONFIG_H

#include "abstractserialconnectionconfig.h"
#include "libPr3_global.h"

class SerialPortAdapter;
class LIBPR3SHARED_EXPORT LocobufferConnectionConfig : public AbstractSerialConnectionConfig
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LocobufferConnectionConfig(QObject *parent = 0);
    /*public*/ LocobufferConnectionConfig(SerialPortAdapter* p, QObject *parent = 0);
    ~LocobufferConnectionConfig() {}
    LocobufferConnectionConfig(const LocobufferConnectionConfig &);
    /*public*/ bool isOptList2Advanced();
    /*public*/ QString name();
protected:
    /*protected*/ void setInstance() ;

signals:

public slots:

};
Q_DECLARE_METATYPE(LocobufferConnectionConfig)
#endif // LOCOBUFFER_H
