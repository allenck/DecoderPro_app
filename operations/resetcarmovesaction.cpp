#include "resetcarmovesaction.h"
#include "carmanager.h"
#include <QMessageBox>
#include "logger.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * This routine will reset the move count for all cars in the operation
  * database.
  *
  * @author Dan Boudreau Copyright (C) 2012
  * @version $Revision: 17977 $
  */
 ///*public*/ class ResetCarMovesAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -583218206426311128L;

 /*public*/ ResetCarMovesAction::ResetCarMovesAction(QString actionName, QWidget* frame)
     : AbstractAction(actionName, frame)
 {
     //super(actionName);
  log = new Logger("ResetCarMoves");
  manager = ((CarManager*)InstanceManager::getDefault("CarManager"));
  connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }

 /*public*/ void ResetCarMovesAction::actionPerformed(ActionEvent* ae)
 {
//     if (JOptionPane.showConfirmDialog(null, Bundle.getMessage("carSureResetMoves"),
//             Bundle.getMessage("carResetMovesAll"), JOptionPane.OK_CANCEL_OPTION) == JOptionPane.OK_OPTION) {
  if(QMessageBox::question(NULL, tr("Reset the move counts?"), tr("Are you sure you want to reset the move count for all of the cars in your roster?"), QMessageBox::Ok | QMessageBox::Cancel)== QMessageBox::Ok)
  {
   log->debug("Reset moves for all cars in roster");
   manager->resetMoves();
  }
 }
}
