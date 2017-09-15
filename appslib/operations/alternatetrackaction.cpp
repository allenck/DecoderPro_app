#include "alternatetrackaction.h"
#include "trackeditframe.h"
#include "alternatetrackframe.h"

namespace Operations
{
 /**
  * Action to launch selection of alternate track.
  *
  * @author Daniel Boudreau Copyright (C) 2011
  * @version $Revision: 17977 $
  */
 ///*public*/ class AlternateTrackAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -5179558203243699849L;

 /*public*/ AlternateTrackAction::AlternateTrackAction(TrackEditFrame* tef)  : AbstractAction(tr("Alternate Track"), tef){
     //super(Bundle.getMessage("AlternateTrack"));
     _tef = tef;
     connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }

 /*public*/ void AlternateTrackAction::actionPerformed(ActionEvent* /*e*/) {
     new AlternateTrackFrame(_tef);
 }
}
