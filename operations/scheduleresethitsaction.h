#ifndef SCHEDULERESETHITSACTION_H
#define SCHEDULERESETHITSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class Schedule;
 class ScheduleResetHitsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ScheduleResetHitsAction(Schedule* schedule, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  Schedule* _schedule;

 };
}
#endif // SCHEDULERESETHITSACTION_H
