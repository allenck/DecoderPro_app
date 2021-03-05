#include "trackeditframe.h"
#include "trainmanager.h"
#include "routemanager.h"
#include "location.h"
#include "track.h"
#include <QMenu>
#include <QMenuBar>
#include <QCheckBox>
#include <QScrollArea>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include "htmltextedit.h"
#include "jtextfield.h"
#include "control.h"
#include <QComboBox>
#include <gridbaglayout.h>
#include "carloads.h"
#include "carroads.h"
#include "cartypes.h"
#include <QBoxLayout>
#include <QGroupBox>
#include "enginetypes.h"
#include "flowlayout.h"
#include <gridbagconstraints.h>
#include "train.h"
#include "gridbaglayout.h"
#include "route.h"
#include "rosterentry.h"
#include <QMessageBox>
#include "operationsxml.h"
#include "setup.h"
#include "locationmanager.h"
#include <QScrollBar>
#include "trackeditcommentsaction.h"
#include "vptr.h"
#include "train.h"
#include "trackroadeditaction.h"
#include "trackloadeditaction.h"
#include "pooltrackaction.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Frame for user edit of tracks
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012, 2013
 * @version $Revision: 29665 $
 */
///*public*/ class TrackEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 // private static boolean loadAndType = false;
 /**
  *
  */
 ///private static /*final*/ long serialVersionUID = -4882708019195894528L;
 // /Managers
 // LocationManagerXml managerXml = LocationManagerXml.instance();


 /*public*/ /*static*/ /*final*/ QString TrackEditFrame::DISPOSE = "dispose"; // NOI18N
 /*public*/ /*static*/ /*final*/ int TrackEditFrame::MAX_NAME_LENGTH = Control::max_len_string_track_name;

 /*public*/ TrackEditFrame::TrackEditFrame(QWidget* parent)
  : CarAttributeEditFrame(parent)
 {
     //super();
  log = new Logger("TrackEditFrame");
  trainManager = ((TrainManager*)InstanceManager::getDefault("TrainManager"));
  routeManager = ((RouteManager*)InstanceManager::getDefault("RouteManager"));

  _location = NULL;
  _track = NULL;
  _trackName = ""; // track name for tools menu
  _type = "";
  _toolMenu = NULL;
  x = 0;
  y = 0; // vertical position in panel

  checkBoxes =  QList<QCheckBox*>();

  // panels
  checkBoxesGroupBox =  new QGroupBox(); //new QScrollArea(/*panelCheckBoxes*/);
  checkBoxesGroupBox->setLayout(new QVBoxLayout);
  panelCheckBoxes = new QWidget();
  panelCheckBoxes->setLayout(pcbLayout = new GridBagLayout);
  paneCheckBoxesScroll = new QScrollArea();
  //paneCheckBoxesScroll->setWidget(panelCheckBoxes);
  paneCheckBoxesScroll->setWidgetResizable(true);
  checkBoxesGroupBox->layout()->addWidget(paneCheckBoxesScroll);

  panelTrainDir = new QGroupBox();
  pShipLoadOption = new QGroupBox();
  pDestinationOption = new QGroupBox();
  panelOrder = new QGroupBox();

  // labels
  loadOption = new QLabel();
  shipLoadOption = new QLabel();
  roadOption = new QLabel(tr("AcceptsAllRoads"));
  destinationOption = new QLabel();

  // major buttons
  clearButton = new QPushButton(tr("Clear"));
  setButton = new QPushButton(tr("Select"));
  saveTrackButton = new QPushButton(tr("SaveTrack"));
  deleteTrackButton = new QPushButton(tr("DeleteTrack"));
  addTrackButton = new QPushButton(tr("AddTrack"));

  deleteDropButton = new QPushButton(tr("Delete"));
  addDropButton = new QPushButton(tr("Add"));
  deletePickupButton = new QPushButton(tr("Delete"));
  addPickupButton = new QPushButton(tr("Add"));

  // check boxes
  northCheckBox = new QCheckBox(tr("North"));
  southCheckBox = new QCheckBox(tr("South"));
  eastCheckBox = new QCheckBox(tr("East"));
  westCheckBox = new QCheckBox(tr("West"));
  autoDropCheckBox = new QCheckBox(tr("Auto"));
  autoPickupCheckBox = new QCheckBox(tr("Auto"));

  // car pick up order controls
  orderNormal = new QRadioButton(tr("Normal"));
  orderFIFO = new QRadioButton(tr("DescriptiveFIFO"));
  orderLIFO = new QRadioButton(tr("DescriptiveLIFO"));

  anyDrops = new QRadioButton(tr("Any"));
  trainDrop = new QRadioButton(tr("Trains"));
  routeDrop = new QRadioButton(tr("Routes"));
  excludeTrainDrop = new QRadioButton(tr("ExcludeTrains"));
  excludeRouteDrop = new QRadioButton(tr("ExcludeRoutes"));

  anyPickups = new QRadioButton(tr("Any"));
  trainPickup = new QRadioButton(tr("Trains"));
  routePickup = new QRadioButton(tr("Routes"));
  excludeTrainPickup = new QRadioButton(tr("ExcludeTrains"));
  excludeRoutePickup = new QRadioButton(tr("ExcludeRoutes"));

  comboBoxDropTrains = trainManager->getTrainComboBox();
  comboBoxDropRoutes = routeManager->getComboBox();
  comboBoxPickupTrains = trainManager->getTrainComboBox();
  comboBoxPickupRoutes = routeManager->getComboBox();

  // text field
  trackNameTextField = new JTextField(Control::max_len_string_track_name);
  trackLengthTextField = new JTextField(Control::max_len_string_track_length_name);

  // text area
  commentTextArea = new HtmlTextEdit(2, 60);
  //commentScroller = new QScrollArea(); //JScrollPane(commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
//          JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);


  // optional panel for spurs, staging, and interchanges
  dropPanel = new QGroupBox();
  pickupPanel = new QGroupBox();
  panelOpt3 = new QWidget(); // not currently used
  panelOpt4 = new QGroupBox();
 }

 /*public*/ void TrackEditFrame::initComponents(Location* location, Track* track)
 {
  _location = location;
  _track = track;

  // tool tips
  autoDropCheckBox->setToolTip(tr("When selected only show trains or routes that service this track"));
  autoPickupCheckBox->setToolTip(tr("When selected only show trains or routes that service this track"));

  // property changes
  //_location->addPropertyChangeListener(this);
  connect(_location, SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(propertyChange(PropertyChangeEvent*)) );
  // listen for car road name and type changes
  //CarRoads::instance().addPropertyChangeListener(this);
  connect(CarRoads::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(propertyChange(PropertyChangeEvent*)) );
  //CarLoads.instance().addPropertyChangeListener(this);
  connect(CarLoads::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(propertyChange(PropertyChangeEvent*)) );
  //CarTypes.instance().addPropertyChangeListener(this);
  connect(CarTypes::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(propertyChange(PropertyChangeEvent*)) );
  //trainManager.addPropertyChangeListener(this);
  connect(trainManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(propertyChange(PropertyChangeEvent*)) );
  //routeManager.addPropertyChangeListener(this);
  connect(routeManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(propertyChange(PropertyChangeEvent*)) );

  // the following code sets the frame's initial state
  //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // place all panels in a scroll pane.
  QWidget* panels = new QWidget();
  //panels->setLayout(new BoxLayout(panels, BoxLayout.Y_AXIS));
  QVBoxLayout* panelsLayout = new QVBoxLayout(panels);
  QScrollArea* pane = new QScrollArea(/*panels*/);


  // Set up the panels
  // Layout the panel by rows
  // row 1
  QWidget* p1 = new QWidget();
  //p1->setLayout(new BoxLayout(p1, BoxLayout.X_AXIS));
  QHBoxLayout* p1Layout = new QHBoxLayout(p1);
  QScrollArea* p1Pane = new QScrollArea(/*p1*/);
  p1Pane->setWidget(p1);
  p1Pane->setWidgetResizable(true);
//     p1Pane->setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
  p1Pane->verticalScrollBar()->setVisible(false);
  p1Pane->setMinimumSize(QSize(300, 3 * trackNameTextField->sizeHint().height()));
//     p1Pane->setBorder(BorderFactory.createTitledBorder(""));

  // row 1a
  QGroupBox* pName = new QGroupBox();
  pName->setLayout(new GridBagLayout());
  //pName->setBorder(BorderFactory.createTitledBorder(tr("Name")));
  pName->setStyleSheet(gbStyleSheet);
  pName->setTitle(tr("Name"));
  addItem(pName, trackNameTextField, 0, 0);

  // row 1b
  QGroupBox* pLength = new QGroupBox();
  pLength->setLayout(new GridBagLayout());
  //pLength->setBorder(BorderFactory.createTitledBorder(tr("Length")));
  pLength->setStyleSheet(gbStyleSheet);
  pLength->setTitle(tr("Length"));
  pLength->setMinimumSize(QSize(60, 1));
  addItem(pLength, trackLengthTextField, 0, 0);

  // row 1c
  panelTrainDir->setLayout(new GridBagLayout());
  //panelTrainDir->setBorder(BorderFactory.createTitledBorder(tr("TrainTrack")));
  panelTrainDir->setStyleSheet(gbStyleSheet);
  panelTrainDir->setTitle(tr("This track is serviced by trains traveling"));
  panelTrainDir->resize(QSize(200, 10));
  addItem(panelTrainDir, northCheckBox, 1, 1);
  addItem(panelTrainDir, southCheckBox, 2, 1);
  addItem(panelTrainDir, eastCheckBox, 3, 1);
  addItem(panelTrainDir, westCheckBox, 4, 1);

  p1Layout->addWidget(pName);
  p1Layout->addWidget(pLength);
  p1Layout->addWidget(panelTrainDir);

  // row 4
  //panelCheckBoxes->setLayout(new GridBagLayout());

  // status panel for roads and loads
  QWidget* panelRoadAndLoadStatus = new QWidget();
  panelRoadAndLoadStatus->setLayout(new QHBoxLayout); //(panelRoadAndLoadStatus, BoxLayout.X_AXIS));

  QGroupBox* pRoadOption = new QGroupBox();
  //pRoadOption->setBorder(BorderFactory.createTitledBorder(tr("RoadOption")));
  pRoadOption->setLayout(new QVBoxLayout);
  pRoadOption->setStyleSheet(gbStyleSheet);
  pRoadOption->setTitle(tr("Road Option"));
  pRoadOption->layout()->addWidget(roadOption);

  QGroupBox* pLoadOption = new QGroupBox();
  pLoadOption->setLayout(new QVBoxLayout);
  //pLoadOption->setBorder(BorderFactory.createTitledBorder(tr("LoadOption")));
  pLoadOption->setStyleSheet(gbStyleSheet);
  pLoadOption->setTitle(tr("Load Option"));
  pLoadOption->layout()->addWidget(loadOption);
  //pShipLoadOption->setBorder(BorderFactory.createTitledBorder(tr("ShipLoadOption")));
  pShipLoadOption->setStyleSheet(gbStyleSheet);
  pShipLoadOption->setTitle(tr("ShipLoad Option"));
  pShipLoadOption->setLayout(new QVBoxLayout);
  pShipLoadOption->layout()->addWidget(shipLoadOption);
  //pDestinationOption->setBorder(BorderFactory.createTitledBorder(tr("Destinations")));
  pDestinationOption->setLayout(new QVBoxLayout);
  pDestinationOption->setStyleSheet(gbStyleSheet);
  pDestinationOption->setTitle(tr("Destinations"));
  pDestinationOption->layout()->addWidget(destinationOption);

  panelRoadAndLoadStatus->layout()->addWidget(pRoadOption);
  panelRoadAndLoadStatus->layout()->addWidget(pLoadOption);
  panelRoadAndLoadStatus->layout()->addWidget(pShipLoadOption);
  panelRoadAndLoadStatus->layout()->addWidget(pDestinationOption);

  // only staging uses the ship load option
  pShipLoadOption->setVisible(false);
  // only classification/interchange tracks use the destination option
  pDestinationOption->setVisible(false);

  // row 10
  // order panel
  //panelOrder->setLayout(new GridBagLayout());
  panelOrder->setLayout(new QHBoxLayout);
  //panelOrder->setBorder(BorderFactory.createTitledBorder(tr("PickupOrder")));
  panelOrder->setStyleSheet(gbStyleSheet);
  panelOrder->setTitle(tr("Select pick up car order"));
  panelOrder->layout()->addWidget(orderNormal);
  panelOrder->layout()->addWidget(orderFIFO);
  panelOrder->layout()->addWidget(orderLIFO);

  QButtonGroup* orderGroup = new QButtonGroup();
  orderGroup->addButton(orderNormal);
  orderGroup->addButton(orderFIFO);
  orderGroup->addButton(orderLIFO);

  // drop panel

  dropPanel->setLayout(new GridBagLayout());
  //dropPanel->setBorder(BorderFactory.createTitledBorder(tr("TrainsOrRoutesDrops")));
  dropPanel->setStyleSheet(gbStyleSheet);
  dropPanel->setTitle(tr("Select trains or routes for car set outs"));
  // pickup panel
  pickupPanel->setLayout(new GridBagLayout());
  //pickupPanel->setBorder(BorderFactory.createTitledBorder(tr("TrainsOrRoutesPickups")));
  pickupPanel->setStyleSheet(gbStyleSheet);
  pickupPanel->setTitle(tr("Select trains or routes for car pick ups"));

  // row 11
  QGroupBox* panelComment = new QGroupBox();
  panelComment->setLayout(new GridBagLayout());
  //panelComment->setBorder(BorderFactory.createTitledBorder(tr("Comment")));
  panelComment->setStyleSheet(gbStyleSheet);
  panelComment->setTitle(tr("Comment"));
  addItem(panelComment, /*commentScroller*/commentTextArea, 0, 0);

  // adjust text area width based on window size
  //adjustTextAreaColumnWidth(commentScroller, commentTextArea);

  // row 12
  QWidget* panelButtons = new QWidget();
  panelButtons->setLayout(new GridBagLayout());

  // row 13
  addItem(panelButtons, deleteTrackButton, 0, 0);
  addItem(panelButtons, addTrackButton, 1, 0);
  addItem(panelButtons, saveTrackButton, 2, 0);

  //paneCheckBoxes->setBorder(BorderFactory.createTitledBorder(tr("TypesTrack")));
  checkBoxesGroupBox->setStyleSheet(gbStyleSheet);
  checkBoxesGroupBox->setTitle(tr("Select the rolling stock serviced by this track"));


  panelsLayout->addWidget(p1Pane);

  paneCheckBoxesScroll->setWidget(panelCheckBoxes);
  panelsLayout->addWidget(checkBoxesGroupBox);
  panelsLayout->addWidget(panelRoadAndLoadStatus);
  panelsLayout->addWidget(panelOrder);
  panelsLayout->addWidget(dropPanel);
  panelsLayout->addWidget(pickupPanel);

  // add optional panels
  panelsLayout->addWidget(panelOpt3);
  panelsLayout->addWidget(panelOpt4);

  panelsLayout->addWidget(panelComment);
  panelsLayout->addWidget(panelButtons);

  pane->setWidget(panels);
  pane->setWidgetResizable(true);
  thisLayout->addWidget(pane);

  // setup buttons
  addButtonAction(setButton);
  addButtonAction(clearButton);

  addButtonAction(deleteTrackButton);
  addButtonAction(addTrackButton);
  addButtonAction(saveTrackButton);

  addButtonAction(deleteDropButton);
  addButtonAction(addDropButton);
  addButtonAction(deletePickupButton);
  addButtonAction(addPickupButton);

  addRadioButtonAction(orderNormal);
  addRadioButtonAction(orderFIFO);
  addRadioButtonAction(orderLIFO);

  addRadioButtonAction(anyDrops);
  addRadioButtonAction(trainDrop);
  addRadioButtonAction(routeDrop);
  addRadioButtonAction(excludeTrainDrop);
  addRadioButtonAction(excludeRouteDrop);

  addRadioButtonAction(anyPickups);
  addRadioButtonAction(trainPickup);
  addRadioButtonAction(routePickup);
  addRadioButtonAction(excludeTrainPickup);
  addRadioButtonAction(excludeRoutePickup);

//		addComboBoxAction(comboBoxTypes);
  addCheckBoxAction(autoDropCheckBox);
  addCheckBoxAction(autoPickupCheckBox);

  // load fields and enable buttons
  if (_track != NULL)
  {
   //_track->addPropertyChangeListener(this);
   connect(_track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   trackNameTextField->setText(_track->getName());
   commentTextArea->setText(_track->getComment());
   trackLengthTextField->setText(QString::number(_track->getLength()));
   enableButtons(true);
   _trackName = _track->getName();
  }
  else
  {
   enableButtons(false);
  }
  // build menu
  QMenuBar* menuBar = new QMenuBar();
  _toolMenu = new QMenu(tr("Tools"));
  _toolMenu->addAction(new TrackLoadEditAction(this));
  _toolMenu->addAction(new TrackRoadEditAction(this));
  _toolMenu->addAction(new TrackEditCommentsAction(this));
  _toolMenu->addAction(new PoolTrackAction(this));
  menuBar->addMenu(_toolMenu);
  setMenuBar(menuBar);

  // load
  updateCheckboxes();

//		updateTypeComboBoxes();
  updateTrainDir();
  updateCarOrder();
  updateDropOptions();
  updatePickupOptions();
  updateRoadOption();
  updateLoadOption();
  updateDestinationOption();

  setMinimumSize(QSize(Control::panelWidth500, Control::panelHeight600));
  setVisible(true);
 }

 // Save, Delete, Add
 /*public*/ void TrackEditFrame::buttonActionPerformed(QWidget* ae)
 {
  QPushButton* source = (QPushButton*)ae;
  if (source == saveTrackButton)
  {
   log->debug("track save button activated");
   if (_track != NULL)
   {
    if (!checkUserInputs(_track))
    {
       return;
    }
    saveTrack(_track);
   }
   else
   {
    addNewTrack();
   }
   if (Setup::isCloseWindowOnSaveEnabled())
   {
    dispose();
   }
  }
  if (source == deleteTrackButton)
  {
   log->debug("track delete button activated");
   if (_track != NULL) {
       int rs = _track->getNumberRS();
       if (rs > 0) {
//                 if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("ThereAreCars"),
//                         new Object[]{Integer.toString(rs)}), tr("deleteTrack?"),
//                         JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
        if(QMessageBox::question(this, tr("Delete Track?"), tr("There are %1 cars or locomotives at this location, delete?").arg(rs),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
         return;
        }
       }
       selectCheckboxes(false);
       _location->deleteTrack(_track);
       _track = NULL;
       enableButtons(false);
       // save location file
       OperationsXml::save();
   }
  }
  if (source == addTrackButton)
  {
    addNewTrack();
  }
  if (_track == NULL) {
    return;
  }
  if (source == setButton) {
    selectCheckboxes(true);
  }
  if (source == clearButton)
  {
    selectCheckboxes(false);
  }
  if (source == addDropButton)
  {
   QString id = "";
   if (trainDrop->isChecked() || excludeTrainDrop->isChecked())
   {
       if (comboBoxDropTrains->currentText() == NULL) {
           return;
       }
       Train* train = ((Train*) VPtr<Train>::asPtr(comboBoxDropTrains->itemData(comboBoxDropTrains->currentIndex())));
       Route* route = train->getRoute();
       id = train->getId();
       if (!checkRoute(route)) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackNotByTrain"),
//                         new Object[]{train.getName()}), tr("Error"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(this, tr("Error"), tr("This track is not serviced by train (%1)").arg(train->getName()));
           return;
       }
       selectNextItemComboBox(comboBoxDropTrains);
   } else {
       if (comboBoxDropRoutes->currentText() == NULL) {
           return;
       }
       Route* route = ((Route*) VPtr<Route*>::asPtr(comboBoxDropRoutes->itemData(comboBoxDropRoutes->currentIndex())));
       id = route->getId();
       if (!checkRoute(route)) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackNotByRoute"),
//                         new Object[]{route.getName()}), tr("Error"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(this, tr("Error"), tr("This track is not serviced by route (%1)").arg(route->getName()));
           return;
       }
       selectNextItemComboBox(comboBoxDropRoutes);
   }
   _track->addDropId(id);
  }
  if (source == deleteDropButton) {
      QString id = "";
      if (trainDrop->isChecked() || excludeTrainDrop->isChecked()) {
          if (comboBoxDropTrains->currentText() == NULL) {
              return;
          }
          id = ((Train*) VPtr<Train*>::asPtr(comboBoxDropTrains->currentData()))->getId();
          selectNextItemComboBox(comboBoxDropTrains);
      } else {
          if (comboBoxDropRoutes->currentText() == NULL) {
              return;
          }
          id = ((Route*) VPtr<Route>::asPtr(comboBoxDropRoutes->currentText()))->getId();
          selectNextItemComboBox(comboBoxDropRoutes);
      }
      _track->deleteDropId(id);
  }
  if (source == addPickupButton)
  {
   QString id = "";
   if (trainPickup->isChecked() || excludeTrainPickup->isChecked())
   {
    if (comboBoxPickupTrains->currentText() == NULL)
    {
     return;
    }
    Train* train = (Train*) VPtr<Train>::asPtr(comboBoxPickupTrains->currentData());
    Route* route = train->getRoute();
    id = train->getId();
    if (!checkRoute(route))
    {
//              JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackNotByTrain"),
//                      new Object[]{train.getName()}), tr("Error"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Error"), tr("This track is not serviced by train ({%1)").arg(train->getName()));
        return;
    }
    selectNextItemComboBox(comboBoxPickupTrains);
   }
   else
   {
    if (comboBoxPickupRoutes->currentText() == NULL)
    {
     return;
    }
    Route* route = ((Route*) VPtr<Route>::asPtr(comboBoxPickupRoutes->currentData()));
    id = route->getId();
    if (!checkRoute(route))
    {
//              JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackNotByRoute"),
//                      new Object[]{route.getName()}), tr("Error"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Error"), tr("This track is not serviced by route (%1)").arg(route->getName()));
           return;
    }
    selectNextItemComboBox(comboBoxPickupRoutes);
   }
   _track->addPickupId(id);
  }
  if (source == deletePickupButton)
  {
   QString id = "";
   if (trainPickup->isChecked() || excludeTrainPickup->isChecked())
   {
    if (comboBoxPickupTrains->currentText() == NULL)
    {
        return;
    }
    id = ((Train*) VPtr<Train>::asPtr(comboBoxPickupTrains->currentData()))->getId();
    selectNextItemComboBox(comboBoxPickupTrains);
   }
   else
   {
    if (comboBoxPickupRoutes->currentText() == NULL)
    {
        return;
    }
    id = ((Route*) VPtr<Route>::asPtr(comboBoxPickupRoutes->currentData()))->getId();
    selectNextItemComboBox(comboBoxPickupRoutes);
   }
   _track->deletePickupId(id);
  }
 }

 /*protected*/ void TrackEditFrame::addNewTrack()
 {
  // check that track name is valid

  if (!checkName(tr("add"))) {
      return;
  }
  // check to see if track already exists
  Track* check = _location->getTrackByName(trackNameTextField->text(), NULL);
  if (check != NULL)
  {
   reportTrackExists(tr("add"));
   return;
  }
  // add track to this location
  _track = _location->addTrack(trackNameTextField->text(), _type);
  // check track length
  checkLength(_track);

  // save window size so it doesn't change during the following updates
  resize(size());

  // reset all of the track's attributes
  updateTrainDir();
  updateCheckboxes();
  updateDropOptions();
  updatePickupOptions();
  updateRoadOption();
  updateLoadOption();

  //_track->addPropertyChangeListener(this);
  connect(_track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  // setup check boxes
  selectCheckboxes(true);
  // store comment
  _track->setComment(commentTextArea->toPlainText());

  // enable
  enableButtons(true);
  // save location file
  OperationsXml::save();
}

 // check to see if the route services this location
 /*private*/ bool TrackEditFrame::checkRoute(Route* route)
 {
  if (route == NULL) {
      return false;
  }
  RouteLocation* rl = NULL;
  rl = route->getLastLocationByName(_location->getName());
  if (rl == NULL) {
      return false;
  }
  return true;
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*protected*/ void TrackEditFrame::saveTrack(Track* track)
 {
  // save train directions serviced by this location
  int direction = 0;
  if (northCheckBox->isChecked()) {
      direction += Track::NORTH;
  }
  if (southCheckBox->isChecked()) {
      direction += Track::SOUTH;
  }
  if (eastCheckBox->isChecked()) {
      direction += Track::EAST;
  }
  if (westCheckBox->isChecked()) {
      direction += Track::WEST;
  }
  track->setTrainDirections(direction);
  track->setName(trackNameTextField->text());

  track->setComment(commentTextArea->toPlainText());

  // save the last state of the "Use car type and load" checkbox
  // loadAndType = loadAndTypeCheckBox->isChecked();
  // save current window size so it doesn't change during updates
  resize(size());

  // enable
  enableButtons(true);
  // save location file
 }

 /*private*/ bool TrackEditFrame::checkUserInputs(Track* track)
 {
  // check that track name is valid
  if (!checkName(tr("save"))) {
      return false;
  }
  // check to see if track already exists
  Track* check = _location->getTrackByName(trackNameTextField->text(), NULL);
  if (check != NULL && check != track) {
      reportTrackExists(tr("save"));
      return false;
  }
  // check track length
  if (!checkLength(track)) {
      return false;
  }
  // check trains and route option
  if (!checkService(track)) {
      return false;
  }

  return true;
 }

 /**
 *
 * @return true if name is less than 26 characters
 */
 /*private*/ bool TrackEditFrame::checkName(QString s) {
  if (trackNameTextField->text().trimmed()==("")) {
      log->debug("Must enter a track name");
//         JOptionPane.showMessageDialog(this, tr("MustEnterName"), MessageFormat.format(Bundle
//                 .getMessage("CanNotTrack"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 Track!").arg(s), tr("Enter a name"));
      return false;
  }
  if (trackNameTextField->text().length() > MAX_NAME_LENGTH) {
      log->error("Track name must be less than " + QString::number(MAX_NAME_LENGTH + 1) + " charaters"); // NOI18N
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackNameLengthMax"),
//                 new Object[]{Integer.toString(MAX_NAME_LENGTH + 1)}), MessageFormat.format(Bundle
//                         .getMessage("CanNotTrack"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 Track!").arg(s), tr("Track name must be less than %1 characters").arg(MAX_NAME_LENGTH + 1));
      return false;
  }
  return true;
 }

 /*private*/ bool TrackEditFrame::checkLength(Track* track) {
  // convert track length if in inches
  QString length = trackLengthTextField->text();
  if (length.endsWith("\"")) { // NOI18N
      length = length.mid(0, length.length() - 1);
      //try {
      bool ok;
          double inches = (length.toDouble(&ok));
          int feet = (int) (inches * Setup::getScaleRatio() / 12);
          length = QString::number(feet);
      if(!ok) {
          log->error("Can not convert from inches to feet");
//             JOptionPane.showMessageDialog(this, tr("CanNotConvertFeet"), Bundle
//                     .getMessage("ErrorTrackLength"), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Track length incorrect!"), tr("Can not convert from inches to feet"));
          return false;
      }
  }
  if (length.endsWith("cm")) { // NOI18N
      length = length.mid(0, length.length() - 2);
      //try {
      bool ok;
          double cm = (length.toDouble(&ok));
          int meter = (int) (cm * Setup::getScaleRatio() / 100);
          length = QString::number(meter);
      if(!ok) {
          log->error("Can not convert from cm to meters");
//             JOptionPane.showMessageDialog(this, tr("CanNotConvertMeter"), Bundle
//                     .getMessage("ErrorTrackLength"), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Track length incorrect!"), tr("Can not convert from cm to meters"));
          return false;
      }
  }
  // confirm that length is a number and less than 10000 feet
  int trackLength = 0;
  try {
      trackLength = (length.toInt());
      if (length.length() > Control::max_len_string_track_length_name) {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrackMustBeLessThan"),
//                     new Object[]{Math.pow(10, Control.max_len_string_track_length_name),
//                         Setup::getLengthUnit().toLowerCase()}), tr("ErrorTrackLength"),
//                     JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(this, tr("Track length incorrect!"), tr("Track length must be less than %1 {%2").arg(qPow(10, Control::max_len_string_track_length_name)).arg(Setup::getLengthUnit().toLower()));
          return false;
      }
  } catch (NumberFormatException e) {
      log->error("Track length not an integer");
//         JOptionPane.showMessageDialog(this, tr("TrackMustBeNumber"), Bundle
//                 .getMessage("ErrorTrackLength"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Track length incorrect!"), tr("Track length must be a number"));
      return false;
  }
  // track length can not be less than than the sum of used and reserved length
  if (trackLength != track->getLength() && trackLength < track->getUsedLength() + track->getReserved()) {
      log->error("Track length can not be less than used and reserved");
//         JOptionPane.showMessageDialog(this, tr("TrackMustBeGreater"), Bundle
//                 .getMessage("ErrorTrackLength"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Track length incorrect!"), tr("Track length must be greater than the sum of Used and Reserved"));
      return false;
  }
  // if everything is okay, save length
  track->setLength(trackLength);
  return true;
 }

 /*private*/ bool TrackEditFrame::checkService(Track* track) {
  // check train and route restrictions
  if ((trainDrop->isChecked() || routeDrop->isChecked()) && track->getDropIds().length() == 0) {
      log->debug("Must enter trains or routes for this track");
//         JOptionPane.showMessageDialog(this, tr("UseAddTrainsOrRoutes"), Bundle
//                 .getMessage("SetOutDisabled"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Set outs to this track have been disabled!"), tr("Use the Add button to specify which trains or routes this track services"));
      return false;
  }
  if ((trainPickup->isChecked() || routePickup->isChecked()) && track->getPickupIds().length() == 0) {
      log->debug("Must enter trains or routes for this track");
//         JOptionPane.showMessageDialog(this, tr("UseAddTrainsOrRoutes"), Bundle
//                 .getMessage("PickUpsDisabled"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Pick ups from this track have been disabled!"), tr("Use the Add button to specify which trains or routes this track services"));
      return false;
  }
  return true;
 }

 /*private*/ void TrackEditFrame::reportTrackExists(QString s)
 {
  log->info("Can not " + s + ", track already exists");
//     JOptionPane.showMessageDialog(this, tr("TrackAlreadyExists"), MessageFormat.format(Bundle
//             .getMessage("CanNotTrack"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Can not %1 Track!").arg(s), tr("Track with this name already exists"));
 }

 /*protected*/ void TrackEditFrame::enableButtons(bool enabled) {
  northCheckBox->setEnabled(enabled);
  southCheckBox->setEnabled(enabled);
  eastCheckBox->setEnabled(enabled);
  westCheckBox->setEnabled(enabled);
  clearButton->setEnabled(enabled);
  setButton->setEnabled(enabled);
  deleteTrackButton->setEnabled(enabled);
  saveTrackButton->setEnabled(enabled);
  anyDrops->setEnabled(enabled);
  trainDrop->setEnabled(enabled);
  routeDrop->setEnabled(enabled);
  excludeTrainDrop->setEnabled(enabled);
  excludeRouteDrop->setEnabled(enabled);
  anyPickups->setEnabled(enabled);
  trainPickup->setEnabled(enabled);
  routePickup->setEnabled(enabled);
  excludeTrainPickup->setEnabled(enabled);
  excludeRoutePickup->setEnabled(enabled);
  orderNormal->setEnabled(enabled);
  orderFIFO->setEnabled(enabled);
  orderLIFO->setEnabled(enabled);
  enableCheckboxes(enabled);
}

/*public*/ void TrackEditFrame::radioButtonActionPerformed(QWidget* ae) {
  log->debug("radio button activated");
  QRadioButton* source = (QRadioButton*)ae;
  if (source == orderNormal) {
      _track->setServiceOrder(Track::NORMAL);
  }
  if (source == orderFIFO) {
      _track->setServiceOrder(Track::FIFO);
  }
  if (source == orderLIFO) {
      _track->setServiceOrder(Track::LIFO);
  }
  if (source == anyDrops) {
      _track->setDropOption(Track::ANY);
      updateDropOptions();
  }
  if (source == trainDrop) {
      _track->setDropOption(Track::TRAINS);
      updateDropOptions();
  }
  if (source == routeDrop) {
      _track->setDropOption(Track::ROUTES);
      updateDropOptions();
  }
  if (source == excludeTrainDrop) {
      _track->setDropOption(Track::EXCLUDE_TRAINS);
      updateDropOptions();
  }
  if (source == excludeRouteDrop) {
      _track->setDropOption(Track::EXCLUDE_ROUTES);
      updateDropOptions();
  }
  if (source == anyPickups) {
      _track->setPickupOption(Track::ANY);
      updatePickupOptions();
  }
  if (source == trainPickup) {
      _track->setPickupOption(Track::TRAINS);
      updatePickupOptions();
  }
  if (source == routePickup) {
      _track->setPickupOption(Track::ROUTES);
      updatePickupOptions();
  }
  if (source == excludeTrainPickup) {
      _track->setPickupOption(Track::EXCLUDE_TRAINS);
      updatePickupOptions();
  }
  if (source == excludeRoutePickup) {
      _track->setPickupOption(Track::EXCLUDE_ROUTES);
      updatePickupOptions();
  }
 }

 // TODO only update comboBox when train or route list changes.
 /*private*/ void TrackEditFrame::updateDropOptions()
 {
  //dropPanel.removeAll();
 QLayoutItem* item;
 while ( ( item = dropPanel->layout()->takeAt( 0 ) ) != NULL )
 {
     delete item->widget();
     delete item;
 }
 int numberOfItems = getNumberOfCheckboxesPerLine();

  QWidget* p = new QWidget();
  QHBoxLayout* pLayout;
  p->setLayout(pLayout=new QHBoxLayout());
  pLayout->addWidget(anyDrops);
  pLayout->addWidget(trainDrop);
  pLayout->addWidget(routeDrop);
  pLayout->addWidget(excludeTrainDrop);
  pLayout->addWidget(excludeRouteDrop);
  GridBagConstraints gc = GridBagConstraints();
  gc.gridx = 0; // added ACK
  gc.gridy =0; // added ACK
  gc.gridwidth = numberOfItems + 1;
  ((GridBagLayout*)dropPanel->layout())->addWidget(p, gc);

  int y = 1; // vertical position in panel

  if (_track != NULL)
  {
   // set radio button
   anyDrops->setChecked(_track->getDropOption()==(Track::ANY));
   trainDrop->setChecked(_track->getDropOption()==(Track::TRAINS));
   routeDrop->setChecked(_track->getDropOption()==(Track::ROUTES));
   excludeTrainDrop->setChecked(_track->getDropOption()==(Track::EXCLUDE_TRAINS));
   excludeRouteDrop->setChecked(_track->getDropOption()==(Track::EXCLUDE_ROUTES));

if (!anyDrops->isChecked())
{
    p = new QWidget();
    p->setLayout(new FlowLayout());
    if (trainDrop->isChecked() || excludeTrainDrop->isChecked()) {
        pLayout->addWidget(comboBoxDropTrains);
    } else {
        pLayout->addWidget(comboBoxDropRoutes);
    }
    pLayout->addWidget(addDropButton);
    pLayout->addWidget(deleteDropButton);
    pLayout->addWidget(autoDropCheckBox);
    gc.gridy = y++;
    ((GridBagLayout*)dropPanel->layout())->addWidget(p, gc);
    y++;

    QStringList dropIds = _track->getDropIds();
    int x = 0;
    foreach (QString id, dropIds)
    {
     QLabel* names = new QLabel();
     QString name = "<deleted>"; // NOI18N
     if (trainDrop->isChecked() || excludeTrainDrop->isChecked()) {
         Train* train = trainManager->getTrainById(id);
         if (train != NULL) {
             name = train->getName();
         }
     } else {
         Route* route = routeManager->getRouteById(id);
         if (route != NULL) {
             name = route->getName();
         }
     }
     if (name==("<deleted>")) // NOI18N
     {
         _track->deleteDropId(id);
     }
     names->setText(name);
     addItem(dropPanel, names, x++, y);
     if (x > numberOfItems) {
         y++;
         x = 0;
     }
    }
   }
  } else {
      anyDrops->setChecked(true);
  }
  dropPanel->update();
  //dropPanel.repaint();
  //revalidate();
  update();
 }

 /*private*/ void TrackEditFrame::updatePickupOptions() {
  log->debug("update pick up options");
  //pickupPanel->clear();
  if(pickupPanel == NULL || pickupPanel->layout() == NULL) return;

  QLayoutItem* item;
  while ( ( item = pickupPanel->layout()->takeAt( 0 ) ) != NULL )
  {
      delete item->widget();
      delete item;
  }

  int numberOfCheckboxes = getNumberOfCheckboxesPerLine();

  QWidget* p = new QWidget();
  //p->setLayout(new GridBagLayout());
  QHBoxLayout* pLayout = new QHBoxLayout(p);
  pLayout->addWidget(anyPickups);
  pLayout->addWidget(trainPickup);
  pLayout->addWidget(routePickup);
  pLayout->addWidget(excludeTrainPickup);
  pLayout->addWidget(excludeRoutePickup);
  GridBagConstraints gc = GridBagConstraints();
  gc.gridx = gc.gridy = 0;
  gc.gridwidth = numberOfCheckboxes + 1;
  ((GridBagLayout*)pickupPanel->layout())->addWidget(p, gc);

  int y = 1; // vertical position in panel

  if (_track != NULL)
  {
   // set radio button
   anyPickups->setChecked(_track->getPickupOption()==(Track::ANY));
   trainPickup->setChecked(_track->getPickupOption()==(Track::TRAINS));
   routePickup->setChecked(_track->getPickupOption()==(Track::ROUTES));
   excludeTrainPickup->setChecked(_track->getPickupOption()==(Track::EXCLUDE_TRAINS));
   excludeRoutePickup->setChecked(_track->getPickupOption()==(Track::EXCLUDE_ROUTES));

   if (!anyPickups->isChecked()) {
       p = new QWidget();
       p->setLayout(new FlowLayout());
       if (trainPickup->isChecked() || excludeTrainPickup->isChecked()) {
           pLayout->addWidget(comboBoxPickupTrains);
       } else {
           pLayout->addWidget(comboBoxPickupRoutes);
       }
       pLayout->addWidget(addPickupButton);
       pLayout->addWidget(deletePickupButton);
       pLayout->addWidget(autoPickupCheckBox);
       gc.gridy = y++;
       ((GridBagLayout*)pickupPanel->layout())->addWidget(p, gc);
       y++;

       int x = 0;
       foreach (QString id, _track->getPickupIds()) {
           QLabel* names = new QLabel();
           QString name = "<deleted>"; // NOI18N
           if (trainPickup->isChecked() || excludeTrainPickup->isChecked()) {
               Train* train = trainManager->getTrainById(id);
               if (train != NULL) {
                   name = train->getName();
               }
           } else {
               Route* route = routeManager->getRouteById(id);
               if (route != NULL) {
                   name = route->getName();
               }
           }
           if (name==("<deleted>")) // NOI18N
           {
               _track->deletePickupId(id);
           }
           names->setText(name);
           addItem(pickupPanel, names, x++, y);
           if (x > numberOfCheckboxes) {
               y++;
               x = 0;
           }
       }
   }
  } else {
      anyPickups->setChecked(true);
  }
  pickupPanel->update();
  //pickupPanel->repaint();
  update();
 }

 /*private*/ void TrackEditFrame::updateTrainComboBox() {
  trainManager->updateTrainComboBox(comboBoxPickupTrains);
  if (autoPickupCheckBox->isChecked()) {
      autoTrainComboBox(comboBoxPickupTrains);
  }
  trainManager->updateTrainComboBox(comboBoxDropTrains);
  if (autoDropCheckBox->isChecked()) {
      autoTrainComboBox(comboBoxDropTrains);
  }
 }

 // filter all trains not serviced by this track
 /*private*/ void TrackEditFrame::autoTrainComboBox(JComboBox* box) {
  for (int i = 1; i < box->count(); i++) {
      Train* train = VPtr<Train>::asPtr(box->itemData(i));
      if (!checkRoute(train->getRoute())) {
          box->removeItem(i--);
      }
  }
 }

 /*private*/ void TrackEditFrame::updateRouteComboBox() {
  routeManager->updateComboBox(comboBoxPickupRoutes);
  if (autoPickupCheckBox->isChecked()) {
      autoRouteComboBox(comboBoxPickupRoutes);
  }
  routeManager->updateComboBox(comboBoxDropRoutes);
  if (autoDropCheckBox->isChecked()) {
      autoRouteComboBox(comboBoxDropRoutes);
  }
 }

 // filter out all routes not serviced by this track
 /*private*/ void TrackEditFrame::autoRouteComboBox(JComboBox* box) {
  for (int i = 1; i < box->count(); i++) {
      Route* route = VPtr<Route>::asPtr(box->itemData(i));
      if (!checkRoute(route)) {
          box->removeItem(i--);
      }
  }
 }

 /*private*/ void TrackEditFrame::enableCheckboxes(bool enable)
 {
  for (int i = 0; i < checkBoxes.size(); i++) {
      checkBoxes.at(i)->setEnabled(enable);
  }
 }

 /*private*/ void TrackEditFrame::selectCheckboxes(bool enable)
 {
  for (int i = 0; i < checkBoxes.size(); i++) {
      QCheckBox* checkBox = checkBoxes.at(i);
      checkBox->setChecked(enable);
      if (_track != NULL) {
          if (enable) {
              _track->addTypeName(checkBox->text());
          } else {
              _track->deleteTypeName(checkBox->text());
          }
      }
  }
 }

 // car and loco types
 /*private*/ void TrackEditFrame::updateCheckboxes()
 {
 log->debug("Update all checkboxes");
 foreach (QCheckBox* box, checkBoxes)
 {
  pcbLayout->removeWidget(box);
 }
 checkBoxes.clear();
  //panelCheckBoxes.removeAll();
//     if ( panelCheckBoxes->layout() != NULL )
//     {
//         QLayoutItem* item;
//         while ( ( item = panelCheckBoxes->layout()->takeAt( 0 ) ) != NULL )
//         {
//             delete item->widget();
//             delete item;
//         }
//         //delete panelCheckBoxes->layout();
//     }
//     //panelCheckBoxes->setLayout(pcbLayout = new QGridLayout);
//     // Now remove the old scroll area
//     if(paneCheckBoxes->layout() !=NULL)
//     {
//         QLayoutItem* item;
//         while ( ( item = paneCheckBoxes->layout()->takeAt( 0 ) ) != NULL )
//         {
//             delete item->widget(); // delete the QScroll Area
//             delete item;
//         }
//         delete paneCheckBoxes->layout();
//     }
//     paneCheckBoxes->setLayout(new QVBoxLayout);
//     QScrollArea *scroller = new QScrollArea;
//     scroller->setWidget(panelCheckBoxes);
  // Now add the checkboxes to the panelCheckBoxes
  x = 0;
  y = 0; // vertical position in panel
  loadTypes(CarTypes::instance()->getNames());
  loadTypes(EngineTypes::instance()->getNames());
  enableCheckboxes(_track != NULL);

  QWidget* p = new QWidget();
  QHBoxLayout* pLayout;
  p->setLayout(pLayout =new QHBoxLayout);
  pLayout->addWidget(clearButton);
  pLayout->addWidget(setButton);
  GridBagConstraints gc = GridBagConstraints();
  gc.gridwidth = getNumberOfCheckboxesPerLine() + 1;
  gc.gridy = ++y;
  ((GridBagLayout*)panelCheckBoxes->layout())->addWidget(p, gc);

  //panelCheckBoxes.revalidate();
  //panelCheckBoxes.repaint();
  panelCheckBoxes->update();
 }


 /*private*/ void TrackEditFrame::loadTypes(QStringList types)
 {
  if(_location == NULL) return;
  int numberOfCheckboxes = getNumberOfCheckboxesPerLine();
  foreach (QString type, types)
  {
   if (_location->acceptsTypeName(type))
   {
    QCheckBox* checkBox = new QCheckBox();
    checkBoxes.append(checkBox);
    checkBox->setText(type);
    addCheckBoxAction(checkBox);
    addItemLeft(panelCheckBoxes, checkBox, x++, y);
    //pcbLayout->addWidget(checkBox, x++, y,1.1,Qt::AlignLeft);
    if (_track != NULL && _track->acceptsTypeName(type))
    {
     checkBox->setChecked(true);
    }
   }
   if (x > numberOfCheckboxes)
   {
    y++;
    x = 0;
   }
  }
 }

 /*private*/ void TrackEditFrame::updateRoadOption()
 {
  if (_track != NULL)
  {
   if (_track->getRoadOption()==(Track::INCLUDE_ROADS))
   {
    roadOption->setText(tr("AcceptOnly") + " " + QString::number(_track->getRoadNames().length()) + " "
            + tr("Roads"));
   }
   else if (_track->getRoadOption()==(Track::EXCLUDE_ROADS))
   {
    roadOption->setText(tr("Exclude") + " " + QString::number(_track->getRoadNames().length()) + " "
            + tr("Roads"));
   }
   else
   {
    roadOption->setText(tr("Track accepts all roads"));
   }
  }
 }

 /*private*/ void TrackEditFrame::updateLoadOption()
 {
  if (_track != NULL) {
      if (_track->getLoadOption()==(Track::INCLUDE_LOADS)) {
          loadOption->setText(tr("AcceptOnly") + " " + QString::number(_track->getLoadNames().length()) + " "
                  + tr("Loads"));
      } else if (_track->getLoadOption()==(Track::EXCLUDE_LOADS)) {
          loadOption->setText(tr("Exclude") + " " + QString::number(_track->getLoadNames().length()) + " "
                  + tr("Loads"));
      } else {
          loadOption->setText(tr("Track accepts all loads"));
      }

      if (_track->getShipLoadOption()==(Track::INCLUDE_LOADS)) {
          shipLoadOption->setText(tr("ShipOnly") + " " + QString::number(_track->getShipLoadNames().length()) + " "
                  + tr("Loads"));
      } else if (_track->getShipLoadOption()==(Track::EXCLUDE_LOADS)) {
          shipLoadOption->setText(tr("Exclude") + " " + QString::number(_track->getShipLoadNames().length()) + " "
                  + tr("Loads"));
      } else {
          shipLoadOption->setText(tr("Ship all"));
      }
  }
 }

 /*private*/ void TrackEditFrame::updateTrainDir()
 {
  northCheckBox
          ->setVisible(((Setup::getTrainDirection() & Setup::NORTH) & (_location->getTrainDirections() & Location::NORTH)) > 0);
  southCheckBox
          ->setVisible(((Setup::getTrainDirection() & Setup::SOUTH) & (_location->getTrainDirections() & Location::SOUTH)) > 0);
  eastCheckBox
          ->setVisible(((Setup::getTrainDirection() & Setup::EAST) & (_location->getTrainDirections() & Location::EAST)) > 0);
  westCheckBox
          ->setVisible(((Setup::getTrainDirection() & Setup::WEST) & (_location->getTrainDirections() & Location::WEST)) > 0);

  if (_track != NULL) {
      northCheckBox->setChecked((_track->getTrainDirections() & Track::NORTH) > 0);
      southCheckBox->setChecked((_track->getTrainDirections() & Track::SOUTH) > 0);
      eastCheckBox->setChecked((_track->getTrainDirections() & Track::EAST) > 0);
      westCheckBox->setChecked((_track->getTrainDirections() & Track::WEST) > 0);
  }
  panelTrainDir->update();
  update();
 }

 /*public*/ void TrackEditFrame::checkBoxActionPerformed(QWidget* ae)
 {
  QCheckBox* source = (QCheckBox*)ae;
  if (source == autoDropCheckBox || source == autoPickupCheckBox) {
      updateTrainComboBox();
      updateRouteComboBox();
      return;
  }
  QCheckBox* b = (QCheckBox*) source;
  log->debug(tr("checkbox change %1").arg(b->text()));
  if (_location == NULL) {
      return;
  }
  if (b->isChecked()) {
      _track->addTypeName(b->text());
  } else {
      _track->deleteTypeName(b->text());
  }
}

 // set the service order
 /*private*/ void TrackEditFrame::updateCarOrder()
 {
  if (_track != NULL)
  {
   orderNormal->setChecked(_track->getServiceOrder()==(Track::NORMAL));
   orderFIFO->setChecked(_track->getServiceOrder()==(Track::FIFO));
   orderLIFO->setChecked(_track->getServiceOrder()==(Track::LIFO));
  }
 }

 /*protected*/ void TrackEditFrame::updateDestinationOption()
 {
  if (_track != NULL) {
      if (_track->getDestinationOption()==(Track::INCLUDE_DESTINATIONS)) {
          pDestinationOption->setVisible(true);
          destinationOption->setText(tr("Accept only") + " "
                  + QString::number(_track->getDestinationListSize()) + " " + tr("Destinations"));
      } else if (_track->getDestinationOption()==(Track::EXCLUDE_DESTINATIONS)) {
          pDestinationOption->setVisible(true);
          destinationOption->setText(tr("Exclude")
                  + " "
                  + QString::number(((LocationManager*)InstanceManager::getDefault("LocationManager"))->getNumberOfLocations() - _track
                  ->getDestinationListSize()) + " " + tr("Destinations"));
      } else {
          destinationOption->setText(tr("Accept all"));
      }
  }
 }


 /*public*/ void TrackEditFrame::dispose()
 {
  if (_track != NULL) {
      //_track->removePropertyChangeListener(this);
   disconnect(_track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  //_location->removePropertyChangeListener(this);
  disconnect(_location, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarRoads.instance().removePropertyChangeListener(this);
  disconnect(CarRoads::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarLoads.instance().removePropertyChangeListener(this);
  disconnect(CarLoads::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarTypes.instance().removePropertyChangeListener(this);
  disconnect(CarTypes::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     ScheduleManager.instance().removePropertyChangeListener(this);
  //trainManager.removePropertyChangeListener(this);
  disconnect(trainManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //routeManager.removePropertyChangeListener(this);
  disconnect(routeManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  OperationsFrame::dispose();
 }

 /*public*/ void TrackEditFrame::propertyChange(PropertyChangeEvent* e) {
  if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
  }
  if (e->getPropertyName()==(Location::TYPES_CHANGED_PROPERTY)
          || e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
          || e->getPropertyName()==(Track::TYPES_CHANGED_PROPERTY)) {
      updateCheckboxes();
  }

  if (e->getPropertyName()==(Location::TRAINDIRECTION_CHANGED_PROPERTY)
          || e->getPropertyName()==(Track::TRAINDIRECTION_CHANGED_PROPERTY)) {
      updateTrainDir();
  }
  if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)) {
      updateTrainComboBox();
      updateDropOptions();
      updatePickupOptions();
  }
  if (e->getPropertyName()==(RouteManager::LISTLENGTH_CHANGED_PROPERTY)) {
      updateRouteComboBox();
      updateDropOptions();
      updatePickupOptions();
  }
  if (e->getPropertyName()==(Track::ROADS_CHANGED_PROPERTY)) {
      updateRoadOption();
  }
  if (e->getPropertyName()==(Track::LOADS_CHANGED_PROPERTY)) {
      updateLoadOption();
  }
  if (e->getPropertyName()==(Track::DROP_CHANGED_PROPERTY)) {
      updateDropOptions();
  }
  if (e->getPropertyName()==(Track::PICKUP_CHANGED_PROPERTY)) {
      updatePickupOptions();
  }
  if (e->getPropertyName()==(Track::SERVICE_ORDER_CHANGED_PROPERTY)) {
      updateCarOrder();
  }
  if (e->getPropertyName()==(Track::DESTINATIONS_CHANGED_PROPERTY)
          || e->getPropertyName()==(Track::DESTINATION_OPTIONS_CHANGED_PROPERTY)) {
      updateDestinationOption();
  }
 }

 /*public*/ QString TrackEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.TrackEditFrame";
 }

}
