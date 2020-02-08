#ifndef DCS52CONNECTIONCONFIG_H
#define DCS52CONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"

class DCS52ConnectionConfig : public AbstractSerialConnectionConfig
{
 Q_OBJECT
public:
 Q_INVOKABLE DCS52ConnectionConfig(QObject* parent = nullptr);
 /*public*/ DCS52ConnectionConfig(SerialPortAdapter* p, QObject* parent = nullptr);
 ~DCS52ConnectionConfig() {}
 DCS52ConnectionConfig(const DCS52ConnectionConfig&) : AbstractSerialConnectionConfig() {}
 /*public*/ QString name();
protected:
 /*protected*/ void setInstance();

};
Q_DECLARE_METATYPE(DCS52ConnectionConfig)
#endif // DCS52CONNECTIONCONFIG_H
