#include "trackloadeditframe.h"
#include "control.h"
#include "propertychangeevent.h"
#include "location.h"
#include "track.h"
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QButtonGroup>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include "jcombobox.h"
#include "carloads.h"
#include "cartypes.h"
#include "flowlayout.h"
#include "logger.h"
#include "setup.h"
#include "operationsxml.h"
#include <QMessageBox>
#include "carload.h"

namespace Operations
{
/**
 * Frame for user edit of track loads
 *
 * @author Dan Boudreau Copyright (C) 2013, 2014
 * @version $Revision: 22371 $
 */
///*public*/ class TrackLoadEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static /*final*/ long serialVersionUID = -5231003531264725867L;
 /*private*/ /*static*/ bool TrackLoadEditFrame::loadAndType = false;
 /*private*/ /*static*/ bool TrackLoadEditFrame::shipLoadAndType = false;


 /*public*/ /*static*/ /*final*/ QString TrackLoadEditFrame::DISPOSE = "dispose"; // NOI18N
 /*public*/ /*static*/ /*final*/ int TrackLoadEditFrame::MAX_NAME_LENGTH = Control::max_len_string_track_name;

 /*public*/ TrackLoadEditFrame::TrackLoadEditFrame(QWidget* parent)
     : OperationsFrame(tr("Edit Track Loads"), parent)
 {
  log = new Logger("TrackLoadEditFrame");
  //super(tr("TitleEditTrackLoads"));
  _location = NULL;
  _track = NULL;
  _type = "";
  _toolMenu = NULL;

  // panels
  pLoadControls = new QGroupBox();
  panelLoads = new QWidget();
  paneLoads = new QScrollArea(/*panelLoads*/);

  pShipLoadControls = new QGroupBox();
  panelShipLoads = new QGroupBox();
  paneShipLoadControls = NULL;
  paneShipLoads = new QScrollArea(/*panelShipLoads*/);

  // major buttons
  saveTrackButton = new QPushButton(tr("Save Track"));

  addLoadButton = new QPushButton(tr("Add Load"));
  deleteLoadButton = new QPushButton(tr("Delete Load"));
  deleteAllLoadsButton = new QPushButton(tr("Delete All"));

  addShipLoadButton = new QPushButton(tr("Add Load"));
  deleteShipLoadButton = new QPushButton(tr("Delete Load"));
  deleteAllShipLoadsButton = new QPushButton(tr("Delete All"));

  // check boxes
  loadAndTypeCheckBox = new QCheckBox(tr("Type And Load"));
  shipLoadAndTypeCheckBox = new QCheckBox(tr("Type And Load"));

  // radio buttons
  loadNameAll = new QRadioButton(tr("AcceptAll"));
  loadNameInclude = new QRadioButton(tr("AcceptOnly"));
  loadNameExclude = new QRadioButton(tr("Exclude"));

  shipLoadNameAll = new QRadioButton(tr("ShipAll"));
  shipLoadNameInclude = new QRadioButton(tr("ShipOnly"));
  shipLoadNameExclude = new QRadioButton(tr("Exclude"));

  // combo box
  comboBoxLoads = CarLoads::instance()->getComboBox(NULL);
  comboBoxShipLoads = CarLoads::instance()->getComboBox(NULL);
  comboBoxTypes = CarTypes::instance()->getComboBox();
  comboBoxShipTypes = CarTypes::instance()->getComboBox();

  // labels
  trackName = new QLabel();
 }

 /*public*/ void TrackLoadEditFrame::initComponents(Location* location, Track* track)
 {
  _location = location;
  _track = track;

  // property changes
  //_location.addPropertyChangeListener(this);
  connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  // listen for car load name and type changes
  //CarLoads.instance().addPropertyChangeListener(this);
  connect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarTypes.instance().addPropertyChangeListener(this);
  connect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  // the following code sets the frame's initial state

  //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Set up the panels
  // Layout the panel by rows
  // row 1
  QWidget* p1 = new QWidget();
  p1->setLayout(new QHBoxLayout); //(p1, BoxLayout.X_AXIS));
  p1->setMaximumSize(QSize(2000, 250));

  // row 1a
  QGroupBox* pTrackName = new QGroupBox();
  pTrackName->setLayout(new GridBagLayout());
  //pTrackName->setBorder(BorderFactory.createTitledBorder(tr("Track")));
  pTrackName->setStyleSheet(gbStyleSheet);
  pTrackName->setTitle(tr("Track"));
  addItem(pTrackName, trackName, 0, 0);

  // row 1b
  QGroupBox* pLocationName = new QGroupBox();
  pLocationName->setLayout(new GridBagLayout());
  //pLocationName->setBorder(BorderFactory.createTitledBorder(tr("Location")));
  pLocationName->setStyleSheet(gbStyleSheet);
  pLocationName->setTitle(tr("Location"));
  addItem(pLocationName, new QLabel(_location->getName()), 0, 0);

  p1->layout()->addWidget(pTrackName);
  p1->layout()->addWidget(pLocationName);

  // row 3
  QGroupBox* p3Frame = new QGroupBox;
  p3Frame->setLayout(new QVBoxLayout);
  QWidget* p3 = new QWidget();
  p3->setLayout(new QVBoxLayout);//(p3, BoxLayout.Y_AXIS));
  QScrollArea* pane3 = new QScrollArea(/*p3*/);
  p3Frame->layout()->addWidget(pane3);
  pane3->setWidgetResizable(true);
  //pane3->setBorder(BorderFactory.createTitledBorder(tr("LoadsTrack")));
  p3Frame->setStyleSheet(gbStyleSheet);
  p3Frame->setTitle("Select loads serviced by this track");
  pane3->setMaximumSize(QSize(2000, 400));

  QWidget* pLoadRadioButtons = new QWidget();
  pLoadRadioButtons->setLayout(new FlowLayout());

  pLoadRadioButtons->layout()->addWidget(loadNameAll);
  pLoadRadioButtons->layout()->addWidget(loadNameInclude);
  pLoadRadioButtons->layout()->addWidget(loadNameExclude);
  pLoadRadioButtons->layout()->addWidget(loadAndTypeCheckBox);

  pLoadControls->setLayout(new FlowLayout());

  pLoadControls->layout()->addWidget(comboBoxTypes);
  pLoadControls->layout()->addWidget(comboBoxLoads);
  pLoadControls->layout()->addWidget(addLoadButton);
  pLoadControls->layout()->addWidget(deleteLoadButton);
  pLoadControls->layout()->addWidget(deleteAllLoadsButton);

  pLoadControls->setVisible(false);

  p3->layout()->addWidget(pLoadRadioButtons);
  p3->layout()->addWidget(pLoadControls);

  // row 4
  QGroupBox* p4Frame = new QGroupBox;
  p4Frame->setLayout(new QVBoxLayout);
  panelLoads->setLayout(new GridBagLayout());
  paneLoads->setWidgetResizable(true);
  p4Frame->layout()->addWidget(paneLoads);
  //paneLoads->setBorder(BorderFactory.createTitledBorder(tr("Loads")));
  p4Frame->setStyleSheet(gbStyleSheet);
  p4Frame->setTitle(tr("Loads"));

  QButtonGroup* loadGroup = new QButtonGroup();
  loadGroup->addButton(loadNameAll);
  loadGroup->addButton(loadNameInclude);
  loadGroup->addButton(loadNameExclude);

  // row 6
  QGroupBox* p6Frame = new QGroupBox;
  p6Frame->setLayout(new QVBoxLayout);
  QWidget* p6 = new QWidget();
  p6->setLayout(new QVBoxLayout);//(p6, BoxLayout.Y_AXIS));
  paneShipLoadControls = new QScrollArea(/*p6*/);
  paneShipLoadControls->setWidgetResizable(true);
  p6Frame->layout()->addWidget(paneShipLoadControls);
  //paneShipLoadControls->setBorder(BorderFactory.createTitledBorder(tr("ShipLoadsTrack")));
  p6Frame->setStyleSheet(gbStyleSheet);
  p6Frame->setTitle(tr("Select loads shipped from this track"));
  paneShipLoadControls->setMaximumSize(QSize(2000, 400));

  QWidget* pShipLoadRadioButtons = new QWidget();
  pShipLoadRadioButtons->setLayout(new FlowLayout());

  pShipLoadRadioButtons->layout()->addWidget(shipLoadNameAll);
  pShipLoadRadioButtons->layout()->addWidget(shipLoadNameInclude);
  pShipLoadRadioButtons->layout()->addWidget(shipLoadNameExclude);
  pShipLoadRadioButtons->layout()->addWidget(shipLoadAndTypeCheckBox);

  pShipLoadControls->setLayout(new FlowLayout());

  pShipLoadControls->layout()->addWidget(comboBoxShipTypes);
  pShipLoadControls->layout()->addWidget(comboBoxShipLoads);
  pShipLoadControls->layout()->addWidget(addShipLoadButton);
  pShipLoadControls->layout()->addWidget(deleteShipLoadButton);
  pShipLoadControls->layout()->addWidget(deleteAllShipLoadsButton);

  pShipLoadControls->setVisible(false);

  p6->layout()->addWidget(pShipLoadRadioButtons);
  p6->layout()->addWidget(pShipLoadControls);

  // row 7
  panelShipLoads->setLayout(new GridBagLayout());
  //paneShipLoads->setBorder(BorderFactory.createTitledBorder(tr("Loads")));
  panelShipLoads->setStyleSheet(gbStyleSheet);
  panelShipLoads->setTitle(tr("Loads"));

  QButtonGroup* shipLoadGroup = new QButtonGroup();
  shipLoadGroup->addButton(shipLoadNameAll);
  shipLoadGroup->addButton(shipLoadNameInclude);
  shipLoadGroup->addButton(shipLoadNameExclude);

  // row 12
  QGroupBox* panelButtons = new QGroupBox();
  panelButtons->setLayout(new GridBagLayout());
  //panelButtons->setBorder(BorderFactory.createTitledBorder(""));
  panelButtons->setStyleSheet(gbStyleSheet);
  panelButtons->setMaximumSize(QSize(2000, 200));

  // row 13
  addItem(panelButtons, saveTrackButton, 0, 0);

  thisLayout->addWidget(p1);
  pane3->setWidget(p3);
  thisLayout->addWidget(/*pane3*/p3Frame);
  paneLoads->setWidget(panelLoads);
  thisLayout->addWidget(p4Frame);
  paneShipLoadControls->setWidget(p6);
  thisLayout->addWidget(/*paneShipLoadControls*/p6Frame);
  thisLayout->addWidget(panelShipLoads);
  thisLayout->addWidget(panelButtons);

  // setup buttons
  addButtonAction(saveTrackButton);

  addButtonAction(deleteLoadButton);
  addButtonAction(deleteAllLoadsButton);
  addButtonAction(addLoadButton);

  addButtonAction(deleteShipLoadButton);
  addButtonAction(deleteAllShipLoadsButton);
  addButtonAction(addShipLoadButton);

  addRadioButtonAction(loadNameAll);
  addRadioButtonAction(loadNameInclude);
  addRadioButtonAction(loadNameExclude);

  addRadioButtonAction(shipLoadNameAll);
  addRadioButtonAction(shipLoadNameInclude);
  addRadioButtonAction(shipLoadNameExclude);

  addComboBoxAction(comboBoxTypes);
  addComboBoxAction(comboBoxShipTypes);

  paneShipLoadControls->setVisible(false);
  paneShipLoads->setVisible(false);

  // load fields and enable buttons
  if (_track != NULL)
  {
   //_track->addPropertyChangeListener(this);
   trackName->setText(_track->getName());
   // only show ship loads for staging tracks
   paneShipLoadControls->setVisible(_track->getTrackType()==(Track::STAGING));
   paneShipLoads->setVisible(_track->getTrackType()==(Track::STAGING));

   updateButtons(true);
  }
  else
  {
   updateButtons(false);
  }

  // build menu
  // JMenuBar menuBar = new JMenuBar();
  // _toolMenu = new JMenu(tr("Tools"));
  // menuBar.add(_toolMenu);
  // setJMenuBar(menuBar);
  // load
  updateTypeComboBoxes();
  updateLoadComboBoxes();
  updateLoadNames();
  updateShipLoadNames();
  //panelLoads->layout()->addWidget(new QLabel("test item"));

  loadAndTypeCheckBox->setChecked(loadAndType);
  shipLoadAndTypeCheckBox->setChecked(shipLoadAndType);

  initMinimumSize(QSize(Control::panelWidth600, Control::panelHeight400));
 }

 // Save, Delete, Add
 /*public*/ void TrackLoadEditFrame::buttonActionPerformed(QWidget* ae) {
     if (_track == NULL) {
         return;
     }
     QPushButton* source = (QPushButton*)ae;
     if (source == saveTrackButton) {
         log->debug("track save button activated");
         save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
     if (source == addLoadButton) {
         QString loadName =  comboBoxLoads->currentText();
         if (loadAndTypeCheckBox->isChecked()) {
             loadName = comboBoxTypes->currentText() + CarLoad::SPLIT_CHAR + loadName;
         }
         _track->addLoadName(loadName);
         selectNextItemComboBox(comboBoxLoads);
     }
     if (source == deleteLoadButton) {
         QString loadName =  comboBoxLoads->currentText();
         if (loadAndTypeCheckBox->isChecked()) {
             loadName = comboBoxTypes->currentText() + CarLoad::SPLIT_CHAR + loadName;
         }
         _track->deleteLoadName(loadName);
         selectNextItemComboBox(comboBoxLoads);
     }
     if (source == deleteAllLoadsButton) {
         deleteAllLoads();
     }
     if (source == addShipLoadButton) {
         QString loadName =  comboBoxShipLoads->currentText();
         if (shipLoadAndTypeCheckBox->isChecked()) {
             loadName = comboBoxShipTypes->currentText() + CarLoad::SPLIT_CHAR + loadName;
         }
         _track->addShipLoadName(loadName);
         selectNextItemComboBox(comboBoxShipLoads);
     }
     if (source == deleteShipLoadButton) {
         QString loadName =  comboBoxShipLoads->currentText();
         if (shipLoadAndTypeCheckBox->isChecked()) {
             loadName = comboBoxShipTypes->currentText() + CarLoad::SPLIT_CHAR + loadName;
         }
         _track->deleteShipLoadName(loadName);
         selectNextItemComboBox(comboBoxShipLoads);
     }
     if (source == deleteAllShipLoadsButton) {
         deleteAllShipLoads();
     }
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*protected*/ void TrackLoadEditFrame::save() {
     checkForErrors();
     // save the last state of the "Use car type and load" checkbox
     loadAndType = loadAndTypeCheckBox->isChecked();
     shipLoadAndType = shipLoadAndTypeCheckBox->isChecked();
     // save location file
     OperationsXml::save();
 }

 /*protected*/ void TrackLoadEditFrame::updateButtons(bool enabled) {
     saveTrackButton->setEnabled(enabled);

     loadNameAll->setEnabled(enabled);
     loadNameInclude->setEnabled(enabled);
     loadNameExclude->setEnabled(enabled);
     loadAndTypeCheckBox->setEnabled(enabled);

     bool en = enabled
             && (_track->isAddCustomLoadsAnyStagingTrackEnabled() || _track->isAddCustomLoadsAnySpurEnabled() || _track
             ->isAddCustomLoadsEnabled());

     shipLoadNameAll->setEnabled(en);
     shipLoadNameInclude->setEnabled(en);
     shipLoadNameExclude->setEnabled(en);
     shipLoadAndTypeCheckBox->setEnabled(en);

     addShipLoadButton->setEnabled(en);
     deleteShipLoadButton->setEnabled(en);
     deleteAllShipLoadsButton->setEnabled(en);

     comboBoxShipLoads->setEnabled(en);
     comboBoxShipTypes->setEnabled(en);

 }

 /*public*/ void TrackLoadEditFrame::radioButtonActionPerformed(QWidget* ae) {
     log->debug("radio button activated");
     QRadioButton* source = (QRadioButton*)ae;
     if (source == loadNameAll) {
         _track->setLoadOption(Track::ALL_LOADS);
     }
     if (source == loadNameInclude) {
         _track->setLoadOption(Track::INCLUDE_LOADS);
     }
     if (source == loadNameExclude) {
         _track->setLoadOption(Track::EXCLUDE_LOADS);
     }
     if (source == shipLoadNameAll) {
         _track->setShipLoadOption(Track::ALL_LOADS);
     }
     if (source == shipLoadNameInclude) {
         _track->setShipLoadOption(Track::INCLUDE_LOADS);
     }
     if (source == shipLoadNameExclude) {
         _track->setShipLoadOption(Track::EXCLUDE_LOADS);
     }
 }

 // Car type combo box has been changed, show loads associated with this car type
 /*public*/ void TrackLoadEditFrame::comboBoxActionPerformed(QWidget* ae) {
     updateLoadComboBoxes();
 }

 /*private*/ void TrackLoadEditFrame::updateLoadComboBoxes() {
     QString carType =  comboBoxTypes->currentText();
     CarLoads::instance()->updateComboBox(carType, comboBoxLoads);
     carType =  comboBoxShipTypes->currentText();
     CarLoads::instance()->updateComboBox(carType, comboBoxShipLoads);
 }

 /*private*/ void TrackLoadEditFrame::updateLoadNames()
 {
  log->debug("Update load names");
  //panelLoads.removeAll();
  QLayoutItem* item;
  while ( ( item = panelLoads->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  if (_track != NULL)
  {
   // set radio button
   loadNameAll->setChecked(_track->getLoadOption()==(Track::ALL_LOADS));
   loadNameInclude->setChecked(_track->getLoadOption()==(Track::INCLUDE_LOADS));
   loadNameExclude->setChecked(_track->getLoadOption()==(Track::EXCLUDE_LOADS));

   pLoadControls->setVisible(!loadNameAll->isChecked());

   if (!loadNameAll->isChecked())
   {
    int x = 0;
    int y = 0; // vertical position in panel

    int numberOfLoads = getNumberOfCheckboxesPerLine() / 2 + 1;
    foreach (QString loadName, _track->getLoadNames())
    {
     QLabel* load = new QLabel();
     load->setText(loadName);
     addItemTop(panelLoads, load, x++, y);
     // limit the number of loads per line
     if (x > numberOfLoads) {
         y++;
         x = 0;
     }
    }
    update();
   }
  }
  else
  {
   loadNameAll->setChecked(true);
  }
  panelLoads->update();
  //panelLoads->repaint();
 }

 /*private*/ void TrackLoadEditFrame::updateShipLoadNames() {
     log->debug("Update ship load names");
     //panelShipLoads.removeAll();
     QLayoutItem* item;
     while ( ( item = panelShipLoads->layout()->takeAt( 0 ) ) != NULL )
     {
      delete item->widget();
      delete item;
     }
     if (_track != NULL) {
         // set radio button
         shipLoadNameAll->setChecked(_track->getShipLoadOption()==(Track::ALL_LOADS));
         shipLoadNameInclude->setChecked(_track->getShipLoadOption()==(Track::INCLUDE_LOADS));
         shipLoadNameExclude->setChecked(_track->getShipLoadOption()==(Track::EXCLUDE_LOADS));

         pShipLoadControls->setVisible(!shipLoadNameAll->isChecked());

         if (!shipLoadNameAll->isChecked()) {
             int x = 0;
             int y = 0; // vertical position in panel

             int numberOfLoads = getNumberOfCheckboxesPerLine() / 2 + 1;
             foreach (QString loadName, _track->getShipLoadNames()) {
                 QLabel* load = new QLabel();
                 load->setText(loadName);
                 addItemTop(panelShipLoads, load, x++, y);
                 // limit the number of loads per line
                 if (x > numberOfLoads) {
                     y++;
                     x = 0;
                 }
             }
             update();
         }
     } else {
         shipLoadNameAll->setChecked(true);
     }
     //panelShipLoads->repaint();
     panelShipLoads->update();
 }

 /*private*/ void TrackLoadEditFrame::deleteAllLoads() {
     if (_track != NULL) {
         foreach (QString loadName, _track->getLoadNames()) {
             _track->deleteLoadName(loadName);
         }
     }
 }

 /*private*/ void TrackLoadEditFrame::deleteAllShipLoads() {
     if (_track != NULL) {
         foreach (QString loadName, _track->getShipLoadNames()) {
             _track->deleteShipLoadName(loadName);
         }
     }
 }

 /*private*/ void TrackLoadEditFrame::updateTypeComboBoxes() {
     CarTypes::instance()->updateComboBox(comboBoxTypes);
     // remove car types not serviced by this location and track
     for (int i = comboBoxTypes->count() - 1; i >= 0; i--) {
         QString type = comboBoxTypes->itemText(i);
         if (_track != NULL && !_track->acceptsTypeName(type)) {
             comboBoxTypes->removeItem(comboBoxTypes->findText(type));
         }
     }
     CarTypes::instance()->updateComboBox(comboBoxShipTypes);
     // remove car types not serviced by this location and track
     for (int i = comboBoxShipTypes->count() - 1; i >= 0; i--) {
         QString type = comboBoxShipTypes->itemText(i);
         if (_track != NULL && !_track->acceptsTypeName(type)) {
             comboBoxShipTypes->removeItem(comboBoxShipTypes->findText(type));
         }
     }
 }

 /*private*/ void TrackLoadEditFrame::checkForErrors() {
     if (_track->getLoadOption()==(Track::INCLUDE_LOADS) && _track->getLoadNames().length() == 0
             || _track->getShipLoadOption()==(Track::INCLUDE_LOADS) && _track->getShipLoadNames().length() == 0) {
//         JOptionPane.showMessageDialog(this, tr("ErrorNeedLoads"), tr("ErrorNoLoads"),
//                 JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Error no Loads"),tr("You must add at least one load!"));
     }
 }

 /*public*/ void TrackLoadEditFrame::dispose() {
     if (_track != NULL) {
         //_track->removePropertyChangeListener(this);
      disconnect(_track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
     }
     //_location.removePropertyChangeListener(this);
     disconnect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarLoads.instance().removePropertyChangeListener(this);
     disconnect(CarLoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().removePropertyChangeListener(this);
     disconnect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }

 /*public*/ void TrackLoadEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Location::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::TYPES_CHANGED_PROPERTY)) {
         updateTypeComboBoxes();
     }
     if (e->getPropertyName()==(CarLoads::LOAD_NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarLoads::LOAD_CHANGED_PROPERTY)) {
         updateLoadComboBoxes();
         updateLoadNames();
         updateShipLoadNames();
     }
     if (e->getPropertyName()==(Track::LOADS_CHANGED_PROPERTY)) {
         updateLoadNames();
         updateShipLoadNames();
     }
     if (e->getPropertyName()==(Track::LOAD_OPTIONS_CHANGED_PROPERTY)) {
         if (_track != NULL) {
             updateButtons(true);
         }
     }
 }

 /*public*/ QString TrackLoadEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.tools.TrackLoadEditFrame";
 }

}
