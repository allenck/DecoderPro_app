#ifndef ENGINESTABLEACTION_H
#define ENGINESTABLEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT EnginesTableAction : public AbstractAction
 {
  Q_OBJECT
 public:
  //explicit EnginesTableAction(QObject *parent = 0);
  /*public*/ EnginesTableAction(QString s, QObject *parent) ;
  /*public*/ EnginesTableAction(QObject *parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);

 signals:

 private:
  void common();

 public slots:

 };
}
#endif // ENGINESTABLEACTION_H
