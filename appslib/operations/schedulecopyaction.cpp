#include "schedulecopyaction.h"
#include "schedulecopyframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a ScheduleCopyFrame object.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2015
  * @version $Revision: 17977 $
  */
 ///*public*/ class ScheduleCopyAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 2327541514192626388L;

 /*public*/ ScheduleCopyAction::ScheduleCopyAction(QObject* parent)
  : AbstractAction(tr("Copy Schedule"),parent)
 {
     //super(Bundle.getMessage("MenuItemCopySchedule"));
  f = NULL;
  schedule = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ ScheduleCopyAction::ScheduleCopyAction(Schedule* schedule, QObject* parent)
 : AbstractAction(tr("Copy Schedule"),parent)
 {
     //this();
 f = NULL;
     this->schedule = schedule;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ void ScheduleCopyAction::actionPerformed(ActionEvent* /*e*/) {
     // create a copy track frame
     if (f == NULL || !f->isVisible()) {
         f = new ScheduleCopyFrame(schedule);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
