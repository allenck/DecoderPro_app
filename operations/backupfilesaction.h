#ifndef BACKUPFILESACTION_H
#define BACKUPFILESACTION_H

#include "abstractaction.h"
namespace Operations
{
 class BackupFilesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ BackupFilesAction(QString s, QObject* parent);

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  /*private*/ void backUp();

 };
}
#endif // BACKUPFILESACTION_H
