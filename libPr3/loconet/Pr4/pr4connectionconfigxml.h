#ifndef PR4CONNECTIONCONFIGXML_H
#define PR4CONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

class Pr4ConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
 Q_OBJECT
public:
 Q_INVOKABLE Pr4ConnectionConfigXml(QObject *parent= nullptr);
 ~Pr4ConnectionConfigXml() {}
 Pr4ConnectionConfigXml(const Pr4ConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
protected:
 /*protected*/ void getInstance() override;
 /*protected*/ void getInstance(QObject* object);
 /*protected*/ void _register() override;

};
Q_DECLARE_METATYPE(Pr4ConnectionConfigXml)
#endif // PR4CONNECTIONCONFIGXML_H
