#ifndef SCHEDULESTABLEACTION_H
#define SCHEDULESTABLEACTION_H

#include "abstractaction.h"
#include "schedulestableframe.h"
#include <QPointer>
namespace Operations
{
 class SchedulesTableFrame;
 class SchedulesTableAction : public AbstractAction
 {
  Q_OBJECT
 public:
  SchedulesTableAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/)override;

 private:
  QPointer<SchedulesTableFrame> f = nullptr;

 };
}
#endif // SCHEDULESTABLEACTION_H
