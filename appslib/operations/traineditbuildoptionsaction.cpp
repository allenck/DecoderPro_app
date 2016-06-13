#include "traineditbuildoptionsaction.h"
#include "traineditframe.h"
#include "traineditbuildoptionsframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a TrainEditBuildOptionFrame.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 ///*public*/ class TrainEditBuildOptionsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 5533217709531560265L;

 /*public*/ TrainEditBuildOptionsAction::TrainEditBuildOptionsAction(QString s, TrainEditFrame* frame)
  : AbstractAction(s, frame)
 {
  //super(s);
  f = NULL;
  this->frame = frame;
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void TrainEditBuildOptionsAction::actionPerformed(ActionEvent* e)
 {
     // create a train edit option frame
     if (f != NULL && f->isVisible()) {
         f->dispose();
     }
     f = new TrainEditBuildOptionsFrame();
     f->initComponents(frame);
 }
}
