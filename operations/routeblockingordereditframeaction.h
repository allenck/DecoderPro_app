#ifndef OPERATIONS_ROUTEBLOCKINGORDEREDITFRAMEACTION_H
#define OPERATIONS_ROUTEBLOCKINGORDEREDITFRAMEACTION_H

#include <abstractaction.h>
#include "routeblockingordereditframe.h"
#include <QPointer>

namespace Operations {

 class Route;
 class RouteBlockingOrderEditFrame;
 class RouteBlockingOrderEditFrameAction : public AbstractAction
 {
  public:
   explicit RouteBlockingOrderEditFrameAction(QObject *parent = nullptr);
   /*public*/ RouteBlockingOrderEditFrameAction(Route* route, QObject* parent);

  public slots:
   /*public*/ void actionPerformed(JActionEvent* /*e*/=0)override;

  private:
   Route* _route;
   QPointer<RouteBlockingOrderEditFrame> f = nullptr;

 };

} // namespace Operations

#endif // OPERATIONS_ROUTEBLOCKINGORDEREDITFRAMEACTION_H
