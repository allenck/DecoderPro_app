#include "trainsscriptaction.h"
#include "trainsscriptframe.h"
#include "trainstableframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a TrainsScriptFrame.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2011
  * @version $Revision: 28746 $
  */
 ///*public*/ class TrainsScriptAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -4651831842002920942L;

 /*public*/ TrainsScriptAction::TrainsScriptAction(QString s, TrainsTableFrame* frame)
   :  AbstractAction(s, frame)
 {
     //super(s);
  this->frame = frame;
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }



 /*public*/ void TrainsScriptAction::actionPerformed(JActionEvent *e) {
     // create a train scripts frame
     if (f != NULL && f->isVisible()) {
         f->dispose();
     }
     f = new TrainsScriptFrame();
     f->move(frame->pos().x(),frame->pos().y());
     f->initComponents();
     //f->setExtendedState(Frame.NORMAL);
     f->setTitle(tr("Scripts"));
 }
}
