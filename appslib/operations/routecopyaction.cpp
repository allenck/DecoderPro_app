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

 /*public*/ RouteCopyAction::RouteCopyAction(QString s, QObject* parent)
   : AbstractAction(s,parent)
 {
     //super(s);
 common();
 }


 /*public*/ RouteCopyAction::RouteCopyAction(QString s, QString routeName,  QObject* parent)
 : AbstractAction(s,parent)
 {
     //super(s);
     common();
     this->routeName = routeName;
 }

void RouteCopyAction::common()
{
 f= NULL;
 routeName = "";
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

 /*public*/ void RouteCopyAction::actionPerformed(ActionEvent* e) {
     // create a copy route frame

     if (f == NULL || !f->isVisible()) {
         f = new RouteCopyFrame();
     }
     if (routeName != NULL) {
         f->setRouteName(routeName);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
