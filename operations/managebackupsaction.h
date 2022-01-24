#ifndef MANAGEBACKUPSACTION_H
#define MANAGEBACKUPSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ManageBackupsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ManageBackupsAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/)override;

 };
}
#endif // MANAGEBACKUPSACTION_H
