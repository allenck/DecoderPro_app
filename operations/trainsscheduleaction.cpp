#include "trainsscheduleaction.h"

namespace Operations
{
 /**
  * Swing action to create and register a TrainsScheduleTableFrame object.
  *
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 ///*public*/ class TrainsScheduleAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -2153851570593170952L;

 /*public*/ TrainsScheduleAction::TrainsScheduleAction(QString s, QObject* parent)
   : AbstractAction(s, parent)
{
  //super(s);
  f = NULL;
  connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }


 /*public*/ void TrainsScheduleAction::actionPerformed(JActionEvent* /*e*/) {
     // create a frame
     if (f == NULL || !f->isVisible()) {
         f = new TrainsScheduleTableFrame();
     }
     f->setExtendedState(JFrame::NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
