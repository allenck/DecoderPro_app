#include "locationstableaction.h"
#include "locationstableframe.h"

//LocationsTableAction::LocationsTableAction()
//{

//}
namespace Operations
{
/**
 * Swing action to create and register a LocationTableFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 28746 $
 */
///*NULL*/ class LocationsTableAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -8215433161940132587L;

 /*NULL*/ LocationsTableAction::LocationsTableAction(QString s, QObject* parent) : AbstractAction(s, parent) {
     //super(s);
 common();
 }

 /*NULL*/ LocationsTableAction::LocationsTableAction(QObject* parent) : AbstractAction(tr("Locations"), parent)
{
     //this(Bundle.getMessage("MenuLocations"));	// NOI18N
 common();
 }

 /*static*/ LocationsTableFrame* LocationsTableAction::f = NULL;

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*NULL*/ void LocationsTableAction::actionPerformed(ActionEvent* e) {
     // create a location table frame

     if (f == NULL || !f->isVisible()) {
         f = new LocationsTableFrame();
     }
     //f->setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus

 }
 void LocationsTableAction::common()
 {
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }
}
