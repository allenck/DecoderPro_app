#include "trainroadoptionsaction.h"
#include "trainroadoptionsframe.h"
#include "traineditframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a TrainRoadOptionsFrame.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2013
  * @version $Revision: 21765 $
  */
 //public class TrainRoadOptionsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 8700464067750312373L;

 /*public*/ TrainRoadOptionsAction::TrainRoadOptionsAction(QString s, TrainEditFrame* frame)
 :   AbstractAction(s, frame)
 {
     //super(s);
     this->frame = frame;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ void TrainRoadOptionsAction::actionPerformed(ActionEvent* /*e*/) {
     // create a train edit option frame
     if (f != NULL && f->isVisible()) {
         f->dispose();
     }
     f = new TrainRoadOptionsFrame();
     f->initComponents(frame);
 }
}
