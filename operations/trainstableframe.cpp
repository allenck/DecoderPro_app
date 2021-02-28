#include "trainstableframe.h"
#include "carmanagerxml.h"
#include "enginemanagerxml.h"
#include "trainmanagerxml.h"
#include "trainmanager.h"
#include "locationmanager.h"
#include "trainstablemodel.h"
#include <QSortFilterProxyModel>
#include <QBoxLayout>
#include "jtable.h"
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QScrollArea>
#include "setup.h"
#include <QMenu>
#include <QMenuBar>
#include "operationsmenu.h"
#include "location.h"
#include "flowlayout.h"
#include "logger.h"
#include "control.h"
#include "autosave.h"
#include <QStatusBar>
#include "autosave.h"
#include "traineditframe.h"
#include "printtrainaction.h"
#include "optionaction.h"
#include "train.h"
#include <QMessageBox>
#include "printtrainsaction.h"
#include "trainschedule.h"
#include  "trainschedulemanager.h"
#include "trainsbycartypeaction.h"
#include "printoptionaction.h"
#include "trainswitchlisteditframe.h"
#include "buildreportoptionaction.h"
#include "trainbycartypeaction.h"
#include "trainstablesetcoloraction.h"
#include "changedeparturetimesaction.h"
#include "trainsscheduleaction.h"
#include "traincopyaction.h"
#ifdef SCRIPTING_ENABLED
#include "trainsscriptaction.h"
#endif
#include "exporttrainrosteraction.h"
#include "setupexcelprogramframeaction.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Frame for adding and editing the train roster for operations.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013,
 * 2014
 * @version $Revision: 29638 $
 */
///*public*/ class TrainsTableFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 4237149773850338265L;
 /*public*/ /*static*/ /*final*/ QString TrainsTableFrame::MOVE = tr("Move");
 /*public*/ /*static*/ /*final*/ QString TrainsTableFrame::TERMINATE = tr("Terminate");
 /*public*/ /*static*/ /*final*/ QString TrainsTableFrame::RESET = tr("Reset");
 /*public*/ /*static*/ /*final*/ QString TrainsTableFrame::CONDUCTOR = tr("Conductor");


 /*public*/ TrainsTableFrame::TrainsTableFrame(QWidget* parent) : OperationsFrame(parent)
 {
  //super();
  setObjectName("TrainsTableFrame");
  log = new Logger("TrainsTableFrame");
  carManagerXml = CarManagerXml::instance(); // load cars
  engineManagerXml = ((EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml")); // load engines
  trainManager = TrainManager::instance();
  trainManagerXml = TrainManagerXml::instance();
  locationManager = LocationManager::instance();

  // labels
  numTrains = new QLabel();
  textTrains = new QLabel(tr("Trains").toLower());
  textSep1 = new QLabel("      ");

  // radio buttons
  showTime = new QRadioButton(tr("Time"));
  showId = new QRadioButton(tr("Id"));

  moveRB = new QRadioButton(MOVE);
  terminateRB = new QRadioButton(TERMINATE);
  resetRB = new QRadioButton(RESET);
  conductorRB = new QRadioButton(CONDUCTOR);

  // major buttons
  addButton = new QPushButton(tr("Add"));
  buildButton = new QPushButton(tr("Build"));
  printButton = new QPushButton(tr("Print"));
  openFileButton = new QPushButton(tr("OpenFile"));
  runFileButton = new QPushButton(tr("RunFile"));
  switchListsButton = new QPushButton(tr("SwitchLists"));
  terminateButton = new QPushButton(tr("Terminate"));
  saveButton = new QPushButton(tr("SaveBuilds"));

  // check boxes
  buildMsgBox = new QCheckBox(tr("BuildMessages"));
  buildReportBox = new QCheckBox(tr("BuildReport"));
  printPreviewBox = new QCheckBox(tr("Preview"));
  openFileBox = new QCheckBox(tr("OpenFile"));
  runFileBox = new QCheckBox(tr("RunFile"));
  showAllBox = new QCheckBox(tr("ShowAllTrains"));

  _status = 0; //TableSorter.ASCENDING;
  setStatusBar(new QStatusBar());
  statusBar()->setSizeGripEnabled(true);

  updateTitle();

  // create ShutDownTasks
  createShutDownTask();
  // always check for dirty operations files
  setModifiedFlag(true);

  // general GUI configuration
  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Set up the jtable in a Scroll Pane..
  trainsModel = new TrainsTableModel();
  sorter = new QSortFilterProxyModel(/*trainsModel*/);
  sorter->setSourceModel(trainsModel);
  trainsTable = new JTable(sorter);
  //sorter.setTableHeader(trainsTable.getTableHeader());
  //trainsPane = new JScrollPane(trainsTable);
  trainsModel->initTable(trainsTable, this);

  // Set up the control panel
  // row 1
  QWidget* cp1 = new QWidget();
  cp1->setLayout(new QVBoxLayout);//(cp1, BoxLayout.X_AXIS));

  QGroupBox* show = new QGroupBox();
  show->setLayout(new QHBoxLayout);
  show->setStyleSheet(gbStyleSheet);
  show->setTitle(tr("Click to sort"));
  //show.setBorder(BorderFactory.createTitledBorder(tr("ShowClickToSort")));
  show->layout()->addWidget(showTime);
  show->layout()->addWidget(showId);


  QGroupBox* options = new QGroupBox();
  //options.setBorder(BorderFactory.createTitledBorder(tr("Options")));
  options->setLayout(new FlowLayout);
  options->setStyleSheet(gbStyleSheet);
  options->setTitle(tr("Options"));
  options->layout()->addWidget(showAllBox);
  options->layout()->addWidget(buildMsgBox);
  options->layout()->addWidget(buildReportBox);
  options->layout()->addWidget(printPreviewBox);
  options->layout()->addWidget(openFileBox);
  options->layout()->addWidget(runFileBox);

  QGroupBox* action = new QGroupBox();
  //action.setBorder(BorderFactory.createTitledBorder(tr("Action")));
  action->setLayout(new FlowLayout);
  action->setStyleSheet(gbStyleSheet);
  action->setTitle(tr("Action"));
  action->layout()->addWidget(moveRB);
  action->layout()->addWidget(conductorRB);
  action->layout()->addWidget(terminateRB);
  action->layout()->addWidget(resetRB);

  cp1->layout()->addWidget(show);
  cp1->layout()->addWidget(options);
  cp1->layout()->addWidget(action);

  // tool tips, see setPrintButtonText() for more tool tips
  addButton->setToolTip(tr("Add Train"));
  buildButton->setToolTip(tr("Build selected trains"));
  switchListsButton->setToolTip(tr("Preview or Print Switch Lists"));

  terminateButton->setToolTip(tr("Terminate selected trains"));
  saveButton->setToolTip(tr("Save train, car, locomotive and location files"));
  openFileButton->setToolTip(tr("OpeOpen CSV manifest files for selected trainsnFileButtonTip"));
  runFileButton->setToolTip(tr("Run Excel program (Manifest Creator) for selected trains"));
  buildMsgBox->setToolTip(tr("When selected, show a message when a problem occurs"));
  printPreviewBox->setToolTip(tr("When selected, preview the manifest and build reports for a train"));
  openFileBox->setToolTip(tr("When selected, open the CSV manifest file for a train"));
  runFileBox->setToolTip(tr("When selected, run Excel program (Manifest Creator) for a train"));
  showAllBox->setToolTip(tr("When selected show all trains, unselected only show trains to build"));

  moveRB->setToolTip(tr("When selected, show Move button for train"));
  terminateRB->setToolTip(tr("When selected, show Terminate button for train"));
  resetRB->setToolTip(tr("When selected, show Reset button for train"));

  // row 2
  QGroupBox* addTrain = new QGroupBox();
  //addTrain.setBorder(BorderFactory.createTitledBorder(""));
  addTrain->setLayout(new QHBoxLayout);
  addTrain->setStyleSheet(gbStyleSheet);
  //addTrain->setTitle(tr("Options"));
  addTrain->layout()->addWidget(numTrains);
  addTrain->layout()->addWidget(textTrains);
  addTrain->layout()->addWidget(textSep1);
  addTrain->layout()->addWidget(addButton);

  numTrains->setText(QString::number(trainManager->getNumEntries()));

  QWidget* select = new QGroupBox();
  //select.setBorder(BorderFactory.createTitledBorder(""));
  select->setLayout(new QHBoxLayout);
  select->setStyleSheet(gbStyleSheet);
  //select->setTitle(tr("Options"));
  select->layout()->addWidget(buildButton);
  select->layout()->addWidget(printButton);
  select->layout()->addWidget(openFileButton);
  select->layout()->addWidget(runFileButton);
  select->layout()->addWidget(switchListsButton);
  select->layout()->addWidget(terminateButton);

  QGroupBox* save = new QGroupBox();
  save->setLayout(new QHBoxLayout);
  //save.setBorder(BorderFactory.createTitledBorder(""));
  save->layout()->addWidget(saveButton);

  QWidget* cp2 = new QWidget();
  cp2->setLayout(new QHBoxLayout); //(cp2, BoxLayout.X_AXIS));
  cp2->layout()->addWidget(addTrain);
  cp2->layout()->addWidget(select);
  cp2->layout()->addWidget(save);

  // place controls in scroll pane
  QWidget* controlPanel = new QWidget();
  controlPanel->setLayout(new QVBoxLayout); //(controlPanel, BoxLayout.Y_AXIS));
  controlPanel->layout()->addWidget(cp1);
  controlPanel->layout()->addWidget(cp2);

  QScrollArea* controlPane = new QScrollArea(/*controlPanel*/);
  controlPane->setWidget(controlPanel);
  controlPane->setWidgetResizable(true);

  thisLayout->addWidget(trainsTable);
  thisLayout->addWidget(controlPane);

  // setup buttons
  addButtonAction(addButton);
  addButtonAction(buildButton);
  addButtonAction(printButton);
  addButtonAction(openFileButton);
  addButtonAction(runFileButton);
  addButtonAction(switchListsButton);
  addButtonAction(terminateButton);
  addButtonAction(saveButton);

  QButtonGroup* showGroup = new QButtonGroup();
  showGroup->addButton(showTime);
  showGroup->addButton(showId);
  showTime->setChecked(true);

  QButtonGroup* actionGroup = new QButtonGroup();
  actionGroup->addButton(moveRB);
  actionGroup->addButton(conductorRB);
  actionGroup->addButton(terminateRB);
  actionGroup->addButton(resetRB);

  addRadioButtonAction(showTime);
  addRadioButtonAction(showId);

  addRadioButtonAction(moveRB);
  addRadioButtonAction(terminateRB);
  addRadioButtonAction(resetRB);
  addRadioButtonAction(conductorRB);

  buildMsgBox->setChecked(trainManager->isBuildMessagesEnabled());
  buildReportBox->setChecked(trainManager->isBuildReportEnabled());
  printPreviewBox->setChecked(trainManager->isPrintPreviewEnabled());
  openFileBox->setChecked(trainManager->isOpenFileEnabled());
  runFileBox->setChecked(trainManager->isRunFileEnabled());
  showAllBox->setChecked(trainsModel->isShowAll());

  // show open files only if create csv is enabled
  updateRunAndOpenButtons();

  addCheckBoxAction(buildMsgBox);
  addCheckBoxAction(buildReportBox);
  addCheckBoxAction(printPreviewBox);
  addCheckBoxAction(showAllBox);
  addCheckBoxAction(openFileBox);
  addCheckBoxAction(runFileBox);
  // Set the button text to Print or Preview
  setPrintButtonText();
  // Set the train action button text to Move or Terminate
  setTrainActionButton();

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));

  toolMenu->addAction(new OptionAction(tr("Options"), this));
  toolMenu->addAction(new PrintOptionAction(this));
  toolMenu->addAction(new BuildReportOptionAction(this));
  toolMenu->addAction(new TrainsByCarTypeAction(tr("Modify Trains by Car Type"),this));
  toolMenu->addAction(new TrainByCarTypeAction(tr("Show Car Types"), NULL, this));
  toolMenu->addAction(new ChangeDepartureTimesAction(tr("Change Departure Time"),this));
  toolMenu->addAction(new TrainsTableSetColorAction(this));
  toolMenu->addAction(new TrainsScheduleAction(tr("TimeTable"),this));
  toolMenu->addAction(new TrainCopyAction(tr("Copy Train"),this));
#ifdef SCRIPTING_ENABLED
  toolMenu->addAction(new TrainsScriptAction(tr("Scripts"), this));
#endif
  toolMenu->addAction(new SetupExcelProgramFrameAction(tr("Setup Excel Program"),this));
  toolMenu->addAction(new ExportTrainRosterAction(this));
  toolMenu->addAction(new PrintTrainsAction(tr("Print"), new JFrame(), false, this));
  toolMenu->addAction(new PrintTrainsAction(tr("Print Preview"), new JFrame(), true, this));

  menuBar->addMenu(toolMenu);
  menuBar->addMenu(new OperationsMenu());
  setMenuBar(menuBar);

  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_Trains", true); // NOI18N

  initMinimumSize();
  setFrameRef("jmri.jmrit.operations.trains.TrainsTableFrame");

  //addHorizontalScrollBarKludgeFix(controlPane, controlPanel);

  // listen for timetable changes
  //trainManager.addPropertyChangeListener(this);
  connect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
  //SetupaddPropertyChangeListener(this);
  // listen for location switch list changes
  addPropertyChangeLocations();

  // auto save
  new AutoSave();
 }

 /*public*/ void TrainsTableFrame::radioButtonActionPerformed(QWidget* ae)
 {
 QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (source == showId) {
         trainsModel->setSort(trainsModel->SORTBYID);
     }
     if (source == showTime) {
         trainsModel->setSort(trainsModel->SORTBYTIME);
     }
     if (source == moveRB) {
         trainManager->setTrainsFrameTrainAction(MOVE);
     }
     if (source == terminateRB) {
         trainManager->setTrainsFrameTrainAction(TERMINATE);
     }
     if (source == resetRB) {
         trainManager->setTrainsFrameTrainAction(RESET);
     }
     if (source == conductorRB) {
         trainManager->setTrainsFrameTrainAction(CONDUCTOR);
     }
 }


 // add, build, print, switch lists, terminate, and save buttons
 /*public*/ void TrainsTableFrame::buttonActionPerformed(QWidget* ae)
 {
  QPushButton* source = (QPushButton*)ae;
  // log->debug("train button activated");

  if (source == addButton)
  {
   new TrainEditFrame(NULL);
  }

  if (source == buildButton)
  {
   // uses a thread which allows table updates during build
   trainManager->buildSelectedTrains(getSortByList());
  }
  if (source == printButton)
  {
   trainManager->printSelectedTrains(getSortByList());
  }
  if (source == openFileButton)
  {
   // open the csv files
   QList<Train*> trains = getSortByList();
   foreach (Train* train, trains)
   {
    if (train->isBuildEnabled())
    {
     if (!train->isBuilt() && trainManager->isBuildMessagesEnabled())
     {
//                     JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
//                             .getMessage("NeedToBuildBeforeOpenFile"), new Object[]{
//                                 train.getName(),
//                                 (trainManager->->current() ? tr("preview") : Bundle
//                                         .getMessage("print"))}), MessageFormat.format(Bundle
//                                     .getMessage("CanNotPrintManifest"),
//                                     new Object[]{trainManager->isPrintPreviewEnabled() ? tr("preview")
//                                                 : tr("print")}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 train!").arg(trainManager->isPrintPreviewEnabled()?tr("preview"):tr("print")),
                            tr("Need to build train (%1) before you can %2 ").arg(train->getName()).arg(trainManager->isPrintPreviewEnabled()?tr("preview"):tr("print")));
     } else if (train->isBuilt())
     {
      train->openFile();
     }
    }
   }
  }
#if 0
  if (source == runFileButton) {
      // Processes the CSV Manifest files using an external custom program.
      if (!TrainCustomManifest.manifestCreatorFileExists()) {
          log->warn("Manifest creator file not found!, directory name: " + TrainCustomManifest.getDirectoryName()
                  + ", file name: " + TrainCustomManifest.getFileName()); // NOI18N
          JOptionPane.showMessageDialog(this, MessageFormat.format(
                  tr("LoadDirectoryNameFileName"), new Object[]{
                      TrainCustomManifest.getDirectoryName(), TrainCustomManifest.getFileName()}), Bundle
                  .getMessage("ManifestCreatorNotFound"), JOptionPane.ERROR_MESSAGE);
          return;
      }
      List<Train> trains = getSortByList();
      for (Train train : trains) {
          if (train->isBuildEnabled()) {
              if (!train->isBuilt() && trainManager->isBuildMessagesEnabled()) {
                  JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle
                          .getMessage("NeedToBuildBeforeRunFile"), new Object[]{
                              train.getName(),
                              (trainManager->isPrintPreviewEnabled() ? tr("preview") : Bundle
                                      .getMessage("print"))}), MessageFormat.format(Bundle
                                  .getMessage("CanNotPrintManifest"),
                                  new Object[]{trainManager->isPrintPreviewEnabled() ? tr("preview")
                                              : tr("print")}), JOptionPane.ERROR_MESSAGE);
              } else if (train->isBuilt()) {
                  // Make sure our csv manifest file exists for this Train.
                  File csvFile = train.createCSVManifestFile();
                  // Add it to our collection to be processed.
                  TrainCustomManifest.addCVSFile(csvFile);
              }
          }
      }

      // Now run the user specified custom Manifest processor program
      TrainCustomManifest.process();
  }
#endif
  if (source == switchListsButton)
  {
   if (tslef != NULL) {
       tslef->dispose();
   }
   tslef = new TrainSwitchListEditFrame();
   tslef->initComponents();
  }

  if (source == terminateButton) {
      trainManager->terminateSelectedTrains(getSortByList());
  }
  if (source == saveButton) {
      storeValues();
  }
 }

 /*protected*/ QString TrainsTableFrame::getSortBy() {
     // set the defaults
     QString sortBy = TrainsTableModel::TIMECOLUMNNAME;
#if 0
     _status = TableSorter.ASCENDING;
     // now look to see if a sort is active
     for (int i = 0; i < sorter.getColumnCount(); i++) {
         QString name = sorter.getColumnName(i);
         int status = sorter.getSortingStatus(i);
         // log->debug("Column " + name + " status " + status);
         if (status != TableSorter.NOT_SORTED && !name==("")) {
             sortBy = name;
             _status = status;
             break;
         }
     }
#endif
     return sortBy;
 }

 /*public*/ QList<Train*> TrainsTableFrame::getSortByList()
 {
  QList<Train*> sysList;
  QString sortBy = getSortBy();
  if (sortBy==(TrainsTableModel::IDCOLUMNNAME)) {
      sysList = trainManager->getTrainsByIdList();
  } else if (sortBy==(TrainsTableModel::TIMECOLUMNNAME)) {
      sysList = trainManager->getTrainsByTimeList();
  }
  else if (sortBy==(TrainsTableModel::DEPARTSCOLUMNNAME)) {
      sysList = trainManager->getTrainsByDepartureList();
  } else if (sortBy==(TrainsTableModel::TERMINATESCOLUMNNAME)) {
      sysList = trainManager->getTrainsByTerminatesList();
  } else if (sortBy==(TrainsTableModel::ROUTECOLUMNNAME)) {
      sysList = trainManager->getTrainsByRouteList();
  } else if (sortBy==(TrainsTableModel::STATUSCOLUMNNAME)) {
      sysList = trainManager->getTrainsByStatusList();
  }
  else {
      sysList = trainManager->getTrainsByNameList();
  }
  return sysList;
 }

 // Modifies button text and tool tips
 /*private*/ void TrainsTableFrame::setPrintButtonText() {
     if (printPreviewBox->isChecked()) {
         printButton->setText(tr("Preview"));
         printButton->setToolTip(tr("Preview manifests for selected trains"));
         buildReportBox->setToolTip(tr("When selected, preview the build report for a train"));
     } else {
         printButton->setText(tr("Print"));
         printButton->setToolTip(tr("Print manifests for selected trains"));
         buildReportBox->setToolTip(tr("When selected, print the build report for a train"));
     }
 }

 /*private*/ void TrainsTableFrame::setTrainActionButton() {
     moveRB->setChecked(trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::MOVE));
     terminateRB->setChecked(trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::TERMINATE));
     resetRB->setChecked(trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::RESET));
     conductorRB->setChecked(trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::CONDUCTOR));
 }

 /*public*/ void TrainsTableFrame::checkBoxActionPerformed(QWidget* ae) {
      QCheckBox* source = (QCheckBox*)ae;
     if (source == buildMsgBox) {
         trainManager->setBuildMessagesEnabled(buildMsgBox->isChecked());
     }
     if (source == buildReportBox) {
         trainManager->setBuildReportEnabled(buildReportBox->isChecked());
     }
     if (source == printPreviewBox) {
         trainManager->setPrintPreviewEnabled(printPreviewBox->isChecked());
         setPrintButtonText(); // set the button text for Print or Preview
     }
     if (source == openFileBox) {
         trainManager->setOpenFileEnabled(openFileBox->isChecked());
         runFileBox->setChecked(false);
         trainManager->setRunFileEnabled(false);
     }
     if (source == runFileBox) {
         trainManager->setRunFileEnabled(runFileBox->isChecked());
         openFileBox->setChecked(false);
         trainManager->setOpenFileEnabled(false);
     }
     if (source == showAllBox) {
         trainsModel->setShowAll(showAllBox->isChecked());
     }
 }

 /*private*/ void TrainsTableFrame::updateTitle() {
     QString title = tr("Trains Table");
     TrainSchedule* sch = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(trainManager->getTrainScheduleActiveId());
     if (sch != NULL) {
         title = title + " (" + sch->getName() + ")";
     }

     setTitle(title);
 }
#
 /*private*/ void TrainsTableFrame::updateSwitchListButton() {
     log->debug("update switch list button");
     QList<Location*> locations = locationManager->getList();
     foreach (Location* location, locations) {
         if (location != NULL && location->isSwitchListEnabled() && location->getStatus()==(Location::MODIFIED)) {
 // TODO:            switchListsButton->setBackground(Color.RED);
             return;
         }
     }
// TODO:     switchListsButton->setBackground(Color.GREEN);
 }

 // show open files only if create csv is enabled
 /*private*/ void TrainsTableFrame::updateRunAndOpenButtons() {
     openFileBox->setVisible(Setup::isGenerateCsvManifestEnabled());
     openFileButton->setVisible(Setup::isGenerateCsvManifestEnabled());
     runFileBox->setVisible(Setup::isGenerateCsvManifestEnabled());
     runFileButton->setVisible(Setup::isGenerateCsvManifestEnabled());
 }

 /*private*/ /*synchronized*/ void TrainsTableFrame::addPropertyChangeLocations() {
     QList<Location*> locations = locationManager->getList();
     foreach (Location* location, locations) {
         //location.addPropertyChangeListener(this);
      connect(location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));

     }
 }

 /*private*/ /*synchronized*/ void TrainsTableFrame::removePropertyChangeLocations() {
     QList<Location*> locations = locationManager->getList();
     foreach (Location* location, locations) {
         //location.removePropertyChangeListener(this);
      disconnect(location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ void TrainsTableFrame::dispose() {
     /*
      * all JMRI window position and size are now saved in user preference file
      * trainManager.setTrainsFrameTableColumnWidths(getCurrentTableColumnWidths()); // save column widths
      * trainManager.setTrainsFrame(NULL);
      */
     trainsModel->dispose();
     trainManager->runShutDownScripts();
     //trainManager.removePropertyChangeListener(this);
     disconnect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //Setup.removePropertyChangeListener(this);
     removePropertyChangeLocations();
     OperationsFrame::dispose();
 }

 /*protected*/ void TrainsTableFrame::handleModified()
 {
  if (OperationsXml::areFilesDirty())
  {
//      int result = javax.swing.JOptionPane.showOptionDialog(this,
//              tr("PromptQuitWindowNotWritten"), tr("PromptSaveQuit"),
//              javax.swing.JOptionPane.YES_NO_OPTION, javax.swing.JOptionPane.WARNING_MESSAGE, NULL, // icon
//              new String[]{ResourceBundle.getBundle("jmri.util.UtilBundle").getString("WarnYesSave"), // NOI18N
//                  ResourceBundle.getBundle("jmri.util.UtilBundle").getString("WarnNoClose")}, // NOI18N
//              ResourceBundle.getBundle("jmri.util.UtilBundle").getString("WarnYesSave"));
//      if (result == javax.swing.JOptionPane.NO_OPTION) {
   if(QMessageBox::question(this, tr("WARNING Operation files not saved!"), tr("Save?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
   {
          return;
   }
   // user wants to save
   storeValues();
  }
 }

 /*protected*/ void TrainsTableFrame::storeValues() {
     OperationsFrame::storeValues();
     saveTableDetails(trainsTable);
 }

 /*public*/ void TrainsTableFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
            ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(TrainManager::ACTIVE_TRAIN_SCHEDULE_ID)) {
         updateTitle();
     }
     if (e->getPropertyName()==(Location::STATUS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::SWITCHLIST_CHANGED_PROPERTY)) {
         updateSwitchListButton();
     }
     if (e->getPropertyName()==(Setup::MANIFEST_CSV_PROPERTY_CHANGE)) {
         updateRunAndOpenButtons();
     }
     if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)) {
         numTrains->setText(QString::number((trainManager->getNumEntries())));
     }
 }

 /*public*/ QString TrainsTableFrame::getClassName()
 {
  return "jmri.jmrit.operations.trains.schedules.TrainsTableFrame";
 }

}
