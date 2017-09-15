#include "ignoreusedtrackaction.h"
#include "trackeditframe.h"
#include "ignoreusedtrackframe.h"

namespace Operations
{
 /**
  * Action to allow a user to define how much used track space is to be ignored
  * by the program when placing new rolling stock to a track.
  *
  * @author Daniel Boudreau Copyright (C) 2012
  * @version $Revision: 18559 $
  */
 //public class IgnoreUsedTrackAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 5281427667478029138L;

 /*public*/ IgnoreUsedTrackAction::IgnoreUsedTrackAction(TrackEditFrame* tef)
 : AbstractAction(tr("Planned Pickups"), tef)
 {
     //super(Bundle.getMessage("MenuItemPlannedPickups"));
     _tef = tef;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void IgnoreUsedTrackAction::actionPerformed(ActionEvent* /*e*/) {
     if (_iutf != NULL) {
         _iutf->dispose();
     }
     _iutf = new IgnoreUsedTrackFrame(_tef);
 }
}
