#ifndef SCHEDULESBYLOADACTION_H
#define SCHEDULESBYLOADACTION_H

#include "abstractaction.h"
namespace Operations
{
 class SchedulesByLoadFrame;
 class SchedulesByLoadAction : public AbstractAction
 {
  Q_OBJECT
 public:
  SchedulesByLoadAction(QString actionName, QObject* parent);
  public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  /*private*/ SchedulesByLoadFrame* _slf;

 };
}
#endif // SCHEDULESBYLOADACTION_H
