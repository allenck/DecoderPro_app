#ifndef SCHEDULESRESETHITSACTION_H
#define SCHEDULESRESETHITSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class SchedulesResetHitsAction : public AbstractAction
 {
 public:
  SchedulesResetHitsAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 };
}
#endif // SCHEDULESRESETHITSACTION_H
