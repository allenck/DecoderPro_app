#ifndef DCS240CONNECTIONCONFIG_H
#define DCS240CONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"

class DCS240ConnectionConfig : public AbstractSerialConnectionConfig
{
 Q_OBJECT
public:
 DCS240ConnectionConfig(SerialPortAdapter* p, QObject* parent = nullptr);
 ~DCS240ConnectionConfig() {}
 DCS240ConnectionConfig(const DCS240ConnectionConfig&) : AbstractSerialConnectionConfig() {}
 Q_INVOKABLE /*public*/ DCS240ConnectionConfig(QObject* parent = nullptr);
 /*public*/ QString name() override;

protected:
 /*protected*/ void setInstance();


};
Q_DECLARE_METATYPE(DCS240ConnectionConfig)
#endif // DCS240CONNECTIONCONFIG_H
