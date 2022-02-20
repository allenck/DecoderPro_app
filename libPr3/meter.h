#ifndef METER_H
#define METER_H
#include "qobject.h"

class Meter
{
 public:
  /*public*/ enum Unit {

          /**
           * The meter measures in percent: 0.0 - 100.0
           */
          Percent,

          /**
           * The meter measures in kilo units (kilo volts, kilo amperes, ...)
           */
          Kilo,

          /**
           * The meter measures in full units (volts, amperes, ...)
           */
          NoPrefix,

          /**
           * The meter measures in milli units (milli volts, milli amperes, ...)
           */
          Milli,

          /**
           * The meter measures in micro units (micro volts, micro amperes, ...)
           */
          Micro
      };

  /*public*/ virtual Unit getUnit() {return Percent;}

      /**
       * Enable this meter
       */
  /*public*/ virtual void enable() {}

      /**
       * Disable this meter
       */
  /*public*/ virtual void disable() {}

      /**
       * Remove references to and from this object, so that it can eventually be
       * garbage-collected.
       * <p>
       * The meter must be disabled before it's disposed.
       */
      //@Override
  /*public*/ virtual void dispose() {}
  virtual QObject* mself() =0;
};
Q_DECLARE_INTERFACE(Meter, "Meter")
#endif // METER_H
