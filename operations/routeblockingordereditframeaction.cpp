#include "routeblockingordereditframeaction.h"
#include "routeblockingordereditframe.h"

namespace Operations {

 /**
  * Swing action to create RouteBlockingOrderEditFrame
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2021
  */
 //*public*/ class RouteBlockingOrderEditFrameAction extends AbstractAction {

     /*public*/ RouteBlockingOrderEditFrameAction::RouteBlockingOrderEditFrameAction(QObject* parent) : AbstractAction(tr("Blocking Order"), parent){
         //super(Bundle.getMessage("MenuBlockingOrder"));
  connect(this, &QAction::triggered, [=]{actionPerformed();});
     }

     /*public*/ RouteBlockingOrderEditFrameAction::RouteBlockingOrderEditFrameAction(Route* route, QObject* parent) : AbstractAction(tr("Blocking Order"), parent) {
         //this();
         _route = route;
         connect(this, &QAction::triggered, [=]{actionPerformed();});

     }


     //@Override
     /*public*/ void RouteBlockingOrderEditFrameAction::actionPerformed(JActionEvent* /*e*/) {
         // create a copy route frame
         if (f == nullptr || !f->isVisible()) {
             f = new RouteBlockingOrderEditFrame(_route);
         }
//         f->setExtendedState(JFrame::NORMAL);
         f->setVisible(true); // this also brings the frame into focus
     }

} // namespace Operations
