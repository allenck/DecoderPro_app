#include "trainsscheduletableframe.h"
#include "trainmanager.h"
#include "train.h"
#include "trainschedulemanager.h"
#include "trainschedule.h"
#include "locationmanager.h"
#include "location.h"
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QScrollArea>
#include "jtable.h"
#include <QLabel>
#include <QSortFilterProxyModel>
#include "flowlayout.h"
#include "trainsscheduleeditaction.h"
#include <QMenuBar>
#include <QMenu>
#include "trainsscheduletablemodel.h"
#include "setup.h"
#include "logger.h"
#include "trainswitchlists.h"
#include "operationsxml.h"
#include "control.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Frame for adding and editing train schedules (Timetable) for operations.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010, 2012
  * @version $Revision: 29599 $
  */
 ///*public*/ class TrainsScheduleTableFrame extends OperationsFrame implements PropertyChangeListener {

 // /*public*/ static SwingShutDownTask trainDirtyTask;
 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -2436589778859368847L;
 /*public*/ /*static*/ /*final*/ QString TrainsScheduleTableFrame::NAME = tr("Name"); // Sort by choices
 /*public*/ /*static*/ /*final*/ QString TrainsScheduleTableFrame::TIME = tr("Time");


 /*public*/ TrainsScheduleTableFrame::TrainsScheduleTableFrame(QWidget* parent) : OperationsFrame(parent)
 {
  log = new Logger("TrainsScheduleTableFrame");
  trainManager = ((TrainManager*)InstanceManager::getDefault("TrainManager"));
  scheduleManager = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"));
  locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));

  trainsScheduleModel = new TrainsScheduleTableModel();
  trainsScheduleTable = new JTable(trainsScheduleModel);

  // labels
  textSort = new QLabel(tr("Sort By"));

  // radio buttons
  sortByName = new QRadioButton(NAME);
  sortByTime = new QRadioButton(TIME);

  noneButton = new QRadioButton(tr("None"));

  // radio button groups
  schGroup = new QButtonGroup();

  // major buttons
  selectButton = new QPushButton(tr("Select"));
  clearButton = new QPushButton(tr("Clear"));

  applyButton = new QPushButton(tr("Apply"));
  buildButton = new QPushButton(tr("Build"));
  printButton = new QPushButton(tr("Print"));
  switchListsButton = new QPushButton();
  terminateButton = new QPushButton(tr("Terminate"));

  activateButton = new QPushButton(tr("Activate"));
  saveButton = new QPushButton(tr("Save"));

  // check boxes
  // panel
  schedule = new JPanel();

     // general GUI configuration
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // Set up the jtable in a Scroll Pane..
     //trainsPane = new JScrollPane(trainsScheduleTable);
//     trainsPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     trainsPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
     trainsScheduleModel->initTable(trainsScheduleTable, this);

     // Set up the control panel
     // row 1
     QWidget* cp1 = new QWidget();
     cp1->setLayout(new QHBoxLayout); //(cp1, BoxLayout.X_AXIS));

     // row 1
     JPanel* sortBy = new JPanel();
     sortBy->setLayout(new FlowLayout);
     sortBy->setBorder(BorderFactory::createTitledBorder(tr("Sort By")));
     sortBy->layout()->addWidget(sortByTime);
     sortBy->layout()->addWidget(sortByName);

     // row 2
     schedule->setBorder(BorderFactory::createTitledBorder(tr("Active")));
     schedule->setLayout(new QHBoxLayout);

     updateControlPanel();

     cp1->layout()->addWidget(sortBy);
     cp1->layout()->addWidget(schedule);

     QWidget* pButtons = new QWidget();
     pButtons->setLayout(new QHBoxLayout);//(pButtons, BoxLayout.X_AXIS));

     JPanel* cp3 = new JPanel();
     cp3->setLayout(new FlowLayout);
     cp3->setBorder(BorderFactory::createTitledBorder(""));
     //cp3->setTitle(tr(""));
     cp3->layout()->addWidget(clearButton);
     cp3->layout()->addWidget(selectButton);

     JPanel* cp4 = new JPanel();
     cp4->setLayout(new FlowLayout);
     cp4->setBorder(BorderFactory::createTitledBorder(""));
     //cp4->setTitle(tr(""));
     cp4->layout()->addWidget(applyButton);
     cp4->layout()->addWidget(buildButton);
     cp4->layout()->addWidget(printButton);
     cp4->layout()->addWidget(switchListsButton);
     cp4->layout()->addWidget(terminateButton);

     JPanel* cp5 = new JPanel();
     cp5->setLayout(new FlowLayout);
     cp5->setBorder(BorderFactory::createTitledBorder(""));
     //cp5->setTitle(tr(""));
     cp5->layout()->addWidget(activateButton);
     cp5->layout()->addWidget(saveButton);

     pButtons->layout()->addWidget(cp3);
     pButtons->layout()->addWidget(cp4);
     pButtons->layout()->addWidget(cp5);

     // tool tips
     selectButton->setToolTip(tr("Selects all checkboxes for the selected timetable"));
     clearButton->setToolTip(tr("Clears all checkboxes for the selected timetable"));
     applyButton->setToolTip(tr("Select one of the active radio buttons before pressing"));
     activateButton->setToolTip(tr("Makes the selected radio button the active timetable"));

     setPrintButtonText();
     setSwitchListButtonText();

     // place controls in scroll pane
     QWidget* controlPanel = new QWidget();
     controlPanel->setLayout(new QVBoxLayout); //(controlPanel, BoxLayout.Y_AXIS));
     controlPanel->layout()->addWidget(cp1);
     controlPanel->layout()->addWidget(pButtons);

     QScrollArea* controlPane = new QScrollArea(/*controlPanel*/);
     // make sure control panel is the right size
     controlPane->setWidget(controlPanel);
     controlPane->setWidgetResizable(true);
     controlPane->setMinimumSize(QSize(500, 130));
     controlPane->setMaximumSize(QSize(2000, 200));
     //controlPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);

     thisLayout->addWidget(trainsScheduleTable);
     thisLayout->addWidget(controlPane);

     // setup buttons
     addButtonAction(clearButton);
     addButtonAction(selectButton);
     addButtonAction(applyButton);
     addButtonAction(buildButton);
     addButtonAction(printButton);
     addButtonAction(switchListsButton);
     addButtonAction(terminateButton);
     addButtonAction(activateButton);
     addButtonAction(saveButton);

     QButtonGroup* sortGroup = new QButtonGroup();
     sortGroup->addButton(sortByTime);
     sortGroup->addButton(sortByName);
     sortByTime->setChecked(true);

     addRadioButtonAction(sortByTime);
     addRadioButtonAction(sortByName);

     addRadioButtonAction(noneButton);

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
     toolMenu->addAction(new TrainsScheduleEditAction(this));
     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_Timetable", true); // NOI18N

     setTitle(tr("TimeTable"));

     initMinimumSize();

     //addHorizontalScrollBarKludgeFix(controlPane, controlPanel);

    // Setup.addPropertyChangeListener(this);
     //trainManager.addPropertyChangeListener(this);
     connect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //scheduleManager.addPropertyChangeListener(this);
     connect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     addPropertyChangeLocations();
     addPropertyChangeTrainSchedules();
 }

 /*public*/ void TrainsScheduleTableFrame::radioButtonActionPerformed(QWidget* ae)
 {
 QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (source == sortByName) {
         trainsScheduleModel->setSort(TrainsScheduleTableModel::SORTBYNAME);
     } else if (source == sortByTime) {
         trainsScheduleModel->setSort(TrainsScheduleTableModel::SORTBYTIME);
     } else if (source == noneButton) {
         enableButtons(false);
         // must be one of the schedule radio buttons
     } else {
         enableButtons(true);
     }
 }

 // add, build, print, switch lists, terminate, and save buttons
 /*public*/ void TrainsScheduleTableFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     log->debug("button activated");
     if (source == clearButton) {
         updateCheckboxes(false);
     }
     if (source == selectButton) {
         updateCheckboxes(true);
     }
     if (source == applyButton) {
         applySchedule();
     }
     if (source == buildButton) {
         switchListsButton->setEnabled(false);
         // uses a thread which allows table updates during build
         trainManager->buildSelectedTrains(getSortByList());
     }
     if (source == printButton) {
         trainManager->printSelectedTrains(getSortByList());
     }
     if (source == switchListsButton) {
         buildSwitchList();
     }
     if (source == terminateButton) {
         trainManager->terminateSelectedTrains(getSortByList());
     }
     if (source == activateButton) {
         trainManager->setTrainSecheduleActiveId(getSelectedScheduleId());
         activateButton->setEnabled(false);
     }
     if (source == saveButton) {
         storeValues();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 /*
  * Update radio button names in the same order was the table
  */
 /*private*/ void TrainsScheduleTableFrame::updateControlPanel()
 {
     //schedule.removeAll();
  QLayoutItem* item;
  while ( ( item = schedule->layout()->takeAt( 0 ) ) != NULL )
  {
      delete item->widget();
      delete item;
  }
  noneButton = new QRadioButton(tr("None"));

  noneButton->setObjectName(""); // Name holds schedule id for the selected radio button
  noneButton->setChecked(true);
  enableButtons(false);
  schedule->layout()->addWidget(noneButton);
  schGroup->addButton(noneButton);

  for (int i = trainsScheduleModel->getFixedColumn(); i < trainsScheduleModel->columnCount(QModelIndex()); i++)
  {
   QString columnName = trainsScheduleTable->model()->headerData(i, Qt::Horizontal,Qt::DisplayRole).toString();
   log->debug(tr("Column name: %1").arg(columnName));
   TrainSchedule* ts = scheduleManager->getScheduleByName(columnName);
   if (ts != NULL)
   {
    QRadioButton* b = new QRadioButton();
    b->setText(ts->getName());
    b->setObjectName(ts->getId());
    schedule->layout()->addWidget(b);
    schGroup->addButton(b);
    addRadioButtonAction(b);
    if (b->objectName()==(trainManager->getTrainScheduleActiveId()))
    {
     b->setChecked(true);
     enableButtons(true);
    }
   }
  }
  schedule->update();
 }

 /*private*/ void TrainsScheduleTableFrame::updateCheckboxes(bool selected) {
     TrainSchedule* ts = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(getSelectedScheduleId());
     if (ts != NULL) {
         foreach (Train* train, trainManager->getTrainsByIdList()) {
             if (selected) {
                 ts->addTrainId(train->getId());
             } else {
                 ts->removeTrainId(train->getId());
             }
         }
     }
 }

 /*private*/ void TrainsScheduleTableFrame::applySchedule() {
     TrainSchedule* ts = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(getSelectedScheduleId());
     if (ts != NULL) {
         foreach (Train* train, trainManager->getTrainsByIdList()) {
             train->setBuildEnabled(ts->containsTrainId(train->getId()));
         }
     }
 }

 /*private*/ QString TrainsScheduleTableFrame::getSelectedScheduleId() {
     QAbstractButton* b;
     QListIterator<QAbstractButton*> en = schGroup->buttons();
     while (en.hasNext()) {
         b = en.next();
         if (b->isChecked()) {
             log->debug("schedule radio button " + b->text());
             return b->objectName();
         }
     }
     return NULL;
 }

 /*private*/ void TrainsScheduleTableFrame::enableButtons(bool enable) {
     selectButton->setEnabled(enable);
     clearButton->setEnabled(enable);
     applyButton->setEnabled(enable);
     buildButton->setEnabled(enable);
     printButton->setEnabled(enable);
     switchListsButton->setEnabled(enable);
     terminateButton->setEnabled(enable);

     log->debug(tr("Selected id: %1, Active id:%2").arg(getSelectedScheduleId()).arg(trainManager->getTrainScheduleActiveId()));

     activateButton->setEnabled(getSelectedScheduleId() != NULL
             && getSelectedScheduleId()!=(trainManager->getTrainScheduleActiveId()));
 }

 /*private*/ QList<Train*> TrainsScheduleTableFrame::getSortByList() {
     if (sortByTime->isChecked()) {
         return trainManager->getTrainsByTimeList();
     } else {
         return trainManager->getTrainsByNameList();
     }
 }

 /*private*/ void TrainsScheduleTableFrame::setSwitchListButtonText() {
     if (!Setup::isSwitchListRealTime()) {
         switchListsButton->setText(tr("Update"));
     } else if (trainManager->isPrintPreviewEnabled()) {
         switchListsButton->setText(tr("Preview Switch Lists"));
     } else {
         switchListsButton->setText(tr("Print Switch Lists"));
     }
 }

 // Modifies button text and tool tips
 /*private*/ void TrainsScheduleTableFrame::setPrintButtonText() {
     if (trainManager->isPrintPreviewEnabled()) {
         printButton->setText(tr("Preview"));
         printButton->setToolTip(tr("Preview manifests for selected trains"));
     } else {
         printButton->setText(tr("Print"));
         printButton->setToolTip(tr("Print manifests for selected trains"));
     }
 }

 /*private*/ void TrainsScheduleTableFrame::buildSwitchList() {
     TrainSwitchLists* trainSwitchLists = new TrainSwitchLists();
     foreach (Location* location, locationManager->getLocationsByNameList()) {
         if (location->isSwitchListEnabled()) {
             trainSwitchLists->buildSwitchList(location);
             // // print or print changes
             if (Setup::isSwitchListRealTime() && location->getStatus()!=(Location::PRINTED)) {
                 trainSwitchLists->printSwitchList(location, ((TrainManager*)InstanceManager::getDefault("TrainManager"))->isPrintPreviewEnabled());
             }
         }
     }
     // set trains switch lists printed
     ((TrainManager*)InstanceManager::getDefault("TrainManager"))->setTrainsSwitchListStatus(Train::PRINTED);
 }

 /*private*/ void TrainsScheduleTableFrame::updateSwitchListButton() {
     log->debug("update switch list button");
     QList<Location*> locations = locationManager->getList();
     foreach (Location* location, locations) {
         if (location != NULL && location->isSwitchListEnabled() && location->getStatus()==(Location::MODIFIED)) {
             //switchListsButton->setBackground(Qt::red);
          switchListsButton->setStyleSheet("QPushButton {background-color: red; border: none");
             return;
         }
     }
     //switchListsButton->setBackground(Qt::green);
     switchListsButton->setStyleSheet("QPushButton {background-color: green; border: none");
 }

 /*protected*/ void TrainsScheduleTableFrame::storeValues() {
     updateControlPanel();
     saveTableDetails(trainsScheduleTable);
     OperationsXml::save();
 }

 /*public*/ void TrainsScheduleTableFrame::dispose() {
     //Setup.removePropertyChangeListener(this);
     //trainManager.removePropertyChangeListener(this);
 disconnect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //scheduleManager.removePropertyChangeListener(this);
 disconnect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeTrainSchedules();
     removePropertyChangeLocations();
     trainsScheduleModel->dispose();
     OperationsFrame::dispose();
 }

 /*private*/ void TrainsScheduleTableFrame::addPropertyChangeLocations() {
     foreach (Location* location, locationManager->getList()) {
      location->addPropertyChangeListener(this);
     }
 }

 /*private*/ void TrainsScheduleTableFrame::removePropertyChangeLocations() {
     foreach (Location* location, locationManager->getList()) {
         location->removePropertyChangeListener(this);
     }
 }

 /*private*/ void TrainsScheduleTableFrame::addPropertyChangeTrainSchedules() {
     QList<TrainSchedule*> trainSchedules = scheduleManager->getSchedulesByIdList();
     foreach (TrainSchedule* ts, trainSchedules) {
         //ts.addPropertyChangeListener(this);
      connect(ts->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*private*/ void TrainsScheduleTableFrame::removePropertyChangeTrainSchedules() {
     QList<TrainSchedule*> trainSchedules = scheduleManager->getSchedulesByIdList();
     foreach (TrainSchedule* ts, trainSchedules) {
         //ts.removePropertyChangeListener(this);
         disconnect(ts->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ void TrainsScheduleTableFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY)
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     if (e->getPropertyName()==(TrainScheduleManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(TrainSchedule::NAME_CHANGED_PROPERTY)) {
         updateControlPanel();
     }
     if (e->getPropertyName()==(TrainManager::PRINTPREVIEW_CHANGED_PROPERTY)) {
         setPrintButtonText();
         setSwitchListButtonText();
     }
     if (e->getPropertyName()==(TrainManager::TRAINS_BUILT_CHANGED_PROPERTY)) {
         switchListsButton->setEnabled(true);
     }
     if (e->getPropertyName()==(Setup::REAL_TIME_PROPERTY_CHANGE)) {
         setSwitchListButtonText();
     }
     if (e->getPropertyName()==(Location::STATUS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::SWITCHLIST_CHANGED_PROPERTY)) {
         updateSwitchListButton();
     }
 }
/*public*/ QString TrainsScheduleTableFrame::getClassName()
{
 return "jmri.jmrit.operations.operations.trains.schedules.TrainsScheduleTableFrame";
}

}
