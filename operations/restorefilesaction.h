#ifndef RESTOREFILESACTION_H
#define RESTOREFILESACTION_H

#include "abstractaction.h"

namespace Operations
{
 class RestoreFilesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  RestoreFilesAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  /*private*/ void restore();

 };
}
#endif // RESTOREFILESACTION_H
