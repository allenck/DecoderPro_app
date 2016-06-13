#include "trainsbycartypeaction.h"
#include "trainsbycartypeframe.h"

namespace Operations
{
/**
 * Swing action to create and register a TrainsByCarTypeFrame object.
 *
 * @author Daniel Boudreau Copyright (C) 2009
 * @version $Revision: 28746 $
 */
///*public*/ class TrainsByCarTypeAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 2521837006549809639L;

 /*public*/ TrainsByCarTypeAction::TrainsByCarTypeAction(QString s, QObject* parent) : AbstractAction(s, parent){
     //super(s);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ TrainsByCarTypeAction::TrainsByCarTypeAction(QObject* parent)
: AbstractAction(tr("Modify Trains by Car Type"), parent) {
     //super(Bundle.getMessage("TitleModifyTrains"));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ void TrainsByCarTypeAction::actionPerformed(ActionEvent* e) {
     // create a frame
     if (f == NULL || !f->isVisible()) {
         f = new TrainsByCarTypeFrame();
         f->initComponents("");
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }
}
