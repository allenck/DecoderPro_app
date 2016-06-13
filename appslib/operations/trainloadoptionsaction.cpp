#include "trainloadoptionsaction.h"
#include "traineditframe.h"
#include "trainloadoptionsframe.h"

namespace Operations

{
 /**
  * Swing action to create and register a TrainLoadOptionsFrame.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2013
  * @version $Revision: 21765 $
  */
 ///*public*/ class TrainLoadOptionsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -9221271710779934736L;

 /*public*/ TrainLoadOptionsAction::TrainLoadOptionsAction(QString s, TrainEditFrame* frame)
 : AbstractAction(s, frame)
 {
     //super(s);
     this->frame = frame;
  f = NULL;
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void TrainLoadOptionsAction::actionPerformed(ActionEvent* e) {
     // create a train edit option frame
     if (f != NULL && f->isVisible()) {
         f->dispose();
     }
     f = new TrainLoadOptionsFrame();
     f->initComponents(frame);
 }
}

