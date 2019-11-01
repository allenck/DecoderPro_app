#include "schedulestableaction.h"
#include "schedulestableframe.h"

namespace Operations
{
/**
 * Swing action to create and register a ScheduleTableFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2009
 * @version $Revision: 28746 $
 */
///*public*/ class SchedulesTableAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 7587426088852825010L;

 /*public*/ SchedulesTableAction::SchedulesTableAction(QString s, QObject* parent)
  : AbstractAction(s, parent) {
     //super(s);
  f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void SchedulesTableAction::actionPerformed(ActionEvent* /*e*/) {
     // create a schedule table frame
     if (f == NULL || !f->isVisible()) {
         f = new SchedulesTableFrame();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
