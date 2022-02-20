#ifndef CURRENTMETER_H
#define CURRENTMETER_H
#include "meter.h"

class CurrentMeter : public Meter
{
 Q_INTERFACES(Meter)
 public:
  //QObject* mself() override {return (QObject*) this;}
};
Q_DECLARE_INTERFACE(CurrentMeter, "CurrentMeter")
#endif // CURRENTMETER_H
