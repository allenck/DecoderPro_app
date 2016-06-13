#include "editcartypeaction.h"
#include "carattributeeditframe.h"
#include "careditframe.h"
namespace Operations
{
 /**
  *
  */
 //private static final long serialVersionUID = 7154562626596982051L;

 /*public*/ EditCarTypeAction::EditCarTypeAction(QObject* parent) : AbstractAction(tr("Edit Car Type"), parent) {
     //super(Bundle.getMessage("MenuItemEditCarType"));
  f = NULL;
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void EditCarTypeAction::actionPerformed(ActionEvent* e) {
     // create a copy track frame
     if (f == NULL || !f->isVisible()) {
         f = new CarAttributeEditFrame();
     }
     f->initComponents(CarEditFrame::TYPE, NULL);
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
