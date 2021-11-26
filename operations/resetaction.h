#ifndef RESETACTION_H
#define RESETACTION_H

#include "abstractaction.h"

namespace Operations
{
 class ResetAction : public AbstractAction
 {
   Q_OBJECT
 public:
  ResetAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/=0)override;

 };
}
#endif // RESETACTION_H
