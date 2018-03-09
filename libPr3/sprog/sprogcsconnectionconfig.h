#ifndef SPROGCSCONNECTIONCONFIG_H
#define SPROGCSCONNECTIONCONFIG_H
#include "abstractserialconnectionconfig.h"
#include "serialportadapter.h"

namespace Sprog
{
 class SprogCSConnectionConfig : public AbstractSerialConnectionConfig
 {
  Q_OBJECT
 public:
  SprogCSConnectionConfig(QObject* parent = 0);
  /*public*/ SprogCSConnectionConfig(SerialPortAdapter* p, QObject* parent=0);
  ~SprogCSConnectionConfig() {}
  SprogCSConnectionConfig(const SprogCSConnectionConfig&) : AbstractSerialConnectionConfig() {}
  /*public*/ QString name();
  /*public*/ QString getManufacturer();
  /*public*/ void setManufacturer(QString manu);

 protected:

 //@Override
 /*protected*/ QStringList getPortFriendlyNames() ;
 /*protected*/ void setInstance();

 };
}
Q_DECLARE_METATYPE(Sprog::SprogCSConnectionConfig)
#endif // SPROGCSCONNECTIONCONFIG_H
