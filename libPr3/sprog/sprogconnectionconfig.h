#ifndef SPROGCONNECTIONCONFIG_H
#define SPROGCONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"


namespace Sprog
{
 class SprogConnectionConfig : public AbstractSerialConnectionConfig
 {
  Q_OBJECT

 public:
  SprogConnectionConfig(QObject* parent = 0);
  SprogConnectionConfig(SerialPortAdapter* p, QObject* parent = 0);
  ~SprogConnectionConfig() {}
  SprogConnectionConfig(const SprogConnectionConfig&) : AbstractSerialConnectionConfig() {}
  /*public*/ QString name();

 protected:
  /*protected*/ QStringList getPortFriendlyNames();
  /*protected*/ void setInstance();

 };

}
Q_DECLARE_METATYPE(Sprog::SprogConnectionConfig)

#endif // SPROGCONNECTIONCONFIG_H
