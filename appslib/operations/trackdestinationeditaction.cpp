#include "trackdestinationeditaction.h"
#include "trackdestinationeditframe.h"
#include "trackeditframe.h"

namespace Operations
{
 /**
  *
  */
 //private static final long serialVersionUID = -8415281805320154117L;

 /*public*/ TrackDestinationEditAction::TrackDestinationEditAction(TrackEditFrame* frame)
    : AbstractAction(tr("Destinations"), frame)
 {
     //super(Bundle.getMessage("MenuItemDestinations"));
     tdef = NULL;
     _frame = frame;
     connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }

 /*public*/ void TrackDestinationEditAction::actionPerformed(ActionEvent* e) {
     if (tdef != NULL) {
         tdef->dispose();
     }
     tdef = new TrackDestinationEditFrame();
     tdef->initComponents(_frame->_track);
 }
}
