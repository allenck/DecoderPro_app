#ifndef LNOVERTCPCONNECTIONCONFIG_H
#define LNOVERTCPCONNECTIONCONFIG_H
#include "abstractnetworkconnectionconfig.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT LnOverTcpConnectionConfig : public AbstractNetworkConnectionConfig
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit LnOverTcpConnectionConfig(QObject *parent = 0);
 ~LnOverTcpConnectionConfig() {}
 LnOverTcpConnectionConfig(const LnOverTcpConnectionConfig&) : AbstractNetworkConnectionConfig() {}
 /*public*/ LnOverTcpConnectionConfig(NetworkPortAdapter* p, QObject *parent = 0) ;
 /*public*/ QString name();
 /*public*/ bool isOptList1Advanced();

signals:

public slots:
protected:
 /*protected*/ void setInstance();

};
Q_DECLARE_METATYPE (LnOverTcpConnectionConfig)
#endif // LNOVERTCPCONNECTIONCONFIG_H
