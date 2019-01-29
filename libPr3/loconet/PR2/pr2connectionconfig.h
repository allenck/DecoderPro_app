#ifndef PR2CONNECTIONCONFIG_H
#define PR2CONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"

class Pr2ConnectionConfig : public AbstractSerialConnectionConfig
{
public:
 Q_INVOKABLE /*public*/ Pr2ConnectionConfig(QObject* parent = nullptr);
 Q_INVOKABLE /*public*/ Pr2ConnectionConfig(SerialPortAdapter* p, QObject* parent= nullptr);
 ~Pr2ConnectionConfig() {}
 Pr2ConnectionConfig(const Pr2ConnectionConfig&) : AbstractSerialConnectionConfig() {}
 /*public*/ QString name();

protected:
 /*protected*/ void setInstance();
};
Q_DECLARE_METATYPE(Pr2ConnectionConfig)
#endif // PR2CONNECTIONCONFIG_H
