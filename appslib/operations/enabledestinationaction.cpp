#include "enabledestinationaction.h"
#include "carsetframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a CarsSetFrame object.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 22219 $
  */
 //public class EnableDestinationAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -6780168973942677595L;

 /*public*/ EnableDestinationAction::EnableDestinationAction(QString s, CarSetFrame* frame)
     : AbstractAction(s, frame )
 {
    // super(s);
     _csFrame = frame;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void EnableDestinationAction::actionPerformed(ActionEvent* e) {
     _csFrame->setDestinationEnabled(true);
 }
}

