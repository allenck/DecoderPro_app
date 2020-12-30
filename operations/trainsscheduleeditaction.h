#ifndef TRAINSSCHEDULEEDITACTION_H
#define TRAINSSCHEDULEEDITACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrainsScheduleEditAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainsScheduleEditAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/);

 };
}
#endif // TRAINSSCHEDULEEDITACTION_H
