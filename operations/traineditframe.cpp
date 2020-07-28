#include "traineditframe.h"
#include "train.h"
#include "trainmanager.h"
#include "routemanager.h"
#include "jcombobox.h"
#include <QBoxLayout>
#include "route.h"
#include "location.h"
#include "track.h"
#include "setup.h"
#include "control.h"
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include "gridbaglayout.h"
#include "jtextfield.h"
#include "cartypes.h"
#include "jtextarea.h"
#include "enginemodels.h"
#include <QScrollArea>
#include <QGroupBox>
#include "routelocation.h"
#include <QMenu>
#include <QMenuBar>
#include "propertychangeevent.h"
#include "enginetypes.h"
#include "locationmanager.h"
#include <QLabel>
#include <vptr.h>
#include "routeeditframe.h"
#include "carroads.h"
#include "logger.h"
#include "carmanager.h"
#include "vptr.h"
#include "gridbagconstraints.h"
#include "enginemanager.h"
#include "operationsxml.h"
#include <QMessageBox>
#include "rollingstock.h"
#include "trainconductoraction.h"
#include "routeeditframe.h"
#include "printtrainaction.h"
#include "trackroadeditaction.h"
#include "htmltextedit.h"
#include "printtrainbuildreportaction.h"
#include "printtrainmanifestaction.h"
#include "traineditbuildoptionsaction.h"
#include "traincopyaction.h"
#include "trainloadoptionsaction.h"
#include "trainroadoptionsaction.h"
#include "trainmanifestoptionaction.h"
#include "trainbycartypeaction.h"
#include "trainscriptaction.h"

namespace Operations
{
/**
 * Frame for user edit of a train
 *
 * @author Dan Boudreau Copyright (C) 2008, 2011, 2012, 2013, 2014
 * @version $Revision: 29638 $
 */
///*public*/ class TrainEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 5151081816323580604L;

 /*public*/ /*static*/ /*final*/ QString TrainEditFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ TrainEditFrame::TrainEditFrame(Train* train, QWidget* parent)
     : OperationsFrame(tr("Edit Train"), parent)
 {
  //super(tr("TitleTrainEdit"));
  log = new Logger("TrainEditFrame");
   typeCarCheckBoxes = QList<QCheckBox*>();
  typeEngineCheckBoxes = QList<QCheckBox*>();
   locationCheckBoxes = QList<QCheckBox*>();
  typeCarPanelCheckBoxes = new QWidget();
  typeCarPanelCheckBoxes->setObjectName("typeCarPanelCheckBoxes");
  typeEnginePanelCheckBoxes = new QWidget();
  roadAndLoadStatusPanel = new QWidget();
  locationPanelCheckBoxes = new QWidget();

  // labels
  textRouteStatus = new QLabel();
  loadOption = new QLabel();
  roadOption = new QLabel();
  textModel = new QLabel(tr("Model"));
  textRoad2 = new QLabel(tr("Road"));
  textRoad3 = new QLabel(tr("Road"));
  textEngine = new QLabel(tr("Engines"));

  // major buttons
  editButton = new QPushButton(tr("Edit"));	// edit route
  clearButton = new QPushButton(tr("Clear"));
  setButton = new QPushButton(tr("Select"));
  resetButton = new QPushButton(tr("Reset Train"));
  saveTrainButton = new QPushButton(tr("Save Train"));
  deleteTrainButton = new QPushButton(tr("Delete Train"));
  addTrainButton = new QPushButton(tr("Add Train"));

  // radio buttons
  noneRadioButton = new QRadioButton(tr("None"));
  cabooseRadioButton = new QRadioButton(tr("Caboose"));
  fredRadioButton = new QRadioButton(tr("FRED"));
  group = new QButtonGroup();

  // text field
  trainNameTextField = new JTextField(Control::max_len_string_train_name - 5); // make slightly smaller
  trainDescriptionTextField = new JTextField(30);

  // text area
  commentTextArea = new HtmlTextEdit();
 // commentTextArea = new JTextArea(2, 70);
//  commentScroller = new JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//          JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  // for padding out panel
  space1 = new QLabel("       ");
  space2 = new QLabel("       "); // between hour and minute
  space3 = new QLabel("       ");
  space4 = new QLabel("       ");
  space5 = new QLabel("       ");

  // combo boxes
   hourBox = new JComboBox();
   minuteBox = new JComboBox();
   routeBox = RouteManager::instance()->getComboBox();
   roadCabooseBox = new JComboBox();
   roadEngineBox = new JComboBox();
   modelEngineBox = EngineModels::instance()->getComboBox();
   numEnginesBox = new JComboBox();
   ref = NULL;

  // Set up the jtable in a Scroll Pane..
  QGroupBox* locationsPaneFrame = new QGroupBox;
  locationsPaneFrame->setObjectName("locationsPaneFrame");
  locationsPaneFrame->setLayout(new QVBoxLayout);
  locationsPane = new QScrollArea(/*locationPanelCheckBoxes*/);
  //locationsPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  //locationsPane->setBorder(BorderFactory.createTitledBorder(tr("Stops")));
  locationsPaneFrame->setStyleSheet(gbStyleSheet);
  locationsPaneFrame->setTitle(tr("Stops"));
  locationsPaneFrame->layout()->addWidget(locationsPane);
  locationsPane->setWidgetResizable(true);

  QGroupBox* typeCarPaneFrame = new QGroupBox;
  typeCarPaneFrame->setObjectName("typeCarPaneFrame");
  typeCarPaneFrame->setLayout(new QVBoxLayout);
  typeCarPane = new QScrollArea(/*typeCarPanelCheckBoxes*/);
  //typeCarPane->setBorder(BorderFactory.createTitledBorder(tr("TypesCar")));
  typeCarPaneFrame->setStyleSheet(gbStyleSheet);
  typeCarPaneFrame->setTitle(tr("Car Types"));
  //typeCarPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  typeCarPaneFrame->layout()->addWidget(typeCarPane);
  typeCarPane->setWidgetResizable(true);

  QGroupBox* typeEnginePaneFrame = new QGroupBox;
  typeEnginePaneFrame->setObjectName("typeEnginePaneFrame");
  typeEnginePaneFrame->setLayout(new QVBoxLayout);
  typeEnginePane = new QScrollArea(/*typeEnginePanelCheckBoxes*/);
  //typeEnginePane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  //typeEnginePane->setBorder(BorderFactory.createTitledBorder(tr("TypesEngine")));
  typeEnginePaneFrame->setStyleSheet(gbStyleSheet);
  typeEnginePaneFrame->setTitle(tr("Engine Types"));
  typeEnginePaneFrame->layout()->addWidget(typeEnginePane);
  typeEnginePane->setWidgetResizable(true);

  _train = train;

  // load managers
  trainManager = TrainManager::instance();
  routeManager = RouteManager::instance();
  boxMapper = new QSignalMapper();
  connect(boxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(locationCheckBoxActionPerformed(QWidget*)));
  typeCheckBoxMapper = new QSignalMapper;
  connect(typeCheckBoxMapper, SIGNAL(mapped(QWidget*)), this, SLOT(typeCheckBoxActionPerformed(QWidget*)));
  children = QList<JmriJFrame*>();


  //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Set up the panels
  QWidget* p = new QWidget();
  p->setLayout(new QVBoxLayout); //(p, BoxLayout.Y_AXIS));
  QScrollArea* pPane = new QScrollArea(/*p*/);
  pPane->setMinimumSize(QSize(300, 5 * trainNameTextField->sizeHint().height()));
  //pPane->setBorder(BorderFactory.createTitledBorder(""));
  pPane->setFrameStyle(QFrame::Panel | QFrame::Plain);
  // Layout the panel by rows
  // row 1
  QWidget* p1 = new QWidget();
  p1->setLayout(new QHBoxLayout);//(p1, BoxLayout.X_AXIS));
  // row 1a
  QGroupBox* pName = new QGroupBox();
  pName->setObjectName("pName");
  pName->setLayout(new GridBagLayout());
  //pName->setBorder(BorderFactory.createTitledBorder(tr("Name")));
  pName->setStyleSheet(gbStyleSheet);
  pName->setTitle(tr("Name"));
  addItem(pName, trainNameTextField, 0, 0);
  // row 1b
  QGroupBox* pDesc = new QGroupBox();
  pDesc->setObjectName("pDesc");
  pDesc->setLayout(new GridBagLayout());
  //pDesc->setBorder(BorderFactory.createTitledBorder(tr("Description")));
  pDesc->setStyleSheet(gbStyleSheet);
  pDesc->setTitle(tr("Description"));
  trainDescriptionTextField->setToolTip("%1 = lead engine number, %2 = departure direction, %3 = lead engine road");
  addItem(pDesc, trainDescriptionTextField, 0, 0);

  p1->layout()->addWidget(pName);
  p1->layout()->addWidget(pDesc);

  // row 2
  QWidget* p2 = new QWidget();
  p2->setLayout(new QHBoxLayout);//(p2, BoxLayout.X_AXIS));
  // row 2a
  QGroupBox* pdt = new QGroupBox();
  pdt->setObjectName("pdt");
  pdt->setLayout(new GridBagLayout());
  //pdt->setBorder(BorderFactory.createTitledBorder(tr("DepartTime")));
  pdt->setStyleSheet(gbStyleSheet);
  pdt->setTitle(tr("Depart time"));
  // build hour and minute menus
  for (int i = 0; i < 24; i++) {
      if (i < 10) {
          hourBox->addItem("0" + QString::number(i));
      } else {
          hourBox->addItem(QString::number(i));
      }
  }
  hourBox->setMinimumSize(QSize(100, 25));

  for (int i = 0; i < 60; i += 5) {
      if (i < 10) {
          minuteBox->addItem("0" + QString::number(i));
      } else {
          minuteBox->addItem(QString::number(i));
      }
  }
  addItem(pdt, space1, 0, 5);
  addItem(pdt, hourBox, 1, 5);
  addItem(pdt, space2, 2, 5);
  addItem(pdt, minuteBox, 3, 5);
  addItem(pdt, space3, 4, 5);

  // row 2b
  // BUG! routeBox needs its own panel when resizing frame!
  QGroupBox* pr = new QGroupBox();
  pr->setObjectName("pr");
  pr->setLayout(new GridBagLayout());
  //pr->setBorder(BorderFactory.createTitledBorder(tr("Route")));
  pr->setStyleSheet(gbStyleSheet);
  pr->setTitle(tr("Route"));
  addItem(pr, routeBox, 0, 5);
  addItem(pr, space4, 1, 5);
  addItem(pr, editButton, 2, 5);
  addItem(pr, space5, 3, 5);
  addItem(pr, textRouteStatus, 4, 5);

  p2->layout()->addWidget(pdt);
  p2->layout()->addWidget(pr);

  p->layout()->addWidget(p1);
  p->layout()->addWidget(p2);

  // row 5
  locationPanelCheckBoxes->setLayout(new GridBagLayout());

  // row 6
  typeCarPanelCheckBoxes->setLayout(new GridBagLayout());

  // row 8
  typeEnginePanelCheckBoxes->setLayout(new GridBagLayout());

  // status panel for roads and loads
  roadAndLoadStatusPanel->setLayout(new QHBoxLayout); //(roadAndLoadStatusPanel, BoxLayout.X_AXIS));
  QGroupBox* pRoadOption = new QGroupBox();
  pRoadOption->setObjectName("pRoadOption");
  pRoadOption->setLayout(new QVBoxLayout);
  //pRoadOption->setBorder(BorderFactory.createTitledBorder(tr("RoadOption")));
  pRoadOption->setStyleSheet(gbStyleSheet);
  pRoadOption->setTitle(tr("Road Option"));
  pRoadOption->layout()->addWidget(roadOption);

  QGroupBox* pLoadOption = new QGroupBox();
  pLoadOption->setObjectName("pLoadOption");
  pLoadOption->setLayout(new QVBoxLayout);
  //pLoadOption->setBorder(BorderFactory.createTitledBorder(tr("LoadOption")));
  pLoadOption->setStyleSheet(gbStyleSheet);
  pLoadOption->setTitle(tr("Load Option"));
  pLoadOption->layout()->addWidget(loadOption);

  roadAndLoadStatusPanel->layout()->addWidget(pRoadOption);
  roadAndLoadStatusPanel->layout()->addWidget(pLoadOption);
  roadAndLoadStatusPanel->setVisible(false); // don't show unless there's a restriction

  // row 10
  QGroupBox* trainReq = new QGroupBox();
  trainReq->setObjectName("trainReq");
  trainReq->setLayout(new GridBagLayout());
  //trainReq->setBorder(BorderFactory.createTitledBorder(tr("TrainRequires")));
  trainReq->setStyleSheet(gbStyleSheet);
  trainReq->setTitle(tr("Optional train requirements"));

  for (int i = 0; i < Setup::getMaxNumberEngines() + 1; i++) {
      numEnginesBox->addItem(QString::number(i));
  }
  numEnginesBox->addItem(Train::AUTO);
  numEnginesBox->setMinimumSize(QSize(65, 20));
  numEnginesBox->setToolTip(tr("Select the number of locomotives for this train"));
  addItem(trainReq, textEngine, 1, 1);
  addItem(trainReq, numEnginesBox, 2, 1);
  addItem(trainReq, textModel, 3, 1);
  modelEngineBox->insertItem(0,NONE);
  modelEngineBox->setCurrentIndex(0);
  modelEngineBox->setMinimumSize(QSize(120, 20));
  modelEngineBox->setToolTip(tr("Optionally select locomotive model"));
  addItem(trainReq, modelEngineBox, 4, 1);
  addItem(trainReq, textRoad2, 5, 1);
  roadEngineBox->insertItem(0,NONE);
  roadEngineBox->setCurrentIndex(0);
  roadEngineBox->setMinimumSize(QSize(120, 20));
  roadEngineBox->setToolTip(tr("Optionally select locomotive road name"));
  addItem(trainReq, roadEngineBox, 6, 1);

  addItem(trainReq, noneRadioButton, 2, 2);
  noneRadioButton->setToolTip(tr("Caboose or FRED not required for train"));
  addItem(trainReq, fredRadioButton, 3, 2);
  fredRadioButton->setToolTip(tr("Last car on the train must have a Flashing Rear End Device (FRED)"));
  addItem(trainReq, cabooseRadioButton, 4, 2);
  cabooseRadioButton->setToolTip(tr("Last car on the train must be a caboose"));
  addItem(trainReq, textRoad3, 5, 2);
  roadCabooseBox->setMinimumSize(QSize(120, 20));
  roadCabooseBox->setToolTip(tr("Optionally select road name for caboose or FRED"));
  addItem(trainReq, roadCabooseBox, 6, 2);
  group->addButton(noneRadioButton);
  group->addButton(cabooseRadioButton);
  group->addButton(fredRadioButton);
  noneRadioButton->setChecked(true);

  // row 13 comment
  QGroupBox* pC = new QGroupBox();
  pC->setObjectName("pC");
  //pC->setBorder(BorderFactory.createTitledBorder(tr("Comment")));
  pC->setStyleSheet(gbStyleSheet);
  pC->setTitle(tr("Comment"));
  pC->setLayout(new GridBagLayout());
  addItem(pC, /*commentScroller*/commentTextArea, 1, 0);

  // adjust text area width based on window size
  adjustTextAreaColumnWidth(/*commentScroller*/pC, commentTextArea);

  // row 15 buttons
  QWidget* pB = new QWidget();
  pB->setLayout(new GridBagLayout());
  addItem(pB, deleteTrainButton, 0, 0);
  addItem(pB, resetButton, 1, 0);
  addItem(pB, addTrainButton, 2, 0);
  addItem(pB, saveTrainButton, 3, 0);

  pPane->setWidget(p);
  thisLayout->addWidget(pPane);
  locationsPane->setWidget(locationPanelCheckBoxes);
  thisLayout->addWidget(/*locationsPane*/locationsPaneFrame);
  typeCarPane->setWidget(typeCarPanelCheckBoxes);
  thisLayout->addWidget(/*typeCarPane*/typeCarPaneFrame);
  typeEnginePane->setWidget(typeEnginePanelCheckBoxes);
  thisLayout->addWidget(/*typeEnginePane*/typeEnginePaneFrame);
  thisLayout->addWidget(roadAndLoadStatusPanel);
  thisLayout->addWidget(trainReq);
  thisLayout->addWidget(pC);
  thisLayout->addWidget(pB);

  // setup buttons
  addButtonAction(editButton);
  addButtonAction(setButton);
  addButtonAction(clearButton);
  addButtonAction(resetButton);
  addButtonAction(deleteTrainButton);
  addButtonAction(addTrainButton);
  addButtonAction(saveTrainButton);

  addRadioButtonAction(noneRadioButton);
  addRadioButtonAction(cabooseRadioButton);
  addRadioButtonAction(fredRadioButton);

  // tool tips
  resetButton->setToolTip(tr("Remove rolling stock assigned to this train"));

  if (_train != NULL) {
      trainNameTextField->setText(_train->getName());
      trainDescriptionTextField->setText(_train->getRawDescription());
      routeBox->setCurrentIndex(routeBox->findData(VPtr<Route>::asQVariant(_train->getRoute())));
      modelEngineBox->setCurrentIndex(modelEngineBox->findText(_train->getEngineModel()));
      commentTextArea->setText(_train->getComment(false));
      cabooseRadioButton->setChecked((_train->getRequirements() & Train::CABOOSE) > 0);
      fredRadioButton->setChecked((_train->getRequirements() & Train::FRED) > 0);
      updateDepartureTime();
      enableButtons(true);
      // listen for train changes
      //_train->addPropertyChangeListener(this);
      connect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
      // listen for route changes
      Route* route = _train->getRoute();
      if (route != NULL) {
          //route.addPropertyChangeListener(this);
       connect(route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
           if(_train->getTrainDepartsRouteLocation() != NULL && !_train->getTrainDepartsRouteLocation()->getLocation()->isStaging())
              numEnginesBox->addItem(Train::AUTO_HPT);
      }
     numEnginesBox->setCurrentIndex(numEnginesBox->findText(_train->getNumberEngines()));
  } else {
      setTitle(tr("Add Train"));
      enableButtons(false);
  }

  modelEngineBox->setEnabled(numEnginesBox->currentText()!=("0"));
  roadEngineBox->setEnabled(numEnginesBox->currentText()!=("0"));

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));

  toolMenu->addAction(new TrainEditBuildOptionsAction(tr("Build Options"), this));
  toolMenu->addAction(new TrainLoadOptionsAction(tr("Load Options"), this));
  toolMenu->addAction(new TrainRoadOptionsAction(tr("Road Options"), this));
  toolMenu->addAction(new TrainManifestOptionAction(tr("Options"), this));
  if (_train != NULL) {
      toolMenu->addAction(new TrainCopyAction(tr("Copy Train"), _train, this));
  }
  toolMenu->addAction(new TrainScriptAction(tr("Scripts"), this));
  toolMenu->addAction(new TrainByCarTypeAction(tr("Show Car Types"), _train, this));
  if (_train != NULL) {
      toolMenu->addAction(new TrainConductorAction(tr("Train Conductor"), _train, this));
  }

  toolMenu->addAction(new PrintTrainAction(tr("Print"), new JFrame(), false, this));
  toolMenu->addAction(new PrintTrainAction(tr("Preview"), new JFrame(), true, this));
  toolMenu->addAction(new PrintTrainManifestAction(tr("Print Manifest"), false, this));
  toolMenu->addAction(new PrintTrainManifestAction(tr("Preview Manifest"), true, this));
  toolMenu->addAction(new PrintTrainBuildReportAction(tr("Print Build Report"), false, this));
  toolMenu->addAction(new PrintTrainBuildReportAction(tr("Preview Build Report"), true, this));
  menuBar->addMenu(toolMenu);
  setMenuBar(menuBar);
  addHelpMenu("package.jmri.jmrit.operations.Operations_TrainEdit", true); // NOI18N
  // load route location checkboxes
  updateLocationCheckboxes();
  //log->debug(tr("locationPanelCheckboxes has %1 boxes").arg(locationPanelCheckBoxes->layout()->children().count()));
  updateCarTypeCheckboxes();
  //log->debug(tr("typeCarPanelCheckBoxes has %1 boxes").arg(typeCarPanelCheckBoxes->layout()->children().count()));
  updateEngineTypeCheckboxes();
  //log->debug(tr("typeEnginePanelCheckBoxes has %1 boxes").arg(typeEnginePanelCheckBoxes->layout()->children().count()));
  updateRoadAndLoadStatus();
  updateCabooseRoadComboBox();
  updateEngineRoadComboBox();

  // setup combobox
  addComboBoxAction(numEnginesBox);
  addComboBoxAction(routeBox);
  addComboBoxAction(modelEngineBox);

  // get notified if combo box gets modified
  //routeManager.addPropertyChangeListener(this);
  connect(routeManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  // get notified if car types or roads gets modified
  //CarTypes::instance().addPropertyChangeListener(this);
  connect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarRoads.instance().addPropertyChangeListener(this);
  connect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //EngineTypes.instance().addPropertyChangeListener(this);
  connect(EngineTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //EngineModels.instance().addPropertyChangeListener(this);
  connect(EngineModels::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //LocationManager.instance().addPropertyChangeListener(this);
  connect(LocationManager::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  packFrame();
 }

 // Save, Delete, Add, Edit, Reset, Set, Clear
 /*public*/ void TrainEditFrame::buttonActionPerformed(QWidget* ae)
 {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveTrainButton) {
         log->debug("train save button activated");
         Train* train = trainManager->getTrainByName(trainNameTextField->text());
         if (_train == NULL && train == NULL) {
             saveNewTrain();
         } else {
             if (train != NULL && train != _train) {
                 reportTrainExists(tr("save"));
                 return;
             }
             checkRoute(); // check to see if use supplied a route, just warn if no route
             saveTrain();
         }
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
     if (source == deleteTrainButton) {
         log->debug("train delete button activated");
         Train* train = trainManager->getTrainByName(trainNameTextField->text());
         if (train == NULL) {
             return;
         }
         if (!_train->reset()) {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrainIsInRoute"),
//                     new Object[]{train.getTrainTerminatesName()}), tr("CanNotDeleteTrain"),
//                     JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Can not delete train!"),tr("Train is in route to %1").arg(train->getTrainTerminatesName()));
             return;
         }
//         if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("deleteMsg"),
//                 new Object[]{train.getName()}), tr("deleteTrain"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
         if(QMessageBox::question(this, tr("Delete train?"), tr("Do you really want to delete train %1?").arg(train->getName()), QMessageBox::Yes | QMessageBox::No)!= QMessageBox::Yes)
         {
             return;
         }
         routeBox->setCurrentIndex(0);
         trainManager->deregister(train);
         foreach (JmriJFrame* frame, children) {
             frame->dispose();
         }
         _train = NULL;
         enableButtons(false);
         // save train file
         OperationsXml::save();
     }
     if (source == addTrainButton) {
         Train* train = trainManager->getTrainByName(trainNameTextField->text());
         if (train != NULL) {
             reportTrainExists(tr("add"));
             return;
         }
         saveNewTrain();
     }

     if (source == editButton) {
         editAddRoute();
     }
     if (source == setButton) {
         selectCheckboxes(true);
     }
     if (source == clearButton) {
         selectCheckboxes(false);
     }
     if (source == resetButton) {
         if (_train != NULL) {
             if (!_train->reset()) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrainIsInRoute"),
//                         new Object[]{_train->getTrainTerminatesName()}), tr("CanNotResetTrain"),
//                         JOptionPane.ERROR_MESSAGE);
              QMessageBox::critical(this, tr("Can not reset train!"), tr("Train is in route to %1").arg(_train->getTrainTerminatesName()));
             }
         }
     }
 }

 /*public*/ void TrainEditFrame::radioButtonActionPerformed(QWidget* ae)
 {
  QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (_train != NULL) {
         if (source == noneRadioButton || source == cabooseRadioButton
                 || source == fredRadioButton) {
             updateCabooseRoadComboBox();
         }
     }
 }

 /*private*/ void TrainEditFrame::saveNewTrain() {
     if (!checkName(tr("add"))) {
         return;
     }
     Train* train = trainManager->newTrain(trainNameTextField->text());
     _train = train;
     if (_train != NULL) {
         //_train->addPropertyChangeListener(this);
      connect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     // update check boxes
     updateCarTypeCheckboxes();
     updateEngineTypeCheckboxes();
     // enable check boxes and buttons
     enableButtons(true);
     saveTrain();
 }

 /*private*/ void TrainEditFrame::saveTrain() {
     if (!checkName(tr("save"))) {
         return;
     }
     if (!checkModel() || !checkEngineRoad()) {
         return;
     }
//        if (numEnginesBox.getSelectedItem()==(Train::AUTO) && !_train->getNumberEngines()==(Train::AUTO)) {
//            JOptionPane.showMessageDialog(this, tr("AutoEngines"), Bundle
//                    .getMessage("FeatureUnderDevelopment"), JOptionPane.INFORMATION_MESSAGE);
//        }
     _train->setDepartureTime( hourBox->currentText(),  minuteBox->currentText());
     _train->setNumberEngines(numEnginesBox->currentText());
     if (_train->getNumberEngines()==("0")) {
         modelEngineBox->setCurrentIndex(0);
         roadEngineBox->setCurrentIndex(0);
     }
     _train->setEngineRoad( roadEngineBox->currentText());
     _train->setEngineModel( modelEngineBox->currentText());
     if (cabooseRadioButton->isChecked()) {
         _train->setRequirements(Train::CABOOSE);
     }
     if (fredRadioButton->isChecked()) {
         _train->setRequirements(Train::FRED);
     }
     if (noneRadioButton->isChecked()) {
         _train->setRequirements(Train::NO_CABOOSE_OR_FRED);
     }
     _train->setCabooseRoad( roadCabooseBox->currentText());
     _train->setName(trainNameTextField->text().trimmed());
     _train->setDescription(trainDescriptionTextField->text());
     _train->setComment(commentTextArea->toHtml());
     // save train file
     OperationsXml::save();
 }

 /**
  *
  * @return true if name isn't too long and is at least one character
  */
 /*private*/ bool TrainEditFrame::checkName(QString s) {
     QString trainName = trainNameTextField->text().trimmed();
     if (trainName==("")) {
         log->debug("Must enter a train name");
//         JOptionPane.showMessageDialog(this, tr("MustEnterName"), MessageFormat.format(Bundle
//                 .getMessage("CanNot"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(this, tr("Can not {%1 train!").arg(s), tr("Enter a name for the train"));
         return false;
     }
     if (trainName.length() > Control::max_len_string_train_name) {
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrainNameLess"),
//                 new Object[]{Control::max_len_string_train_name + 1}), MessageFormat.format(Bundle
//                         .getMessage("CanNot"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(this, tr("Can not %1 train!").arg(s), tr("Train name must be less than %1 characters").arg(Control::max_len_string_train_name + 1));
         return false;
     }
     if (trainName.contains(".") || trainName.contains("<") || trainName.contains(">") // NOI18N
             || trainName.contains(":") || trainName.contains("\"") || trainName.contains("\\") // NOI18N
             || trainName.contains("/") || trainName.contains("|") || trainName.contains("?") // NOI18N
             || trainName.contains("*")) { // NOI18N
         log->error("Train name must not contain reserved characters");
//         JOptionPane.showMessageDialog(this, tr("TrainNameResChar") + NEW_LINE
//                 + tr("ReservedChar"), MessageFormat.format(tr("CanNot"),
//                         new Object[]{s}), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(this, tr("Can not %1 train!").arg(s), tr("Train name must not contain reserved characters"));
         return false;
     }

     return true;
 }

 /*private*/ bool TrainEditFrame::checkModel() {
     QString model =  modelEngineBox->currentText();
     if (numEnginesBox->currentText()==("0") || model==(NONE)) {
         return true;
     }
     QString type = EngineModels::instance()->getModelType(model);
     if (!_train->acceptsTypeName(type)) {
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrainModelService"),
//                 new Object[]{model, type}), MessageFormat.format(tr("CanNot"),
//                         new Object[]{tr("save")}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 train!").arg(tr("save")), tr("Train does not service loco model (%1) type (%2)").arg(model).arg(type));
         return false;
     }
     if (roadEngineBox->count() == 1) {
         log->debug("No locos available that match the model selected!");
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("NoLocosModel"),
//                 new Object[]{model}), MessageFormat.format(tr("TrainWillNotBuild"),
//                         new Object[]{_train->getName()}), JOptionPane.WARNING_MESSAGE);
         QMessageBox::warning(this, tr("Train (%1) will not build!").arg(_train->getName()), tr("No model (%1) in your locomotive roster! ").arg(model));
     }
     return true;
 }

 /*private*/ bool TrainEditFrame::checkEngineRoad() {
     QString road =  roadEngineBox->currentText();
     QString model =  modelEngineBox->currentText();
     if (numEnginesBox->currentText()==("0") || road==(NONE) || model!=(NONE)) {
         return true;
     }
     foreach (RollingStock* rs, *EngineManager::instance()->getList()) {
         if (!_train->acceptsTypeName(rs->getTypeName())) {
             continue;
         }
         if (rs->getRoadName()==(road)) {
             return true;
         }
     }
//     JOptionPane.showMessageDialog(this, MessageFormat
//             .format(tr("NoLocoRoad"), new Object[]{road}), MessageFormat.format(Bundle
//                     .getMessage("TrainWillNotBuild"), new Object[]{_train->getName()}), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(this, tr("Train (%1) will not build!").arg(_train->getName()), tr("No road (%1) in your locomotive roster that also meets the locomotive types serviced by this train.").arg(road));
     return false; // couldn't find a loco with the selected road
 }

 /*private*/ bool TrainEditFrame::checkRoute() {
     if (_train->getRoute() == NULL) {
//         JOptionPane.showMessageDialog(this, tr("TrainNeedsRoute"),
//                 tr("TrainNoRoute"), JOptionPane.WARNING_MESSAGE);
      QMessageBox::critical(this, tr("Train requires a route!"), tr("You must specify a route for this train"));
         return false;
     }
     return true;

 }

 /*private*/ void TrainEditFrame::reportTrainExists(QString s) {
     log->info("Can not " + s + ", train already exists");
//     JOptionPane.showMessageDialog(this, tr("TrainNameExists"), MessageFormat.format(Bundle
//             .getMessage("CanNot"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Can not %1 train!").arg(tr("s")), tr("Train with this name already exists"));
 }

 /*private*/ void TrainEditFrame::enableButtons(bool enabled) {
     editButton->setEnabled(enabled);
     routeBox->setEnabled(enabled && _train != NULL && !_train->isBuilt());
     clearButton->setEnabled(enabled);
     resetButton->setEnabled(enabled);
     setButton->setEnabled(enabled);
     saveTrainButton->setEnabled(enabled);
     deleteTrainButton->setEnabled(enabled);
     numEnginesBox->setEnabled(enabled);
     enableCheckboxes(enabled);
     noneRadioButton->setEnabled(enabled);
     fredRadioButton->setEnabled(enabled);
     cabooseRadioButton->setEnabled(enabled);
     // the inverse!
     addTrainButton->setEnabled(!enabled);
 }

 /*private*/ void TrainEditFrame::selectCheckboxes(bool enable) {
     for (int i = 0; i < typeCarCheckBoxes.size(); i++) {
         QCheckBox* checkBox = typeCarCheckBoxes.at(i);
         checkBox->setChecked(enable);
         if (_train != NULL) {
             //_train->removePropertyChangeListener(this);
          disconnect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             if (enable) {
                 _train->addTypeName(checkBox->text());
             } else {
                 _train->deleteTypeName(checkBox->text());
             }
             //_train->addPropertyChangeListener(this);
             connect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }

 /*public*/ void TrainEditFrame::comboBoxActionPerformed(QWidget* ae)
  {
     if (_train == NULL) {
         return;
     }
     JComboBox* source = (JComboBox*)ae;
     if (source == numEnginesBox) {
         modelEngineBox->setEnabled(numEnginesBox->currentText()!=("0"));
         roadEngineBox->setEnabled(numEnginesBox->currentText()!=("0"));
     }
     if (source == modelEngineBox) {
         updateEngineRoadComboBox();
     }
     if (source == routeBox) {
         if (routeBox->isEnabled()) {
             Route* route = _train->getRoute();
             if (route != NULL) {
                 //route.removePropertyChangeListener(this);
              disconnect(route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             }
             QVariant selected = routeBox->currentData();
             if (selected != QVariant()) {
                 route = (Route*) VPtr<Route*>::asPtr(selected);
                 _train->setRoute(route);
                 //route.addPropertyChangeListener(this);
                 connect(route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             } else {
                 _train->setRoute(NULL);
             }
             updateLocationCheckboxes();
             packFrame();
         }
     }
 }

 /*private*/ void TrainEditFrame::enableCheckboxes(bool enable) {
     for (int i = 0; i < typeCarCheckBoxes.size(); i++) {
         typeCarCheckBoxes.at(i)->setEnabled(enable);
     }
     for (int i = 0; i < typeEngineCheckBoxes.size(); i++) {
         typeEngineCheckBoxes.at(i)->setEnabled(enable);
     }
 }

 /*private*/ void TrainEditFrame::addLocationCheckBoxAction(QCheckBox* b) {
//     b.addActionListener(new java.awt.event.ActionListener() {
//         /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//             locationCheckBoxActionPerformed(e);
//         }
//     });
  boxMapper->setMapping(b,b);
  connect(b, SIGNAL(clicked(bool)), boxMapper, SLOT(map()));
 }

 /*public*/ void TrainEditFrame::locationCheckBoxActionPerformed(QWidget* ae)
 {
  QCheckBox* b = (QCheckBox*) ae;
  log->debug("checkbox change " + b->text());
  if (_train == NULL) {
      return;
  }
  QString id = b->text();
  if (b->isChecked()) {
      _train->deleteTrainSkipsLocation(id);
  } else {
      _train->addTrainSkipsLocation(id);
  }
 }

 /*private*/ void TrainEditFrame::updateRouteComboBox()
 {
  routeBox->setEnabled(false);
  routeManager->updateComboBox(routeBox);
  if (_train != NULL) {
      routeBox->setCurrentIndex(routeBox->findData(VPtr<Route>::asQVariant(_train->getRoute())));
  }
  routeBox->setEnabled(true);
 }

 /*private*/ void TrainEditFrame::updateCarTypeCheckboxes()
 {
  typeCarCheckBoxes.clear();
  //typeCarPanelCheckBoxes.removeAll();
  QLayoutItem* item;
  while ( ( item = typeCarPanelCheckBoxes->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  loadCarTypes();
  enableCheckboxes(_train != NULL);
  typeCarPanelCheckBoxes->update();
  update();
 }

 /*private*/ void TrainEditFrame::loadCarTypes()
 {
  int numberOfCheckboxes = getNumberOfCheckboxesPerLine();	// number per line
  int x = 0;
  int y = 1; // vertical position in panel
  foreach (QString type, CarTypes::instance()->getNames())
  {
   QCheckBox* checkBox = new QCheckBox();
   typeCarCheckBoxes.append(checkBox);
   checkBox->setText(type);
   addTypeCheckBoxAction(checkBox);
   addItemLeft(typeCarPanelCheckBoxes, checkBox, x++, y);
   if (_train != NULL && _train->acceptsTypeName(type))
   {
    checkBox->setChecked(true);
   }
   if (x > numberOfCheckboxes)
   {
    y++;
    x = 0;
   }
  }

  QWidget* p = new QWidget();
  p->setLayout(new QHBoxLayout);
  p->layout()->addWidget(clearButton);
  p->layout()->addWidget(setButton);
  GridBagConstraints gc = GridBagConstraints();
  gc.gridx = 0;
  gc.gridwidth = getNumberOfCheckboxesPerLine() + 1;
  gc.gridy = ++y;
//  ((GridBagLayout*)typeCarPanelCheckBoxes)->addWidget(p, gc);
 }

 /*private*/ void TrainEditFrame::updateEngineTypeCheckboxes()
 {
  typeEngineCheckBoxes.clear();
  //typeEnginePanelCheckBoxes.removeAll();
  QLayoutItem* item;
  while ( ( item = typeEnginePanelCheckBoxes->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  loadEngineTypes();
  enableCheckboxes(_train != NULL);
  typeEnginePanelCheckBoxes->update();
  update();
 }

 /*private*/ void TrainEditFrame::loadEngineTypes()
 {
  int numberOfCheckboxes = getNumberOfCheckboxesPerLine();	// number per line
  int x = 0;
  int y = 1;
  foreach (QString type, EngineTypes::instance()->getNames())
  {
   QCheckBox* checkBox = new QCheckBox();
   typeEngineCheckBoxes.append(checkBox);
   checkBox->setText(type);
   addTypeCheckBoxAction(checkBox);
   addItemLeft(typeEnginePanelCheckBoxes, checkBox, x++, y);
   if (_train != NULL && _train->acceptsTypeName(type))
   {
    checkBox->setChecked(true);
   }
   if (x > numberOfCheckboxes)
   {
    y++;
    x = 0;
   }
  }
  log->debug(tr("typeEnginePanelCheckBoxes has %1 boxes").arg(typeEnginePanelCheckBoxes->layout()->children().count()));

 }

 /*private*/ void TrainEditFrame::updateRoadComboBoxes() {
     updateCabooseRoadComboBox();
     updateEngineRoadComboBox();
 }

 // update caboose road box based on radio selection
 /*private*/ void TrainEditFrame::updateCabooseRoadComboBox()
 {
  roadCabooseBox->clear();
  roadCabooseBox->addItem(NONE);
  if (noneRadioButton->isChecked()) {
      roadCabooseBox->setEnabled(false);
      return;
  }
  roadCabooseBox->setEnabled(true);
  QStringList roads;
  if (cabooseRadioButton->isChecked()) {
      roads = CarManager::instance()->getCabooseRoadNames();
  } else {
      roads = CarManager::instance()->getFredRoadNames();
  }
//     for (String road : roads) {
//         roadCabooseBox.addItem(road);
//     }
  roadCabooseBox->addItems(roads);
  if (_train != NULL) {
      roadCabooseBox->setCurrentIndex(roadCabooseBox->findText(_train->getCabooseRoad()));
  }
 }

 /*private*/ void TrainEditFrame::updateEngineRoadComboBox() {
     QString engineModel =  modelEngineBox->currentText();
     if (engineModel == NULL) {
         return;
     }
     roadEngineBox->clear();
     roadEngineBox->addItem(NONE);
     QStringList roads = EngineManager::instance()->getEngineRoadNames(engineModel);
//     for (String roadName : roads) {
//         roadEngineBox.addItem(roadName);
//     }
     roadEngineBox->addItems(roads);
     if (_train != NULL) {
         roadEngineBox->setCurrentIndex(roadEngineBox->findText(_train->getEngineRoad()));
     }
 }

 /*private*/ void TrainEditFrame::addTypeCheckBoxAction(QCheckBox* b) {
//     b.addActionListener(new java.awt.event.ActionListener() {
//         /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//             typeCheckBoxActionPerformed(e);
//         }
//     });
  typeCheckBoxMapper->setMapping(b,b);
  connect(b,SIGNAL(clicked(bool)), typeCheckBoxMapper, SLOT(map()));
 }

 /*public*/ void TrainEditFrame::typeCheckBoxActionPerformed(QWidget* ae) {
     QCheckBox* b = (QCheckBox*) ae;
     log->debug("checkbox change " + b->text());
     if (_train == NULL) {
         return;
     }
     if (b->isChecked()) {
         _train->addTypeName(b->text());
     } else {
         _train->deleteTypeName(b->text());
     }
 }

 // the train's route shown as locations with checkboxes
 /*private*/ void TrainEditFrame::updateLocationCheckboxes()
 {
  locationCheckBoxes.clear();
  //locationPanelCheckBoxes.removeAll();
  QLayoutItem* item;
  while ( ( item = locationPanelCheckBoxes->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  if(locationPanelCheckBoxes->layout() == NULL)
  {
   locationPanelCheckBoxes->setLayout(new GridBagLayout);
  }

  int y = 0; // vertical position in panel
  Route* route = NULL;
  textRouteStatus->setText(NONE); // clear out previous status
  if (_train != NULL)
  {
      route = _train->getRoute();
  }
  if (route != NULL)
  {
   if (route->getStatus()!=(Route::OKAY))
   {
       textRouteStatus->setText(route->getStatus());
   }
   QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
   for (int i = 0; i < routeList->size(); i++)
   {
    RouteLocation* rl = routeList->at(i);
    QCheckBox* checkBox = new QCheckBox();
    locationCheckBoxes.append(checkBox);
    checkBox->setText(rl->toString());
    checkBox->setText(rl->getId());
    addItemLeft(locationPanelCheckBoxes, checkBox, 0, y++);
    Location* loc = LocationManager::instance()->getLocationByName(rl->getName());
    // does the location exist?
    if (loc != NULL)
    {
     // need to listen for name and direction changes
     //loc.removePropertyChangeListener(this);
     disconnect(loc->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //loc.addPropertyChangeListener(this);
     connect(loc->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     bool services = false;
     // does train direction service location?
     if ((rl->getTrainDirection() & loc->getTrainDirections()) > 0)
     {
      services = true;
     } // train must service last location or single location
     else if (i == routeList->size() - 1)
     {
      services = true;
     }
     // check can drop and pick up, and moves > 0
     if (services && (rl->isDropAllowed() || rl->isPickUpAllowed()) && rl->getMaxCarMoves() > 0)
     {
      checkBox->setChecked(!_train->skipsLocation(rl->getId()));
     }
     else
     {
      checkBox->setEnabled(false);
     }
     addLocationCheckBoxAction(checkBox);
    }
    else
    {
        checkBox->setEnabled(false);
    }
   }
  }
  locationPanelCheckBoxes->update();
 }


 /*private*/ void TrainEditFrame::editAddRoute()
 {
  log->debug("Edit/add route");
  // warn user if train is built that they shouldn't edit the train's route
  if (_train != NULL && _train->isBuilt()) {
//         JOptionPane.showMessageDialog(this, tr("DoNotModifyRoute"), tr("BuiltTrain"),
//                 JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(this,tr("Built Train!"), tr("Do not modify the route of a built train, reset or terminate the train before making changes to the train's route") );
  }
  if (ref != NULL) {
      ref->dispose();
  }
  ref = new RouteEditFrame();
  setChildFrame(ref);
  QVariant selected = routeBox->currentData();
  if (selected != QVariant())
  {
   Route* route = (Route*) VPtr<Route>::asPtr(selected);
   ref->initComponents(route);
  } else {
   ref->initComponents(NULL, _train);
  }
 }

 /*private*/ void TrainEditFrame::updateDepartureTime() {
     hourBox->setCurrentText(_train->getDepartureTimeHour());
     minuteBox->setCurrentIndex(minuteBox->findText(_train->getDepartureTimeMinute()));
     // check to see if route has a departure time from the 1st location
     RouteLocation* rl = _train->getTrainDepartsRouteLocation();
     if (rl != NULL && rl->getDepartureTime()!=(NONE)) {
         hourBox->setEnabled(false);
         minuteBox->setEnabled(false);
     } else {
         hourBox->setEnabled(true);
         minuteBox->setEnabled(true);
     }
 }

 /*private*/ void TrainEditFrame::updateRoadAndLoadStatus() {
     if (_train != NULL) {
         // road options
         if (_train->getRoadOption()==(Train::ALL_ROADS)) {
             roadOption->setText(tr("AcceptAll"));
         } else if (_train->getRoadOption()==(Train::INCLUDE_LOADS))
         {
          roadOption->setText(tr("AcceptOnly") + " " + QString::number(_train->getRoadNames().length()) + " "
                     + tr("Roads"));
         } else {
             roadOption->setText(tr("Exclude") + " " + QString::number(_train->getRoadNames().length()) + " "
                     + tr("Roads"));
         }
         // load options
         if (_train->getLoadOption()==(Train::ALL_ROADS)) {
             loadOption->setText(tr("AcceptAll"));
         } else if (_train->getLoadOption()==(Train::INCLUDE_LOADS)) {
             loadOption->setText(tr("AcceptOnly") + " " + QString::number(_train->getLoadNames().length()) + " "
                     + tr("Loads"));
         } else {
             loadOption->setText(tr("Exclude") + " " + QString::number(_train->getLoadNames().length()) + " "
                     + tr("Loads"));
         }
         if (_train->getRoadOption()!=(Train::ALL_ROADS) || _train->getLoadOption()!=(Train::ALL_LOADS)) {
             roadAndLoadStatusPanel->setVisible(true);
         }
     }
 }

 /*private*/ void TrainEditFrame::packFrame() {
     setVisible(false);
     setMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
     adjustSize();
     setVisible(true);
 }


 /*public*/ void TrainEditFrame::setChildFrame(JmriJFrame* frame) {
     if (children.contains(frame)) {
         return;
     }
     children.append(frame);
 }

 /*public*/ void TrainEditFrame::dispose() {
//     LocationManager.instance().removePropertyChangeListener(this);
 disconnect(LocationManager::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     EngineTypes.instance().removePropertyChangeListener(this);
 disconnect(EngineTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     EngineModels.instance().removePropertyChangeListener(this);
 disconnect(EngineModels::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     CarTypes::instance().removePropertyChangeListener(this);
 disconnect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     CarRoads.instance().removePropertyChangeListener(this);
 disconnect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     routeManager.removePropertyChangeListener(this);
 disconnect(routeManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     foreach (JmriJFrame* frame, children)
     {
         frame->dispose();
     }
     if (_train != NULL)
     {
         //_train->removePropertyChangeListener(this);
      disconnect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         Route* route = _train->getRoute();
         if (route != NULL) {
             //route.removePropertyChangeListener(this);
          disconnect(route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
             for (int i = 0; i < routeList->size(); i++) {
                 Location* loc = LocationManager::instance()->getLocationByName(routeList->at(i)->getName());
                 if (loc != NULL) {
                     //loc.removePropertyChangeListener(this);
                  disconnect(loc->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                 }
             }
         }
     }
     OperationsFrame::dispose();
 }

 /*public*/ void TrainEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::TYPES_CHANGED_PROPERTY)) {
         updateCarTypeCheckboxes();
     }
     if (e->getPropertyName()==(EngineTypes::ENGINETYPES_CHANGED_PROPERTY)) {
         updateEngineTypeCheckboxes();
     }
     if (e->getPropertyName()==(RouteManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateRouteComboBox();
     }
     if (e->getPropertyName()==(Route::LISTCHANGE_CHANGED_PROPERTY)
             || e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::TRAINDIRECTION_CHANGED_PROPERTY)) {
         updateLocationCheckboxes();
         packFrame();
     }
     if (e->getPropertyName()==(CarRoads::CARROADS_CHANGED_PROPERTY)) {
         updateRoadComboBoxes();
     }
     if (e->getPropertyName()==(EngineModels::ENGINEMODELS_CHANGED_PROPERTY)) {
         EngineModels::instance()->updateComboBox(modelEngineBox);
         modelEngineBox->insertItem(0,NONE);
         modelEngineBox->setCurrentIndex(0);
         if (_train != NULL) {
             modelEngineBox->setCurrentIndex(modelEngineBox->findText(_train->getEngineModel()));
         }
     }
     if (e->getPropertyName()==(Train::DEPARTURETIME_CHANGED_PROPERTY)) {
         updateDepartureTime();
     }
     if (e->getPropertyName()==(Train::TRAIN_ROUTE_CHANGED_PROPERTY) && _train != NULL) {
         routeBox->setCurrentIndex(routeBox->findData(VPtr<Route>::asQVariant(_train->getRoute())));
     }
     if (e->getPropertyName()==(Train::BUILT_CHANGED_PROPERTY)) {
         enableButtons(_train != NULL);
     }
     if (e->getPropertyName()==(Train::ROADS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::LOADS_CHANGED_PROPERTY)) {
         updateRoadAndLoadStatus();
     }
 }

 /*public*/ QString TrainEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.trains.TrainEditFrame";
 }

}
