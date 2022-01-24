#ifndef RESTOREFILESACTION_H
#define RESTOREFILESACTION_H

#include "abstractaction.h"

namespace Operations
{
 class RestoreFilesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  RestoreFilesAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0)override;

 private:
  /*private*/ void restore();

 };
}
#endif // RESTOREFILESACTION_H
