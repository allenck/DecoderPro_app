#include "deletecarrosteraction.h"
#include "joptionpane.h"
#include "carstableframe.h"
#include "carstablemodel.h"
#include "track.h"
#include "carmanager.h"
#include "logger.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * This routine will remove all cars from the operation database,
  * or remove all cars sitting on a track.
  *
  * @author Dan Boudreau Copyright (C) 2007, 2016
  * @version $Revision$
  */
 ///*public*/ class DeleteCarRosterAction extends AbstractAction {




 /*public*/ DeleteCarRosterAction::DeleteCarRosterAction(CarsTableFrame* carsTableFrame)
    : AbstractAction(carsTableFrame->carsTableModel->trackName==""?tr("Delete"):tr("Delete cars on track"), carsTableFrame)
 {
//     super(carsTableFrame.carsTableModel.trackName == NULL ?
//             tr("MenuItemDelete") :
//             MessageFormat.format(tr("MenuDeleteCarsTrack"), new Object[]{carsTableFrame.carsTableModel.trackName}));
     common();
     _carsTableFrame = carsTableFrame;
 }

 void DeleteCarRosterAction::common()
 {
  log = new Logger("DeleteCarRosterAction");
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 //@Override
 /*public*/ void DeleteCarRosterAction::actionPerformed(JActionEvent* /*ae*/)
 {
  if (_carsTableFrame->carsTableModel->trackName == NULL)
  {
   if (JOptionPane::showConfirmDialog(NULL,  tr("Are you sure you want to delete all the cars in your roster?"),
             tr("Delete all cars?"), JOptionPane::OK_CANCEL_OPTION) == JOptionPane::OK_OPTION)
   {
    log->debug("removing all cars from roster");
    ((CarManager*)InstanceManager::getDefault("Operations::CarManager"))->deleteAll();
   }
  }
  else
  {
 if (JOptionPane::showConfirmDialog(NULL, tr("Are you sure you want to delete all the cars on track %1?").arg(_carsTableFrame->carsTableModel->trackName),
                 tr("Delete all cars?"), JOptionPane::OK_CANCEL_OPTION) == JOptionPane::OK_OPTION)
   {
    foreach (Car* car, *_carsTableFrame->carsTableModel->getSelectedCarList())
    {
     ((CarManager*)InstanceManager::getDefault("Operations::CarManager"))->deregister((RollingStock*)car);
    }
   }
  }
 }
} // Operations namespace
