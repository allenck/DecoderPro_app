#include "printswitchlistaction.h"
#include "trainswitchlists.h"
#include "setup.h"

namespace Operations
{
 /**
  * Swing action to preview or print a switch list for a location.
  *
  * @author Daniel Boudreau Copyright (C) 2013
  * @version $Revision: 22219 $
  */
 ///*public*/ class PrintSwitchListAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -686196539645588273L;

 /*public*/ PrintSwitchListAction::PrintSwitchListAction(QString actionName, Location* location, bool isPreview, QObject* parent)
     : AbstractAction(actionName, parent)
 {
     //super(actionName);
     this->location = location;
     this->isPreview = isPreview;
     // The switch list must be accessed from the Trains window if running in consolidated mode
     setEnabled(Setup::isSwitchListRealTime());
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintSwitchListAction::actionPerformed(ActionEvent* /*e*/) {
     TrainSwitchLists* ts = new TrainSwitchLists();
     ts->buildSwitchList(location);
     ts->printSwitchList(location, isPreview);
 }
}
