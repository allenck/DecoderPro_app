#ifndef DCS52CONNECTIONCONFIGXML_H
#define DCS52CONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

class DCS52ConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
 Q_OBJECT
public:
 Q_INVOKABLE DCS52ConnectionConfigXml(QObject *parent= nullptr);
 ~DCS52ConnectionConfigXml() {}
 DCS52ConnectionConfigXml(const DCS52ConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
protected:
 /*protected*/ void getInstance();
 /*protected*/ void getInstance(QObject* object);
 /*protected*/ void _register();


};
Q_DECLARE_METATYPE(DCS52ConnectionConfigXml)
#endif // DCS52CONNECTIONCONFIGXML_H
