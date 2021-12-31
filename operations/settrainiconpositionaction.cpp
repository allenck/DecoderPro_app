#include "settrainiconpositionaction.h"
#include "settrainiconpositionframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a RouteCopyFrame object.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision$
  */
 ///*public*/ class SetTrainIconPositionAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -1305604823720347502L;

 /*public*/ SetTrainIconPositionAction::SetTrainIconPositionAction(QObject* parent) : AbstractAction(tr("Set Train Icon"), parent) {
     //super(s);
      f = NULL;
      connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 //@Override
 /*public*/ void SetTrainIconPositionAction::actionPerformed(JActionEvent* /*e*/) {
     // create a copy route frame
     if (f == NULL || !f->isVisible()) {
         f = new SetTrainIconPositionFrame();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
