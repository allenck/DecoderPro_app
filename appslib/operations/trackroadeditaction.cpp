#include "trackroadeditaction.h"
#include "trackroadeditframe.h"
#include "trackeditframe.h"

namespace Operations
{
/**
 * Action to create the TrackRoadEditFrame.
 *
 * @author Daniel Boudreau Copyright (C) 2013
 * @version $Revision: 22219 $
 */
///*public*/ class TrackRoadEditAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -9194843902287797355L;

 /*public*/ TrackRoadEditAction::TrackRoadEditAction(TrackEditFrame* frame)
    : AbstractAction(tr("Road Options"),frame)
 {
     //(Bundle.getMessage("MenuItemRoadOptions"));
     _frame = frame;
     tref = NULL;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void TrackRoadEditAction::actionPerformed(ActionEvent* /*e*/) {
     if (tref != NULL) {
         tref->dispose();
     }
     tref = new TrackRoadEditFrame();
     tref->initComponents(_frame->_location, _frame->_track);
 }
}
