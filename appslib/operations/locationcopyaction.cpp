#include "locationcopyaction.h"
#include "locationcopyframe.h"

namespace Operations
{
 /**
  *
  */
 //private static final long serialVersionUID = 2327541514192626388L;

 /*public*/ LocationCopyAction::LocationCopyAction(QObject* parent)
  : AbstractAction(tr("Copy Location"), parent)
 {
     //super(Bundle.getMessage("MenuItemCopyLocation"));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
  f= NULL;
 }


 /*public*/ void LocationCopyAction::actionPerformed(ActionEvent* e)
 {
     // create a copy track frame
     if (f == NULL || !f->isVisible()) {
         f = new LocationCopyFrame();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
