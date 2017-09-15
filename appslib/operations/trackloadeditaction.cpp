#include "trackloadeditaction.h"
#include "trackeditframe.h"
#include "trackloadeditframe.h"

namespace Operations
{
/**
 * Action to create the TrackLoadEditFrame.
 *
 * @author Daniel Boudreau Copyright (C) 2013
 * @version $Revision: 22219 $
 */
///*public*/ class TrackLoadEditAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -7801467181503433207L;

 /*public*/ TrackLoadEditAction::TrackLoadEditAction(TrackEditFrame* frame)
   : AbstractAction(tr("Load Options"), frame)
{
    // super(Bundle.getMessage("MenuItemLoadOptions"));
     _frame = frame;
     tlef = false;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void TrackLoadEditAction::actionPerformed(ActionEvent* /*e*/)
 {
  if (tlef != NULL)
  {
   tlef->dispose();
  }
  tlef = new TrackLoadEditFrame();
  tlef->initComponents(_frame->_location, _frame->_track);
 }
}
