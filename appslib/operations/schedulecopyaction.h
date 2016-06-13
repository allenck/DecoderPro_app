#ifndef SCHEDULECOPYACTION_H
#define SCHEDULECOPYACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ScheduleCopyFrame;
 class Schedule;
 class ScheduleCopyAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ScheduleCopyAction(QObject* parent);
  /*public*/ ScheduleCopyAction(Schedule* schedule, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  Schedule* schedule;// = null;
  ScheduleCopyFrame* f;// = null;

 };
}
#endif // SCHEDULECOPYACTION_H
