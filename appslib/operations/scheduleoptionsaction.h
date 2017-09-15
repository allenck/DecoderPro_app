#ifndef SCHEDULEOPTIONSACTION_H
#define SCHEDULEOPTIONSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ScheduleEditFrame;
 class ScheduleOptionsAction : public AbstractAction
 {
 public:
  ScheduleOptionsAction(ScheduleEditFrame* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);
 private:
  /*private*/ ScheduleEditFrame* _sef;

 };
}
#endif // SCHEDULEOPTIONSACTION_H
