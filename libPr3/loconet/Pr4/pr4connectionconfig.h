#ifndef PR4CONNECTIONCONFIG_H
#define PR4CONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"

class PR4ConnectionConfig : public AbstractSerialConnectionConfig
{
public:
 /*public*/ PR4ConnectionConfig(SerialPortAdapter* p, QObject* parent = nullptr);
 /*public*/ PR4ConnectionConfig(QObject* parent = nullptr);
 ~PR4ConnectionConfig(){}
 PR4ConnectionConfig(const PR4ConnectionConfig&) : AbstractSerialConnectionConfig() {}
 /*public*/ QString name();
 /*public*/ bool isOptList2Advanced();
protected:
 /*protected*/ QStringList getPortFriendlyNames();
 /*protected*/ void setInstance() ;
};
Q_DECLARE_METATYPE(PR4ConnectionConfig)
#endif // PR4CONNECTIONCONFIG_H
