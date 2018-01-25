#include "trackroadeditframe.h"
#include "propertychangeevent.h"
#include "control.h"
#include "location.h"
#include "track.h"
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QScrollArea>
#include "carroads.h"
#include <QLabel>
#include <gridbaglayout.h>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QButtonGroup>
#include "setup.h"
#include "operationsxml.h"
#include <QComboBox>
#include "logger.h"
#include <QCheckBox>
#include <QMessageBox>

namespace Operations
{
/**
 * Frame for user edit of track roads
 *
 * @author Dan Boudreau Copyright (C) 2013, 2014
 * @version $Revision: 22371 $
 */
///*public*/ class TrackRoadEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static /*final*/ long serialVersionUID = -2432450380175043238L;

 /*public*/ /*static*/ /*final*/ QString TrackRoadEditFrame::DISPOSE = "dispose"; // NOI18N
 /*public*/ /*static*/ /*final*/ int TrackRoadEditFrame::MAX_NAME_LENGTH = Control::max_len_string_track_name;

 /*public*/ TrackRoadEditFrame::TrackRoadEditFrame(QWidget* parent)
     : OperationsFrame(tr("Edit Track Roads"), parent)
 {
  //super(tr("TitleEditTrackRoads"));
  log = new Logger("TrackRoadEditFrame");
   _location = NULL;
  _track = NULL;

  // panels
  pRoadControls = new QGroupBox();
  panelRoads = new QWidget();
  paneRoads = new QScrollArea(/*panelRoads*/);

  // major buttons
  saveTrackButton = new QPushButton(tr("SaveTrack"));
  addRoadButton = new QPushButton(tr("AddRoad"));
  deleteRoadButton = new QPushButton(tr("DeleteRoad"));
  deleteAllRoadsButton = new QPushButton(tr("DeleteAll"));

  // radio buttons
  roadNameAll = new QRadioButton(tr("AcceptAll"));
  roadNameInclude = new QRadioButton(tr("AcceptOnly"));
  roadNameExclude = new QRadioButton(tr("Exclude"));

  // combo box
  comboBoxRoads = CarRoads::instance()->getComboBox();

  // labels
  trackName = new QLabel();

 }

 /*public*/ void TrackRoadEditFrame::initComponents(Location* location, Track* track) {
     _location = location;
     _track = track;

     // property changes
     // listen for car road name changes
     //CarRoads::instance().addPropertyChangeListener(this);
     connect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

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
     p3->setLayout(new QVBoxLayout); //(p3, BoxLayout.Y_AXIS));
     QScrollArea* pane3 = new QScrollArea(/*p3*/);
     pane3->setWidgetResizable(true);
     //pane3->setBorder(BorderFactory.createTitledBorder(tr("RoadsTrack")));
     p3Frame->setStyleSheet(gbStyleSheet);
     p3Frame->setTitle(tr("Select the roads serviced by this track"));
     pane3->setMaximumSize(QSize(2000, 400));

     QWidget* pRoadRadioButtons = new QWidget();
     pRoadRadioButtons->setLayout(new FlowLayout());

     pRoadRadioButtons->layout()->addWidget(roadNameAll);
     pRoadRadioButtons->layout()->addWidget(roadNameInclude);
     pRoadRadioButtons->layout()->addWidget(roadNameExclude);

     pRoadControls->setLayout(new FlowLayout());

     pRoadControls->layout()->addWidget(comboBoxRoads);
     pRoadControls->layout()->addWidget(addRoadButton);
     pRoadControls->layout()->addWidget(deleteRoadButton);
     pRoadControls->layout()->addWidget(deleteAllRoadsButton);

     pRoadControls->setVisible(false);

     p3->layout()->addWidget(pRoadRadioButtons);
     p3->layout()->addWidget(pRoadControls);
     pane3->setWidget(p3);

     // row 4
     QGroupBox* paneRoadsFrame= new QGroupBox;
     paneRoadsFrame->setLayout(new QVBoxLayout);
     paneRoadsFrame->layout()->addWidget(paneRoads);
     paneRoads->setWidgetResizable(true);
     panelRoads->setLayout(new GridBagLayout());
     //paneRoads->setBorder(BorderFactory.createTitledBorder(tr("Roads")));
     paneRoadsFrame->setStyleSheet(gbStyleSheet);
     paneRoadsFrame->setTitle(tr("Roads"));

     QButtonGroup* roadGroup = new QButtonGroup();
     roadGroup->addButton(roadNameAll);
     roadGroup->addButton(roadNameInclude);
     roadGroup->addButton(roadNameExclude);

     // row 12
     QGroupBox* panelButtons = new QGroupBox();
     panelButtons->setLayout(new GridBagLayout());
     //panelButtons->setBorder(BorderFactory.createTitledBorder(""));
     panelButtons->setStyleSheet(gbStyleSheet);
     panelButtons->setMaximumSize(QSize(2000, 200));

     // row 13
     addItem(panelButtons, saveTrackButton, 0, 0);

     thisLayout->addWidget(p1);
     thisLayout->addWidget(pane3);
     paneRoads->setWidget(panelRoads);
     thisLayout->addWidget(paneRoadsFrame);
     thisLayout->addWidget(panelButtons);

     // setup buttons
     addButtonAction(saveTrackButton);

     addButtonAction(deleteRoadButton);
     addButtonAction(deleteAllRoadsButton);
     addButtonAction(addRoadButton);

     addRadioButtonAction(roadNameAll);
     addRadioButtonAction(roadNameInclude);
     addRadioButtonAction(roadNameExclude);

     // road fields and enable buttons
     if (_track != NULL) {
         //_track->addPropertyChangeListener(this);
      connect(_track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         trackName->setText(_track->getName());
         enableButtons(true);
     } else {
         enableButtons(false);
     }

     // build menu
     // JMenuBar menuBar = new JMenuBar();
     // _toolMenu = new JMenu(tr("Tools"));
     // menuBar.add(_toolMenu);
     // setJMenuBar(menuBar);
     // load
     updateRoadComboBox();
     updateRoadNames();

     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight400));
 }

 // Save, Delete, Add
 /*public*/ void TrackRoadEditFrame::buttonActionPerformed(QWidget* ae)
 {
  if (_track == NULL) {
      return;
  }
  QPushButton* source =(QPushButton*)ae;
  if (source == saveTrackButton) {
      log->debug("track save button activated");
      checkForErrors();
      OperationsXml::save();
      if (Setup::isCloseWindowOnSaveEnabled()) {
          dispose();
      }
  }
  if (source == addRoadButton) {
      _track->addRoadName( comboBoxRoads->currentText());
      selectNextItemComboBox(comboBoxRoads);
  }
  if (source == deleteRoadButton) {
      _track->deleteRoadName( comboBoxRoads->currentText());
      selectNextItemComboBox(comboBoxRoads);
  }
  if (source == deleteAllRoadsButton) {
      deleteAllRoads();
  }
 }

 /*protected*/ void TrackRoadEditFrame::enableButtons(bool enabled) {
     saveTrackButton->setEnabled(enabled);
     roadNameAll->setEnabled(enabled);
     roadNameInclude->setEnabled(enabled);
     roadNameExclude->setEnabled(enabled);
 }

 /*public*/ void TrackRoadEditFrame::radioButtonActionPerformed(QWidget* ae) {
     log->debug("radio button activated");
     QRadioButton* source = (QRadioButton*)ae;
     if (source == roadNameAll) {
         _track->setRoadOption(Track::ALL_ROADS);
     }
     if (source == roadNameInclude) {
         _track->setRoadOption(Track::INCLUDE_ROADS);
     }
     if (source == roadNameExclude) {
         _track->setRoadOption(Track::EXCLUDE_ROADS);
     }
 }

 /*private*/ void TrackRoadEditFrame::updateRoadComboBox()
 {
  CarRoads::instance()->updateComboBox(comboBoxRoads);
 }

 /*private*/ void TrackRoadEditFrame::updateRoadNames()
 {
  log->debug("Update road names");
  //panelRoads->removeAll();
  QLayoutItem* item;
  while ( ( item = panelRoads->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }

  if (_track != NULL)
  {
   // set radio button
   roadNameAll->setChecked(_track->getRoadOption()==(Track::ALL_ROADS));
   roadNameInclude->setChecked(_track->getRoadOption()==(Track::INCLUDE_ROADS));
   roadNameExclude->setChecked(_track->getRoadOption()==(Track::EXCLUDE_ROADS));

   pRoadControls->setVisible(!roadNameAll->isChecked());

   if (!roadNameAll->isChecked()) {
       int x = 0;
       int y = 0; // vertical position in panel

       int numberOfRoads = getNumberOfCheckboxesPerLine();
       foreach (QString roadName, _track->getRoadNames()) {
           QLabel* road = new QLabel();
           road->setText(roadName);
           addItemTop(panelRoads, road, x++, y);
           // limit the number of roads per line
           if (x > numberOfRoads) {
               y++;
               x = 0;
           }
       }
       update();
   }
  }
  else
  {
   roadNameAll->setChecked(true);
  }
  //panelRoads->repaint();
  panelRoads->update();
 }

 /*private*/ void TrackRoadEditFrame::deleteAllRoads() {
     if (_track != NULL) {
         foreach (QString roadName, _track->getRoadNames()) {
             _track->deleteRoadName(roadName);
         }
     }
 }

 /*public*/ void TrackRoadEditFrame::checkBoxActionPerformed(QWidget* ae) {
     QCheckBox* b = (QCheckBox*) ae;
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

 /*private*/ void TrackRoadEditFrame::checkForErrors() {
     if (_track->getRoadOption()==(Track::INCLUDE_ROADS) && _track->getRoadNames().length() == 0) {
//         JOptionPane.showMessageDialog(this, tr("ErrorNeedRoads"), tr("ErrorNoRoads"),
//                 JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Error no roads"), tr("You must add at least one road!"));
     }
 }

 /*public*/ void TrackRoadEditFrame::dispose() {
     if (_track != NULL) {
         //_track->removePropertyChangeListener(this);
      disconnect(_track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     //CarRoads.instance().removePropertyChangeListener(this);
     disconnect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }

 /*public*/ void TrackRoadEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::showProperty) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarRoads::CARROADS_CHANGED_PROPERTY)) {
         updateRoadComboBox();
         updateRoadNames();
     }
     if (e->getPropertyName()==(Track::ROADS_CHANGED_PROPERTY)) {
         updateRoadNames();
     }
 }
}
