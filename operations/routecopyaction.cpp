#include "routecopyaction.h"
#include "routecopyframe.h"

namespace Operations
{
/**
 * Swing action to create and register a RouteCopyFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 28746 $
 */
///*public*/ class RouteCopyAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -8588935081117079361L;

 /*public*/ RouteCopyAction::RouteCopyAction(QObject* parent) : AbstractAction(tr("Copy"), parent){
         //super(Bundle.getMessage("MenuItemCopy"));
  common();
}

/*public*/ RouteCopyAction::RouteCopyAction(Route* route, QObject* parent) : AbstractAction(tr("Copy"), parent){
    //this();
  common();
    _route = route;
}

void RouteCopyAction::common()
{
 f= NULL;
 routeName = "";
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

 /*public*/ void RouteCopyAction::actionPerformed(ActionEvent* /*e*/) {
     // create a copy route frame

     if (f == NULL || !f->isVisible()) {
         f = new RouteCopyFrame(_route);
     }
     if (routeName != NULL) {
         f->setRouteName(routeName);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
