#ifndef PR4CONNECTIONCONFIG_H
#define PR4CONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"

class Pr4ConnectionConfig : public AbstractSerialConnectionConfig
{
 Q_OBJECT
public:
 Q_INVOKABLE /*public*/ Pr4ConnectionConfig(SerialPortAdapter* p, QObject* parent = nullptr);
 Q_INVOKABLE /*public*/ Pr4ConnectionConfig(QObject* parent = nullptr);
 ~Pr4ConnectionConfig(){}
 Pr4ConnectionConfig(const Pr4ConnectionConfig&) : AbstractSerialConnectionConfig() {}
 /*public*/ QString name() override;
 /*public*/ bool isOptList2Advanced();
protected:
 /*protected*/ QStringList getPortFriendlyNames();
 /*protected*/ void setInstance() ;
};
Q_DECLARE_METATYPE(Pr4ConnectionConfig)
#endif // PR4CONNECTIONCONFIG_H
