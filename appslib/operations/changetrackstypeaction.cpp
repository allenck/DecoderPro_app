#include "changetrackstypeaction.h"
#include "changetracksframe.h"

namespace Operations
{
 /**
  *
  */
 //private static final long serialVersionUID = -4301236628809396753L;

 /*public*/ ChangeTracksTypeAction::ChangeTracksTypeAction(LocationEditFrame* lef)
 : AbstractAction(tr("Change Track Type"), lef){
     //super(Bundle.getMessage("MenuItemChangeTrackType"));
     _lef = lef;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ChangeTracksTypeAction::actionPerformed(ActionEvent* /*e*/) {
     new ChangeTracksFrame(_lef);
 }
}
