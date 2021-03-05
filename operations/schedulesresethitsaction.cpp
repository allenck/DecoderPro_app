#include "schedulesresethitsaction.h"
#include "schedulemanager.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * Action to reset the all of the schedule item hit counts for all schedules
  *
  * @author Daniel Boudreau Copyright (C) 2014
  * @version $Revision: 17977 $
  */
 ///*public*/ class SchedulesResetHitsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -8261728289596035515L;

 /*public*/ SchedulesResetHitsAction::SchedulesResetHitsAction(QString s, QObject* parent) : AbstractAction(s, parent) {
     //super(s);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void SchedulesResetHitsAction::actionPerformed(ActionEvent* /*e*/) {
     ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->resetHitCounts();
 }
}
