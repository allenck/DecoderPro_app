#ifndef SETTRAINICONROUTEACTION_H
#define SETTRAINICONROUTEACTION_H

#include "abstractaction.h"
#include "settrainiconrouteframe.h"
#include <QPointer>

namespace Operations
{
class Route;
 class SetTrainIconRouteFrame;
 class SetTrainIconRouteAction : public AbstractAction
 {
 public:
  /*public*/ SetTrainIconRouteAction( QObject* parent);
  /*public*/ SetTrainIconRouteAction(Route* route, QObject* parent)
  ;
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e =0);

 private:
  //SetTrainIconRouteFrame* f = nullptr;
  QPointer<SetTrainIconRouteFrame> f;

  void common(Route *route);
  QString routeName;
  Route* _route;
 };
}
#endif // SETTRAINICONROUTEACTION_H
