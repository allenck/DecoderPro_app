#ifndef OPERATIONSSETTINGSACTION_H
#define OPERATIONSSETTINGSACTION_H

#include <abstractaction.h>
#include "operationssettingsframe.h"
#include <QPointer>

namespace Operations
{
 class OperationsSettingsAction : public AbstractAction
 {
   Q_OBJECT
  public:
   explicit OperationsSettingsAction(QObject *parent = nullptr);
  public slots:
   /*public*/ void actionPerformed(JActionEvent* e =0)override;

  private:
   static QPointer<OperationsSettingsFrame> operationsSettingsFrame;// = nullptr;

 };
}
#endif // OPERATIONSSETTINGSACTION_H
