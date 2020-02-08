#ifndef LOCOBUFFERIICONNECTIONCONFIGXML_H
#define LOCOBUFFERIICONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

class LocoBufferIIConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
 Q_OBJECT
public:
 LocoBufferIIConnectionConfigXml(QObject* object = nullptr);
 ~LocoBufferIIConnectionConfigXml() {}
 LocoBufferIIConnectionConfigXml(const LocoBufferIIConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
protected:
 /*protected*/ void getInstance() ;
 /*protected*/ void getInstance(QObject* object);
 /*protected*/ void _register();

};
Q_DECLARE_METATYPE(LocoBufferIIConnectionConfigXml)

#endif // LOCOBUFFERIICONNECTIONCONFIGXML_H
