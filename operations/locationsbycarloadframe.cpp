#include "locationsbycarloadframe.h"
#include "locationmanager.h"
#include "track.h"
#include "location.h"
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "jcombobox.h"
#include "cartypes.h"
#include "carloads.h"
#include "carload.h"
#include <QScrollArea>
#include "control.h"
#include <QMenu>
#include <QMenuBar>
//#include "printlocationsbycartypesaction.h"
#include "jframe.h"
#include "logger.h"
#include <QLabel>
#include "operationsxml.h"
#include "setup.h"
#include <QMessageBox>
#include "trackloadeditframe.h"
#include "printlocationsbycartypesaction.h"

namespace Operations
{
 /**
  * Frame to display which locations service certain car loads
  *
  * @author Dan Boudreau Copyright (C) 2014
  * @version $Revision: 27492 $
  */
 ///*public*/ class LocationsByCarLoadFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 968602554445596299L;


 /*public*/ LocationsByCarLoadFrame::LocationsByCarLoadFrame(QWidget* parent) : OperationsFrame(parent)
 {
  //super();
  log = new Logger("LocationsByCarLoadFrame");
  // checkboxes track id as the checkbox name
  trackCheckBoxList = QList<QCheckBox*>();
  locationCheckBoxes = new QWidget();

  // major buttons
  clearButton = new QPushButton(tr("Clear"));
  setButton = new QPushButton(tr("Select"));
  saveButton = new QPushButton(tr("Save"));

  // check boxes
  // JCheckBox copyCheckBox = new JCheckBox(tr("Copy"));
  loadAndTypeCheckBox = new QCheckBox(tr("Use car type and load"));

  // radio buttons
  // text field
  // combo boxes
  typeComboBox = CarTypes::instance()->getComboBox();
  loadComboBox = CarLoads::instance()->getComboBox(NULL);

 }

 /*public*/ void LocationsByCarLoadFrame::initComponents(Location* location) {
     this->_location = location;
     initComponents();
 }

 /*public*/ void LocationsByCarLoadFrame::initComponents()
 {
  // load managers
  locationManager = LocationManager::instance();

  // general GUI config
  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Set up the panels
  QGroupBox* pCarType = new QGroupBox();
  pCarType->setLayout(new GridBagLayout());
  //pCarType.setBorder(BorderFactory.createTitledBorder(tr("Type")));
  pCarType->setStyleSheet(gbStyleSheet);
  pCarType->setTitle(tr("Type"));
  addItem(pCarType, typeComboBox, 0, 0);

  QGroupBox* pLoad = new QGroupBox();
  pLoad->setLayout(new GridBagLayout());
  //pLoad.setBorder(BorderFactory.createTitledBorder(tr("Load")));
  pLoad->setStyleSheet(gbStyleSheet);
  pLoad->setTitle(tr("Load"));

  addItem(pLoad, loadComboBox, 0, 0);
  addItem(pLoad, loadAndTypeCheckBox, 1, 0);

  QGroupBox* pLocationsFrame = new QGroupBox;
  pLocationsFrame->setLayout(new QVBoxLayout);
  pLocations = new QWidget();
  pLocations->setLayout(new GridBagLayout());
  QScrollArea* locationPane = new QScrollArea(/*pLocations*/);
  locationPane->setWidgetResizable(true);
  pLocationsFrame->layout()->addWidget(locationPane);
  //locationPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  //locationPane.setBorder(BorderFactory.createTitledBorder(tr("Locations")));
  pLocationsFrame->setStyleSheet(gbStyleSheet);
  pLocationsFrame->setTitle(tr("Locations"));
  updateLoadComboBox();

  QGroupBox* pButtons = new QGroupBox();
  pButtons->setLayout(new GridBagLayout());
  //pButtons.setBorder(BorderFactory.createTitledBorder(""));
  pButtons->setStyleSheet(gbStyleSheet);

  addItem(pButtons, clearButton, 0, 0);
  addItem(pButtons, setButton, 1, 0);
  addItem(pButtons, saveButton, 2, 0);

  thisLayout->addWidget(pCarType);
  thisLayout->addWidget(pLoad);
  locationPane->setWidget(pLocations);
  thisLayout->addWidget(pLocationsFrame);
  thisLayout->addWidget(pButtons);

  // setup combo box
  addComboBoxAction(typeComboBox);
  addComboBoxAction(loadComboBox);

  // setup buttons
  addButtonAction(setButton);
  addButtonAction(clearButton);
  addButtonAction(saveButton);

  // setup checkbox
  addCheckBoxAction(loadAndTypeCheckBox);

  //locationManager.addPropertyChangeListener(this);
  connect(locationManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarTypes::instance().addPropertyChangeListener(this);
  connect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarLoads::instance().addPropertyChangeListener(this);
  connect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));

  toolMenu->addAction(new PrintLocationsByCarTypesAction(tr("MenuItemPrintByType"), new JFrame(), false,
          this));
  toolMenu->addAction(new PrintLocationsByCarTypesAction(tr("MenuItemPreviewByType"), new JFrame(), true,
          this));

  menuBar->addMenu(toolMenu);
  setMenuBar(menuBar);
  addHelpMenu("package.jmri.jmrit.operations.Operations_ModifyLocationsByCarType", true); // NOI18N

  resize(QSize()); // we need to resize this frame
  adjustSize();
  setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight250));
  resize(width() + 25, height()); // make a bit wider to eliminate scroll bar
  if (_location != NULL) {
      setTitle(tr("Modify Location by Car Load"));
  } else {
      setTitle(tr("Modify Locations by Car Load"));
  }
  setVisible(true);
 }

 /*public*/ void LocationsByCarLoadFrame::comboBoxActionPerformed(QWidget* ae)
{
     log->debug("combo box action");
     JComboBox* source = (JComboBox*)ae;
     if (source == loadComboBox) {
         log->debug(tr("Load combobox change, selected load: (%1)").arg(loadComboBox->currentText()));
         if (loadComboBox->isEnabled() && loadComboBox->currentText() != NULL) {
             updateLocations();
         }
     }
     if (source == typeComboBox) {
         updateLoadComboBox();
     }
 }

 // Save, Delete, Add
 /*public*/ void LocationsByCarLoadFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         save();
     }
     if (source == setButton) {
         selectCheckboxes(true);
     }
     if (source == clearButton) {
         selectCheckboxes(false);
     }
 }

 /**
  * Update the car types that locations and tracks service. Note that the
  * checkbox name is the id of the location or track->
  */
 /*private*/ void LocationsByCarLoadFrame::save() {
     log->debug("save");
     OperationsXml::save();
     if (Setup::isCloseWindowOnSaveEnabled()) {
         dispose();
     }
 }

 /**
  * Update tracks at locations based on car type serviced, or car loads
  * serviced. If car loads, disable any tracks that don't service the car
  * type selected.
  */
 /*private*/ void LocationsByCarLoadFrame::updateLocations() {
     log->debug("update checkboxes");
     removePropertyChangeLocations();
     trackCheckBoxList.clear();
     int x = 0;
     //pLocations.removeAll();
     QLayoutItem* item;
     while ( ( item = pLocations->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }

     QString type =  typeComboBox->currentText();
     QString load =  loadComboBox->currentText();
     log->debug(tr("Selected car type : (%1) load (%2)").arg(type).arg(load));
     QList<Location*> locations = locationManager->getLocationsByNameList();
     foreach (Location* location, locations) {
         // show only one location?
         if (_location != NULL && _location != location) {
             continue;
         }
         //location->addPropertyChangeListener(this);
         connect(location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         QLabel* locationName = new QLabel(location->getName());
         addItemLeft(pLocations, locationName, 0, x++);
         QList<Track*> tracks = location->getTrackByNameList(NULL);
         foreach (Track* track, tracks)
         {
             //track->addPropertyChangeListener(this);
          connect(track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             QCheckBox* cb = new QCheckBox(track->getName());
             cb->setObjectName(track->getId() + "-" + "r");
             addCheckBoxAction(cb);
             trackCheckBoxList.append(cb);
             cb->setEnabled(track->acceptsTypeName(type));
             cb->setChecked(track->acceptsLoad(load, type));
             addItemLeft(pLocations, cb, 1, x++);
             if (cb->isEnabled()) {
                 cb->setToolTip(tr("Select this track if it services car load %1").arg(load));
             } else {
                 cb->setToolTip(tr("Track does not service car type %1").arg(type));
             }
         }
         if (location->isStaging()) {
             QLabel* ships = new QLabel(location->getName() + " (" + tr("Ships") + ")");
             addItemLeft(pLocations, ships, 0, x++);
             foreach (Track* track, tracks) {
                 QCheckBox* cb = new QCheckBox(track->getName());
                 cb->setObjectName(track->getId() + "-" + "s");
                 addCheckBoxAction(cb);
                 trackCheckBoxList.append(cb);
                 cb->setEnabled(track->acceptsTypeName(type));
                 cb->setChecked(track->shipsLoad(load, type));
                 addItemLeft(pLocations, cb, 1, x++);
                 if (cb->isEnabled()) {
                     cb->setToolTip(tr("Select this track if it ships car load %1").arg(load));
                 } else {
                     cb->setToolTip(tr("Track does not service car type %1").arg(type));
                 }
             }

         }
     }
     pLocations->update();
     update();
 }

 /*private*/ void LocationsByCarLoadFrame::updateTypeComboBox() {
     log->debug("update type combobox");
     CarTypes::instance()->updateComboBox(typeComboBox);
 }

 /*private*/ void LocationsByCarLoadFrame::updateLoadComboBox() {
     log->debug("update load combobox");
     if (typeComboBox->currentText() != NULL) {
         QString type =  typeComboBox->currentText();
         QString load =  loadComboBox->currentText();
         log->debug(tr("Selected car type : (%1) load (%2)").arg(type).arg(load));
         CarLoads::instance()->updateComboBox(type, loadComboBox);
         loadComboBox->setEnabled(false); // used as a flag to prevent updateLocations()
         if (load != NULL) {
             loadComboBox->setCurrentIndex(loadComboBox->findText(load));
         }
         loadComboBox->setEnabled(true);
         updateLocations();
     }
 }

 /*private*/ void LocationsByCarLoadFrame::selectCheckboxes(bool select) {
     foreach (QCheckBox* cb, trackCheckBoxList) {
         if (cb->isEnabled()) {
             cb->setChecked(select);
         }
     }
 }


 /*public*/ void LocationsByCarLoadFrame::checkBoxActionPerformed(QWidget* ae) {
 QCheckBox* source = (QCheckBox*)ae;
     if (source == loadAndTypeCheckBox) {
         updateLocations();
         return;
     }
     QCheckBox* cb =  source;
     QStringList locId = cb->objectName().split("-");
     QStringList id = locId[0].split("s");
     Location* loc = locationManager->getLocationById(id[0]);
     if (loc != NULL) {
         Track* track = loc->getTrackById(locId[0]);
         // if enabled track services this car type
         log->debug(tr("CheckBox : %1 track: (%2) isEnabled: %3 isSelected: %4").arg(cb->objectName()).arg(track->getName()).arg(cb
                 ->isEnabled()).arg(cb->isChecked()));
         if (cb->isEnabled()) {
             bool needLoadTrackEditFrame = false;
             QString loadName =  loadComboBox->currentText();
             QString load = loadName;
             QString type =  typeComboBox->currentText();
             log->debug(tr("Selected load (%1)").arg(loadName));
             if (loadAndTypeCheckBox->isChecked()) {
                 loadName = type + CarLoad::SPLIT_CHAR + loadName;
             }
             if (locId[1]==("r")) {
                 if (cb->isChecked()) {
                     if (track->getLoadOption()==(Track::ALL_LOADS)) {
                         log->debug(tr("All loads selected for track (%1)").arg(track->getName()));
                     } else if (track->getLoadOption()==(Track::INCLUDE_LOADS)) {
                         track->addLoadName(loadName);
                     } else if (track->getLoadOption()==(Track::EXCLUDE_LOADS)) {
                         track->deleteLoadName(loadName);
                         // need to check if load configuration is to exclude all car types using this load
                         if (!track->acceptsLoadName(load)) {
//                             JOptionPane.showMessageDialog(this,
//                                     tr("Warning! Track (%1) excludes all cars with load (%2)").arg(track->getName()).arg(load)).arg(tr("Error"),
//                                     JOptionPane.WARNING_MESSAGE);
                          QMessageBox::warning(this, tr("Error"), tr("Warning! Track (%1) excludes all cars with load (%2)").arg(track->getName()).arg(load));
                             needLoadTrackEditFrame = true;
                         } else if (!track->acceptsLoad(load, type))
                         {
//                             JOptionPane.showMessageDialog(this, Bundle
//                                     ->getMessage("WarningExcludeTrackTypeAndLoad"), new Object[]{track->getName(),
//                                         type, load}), tr("Error"), JOptionPane.WARNING_MESSAGE);
                          QMessageBox::critical(this, tr("Error"), tr("Warning! Track (%1) excludes car type (%1) with load (%2)").arg(track->getName()).arg(type).arg(load));
                             needLoadTrackEditFrame = true;
                         }
                     }
                 } else {
                     if (track->getLoadOption()==(Track::INCLUDE_LOADS)) {
                         track->deleteLoadName(loadName);
                         // need to check if load configuration is to accept all car types using this load
                         if (track->acceptsLoadName(load)) {
//                             JOptionPane.showMessageDialog(this, Bundle
//                                     ->getMessage("WarningAcceptTrackLoad"), new Object[]{track->getName(), load}),
//                                     tr("Error"), JOptionPane.WARNING_MESSAGE);
                          QMessageBox::warning(this, tr("Error"), tr("Warning! Track (%1) accepts all cars with load (%2)").arg(track->getName()).arg(load));
                             needLoadTrackEditFrame = true;
                         } else if (track->acceptsLoad(load, type)) {
//                             JOptionPane.showMessageDialog(this, Bundle
//                                     ->getMessage("WarningAcceptTrackTypeAndLoad"), new Object[]{track->getName(),
//                                         type, load}), tr("Error"), JOptionPane.WARNING_MESSAGE);
                          QMessageBox::warning(this, tr("Error"), tr(""));
                             needLoadTrackEditFrame = true;
                         }
                     } else if (track->getLoadOption()==(Track::EXCLUDE_LOADS)) {
                         track->addLoadName(loadName);
                     } else if (track->getLoadOption()==(Track::ALL_LOADS)) {
                         // need to exclude this load
                         track->setLoadOption(Track::EXCLUDE_LOADS);
                         track->addLoadName(loadName);
                     }
                 }
             }
             if (locId[1]==("s")) {
                 if (cb->isChecked()) {
                     if (track->getShipLoadOption()==(Track::ALL_LOADS)) {
                         log->debug(tr("Ship all loads selected for track (%1)").arg(track->getName()));
                     } else if (track->getShipLoadOption()==(Track::INCLUDE_LOADS)) {
                         track->addShipLoadName(loadName);
                     } else if (track->getShipLoadOption()==(Track::EXCLUDE_LOADS)) {
                         track->deleteShipLoadName(loadName);
                         // need to check if load configuration is to exclude all car types using this load
                         if (!track->shipsLoadName(load)) {
//                             JOptionPane.showMessageDialog(this, Bundle
//                                     ->getMessage("WarningExcludeTrackShipLoad"), new Object[]{track->getName(),
//                                         load}), tr("Error"), JOptionPane.WARNING_MESSAGE);
                          QMessageBox::warning(this, tr("Error"), tr(""));
                             needLoadTrackEditFrame = true;
                         } else if (!track->shipsLoad(load, type)) {
//                             JOptionPane.showMessageDialog(this, Bundle
//                                     ->getMessage("WarningExcludeTrackShipTypeAndLoad"), new Object[]{
//                                         track->getName(), type, load}), tr("Error"),
//                                     JOptionPane.WARNING_MESSAGE);
                          QMessageBox::warning(this, tr("Error"), tr("Warning! Track (%1) doesn''t ship car type (%2) with load (%3)").arg(track->getName()).arg(type).arg(load));
                             needLoadTrackEditFrame = true;
                         }
                     }
                 } else {
                     if (track->getShipLoadOption()==(Track::INCLUDE_LOADS)) {
                         track->deleteShipLoadName(loadName);
                         // need to check if load configuration is to accept all car types using this load
                         if (track->shipsLoadName(load)) {
//                             JOptionPane.showMessageDialog(this, Bundle
//                                     ->getMessage("WarningShipTrackLoad"), new Object[]{track->getName(), load}),
//                                     tr("Error"), JOptionPane.WARNING_MESSAGE);
                          QMessageBox::warning(this, tr("Error"), tr("Warning! Track (%1) ships all cars with load (%2)").arg(track->getName()).arg(load));
                             needLoadTrackEditFrame = true;
                         } else if (track->shipsLoad(load, type)) {
//                             JOptionPane.showMessageDialog(this, Bundle
//                                     ->getMessage("WarningShipTrackTypeAndLoad"), new Object[]{track->getName(),
//                                         type, load}), tr("Error"), JOptionPane.WARNING_MESSAGE);
                          QMessageBox::warning(this, tr("Error"), tr("Warning! Track (%1) ships car type (%2) with load (%3)").arg(track->getName()).arg(type).arg(load));
                             needLoadTrackEditFrame = true;
                         }
                     } else if (track->getShipLoadOption()==(Track::EXCLUDE_LOADS)) {
                         track->addShipLoadName(loadName);
                     } else if (track->getShipLoadOption()==(Track::ALL_LOADS)) {
                         // need to exclude this load
                         track->setShipLoadOption(Track::EXCLUDE_LOADS);
                         track->addShipLoadName(loadName);
                     }
                 }
             }
             if (needLoadTrackEditFrame) {
                 if (tlef != NULL) {
                     tlef->dispose();
                 }
                 tlef = new TrackLoadEditFrame();
                 tlef->initComponents(track->getLocation(), track);
             }
         }
     }
 }

 /*private*/ void LocationsByCarLoadFrame::removePropertyChangeLocations()
{
     foreach (Location* location, locationManager->getList()) {
         //location->removePropertyChangeListener(this);
      disconnect(location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         QList<Track*> tracks = location->getTrackList();
         foreach (Track* track, tracks) {
             //track->removePropertyChangeListener(this);
          disconnect(track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

         }
     }
 }

 /*public*/ void LocationsByCarLoadFrame::dispose() {
     //locationManager.removePropertyChangeListener(this);
     disconnect(locationManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes::instance().removePropertyChangeListener(this);
     disconnect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarLoads::instance().removePropertyChangeListener(this);
     disconnect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeLocations();
     OperationsFrame::dispose();
 }

 /*public*/ void LocationsByCarLoadFrame::propertyChange(PropertyChangeEvent* e) {
     if (log->isDebugEnabled()) {
      log->debug(tr("PropertyChange (%1) new ({%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
     }
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::TRACK_LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::NAME_CHANGED_PROPERTY)) {
         updateLocations();
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarTypes::CARTYPES_NAME_CHANGED_PROPERTY)) {
         updateTypeComboBox();
     }
     if (e->getPropertyName()==(CarLoads::LOAD_CHANGED_PROPERTY)) {
         updateLoadComboBox();
     }
 }
/*public*/ QString LocationsByCarLoadFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.tools.LocationsByCarLoadFrame";
}

}
