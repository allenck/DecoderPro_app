#ifndef MANAGEBACKUPSACTION_H
#define MANAGEBACKUPSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ManageBackupsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ManageBackupsAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);

 };
}
#endif // MANAGEBACKUPSACTION_H
