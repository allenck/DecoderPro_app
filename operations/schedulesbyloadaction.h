#ifndef SCHEDULESBYLOADACTION_H
#define SCHEDULESBYLOADACTION_H

#include "abstractaction.h"
#include "schedulesbyloadframe.h"
#include <QPointer>

namespace Operations
{
 class SchedulesByLoadAction : public AbstractAction
 {
  Q_OBJECT
 public:
  SchedulesByLoadAction(QString actionName, QObject* parent);
  public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);
 private:
  /*private*/ QPointer<SchedulesByLoadFrame> _slf;
 };
}
#endif // SCHEDULESBYLOADACTION_H
