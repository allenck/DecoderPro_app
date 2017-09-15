#include "pooltrackaction.h"
#include "pooltrackframe.h"
#include "trackeditframe.h"
namespace Operations
{
 /**
  * Action to create a track pool and place a track in that pool.
  *
  * @author Daniel Boudreau Copyright (C) 2011
  * @author Gregory Madsen Copyright (C) 2012
  * @version $Revision: 28746 $
  */
 ///*public*/ class PoolTrackAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -9167674151000147867L;

 /*public*/ PoolTrackAction::PoolTrackAction(TrackEditFrame* tef)
    : AbstractAction(tr("Pool Track"),(QObject*)tef)
 {
     //super(Bundle.getMessage("MenuItemPoolTrack"));
     _tef = tef;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void PoolTrackAction::actionPerformed(ActionEvent* /*e*/) {
     if (_ptf != NULL) {
         _ptf->dispose();
     }
     _ptf = new PoolTrackFrame(_tef->_track);
     _ptf->initComponents();
 }
}
