#ifndef HEXFILECONNECTIONCONFIG_H
#define HEXFILECONNECTIONCONFIG_H
#include "abstractsimulatorconnectionconfig.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT HexFileConnectionConfig : public AbstractSimulatorConnectionConfig
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit HexFileConnectionConfig(QObject *parent = 0);
    ~HexFileConnectionConfig() {}
    HexFileConnectionConfig(const HexFileConnectionConfig&) : AbstractSimulatorConnectionConfig() {}
    /*public*/ HexFileConnectionConfig(SerialPortAdapter* p, QObject *parent = 0);
    /*public*/ QString name();
    /*public*/ void dispose();
signals:

public slots:
protected:
    /*protected*/ void setInstance();

};

#endif // HEXFILECONNECTIONCONFIG_H
