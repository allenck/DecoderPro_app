#include "scheduleresethitsaction.h"
#include "schedule.h"
namespace Operations
{
 /**
  * Action to reset the all of the schedule item hit counts for this schedule
  *
  * @author Daniel Boudreau Copyright (C) 2014
  * @version $Revision: 17977 $
  */
 ///*public*/ class ScheduleResetHitsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 8633992345767664436L;

 /*public*/ ScheduleResetHitsAction::ScheduleResetHitsAction(Schedule* schedule, QObject* parent)
 : AbstractAction(tr("Reset Hit Counts"), parent)
 {
  //super(Bundle.getMessage("MenuItemResetHits"));
  _schedule = schedule;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ScheduleResetHitsAction::actionPerformed(ActionEvent* e)
 {
  _schedule->resetHitCounts();
 }
}
