#ifndef TRAINSSCHEDULEACTION_H
#define TRAINSSCHEDULEACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrainsScheduleTableFrame;
 class TrainsScheduleAction : public AbstractAction
 {
   Q_OBJECT
 public:
  TrainsScheduleAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  TrainsScheduleTableFrame* f;// = null;

 };
}
#endif // TRAINSSCHEDULEACTION_H
