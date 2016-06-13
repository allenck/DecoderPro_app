#include "changetracktypeaction.h"
#include "trackeditframe.h"
#include "changetrackframe.h"

namespace Operations
{
 /**
  * Action to change the type of track. Track types are Spurs, Yards,
  * Interchanges and Staging.
  *
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 ///*public*/ class ChangeTrackTypeAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -9023722229777217045L;

 /*public*/ ChangeTrackTypeAction::ChangeTrackTypeAction(TrackEditFrame* tef)
    : AbstractAction(tr("Change Track Type"),tef)

 {
  //super(Bundle.getMessage("MenuItemChangeTrackType"));
     _tef = tef;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ChangeTrackTypeAction::actionPerformed(ActionEvent* e) {
     new ChangeTrackFrame(_tef);
 }
}
