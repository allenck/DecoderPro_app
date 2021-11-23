#include "locationsbycartypeframe.h"
#include <QCheckBox>
#include "cartypes.h"
#include "locationmanager.h"
#include <QBoxLayout>
#include "jpanel.h"
#include "gridbaglayout.h"
#include <QScrollArea>
#include <QComboBox>
#include <QMenu>
#include <QMenuBar>
#include "control.h"
#include "location.h"
#include "track.h"
#include <QLabel>
#include "jbutton.h"
#include "cartypes.h"
#include "logger.h"
#include <QMessageBox>
#include "operationsxml.h"
#include "setup.h"
#include "printlocationsbycartypesaction.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Frame to display which locations service certain car types
 *
 * @author Dan Boudreau Copyright (C) 2009, 2011
 * @version $Revision: 29410 $
 */
///*public*/ class LocationsByCarTypeFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -5286439226672099226L;

 /*public*/ LocationsByCarTypeFrame::LocationsByCarTypeFrame(QWidget* parent) : OperationsFrame(parent)
 {
     //super();
  log = new Logger("LocationsByCarTypeFrame");
  Empty = "            ";

  // checkboxes have the location id or track id as the checkbox name
  locationCheckBoxList =  QList<QCheckBox*>();
  trackCheckBoxList = QList<QCheckBox*>();
  locationCheckBoxes = new QWidget();

  // major buttons
  clearButton = new JButton(tr("Clear"));
  setButton = new JButton(tr("Select"));
  saveButton = new JButton(tr("Save"));

  // check boxes
  copyCheckBox = new QCheckBox(tr("Copy"));

  // text field
  textCarType = new QLabel(Empty);

 // combo boxes
  typeComboBox = ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getComboBox();

 }

 /*public*/ void LocationsByCarTypeFrame::initComponents() {
     initComponents(NONE);
 }

 /*public*/ void LocationsByCarTypeFrame::initComponents(Location* location) {
     this->location = location;
     initComponents(NONE);
 }

 /*public*/ void LocationsByCarTypeFrame::initComponents(Location* location, QString carType) {
     this->location = location;
     initComponents(carType);
 }

 /*public*/ void LocationsByCarTypeFrame::initComponents(QString carType) {

     // load managers
     manager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));

     // general GUI config
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // Set up the panels
     JPanel* pCarType = new JPanel();
     pCarType->setLayout(new GridBagLayout());
     pCarType->setBorder(BorderFactory::createTitledBorder(tr("Type")));

     addItem(pCarType, typeComboBox, 0, 0);
     addItem(pCarType, copyCheckBox, 1, 0);
     addItem(pCarType, textCarType, 2, 0);
     typeComboBox->setCurrentIndex(typeComboBox->findText(carType));
     copyCheckBox->setToolTip(tr("First select the car type you want to copy, then select Copy, then the car type you want to copy to, then Save"));

     JPanel* pLocationsGroupBox = new JPanel;
     pLocationsGroupBox->setLayout(new QVBoxLayout);
     pLocations = new JPanel();
     pLocations->setLayout(new GridBagLayout());
     locationPane = new QScrollArea; //(pLocations);
     //locationPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
     pLocationsGroupBox->setBorder(BorderFactory::createTitledBorder(tr("Locations")));
     locationPane->setWidgetResizable(true);
     pLocationsGroupBox->layout()->addWidget(locationPane);
     updateLocations();
     pLocations->layout()->addWidget(new QLabel("Test Widget"));

     JPanel* pButtons = new JPanel();
     pButtons->setLayout(new GridBagLayout());
     pButtons->setBorder(BorderFactory::createTitledBorder(""));
     //pLocationsGroupBox->setTitle("Locations");

     addItem(pButtons, (QWidget*)clearButton, 0, 0);
     addItem(pButtons, (QWidget*)setButton, 1, 0);
     addItem(pButtons, (QWidget*)saveButton, 2, 0);

     thisLayout->addWidget(pCarType);
     locationPane->setWidget(pLocations);
     thisLayout->addWidget(pLocationsGroupBox);
     thisLayout->addWidget(pButtons);

     // setup combo box
     addComboBoxAction(typeComboBox);

     // setup buttons
     addButtonAction(setButton);
     addButtonAction(clearButton);
     addButtonAction(saveButton);

     // setup checkbox
     addCheckBoxAction(copyCheckBox);

     //manager.addPropertyChangeListener(this);
     connect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().addPropertyChangeListener(this);
     connect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
     toolMenu->addAction(new PrintLocationsByCarTypesAction(tr("Print By Type"), new JFrame(), false,
             this));
     toolMenu->addAction(new PrintLocationsByCarTypesAction(tr("Preview By Type"), new JFrame(), true,
             this));
     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_ModifyLocationsByCarType", true); // NOI18N

     resize(QSize()); // we need to resize this frame
     adjustSize();
     setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight250));
     resize(width() + 25, height()); // make a bit wider to eliminate scroll bar
     if (location != NULL) {
         setTitle(tr("Modify Location"));
     } else {
         setTitle(tr("Modify Locations"));
     }
     setVisible(true);
 }

 /*public*/ void LocationsByCarTypeFrame::comboBoxActionPerformed(QWidget* ae) {
     log->debug("combo box action");
     updateLocations();
 }

 // Save, Delete, Add
 /*public*/ void LocationsByCarTypeFrame::buttonActionPerformed(QWidget* ae)
 {
  JButton* source = (JButton*)ae;
  if (source == saveButton)
  {
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
  * checkbox name is the id of the location or track.
  */
 /*private*/ void LocationsByCarTypeFrame::save()
 {
  //     if (copyCheckBox.isSelected() && JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("CopyCarType"),
  //             new Object[]{typeComboBox.getSelectedItem(), textCarType.getText()}), tr("CopyCarTypeTitle"),
  //             JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
  if(copyCheckBox->isChecked() && QMessageBox::question(this, tr("Copy car type?"), tr("Do you want car type (%1) to service the same tracks as car type (%2)?").arg(typeComboBox->currentText()).arg(textCarType->text()),QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
  {
   return;
  }
  log->debug(tr("save %1 locations").arg(locationCheckBoxList.size()));
  removePropertyChangeLocations();
  foreach (QCheckBox* cb, locationCheckBoxList)
  {
   Location* loc = manager->getLocationById(cb->objectName());
   if (cb->isChecked())
   {
    loc->addTypeName(typeComboBox->currentText());
    // save tracks that have the same id as the location
    foreach (QCheckBox* cbt, trackCheckBoxList)
    {
     QStringList id = cbt->objectName().split("s");
     if (loc->getId()==(id[0]))
     {
      Track* track = loc->getTrackById(cbt->objectName());
      if (cbt->isChecked())
      {
       track->addTypeName( typeComboBox->currentText());
      }
      else
      {
       track->deleteTypeName( typeComboBox->currentText());
      }
     }
    }
   }
   else
   {
    loc->deleteTypeName( typeComboBox->currentText());
   }
  }
  OperationsXml::save();
  updateLocations();
  if (Setup::isCloseWindowOnSaveEnabled()) {
      dispose();
  }
 }

 /*private*/ void LocationsByCarTypeFrame::updateLocations()
 {
  log->debug("update checkboxes");
  removePropertyChangeLocations();
  locationCheckBoxList.clear();
  trackCheckBoxList.clear();
  int x = 0;
  //pLocations.removeAll();
  int i0=0, i1 =0, i2=0;
  QLayoutItem* item;
  while ( ( item = pLocations->layout()->takeAt( 0 ) ) != NULL )
  {
      delete item->widget();
      delete item;
   i0++;
  }
  QString carType =  typeComboBox->currentText();
  if (copyCheckBox->isChecked()) {
      carType = textCarType->text();
  }
  QList<Location*> locations = manager->getLocationsByNameList();
  foreach (Location* loc, locations)
  {
   // show only one location?
   if (location != NULL && location != loc)
   {
       continue;
   }
   //loc.addPropertyChangeListener(this);
   connect(loc, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   QCheckBox* cb = new QCheckBox(loc->getName());
   cb->setObjectName(loc->getId());
   cb->setToolTip(tr("Select this location if it services car type %1").arg(carType));
   addCheckBoxAction(cb);
   locationCheckBoxList.append(cb);
   bool locAcceptsType = loc->acceptsTypeName(carType);
   cb->setChecked(locAcceptsType);
   addItemLeft(pLocations, cb, 0, x++);
   i1++;
   QList<Track*> tracks = loc->getTrackByNameList(NULL);
   foreach (Track* track, tracks)
   {
    //track.addPropertyChangeListener(this);
    connect(track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    cb = new QCheckBox(track->getName());
    cb->setObjectName(track->getId());
    cb->setToolTip(tr("Select this track if it services car type %1").arg(carType));
    addCheckBoxAction(cb);
    trackCheckBoxList.append(cb);
    cb->setChecked(track->acceptsTypeName(carType));
    addItemLeft(pLocations, cb, 1, x++);
    i2 ++;
   }
  }
  log->debug(tr("deleted %3items added %1 locations, %2 tracks").arg(i1).arg(i2).arg(i0));
  locationPane->update();
  pLocations->update();
  update();
 }

 /*private*/ void LocationsByCarTypeFrame::updateComboBox() {
     log->debug("update combobox");
     ((CarTypes*)InstanceManager::getDefault("CarTypes"))->updateComboBox(typeComboBox);
 }

 /*private*/ void LocationsByCarTypeFrame::selectCheckboxes(bool select) {
     for (int i = 0; i < locationCheckBoxList.size(); i++) {
         locationCheckBoxList.at(i)->setChecked(select);
     }
     for (int i = 0; i < trackCheckBoxList.size(); i++) {
         trackCheckBoxList.at(i)->setChecked(select);
     }
 }

 /*public*/ void LocationsByCarTypeFrame::checkBoxActionPerformed(QWidget* ae)
 {
     // copy checkbox?
  QCheckBox* source = (QCheckBox*)ae;
     if (source == copyCheckBox) {
         if (copyCheckBox->isChecked()) {
             textCarType->setText( typeComboBox->currentText());
         } else {
             textCarType->setText(Empty);
             updateLocations();
         }
     } else {
         QCheckBox* cb = (QCheckBox*) source;
         log->debug(tr("Checkbox %1 text: %2").arg(cb->objectName()).arg(cb->text()));
         if (locationCheckBoxList.contains(cb)) {
             log->debug(tr("Checkbox location %1").arg(cb->text()));
             // must deselect tracks if location is deselect
             if (!cb->isChecked()) {
                 QString locId = cb->objectName();
                 for (int i = 0; i < trackCheckBoxList.size(); i++) {
                     cb = trackCheckBoxList.at(i);
                     QStringList id = cb->objectName().split("s");
                     if (locId==(id[0])) {
                         cb->setChecked(false);
                     }
                 }
             }

         } else if (trackCheckBoxList.contains(cb)) {
             log->debug(tr("Checkbox track %1").arg(cb->text()));
             // Must select location if track is selected
             if (cb->isChecked()) {
                 QStringList loc = cb->objectName().split("s");
                 for (int i = 0; i < locationCheckBoxList.size(); i++) {
                     cb = locationCheckBoxList.at(i);
                     if (cb->objectName()==(loc[0])) {
                         cb->setChecked(true);
                         break;
                     }
                 }
             }
         } else {
             log->error("Error checkbox not found");
         }
     }
 }

 /*private*/ void LocationsByCarTypeFrame::removePropertyChangeLocations() {
     if (!locationCheckBoxList.isEmpty()) {
         for (int i = 0; i < locationCheckBoxList.size(); i++) {
             // checkbox name is the location id
             Location* loc = manager->getLocationById(locationCheckBoxList.at(i)->objectName());
             if (loc != NULL) {
                 //loc.removePropertyChangeListener(this);
              disconnect(loc, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

                 QList<Track*> tracks = loc->getTrackList();
                 foreach (Track* track, tracks) {
                     //track.removePropertyChangeListener(this);
                  disconnect(track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                 }
             }
         }
     }
 }

 /*public*/ void LocationsByCarTypeFrame::dispose() {
     //manager.removePropertyChangeListener(this);
 disconnect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().removePropertyChangeListener(this);
 disconnect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeLocations();
     OperationsFrame::dispose();
 }

 /*public*/ void LocationsByCarTypeFrame::propertyChange(PropertyChangeEvent* e) {
     if (log->isDebugEnabled()) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
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
         updateComboBox();
     }
 }
/*public*/ QString LocationsByCarTypeFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.tools.LocationsByCarTypeFrame";
}


}
