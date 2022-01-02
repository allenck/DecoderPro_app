#ifndef OPERATIONS_EXPORTLOCATIONSROSTERACTION_H
#define OPERATIONS_EXPORTLOCATIONSROSTERACTION_H

#include <abstractaction.h>

namespace Operations {

 class ExportLocationsRosterAction : public AbstractAction
 {
   Q_OBJECT
  public:
   explicit ExportLocationsRosterAction(QObject *parent = nullptr);

  public slots:
   /*public*/ void actionPerformed(JActionEvent* ae =0)override;

 };

} // namespace Operations

#endif // OPERATIONS_EXPORTLOCATIONSROSTERACTION_H
