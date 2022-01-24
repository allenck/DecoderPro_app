#ifndef PHYSICALLOCATIONREPORTER_H
#define PHYSICALLOCATIONREPORTER_H
#include <QObject>
#include "locoaddress.h"
#include "physicallocation.h"

class PhysicalLocationReporter //: public QObject
{
 //Q_OBJECT
 public:
  enum Direction
  {
   UNKNOWN, ENTER, EXIT
  };
  //PhysicalLocationReporter() {}
  /*public*/ virtual LocoAddress* getLocoAddress(QString s) =0;
  /*public*/ virtual Direction getDirection(QString s) =0;
  /*public*/ virtual PhysicalLocation* getPhysicalLocation()=0;
  /*public*/ virtual PhysicalLocation* getPhysicalLocation(QString s) =0;
};
Q_DECLARE_INTERFACE(PhysicalLocationReporter, "PhysicalLocationReporter")
#endif // PHYSICALLOCATIONREPORTER_H
