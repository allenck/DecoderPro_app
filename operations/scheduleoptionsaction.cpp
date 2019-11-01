#include "scheduleoptionsaction.h"
#include "scheduleoptionsframe.h"
#include "scheduleeditframe.h"

namespace Operations
{
 /**
  * Action to launch schedule options.
  *
  * @author Daniel Boudreau Copyright (C) 2010, 2011
  * @version $Revision: 28746 $
  */
 //*public*/ class ScheduleOptionsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 6958291145537202643L;

 /*public*/ ScheduleOptionsAction::ScheduleOptionsAction(ScheduleEditFrame* sef) : AbstractAction(tr("Schedule Options"), sef) {
     //super(Bundle.getMessage("MenuItemScheduleOptions"));
     _sef = sef;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ScheduleOptionsAction::actionPerformed(ActionEvent* /*e*/) {
     new ScheduleOptionsFrame(_sef);
 }
}
