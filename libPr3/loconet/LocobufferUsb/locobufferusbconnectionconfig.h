#ifndef LOCOBUFFERUSBCONNECTIONCONFIG_H
#define LOCOBUFFERUSBCONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT LocobufferUsbConnectionConfig : public AbstractSerialConnectionConfig
{
    Q_OBJECT
public:
    explicit LocobufferUsbConnectionConfig(QObject *parent = 0);
    /*public*/ LocobufferUsbConnectionConfig(SerialPortAdapter* p, QObject *parent = 0);
    ~LocobufferUsbConnectionConfig() {}
    LocobufferUsbConnectionConfig(const LocobufferUsbConnectionConfig &)
        : AbstractSerialConnectionConfig() {}

    /*public*/ QString name();
    /*public*/ bool isOptList2Advanced();

signals:

public slots:
protected:
    /*protected*/ void setInstance() ;
    /*protected*/ virtual QStringList getPortFriendlyNames();


};

#endif // LOCOBUFFERUSBCONNECTIONCONFIG_H
