#include "trainswitchlisteditframe.h"
#include "jbutton.h"
#include "operationsxml.h"
#include <control.h>
#include "setup.h"
#include <QBoxLayout>
#include <gridbaglayout.h>
#include "jpanel.h"
#include <QCheckBox>
#include "jcombobox.h"
#include "locationmanager.h"
#include <QScrollArea>
#include "flowlayout.h"
#include <QMenu>
#include <QMenuBar>
#include "location.h"
#include "train.h"
#include "trainmanager.h"
#include "trainprintutilities.h"
#include "trainswitchlists.h"
#include "htmltextedit.h"
#include <QLabel>
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Frame for user selection of switch lists
 *
 * @author Dan Boudreau Copyright (C) 2008, 2012, 2013, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class TrainSwitchListEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 3796539428562528626L;


 /*public*/ TrainSwitchListEditFrame::TrainSwitchListEditFrame(QWidget* parent)
    : OperationsFrame(tr("SwitchLists"), parent)
 {
  //super(tr("TitleSwitchLists"));
  setFrameRef(getClassName());
  locationManager = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"));
  locationCheckBoxes = QList<QCheckBox*>();
  locationComboBoxes = QList<JComboBox*>();
  locationPanelCheckBoxes = new JPanel();

  // checkboxes
  switchListRealTimeCheckBox = new QCheckBox(tr("Real Time"));
  switchListAllTrainsCheckBox = new QCheckBox(tr("All Trains"));

     // major buttons
  clearButton = new JButton(tr("Clear"));
  setButton = new JButton(tr("Select"));
  printButton = new JButton(tr("Print Switch Lists"));
  previewButton = new JButton(tr("Preview Switch Lists"));
  changeButton = new JButton(tr("Print Changes"));
  runButton = new JButton(tr("Run"));
  runChangeButton = new JButton(tr("Run Changes"));
  csvGenerateButton = new JButton(tr("Generate CSV Switch Lists"));
  csvChangeButton = new JButton(tr("Generate CSV Switch Lists Changes"));
  updateButton = new JButton(tr("Update"));
  resetButton = new JButton(tr("Reset Switch Lists"));
  saveButton = new JButton(tr("Save"));

  switchListPageComboBox = Setup::getSwitchListPageFormatComboBox();

  locationCheckBoxMapper = new QSignalMapper();
  connect(locationCheckBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(locationCheckBoxActionPerformed(QWidget*)));
 }

 /*public*/ void TrainSwitchListEditFrame::initComponents() {
     // listen for any changes in the number of locations
     //locationManager.addPropertyChangeListener(this);
connect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     // the following code sets the frame's initial state
     //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // tool tips
     switchListRealTimeCheckBox->setToolTip(tr("When selected, switch lists show only built trains"));
     switchListAllTrainsCheckBox->setToolTip(tr("When selected, the switch lists show all trains visiting a location, even if there isn't any work for that train"));
     switchListPageComboBox->setToolTip(tr("Adjust the number of pages printed per train or per visit"));
     csvChangeButton->setToolTip(tr("Generates a switch list csv file for locations selected and with changes"));
     changeButton->setToolTip(tr("Print switch lists for locations selected and with changes"));
     resetButton->setToolTip(tr("Removes terminated and reset trains from switch lists"));

     JPanel* switchPaneFrame = new JPanel;
     switchPaneFrame->setLayout(new QVBoxLayout);
     switchPane = new QScrollArea(/*locationPanelCheckBoxes*/);
     switchPaneFrame->layout()->addWidget(switchPane);
     //switchPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
     switchPaneFrame->setBorder(BorderFactory::createTitledBorder(""));

     // Layout the panel by rows
     locationPanelCheckBoxes->setLayout(new GridBagLayout());
     updateLocationCheckboxes();
     enableChangeButtons();

     // Clear and set buttons
     JPanel* pButtons = new JPanel();
     pButtons->setLayout(new GridBagLayout());
     pButtons->setBorder(BorderFactory::createTitledBorder(""));
     addItem(pButtons, clearButton, 0, 1);
     addItem(pButtons, setButton, 1, 1);

     // options
     JPanel* pSwitchListOptions = new JPanel();
     pSwitchListOptions->setLayout(new GridBagLayout());
     pSwitchListOptions->setBorder(BorderFactory::createTitledBorder(tr("Switch List Options")));

     JPanel* pSwitchListPageFormat = new JPanel();
     pSwitchListPageFormat->setLayout(new FlowLayout);
     pSwitchListPageFormat->setBorder(BorderFactory::createTitledBorder(tr("Switch List Page Format")));
     pSwitchListPageFormat->layout()->addWidget(switchListPageComboBox);

     addItem(pSwitchListOptions, switchListAllTrainsCheckBox, 1, 0);
     addItem(pSwitchListOptions, pSwitchListPageFormat, 2, 0);
     addItem(pSwitchListOptions, switchListRealTimeCheckBox, 3, 0);
     addItem(pSwitchListOptions, saveButton, 4, 0);

     // buttons
     JPanel* controlPanel = new JPanel();
     controlPanel->setLayout(new GridBagLayout());
     controlPanel->setBorder(BorderFactory::createTitledBorder(""));

     // row 3
     addItem(controlPanel, previewButton, 0, 2);
     addItem(controlPanel, printButton, 1, 2);
     addItem(controlPanel, changeButton, 2, 2);
     // row 4
     addItem(controlPanel, updateButton, 0, 3);
     addItem(controlPanel, resetButton, 1, 3);

     // row 5
     customPanel = new JPanel();
     customPanel->setLayout(new GridBagLayout());
     customPanel->setBorder(BorderFactory::createTitledBorder(tr("Custom Switch Lists")));

     addItem(customPanel, csvGenerateButton, 1, 4);
     addItem(customPanel, csvChangeButton, 2, 4);
     addItem(customPanel, runButton, 1, 5);
     addItem(customPanel, runChangeButton, 2, 5);

     switchPane->setWidget(locationPanelCheckBoxes);
     thisLayout->addWidget(switchPaneFrame);
     thisLayout->addWidget(pButtons);
     thisLayout->addWidget(pSwitchListOptions);
     thisLayout->addWidget(controlPanel);
     thisLayout->addWidget(customPanel);

     customPanel->setVisible(Setup::isGenerateCsvSwitchListEnabled());

     // Set the state
     switchListRealTimeCheckBox->setChecked(Setup::isSwitchListRealTime());
     switchListAllTrainsCheckBox->setChecked(Setup::isSwitchListAllTrainsEnabled());
     switchListPageComboBox->setCurrentIndex(switchListPageComboBox->findText(Setup::getSwitchListPageFormat()));

     updateButton->setVisible(!switchListRealTimeCheckBox->isChecked());
     resetButton->setVisible(!switchListRealTimeCheckBox->isChecked());
     saveButton->setEnabled(false);

     addButtonAction(clearButton);
     addButtonAction(setButton);
     addButtonAction(printButton);
     addButtonAction(previewButton);
     addButtonAction(changeButton);
     addButtonAction(runButton);
     addButtonAction(runChangeButton);
     addButtonAction(csvGenerateButton);
     addButtonAction(csvChangeButton);
     addButtonAction(updateButton);
     addButtonAction(resetButton);
     addButtonAction(saveButton);

     addCheckBoxAction(switchListRealTimeCheckBox);
     addCheckBoxAction(switchListAllTrainsCheckBox);

     addComboBoxAction(switchListPageComboBox);

//     Setup::addPropertyChangeListener(this);  // can't do on a static class; needs work

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
//     toolMenu.add(new SetupExcelProgramSwitchListFrameAction(tr("MenuItemSetupExcelProgramSwitchList")));
     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_SwitchList", true); // NOI18N
     // set frame size and train for display
     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
 }

 // Buttons
 /*public*/ void TrainSwitchListEditFrame::buttonActionPerformed(QWidget* ae)
 {
  JButton* source = (JButton*)ae;
     if (source == clearButton) {
         selectCheckboxes(false);
     }
     if (source == setButton) {
         selectCheckboxes(true);
     }
     if (source == previewButton) {
         buildSwitchList(true, false, false, false);
     }
     if (source == printButton) {
         buildSwitchList(false, false, false, false);
     }
     if (source == changeButton) {
         buildSwitchList(false, true, false, false);
     }
     if (source == csvGenerateButton) {
         buildSwitchList(false, false, true, false);
     }
     if (source == csvChangeButton) {
         buildSwitchList(false, true, true, false);
     }
     if (source == updateButton) {
         buildSwitchList(true, false, false, true);
     }
     if (source == runButton) {
         runCustomSwitchLists(false);
     }
     if (source == runChangeButton) {
         runCustomSwitchLists(true);
     }
     if (source == resetButton) {
         reset();
     }
     if (source == saveButton) {
         save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 /*public*/ void TrainSwitchListEditFrame::checkBoxActionPerformed(QWidget* ae) {
 QCheckBox* source = (QCheckBox*)ae;
     if (source == switchListRealTimeCheckBox) {
         updateButton->setVisible(!switchListRealTimeCheckBox->isChecked());
         resetButton->setVisible(!switchListRealTimeCheckBox->isChecked());
     }
     // enable the save button whenever a checkbox is changed
     enableSaveButton(true);
 }

 // Remove all terminated or reset trains from the switch lists for selected locations
 /*private*/ void TrainSwitchListEditFrame::reset() {
     for (int i = 0; i < locationCheckBoxes.size(); i++) {
         QString locationName = locationCheckBoxes.at(i)->objectName();
         Location* location = locationManager->getLocationByName(locationName);
         if (location->isSwitchListEnabled()) {
             // new switch lists will now be created for the location
             location->setSwitchListState(Location::SW_CREATE);
             location->setStatus(Location::MODIFIED);
         }
     }
     // set trains switch lists unknown, any built trains should remain on the switch lists
     ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->setTrainsSwitchListStatus(Train::UNKNOWN);
 }

 // save printer selection
 /*private*/ void TrainSwitchListEditFrame::save() {
     for (int i = 0; i < locationCheckBoxes.size(); i++) {
         QString locationName = locationCheckBoxes.at(i)->objectName();
         Location* location = locationManager->getLocationByName(locationName);
         JComboBox* comboBox = locationComboBoxes.at(i);
         QString printerName =  comboBox->currentText();
         if (printerName==(TrainPrintUtilities::getDefaultPrinterName())) {
             location->setDefaultPrinterName(Location::NONE);
         } else {
             log->debug("Location " + location->getName() + " has selected printer " + printerName);
             location->setDefaultPrinterName(printerName);
         }
     }
     Setup::setSwitchListRealTime(switchListRealTimeCheckBox->isChecked());
     Setup::setSwitchListAllTrainsEnabled(switchListAllTrainsCheckBox->isChecked());
     Setup::setSwitchListPageFormat( switchListPageComboBox->currentText());
     // save location file
     OperationsXml::save();
     enableSaveButton(false);
     if (Setup::isCloseWindowOnSaveEnabled()) {
         dispose();
     }
 }

 /**
  * Print = all false;
  *
  * @param isPreview true if print preview
  * @param isChanged true if print changes was requested
  * @param isCsv     true if building a CSV switch list files
  * @param isUpdate  true if only updating switch lists
  */
 /*private*/ void TrainSwitchListEditFrame::buildSwitchList(bool isPreview, bool isChanged, bool isCsv, bool isUpdate) {
     TrainSwitchLists* trainSwitchLists = new TrainSwitchLists();
     for (int i = 0; i < locationCheckBoxes.size(); i++) {
         QString locationName = locationCheckBoxes.at(i)->objectName();
         Location* location = locationManager->getLocationByName(locationName);
         if (location->isSwitchListEnabled()) {
             if (!isCsv) {
                 trainSwitchLists->buildSwitchList(location);
                 // print or print changes
                 if (!isUpdate && !isChanged
                         || (!isUpdate && isChanged && location->getStatus()!=(Location::PRINTED))) {
                     trainSwitchLists->printSwitchList(location, isPreview);
                 }
             }
#if 0
             else if (Setup::isGenerateCsvSwitchListEnabled()) {
                 TrainCsvSwitchLists trainCsvSwitchLists = new TrainCsvSwitchLists();
                 trainCsvSwitchLists.buildSwitchList(location);
             }
#endif
         }
     }
     // set trains switch lists printed
     ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->setTrainsSwitchListStatus(Train::PRINTED);
 }

 /*private*/ void TrainSwitchListEditFrame::selectCheckboxes(bool enable) {
     for (int i = 0; i < locationCheckBoxes.size(); i++) {
         QString locationName = locationCheckBoxes.at(i)->objectName();
         Location* l = locationManager->getLocationByName(locationName);
         l->setSwitchListEnabled(enable);
     }
     // enable the save button whenever a checkbox is changed
     saveButton->setEnabled(true);
 }

 // name change or number of locations has changed
 /*private*/ void TrainSwitchListEditFrame::updateLocationCheckboxes() {
    QList<Location*> locations = locationManager->getLocationsByNameList();
     /*synchronized (this)*/ {
         foreach (Location* location, locations) {
          location->removePropertyChangeListener(this);
         }
     }

     locationCheckBoxes.clear();
     locationComboBoxes.clear(); // remove printer selection
     //locationPanelCheckBoxes.removeAll();
     QLayoutItem* item;
     while ( ( item = locationPanelCheckBoxes->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     // create header
     addItem(locationPanelCheckBoxes, new QLabel(tr("Location")), 0, 0);
     addItem(locationPanelCheckBoxes, new QLabel("        "), 1, 0);
     addItem(locationPanelCheckBoxes, new QLabel(tr("Status")), 2, 0);
     addItem(locationPanelCheckBoxes, new QLabel("        "), 3, 0);
     addItem(locationPanelCheckBoxes, new QLabel(tr("Comment")), 4, 0);
     addItem(locationPanelCheckBoxes, new QLabel("        "), 5, 0);
     addItem(locationPanelCheckBoxes, new QLabel(tr("Printer")), 6, 0);

     int y = 1; // vertical position in panel

     Location* mainLocation = NULL; // user can have multiple locations with the "same" name.

     foreach (Location* location, locations) {
         QString name = TrainCommon::splitString(location->getName());
         if (mainLocation != NULL && TrainCommon::splitString(mainLocation->getName())==(name)) {
             location->setSwitchListEnabled(mainLocation->isSwitchListEnabled());
             if (mainLocation->isSwitchListEnabled() && location->getStatus()==(Location::MODIFIED)) {
                 mainLocation->setStatusModified(); // we need to update the primary location
                 location->setStatus(Location::UPDATED); // and clear the secondaries
             }
             continue;
         }
         mainLocation = location;

         QCheckBox* checkBox = new QCheckBox();
         locationCheckBoxes.append(checkBox);
         checkBox->setChecked(location->isSwitchListEnabled());
         checkBox->setText(name);
         checkBox->setObjectName(location->getName());
         addLocationCheckBoxAction(checkBox);
         addItemLeft(locationPanelCheckBoxes, checkBox, 0, y);

         QLabel* status = new QLabel(location->getStatus());
         addItem(locationPanelCheckBoxes, status, 2, y);

         JButton* button = new JButton(tr("Add"));
         if (location->getSwitchListComment()!=(Location::NONE)) {
             button->setText(tr("Edit"));
         }
         button->setObjectName(location->getName());
         addCommentButtonAction(button);
         addItem(locationPanelCheckBoxes, button, 4, y);

         JComboBox* comboBox = TrainPrintUtilities::getPrinterJComboBox();
         locationComboBoxes.append(comboBox);
         comboBox->setCurrentIndex(comboBox->findText(location->getDefaultPrinterName()));
         addComboBoxAction(comboBox);
         addItem(locationPanelCheckBoxes, comboBox, 6, y++);

     }

     // restore listeners
     /*synchronized (this)*/ {
         foreach (Location* location, locations) {
          location->SwingPropertyChangeSupport::addPropertyChangeListener(this);
         }
     }

     locationPanelCheckBoxes->update();
     adjustSize();
     update();
 }

 /*private*/ void TrainSwitchListEditFrame::runCustomSwitchLists(bool isChanged) {
     if (!Setup::isGenerateCsvSwitchListEnabled()) {
         return;
     }
     log->debug("run custom switch lists");
     TrainSwitchLists* trainSwitchLists = new TrainSwitchLists();
//     TrainCsvSwitchLists trainCsvSwitchLists = new TrainCsvSwitchLists();
     for (int i = 0; i < locationCheckBoxes.size(); i++) {
         QString locationName = locationCheckBoxes.at(i)->objectName();
         Location* location = locationManager->getLocationByName(locationName);
         if (location->isSwitchListEnabled()
                 && (!isChanged || isChanged && location->getStatus()==(Location::MODIFIED))) {
             // also build the regular switch lists so they can be used
             if (!switchListRealTimeCheckBox->isChecked()) {
                 trainSwitchLists->buildSwitchList(location);
             }
#if 0
             File* csvFile = trainCsvSwitchLists.buildSwitchList(location);
             if (csvFile == NULL || !csvFile.exists()) {
                 log->error(tr("CSV switch list file was not created for location %1").arg(locationName));
                 return;
             }

             TrainCustomSwitchList.addCVSFile(csvFile);
#endif
         }
     }
#if 0
     // Processes the CSV Manifest files using an external custom program.
     if (!TrainCustomSwitchList.manifestCreatorFileExists()) {
         log->warn("Manifest creator file not found!, directory name: {}, file name: {}", TrainCustomSwitchList
                 .getDirectoryName(), TrainCustomSwitchList.getFileName());
         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("LoadDirectoryNameFileName"),
                 new Object[]{TrainCustomSwitchList.getDirectoryName(), TrainCustomSwitchList.getFileName()}),
                 tr("ManifestCreatorNotFound"), JOptionPane.ERROR_MESSAGE);
         return;
     }
     // Now run the user specified custom Switch List processor program
     TrainCustomSwitchList.process();
#endif
     // set trains switch lists printed
     ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->setTrainsSwitchListStatus(Train::PRINTED);
 }

 /*private*/ void TrainSwitchListEditFrame::enableSaveButton(bool enable) {
     saveButton->setEnabled(enable);
     // these get the inverse
     previewButton->setEnabled(!enable);
     printButton->setEnabled(!enable);
     updateButton->setEnabled(!enable);
     resetButton->setEnabled(!enable);
 }

 /*private*/ void TrainSwitchListEditFrame::enableChangeButtons() {
     changeButton->setEnabled(false);
     csvChangeButton->setEnabled(false);
     runChangeButton->setEnabled(false);
     foreach (Location* location, locationManager->getLocationsByNameList()) {
         if (location->getStatus()==(Location::MODIFIED) && location->isSwitchListEnabled()) {
             changeButton->setEnabled(true);
             csvChangeButton->setEnabled(true);
             runChangeButton->setEnabled(true);
         }
     }
 }

 // The print switch list for a location has changed
 /*private*/ void TrainSwitchListEditFrame::changeLocationCheckboxes(PropertyChangeEvent* e) {
     Location* l = (Location*) e->getSource();
     for (int i = 0; i < locationCheckBoxes.size(); i++) {
         QCheckBox* checkBox = locationCheckBoxes.at(i);
         if (checkBox->objectName()==(l->objectName())) {
             checkBox->setChecked(l->isSwitchListEnabled());
             break;
         }
     }
 }

 /*private*/ void TrainSwitchListEditFrame::addLocationCheckBoxAction(QCheckBox* b) {
//     b.addActionListener(new java.awt.event.ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent e) {
//             locationCheckBoxActionPerformed(e);
//         }
//     });
  locationCheckBoxMapper->setMapping(b,b);
  connect(b, SIGNAL(clicked(bool)), locationCheckBoxMapper, SLOT(map()));
 }

 /*public*/ void TrainSwitchListEditFrame::locationCheckBoxActionPerformed(QWidget* ae) {
     QCheckBox* b = (QCheckBox*) ae;
     log->debug("checkbox change " + b->objectName());
     Location* l = locationManager->getLocationByName(b->objectName());
     l->setSwitchListEnabled(b->isChecked());
     // enable the save button whenever a checkbox is changed
     saveButton->setEnabled(true);
 }

 /*private*/ void TrainSwitchListEditFrame::addCommentButtonAction(JButton* b) {
//     b.addActionListener(new java.awt.event.ActionListener() {
//         /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//             commentButtonActionPerformed(e);
//         }
//     });
  connect(b, SIGNAL(clicked(bool)), this, SLOT(commentButtonActionPerformed()));
 }

 /*public*/ void TrainSwitchListEditFrame::commentButtonActionPerformed(JActionEvent* ae) {
  JButton* b = (JButton*) ae;
     log->debug("button action " + b->objectName());
     Location* l = locationManager->getLocationByName(b->objectName());
     new TrainSwitchListCommentFrame(l);
 }

 /*protected*/ void TrainSwitchListEditFrame::comboBoxActionPerformed(QWidget* /*ae*/) {
     log->debug("combo box action");
     enableSaveButton(true);
 }

 /*public*/ void TrainSwitchListEditFrame::dispose() {
     //locationManager.removePropertyChangeListener(this);
 disconnect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     Setup::removePropertyChangeListener(this);
     foreach (Location* location, locationManager->getLocationsByNameList()) {
      location->removePropertyChangeListener(this);
     }
     OperationsFrame::dispose();
 }

 /*public*/ void TrainSwitchListEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Location::SWITCHLIST_CHANGED_PROPERTY)) {
         changeLocationCheckboxes(e);
         enableChangeButtons();
     }
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::STATUS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::SWITCHLIST_COMMENT_CHANGED_PROPERTY)) {
         updateLocationCheckboxes();
         enableChangeButtons();
     }
     if (e->getPropertyName()==(Setup::SWITCH_LIST_CSV_PROPERTY_CHANGE)) {
         customPanel->setVisible(Setup::isGenerateCsvSwitchListEnabled());
     }
 }

// private static class TrainSwitchListCommentFrame extends OperationsFrame {

//     /**
//      *
//      */
//     private static final long serialVersionUID = 4880037349897207594L;
//     // text area
//     JTextArea commentTextArea = new JTextArea(10, 90);
//     JScrollPane commentScroller = new JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//             JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
//     Dimension minScrollerDim = new Dimension(1200, 500);
//  saveButton = new JButton(tr("Save"));

//     Location _location;

     /*private*/ TrainSwitchListCommentFrame::TrainSwitchListCommentFrame(Location* location) {
         //super();
         initComponents(location);
     }

     /*private*/ void TrainSwitchListCommentFrame::initComponents(Location* location) {
         _location = location;
         // the following code sets the frame's initial state
         //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
         QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

         JPanel* pC = new JPanel();
         pC->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
         pC->setLayout(new GridBagLayout());
         //commentScroller->setMinimumSize(minScrollerDim);
         addItem(pC, /*commentScroller*/commentTextArea, 1, 0);

         commentTextArea->setText(location->getSwitchListComment());

         JPanel* pB = new JPanel();
         pB->setLayout(new GridBagLayout());
         addItem(pB, saveButton, 0, 0);

         thisLayout->addWidget(pC);
         thisLayout->addWidget(pB);

         addButtonAction(saveButton);

         adjustSize();
         setTitle(location->getName());
         setVisible(true);
     }

     // Buttons
     /*public*/ void TrainSwitchListCommentFrame::buttonActionPerformed(QWidget* ae) {
      JButton* source = (JButton*)ae;
         if (source == saveButton) {
             _location->setSwitchListComment(commentTextArea->toHtml());
             // save location file
             OperationsXml::save();
             if (Setup::isCloseWindowOnSaveEnabled()) {
                 OperationsFrame::dispose();
             }
         }
     }

     /*public*/ QString TrainSwitchListEditFrame::getClassName()
     {
      return "jmri.jmrit.operations.trains.TrainSwitchListEditFrame";
     }

     /*public*/ QString TrainSwitchListCommentFrame::getClassName()
     {
      return "jmri.jmrit.operations.trains.TrainSwitchListCommentFrame";
     }

}
