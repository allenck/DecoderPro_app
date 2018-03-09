#ifndef SPROGCONNECTIONCONFIGXML_H
#define SPROGCONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"

namespace Sprog
{
 class SprogConnectionConfigXml : public AbstractSerialConnectionConfigXml
 {
  Q_OBJECT
 public:
  SprogConnectionConfigXml(QObject* parent = 0);
  ~SprogConnectionConfigXml() {}
  SprogConnectionConfigXml(const SprogConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}

 protected:
  /*protected*/ void getInstance();
  /*protected*/ void getInstance(QObject* object);
  /*protected*/ void _register();
  /*protected*/ QString javaClass();
 };
}
Q_DECLARE_METATYPE(Sprog::SprogConnectionConfigXml)
#endif // SPROGCONNECTIONCONFIGXML_H
