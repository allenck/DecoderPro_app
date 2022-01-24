#ifndef TRAINSSCHEDULEACTION_H
#define TRAINSSCHEDULEACTION_H

#include "abstractaction.h"
#include "trainsscheduletableframe.h"
#include <QPointer>

namespace Operations
{
 class TrainsScheduleTableFrame;
 class TrainsScheduleAction : public AbstractAction
 {
   Q_OBJECT
 public:
  TrainsScheduleAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent *e = 0);
 private:
  QPointer<TrainsScheduleTableFrame> f;// = null;

 };
}
#endif // TRAINSSCHEDULEACTION_H
