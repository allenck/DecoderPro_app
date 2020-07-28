#include "schedulesbyloadframe.h"
#include "locationmanager.h"
#include <QCheckBox>
#include "jcombobox.h"
#include "location.h"
#include "track.h"
#include "control.h"
#include "setup.h"
#include "cartypes.h"
#include <QBoxLayout>
#include <QGroupBox>
#include "gridbaglayout.h"
#include <QScrollArea>
#include "carloads.h"
#include "printcarloadsaction.h"
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include "schedule.h"
#include "scheduleitem.h"
#include "trainschedulemanager.h"
#include "trainschedule.h"

namespace Operations
{
 /**
  * Frame to display spurs with schedules and their loads
  *
  * @author Dan Boudreau Copyright (C) 2012
  * @version $Revision: 17977 $
  */
 ///*public*/ class SchedulesByLoadFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -1010990061006978311L;

 /*public*/ SchedulesByLoadFrame::SchedulesByLoadFrame(QWidget* parent) : OperationsFrame(tr("Show Schedule by Load"), parent){
     //super(tr("MenuItemShowSchedulesByLoad"));
 // combo box
 typesComboBox= CarTypes::instance()->getComboBox();
 loadsComboBox = new JComboBox();

 // checkbox
 allLoadsCheckBox = new QCheckBox(tr("All Loads"));

 // managers'
 locationManager = LocationManager::instance();

     // the following code sets the frame's initial state
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // load the panel
     QWidget* p1 = new QWidget();
     p1->setMaximumSize(QSize(2000, 200));
     p1->setLayout(new QVBoxLayout);//(p1, BoxLayout.X_AXIS));

     QGroupBox* type = new QGroupBox();
     type->setLayout(new GridBagLayout());
     //type.setBorder(BorderFactory.createTitledBorder(tr("Type")));
     type->setStyleSheet(gbStyleSheet);
     type->setTitle(tr("Type"));
     addItem(type, typesComboBox, 0, 0);

     QGroupBox* load = new QGroupBox();
     load->setLayout(new GridBagLayout());
     //load.setBorder(BorderFactory.createTitledBorder(tr("Load")));
     load->setStyleSheet(gbStyleSheet);
     load->setTitle(tr("Load"));
     addItem(load, loadsComboBox, 0, 0);
     addItem(load, allLoadsCheckBox, 1, 0);

     p1->layout()->addWidget(type);
     p1->layout()->addWidget(load);

     QGroupBox* locationsPanelFrame = new QGroupBox;
     locationsPanelFrame->setLayout(new QVBoxLayout);
     locationsPanel = new QWidget();
     locationsPanel->setLayout(new GridBagLayout());
     QScrollArea* locationsPane = new QScrollArea(/*locationsPanel*/);
     locationsPanelFrame->layout()->addWidget(locationsPane);
     locationsPane->setWidgetResizable(true);
     //locationsPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
     //locationsPane.setBorder(BorderFactory.createTitledBorder(tr("Locations")));
     locationsPanelFrame->setStyleSheet(gbStyleSheet);
     locationsPanelFrame->setTitle(tr("Locations"));

     thisLayout->addWidget(p1);
     locationsPane->setWidget(locationsPanel);
     thisLayout->addWidget(locationsPanelFrame);

     addComboBoxAction(typesComboBox);
     addComboBoxAction(loadsComboBox);

     addCheckBoxAction(allLoadsCheckBox);

     // property changes
     //locationManager.addPropertyChangeListener(this);
     connect(locationManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes::instance().addPropertyChangeListener(this);
     connect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarLoads::instance().addPropertyChangeListener(this);
     connect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
     toolMenu->addAction(new PrintCarLoadsAction(tr("Car Loads Preview"), true, this));
     toolMenu->addAction(new PrintCarLoadsAction(tr("Car Loads Print"), false, this));
     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_ShowSchedulesByCarTypeAndLoad", true); // NOI18N

     // select first item to load contents
     typesComboBox->setCurrentIndex(0);

     initMinimumSize(QSize(Control::panelWidth700, Control::panelHeight250));
 }

 /*public*/ void SchedulesByLoadFrame::comboBoxActionPerformed(QWidget* ae)
 {
  JComboBox* source = (JComboBox*)ae;
     if (source == typesComboBox) {
         updateLoadComboBox();
     }
     if (source == loadsComboBox) {
         updateLocations();
     }

 }

 /*public*/ void SchedulesByLoadFrame::checkBoxActionPerformed(QWidget* ae) {
     loadsComboBox->setEnabled(!allLoadsCheckBox->isChecked());
     updateLocations();
 }

 /*private*/ void SchedulesByLoadFrame::updateLoadComboBox() {
     if (typesComboBox->currentText() != NULL) {
         QString type =  typesComboBox->currentText();
         CarLoads::instance()->updateComboBox(type, loadsComboBox);
     }
 }

 /*private*/ void SchedulesByLoadFrame::updateLocations() {
     QString type = typesComboBox->currentText();
     QString load = loadsComboBox->currentText();
     log->debug(tr("Update locations for type (%1 load (%2)").arg(type).arg(load));
     //locationsPanel.removeAll();
     QLayoutItem* item;
     while ( ( item = locationsPanel->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     int x = 0;
     addItemLeft(locationsPanel, new QLabel(tr("Spur (schedule)")), 1, x);
     addItemLeft(locationsPanel, new QLabel(tr("Receive (type, delivery, road, load)")), 2, x);
     addItemLeft(locationsPanel, new QLabel(tr("Ship (load, pickup)")), 3, x);
     addItemLeft(locationsPanel, new QLabel(tr("Destination (track)")), 4, x++);

     foreach (Location* location, locationManager->getLocationsByNameList()) {
         // don't show staging
         if (location->isStaging())
             continue;
         addItemLeft(locationsPanel, new QLabel(location->getName()), 0, x++);
         // now look for a spur with a schedule
         foreach (Track* spur, location->getTrackByNameList(Track::SPUR)) {
             Schedule* sch = spur->getSchedule();
             if (sch == NULL) {
                 continue;
             }
             // listen for changes
             //spur.removePropertyChangeListener(this);
             disconnect(spur->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             //spur.addPropertyChangeListener(this);
             connect(spur->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             //sch.removePropertyChangeListener(this);
             disconnect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             //sch.addPropertyChangeListener(this);
             connect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             // determine if schedule is requesting car type and load
             foreach (ScheduleItem* si, sch->getItemsBySequenceList()) {
                 if (si->getTypeName()==(type) && si->getReceiveLoadName()==(load)
                         || si->getTypeName()==(type) && si->getReceiveLoadName()==(ScheduleItem::NONE)
                         || si->getTypeName()==(type) && si->getShipLoadName()==(load)
                         || si->getTypeName()==(type) && si->getShipLoadName()==(ScheduleItem::NONE)
                         || si->getTypeName()==(type) && allLoadsCheckBox->isChecked()) {
                     // is the schedule item valid?
                     QString status = spur->checkScheduleValid();
                     if (status!=(Track::SCHEDULE_OKAY)) {
                         addItemLeft(locationsPanel, new QLabel("  " + status), 0, x);
                     }
                     addItemLeft(locationsPanel,
                             new QLabel(spur->getName() + " (" + spur->getScheduleName() + ")"), 1, x);
                     // create string Receive(type, delivery, road, load)
                     QString s = si->getTypeName();
                     if (si->getSetoutTrainScheduleId()!=(ScheduleItem::NONE)
                             && TrainScheduleManager::instance()->getScheduleById(si->getSetoutTrainScheduleId()) != NULL) {
                         s = s  + ", " + TrainScheduleManager::instance()->getScheduleById(si->getSetoutTrainScheduleId())->getName();
                     } else {
                         s = s + ",";
                     }
                     if (si->getRoadName()!=(ScheduleItem::NONE)) {
                         s = s + ", " + si->getRoadName();
                     } else {
                         s = s + ",";
                     }
                     s = s + ", " + si->getReceiveLoadName();
                     addItemLeft(locationsPanel, new QLabel(tr("Receive") + " (" + s + ")"), 2, x);
                     // create string Ship(load, pickup)
                     s = "";
                     if (si->getPickupTrainScheduleId()!=(ScheduleItem::NONE)
                             && TrainScheduleManager::instance()->getScheduleById(si->getPickupTrainScheduleId()) != NULL) {
                         s = ", "+ TrainScheduleManager::instance()->getScheduleById(si->getPickupTrainScheduleId())->getName();
                     }
                     addItemLeft(locationsPanel, new QLabel(tr("Ship") +
                             " (" + si->getShipLoadName() + s + ")"), 3, x++);
                     // now the destination and track
                     if (si->getDestination() != NULL) {
                         addItemLeft(locationsPanel, new QLabel(si->getDestinationName() + " ("
                                 + si->getDestinationTrackName() + ")"), 4, x - 1);
                     }
                     // report if spur can't service the selected load
                     if (!allLoadsCheckBox->isChecked() &&
                             si->getReceiveLoadName()==(ScheduleItem::NONE) &&
                             !spur->acceptsLoad(load, type)) {
                         addItemLeft(locationsPanel, new QLabel(tr("Spur ({0}) doesn''t service type ({1}) load ({2})").arg(
                                 spur->getName()).arg(type, load)), 2, x++);
                     }
                 }
             }
         }
     }
     locationsPanel->update();
     update();
     //repaint();
 }

 /*public*/ void SchedulesByLoadFrame::dispose() {
     //locationManager.removePropertyChangeListener(this);
 disconnect(locationManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().removePropertyChangeListener(this);
 disconnect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarLoads.instance().removePropertyChangeListener(this);
 disconnect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     foreach (Track* spur, locationManager->getTracks(Track::SPUR)) {
         Schedule* sch = spur->getSchedule();
         if (sch == NULL) {
             continue;
         }
         //spur.removePropertyChangeListener(this);
         disconnect(spur->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         //sch.removePropertyChangeListener(this);
         disconnect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     OperationsFrame::dispose();
 }

 /*public*/ void SchedulesByLoadFrame::propertyChange(PropertyChangeEvent* e) {
     if (log->isDebugEnabled())
         log->debug(tr("Property change (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e->getNewValue().toString())); // NOI18N

     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)) {
         CarTypes::instance()->updateComboBox(typesComboBox);
     }
     if (e->getSource()->metaObject()->className()==("CarLoads")) {
         CarLoads::instance()->updateComboBox( typesComboBox->currentText(), loadsComboBox);
     }
     if (e->getSource()->metaObject()->className()==("Schedule") || e->getSource()->metaObject()->className()==("LocationManager")
             || e->getPropertyName()==(Track::LOADS_CHANGED_PROPERTY)) {
         updateLocations();
     }
 }
/*public*/ QString SchedulesByLoadFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.schedules.SchedulesByLoadFrame";
}

}
