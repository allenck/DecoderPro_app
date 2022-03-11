#ifndef DEFAULTMETER_H
#define DEFAULTMETER_H
#include "abstractanalogio.h"
#include "meter.h"
#include "currentmeter.h"
#include "voltagemeter.h"

class MeterUpdateTask;
class DefaultMeter : public AbstractAnalogIO, public  Meter
{
  Q_OBJECT
  Q_INTERFACES(Meter)
 public:
  /*public*/ DefaultMeter(
          /*@Nonnull*/ QString sys,
          /*@Nonnull*/ Unit unit,
          double min, double max, double resolution,
          /*@Nonnull*/ MeterUpdateTask* updateTask, QObject* parent = nullptr);
  /*public*/ void enable() override;
  /*public*/ void disable()override;
  /*public*/ int getState()override;
  /*public*/ QString getBeanType()override;
  /*public*/ Unit getUnit()override;
  /*public*/ double getMin()override;
  /*public*/ double getMax()override;
  /*public*/ double getResolution()override;
  /*public*/ AbsoluteOrRelative::TYPE getAbsoluteOrRelative()override;
  /*public*/ void dispose()override;
  /*public*/ void requestUpdateFromLayout()override;
  QString getSystemName() const override{return AbstractNamedBean::getSystemName();}

  QObject* mself()override {return (QObject*)this;}
  QObject* self()override {return (QObject*)this;}

 private:
  static Logger* log;
  /*@Nonnull*/ /*private*/ /*final*/ MeterUpdateTask* _updateTask;
  /*@Nonnull*/ /*private*/ /*final*/ Meter::Unit _unit;
  /*private*/ /*final*/ double _min;
  /*private*/ /*final*/ double _max;
  /*private*/ /*final*/ double _resolution;

 protected:
  /*protected*/ void sendValueToLayout(double value) /*throw (JmriException)*/;
  /*protected*/ bool cutOutOfBoundsValues();
  /*public*/ void setState(int s) /*throw (JmriException)*/;

};

/**
 * Default implementation of a voltage meter.
 */
/*public*/ /*static*/ class DefaultVoltageMeter : public DefaultMeter, public VoltageMeter
{
  Q_OBJECT
  Q_INTERFACES(VoltageMeter)
 public:
    /*public*/ DefaultVoltageMeter(/*@Nonnull*/ QString sys, Unit unit, double min, double max, double resolution, MeterUpdateTask* updateTask)
   : DefaultMeter(sys, unit, min, max, resolution, updateTask){
        //super(sys, unit, min, max, resolution, updateTask);
   setObjectName(sys);
    }
  QObject* mself() {return (QObject*)this;}
};


/**
 * Default implementation of a current meter.
 */
/*public*/ /*static*/ class DefaultCurrentMeter : public DefaultMeter,  public CurrentMeter
{
  Q_OBJECT
  Q_INTERFACES(CurrentMeter)
 public:
  /*public*/ DefaultCurrentMeter(/*@Nonnull*/ QString sys, Unit unit, double min, double max, double resolution, MeterUpdateTask* updateTask)
   : DefaultMeter(sys, unit, min, max, resolution, updateTask)
  {
        //super(sys, unit, min, max, resolution, updateTask);
   setObjectName(sys);
  }
  QObject* mself() {return (QObject*)this;}
};

#endif // DEFAULTMETER_H
