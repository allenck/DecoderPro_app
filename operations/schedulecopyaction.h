#ifndef SCHEDULECOPYACTION_H
#define SCHEDULECOPYACTION_H

#include "abstractaction.h"
#include "schedulecopyframe.h"
#include <QPointer>

namespace Operations
{
 class Schedule;
 class ScheduleCopyAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ScheduleCopyAction(QObject* parent);
  /*public*/ ScheduleCopyAction(Schedule* schedule, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);
 private:
  Schedule* schedule;// = null;
  QPointer<ScheduleCopyFrame> f = nullptr;

 };
}
#endif // SCHEDULECOPYACTION_H
