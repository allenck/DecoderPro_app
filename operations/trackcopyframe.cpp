#include "trackcopyframe.h"
#include "location.h"
#include <QVBoxLayout>
#include "locationmanager.h"
#include "locationeditframe.h"
#include "jtextfield.h"
#include "jbutton.h"
#include "jcombobox.h"
#include "control.h"
#include <QCheckBox>
#include "propertychangeevent.h"
#include "gridbaglayout.h"
#include "jpanel.h"
#include "vptr.h"
#include "instancemanager.h"
#include "borderfactory.h"

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
 /*static*/ bool TrackCopyFrame::moveRollingStock = false;
 /*static*/ bool TrackCopyFrame::deleteTrack = false;

 /*public*/ TrackCopyFrame::TrackCopyFrame(LocationEditFrame* lef)
     : OperationsFrame(lef)
 {
 log = new Logger("TrackCopyFrame");
  // text field
  trackNameTextField = new JTextField(Control::max_len_string_track_name);

  // major buttons
  copyButton = new JButton(tr("Copy"));
  saveButton = new JButton(tr("Save"));

  // combo boxes
  locationBox = ((LocationManager*)InstanceManager::getDefault("LocationManager"))->getComboBox();
  trackBox = new JComboBox();

  // checkboxes
  sameNameCheckBox = new QCheckBox(tr("SameName"));
  moveRollingStockCheckBox = new QCheckBox(tr("Move Rolling Stock to New Track"));
  deleteTrackCheckBox = new QCheckBox(tr("Delete Copied Track"));



     _location = lef->_location;

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
     JPanel* pCopy = new JPanel();
     pCopy->setLayout(new GridBagLayout());
     pCopy->setBorder(BorderFactory::createTitledBorder(tr("Select track to copy")));
     addItem(pCopy, locationBox, 0, 0);
     addItem(pCopy, trackBox, 1, 0);

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
     thisLayout->addWidget(pCopy);
     thisLayout->addWidget(pOptions);
     thisLayout->addWidget(pButton);

     addComboBoxAction(locationBox);
     addComboBoxAction(trackBox);

     // set the checkbox states
     sameNameCheckBox->setChecked(sameName);
     moveRollingStockCheckBox->setChecked(moveRollingStock);
     deleteTrackCheckBox->setChecked(deleteTrack);
     deleteTrackCheckBox->setEnabled(moveRollingStockCheckBox->isChecked());

     // get notified if combo box gets modified
     //((LocationManager*)InstanceManager::getDefault("LocationManager")).addPropertyChangeListener(this);
     connect(((LocationManager*)InstanceManager::getDefault("LocationManager")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_Locations", true); // NOI18N

     adjustSize();
     setMinimumSize(QSize(Control::panelWidth400, Control::panelHeight400));

     if (_location != NULL) {
         setTitle(tr("Copy Track to (%1)").arg(_location->getName()));
         _location->PropertyChangeSupport::addPropertyChangeListener(this);
     } else {
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
#if 0
 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*protected*/ void buttonActionPerformed(ActionEvent* ae) {
     if (source == copyButton) {
         log->debug("copy track button activated");
         if (!checkName()) {
             return;
         }
         if (trackBox.getSelectedItem() == null || trackBox.getSelectedItem()==(Location.NONE) || _location == null) {
             // tell user that they need to select a track to copy
             JOptionPane.showMessageDialog(this, tr("SelectLocationAndTrack"), Bundle
                     .getMessage("SelectTrackToCopy"), JOptionPane.INFORMATION_MESSAGE);
             return;
         }
         Track* fromTrack = (Track) trackBox.getSelectedItem();
         if (moveRollingStockCheckBox.isSelected() && fromTrack.getPickupRS() > 0) {
             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("FoundRollingStockPickUp"),
                     new Object[]{fromTrack.getPickupRS()}), MessageFormat.format(Bundle
                             .getMessage("TrainsServicingTrack"), new Object[]{fromTrack.getName()}),
                     JOptionPane.WARNING_MESSAGE);
             return; // failed
         }
         if (moveRollingStockCheckBox.isSelected() && fromTrack.getDropRS() > 0) {
             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("FoundRollingStockDrop"),
                     new Object[]{fromTrack.getDropRS()}), MessageFormat.format(Bundle
                             .getMessage("TrainsServicingTrack"), new Object[]{fromTrack.getName()}),
                     JOptionPane.WARNING_MESSAGE);
             return; // failed
         }
         // only copy tracks that are okay with the location
         if (fromTrack.getTrackType()==(Track.STAGING) ^ _location.isStaging()) {
             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackTypeWrong"),
                     new Object[]{fromTrack.getTrackType(), _location.getName()}), MessageFormat.format(Bundle
                             .getMessage("CanNotCopy"), new Object[]{fromTrack.getName()}), JOptionPane.ERROR_MESSAGE);
             return;
         }
         Track toTrack = fromTrack.copyTrack(trackNameTextField.getText(), _location);
         if (moveRollingStockCheckBox.isSelected()) {
             // move rolling stock
             moveRollingStock(fromTrack, toTrack);
             if (deleteTrackCheckBox.isSelected()) {
                 fromTrack.getLocation().deleteTrack(fromTrack);
             }
         }
     }
     if (source == saveButton) {
         log->debug("save track button activated");
         // save checkbox states
         sameName = sameNameCheckBox.isSelected();
         moveRollingStock = moveRollingStockCheckBox.isSelected();
         deleteTrack = deleteTrackCheckBox.isSelected();
         // save location file
         OperationsXml.save();
     }
 }

 /*protected*/ void checkBoxActionPerformed(java.awt.event.ActionEvent ae) {
     if (source == sameNameCheckBox) {
         updateTrackName();
     }
     if (source == moveRollingStockCheckBox) {
         deleteTrackCheckBox.setEnabled(moveRollingStockCheckBox.isSelected());
         deleteTrackCheckBox.setSelected(false);
     }
 }
#endif
 /*protected*/ void TrackCopyFrame::updateComboBoxes() {
     log->debug("update location combobox");
     ((LocationManager*)InstanceManager::getDefault("LocationManager"))->updateComboBox(locationBox);
 }
#if 0
 /**
  *
  * @return true if name entered and isn't too long
  */
 /*protected*/ bool checkName() {
     if (trackNameTextField.getText().trim()==("")) {
         JOptionPane.showMessageDialog(this, tr("MustEnterName"), MessageFormat.format(Bundle
                 .getMessage("CanNotTrack"), new Object[]{tr("Copy")}), JOptionPane.ERROR_MESSAGE);
         return false;
     }
     if (trackNameTextField.getText().length() > Control.max_len_string_track_name) {
         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackNameLengthMax"),
                 new Object[]{Integer.toString(Control.max_len_string_track_name + 1)}), MessageFormat.format(Bundle
                         .getMessage("CanNotTrack"), new Object[]{tr("Copy")}), JOptionPane.ERROR_MESSAGE);
         return false;
     }
     // check to see if track already exists
     if (_location == null) {
         return false;
     }
     Track check = _location.getTrackByName(trackNameTextField.getText(), null);
     if (check != null) {
         JOptionPane.showMessageDialog(this, tr("TrackAlreadyExists"), MessageFormat.format(Bundle
                 .getMessage("CanNotTrack"), new Object[]{tr("Copy")}), JOptionPane.ERROR_MESSAGE);
         return false;
     }
     return true;
 }

 /*protected*/ void moveRollingStock(Track fromTrack, Track toTrack) {
     moveRollingStock(fromTrack, toTrack, CarManager.instance());
     moveRollingStock(fromTrack, toTrack, EngineManager.instance());
 }

 private void moveRollingStock(Track fromTrack, Track toTrack, RollingStockManager manager) {
     for (RollingStock rs : manager.getByIdList()) {
         if (rs.getTrack() == fromTrack) {
             rs.setLocation(toTrack.getLocation(), toTrack, true);
         }
     }
 }
#endif
 /*public*/ void TrackCopyFrame::dispose() {
     //((LocationManager*)InstanceManager::getDefault("LocationManager")).removePropertyChangeListener(this);
 disconnect(((LocationManager*)InstanceManager::getDefault("LocationManager")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
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
