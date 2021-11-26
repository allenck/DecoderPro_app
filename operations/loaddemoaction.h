#ifndef LOADDEMOACTION_H
#define LOADDEMOACTION_H

#include "abstractaction.h"

namespace Operations
{
 class AutoBackup;
 class LoadDemoAction : public AbstractAction
 {
  Q_OBJECT
 public:
  LoadDemoAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0)override;
 private:
  AutoBackup* backup;// = new AutoBackup();

 };
}
#endif // LOADDEMOACTION_H
