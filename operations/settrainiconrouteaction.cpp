#include "settrainiconrouteaction.h"

namespace Operations
{
/**
 * Swing action to create and register a SetTrainIconRouteFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2010
 * @version $Revision: 28746 $
 */
///*public*/ class SetTrainIconRouteAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -9152117316952301773L;

 /*public*/ SetTrainIconRouteAction::SetTrainIconRouteAction( QObject* parent)
 : AbstractAction(tr("Set Train Icons Coordinates for this Route"), parent)
 {
  //super(s);
  common(nullptr);
 }


 /*public*/ SetTrainIconRouteAction::SetTrainIconRouteAction(Route* route, QObject* parent)
 : AbstractAction(tr("Set Train Icons Coordinates for this Route"), parent)
{
  // super(s);
  common(route);
  this->routeName = routeName;
 }

 void SetTrainIconRouteAction::common(Route* route)
 {
  f = QPointer<SetTrainIconRouteFrame>();
  routeName = "";
  this->_route = route;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void SetTrainIconRouteAction::actionPerformed(JActionEvent * /*e*/) {
     // create a copy route frame

     if (f == NULL || !f->isVisible()) {
         f = new SetTrainIconRouteFrame(_route);
     }
     f->setExtendedState(JFrame::NORMAL);
     f->setVisible(true);	// this also brings the frame into focus

 }

}
