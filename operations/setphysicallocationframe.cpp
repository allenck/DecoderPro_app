#include "setphysicallocationframe.h"
#include "loggerfactory.h"
#include "borderfactory.h"
#include "physicallocationpanel.h"
#include "gridbaglayout.h"
#include "control.h"
#include "vptr.h"
#include "joptionpane.h"
#include "operationsxml.h"
#include "setup.h"

namespace Operations {

 /**
  * Frame for setting train physical location coordinates for a location.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010
  * @author Mark Underwood Copyright (C) 2011
  */
// /*public*/  class SetPhysicalLocationFrame extends OperationsFrame {


     /*public*/  SetPhysicalLocationFrame::SetPhysicalLocationFrame(Location* l, QWidget* parent) : OperationsFrame(tr("Set PhysicalLocation"), parent) {
         //super(Bundle.getMessage("MenuSetPhysicalLocation"));

         // Store the location (null if called from the list view)
         _location = l;

         // general GUI config
         getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));

         // set tool tips
         saveButton->setToolTip(tr("Saves the physical location coordinates for the selected location"));
         closeButton->setToolTip(tr("Close this window"));

         // Set up the panels
         JPanel* pLocation = new JPanel(new FlowLayout);
         pLocation->setBorder(BorderFactory::createTitledBorder(tr("Location")));
         pLocation->layout()->addWidget(locationBox);

         physicalLocation = new PhysicalLocationPanel(tr("PhysicalLocation"));
         physicalLocation->setToolTip(tr("Use this to set the physical position on your layout of this location.  (0,0,0) is the operator's position. Units are arbitrary."));
         physicalLocation->setVisible(true);

         JPanel* pControl = new JPanel();
         pControl->setLayout(new GridBagLayout());
         pControl->setBorder(BorderFactory::createTitledBorder(""));
         addItem(pControl, saveButton, 1, 0);
         addItem(pControl, closeButton, 2, 0);

         getContentPane()->layout()->addWidget(pLocation);
         getContentPane()->layout()->addWidget(physicalLocation);
         getContentPane()->layout()->addWidget(pControl);

         // add help menu to window
         addHelpMenu("package.jmri.jmrit.operations.Operations_SetTrainIconCoordinates", true); // fix this // NOI18N
         // later

         // setup buttons
//         saveButton.addActionListener(new java.awt.event.ActionListener() {
//             @Override
//             /*public*/  void actionPerformed(java.awt.event.ActionEvent e) {
         connect(saveButton, &JButton::clicked, [=]{
                 saveButtonActionPerformed(saveButton);
//             }
         });
//         closeButton.addActionListener(new java.awt.event.ActionListener() {
//             @Override
//             /*public*/  void actionPerformed(java.awt.event.ActionEvent e) {
         connect(closeButton, &JButton::clicked, [=](){
                 closeButtonActionPerformed(closeButton);
//             }
         });

         // setup combo box
         addComboBoxAction(locationBox);

         if (_location != nullptr) {
             locationBox->setSelectedItem(_location->getName());
         }

         initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight250));
     }

     /**
      * Close button action
      *
      * @param ae The ActionEvent.
      */
     /*public*/  void SetPhysicalLocationFrame::closeButtonActionPerformed(QWidget* /*ae*/) {
         dispose();
     }

     /**
      * Save button action {@literal ->} save this Reporter's location
      *
      * @param ae The ActionEvent.
      */
     /*public*/  void SetPhysicalLocationFrame::saveButtonActionPerformed(QWidget* ae) {
         // check to see if a location has been selected
         if (locationBox->getSelectedItem() == nullptr) {
             JOptionPane::showMessageDialog(this, tr("Select a location to edit"),
                     tr("No Location Selected!"), JOptionPane::ERROR_MESSAGE);
             return;
         }
         Location* l = VPtr<Location>::asPtr(locationBox->currentData());
         if (l == nullptr) {
             return;
         }
         if (ae/*.getSource()*/ == saveButton) {
             int value = JOptionPane::showConfirmDialog(this,
                     tr("Update physical location coordinates for location \"%1\"? ").arg(l->getName()),
                     tr("Update the defaults for this location?"), JOptionPane::YES_NO_OPTION);
             if (value == JOptionPane::YES_OPTION) {
                 saveSpinnerValues(l);
             }
             OperationsXml::save();
             if (Setup::isCloseWindowOnSaveEnabled()) {
                 dispose();
             }
         }
     }

     //@Override
     /*public*/  void SetPhysicalLocationFrame::comboBoxActionPerformed(QWidget* /*ae*/) {
         if (locationBox->getSelectedItem() == "") {
             resetSpinners();
         } else {
             Location* l = VPtr<Location>::asPtr(locationBox->currentData());
             loadSpinners(l);
         }
     }

     //@Override
     /*public*/  void SetPhysicalLocationFrame::spinnerChangeEvent(QWidget* ae) {
         if (ae/*.getSource()*/ == physicalLocation) {
             Location* l = VPtr<Location>::asPtr(locationBox->currentData());
             if (l != nullptr) {
                 l->setPhysicalLocation(physicalLocation->getValue());
             }
         }
     }

     /*private*/ void SetPhysicalLocationFrame::resetSpinners() {
         // Reset spinners to zero.
         physicalLocation->setValue(new PhysicalLocation());
     }

     /*private*/ void SetPhysicalLocationFrame::loadSpinners(Location* l) {
         log->debug(tr("Load spinners location %1").arg(l->getName()));
         physicalLocation->setValue(l->getPhysicalLocation());
     }

     /*
      * private void spinnersEnable(boolean enable){
      * physicalLocation.setEnabled(enable); }
      */
     /*private*/ void SetPhysicalLocationFrame::saveSpinnerValues(Location* l) {
         log->debug(tr("Save physical coordinates for location %1").arg(l->getName()));
         l->setPhysicalLocation(physicalLocation->getValue());
     }

     //@Override
     /*public*/  void SetPhysicalLocationFrame::dispose() {
         OperationsFrame::dispose();
     }

     /*private*/ /*final*/ /*static*/ Logger* SetPhysicalLocationFrame::log = LoggerFactory::getLogger("SetPhysicalLocationFrame");

} // namespace Operations
