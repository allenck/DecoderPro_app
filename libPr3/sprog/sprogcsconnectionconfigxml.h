#ifndef SPROGCSCONNECTIONCONFIGXML_H
#define SPROGCSCONNECTIONCONFIGXML_H
#include "abstractserialconnectionconfigxml.h"
namespace Sprog
{
 class SprogCSConnectionConfigXml : public AbstractSerialConnectionConfigXml
 {
  Q_OBJECT
 public:
  SprogCSConnectionConfigXml(QObject* parent =0);
  ~SprogCSConnectionConfigXml() {}
  SprogCSConnectionConfigXml(const SprogCSConnectionConfigXml&) : AbstractSerialConnectionConfigXml() {}
  /*protected*/ void getInstance();
  /*protected*/ void getInstance(QObject* object);
  /*protected*/ void _register();
  /*protected*/ QString javaClass();

 };
}
Q_DECLARE_METATYPE(Sprog::SprogCSConnectionConfigXml)
#endif // SPROGCSCONNECTIONCONFIGXML_H
