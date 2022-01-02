#include "trackcopyaction.h"
#include "locationeditframe.h"

namespace Operations
{
 /*public*/ TrackCopyAction::TrackCopyAction(QObject* parent) : AbstractAction(tr("Copy Track"), parent){
         //super(Bundle.getMessage("MenuItemCopyTrack"));
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

 }

 /*public*/ TrackCopyAction::TrackCopyAction(LocationEditFrame* lef)
    : AbstractAction(tr("Copy Track"),lef)
 {
     //super(Bundle.getMessage("MenuItemCopyTrack"));
     _lef = lef;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void TrackCopyAction::actionPerformed(JActionEvent * /*e*/) {
     // create a copy track frame
     if (f == NULL || !f->isVisible()) {
         f = new TrackCopyFrame(_lef);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
