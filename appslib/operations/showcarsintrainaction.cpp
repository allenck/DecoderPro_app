#include "showcarsintrainaction.h"
#include "showcarsintrainframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a ShowCarsInTrainFrame.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2012
  * @version $Revision: 17977 $
  */
 ///*public*/ class ShowCarsInTrainAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -269006813756862745L;

 /*public*/ ShowCarsInTrainAction::ShowCarsInTrainAction(QString s, Train* train, QObject* parent)
    : AbstractAction(s, parent)
 {
     //super(s);
     this->train = train;
     f=NULL;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ void ShowCarsInTrainAction::actionPerformed(ActionEvent* e) {
     // create a copy train frame
     if (f == NULL || !f->isVisible()) {
         f = new ShowCarsInTrainFrame();
         f->initComponents(train);
     } else {
         //f.setExtendedState(Frame.NORMAL);
         f->setVisible(true);	// this also brings the frame into focus
     }
 }
}
