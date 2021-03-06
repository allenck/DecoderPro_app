#include "locationcopyframe.h"
#include "locationmanager.h"
#include "track.h"
#include "jtextfield.h"
#include <QPushButton>
#include <QBoxLayout>
#include "propertychangeevent.h"
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <gridbaglayout.h>
#include "control.h"
#include "logger.h"
#include "operationsxml.h"
#include "vptr.h"
#include <QPushButton>
#include <QMessageBox>
#include "jcombobox.h"
#include "rollingstockmanager.h"
#include "carmanager.h"
#include "enginemanager.h"
#include "rollingstock.h"
#include "location.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Frame for copying a location for operations.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2014
 * @version $Revision: 17977 $
 */
 ///*public*/ class LocationCopyFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private*/ static final long serialVersionUID = 5798102907541807915L;

// remember state of checkboxes during a session
/*static*/ bool LocationCopyFrame::_moveRollingStock = false;
/*static*/ bool LocationCopyFrame::deleteTrack = false;

  /*public*/ LocationCopyFrame::LocationCopyFrame(QWidget* parent)
   : OperationsFrame(parent)
  {
   log = new Logger("LocationCopyFrame");
   locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));

   // text field
   locationNameTextField = new JTextField(Control::max_len_string_location_name);

   // major buttons
   copyButton = new QPushButton(tr("Copy"));
   saveButton = new QPushButton(tr("Save"));

   // combo boxes
   JComboBox* locationBox = locationManager->getComboBox();

   // checkboxes
   moveRollingStockCheckBox = new QCheckBox(tr("Move Rolling Stock to New Track"));
   deleteTrackCheckBox = new QCheckBox(tr("Delete Copied Track"));

   // general GUI config
   //().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
   QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

   // Set up the panels
   // Layout the panel by rows
   // row 1
   QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  QGroupBox* pName = new QGroupBox();
  pName->setLayout(new GridBagLayout());
  //pName.setBorder(BorderFactory.createTitledBorder(tr("LocationName")));
  pName->setStyleSheet(gbStyleSheet);
  pName->setTitle(tr("Location name"));
  addItem(pName, locationNameTextField, 0, 0);

  // row 2
  QGroupBox* pCopy = new QGroupBox();
  pCopy->setLayout(new GridBagLayout());
  //pCopy.setBorder(BorderFactory.createTitledBorder(tr("SelectLocationToCopy")));
  pCopy->setStyleSheet(gbStyleSheet);
  pCopy->setTitle(tr("Select Location to Copy"));
  addItem(pCopy, locationBox, 0, 0);

  // row 3
  QGroupBox* pOptions = new QGroupBox();
  pOptions->setLayout(new GridBagLayout());
  //pOptions.setBorder(BorderFactory.createTitledBorder(tr("Options")));
  pOptions->setStyleSheet(gbStyleSheet);
  pOptions->setTitle(tr("Options"));
  addItemLeft(pOptions, moveRollingStockCheckBox, 0, 1);
  addItemLeft(pOptions, deleteTrackCheckBox, 0, 2);

  // row 4
  QWidget* pButton = new QWidget();
  pButton->setLayout(new GridBagLayout());
  addItem(pButton, copyButton, 0, 0);
  addItem(pButton, saveButton, 1, 0);

  thisLayout->addWidget(pName);
  thisLayout->addWidget(pCopy);
  thisLayout->addWidget(pOptions);
  thisLayout->addWidget(pButton);

  // set the checkbox states
  moveRollingStockCheckBox->setChecked(_moveRollingStock);
  deleteTrackCheckBox->setChecked(deleteTrack);
  deleteTrackCheckBox->setEnabled(moveRollingStockCheckBox->isChecked());

  // get notified if combo box gets modified
  locationManager->addPropertyChangeListener(this);

  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_Locations", true); // NOI18N

  adjustSize();
  setMinimumSize(QSize(Control::panelWidth400, Control::panelHeight400));

  // setup buttons
  addButtonAction(copyButton);
  addButtonAction(saveButton);

  addCheckBoxAction(moveRollingStockCheckBox);

  setTitle(tr("Copy Location"));
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*protected*/ void LocationCopyFrame::buttonActionPerformed(QWidget* ae)
 {
  QPushButton* source = (QPushButton*)ae;
  if (source == copyButton)
  {
      log->debug("copy location button activated");
      if (!checkName()) {
          return;
      }

      if (locationBox->currentText() == NULL) {
//          JOptionPane.showMessageDialog(this, tr("SelectLocationToCopy"), MessageFormat.format(Bundle
//                  .getMessage("CanNotLocation"), new Object[]{tr("Copy")}), JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(this, tr("Can not %1 location!").arg(tr("Copy")), tr("Select Location to Copy"));
          return;
      }

      Location* location = (Location*) VPtr<Location*>::asPtr(locationBox->currentData());
      // check to see if there are cars scheduled for pickup or set out
      if (moveRollingStockCheckBox->isChecked()) {
          foreach (Track* track, location->getTrackList()) {
              if (track->getPickupRS() > 0) {
//                  JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
//                          .getMessage("FoundRollingStockPickUp"), new Object[]{track.getPickupRS()}),
//                          MessageFormat.format(tr("TrainsServicingTrack"), new Object[]{track
//                              .getName()}), JOptionPane.WARNING_MESSAGE);
               QMessageBox::warning(this, tr("Trains are servicing track (%1)!").arg(track->getName()), tr("Found %1 rolling stock scheduled for pick up by a train").arg(track->getPickupRS()));
                  return; // can't move rolling stock, some are scheduled for a pick up
              }
              if (track->getDropRS() > 0) {
//                  JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
//                          .getMessage("FoundRollingStockDrop"), new Object[]{track.getDropRS()}),
//                          MessageFormat.format(tr("TrainsServicingTrack"), new Object[]{track
//                              .getName()}), JOptionPane.WARNING_MESSAGE);
               QMessageBox::warning(this, tr("Trains are servicing track (%1)!").arg(track->getName()), tr("Found %1 rolling stock scheduled for set out by a train").arg(track->getPickupRS()));
                  return; // can't move rolling stock, some are scheduled for drops
              }
          }
      }
      // now copy all of the tracks
      Location* newLocation = locationManager->newLocation(locationNameTextField->text());
      location->copyLocation(newLocation);

      // does the user want the cars to also move to the new tracks?
      if (moveRollingStockCheckBox->isChecked()) {
          foreach (Track* track, location->getTrackList()) {
              moveRollingStock(track, newLocation->getTrackByName(track->getName(), NULL));
              if (deleteTrackCheckBox->isChecked()) {
                  location->deleteTrack(track);
              }
          }
      }
  }
  if (source == saveButton) {
      log->debug("save track button activated");
      // save checkbox states
      _moveRollingStock = moveRollingStockCheckBox->isChecked();
      deleteTrack = deleteTrackCheckBox->isChecked();
      // save location file
      OperationsXml::save();
  }
 }

 /*protected*/ void LocationCopyFrame::checkBoxActionPerformed(QWidget* ae) {
 QCheckBox* source = (QCheckBox*)ae;
     if (source == moveRollingStockCheckBox) {
         deleteTrackCheckBox->setEnabled(moveRollingStockCheckBox->isChecked());
         deleteTrackCheckBox->setChecked(false);
     }
 }

 /*protected*/ void LocationCopyFrame::updateComboBoxes() {
     log->debug("update location combobox");
     QVariant item = locationBox->currentData(); // remember which object was selected
     locationManager->updateComboBox(locationBox);
     locationBox->setCurrentIndex(locationBox->findData(item));
 }

 /**
  *
  * @return true if name entered and isn't too long
  */
 /*protected*/ bool LocationCopyFrame::checkName() {
     if (locationNameTextField->text().trimmed()==("")) {
//         JOptionPane.showMessageDialog(this, tr("MustEnterName"), MessageFormat.format(Bundle
//                 .getMessage("CanNotLocation"), new Object[]{tr("Copy")}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 location!").arg(tr("Copy")), tr("Enter a name"));
         return false;
     }
     if (locationNameTextField->text().length() > Control::max_len_string_location_name) {
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("LocationNameLengthMax"),
//                 new Object[]{Integer.toString(Control.max_len_string_location_name + 1)}), MessageFormat.format(Bundle
//                         .getMessage("CanNotLocation"), new Object[]{tr("Copy")}), JOptionPane.ERROR_MESSAGE);
         return false;
         QMessageBox::critical(this, tr("Can not %1 location!").arg(tr("Copy")), tr("Location name must be less than %1 characters").arg(Control::max_len_string_location_name + 1));
     }
     Location* check = locationManager->getLocationByName(locationNameTextField->text());
     if (check != NULL) {
//         JOptionPane.showMessageDialog(this, tr("LocationAlreadyExists"), MessageFormat.format(Bundle
//                 .getMessage("CanNotLocation"), new Object[]{tr("Copy")}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 location!").arg(tr("Copy")), tr("Location with this name already exists"));
         return false;
     }
     return true;
 }

 /*protected*/ void LocationCopyFrame::moveRollingStock(Track* fromTrack, Track* toTrack) {
     moveRollingStock(fromTrack, toTrack, ((CarManager*)InstanceManager::getDefault("CarManager")));
     moveRollingStock(fromTrack, toTrack, ((EngineManager*)InstanceManager::getDefault("EngineManager")));
 }

 /*private*/ void LocationCopyFrame::moveRollingStock(Track* fromTrack, Track* toTrack, RollingStockManager* manager) {
     foreach (RollingStock* rs, *manager->getByIdList()) {
         if (rs->getTrack() == fromTrack) {
             rs->setLocation(toTrack->getLocation(), toTrack, true);
         }
     }
 }

  /*public*/ void LocationCopyFrame::dispose() {
   locationManager->removePropertyChangeListener(this);
   OperationsFrame::dispose();
 }

  /*public*/ void LocationCopyFrame::propertyChange(PropertyChangeEvent* e) {
  log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
          ->getNewValue().toString()));
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateComboBoxes();
     }
 }

 /*public*/ QString LocationCopyFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.tools.LocationCopyFrame";
 }

}
