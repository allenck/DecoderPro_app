#include "trackcopyframe.h"
#include "location.h"
#include <QVBoxLayout>
#include "locationmanager.h"
#include "locationeditframe.h"
#include "jcombobox.h"
#include <QCheckBox>
#include "propertychangeevent.h"
#include "gridbaglayout.h"
#include "jpanel.h"
#include "vptr.h"
#include "instancemanager.h"
#include "borderfactory.h"
#include "joptionpane.h"
#include "operationsxml.h"
#include "track.h"
#include "carmanager.h"
#include "enginemanager.h"

namespace Operations
 {
 /**
  * Frame for copying a track for operations.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2013
  * @version $Revision: 17977 $
  */
 ///*public*/ class TrackCopyFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 6643856888682557276L;


 // remember state of checkboxes during a session
 /*static*/ bool TrackCopyFrame::sameName = false;
 /*static*/ bool TrackCopyFrame::_moveRollingStock = false;
 /*static*/ bool TrackCopyFrame::deleteTrack = false;

 /*public*/ TrackCopyFrame::TrackCopyFrame(LocationEditFrame* lef, QWidget* parent)
     : OperationsFrame(parent)
 {
  // combo boxes
  locationBox = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getComboBox();
  trackBox = new JComboBox();

  if (lef != nullptr) {
      _destination = lef->_location;
  }

     // general GUI config
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // Set up the panels
     // Layout the panel by rows
     // row 1
     JPanel* pName = new JPanel();
     pName->setLayout(new GridBagLayout());
     pName->setBorder(BorderFactory::createTitledBorder(tr("Track Name")));
     addItem(pName, trackNameTextField, 0, 0);

     // row 2
     JPanel* pCopyTo = new JPanel();
     pCopyTo->setLayout(new GridBagLayout());
     pCopyTo->setBorder(BorderFactory::createTitledBorder(tr("Select track to copy")));
     addItem(pCopyTo, locationBox, 0, 0);
     addItem(pCopyTo, trackBox, 1, 0);

     // row 3
     JPanel* pOptions = new JPanel();
     pOptions->setLayout(new GridBagLayout());
     pOptions->setBorder(BorderFactory::createTitledBorder(tr("Options")));
     addItemLeft(pOptions, sameNameCheckBox, 0, 0);
     addItemLeft(pOptions, moveRollingStockCheckBox, 0, 1);
     addItemLeft(pOptions, deleteTrackCheckBox, 0, 2);

     // row 4
     JPanel* pButton = new JPanel();
     pButton->setLayout(new GridBagLayout());
     addItem(pButton, copyButton, 0, 0);
     addItem(pButton, saveButton, 1, 0);

     thisLayout->addWidget(pName);
     thisLayout->addWidget(pCopyTo);
     thisLayout->addWidget(pOptions);
     thisLayout->addWidget(pButton);

     addComboBoxAction(locationBox);
     addComboBoxAction(trackBox);

     // set the checkbox states
     sameNameCheckBox->setChecked(sameName);
     moveRollingStockCheckBox->setChecked(_moveRollingStock);
     deleteTrackCheckBox->setChecked(deleteTrack);
     deleteTrackCheckBox->setEnabled(moveRollingStockCheckBox->isChecked());

     // get notified if combo box gets modified
     //((LocationManager*)InstanceManager::getDefault("Operations::LocationManager")).addPropertyChangeListener(this);
     connect(((LocationManager*)InstanceManager::getDefault("Operations::LocationManager")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_Locations", true); // NOI18N

     adjustSize();
     setMinimumSize(QSize(Control::panelWidth400, Control::panelHeight400));

     if (_destination != nullptr) {
         setTitle(tr("Copy Track").arg(_destination->getName()));
         pCopyTo->setVisible(false);
         _destination->addPropertyChangeListener(this);
     } else {
         setTitle(tr("Copy Track"));
         copyButton->setEnabled(false);
     }
     // setup buttons
     addButtonAction(copyButton);
     addButtonAction(saveButton);

     addCheckBoxAction(sameNameCheckBox);
     addCheckBoxAction(moveRollingStockCheckBox);
 }

 // location combo box
 /*protected*/ void TrackCopyFrame::comboBoxActionPerformed(QWidget* ae) {
 JComboBox* source = (JComboBox*)ae;
     if (source == locationBox) {
         updateTrackComboBox();
     }
     if (source == trackBox) {
         updateTrackName();
     }
 }

 /*protected*/ void TrackCopyFrame::updateTrackComboBox() {
     log->debug("update track combobox");
     if (locationBox->currentText() == NULL) {
         trackBox->clear();
     } else {
         log->debug(tr("Copy Track Frame sees location: %1").arg(locationBox->currentText()));
         Location* l = (Location*) VPtr<Location>::asPtr(locationBox->currentData());
         l->updateComboBox(trackBox);
     }
 }

 /*protected*/ void TrackCopyFrame::updateTrackName() {
     if (sameNameCheckBox->isChecked() && trackBox->currentText() != NULL) {
         trackNameTextField->setText(trackBox->currentText());
     }
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*protected*/ void TrackCopyFrame::buttonActionPerformed(QWidget* ae) {
     if (ae == copyButton) {
         log->debug("copy track button activated");
         if (!checkName()) {
             return;
         }
         if (trackBox->getSelectedItem() == "" || trackBox->getSelectedItem()==(Location::NONE) || _destination == nullptr) {
             // tell user that they need to select a track to copy
             JOptionPane::showMessageDialog(this, tr("You must select the location and track you wish to copy"),
                     tr("Select Track to Copy"), JOptionPane::INFORMATION_MESSAGE);
             return;
         }
         Track* fromTrack = VPtr<Track>::asPtr(trackBox->currentData());
         if (moveRollingStockCheckBox->isSelected() && fromTrack->getPickupRS() > 0) {
             JOptionPane::showMessageDialog(this, tr("Found %1 rolling stock scheduled for pick up by a train").arg(fromTrack->getPickupRS()),
                                            tr("Trains are servicing track (%1)!").arg(fromTrack->getName()),
                     JOptionPane::WARNING_MESSAGE);
             return; // failed
         }
         if (moveRollingStockCheckBox->isSelected() && fromTrack->getDropRS() > 0) {
             JOptionPane::showMessageDialog(this, tr("Found %1 rolling stock scheduled for set out by a train").arg(
                     fromTrack->getDropRS()), tr("Trains are servicing track (%1)!").arg(fromTrack->getName()),
                     JOptionPane::WARNING_MESSAGE);
             return; // failed
         }
         // only copy tracks that are okay with the location
         if (fromTrack->getTrackType()==(Track::STAGING) ^ _destination->isStaging()) {
             JOptionPane::showMessageDialog(this, tr("Track type (%1) is not allowed at location (%2)").arg(
                     fromTrack->getTrackType(), _destination->getName()), tr("Can not Copy Track (%1)").arg(fromTrack->getName()),
                                            JOptionPane::ERROR_MESSAGE);
             return;
         }
         Track* toTrack = fromTrack->copyTrack(trackNameTextField->text(), _destination);
         if (moveRollingStockCheckBox->isSelected()) {
             // move rolling stock
             moveRollingStock(fromTrack, toTrack);
             if (deleteTrackCheckBox->isSelected()) {
                 fromTrack->getLocation()->deleteTrack(fromTrack);
             }
         }
     }
     if (ae == saveButton) {
         log->debug("save track button activated");
         // save checkbox states
         sameName = sameNameCheckBox->isSelected();
         _moveRollingStock = moveRollingStockCheckBox->isSelected();
         deleteTrack = deleteTrackCheckBox->isSelected();
         // save location file
         OperationsXml::save();
     }
 }

 /*protected*/ void TrackCopyFrame::checkBoxActionPerformed(QWidget* ae) {
     if (ae == sameNameCheckBox) {
         updateTrackName();
     }
     if (ae == moveRollingStockCheckBox) {
         deleteTrackCheckBox->setEnabled(moveRollingStockCheckBox->isSelected());
         deleteTrackCheckBox->setSelected(false);
     }
 }

 /*protected*/ void TrackCopyFrame::updateComboBoxes() {
     log->debug("update location combobox");
     ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->updateComboBox(locationBox);
 }

 /**
  *
  * @return true if name entered and isn't too long
  */
 /*protected*/ bool TrackCopyFrame::checkName() {
     if (trackNameTextField->text().trimmed()==("")) {
         JOptionPane::showMessageDialog(this, tr("Enter a name"), tr("Can not %1 Track!").arg(tr("Copy")), JOptionPane::ERROR_MESSAGE);
         return false;
     }
     if (trackNameTextField->text().length() > Control::max_len_string_track_name) {
         JOptionPane::showMessageDialog(this,tr("Track name must be less than %1 characters").arg(Control::max_len_string_track_name + 1),
           tr("Can not %1 Track!").arg(tr("Copy")), JOptionPane::ERROR_MESSAGE);
         return false;
     }
     // check to see if track already exists
     if (_destination == nullptr) {
         return false;
     }
     Track* check = _destination->getTrackByName(trackNameTextField->text(), nullptr);
     if (check != nullptr) {
         JOptionPane::showMessageDialog(this, tr("Track with this name already exists"),
                                        tr("Can not %1 Track!").arg( tr("Copy")), JOptionPane::ERROR_MESSAGE);
         return false;
     }
     return true;
 }

 /*protected*/ void TrackCopyFrame::moveRollingStock(Track* fromTrack, Track* toTrack) {
     moveRollingStock(fromTrack, toTrack, (CarManager*)InstanceManager::getDefault("Operations::CarManager"));
     moveRollingStock(fromTrack, toTrack, (EngineManager*)InstanceManager::getDefault("Operations::EngineManager"));
 }

 /*private*/ void TrackCopyFrame::moveRollingStock(Track* fromTrack, Track* toTrack, RollingStockManager* manager) {
     for (RollingStock* rs : *manager->getByIdList()) {
         if (rs->getTrack() == fromTrack) {
             rs->setLocation(toTrack->getLocation(), toTrack, true);
         }
     }
 }

 /*public*/ void TrackCopyFrame::dispose() {
     //((LocationManager*)InstanceManager::getDefault("Operations::LocationManager")).removePropertyChangeListener(this);
 disconnect(((LocationManager*)InstanceManager::getDefault("Operations::LocationManager")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (_location != NULL) {
      _location->removePropertyChangeListener(this);
     }
     OperationsFrame::dispose();
 }

 /*public*/ void TrackCopyFrame::propertyChange(PropertyChangeEvent* e) {
     log->debug(tr("PropertyChange (%1) new (%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateComboBoxes();
     }
     if (e->getPropertyName()==(Location::DISPOSE_CHANGED_PROPERTY)) {
         dispose();
     }
 }

 /*public*/ QString TrackCopyFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.tools.TrackCopyFrame";
 }

}
