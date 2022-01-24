#include "modifylocationscarloadsaction.h"
namespace Operations
{
 /**
  * Swing action to create and register a LocationsByCarTypeFrame object.
  *
  * @author Daniel Boudreau Copyright (C) 2009
  * @version $Revision: 23881 $
  */
 ///*public*/ class ModifyLocationsCarLoadsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -3251382228253085472L;

 /*public*/ ModifyLocationsCarLoadsAction::ModifyLocationsCarLoadsAction(Location* location, QObject* parent)
    : AbstractAction(tr("Modify Location by Car Load"), parent)
 {
     //super(tr("TitleModifyLocationLoad"));
  common();
     _location = location;
 }

 /*public*/ ModifyLocationsCarLoadsAction::ModifyLocationsCarLoadsAction(QObject* parent)
 : AbstractAction(tr("Modify Location by Car Load"), parent)
 {
  common();
  //super(tr("TitleModifyLocationsLoad"));
 }

 void ModifyLocationsCarLoadsAction::common()
 {
  f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void ModifyLocationsCarLoadsAction::actionPerformed(JActionEvent* /*e*/) {
     // create a frame
     if (f == NULL || !f->isVisible()) {
         f = new LocationsByCarLoadFrame();
         f->initComponents(_location);
     }
     f->setExtendedState(JFrame::NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}

