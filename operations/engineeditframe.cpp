#include "engineeditframe.h"
#include "enginemanager.h"
#include "enginemanagerxml.h"
#include "enginemodels.h"
#include "locationmanager.h"
#include "logger.h"
#include <QPushButton>
#include "jcombobox.h"
#include "jtextfield.h"
#include "control.h"
#include <QGroupBox>
#include <QGridLayout>
#include <QScrollArea>
#include "propertychangeevent.h"
#include "propertychangesupport.h"
#include "engineattributeeditframe.h"
#include "engine.h"
#include <QPushButton>
#include "location.h"
#include "carroads.h"
#include <QMessageBox>
#include <QCheckBox>
#include "setup.h"
#include "carmanagerxml.h"
#include "track.h"
#include "idtag.h"
#include "rosterentry.h"
#include "consist.h"
#include "idtagmanager.h"
#include "rosterentry.h"
#include "enginetypes.h"
#include "carowners.h"
#include "enginelengths.h"
#include "joptionpane.h"
#include "abstractidtag.h"
#include "loggerfactory.h"
#include "gridbaglayout.h"
#include "borderfactory.h"
#include "consistmanager.h"

//EditEnginesFrame::EditEnginesFrame(QWidget *parent) :
//  OperationsFrame(parent)
//{
//}

namespace Operations
{
/**
 * Frame for user edit of engine
 *
 * @author Dan Boudreau Copyright (C) 2008, 2011
 * @version $Revision: 29493 $
 */
///*public*/ class EngineEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {
    /**
     *
     */
 ///*private*/ static final long serialVersionUID = 7527604846983933144L;
 /*public static final*/ QString EngineEditFrame::ROAD = tr("Road");
 /*public static final*/ QString EngineEditFrame::MODEL = tr("Model");
 /*public static final*/ QString EngineEditFrame::TYPE = tr("Type");
 /*public static final*/ QString EngineEditFrame::COLOR = tr("Color");
 /*public static final*/ QString EngineEditFrame::LENGTH = tr("Length");
 /*public static final*/ QString EngineEditFrame::OWNER = tr("Owner");
 /*public static final*/ QString EngineEditFrame::CONSIST = tr("Consist");

 /*private*/ /*static*/ /*final*/ QString EngineEditFrame::SPEED = "25"; // MPH for tractive effort to HP conversion

 /*public*/ EngineEditFrame::EngineEditFrame(QWidget *parent) :
  RollingStockEditFrame(tr("Edit Engine"), parent)
 {
  //super();
 }

 /*public*/ void EngineEditFrame::initComponents()
 {
  groupComboBox = ((ConsistManager*)InstanceManager::getDefault("Operations::ConsistManager"))->getComboBox();
  modelComboBox = engineModels->getComboBox();

  RollingStockEditFrame::initComponents();

  addButton->setText(tr("Engine Add"));

  // type options for engines
  addItem(pTypeOptions, bUnitCheckBox, 0, 1);

  // default check box selections
  bUnitCheckBox->setChecked(false);

  // set tips
  builtTextField->setToolTip(tr("Enter the year that the locomotive was built, use 4 digits "));
  editModelButton->setToolTip(tr("Add, delete or replace %1")
          .arg(tr("Model").toLower()));
  editGroupButton->setToolTip(tr("Add, delete or replace %1 names").arg(
                  tr("Consist").toLower()));
  bUnitCheckBox->setToolTip(tr("Select if locomotive is a booster unit"));

  deleteButton->setToolTip(tr("Removes this locomotive from the roster"));
  addButton->setToolTip(tr("Adds a locomotive to the roster"));
  saveButton->setToolTip(tr("Saves changes for this locomotive"));

  // row 3
  pModel->setLayout(new GridBagLayout());
  pModel->setBorder(BorderFactory::createTitledBorder(tr("Model")));
  addItem(pModel, modelComboBox, 1, 0);
  addItem(pModel, editModelButton, 2, 0);
  pModel->setVisible(true);

  // row 12
  pHp->setLayout(new GridBagLayout());
  pHp->setBorder(BorderFactory::createTitledBorder(tr("Hp")));
  addItem(pHp, hpTextField, 0, 0);
  pHp->setVisible(true);
  JPanel* pTe = new JPanel();
  pTe->setLayout(new GridBagLayout());
  pTe->setBorder(BorderFactory::createTitledBorder(tr("Tractive Effort")));
  addItem(pTe, teTextField, 0, 0);
  pPower->layout()->addWidget(pHp);
  pPower->layout()->addWidget(pTe);
  pPower->setVisible(true);

  teTextField->setToolTip(tr("Converts Tractive Effort (lbf) to Horse Power at %1 MPH. Press Save to convert.").arg( SPEED ));

  pGroup->setBorder(BorderFactory::createTitledBorder(tr("Consist")));

  addEditButtonAction(editModelButton);

  addComboBoxAction(modelComboBox);
  modelComboBox->setSelectedIndex(0);

  addHelpMenu("package.jmri.jmrit.operations.Operations_LocomotivesAdd", true); // NOI18N
 }

 //@Override
 /*protected*/ ResourceBundle* EngineEditFrame::getRb() {
     return rb;
 }

 //@Override
 /*protected*/ RollingStockAttribute* EngineEditFrame::getTypeManager() {
     return (EngineTypes*)InstanceManager::getDefault("EngineTypes");
 }

 //@Override
 /*protected*/ RollingStockAttribute* EngineEditFrame::getLengthManager() {
     return (EngineLengths*)InstanceManager::getDefault("EngineLengths");
 }

 /*public*/ void EngineEditFrame::load(Engine* engine)
 {
     if (!engineModels->containsName(engine->getModel())) {
         QString msg = tr("Model \"%1\" does not exist in your roster, add?").arg(
                 engine->getModel());
//         if (JOptionPane
//                 .showConfirmDialog(this, msg, tr("engineAddModel"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
         if(QMessageBox::question(this, tr("Add locomotive model?"), msg, QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
         {
             engineModels->addName(engine->getModel());
         }
     }
     modelComboBox->setCurrentIndex(modelComboBox->findText(engine->getModel()));

     RollingStockEditFrame::load(engine);

     pBlocking->setVisible(engine->getConsist() != nullptr);
     blockingTextField->setEnabled(false); // don't allow user to modify, only see
     bUnitCheckBox->setChecked(engine->isBunit());
     hpTextField->setText(engine->getHp());
     groupComboBox->setSelectedItem(engine->getConsistName());

     setTitle(tr("Edit Locomotive"));
 }

 // combo boxes
 /*public*/ void EngineEditFrame::comboBoxActionPerformed(QWidget* ae)
{
 JComboBox* source = (JComboBox*)ae;
  if (source == modelComboBox)
  {
      if (modelComboBox->currentText() != NULL) {
          QString model =  modelComboBox->currentText();
          // load the default hp and length for the model selected
          hpTextField->setText(engineModels->getModelHorsepower(model));
          weightTextField->setText(engineModels->getModelWeight(model));
          if (engineModels->getModelLength(model) != NULL && engineModels->getModelLength(model)!=("")) {
              lengthComboBox->setCurrentIndex(lengthComboBox->findText(engineModels->getModelLength(model)));
          }
          if (engineModels->getModelType(model) != NULL && engineModels->getModelType(model)!=("")) {
              typeComboBox->setCurrentIndex(typeComboBox->findText(engineModels->getModelType(model)));
          }
      }
  }
  if (source == locationBox)
  {
   if (locationBox->currentText() == NULL)
   {
    trackLocationBox->clear();
   }
   else
   {
    log->debug("EnginesSetFrame sees location: " + locationBox->currentText());
    Location* l;
    QVariant v = locationBox->currentData();
    if(v.isValid())
     l = VPtr<Operations::Location>::asPtr(locationBox->currentData());
    else
     l= locationManager->getLocationByName(locationBox->currentText());
    l->updateComboBox(trackLocationBox);
   }
  }
 }

 //@Override
/*protected*/ bool EngineEditFrame::check(RollingStock* engine) {
 // check to see if engine with road and number already exists
 Engine* existingEngine =
   (Engine*)engineManager->getByRoadAndNumber( roadComboBox->getSelectedItem(),
                   roadNumberTextField->text());
 if (existingEngine != nullptr) {
     if (engine == nullptr || existingEngine->getId() != (engine->getId())) {
         JOptionPane::showMessageDialog(this, tr("Locomotive with this road name and number already exists!"), tr("Can not update locomotive!"), JOptionPane::ERROR_MESSAGE);
         return false;
     }
 }
 return RollingStockEditFrame::check(engine);
}

/*private*/ void EngineEditFrame::save(bool isSave) {
  RollingStockEditFrame::save(engineManager, isSave);
  Engine* engine = (Engine*) _rs;

  engine->setBunit(bUnitCheckBox->isChecked());

  if (groupComboBox->getSelectedItem() != nullptr) {
     if (groupComboBox->getSelectedItem() ==(EngineManager::NONE)) {
         engine->setConsist(nullptr);
         engine->setBlocking(Engine::DEFAULT_BLOCKING_ORDER);
     } else if (engine->getConsistName() != (groupComboBox->getSelectedItem())) {
         engine->setConsist(((ConsistManager*)InstanceManager::getDefault("Operations::ConsistManager"))->getConsistByName(/*(String)*/ groupComboBox->getSelectedItem()));
         if (engine->getConsist() != nullptr) {
             engine->setBlocking(engine->getConsist()->getSize());
             blockingTextField->setText(QString::number(engine->getBlocking()));
         }
     }
  }
  pBlocking->setVisible(engine->getConsist() != nullptr);

  // confirm that horsepower is a number
  if (!hpTextField->text().trimmed().isEmpty()) {
      bool ok;
          hpTextField->text().toInt(&ok);
          engine->setHp(hpTextField->text());
      if(!ok) {
          JOptionPane::showMessageDialog(this, tr("Locomotive horsepower must be a number"),
                  tr("Can not save locomotive horsepower!"), JOptionPane::ERROR_MESSAGE);
      }
  }
 }

 //@Override
 /*protected*/ void EngineEditFrame::_delete() {
     Engine* engine = (Engine*)engineManager->getByRoadAndNumber(/*(String)*/ roadComboBox->getSelectedItem(), roadNumberTextField
             ->text());
     if (engine != nullptr) {
         engineManager->deregister(engine);
     }
 }

// edit buttons only one frame active at a time
 /*public*/ void EngineEditFrame::buttonEditActionPerformed(QWidget* ae)
{
  if (engineAttributeEditFrame != nullptr) {
      engineAttributeEditFrame->dispose();
  }
  engineAttributeEditFrame = new EngineAttributeEditFrame();
  //engineAttributeEditFrame->setLocationRelativeTo(this);
  engineAttributeEditFrame->addPropertyChangeListener(this);

  if (ae == editRoadButton) {
      engineAttributeEditFrame->initComponents(ROAD,  roadComboBox->currentText());
  }
  if (ae == editModelButton) {
      engineAttributeEditFrame->initComponents(MODEL,  modelComboBox->currentText());
  }
  if (ae == editTypeButton) {
      engineAttributeEditFrame->initComponents(TYPE,  typeComboBox->currentText());
  }
  if (ae == editLengthButton) {
      engineAttributeEditFrame->initComponents(LENGTH,  lengthComboBox->currentText());
  }
  if (ae == editOwnerButton) {
      engineAttributeEditFrame->initComponents(OWNER,  ownerComboBox->currentText());
  }
  if (ae == editGroupButton) {
   engineAttributeEditFrame->initComponents(EngineAttributeEditFrame::CONSIST,
           /*(String)*/ groupComboBox->getSelectedItem());
  }

 }

 //@Override
 /*protected*/ void EngineEditFrame::addPropertyChangeListeners() {
     engineModels->PropertyChangeSupport::addPropertyChangeListener(this);
     engineManager->PropertyChangeSupport::addPropertyChangeListener(this);
     RollingStockEditFrame::addPropertyChangeListeners();
 }

 //@Override
 /*protected*/ void EngineEditFrame::removePropertyChangeListeners() {
     engineModels->removePropertyChangeListener(this);
     engineManager->removePropertyChangeListener(this);
     if (_rs != nullptr) {
         _rs->removePropertyChangeListener(this);
     }
     RollingStockEditFrame::removePropertyChangeListeners();
 }

 /*public*/ void EngineEditFrame::propertyChange(PropertyChangeEvent* e) {
  if (Control::SHOW_PROPERTY) {
   log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg( e->getOldValue().toString()).arg(e->getNewValue().toString()));
  }
  RollingStockEditFrame::propertyChange(e);

  if (e->getPropertyName() == (EngineLengths::ENGINELENGTHS_CHANGED_PROPERTY)) {
   ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->updateComboBox(lengthComboBox);
   if (_rs != nullptr) {
       lengthComboBox->setSelectedItem(_rs->getLength());
   }
  }
  if (e->getPropertyName() == (EngineModels::ENGINEMODELS_CHANGED_PROPERTY)) {
      engineModels->updateComboBox(modelComboBox);
      if (_rs != nullptr) {
          modelComboBox->setSelectedItem(((Engine*) _rs)->getModel());
      }
  }
  if (e->getPropertyName() == (ConsistManager::LISTLENGTH_CHANGED_PROPERTY)) {
   ((ConsistManager*)InstanceManager::getDefault("Operations::ConsistManager"))->updateComboBox(groupComboBox);
      if (_rs != nullptr) {
          groupComboBox->setSelectedItem(((Engine*) _rs)->getConsistName());
      }
  }
  if (e->getPropertyName() == (EngineAttributeEditFrame::DISPOSE)) {
      engineAttributeEditFrame = nullptr;
  }
 }

 /*public*/ QString EngineEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.rollingstock.engines.EngineEditFrame";
 }
 /*public*/ EngineResourceBundle::EngineResourceBundle()
 {
  map.insert("RoadNumMustBeLess", tr("Locomotive road number must be less than 10 characters"));
  map.insert("RoadNumTooLong", tr("Locomotive road number too long!"));
  map.insert("WeightFormatTon", tr("Locomotive weight must be in the format of xx tons"));
  map.insert("WeightTonError", tr("Can not save locomotive weight!"));
  map.insert("rsFullySelect", tr("To place a locomotive, you must select the locomotive's's location and track"));
  map.insert("rsCanNotLoc", tr("Can not update locomotive location"));
  map.insert("rsType", tr("Car"));
 }
 /*private*/ /*final*/ /*static*/ Logger* EngineEditFrame::log = LoggerFactory::getLogger("EngineEditFrame");
}
