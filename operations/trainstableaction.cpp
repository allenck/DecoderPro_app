#include "trainstableaction.h"
#include "trainstableframe.h"

namespace Operations {
/**
 * Swing action to create and register a TrainTableFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 28746 $
 */
///*public*/ class TrainsTableAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -7608766876884479719L;

 /*public*/ TrainsTableAction::TrainsTableAction(QString s, QObject* parent) : AbstractAction(s, parent) {
     //super(s);
 common();
 }

 /*public*/ TrainsTableAction::TrainsTableAction(QObject* parent) : AbstractAction(tr("Trains"), parent) {
     //this(Bundle.getMessage("MenuTrains"));	// NOI18N
common();
 }
 void TrainsTableAction::common()
 {
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*static*/ TrainsTableFrame* TrainsTableAction::f = NULL;

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void TrainsTableAction::actionPerformed(JActionEvent* /*e*/) {
     // create a train table frame
     if (f == NULL || !f->isVisible()) {
         f = new TrainsTableFrame();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
