#include "trainstablesetcoloraction.h"
#include "trainstablesetcolorframe.h"
#include "train.h"

namespace Operations
{
 /**
  * Swing action to create and register a TrainSetColorFrame object.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2014
  * @version $Revision: 17977 $
  */
 ///*public*/ class TrainsTableSetColorAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 2895152667316839146L;

 /*public*/ TrainsTableSetColorAction::TrainsTableSetColorAction(QObject* parent)
    : AbstractAction(tr("Set Train Color"), parent)
 {
     //super(Bundle.getMessage("MenuItemSetTrainColor"));
  common();
 }


 /*public*/ TrainsTableSetColorAction::TrainsTableSetColorAction(QString s, Train* train, QObject* parent)
    : AbstractAction(s, parent)
 {
     //super(s);
     _train = train;
 }

 void TrainsTableSetColorAction::common()
 {
  _train = NULL;
  f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

 }

 /*public*/ void TrainsTableSetColorAction::actionPerformed(JActionEvent* /*e*/) {
     if (f == NULL || !f->isVisible()) {
         f = new TrainsTableSetColorFrame(_train);
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true); // this also brings the frame into focus
 }
}
