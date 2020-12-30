#include "trainsscheduleeditaction.h"
#include "trainsscheduleeditframe.h"

namespace Operations
{
 /**
  * Action to edit timetable (Schedule)
  *
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 29599 $
  */
 ///*public*/ class TrainsScheduleEditAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 1796097519377642811L;

 /*public*/ TrainsScheduleEditAction::TrainsScheduleEditAction(QObject* parent)
  : AbstractAction(tr("Edit Schedule"), parent)
 {
     //super(Bundle.getMessage("MenuItemEditSchedule"));
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void TrainsScheduleEditAction::actionPerformed(JActionEvent* /*e*/) {
     new TrainsScheduleEditFrame();
 }
}
