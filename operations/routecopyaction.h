#ifndef ROUTECOPYACTION_H
#define ROUTECOPYACTION_H

#include "abstractaction.h"
#include "route.h"
#include <QPointer>
#include "routecopyframe.h"

namespace Operations
{
 class RouteCopyAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ RouteCopyAction(QObject* parent);
  /*public*/ RouteCopyAction(Route* route,  QObject* parent);

 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);
 private:
  Route* _route = nullptr;
  QPointer<RouteCopyFrame> f = nullptr;
  void common();
  QString routeName;

 };
}
#endif // ROUTECOPYACTION_H
