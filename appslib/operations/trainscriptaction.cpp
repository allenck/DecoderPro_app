#include "trainscriptaction.h"
#include "trainscriptframe.h"
#include "traineditframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a TrainScriptFrame.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 ///*public*/ class TrainScriptAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 3104111810133179128L;

 /*public*/ TrainScriptAction::TrainScriptAction(QString s, TrainEditFrame* frame)
  : AbstractAction(s, frame)
 {
     //super(s);
     f = NULL;
     this->frame = frame;
     connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }

 /*public*/ void TrainScriptAction::actionPerformed(ActionEvent* /*e*/) {
     // create a train scripts frame
     if (f != NULL && f->isVisible()) {
         f->dispose();
     }
     f = new TrainScriptFrame();
     f->move(frame->pos());
     f->initComponents(frame);
     //f.setExtendedState(Frame.NORMAL);
     f->setTitle(tr("Scripts"));
 }
}
