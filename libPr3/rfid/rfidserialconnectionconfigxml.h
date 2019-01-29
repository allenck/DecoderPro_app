#ifndef RFIDSERIALCONNECTIONCONFIGXML_H
#define RFIDSERIALCONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

class RfidSerialConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
public:
  RfidSerialConnectionConfigXml(QObject *parent= nullptr);
 ~RfidSerialConnectionConfigXml() {}
 RfidSerialConnectionConfigXml(const RfidSerialConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
private:
 static Logger* log;

protected:
 /*protected*/ void getInstance();
 /*protected*/ void getInstance(QObject *object);
 /*protected*/ void _register();

};
Q_DECLARE_METATYPE(RfidSerialConnectionConfigXml)
#endif // RFIDSERIALCONNECTIONCONFIGXML_H
