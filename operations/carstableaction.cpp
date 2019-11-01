#include "carstableaction.h"
#include "carstableframe.h"

//CarsTableAction::CarsTableAction()
//{

//}
namespace Operations
{
 /**
  * Swing action to create and register a CarsTableFrame object.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2008
  * @version $Revision: 28746 $
  */
 ///*public*/ class CarsTableAction extends AbstractAction {

 /**
   *
  */
 //private static final long serialVersionUID = 1165041540465869264L;

 /*public*/ CarsTableAction::CarsTableAction(QString s, QObject* parent)
  : AbstractAction(s, parent)
 {
     //super(s);
  common();
 }

 /*public*/ CarsTableAction::CarsTableAction(QObject* parent)
  : AbstractAction(tr("Cars"), parent) {
     //this(Bundle.getMessage("MenuCars")); // NOI18N
  common();
 }

 /*public*/ void CarsTableAction::actionPerformed(ActionEvent* /*e*/) {
     // create a car table frame
     new CarsTableFrame(true, "", "");
 }
 void CarsTableAction::common()
 {
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }
}
