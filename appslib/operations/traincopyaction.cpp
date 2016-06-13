#include "traincopyaction.h"
#include "traincopyframe.h"

namespace Operations
{
 /**
  * Swing action to create and register a TrainCopyFrame object.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2011
  * @version $Revision: 17977 $
  */
 ///*public*/ class TrainCopyAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -8004749161373746580L;

 /*public*/ TrainCopyAction::TrainCopyAction(QString s, QObject* parent)
    : AbstractAction(s, parent)
 {
  //super(s);
  common();
 }


 /*public*/ TrainCopyAction::TrainCopyAction(QString s, Train* train, QObject* parent)
 : AbstractAction(s, parent)
 {
     //super(s);
     common();
     _train = train;
 }

 void TrainCopyAction::common()
 {
  _train = NULL;
  f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void TrainCopyAction::actionPerformed(ActionEvent* e) {
     // create a copy train frame
     if (f == NULL || !f->isVisible()) {
         f = new TrainCopyFrame(_train);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true); // this also brings the frame into focus
 }
}
