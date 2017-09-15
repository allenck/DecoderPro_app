#include "changedeparturetimesaction.h"
#include "changedeparturetimesframe.h"

namespace Operations
{
 /**
  * Swing action to launch the Change Departure Time window.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2013
  * @version $Revision: 17977 $
  */
 ///*public*/ class ChangeDepartureTimesAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -1524083857693353335L;

 /*public*/ ChangeDepartureTimesAction::ChangeDepartureTimesAction(QString s, QObject* parent)
  : AbstractAction(s, parent)
 {
     //super(s);
  f = NULL;
  connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }


 /*public*/ void ChangeDepartureTimesAction::actionPerformed(ActionEvent* /*e*/) {
     // create a copy train frame
     if (f == NULL || !f->isVisible()) {
         f = new ChangeDepartureTimesFrame();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
