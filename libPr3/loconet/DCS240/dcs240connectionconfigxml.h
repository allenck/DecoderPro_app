#ifndef DCS240CONNECTIONCONFIGXML_H
#define DCS240CONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

class DCS240ConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
 Q_OBJECT
public:
 Q_INVOKABLE DCS240ConnectionConfigXml(QObject* parent = nullptr);
 ~DCS240ConnectionConfigXml() {}
 DCS240ConnectionConfigXml(const DCS240ConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
protected:
 /*protected*/ void getInstance();
 /*protected*/ void getInstance(QObject* object);
 /*protected*/ void _register();

};
Q_DECLARE_METATYPE(DCS240ConnectionConfigXml)
#endif // DCS240CONNECTIONCONFIGXML_H
