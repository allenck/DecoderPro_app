#ifndef ROUTECOPYACTION_H
#define ROUTECOPYACTION_H

#include "abstractaction.h"
#include "route.h"
namespace Operations
{
 class RouteCopyFrame;
 class RouteCopyAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ RouteCopyAction(QObject* parent);
  /*public*/ RouteCopyAction(Route* route,  QObject* parent);

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  Route* _route = nullptr;
  RouteCopyFrame* f;// = null;
  void common();
  QString routeName;

 };
}
#endif // ROUTECOPYACTION_H
