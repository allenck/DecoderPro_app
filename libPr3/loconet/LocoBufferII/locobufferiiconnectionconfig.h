#ifndef LOCOBUFFERIICONNECTIONCONFIG_H
#define LOCOBUFFERIICONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"

class LocoBufferIIConnectionConfig : public AbstractSerialConnectionConfig
{
 Q_OBJECT
public:
 Q_INVOKABLE LocoBufferIIConnectionConfig(QObject* parent = nullptr);
 /*public*/ LocoBufferIIConnectionConfig(SerialPortAdapter* p, QObject* parent =nullptr);
 ~LocoBufferIIConnectionConfig() {}
 LocoBufferIIConnectionConfig(const LocoBufferIIConnectionConfig&) : AbstractSerialConnectionConfig() {}
 /*public*/ QString name();
 /*public*/ bool isOptList2Advanced();
protected:
 /*protected*/ void setInstance();
};
Q_DECLARE_METATYPE(LocoBufferIIConnectionConfig)
#endif // LOCOBUFFERIICONNECTIONCONFIG_H
