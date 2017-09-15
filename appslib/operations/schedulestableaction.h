#ifndef SCHEDULESTABLEACTION_H
#define SCHEDULESTABLEACTION_H

#include "abstractaction.h"

namespace Operations
{
 class SchedulesTableFrame;
 class SchedulesTableAction : public AbstractAction
 {
  Q_OBJECT
 public:
  SchedulesTableAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);

 private:
  SchedulesTableFrame* f;// = null;

 };
}
#endif // SCHEDULESTABLEACTION_H
