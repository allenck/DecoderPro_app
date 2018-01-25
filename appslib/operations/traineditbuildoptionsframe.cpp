#include "traineditbuildoptionsframe.h"
#include "propertychangeevent.h"
#include "control.h"
#include "enginemodels.h"
#include "cartypes.h"
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include "jtextfield.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QScrollArea>
#include "train.h"
#include <QLabel>
#include "carowners.h"
#include "carroads.h"
#include "traineditframe.h"
#include "flowlayout.h"
#include <QButtonGroup>
#include "setup.h"
#include "operationsxml.h"
#include "logger.h"
#include "route.h"
#include "enginemanager.h"
#include "carmanager.h"
#include <QMessageBox>
#include "routelocation.h"
#include "gridbagconstraints.h"
#include "location.h"
#include "vptr.h"

namespace Operations
{
 /**
  * Frame for user edit of a train's build options
  *
  * @author Dan Boudreau Copyright (C) 2010, 2012, 2013
  * @version $Revision: 29493 $
  */
 ///*public*/ class TrainEditBuildOptionsFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -9083947998710208542L;


 /*public*/ /*static final*/ QString TrainEditBuildOptionsFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ TrainEditBuildOptionsFrame::TrainEditBuildOptionsFrame(QWidget* parent)
    : OperationsFrame(tr("Build Options"), parent)
 {
     //super(tr("MenuItemBuildOptions"));
 log = new Logger("TrainEditBuildOptionsFrame");
  _train = NULL;

  panelOwnerNames = new QWidget();
  panelBuilt = new QWidget();
  panelTrainReq1 = new QWidget();
  panelTrainReq2 = new QWidget();

  engine1Option = new QGroupBox();
  engine1DropOption = new QWidget();
  engine1caboose = new QGroupBox();

  engine2Option = new QGroupBox();
  engine2DropOption = new QWidget();
  engine2caboose = new QGroupBox();

  // labels
  trainName = new QLabel();
  trainDescription = new QLabel();
  before = new QLabel(tr("Before"));
  after = new QLabel(tr("After"));

  // major buttons
  addOwnerButton = new QPushButton(tr("Add Owner"));
  deleteOwnerButton = new QPushButton(tr("Delete Owner"));
  saveTrainButton = new QPushButton(tr("SaveT rain"));

  // radio buttons
  ownerNameAll = new QRadioButton(tr("Accept All"));
  ownerNameInclude = new QRadioButton(tr("Accept Only"));
  ownerNameExclude = new QRadioButton(tr("Exclude"));

  builtDateAll = new QRadioButton(tr("AcceptAll"));
  builtDateAfter = new QRadioButton(tr("After"));
  builtDateBefore = new QRadioButton(tr("Before"));
  builtDateRange = new QRadioButton(tr("Range"));

  ownerGroup = new QButtonGroup();
  builtGroup = new QButtonGroup();

  // train requirements 1st set
  none1 = new QRadioButton(tr("None"));
  change1Engine = new QRadioButton(tr("EngineChange"));
  modify1Caboose = new QRadioButton(tr("ChangeCaboose"));
  helper1Service = new QRadioButton(tr("HelperService"));
  remove1Caboose = new QRadioButton(tr("RemoveCaboose"));
  keep1Caboose = new QRadioButton(tr("KeepCaboose"));
  change1Caboose = new QRadioButton(tr("ChangeCaboose"));

  trainReq1Group = new QButtonGroup();
  cabooseOption1Group = new QButtonGroup();

  // train requirements 2nd set
  none2 = new QRadioButton(tr("None"));
  change2Engine = new QRadioButton(tr("Locomotive change"));
  modify2Caboose = new QRadioButton(tr("Change caboose"));
  helper2Service = new QRadioButton(tr("Helper service"));
  remove2Caboose = new QRadioButton(tr("Remove Caboose"));
  keep2Caboose = new QRadioButton(tr("Keep Caboose"));
  change2Caboose = new QRadioButton(tr("Change Caboose"));

  trainReq2Group = new QButtonGroup();
  cabooseOption2Group = new QButtonGroup();

  // check boxes
  buildNormalCheckBox = new QCheckBox(tr("Use normal mode when building this train"));
  sendToTerminalCheckBox = new QCheckBox();
  returnStagingCheckBox = new QCheckBox(tr("Allow cars to return to staging"));
  allowLocalMovesCheckBox = new QCheckBox(tr("Allow local moves if car has a custom load or FD"));
  allowThroughCarsCheckBox = new QCheckBox(tr("Allow cars to travel from origin to terminal"));
  serviceAllCarsCheckBox = new QCheckBox(tr("Service all cars with a final destination (FD)"));
  sendCustomStagngCheckBox = new QCheckBox(tr("Send cars with custom loads to staging"));
  buildConsistCheckBox = new QCheckBox(tr("Build loco consist from single locos"));

  // text field
  builtAfterTextField = new JTextField(10);
  builtAfterTextField->setValidator(new QIntValidator(1800,2050));
  builtBeforeTextField = new JTextField(10);
  builtBeforeTextField->setValidator(new QIntValidator(1800,2050));

  // combo boxes
  ownerBox = CarOwners::instance()->getComboBox();

  // train requirements 1st set
  routePickup1Box = new QComboBox();
  routeDrop1Box = new QComboBox();
  roadCaboose1Box = new QComboBox();
  roadEngine1Box = CarRoads::instance()->getComboBox();
  modelEngine1Box = EngineModels::instance()->getComboBox();
  numEngines1Box = new QComboBox();

  // train requirements 2nd set
  routePickup2Box = new QComboBox();
  routeDrop2Box = new QComboBox();
  roadCaboose2Box = new QComboBox();
  roadEngine2Box = CarRoads::instance()->getComboBox();
  modelEngine2Box = EngineModels::instance()->getComboBox();
  numEngines2Box = new QComboBox();
}

/*public*/ void TrainEditBuildOptionsFrame::initComponents(TrainEditFrame* parent)
{
  QGroupBox* ownerPaneFrame = new QGroupBox;
  ownerPaneFrame->setLayout(new QVBoxLayout);
  ownerPane = new QScrollArea(/*panelOwnerNames*/);
  ownerPaneFrame->layout()->addWidget(ownerPane);
  ownerPane->setWidgetResizable(true);
  //ownerPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  //ownerPane->setBorder(BorderFactory.createTitledBorder(tr("OwnersTrain")));
  ownerPaneFrame->setStyleSheet(gbStyleSheet);
  ownerPaneFrame->setTitle("Select owners serviced by this train");

  QGroupBox* builtPaneFrame = new QGroupBox;
  builtPaneFrame->setLayout(new QVBoxLayout);
  builtPane = new QScrollArea(/*panelBuilt*/);
  builtPaneFrame->layout()->addWidget(builtPane);
  builtPane->setWidgetResizable(true);
  //builtPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  //builtPane->setBorder(BorderFactory.createTitledBorder(tr("BuiltDatesTrain")));
  builtPaneFrame->setStyleSheet(gbStyleSheet);
  builtPaneFrame->setTitle("Select built dates serviced by this train");

  QGroupBox* trainReq1PaneFrame = new QGroupBox;
  trainReq1PaneFrame->setLayout(new QVBoxLayout);
  trainReq1Pane = new QScrollArea(/*panelTrainReq1*/);
  trainReq1PaneFrame->layout()->addWidget(trainReq1Pane);
  trainReq1Pane->setWidgetResizable(true);
  //trainReq1Pane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  //trainReq1Pane->setBorder(BorderFactory.createTitledBorder(tr("TrainRequires")));
  trainReq1PaneFrame->setStyleSheet(gbStyleSheet);
  trainReq1PaneFrame->setTitle("Optional train requirements");

  QGroupBox* trainReq2PaneFrame = new QGroupBox;
  trainReq2PaneFrame->setLayout(new QVBoxLayout);
  trainReq2Pane = new QScrollArea(/*panelTrainReq2*/);
  trainReq2PaneFrame->layout()->addWidget(trainReq2Pane);
  trainReq2Pane->setWidgetResizable(true);
  //trainReq2Pane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  //trainReq2Pane->setBorder(BorderFactory.createTitledBorder(tr("TrainRequires")));
  trainReq2PaneFrame->setStyleSheet(gbStyleSheet);
  trainReq2PaneFrame->setTitle("Optional train requirements");


//  ??   parent->setChildFrame(this);
  _train = parent->_train;

  //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Layout the panel by rows
  QWidget* p1 = new QWidget();
  p1->setLayout(new QHBoxLayout);//(p1, BoxLayout.X_AXIS));
  p1->setMaximumSize(QSize(2000, 250));

  // Layout the panel by rows
  // row 1a
  QGroupBox* pName = new QGroupBox();
  pName->setLayout(new GridBagLayout());
  //pName->setBorder(BorderFactory.createTitledBorder(tr("Name")));
  pName->setStyleSheet(gbStyleSheet);
  pName->setTitle("Name");
  addItem(pName, trainName, 0, 0);

  // row 1b
  QGroupBox* pDesc = new QGroupBox();
  pDesc->setLayout(new GridBagLayout());
  //pDesc->setBorder(BorderFactory.createTitledBorder(tr("Description")));
  pDesc->setStyleSheet(gbStyleSheet);
  pDesc->setTitle("Description");
  addItem(pDesc, trainDescription, 0, 0);

  p1->layout()->addWidget(pName);
  p1->layout()->addWidget(pDesc);

  // row 2
  QGroupBox* pOption = new QGroupBox();
  pOption->setLayout(new GridBagLayout());
  //pOption->setBorder(BorderFactory.createTitledBorder(tr("Options")));
  pOption->setStyleSheet(gbStyleSheet);
  pOption->setTitle("Options");
  addItemLeft(pOption, buildNormalCheckBox, 0, 0);
  addItemLeft(pOption, sendToTerminalCheckBox, 1, 0);
  addItemLeft(pOption, returnStagingCheckBox, 0, 1);
  addItemLeft(pOption, allowLocalMovesCheckBox, 1, 1);
  addItemLeft(pOption, allowThroughCarsCheckBox, 0, 2);
  addItemLeft(pOption, serviceAllCarsCheckBox, 1, 2);
  addItemLeft(pOption, sendCustomStagngCheckBox, 0, 3);
  addItemLeft(pOption, buildConsistCheckBox, 1, 3);
  pOption->setMaximumSize(QSize(2000, 250));

  returnStagingCheckBox->setEnabled(false); // only enable if train departs and returns to same staging loc

  // row 7
  panelOwnerNames->setLayout(new GridBagLayout());
  ownerGroup->addButton(ownerNameAll);
  ownerGroup->addButton(ownerNameInclude);
  ownerGroup->addButton(ownerNameExclude);

  // row 9
  panelBuilt->setLayout(new GridBagLayout());
  builtAfterTextField->setToolTip(tr("Enter the year, use 4 digits"));
  builtBeforeTextField->setToolTip(tr("Enter the year, use 4 digits"));
  addItem(panelBuilt, builtDateAll, 0, 0);
  addItem(panelBuilt, builtDateAfter, 1, 0);
  addItem(panelBuilt, builtDateBefore, 2, 0);
  addItem(panelBuilt, builtDateRange, 3, 0);
  addItem(panelBuilt, after, 1, 1);
  addItem(panelBuilt, builtAfterTextField, 2, 1);
  addItem(panelBuilt, before, 1, 2);
  addItem(panelBuilt, builtBeforeTextField, 2, 2);
  builtGroup->addButton(builtDateAll);
  builtGroup->addButton(builtDateAfter);
  builtGroup->addButton(builtDateBefore);
  builtGroup->addButton(builtDateRange);

  // row 11
  panelTrainReq1->setLayout(new QVBoxLayout);//(panelTrainReq1, BoxLayout.Y_AXIS));

  QWidget* trainOption1 = new QWidget();
  trainOption1->setLayout(new FlowLayout);
  trainOption1->layout()->addWidget(none1);
  trainOption1->layout()->addWidget(change1Engine);
  trainOption1->layout()->addWidget(modify1Caboose);
  trainOption1->layout()->addWidget(helper1Service);
  panelTrainReq1->layout()->addWidget(trainOption1);

  trainReq1Group->addButton(none1);
  trainReq1Group->addButton(change1Engine);
  trainReq1Group->addButton(modify1Caboose);
  trainReq1Group->addButton(helper1Service);

  // engine options
  engine1Option->setLayout(new GridBagLayout());

  for (int i = 0; i < Setup::getMaxNumberEngines() + 1; i++) {
      numEngines1Box->addItem(QString::number(i));
  }
  numEngines1Box->setMinimumSize(QSize(50, 20));
  modelEngine1Box->insertItem(0,"");
  modelEngine1Box->setCurrentIndex(0);
  modelEngine1Box->setMinimumSize(QSize(120, 20));
  modelEngine1Box->setToolTip(tr("ModelEngineTip"));
  roadEngine1Box->insertItem(0,"");
  roadEngine1Box->setCurrentIndex(0);
  roadEngine1Box->setMinimumSize(QSize(120, 20));
  roadEngine1Box->setToolTip(tr("RoadEngineTip"));
  panelTrainReq1->layout()->addWidget(engine1Option);

  // caboose options
  engine1caboose->setLayout(new GridBagLayout());
  //engine1caboose->setBorder(BorderFactory.createTitledBorder(tr("ChangeCaboose")));
  roadCaboose1Box->setMinimumSize(QSize(120, 20));
  roadCaboose1Box->setToolTip(tr("Optionally select road name for caboose or FRED"));
  panelTrainReq1->layout()->addWidget(engine1caboose);

  cabooseOption1Group->addButton(remove1Caboose);
  cabooseOption1Group->addButton(keep1Caboose);
  cabooseOption1Group->addButton(change1Caboose);

  // drop engine panel
  addItem(engine1DropOption, new QLabel(tr("Remove helpers at")), 0, 0);
  addItem(engine1DropOption, routeDrop1Box, 1, 0);
  panelTrainReq1->layout()->addWidget(engine1DropOption);

  // row 13
  panelTrainReq2->setLayout(new QVBoxLayout);//(panelTrainReq2, BoxLayout.Y_AXIS));

  QWidget* trainOption2 = new QWidget();
  trainOption2->setLayout(new FlowLayout);
  trainOption2->layout()->addWidget(none2);
  trainOption2->layout()->addWidget(change2Engine);
  trainOption2->layout()->addWidget(modify2Caboose);
  trainOption2->layout()->addWidget(helper2Service);
  panelTrainReq2->layout()->addWidget(trainOption2);

  trainReq2Group->addButton(none2);
  trainReq2Group->addButton(change2Engine);
  trainReq2Group->addButton(modify2Caboose);
  trainReq2Group->addButton(helper2Service);

  // engine options
  engine2Option->setLayout(new GridBagLayout());

  for (int i = 0; i < Setup::getMaxNumberEngines() + 1; i++) {
      numEngines2Box->addItem(QString::number(i));
  }
  numEngines2Box->setMinimumSize(QSize(50, 20));
  modelEngine2Box->insertItem(0,"");
  modelEngine2Box->setCurrentIndex(0);
  modelEngine2Box->setMinimumSize(QSize(120, 20));
  modelEngine2Box->setToolTip(tr("Optionally select locomotive model"));
  roadEngine2Box->insertItem(0,"");
  roadEngine2Box->setCurrentIndex(0);
  roadEngine2Box->setMinimumSize(QSize(120, 20));
  roadEngine2Box->setToolTip(tr("Optionally select locomotive road name"));
  panelTrainReq2->layout()->addWidget(engine2Option);

  // caboose options
  engine2caboose->setLayout(new GridBagLayout());
  //engine2caboose->setBorder(BorderFactory.createTitledBorder(tr("ChangeCaboose")));
  engine2caboose->setStyleSheet(gbStyleSheet);
  engine2caboose->setTitle("Caboose change");
  roadCaboose2Box->setMinimumSize(QSize(120, 20));
  roadCaboose2Box->setToolTip(tr("RoadCabooseTip"));
  panelTrainReq2->layout()->addWidget(engine2caboose);

  cabooseOption2Group->addButton(remove2Caboose);
  cabooseOption2Group->addButton(keep2Caboose);
  cabooseOption2Group->addButton(change2Caboose);

  // drop engine panel
  addItem(engine2DropOption, new QLabel(tr("Remove helpers at")), 0, 0);
  addItem(engine2DropOption, routeDrop2Box, 1, 0);
  panelTrainReq2->layout()->addWidget(engine2DropOption);

  // row 15 buttons
  QWidget* pB = new QWidget();
  pB->setLayout(new GridBagLayout());
//		pB->setMaximumSize(QSize(2000, 250));
  addItem(pB, saveTrainButton, 3, 0);

  thisLayout->addWidget(p1);
  thisLayout->addWidget(pOption);
  ownerPane->setWidget(panelOwnerNames);
  thisLayout->addWidget(ownerPaneFrame);
  builtPane->setWidget(panelBuilt);
  thisLayout->addWidget(builtPaneFrame);
  trainReq1Pane->setWidget(panelTrainReq1);
  thisLayout->addWidget(trainReq1PaneFrame);
  trainReq2Pane->setWidget(panelTrainReq2);
  thisLayout->addWidget(trainReq2PaneFrame);
  thisLayout->addWidget(pB);

  // setup buttons
  addButtonAction(deleteOwnerButton);
  addButtonAction(addOwnerButton);
  addButtonAction(saveTrainButton);

  addRadioButtonAction(ownerNameAll);
  addRadioButtonAction(ownerNameInclude);
  addRadioButtonAction(ownerNameExclude);

  addRadioButtonAction(builtDateAll);
  addRadioButtonAction(builtDateAfter);
  addRadioButtonAction(builtDateBefore);
  addRadioButtonAction(builtDateRange);

  addRadioButtonAction(none1);
  addRadioButtonAction(change1Engine);
  addRadioButtonAction(modify1Caboose);
  addRadioButtonAction(helper1Service);
  addRadioButtonAction(remove1Caboose);
  addRadioButtonAction(keep1Caboose);
  addRadioButtonAction(change1Caboose);

  addRadioButtonAction(none2);
  addRadioButtonAction(change2Engine);
  addRadioButtonAction(modify2Caboose);
  addRadioButtonAction(helper2Service);
  addRadioButtonAction(remove2Caboose);
  addRadioButtonAction(keep2Caboose);
  addRadioButtonAction(change2Caboose);

  addComboBoxAction(numEngines1Box);
  addComboBoxAction(modelEngine1Box);
  addComboBoxAction(numEngines2Box);
  addComboBoxAction(modelEngine2Box);

  if (_train != NULL)
  {
      trainName->setText(_train->getName());
      trainDescription->setText(_train->getDescription());
      buildNormalCheckBox->setChecked(_train->isBuildTrainNormalEnabled());
      sendToTerminalCheckBox->setChecked(_train->isSendCarsToTerminalEnabled());
      returnStagingCheckBox->setChecked(_train->isAllowReturnToStagingEnabled());
      allowLocalMovesCheckBox->setChecked(_train->isAllowLocalMovesEnabled());
      allowThroughCarsCheckBox->setChecked(_train->isAllowThroughCarsEnabled());
      serviceAllCarsCheckBox->setChecked(_train->isServiceAllCarsWithFinalDestinationsEnabled());
      sendCustomStagngCheckBox->setChecked(_train->isSendCarsWithCustomLoadsToStagingEnabled());
      buildConsistCheckBox->setChecked(_train->isBuildConsistEnabled());
      sendToTerminalCheckBox->setText(tr("Send all car pick ups to terminal (%1)").arg(
              _train->getTrainTerminatesName()));
      builtAfterTextField->setText(_train->getBuiltStartYear());
      builtBeforeTextField->setText(_train->getBuiltEndYear());
      setBuiltRadioButton();
      enableButtons(true);
      // does this train depart staging?
      if (_train->getTrainDepartsRouteLocation() != NULL
              && _train->getTrainDepartsRouteLocation()->getLocation()->isStaging()) {
          buildConsistCheckBox->setEnabled(false);	// can't build a consist out of staging
      }
      // does train depart and return to same staging location?
      if (_train->getTrainDepartsRouteLocation() != NULL
              && _train->getTrainTerminatesRouteLocation() != NULL
              && _train->getTrainTerminatesRouteLocation()->getLocation()->isStaging()
              && _train->getTrainDepartsRouteLocation()->getName()==(
                      _train->getTrainTerminatesRouteLocation()->getName())) {
          allowThroughCarsCheckBox->setEnabled(false);
          if (Setup::isAllowReturnToStagingEnabled()) {
              returnStagingCheckBox->setEnabled(false);
              returnStagingCheckBox->setChecked(true);
              returnStagingCheckBox->setToolTip(tr("TipReturnToStaging"));
          } else {
              returnStagingCheckBox->setEnabled(true);
          }
      }
      // listen for train changes
      //_train->addPropertyChangeListener(this);
      connect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  } else {
      enableButtons(false);
  }
  addHelpMenu("package.jmri.jmrit.operations.Operations_TrainBuildOptions", true); // NOI18N
  updateOwnerNames();
  updateBuilt();
  updateTrainRequires1Option();
  updateTrainRequires2Option();

  // get notified if car owners or engine models gets modified
  //CarOwners::instance().addPropertyChangeListener(this);
  connect(CarOwners::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //EngineModels::instance()->addPropertyChangeListener(this);
  connect(EngineModels::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  initMinimumSize();
}

// Save
/*public*/ void TrainEditBuildOptionsFrame::buttonActionPerformed(QWidget* ae)
{
QPushButton* source = (QPushButton*)ae;
  if (_train != NULL) {
      if (source == saveTrainButton) {
          log->debug("train save button activated");
          saveTrain();
      }
      if (source == addOwnerButton) {
          if (_train->addOwnerName(ownerBox->currentText())) {
              updateOwnerNames();
          }
          selectNextItemComboBox(ownerBox);
      }
      if (source == deleteOwnerButton) {
          if (_train->deleteOwnerName(ownerBox->currentText())) {
              updateOwnerNames();
          }
          selectNextItemComboBox(ownerBox);
      }
  }
}

/*public*/ void TrainEditBuildOptionsFrame::radioButtonActionPerformed(QWidget* ae) {
QRadioButton* source = (QRadioButton*)ae;
  log->debug("radio button activated");
  if (_train != NULL) {
      if (source == ownerNameAll) {
          _train->setOwnerOption(Train::ALL_OWNERS);
          updateOwnerNames();
      }
      if (source == ownerNameInclude) {
          _train->setOwnerOption(Train::INCLUDE_OWNERS);
          updateOwnerNames();
      }
      if (source == ownerNameExclude) {
          _train->setOwnerOption(Train::EXCLUDE_OWNERS);
          updateOwnerNames();
      }
      if (source == builtDateAll || source == builtDateAfter
              || source == builtDateBefore || source == builtDateRange) {
          updateBuilt();
      }
      if (source == none1) {
          _train->setSecondLegOptions(Train::NO_CABOOSE_OR_FRED);
          updateTrainRequires1Option();
          updateTrainRequires2Option();
      }
      if (source == change1Engine) {
          _train->setSecondLegOptions(Train::CHANGE_ENGINES);
          updateTrainRequires1Option();
          updateTrainRequires2Option();
      }
      if (source == modify1Caboose) {
          _train->setSecondLegOptions(Train::ADD_CABOOSE);
          updateTrainRequires1Option();
          updateTrainRequires2Option();
      }
      if (source == helper1Service) {
          _train->setSecondLegOptions(Train::HELPER_ENGINES);
          updateTrainRequires1Option();
      }
      if (source == keep1Caboose || source == change1Caboose
              || source == remove1Caboose) {
          roadCaboose1Box->setEnabled(change1Caboose->isChecked());
          updateTrainRequires2Option();
      }
      if (source == none2) {
          _train->setThirdLegOptions(Train::NO_CABOOSE_OR_FRED);
          updateTrainRequires2Option();
      }
      if (source == change2Engine) {
          _train->setThirdLegOptions(Train::CHANGE_ENGINES);
          updateTrainRequires2Option();
      }
      if (source == modify2Caboose) {
          _train->setThirdLegOptions(Train::ADD_CABOOSE);
          updateTrainRequires2Option();
      }
      if (source == helper2Service) {
          _train->setThirdLegOptions(Train::HELPER_ENGINES);
          updateTrainRequires2Option();
      }
      if (source == keep2Caboose || source == change2Caboose
              || source == remove2Caboose) {
          roadCaboose2Box->setEnabled(change2Caboose->isChecked());
      }
  }
}

// Car type combo box has been changed, show loads associated with this car type
/*public*/ void TrainEditBuildOptionsFrame::comboBoxActionPerformed(QWidget* ae) {
QComboBox* source = (QComboBox*)ae;
  if (source == numEngines1Box) {
      modelEngine1Box->setEnabled(numEngines1Box->currentText()!=("0"));
      roadEngine1Box->setEnabled(numEngines1Box->currentText()!=("0"));
  }
  if (source == modelEngine1Box) {
      updateEngineRoadComboBox(roadEngine1Box, modelEngine1Box->currentText());
      if (_train != NULL) {
          roadEngine1Box->setCurrentIndex(roadEngine1Box->findText(_train->getSecondLegEngineRoad()));
      }
  }
  if (source == numEngines2Box) {
      modelEngine2Box->setEnabled(numEngines2Box->currentText()!=("0"));
      roadEngine2Box->setEnabled(numEngines2Box->currentText()!=("0"));
  }
  if (source == modelEngine2Box) {
      updateEngineRoadComboBox(roadEngine2Box, modelEngine2Box->currentText());
      if (_train != NULL) {
          roadEngine2Box->setCurrentIndex(roadEngine2Box->findText(_train->getThirdLegEngineRoad()));
      }
  }
}

 /*private*/ void TrainEditBuildOptionsFrame::updateOwnerNames()
 {
   //panelOwnerNames.removeAll();
  QLayoutItem* item;
  while ( ( item = panelOwnerNames->layout()->takeAt( 0 ) ) != NULL )
  {
     delete item->widget();
     delete item;
  }

  ownerNameAll = new QRadioButton(tr("Accept All"));
  ownerNameInclude = new QRadioButton(tr("Accept Only"));
  ownerNameExclude = new QRadioButton(tr("Exclude"));

  QWidget* p = new QWidget();
  QHBoxLayout* pLayout;
  p->setLayout(pLayout = new QHBoxLayout());
  pLayout->addWidget(ownerNameAll);
  pLayout->addWidget(ownerNameInclude);
  pLayout->addWidget(ownerNameExclude);
  GridBagConstraints gc = GridBagConstraints();
  gc.gridwidth = 6;
  gc.gridx = 0;
  gc.gridy = 0;
  ((GridBagLayout*)panelOwnerNames->layout())->addWidget(p, gc);

  int y = 1; // vertical position in panel

  if (_train != NULL)
  {
  // set radio button
  ownerNameAll->setChecked(_train->getOwnerOption()==(Train::ALL_OWNERS));
  ownerNameInclude->setChecked(_train->getOwnerOption()==(Train::INCLUDE_OWNERS));
  ownerNameExclude->setChecked(_train->getOwnerOption()==(Train::EXCLUDE_OWNERS));

  if (!ownerNameAll->isChecked())
  {
   p = new QWidget();
   p->setLayout(new FlowLayout());
   p->layout()->addWidget(ownerBox);
   p->layout()->addWidget(addOwnerButton);
   p->layout()->addWidget(deleteOwnerButton);
   gc.gridy = y++;
   ((GridBagLayout*)panelOwnerNames->layout())->addWidget(p, gc);

   int x = 0;
   foreach (QString ownerName , _train->getOwnerNames())
   {
    QLabel* owner = new QLabel();
    owner->setText(ownerName);
    addItem(panelOwnerNames, owner, x++, y);
    if (x > 6)
    {
     y++;
     x = 0;
    }
   }
  }
 }
 else
 {
  ownerNameAll->setChecked(true);
 }
 panelOwnerNames->update();
 //panelOwnerNames->repaint();
 update();
}

/*private*/ void TrainEditBuildOptionsFrame::setBuiltRadioButton() {
  if (_train->getBuiltStartYear()==(Train::NONE) && _train->getBuiltEndYear()==(Train::NONE)) {
      builtDateAll->setChecked(true);
  } else if (_train->getBuiltStartYear()!=(Train::NONE) && _train->getBuiltEndYear()!=(Train::NONE)) {
      builtDateRange->setChecked(true);
  } else if (_train->getBuiltStartYear()!=(Train::NONE)) {
      builtDateAfter->setChecked(true);
  } else if (_train->getBuiltEndYear()!=(Train::NONE)) {
      builtDateBefore->setChecked(true);
  }
}

/*private*/ void TrainEditBuildOptionsFrame::updateBuilt() {
  builtAfterTextField->setVisible(false);
  builtBeforeTextField->setVisible(false);
  after->setVisible(false);
  before->setVisible(false);
  if (builtDateAll->isChecked()) {
      builtAfterTextField->setText("");
      builtBeforeTextField->setText("");
  } else if (builtDateAfter->isChecked()) {
      builtBeforeTextField->setText("");
      builtAfterTextField->setVisible(true);
      after->setVisible(true);
  } else if (builtDateBefore->isChecked()) {
      builtAfterTextField->setText("");
      builtBeforeTextField->setVisible(true);
      before->setVisible(true);
  } else if (builtDateRange->isChecked()) {
      after->setVisible(true);
      before->setVisible(true);
      builtAfterTextField->setVisible(true);
      builtBeforeTextField->setVisible(true);
  }
  update();
}

/*private*/ void TrainEditBuildOptionsFrame::updateTrainRequires1Option() {
  none1->setChecked(true);
  if (_train != NULL) {

      updateCabooseRoadComboBox(roadCaboose1Box);
      updateEngineRoadComboBox(roadEngine1Box, modelEngine1Box->currentText());
      if (_train->getRoute() != NULL) {
          _train->getRoute()->updateComboBox(routePickup1Box);
          _train->getRoute()->updateComboBox(routeDrop1Box);
      }

      change1Engine->setChecked((_train->getSecondLegOptions() & Train::CHANGE_ENGINES) > 0);
      helper1Service->setChecked((_train->getSecondLegOptions() & Train::HELPER_ENGINES) > 0);
      if (!change1Engine->isChecked() && !helper1Service->isChecked()) {
          modify1Caboose->setChecked((_train->getSecondLegOptions() & Train::ADD_CABOOSE) > 0
                  || (_train->getSecondLegOptions() & Train::REMOVE_CABOOSE) > 0);
      }
      numEngines1Box->setCurrentIndex(numEngines1Box->findText(_train->getSecondLegNumberEngines()));
      modelEngine1Box->setCurrentIndex(modelEngine1Box->findText(_train->getSecondLegEngineModel()));
      routePickup1Box->setCurrentIndex(routePickup1Box->findData(VPtr<RouteLocation>::asQVariant(_train->getSecondLegStartLocation())));
      routeDrop1Box->setCurrentIndex(routeDrop1Box->findData(VPtr<RouteLocation>::asQVariant(_train->getSecondLegEndLocation())));
      roadEngine1Box->setCurrentIndex(roadEngine1Box->findText(_train->getSecondLegEngineRoad()));
      keep1Caboose->setChecked(true);
      remove1Caboose->setChecked((_train->getSecondLegOptions() & Train::REMOVE_CABOOSE) > 0);
      change1Caboose->setChecked((_train->getSecondLegOptions() & Train::ADD_CABOOSE) > 0);
      roadCaboose1Box->setEnabled(change1Caboose->isChecked());
      roadCaboose1Box->setCurrentIndex(roadCaboose1Box->findText(_train->getSecondLegCabooseRoad()));
      // adjust radio button text
      if ((_train->getRequirements() & Train::CABOOSE) > 0) {
          change1Caboose->setText(tr("ChangeCaboose"));
          remove1Caboose->setEnabled(true);
      } else {
          change1Caboose->setText(tr("AddCaboose"));
          remove1Caboose->setEnabled(false);
      }
  }
  engine1Option->setVisible(change1Engine->isChecked() || helper1Service->isChecked());
  engine1caboose->setVisible(change1Engine->isChecked() || modify1Caboose->isChecked());
  engine1DropOption->setVisible(helper1Service->isChecked());
  //engine1Option->setBorder(BorderFactory.createTitledBorder(tr("EngineChange")));
  engine1Option->setStyleSheet(gbStyleSheet);
  engine1Option->setTitle(tr("Locomotive change"));
  if (change1Engine->isChecked() || helper1Service->isChecked()) {
      createEngine1Panel();
  }
  if (change1Engine->isChecked() || modify1Caboose->isChecked()) {
      createCaboose1Panel(modify1Caboose->isChecked());
  }
  if (helper1Service->isChecked()) {
      //engine1Option->setBorder(BorderFactory.createTitledBorder(tr("AddHelpers")));
   engine1Option->setStyleSheet(gbStyleSheet);
   engine1Option->setTitle(tr("Add helper locomotives"));
  }
  update();
}

/*private*/ void TrainEditBuildOptionsFrame::updateTrainRequires2Option() {
  none2->setChecked(true);
  if (_train != NULL) {

      updateCabooseRoadComboBox(roadCaboose2Box);
      updateEngineRoadComboBox(roadEngine2Box, modelEngine2Box->currentText());
      if (_train->getRoute() != NULL) {
          _train->getRoute()->updateComboBox(routePickup2Box);
          _train->getRoute()->updateComboBox(routeDrop2Box);
      }

      change2Engine->setChecked((_train->getThirdLegOptions() & Train::CHANGE_ENGINES) > 0);
      helper2Service->setChecked((_train->getThirdLegOptions() & Train::HELPER_ENGINES) > 0);
      if (!change2Engine->isChecked() && !helper2Service->isChecked()) {
          modify2Caboose->setChecked((_train->getThirdLegOptions() & Train::ADD_CABOOSE) > 0
                  || (_train->getThirdLegOptions() & Train::REMOVE_CABOOSE) > 0);
      }
      numEngines2Box->setCurrentIndex(numEngines2Box->findText(_train->getThirdLegNumberEngines()));
      modelEngine2Box->setCurrentIndex(modelEngine2Box->findText(_train->getThirdLegEngineModel()));
      routePickup2Box->setCurrentIndex(routePickup2Box->findData(VPtr<RouteLocation>::asQVariant(_train->getThirdLegStartLocation())));
      routeDrop2Box->setCurrentIndex(routeDrop2Box->findData(VPtr<RouteLocation>::asQVariant(_train->getThirdLegEndLocation())));
      roadEngine2Box->setCurrentIndex(roadEngine2Box->findText(_train->getThirdLegEngineRoad()));
      keep2Caboose->setChecked(true);
      remove2Caboose->setChecked((_train->getThirdLegOptions() & Train::REMOVE_CABOOSE) > 0);
      change2Caboose->setChecked((_train->getThirdLegOptions() & Train::ADD_CABOOSE) > 0);
      roadCaboose2Box->setEnabled(change2Caboose->isChecked());
      roadCaboose2Box->setCurrentIndex(roadCaboose2Box->findText(_train->getThirdLegCabooseRoad()));
      // adjust radio button text
      if (((_train->getRequirements() & Train::CABOOSE) > 0 || change1Caboose->isChecked())
              && !remove1Caboose->isChecked()) {
          change2Caboose->setText(tr("Caboose change"));
          remove2Caboose->setEnabled(true);
      } else {
          change2Caboose->setText(tr("Add caboose"));
          remove2Caboose->setEnabled(false);
      }
  }
  engine2Option->setVisible(change2Engine->isChecked() || helper2Service->isChecked());
  engine2caboose->setVisible(change2Engine->isChecked() || modify2Caboose->isChecked());
  engine2DropOption->setVisible(helper2Service->isChecked());
  //engine2Option->setBorder(BorderFactory.createTitledBorder(tr("EngineChange")));
  engine2Option->setStyleSheet(gbStyleSheet);
  engine2Option->setTitle(tr("Locomotive change"));
  if (change2Engine->isChecked() || helper2Service->isChecked()) {
      createEngine2Panel();
  }
  if (change2Engine->isChecked() || modify2Caboose->isChecked()) {
      createCaboose2Panel(modify2Caboose->isChecked());
  }
  if (helper2Service->isChecked()) {
      //engine2Option->setBorder(BorderFactory.createTitledBorder(tr("AddHelpers")));
   engine2Option->setStyleSheet(gbStyleSheet);
   engine2Option->setTitle(tr("Add helper locomotives"));
  }
  update();
}

/*private*/ void TrainEditBuildOptionsFrame::saveTrain() {
  if (!checkInput()) {
      return;
  }
  _train->setBuildTrainNormalEnabled(buildNormalCheckBox->isChecked());
  _train->setSendCarsToTerminalEnabled(sendToTerminalCheckBox->isChecked());
  _train->setAllowReturnToStagingEnabled(returnStagingCheckBox->isChecked()
          && returnStagingCheckBox->isEnabled());
  _train->setAllowLocalMovesEnabled(allowLocalMovesCheckBox->isChecked());
  _train->setAllowThroughCarsEnabled(allowThroughCarsCheckBox->isChecked());
  _train->setServiceAllCarsWithFinalDestinationsEnabled(serviceAllCarsCheckBox->isChecked());
  _train->setSendCarsWithCustomLoadsToStagingEnabled(sendCustomStagngCheckBox->isChecked());
  _train->setBuildConsistEnabled(buildConsistCheckBox->isChecked());
  _train->setBuiltStartYear(builtAfterTextField->text().trimmed());
  _train->setBuiltEndYear(builtBeforeTextField->text().trimmed());

  int options1 = Train::NO_CABOOSE_OR_FRED;
  if (change1Engine->isChecked()) {
      options1 = options1 | Train::CHANGE_ENGINES;
  }
  if (remove1Caboose->isChecked()) {
      options1 = options1 | Train::REMOVE_CABOOSE;
  } else if (change1Caboose->isChecked()) {
      options1 = options1 | Train::ADD_CABOOSE | Train::REMOVE_CABOOSE;
  }
  if (helper1Service->isChecked()) {
      options1 = options1 | Train::HELPER_ENGINES;
  }
  _train->setSecondLegOptions(options1);
  if (routePickup1Box->currentText() != NULL) {
      _train->setSecondLegStartLocation((RouteLocation*) VPtr<RouteLocation>::asPtr(routePickup1Box->currentData()));
  } else {
      _train->setSecondLegStartLocation(NULL);
  }
  if (routeDrop1Box->currentText() != NULL) {
      _train->setSecondLegEndLocation((RouteLocation*) VPtr<RouteLocation>::asPtr(routeDrop1Box->currentData()));
  } else {
      _train->setSecondLegEndLocation(NULL);
  }
  _train->setSecondLegNumberEngines(numEngines1Box->currentText());
  _train->setSecondLegEngineModel(modelEngine1Box->currentText());
  _train->setSecondLegEngineRoad(roadEngine1Box->currentText());
  _train->setSecondLegCabooseRoad(roadCaboose1Box->currentText());

  int options2 = Train::NO_CABOOSE_OR_FRED;
  if (change2Engine->isChecked()) {
      options2 = options2 | Train::CHANGE_ENGINES;
  }
  if (remove2Caboose->isChecked()) {
      options2 = options2 | Train::REMOVE_CABOOSE;
  } else if (change2Caboose->isChecked()) {
      options2 = options2 | Train::ADD_CABOOSE | Train::REMOVE_CABOOSE;
  }
  if (helper2Service->isChecked()) {
      options2 = options2 | Train::HELPER_ENGINES;
  }
  _train->setThirdLegOptions(options2);
  if (routePickup2Box->currentText() != NULL) {
      _train->setThirdLegStartLocation((RouteLocation*) VPtr<RouteLocation>::asPtr(routePickup2Box->currentData()));
  } else {
      _train->setThirdLegStartLocation(NULL);
  }
  if (routeDrop2Box->currentText() != NULL) {
      _train->setThirdLegEndLocation((RouteLocation*) VPtr<RouteLocation>::asPtr(routeDrop2Box->currentData()));
  } else {
      _train->setThirdLegEndLocation(NULL);
  }
  _train->setThirdLegNumberEngines(numEngines2Box->currentText());
  _train->setThirdLegEngineModel(modelEngine2Box->currentText());
  _train->setThirdLegEngineRoad(roadEngine2Box->currentText());
  _train->setThirdLegCabooseRoad(roadCaboose2Box->currentText());

  OperationsXml::save();
  if (Setup::isCloseWindowOnSaveEnabled()) {
      dispose();
  }
}

/*private*/ bool TrainEditBuildOptionsFrame::checkInput() {
  if ((!none1->isChecked() && routePickup1Box->currentText() == NULL)
          || (!none2->isChecked() && routePickup2Box->currentText() == NULL)) {
//         JOptionPane.showMessageDialog(this, tr("SelectLocationEngChange"), Bundle
//                 ->getMessage("CanNotSave"), JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Can not save train!"), tr("You must select a location for the engine/caboose change or start of helper service"));
      return false;
  }
  if ((helper1Service->isChecked() && routeDrop1Box->currentText() == NULL)
          || (helper2Service->isChecked() && routeDrop2Box->currentText() == NULL)) {
//         JOptionPane.showMessageDialog(this, tr("SelectLocationEndHelper"), Bundle
//                 ->getMessage("CanNotSave"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not save train!"), tr("You must select a location for the end of helper service"));
      return false;
  }
  //try {
      if (builtAfterTextField->text().trimmed()!=("")) {
          (builtAfterTextField->text().trimmed().toInt());
      }
      if (builtBeforeTextField->text().trimmed()!=("")) {
         builtBeforeTextField->text().trimmed().toInt();
      }
//     } catch (NumberFormatException e) {
////         JOptionPane.showMessageDialog(this, tr("EnterFourDigitYear"), Bundle
////                 ->getMessage("CanNotSave"), JOptionPane.ERROR_MESSAGE);
//      QMessageBox::critical(this, tr("Can not save train!"), tr("Enter the built year, use 4 digits"));
//         return false;
//     }
  return true;
}

/*private*/ void TrainEditBuildOptionsFrame::enableButtons(bool enabled) {
  ownerNameAll->setEnabled(enabled);
  ownerNameInclude->setEnabled(enabled);
  ownerNameExclude->setEnabled(enabled);

  builtDateAll->setEnabled(enabled);
  builtDateAfter->setEnabled(enabled);
  builtDateBefore->setEnabled(enabled);
  builtDateRange->setEnabled(enabled);

  none1->setEnabled(enabled);
  change1Engine->setEnabled(enabled);
  modify1Caboose->setEnabled(enabled);
  helper1Service->setEnabled(enabled);

  none2->setEnabled(enabled);
  change2Engine->setEnabled(enabled);
  modify2Caboose->setEnabled(enabled);
  helper2Service->setEnabled(enabled);

  saveTrainButton->setEnabled(enabled);
}

/*private*/ void TrainEditBuildOptionsFrame::updateModelComboBoxes() {
  EngineModels::instance()->updateComboBox(modelEngine1Box);
  EngineModels::instance()->updateComboBox(modelEngine2Box);
  modelEngine1Box->insertItem(0,"");
  modelEngine2Box->insertItem(0,"");
  if (_train != NULL) {
      modelEngine1Box->setCurrentIndex(modelEngine1Box->findText(_train->getSecondLegEngineModel()));
      modelEngine2Box->setCurrentIndex(modelEngine2Box->findText(_train->getThirdLegEngineModel()));
  }
}

/*private*/ void TrainEditBuildOptionsFrame::updateOwnerComboBoxes() {
  CarOwners::instance()->updateComboBox(ownerBox);
}

// update caboose road box based on radio selection
/*private*/ void TrainEditBuildOptionsFrame::updateCabooseRoadComboBox(QComboBox* box) {
  box->clear();
  box->addItem("");
  QStringList roads = CarManager::instance()->getCabooseRoadNames();
  foreach (QString road, roads) {
      box->addItem(road);
  }
}

/*private*/ void TrainEditBuildOptionsFrame::updateEngineRoadComboBox(QComboBox* box, QString engineModel) {
  if (engineModel == NULL) {
      return;
  }
  box->clear();
  box->addItem("");
  QStringList roads = EngineManager::instance()->getEngineRoadNames(engineModel);
  foreach (QString road, roads) {
      box->addItem(road);
  }
}

/*private*/ void TrainEditBuildOptionsFrame::createEngine1Panel() {
  //engine1Option.removeAll();
  QLayoutItem* item;
  while ( ( item = engine1Option->layout()->takeAt( 0 ) ) != NULL )
  {
      delete item->widget();
      delete item;
  }
  addItem(engine1Option, new QLabel(tr("ChangeEnginesAt")), 0, 0);
  addItem(engine1Option, routePickup1Box, 1, 0);
  addItem(engine1Option, new QLabel(tr("Engines")), 2, 0);
  addItem(engine1Option, numEngines1Box, 3, 0);
  addItem(engine1Option, new QLabel(tr("Model")), 4, 0);
  addItem(engine1Option, modelEngine1Box, 5, 0);
  addItem(engine1Option, new QLabel(tr("Road")), 6, 0);
  addItem(engine1Option, roadEngine1Box, 7, 0);
}

/*private*/ void TrainEditBuildOptionsFrame::createEngine2Panel() {
  //engine2Option.removeAll();
  QLayoutItem* item;
  while ( ( item = engine2Option->layout()->takeAt( 0 ) ) != NULL )
  {
      delete item->widget();
      delete item;
  }
  addItem(engine2Option, new QLabel(tr("ChangeEnginesAt")), 0, 0);
  addItem(engine2Option, routePickup2Box, 1, 0);
  addItem(engine2Option, new QLabel(tr("Engines")), 2, 0);
  addItem(engine2Option, numEngines2Box, 3, 0);
  addItem(engine2Option, new QLabel(tr("Model")), 4, 0);
  addItem(engine2Option, modelEngine2Box, 5, 0);
  addItem(engine2Option, new QLabel(tr("Road")), 6, 0);
  addItem(engine2Option, roadEngine2Box, 7, 0);
}

/*private*/ void TrainEditBuildOptionsFrame::createCaboose1Panel(bool withCombox) {
  //engine1caboose.removeAll();
QLayoutItem* item;
while ( ( item = engine1caboose->layout()->takeAt( 0 ) ) != NULL )
{
  delete item->widget();
  delete item;
}
  addItem(engine1caboose, remove1Caboose, 2, 6);
  addItem(engine1caboose, change1Caboose, 4, 6);
  addItem(engine1caboose, new QLabel(tr("Road")), 5, 6);
  addItem(engine1caboose, roadCaboose1Box, 6, 6);
  if (withCombox) {
      addItem(engine1caboose, new QLabel(tr("ChangeEnginesAt")), 0, 6);
      addItem(engine1caboose, routePickup1Box, 1, 6);
  } else {
      addItem(engine1caboose, keep1Caboose, 3, 6);
  }
}

 /*private*/ void TrainEditBuildOptionsFrame::createCaboose2Panel(bool withCombox)
 {
  //engine2caboose.removeAll();
  QLayoutItem* item;
  while ( ( item = engine2caboose->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  addItem(engine2caboose, remove2Caboose, 2, 6);
  addItem(engine2caboose, change2Caboose, 4, 6);
  addItem(engine2caboose, new QLabel(tr("Road")), 5, 6);
  addItem(engine2caboose, roadCaboose2Box, 6, 6);
  if (withCombox) {
      addItem(engine2caboose, new QLabel(tr("ChangeEnginesAt")), 0, 6);
      addItem(engine2caboose, routePickup2Box, 1, 6);
  } else {
      addItem(engine2caboose, keep2Caboose, 3, 6);
  }
 }

 /*
 * private boolean checkModel(String model, String numberEngines){ if (numberEngines==("0") ||
 * model==("")) return true; String type = EngineModels.instance()->getModelType(model);
 * if(_train->acceptsTypeName(type)) return true; JOptionPane.showMessageDialog(this,
 * MessageFormat.format(tr("TrainModelService"), new Object[] {model, type}),
 * MessageFormat.format(tr("CanNot"), new Object[] {tr("save")}),
 * JOptionPane.ERROR_MESSAGE); return false; }
 */
 /*public*/ void TrainEditBuildOptionsFrame::dispose()
 {
    //CarOwners::instance()->removePropertyChangeListener(this);
  disconnect(CarOwners::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    //EngineModels::instance().removePropertyChangeListener(this);
  disconnect(EngineModels::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  if (_train != NULL) {
      //_train->removePropertyChangeListener(this);
   disconnect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  OperationsFrame::dispose();
}

/*public*/ void TrainEditBuildOptionsFrame::propertyChange(PropertyChangeEvent* e) {
  if (Control::showProperty) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
  }
  if (e->getPropertyName()==(CarOwners::CAROWNERS_CHANGED_PROPERTY)) {
      updateOwnerComboBoxes();
      updateOwnerNames();
  }
  if (e->getPropertyName()==(EngineModels::ENGINEMODELS_CHANGED_PROPERTY)
          || e->getPropertyName()==(Train::TYPES_CHANGED_PROPERTY)) {
      updateModelComboBoxes();
  }
  if (e->getPropertyName()==(Train::TRAIN_REQUIREMENTS_CHANGED_PROPERTY)) {
      updateTrainRequires1Option();
      updateTrainRequires2Option();
  }
 }

}
