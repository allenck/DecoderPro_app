#include "locationtrackblockingorderaction.h"
#include "location.h"
#include "locationtrackblockingorderframe.h"

namespace Operations
{
 /**
  * Opens the location track blocking order window.
  *
  * @author Daniel Boudreau Copyright (C) 2015
  * @version $Revision: 28746 $
  */
 ///*public*/ class LocationTrackBlockingOrderAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -8755364574386629561L;

 /*public*/ LocationTrackBlockingOrderAction::LocationTrackBlockingOrderAction(Location* location, QObject* parent)
     : AbstractAction(tr("Track Blocking Order"), parent)
 {
     //super(Bundle.getMessage("TitleTrackBlockingOrder"));
 common();
     _location = location;
 }

 /*public*/ LocationTrackBlockingOrderAction::LocationTrackBlockingOrderAction(QObject* parent)
 : AbstractAction(tr("Modify Locations"), parent)
 {
    // super(Bundle.getMessage("TitleModifyLocations"));
  common();
 }
 void LocationTrackBlockingOrderAction::common()
 {
  _frame = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void LocationTrackBlockingOrderAction::actionPerformed(ActionEvent* /*e*/) {
     // create a frame
     if (_frame == NULL || !_frame->isVisible()) {
         _frame = new LocationTrackBlockingOrderFrame();
         _frame->initComponents(_location);
     }
    // _frame.setExtendedState(Frame.NORMAL);
     _frame->setVisible(true);	// this also brings the frame into focus
 }
}
