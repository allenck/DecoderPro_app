#ifndef VOLTAGEMETER_H
#define VOLTAGEMETER_H
#include "meter.h"

class VoltageMeter : public Meter
{
 Q_INTERFACES(Meter)
 public:
  QObject* self() override {return (QObject*) this;}
};
Q_DECLARE_INTERFACE(VoltageMeter, "VoltageMeter")

#endif // VOLTAGEMETER_H
