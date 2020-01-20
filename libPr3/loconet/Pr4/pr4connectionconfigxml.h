#ifndef PR4CONNECTIONCONFIGXML_H
#define PR4CONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

class PR4ConnectionConfigXml : public AbstractSerialConnectionConfigXml
{
 Q_OBJECT
public:
 PR4ConnectionConfigXml(QObject *parent= nullptr);
 ~PR4ConnectionConfigXml() {}
 PR4ConnectionConfigXml(const PR4ConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
protected:
 /*protected*/ void getInstance();
 /*protected*/ void getInstance(QObject* object);
 /*protected*/ void _register();

};
Q_DECLARE_METATYPE(PR4ConnectionConfigXml)
#endif // PR4CONNECTIONCONFIGXML_H
