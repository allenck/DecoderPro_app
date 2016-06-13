#include "settrainiconrouteaction.h"
#include "settrainiconrouteframe.h"
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

 /*public*/ SetTrainIconRouteAction::SetTrainIconRouteAction(QString s, QObject* parent)
 : AbstractAction(s, parent)
 {
  //super(s);
  common();
 }


 /*public*/ SetTrainIconRouteAction::SetTrainIconRouteAction(QString s, QString routeName, QObject* parent)
 : AbstractAction(s, parent)
{
  // super(s);
  common();
  this->routeName = routeName;
 }

 void SetTrainIconRouteAction::common()
 {
  f = NULL;
  routeName = "";
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void SetTrainIconRouteAction::actionPerformed(ActionEvent* e) {
     // create a copy route frame

     if (f == NULL || !f->isVisible()) {
         f = new SetTrainIconRouteFrame(routeName);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus

 }

}
