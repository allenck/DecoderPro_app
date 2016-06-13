#include "trainmanifestoptionaction.h"
#include "traineditframe.h"
#include "trainmanifestoptionframe.h"

namespace Operations
{
 /**
  * Swing action to load the train manifest options frame.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 //public class TrainManifestOptionAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 5997184366069609071L;

 /*public*/ TrainManifestOptionAction::TrainManifestOptionAction(QString s, TrainEditFrame* frame)
 : AbstractAction(s, frame)
 {
     //super(s);
     this->frame = frame;
     f = NULL;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ void TrainManifestOptionAction::actionPerformed(ActionEvent* e) {
     // create a settings frame
     if (f == NULL || !f->isVisible()) {
         f = new TrainManifestOptionFrame();
         f->initComponents(frame);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }

}
