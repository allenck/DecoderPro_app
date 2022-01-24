#ifndef SENSOREDITACTION_H
#define SENSOREDITACTION_H
#include "beaneditaction.h"

class SensorDebounceEditAction;
class SensorPullUpEditAction;
class SensorEditAction : public BeanEditAction
{
 public:
  SensorEditAction();
  /*public*/ QString helpTarget() override;

 private:
  SensorDebounceEditAction* debounce;
  SensorPullUpEditAction* pullup;

};

#endif // SENSOREDITACTION_H
