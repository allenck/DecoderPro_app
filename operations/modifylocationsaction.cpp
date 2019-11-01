#include "modifylocationsaction.h"
#include "locationsbycartypeframe.h"

namespace Operations
{
 /**
  *
  */
 //private static final long serialVersionUID = -8755364574386629561L;

 /*public*/ ModifyLocationsAction::ModifyLocationsAction(QString s, Location* location, QObject* parent)
 : AbstractAction(s, parent)
 {
     //super(s);
 common();
     l = location;
 }

 /*public*/ ModifyLocationsAction::ModifyLocationsAction(QString s, QObject* parent)
 : AbstractAction(s, parent)
 {
     //super(s);
 common();
 }

 /*public*/ ModifyLocationsAction::ModifyLocationsAction( QObject* parent) :AbstractAction(tr("Modify Locations"), parent) {
     //super(Bundle.getMessage("Modify Locations by Car Type"));
 common();
 }

 void ModifyLocationsAction::common()
 {
  f = NULL;
  l = NULL;
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }



 /*public*/ void ModifyLocationsAction::actionPerformed(ActionEvent* /*e*/) {
     // create a frame
     if (f == NULL || !f->isVisible()) {
         f = new LocationsByCarTypeFrame();
         f->initComponents(l);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
