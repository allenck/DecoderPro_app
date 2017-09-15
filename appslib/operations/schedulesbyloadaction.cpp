#include "schedulesbyloadaction.h"
#include "schedulesbyloadframe.h"

namespace Operations
{
 /**
  * Action to load the schedules by car type and load frame.
  *
  * @author Daniel Boudreau Copyright (C) 2012
  * @version $Revision: 17977 $
  */
 ///*public*/ class SchedulesByLoadAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -6680843615707655230L;

 /*public*/ SchedulesByLoadAction::SchedulesByLoadAction(QString actionName, QObject* parent) : AbstractAction(actionName, parent) {
     //super(actionName);
     _slf = NULL;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void SchedulesByLoadAction::actionPerformed(ActionEvent* /*e*/) {
     if (_slf != NULL) {
         _slf->dispose();
     }
     _slf = new SchedulesByLoadFrame();
 }
}
