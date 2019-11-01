#include "deletecarrosteraction.h"
#include <QMessageBox>
#include "carstableframe.h"
#include "carstablemodel.h"
#include "track.h"
#include "carmanager.h"
#include "logger.h"

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


 /*public*/ DeleteCarRosterAction::DeleteCarRosterAction(QString actionName, QWidget* frame)
 : AbstractAction(actionName, frame)
 {
  //super(actionName);
  common();
 }

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
 /*public*/ void DeleteCarRosterAction::actionPerformed(ActionEvent* ae)
 {
  if (_carsTableFrame->carsTableModel->trackName == NULL)
  {
//         if (JOptionPane.showConfirmDialog(NULL, tr("carSureDelete"),
//                 tr("carDeleteAll"), JOptionPane.OK_CANCEL_OPTION) == JOptionPane.OK_OPTION) {
   if(QMessageBox::question(NULL, tr("Delete all cars?"), tr("Are you sure you want to delete all the cars in your roster?"),QMessageBox::Ok | QMessageBox::Cancel )== QMessageBox::Ok)
   {
    log->debug("removing all cars from roster");
    CarManager::instance()->deleteAll();
   }
  }
  else
  {
//         if (JOptionPane.showConfirmDialog(NULL, MessageFormat.format(tr("carDeleteCarsTrack"),
//                 new Object[]{_carsTableFrame.carsTableModel.trackName}),
//                 tr("carDeleteAll"), JOptionPane.OK_CANCEL_OPTION) == JOptionPane.OK_OPTION) {
   if(QMessageBox::question(NULL, tr("Delete all cars?"), tr("Are you sure you want to delete all the cars on track %1?").arg(_carsTableFrame->carsTableModel->trackName),QMessageBox::Ok | QMessageBox::Cancel )== QMessageBox::Ok)
   {
    foreach (RollingStock* car, *_carsTableFrame->carsTableModel->getSelectedCarList())
    {
     CarManager::instance()->deregister(car);
    }
   }
  }
 }
}
