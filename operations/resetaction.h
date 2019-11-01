#ifndef RESETACTION_H
#define RESETACTION_H

#include "abstractaction.h"

namespace Operations
{
 class ResetAction : public AbstractAction
 {
   Q_OBJECT
 public:
  ResetAction(QString, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);

 };
}
#endif // RESETACTION_H
