#include "trainconductoraction.h"
#include "trainconductorframe.h"

namespace Operations
{
/**
  *
  */
 ///*private*/ static final long serialVersionUID = -6897376422747877387L;

 /*public*/ TrainConductorAction::TrainConductorAction(QString s, Train* train, QObject* parent)
   : AbstractAction(s, parent)
 {
     //super(s);
  f = NULL;
     this->train = train;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 //@Override
 /*public*/ void TrainConductorAction::actionPerformed(ActionEvent* e) {
     // create a copy train frame
     if (f == NULL || !f->isVisible()) {
         f = new TrainConductorFrame(train);
     } else {
         //f.setExtendedState(Frame.NORMAL);
     }
     f->setVisible(true);	// this also brings the frame into focus
 }
}
