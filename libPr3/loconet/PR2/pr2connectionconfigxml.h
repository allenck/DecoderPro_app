#ifndef PR2CONNECTIONCONFIGXML_H
#define PR2CONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

class Pr2ConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
public:
 Pr2ConnectionConfigXml(QObject* parent = nullptr);
 ~Pr2ConnectionConfigXml() {}
 Pr2ConnectionConfigXml(const Pr2ConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}

protected:
 /*protected*/ void getInstance();
 /*protected*/ void getInstance(QObject* object);
 /*protected*/ void _register();

};
Q_DECLARE_METATYPE(Pr2ConnectionConfigXml)
#endif // PR2CONNECTIONCONFIGXML_H
