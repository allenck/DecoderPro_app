#include "trainroadoptionsframe.h"
#include "train.h"
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QScrollArea>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include "carroads.h"
#include "traineditframe.h"
#include "flowlayout.h"
#include "cartypes.h"
#include "control.h"
#include "logger.h"
#include "operationsxml.h"
#include "setup.h"
#include <QLabel>

namespace Operations
{
/**
 * Frame for user edit of a train's road options
 *
 * @author Dan Boudreau Copyright (C) 2013
 * @version $Revision: 23502 $
 */
///*public*/ class TrainRoadOptionsFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 4077306284213827815L;


 /*public*/ /*static*/ /*final*/ QString TrainRoadOptionsFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ TrainRoadOptionsFrame::TrainRoadOptionsFrame(QWidget* parent)
   : OperationsFrame(tr("Road Options"), parent)
 {
     //super(tr("MenuItemRoadOptions"));
 log = new Logger("TrainRoadOptionsFrame");
     _train = NULL;

     pRoadControls = new QWidget();
     panelRoads = new QGroupBox();
     paneRoads = new QScrollArea(/*panelRoads*/);

     // labels
     trainName = new QLabel();
     trainDescription = new QLabel();

     // major buttons
     addRoadButton = new QPushButton(tr("Add Road"));
     deleteRoadButton = new QPushButton(tr("Delete Road"));
     deleteAllRoadsButton = new QPushButton(tr("Delete All"));
     saveTrainButton = new QPushButton(tr("Save Train"));

     // radio buttons
     roadNameAll = new QRadioButton(tr("Accept All"));
     roadNameInclude = new QRadioButton(tr("Accept Only"));
     roadNameExclude = new QRadioButton(tr("Exclude"));

     roadGroup = new QButtonGroup();

     // check boxes
     // text field
     // combo boxes
     comboBoxRoads = CarRoads::instance()->getComboBox();
 }

 /*public*/ void TrainRoadOptionsFrame::initComponents(TrainEditFrame* parent) {

     //parent->setChildFrame(this);
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
     pName->setTitle(tr("Name"));
     addItem(pName, trainName, 0, 0);

     // row 1b
     QGroupBox* pDesc = new QGroupBox();
     pDesc->setLayout(new GridBagLayout());
     //pDesc->setBorder(BorderFactory.createTitledBorder(tr("Description")));
     pDesc->setStyleSheet(gbStyleSheet);
     pDesc->setTitle(tr("Description"));
     addItem(pDesc, trainDescription, 0, 0);

     p1->layout()->addWidget(pName);
     p1->layout()->addWidget(pDesc);

     // row 3
     QGroupBox* p3Frame = new QGroupBox;
     p3Frame->setLayout(new QVBoxLayout);
     QWidget* p3 = new QWidget();
     p3->setLayout(new QVBoxLayout);//(p3, BoxLayout.Y_AXIS));
     QScrollArea* pane3 = new QScrollArea(/*p3*/);
     p3Frame->layout()->addWidget(pane3);
     pane3->setWidgetResizable(true);
     //pane3->setBorder(BorderFactory.createTitledBorder(tr("RoadsTrain")));
     p3Frame->setStyleSheet(gbStyleSheet);
     p3Frame->setTitle(tr("Select roads serviced by this train"));
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

     // row 4
     QGroupBox* panelRoadsFrame = new QGroupBox;
     panelRoadsFrame->setLayout(new QVBoxLayout);
     panelRoads->setLayout(new GridBagLayout());
     //paneRoads->setBorder(BorderFactory.createTitledBorder(tr("Roads")));
     panelRoadsFrame->layout()->addWidget(paneRoads);
     paneRoads->setWidgetResizable(true);
     panelRoadsFrame->setStyleSheet(gbStyleSheet);
     panelRoadsFrame->setTitle(tr("Roads"));

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
     addItem(panelButtons, saveTrainButton, 0, 0);

     thisLayout->addWidget(p1);
     pane3->setWidget(p3);
     thisLayout->addWidget(p3Frame);
     paneRoads->setWidget(panelRoads);
     thisLayout->addWidget(panelRoadsFrame);
     thisLayout->addWidget(panelButtons);

     // setup buttons
     addButtonAction(saveTrainButton);

     addButtonAction(deleteRoadButton);
     addButtonAction(deleteAllRoadsButton);
     addButtonAction(addRoadButton);

     addRadioButtonAction(roadNameAll);
     addRadioButtonAction(roadNameInclude);
     addRadioButtonAction(roadNameExclude);

     if (_train != NULL) {
         trainName->setText(_train->getName());
         trainDescription->setText(_train->getDescription());
         updateButtons(true);
         // listen for train changes
         //_train->addPropertyChangeListener(this);
         connect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     } else {
         updateButtons(false);
     }
     addHelpMenu("package.jmri.jmrit.operations.Operations_TrainRoadOptions", true); // NOI18N
     updateRoadComboBoxes();
     updateRoadNames();

     // get notified if car roads, roads, and owners gets modified
     //CarTypes.instance().addPropertyChangeListener(this);
     connect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarRoads.instance().addPropertyChangeListener(this);
     connect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight400));
 }

 // Save
 /*public*/ void TrainRoadOptionsFrame::buttonActionPerformed(QWidget* ae)
 {
  QPushButton* source = (QPushButton*)ae;
     if (_train != NULL) {
         if (source == saveTrainButton) {
             log->debug("train save button activated");
             saveTrain();
         }
         if (source == addRoadButton) {
             QString roadName =  comboBoxRoads->currentText();
             if (_train->addRoadName(roadName)) {
                 updateRoadNames();
             }
             selectNextItemComboBox(comboBoxRoads);
         }
         if (source == deleteRoadButton) {
             QString roadName =  comboBoxRoads->currentText();
             if (_train->deleteRoadName(roadName)) {
                 updateRoadNames();
             }
             selectNextItemComboBox(comboBoxRoads);
         }
         if (source == deleteAllRoadsButton) {
             deleteAllRoads();
         }
     }
 }

 /*public*/ void TrainRoadOptionsFrame::radioButtonActionPerformed(QWidget* ae)
{
 QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (_train != NULL) {
         if (source == roadNameAll) {
             _train->setRoadOption(Train::ALL_LOADS);
             updateRoadNames();
         }
         if (source == roadNameInclude) {
             _train->setRoadOption(Train::INCLUDE_LOADS);
             updateRoadNames();
         }
         if (source == roadNameExclude) {
             _train->setRoadOption(Train::EXCLUDE_LOADS);
             updateRoadNames();
         }
     }
 }

 /*protected*/ void TrainRoadOptionsFrame::updateButtons(bool enabled) {
     saveTrainButton->setEnabled(enabled);

     roadNameAll->setEnabled(enabled);
     roadNameInclude->setEnabled(enabled);
     roadNameExclude->setEnabled(enabled);
 }

 /*private*/ /*static*/ /*final*/ int TrainRoadOptionsFrame::NUMBER_ROADS_PER_LINE = 6;

 /*private*/ void TrainRoadOptionsFrame::updateRoadNames() {
     log->debug("Update road names");
     //panelRoads.removeAll();
     QLayoutItem* item;
     while ( ( item = panelRoads->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     if (_train != NULL) {
         // set radio button
         roadNameAll->setChecked(_train->getRoadOption()==(Train::ALL_LOADS));
         roadNameInclude->setChecked(_train->getRoadOption()==(Train::INCLUDE_ROADS));
         roadNameExclude->setChecked(_train->getRoadOption()==(Train::EXCLUDE_ROADS));

         pRoadControls->setVisible(!roadNameAll->isChecked());

         if (!roadNameAll->isChecked()) {
             int x = 0;
             int y = 0; // vertical position in panel

             foreach (QString roadName, _train->getRoadNames()) {
                 QLabel* road = new QLabel();
                 road->setText(roadName);
                 addItemTop(panelRoads, road, x++, y);
                 // limit the number of roads per line
                 if (x > NUMBER_ROADS_PER_LINE) {
                     y++;
                     x = 0;
                 }
             }
             update();
         }
     } else {
         roadNameAll->setChecked(true);
     }
     //panelRoads->repaint();
     panelRoads->update();
 }

 /*private*/ void TrainRoadOptionsFrame::deleteAllRoads() {
     if (_train != NULL) {
         foreach (QString road, _train->getRoadNames()) {
             _train->deleteRoadName(road);
         }
     }
     updateRoadNames();
 }

 /*private*/ void TrainRoadOptionsFrame::saveTrain() {
     // save the last state of the "Use car type and road" checkbox
     OperationsXml::save();
     if (Setup::isCloseWindowOnSaveEnabled()) {
         dispose();
     }
 }

 /*private*/ void TrainRoadOptionsFrame::updateRoadComboBoxes() {
     CarRoads::instance()->updateComboBox(comboBoxRoads);
 }

 /*public*/ void TrainRoadOptionsFrame::dispose() {
     //CarTypes.instance().removePropertyChangeListener(this);
 disconnect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarRoads.instance().removePropertyChangeListener(this);
 connect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (_train != NULL) {
         //_train->removePropertyChangeListener(this);
      disconnect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     OperationsFrame::dispose();
 }

 /*public*/ void TrainRoadOptionsFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::showProperty) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarRoads::CARROADS_CHANGED_PROPERTY)) {
         updateRoadComboBoxes();
         updateRoadNames();
     }
 }
}
