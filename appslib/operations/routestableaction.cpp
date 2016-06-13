#include "routestableaction.h"
#include "routestableframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a RoutesTableFrame object.
  *
  * @author	Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2008
  * @version $Revision: 28746 $
  */
 ///*public*/ class RoutesTableAction extends AbstractAction {

 /**
  *
  */
 // /*private*/ static final long serialVersionUID = -5090064971975194515L;

 /*public*/ RoutesTableAction::RoutesTableAction(QString s, QObject* parent)
    : AbstractAction(s, parent)
 {
     //super(s);
  common();
 }

 /*public*/ RoutesTableAction::RoutesTableAction(QObject* parent)
 : AbstractAction(tr("Routes"),parent) {
     //this(Bundle.getMessage("MenuRoutes"));	// NOI18N
 common();
 }
 void RoutesTableAction::common()
 {
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*static*/ RoutesTableFrame* RoutesTableAction::f = NULL;

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void RoutesTableAction::actionPerformed(ActionEvent* e)
 {

  // create a route table frame
  if (f == NULL || !f->isVisible()) {
      f = new RoutesTableFrame();
  }
  //f.setExtendedState(Frame.NORMAL);
  f->setVisible(true);	// this also brings the frame into focus

 }
}

