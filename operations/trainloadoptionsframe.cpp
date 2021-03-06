#include "trainloadoptionsframe.h"
#include "control.h"
#include "jcombobox.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QPushButton>
#include "train.h"
#include <QLabel>
#include <QScrollArea>
#include "cartypes.h"
#include "carloads.h"
#include <QButtonGroup>
#include <QRadioButton>
#include "traineditframe.h"
#include "flowlayout.h"
#include "logger.h"
#include "operationsxml.h"
#include "setup.h"
#include "carload.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * Frame for user edit of a train's load options
  *
  * @author Dan Boudreau Copyright (C) 2013
  * @version $Revision: 23502 $
  */
 ///*public*/ class TrainLoadOptionsFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 3409582934081412947L;


 /*public*/ /*static*/ /*final*/ QString TrainLoadOptionsFrame::DISPOSE = "dispose"; // NOI18N
 /*private*/ /*static*/ bool TrainLoadOptionsFrame::loadAndType =false;

 /*public*/ TrainLoadOptionsFrame::TrainLoadOptionsFrame(QWidget* parent)
     : OperationsFrame(tr("Load Options"),parent)
 {
     //super(tr("MenuItemLoadOptions"));
 log = new Logger("TrainLoadOptionsFrame");
  _train = NULL;

  pLoadControls = new QWidget();
  panelLoads = new QWidget();
  paneLoads = new QScrollArea(/*panelLoads*/);

  // labels
  trainName = new QLabel();
  trainDescription = new QLabel();

  // major buttons
  addLoadButton = new QPushButton(tr("Add Load"));
  deleteLoadButton = new QPushButton(tr("Delete Load"));
  deleteAllLoadsButton = new QPushButton(tr("Delete All"));
  saveTrainButton = new QPushButton(tr("Save Train"));

  // radio buttons
  loadNameAll = new QRadioButton(tr("Accept All"));
  loadNameInclude = new QRadioButton(tr("Accept Only"));
  loadNameExclude = new QRadioButton(tr("Exclude"));

  loadGroup = new QButtonGroup();

  // check boxes
  loadAndTypeCheckBox = new QCheckBox(tr("Use car type and load"));

  // text field
  // combo boxes
  comboBoxTypes = ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getComboBox();
  comboBoxLoads = ((CarLoads*)InstanceManager::getDefault("CarLoads"))->getComboBox(NULL);
 }

 /*public*/ void TrainLoadOptionsFrame::initComponents(TrainEditFrame* parent)
 {
  //->setChildFrame(this);
  _train = parent->_train;

  //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
  // Layout the panel by rows
  QWidget* p1 = new QWidget();
  p1->setLayout(new QHBoxLayout); //(p1, BoxLayout.X_AXIS));
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
  p3->setLayout(new QVBoxLayout); //(p3, BoxLayout.Y_AXIS));
  QScrollArea* pane3 = new QScrollArea(/*p3*/);
  p3Frame->layout()->addWidget(pane3);
  pane3->setWidgetResizable(true);
  //pane3->setBorder(BorderFactory.createTitledBorder(tr("LoadsTrain")));
  p3Frame->setStyleSheet(gbStyleSheet);
  p3Frame->setTitle(tr("Select loads serviced by this train"));
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
  QGroupBox* panelLoadsFrame = new QGroupBox;
  panelLoadsFrame->setLayout(new QVBoxLayout);
  panelLoads->setLayout(new GridBagLayout());
  panelLoadsFrame->layout()->addWidget(paneLoads);
  paneLoads->setWidgetResizable(true);
  //paneLoads->setBorder(BorderFactory.createTitledBorder(tr("Loads")));
  panelLoadsFrame->setStyleSheet(gbStyleSheet);
  panelLoadsFrame->setTitle(tr("Loads"));

  QButtonGroup* loadGroup = new QButtonGroup();
  loadGroup->addButton(loadNameAll);
  loadGroup->addButton(loadNameInclude);
  loadGroup->addButton(loadNameExclude);

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
  paneLoads->setWidget(panelLoads);
  thisLayout->addWidget(panelLoadsFrame);
  thisLayout->addWidget(panelButtons);

  // setup buttons
  addButtonAction(saveTrainButton);

  addButtonAction(deleteLoadButton);
  addButtonAction(deleteAllLoadsButton);
  addButtonAction(addLoadButton);

  addRadioButtonAction(loadNameAll);
  addRadioButtonAction(loadNameInclude);
  addRadioButtonAction(loadNameExclude);

  addComboBoxAction(comboBoxTypes);

  if (_train != NULL)
  {
   trainName->setText(_train->getName());
   trainDescription->setText(_train->getDescription());
   updateButtons(true);
   // listen for train changes
   //_train->addPropertyChangeListener(this);
   connect(_train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  else
  {
   updateButtons(false);
  }
  addHelpMenu("package.jmri.jmrit.operations.Operations_TrainLoadOptions", true); // NOI18N
  updateTypeComboBoxes();
  updateLoadComboBoxes();
  updateLoadNames();

  // get notified if car roads, loads, and owners gets modified
  //CarTypes::instance().addPropertyChangeListener(this);
  connect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarLoads.instance().addPropertyChangeListener(this);
  connect(((CarLoads*)InstanceManager::getDefault("CarLoads")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  loadAndTypeCheckBox->setChecked(loadAndType);

  initMinimumSize(QSize(Control::panelWidth600, Control::panelHeight400));
 }

 // Save
 /*public*/ void TrainLoadOptionsFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (_train != NULL) {
         if (source == saveTrainButton) {
             log->debug("train save button activated");
             saveTrain();
         }
         if (source == addLoadButton) {
             QString loadName =  comboBoxLoads->currentText();
             if (loadAndTypeCheckBox->isChecked()) {
                 loadName = comboBoxTypes->currentText() + CarLoad::SPLIT_CHAR + loadName;
             }
             if (_train->addLoadName(loadName)) {
                 updateLoadNames();
             }
             selectNextItemComboBox(comboBoxLoads);
         }
         if (source == deleteLoadButton) {
             QString loadName =  comboBoxLoads->currentText();
             if (loadAndTypeCheckBox->isChecked()) {
                 loadName = comboBoxTypes->currentText() + CarLoad::SPLIT_CHAR + loadName;
             }
             if (_train->deleteLoadName(loadName)) {
                 updateLoadNames();
             }
             selectNextItemComboBox(comboBoxLoads);
         }
         if (source == deleteAllLoadsButton) {
             deleteAllLoads();
         }
     }
 }

 /*public*/ void TrainLoadOptionsFrame::radioButtonActionPerformed(QWidget* ae) {
 QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (_train != NULL) {
         if (source == loadNameAll) {
             _train->setLoadOption(Train::ALL_LOADS);
             updateLoadNames();
         }
         if (source == loadNameInclude) {
             _train->setLoadOption(Train::INCLUDE_LOADS);
             updateLoadNames();
         }
         if (source == loadNameExclude) {
             _train->setLoadOption(Train::EXCLUDE_LOADS);
             updateLoadNames();
         }
     }
 }

 // Car type combo box has been changed, show loads associated with this car type
 /*public*/ void TrainLoadOptionsFrame::comboBoxActionPerformed(QWidget*ae) {
 JComboBox* source = (JComboBox*)ae;
     if (source == comboBoxTypes) {
         updateLoadComboBoxes();
     }
 }

 /*protected*/ void TrainLoadOptionsFrame::updateButtons(bool enabled) {
     saveTrainButton->setEnabled(enabled);

     loadNameAll->setEnabled(enabled);
     loadNameInclude->setEnabled(enabled);
     loadNameExclude->setEnabled(enabled);
     loadAndTypeCheckBox->setEnabled(enabled);
 }

 /*private*/ void TrainLoadOptionsFrame::updateLoadNames()
 {
  log->debug("Update load names");
  //panelLoads.removeAll();
  QLayoutItem* item;
  while ( ( item = panelLoads->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  if (_train != NULL)
  {
   // set radio button
   loadNameAll->setChecked(_train->getLoadOption()==(Train::ALL_LOADS));
   loadNameInclude->setChecked(_train->getLoadOption()==(Train::INCLUDE_ROADS));
   loadNameExclude->setChecked(_train->getLoadOption()==(Train::EXCLUDE_ROADS));

   pLoadControls->setVisible(!loadNameAll->isChecked());

   if (!loadNameAll->isChecked())
   {
    int x = 0;
    int y = 0; // vertical position in panel

    int numberOfLoads = getNumberOfCheckboxesPerLine() / 2 + 1;
    foreach (QString loadName, _train->getLoadNames())
    {
     QLabel* load = new QLabel();
     load->setText(loadName);
     addItemTop(panelLoads, load, x++, y);
     // limit the number of loads per line
     if (x > numberOfLoads)
     {
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
  //panelLoads->repaint();
  panelLoads->update();
 }

 /*private*/ void TrainLoadOptionsFrame::deleteAllLoads() {
     if (_train != NULL) {
         foreach (QString load, _train->getLoadNames()) {
             _train->deleteLoadName(load);
         }
     }
     updateLoadNames();
 }

 /*private*/ void TrainLoadOptionsFrame::saveTrain() {
     // save the last state of the "Use car type and load" checkbox
     loadAndType = loadAndTypeCheckBox->isChecked();
     OperationsXml::save();
     if (Setup::isCloseWindowOnSaveEnabled()) {
         dispose();
     }
 }

 /*private*/ void TrainLoadOptionsFrame::updateTypeComboBoxes() {
     ((CarTypes*)InstanceManager::getDefault("CarTypes"))->updateComboBox(comboBoxTypes);
     // remove types not serviced by this train
     for (int i = comboBoxTypes->count() - 1; i >= 0; i--) {
         QString type = comboBoxTypes->itemText(i);
         if (_train != NULL && !_train->acceptsTypeName(type)) {
             comboBoxTypes->removeItem(comboBoxTypes->findText(type));
         }
     }
 }

 /*private*/ void TrainLoadOptionsFrame::updateLoadComboBoxes() {
     QString carType =  comboBoxTypes->currentText();
     ((CarLoads*)InstanceManager::getDefault("CarLoads"))->updateComboBox(carType, comboBoxLoads);
 }

 /*public*/ void TrainLoadOptionsFrame::dispose() {
     //CarTypes.instance().removePropertyChangeListener(this);
 disconnect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarLoads.instance().removePropertyChangeListener(this);
 disconnect(((CarLoads*)InstanceManager::getDefault("CarLoads")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (_train != NULL) {
         //_train->removePropertyChangeListener(this);
      disconnect(_train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     OperationsFrame::dispose();
 }

 /*public*/ void TrainLoadOptionsFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarLoads::LOAD_NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarLoads::LOAD_CHANGED_PROPERTY)) {
         updateLoadComboBoxes();
         updateLoadNames();
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::TYPES_CHANGED_PROPERTY)) {
         updateTypeComboBoxes();
     }
 }
/*public*/ QString TrainLoadOptionsFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.TrainLoadOptionsFrame";
}

}
