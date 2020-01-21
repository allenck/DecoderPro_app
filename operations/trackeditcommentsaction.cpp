#include "trackeditcommentsaction.h"
#include "trackeditcommentsframe.h"
#include "trackeditframe.h"

namespace Operations
{
/**
 * Action to launch edit of track comments.
 *
 * @author Daniel Boudreau Copyright (C) 2013
 * @version $Revision: 17977 $
 */
//public class TrackEditCommentsAction extends AbstractAction {

 /**
  *
  */

 /*public*/ TrackEditCommentsAction::TrackEditCommentsAction(TrackEditFrame* tef)
 : AbstractAction(tr("Item Comments"), (QWidget*)tef)
{
    // super(Bundle.getMessage("MenuItemComments"));
     _tef = tef;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void TrackEditCommentsAction::actionPerformed(ActionEvent* /*e*/) {
     new TrackEditCommentsFrame(_tef->_track);
 }

}
