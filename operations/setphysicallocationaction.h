#ifndef OPERATIONS_SETPHYSICALLOCATIONACTION_H
#define OPERATIONS_SETPHYSICALLOCATIONACTION_H

#include <abstractaction.h>
#include "setphysicallocationframe.h"

namespace Operations
{
 class SetPhysicalLocationAction : public AbstractAction
 {
   Q_OBJECT
  public:
   explicit SetPhysicalLocationAction(Location* location, QObject *parent = nullptr);

  public slots:
   /*public*/  void actionPerformed(JActionEvent* =0)override;

  private:
   Location* _location;
   QPointer<SetPhysicalLocationFrame> f = nullptr;


 };
} // namespace Operations
#endif // OPERATIONS_SETPHYSICALLOCATIONACTION_H
