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
  LoadDemoAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  AutoBackup* backup;// = new AutoBackup();

 };
}
#endif // LOADDEMOACTION_H
