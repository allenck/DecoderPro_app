#ifndef OPERATIONS_NCECONSISTENGINEACTION_H
#define OPERATIONS_NCECONSISTENGINEACTION_H

#include <abstractaction.h>

namespace Operations {
 class NceTrafficController;
 class NceConsistEngineAction : public AbstractAction
 {
   Q_OBJECT
  public:
   explicit NceConsistEngineAction(QObject *parent);

  public slots:
   /*public*/ void actionPerformed(JActionEvent* /*ae*/=0)override;

  private:
   NceTrafficController* tc;
 };

} // namespace Operations

#endif // OPERATIONS_NCECONSISTENGINEACTION_H
