#include "trackcopyaction.h"
#include "trackcopyframe.h"
#include "locationeditframe.h"

namespace Operations
{
 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -353491308526162622L;

 /*public*/ TrackCopyAction::TrackCopyAction(LocationEditFrame* lef)
    : AbstractAction(tr("Copy Track"),lef)
 {
     //super(Bundle.getMessage("MenuItemCopyTrack"));
     _lef = lef;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void TrackCopyAction::actionPerformed(ActionEvent* /*e*/) {
     // create a copy track frame
     if (f == NULL || !f->isVisible()) {
         f = new TrackCopyFrame(_lef);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
