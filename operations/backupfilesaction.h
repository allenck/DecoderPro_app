#ifndef BACKUPFILESACTION_H
#define BACKUPFILESACTION_H

#include "abstractaction.h"
namespace Operations
{
 class BackupFilesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ BackupFilesAction(QObject* parent);

 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0)override;

 private:
  /*private*/ void backUp();

 };
}
#endif // BACKUPFILESACTION_H
