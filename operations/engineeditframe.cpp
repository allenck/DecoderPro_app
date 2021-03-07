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
#include "instancemanager.h"
#include "rosterentry.h"
#include "enginetypes.h"
#include "carowners.h"
#include "enginelengths.h"
#include "joptionpane.h"
#include "abstractidtag.h"

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

 /*public*/ EngineEditFrame::EngineEditFrame(QWidget *parent) :
  OperationsFrame(parent)
 {
 log = new Logger("EngineEditFrame");
        //super();
  manager = ((EngineManager*)InstanceManager::getDefault("EngineManager"));
  managerXml = ((EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml"));
  engineModels = (EngineModels*)InstanceManager::getDefault("EngineModels");
  engineTypes = ((EngineTypes*)InstanceManager::getDefault("EngineTypes"));
  engineLengths = ((EngineLengths*)InstanceManager::getDefault("EngineLengths"));
  carManagerXml = ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"));
  locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));

  // major buttons
  editRoadButton = new QPushButton(tr("Edit"));
  clearRoadNumberButton = new QPushButton(tr("Clear"));
  editModelButton = new QPushButton(tr("Edit"));
  editTypeButton = new QPushButton(tr("Edit"));
  editLengthButton = new QPushButton(tr("Edit"));
  fillWeightButton = new QPushButton();
  editConsistButton = new QPushButton(tr("Edit"));
  editOwnerButton = new QPushButton(tr("Edit"));

  saveButton = new QPushButton(tr("Save"));
  deleteButton = new QPushButton(tr("Delete"));
  addButton = new QPushButton(tr("Add"));
  _engine = NULL;

  // check boxes
  // text field
  roadNumberTextField = new JTextField(Control::max_len_string_road_number);
  builtTextField = new JTextField(Control::max_len_string_built_name + 3);
  hpTextField = new JTextField(8);
  weightTextField = new JTextField(Control::max_len_string_weight_name);
  commentTextField = new JTextField(35);
  valueTextField = new JTextField(8);

  // combo boxes
  roadComboBox = ((CarRoads*)InstanceManager::getDefault("CarRoads"))->getComboBox();
  modelComboBox = engineModels->getComboBox();
  typeComboBox = engineTypes->getComboBox();
  lengthComboBox = engineLengths->getComboBox();
  ownerComboBox = ((CarOwners*)InstanceManager::getDefault("CarOwners"))->getComboBox();
  locationBox = locationManager->getComboBox();
  trackLocationBox = new JComboBox();
  consistComboBox = manager->getConsistComboBox();
  rfidComboBox = new JComboBox();
  bUnitCheckBox = new QCheckBox(tr("B Unit"));
  editActive = false;
  buttonEditMapper = new QSignalMapper();
  connect(buttonEditMapper, SIGNAL(mapped(QWidget*)), this, SLOT(buttonEditActionPerformed(QWidget*)));

 }

 /*public*/ void EngineEditFrame::initComponents()
 {
     // set tips
     builtTextField->setToolTip(tr("Enter the year that the locomotive was built, use 4 digits "));
     rfidComboBox->setToolTip(tr("Enter locomotive's 12 digit Radio Frequency Identification"));
     editRoadButton->setToolTip(tr("Add, delete or replace %1")
             .arg(tr("Road").toLower()));
     editTypeButton->setToolTip(tr("Add, delete or replace %1").arg(tr("Type").toLower()));
     editModelButton->setToolTip(tr("Add, delete or replace %1")
             .arg(tr("Model").toLower()));
     editLengthButton->setToolTip(tr("Add, delete or replace %1")
            .arg(tr("Length").toLower()));
     editOwnerButton->setToolTip(tr("Add, delete or replace %1")
             .arg(tr("Owner").toLower()));
     editConsistButton->setToolTip(tr("Add, delete or replace %1")
             .arg(tr("Consist").toLower()));

     // create panel
     QWidget* pPanel = new QWidget();
     //pPanel.setLayout(new BoxLayout(pPanel, BoxLayout.Y_AXIS));
     QVBoxLayout* pPanelLayout = new QVBoxLayout(pPanel);

     // Layout the panel by rows
     // row 1
     QGroupBox* pRoad = new QGroupBox();
     pRoad->setStyleSheet(gbStyleSheet);
     //pRoad.setLayout(new GridBagLayout());
     QGridLayout* pRoadLayout = new QGridLayout(pRoad);
     //pRoad.setBorder(BorderFactory.createTitledBorder(tr("Road")));
     pRoad->setTitle(tr("Road"));
     addItem(pRoad, roadComboBox, 1, 0);
     addItem(pRoad, editRoadButton, 2, 0);
     pPanelLayout->addWidget(pRoad);

     // row 2
     QGroupBox* pRoadNumber = new QGroupBox();
     //pRoadNumber.setLayout(new GridBagLayout());
     QGridLayout* pRoadNumberLayout = new QGridLayout(pRoadNumber);
     //pRoadNumber.setBorder(BorderFactory.createTitledBorder(tr("RoadNumber")));
     pRoadNumber->setStyleSheet(gbStyleSheet);
     pRoadNumber->setTitle(tr("Road Number"));
     addItem(pRoadNumber,roadNumberTextField, 1, 0);
     addItem(pRoadNumber,clearRoadNumberButton, 2, 0);
     pPanelLayout->addWidget(pRoadNumber);

     // row 3
     QGroupBox* pModel = new QGroupBox();
     //pModel.setLayout(new GridBagLayout());
     QGridLayout* pModelLayout = new QGridLayout(pModel);
     //pModel.setBorder(BorderFactory.createTitledBorder(tr("Model")));
     pModel->setStyleSheet(gbStyleSheet);
     pModel->setTitle(tr("Model"));
     pModelLayout->addWidget(modelComboBox, 1, 0);
     pModelLayout->addWidget(editModelButton, 2, 0);
     pPanelLayout->addWidget(pModel);

     // row 4
     QGroupBox* pType = new QGroupBox();
     //pType.setLayout(new GridBagLayout());
     QGridLayout* pTypeLayout = new QGridLayout(pType);
     //pType.setBorder(BorderFactory.createTitledBorder(tr("Type")));
     pType->setStyleSheet(gbStyleSheet);
     pType->setTitle(tr("Type"));
     pTypeLayout->addWidget(typeComboBox, 1, 0);
     pTypeLayout->addWidget(editTypeButton, 2, 0);
     pPanelLayout->addWidget(pType);

     // row 5
     QGroupBox* pLength = new QGroupBox();
     //pLength.setLayout(new GridBagLayout());
     QGridLayout* pLengthLayout = new QGridLayout(pLength);
     //pLength.setBorder(BorderFactory.createTitledBorder(tr("Length")));
     pLength->setStyleSheet(gbStyleSheet);
     pLength->setTitle(tr("Length"));
     pLengthLayout->addWidget(lengthComboBox, 1, 0);
     pLengthLayout->addWidget(editLengthButton, 2, 0);
     pPanelLayout->addWidget(pLength);

     // row 6
     QGroupBox* pLocation = new QGroupBox();
     //pLocation.setLayout(new GridBagLayout());
     QGridLayout* pLocationLayout = new QGridLayout(pLocation);
     //pLocation.setBorder(BorderFactory.createTitledBorder(tr("Location and Track")));
     pLocation->setStyleSheet(gbStyleSheet);
     pLocation->setTitle(tr("LocationAndTrack"));
     pLocationLayout->addWidget(locationBox, 1, 0);
     pLocationLayout->addWidget(trackLocationBox, 2, 0);
     pPanelLayout->addWidget(pLocation);

     // optional panel
     QWidget* pOptional = new QWidget();
     //pOptional.setLayout(new BoxLayout(pOptional, BoxLayout.Y_AXIS));
     QVBoxLayout* pOptionalLayout = new QVBoxLayout(pOptional);
     QScrollArea* optionPane = new QScrollArea(/*pOptional*/);
     //optionPane.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutOptional")));
     QHBoxLayout* optionPaneLayout = new QHBoxLayout(optionPane);
     optionPaneLayout->addWidget(pOptional);

     // row 11
     QGroupBox* pWeightTons = new QGroupBox();
     //pWeightTons.setLayout(new GridBagLayout());
     QGridLayout* pWeightTonsLayout = new QGridLayout(pWeightTons);
     //pWeightTons.setBorder(BorderFactory.createTitledBorder(tr("WeightTons")));
     pWeightTons->setStyleSheet(gbStyleSheet);
     pWeightTons->setTitle(tr("Weight Tons"));
     pWeightTonsLayout->addWidget(weightTextField, 0, 0);
     pOptionalLayout->addWidget(pWeightTons);

     // row 12
     QGroupBox* pHp = new QGroupBox();
     //pHp.setLayout(new GridBagLayout());
     QGridLayout* pHpLayout = new QGridLayout(pHp);
     //pHp.setBorder(BorderFactory.createTitledBorder(tr("Hp")));
     pWeightTons->setStyleSheet(gbStyleSheet);
     pWeightTons->setTitle(tr("Horsepower"));
     pHpLayout->addWidget(hpTextField, 0, 0);
     pOptionalLayout->addWidget(pHp);

     // row 13
     QGroupBox* pConsist = new QGroupBox();
     //pConsist.setLayout(new GridBagLayout());
     QGridLayout* pConsistLayout = new QGridLayout(pConsist);

     //pConsist.setBorder(BorderFactory.createTitledBorder(tr("Consist")));
     pConsist->setStyleSheet(gbStyleSheet);
     pConsist->setTitle(tr("Consist"));
     pConsistLayout->addWidget(consistComboBox, 1, 0);
     pConsistLayout->addWidget(editConsistButton, 2, 0);
     pOptionalLayout->addWidget(pConsist);

     // row 14
     QGroupBox* pBuilt = new QGroupBox();
     //pBuilt.setLayout(new GridBagLayout());
     QGridLayout* pBuiltLayout = new QGridLayout(pBuilt);
     //pBuilt.setBorder(BorderFactory.createTitledBorder(tr("Built")));
     pBuilt->setStyleSheet(gbStyleSheet);
     pBuilt->setTitle(tr("Built"));
     pBuiltLayout->addWidget(builtTextField, 1, 0);
     pOptionalLayout->addWidget(pBuilt);

     // row 15
     QGroupBox* pOwner = new QGroupBox();
     //pOwner.setLayout(new GridBagLayout());
     QGridLayout* pOwnerLayout = new QGridLayout(pOwner);
     //pOwner.setBorder(BorderFactory.createTitledBorder(tr("Owner")));
     pOwner->setStyleSheet(gbStyleSheet);
     pOwner->setTitle(tr("Owner"));
     pOwnerLayout->addWidget(ownerComboBox, 1, 0);
     pOwnerLayout->addWidget(editOwnerButton, 2, 0);
     pOptionalLayout->addWidget(pOwner);

     // row 18
     if (Setup::isValueEnabled()) {
         QGroupBox* pValue = new QGroupBox();
         //pValue.setLayout(new GridBagLayout());
         QGridLayout* pValueLayout = new QGridLayout(pValue);
         //pValue.setBorder(BorderFactory.createTitledBorder(Setup.getValueLabel()));
         pValue->setStyleSheet(gbStyleSheet);
         pValue->setTitle(tr("Value"));
         pValueLayout->addWidget(valueTextField, 1, 0);
         pOptionalLayout->addWidget(pValue);
     }

     // row 20
     if (Setup::isRfidEnabled()) {
         QGroupBox* pRfid = new QGroupBox();
         //pRfid.setLayout(new GridBagLayout());
         QGridLayout* pRfidLayout = new QGridLayout(pRfid);
         pRfid->setStyleSheet(gbStyleSheet);
         pRfid->setTitle(Setup::getRfidLabel());
         //pRfid.setBorder(BorderFactory.createTitledBorder(Setup.getRfidLabel()));
         pRfidLayout->addWidget( rfidComboBox, 1, 0);
         //((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->getNamedBeanList()->forEach((tag) -> rfidComboBox->addItem((IdTag*) tag));
         QList<NamedBean*>* list = ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->getNamedBeanList();
         foreach(NamedBean* bean, *list)
         {
          rfidComboBox->addItem(((AbstractIdTag*)bean)->getDisplayName(), VPtr<NamedBean>::asQVariant(bean));
         }

         pOptionalLayout->addWidget(pRfid);
     }

     // row 22
     QGroupBox* pComment = new QGroupBox();
     //pComment.setLayout(new GridBagLayout());
     QGridLayout* pCommentLayout = new QGridLayout(pComment);
     //pComment.setBorder(BorderFactory.createTitledBorder(tr("Comment")));
     pComment->setStyleSheet(gbStyleSheet);
     pComment->setTitle("Comment");
     pCommentLayout->addWidget( commentTextField, 1, 0);
     pOptionalLayout->addWidget(pComment);

     // button panel
     QWidget* pButtons = new QWidget();
     //pButtons.setLayout(new GridBagLayout());
     //* pButtonsLayout = new QGridLayout(pButtons);
     addItem(pButtons,deleteButton, 0, 25);
     addItem(pButtons,addButton, 1, 25);
     addItem(pButtons,saveButton, 3, 25);

     // add panels
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     thisLayout->addWidget(pPanel);
     thisLayout->addWidget(optionPane);
     thisLayout->addWidget(pButtons);

     // setup buttons
     addEditButtonAction(editRoadButton);
     addButtonAction(clearRoadNumberButton);
     addEditButtonAction(editModelButton);
     addEditButtonAction(editTypeButton);
     addEditButtonAction(editLengthButton);
     addEditButtonAction(editConsistButton);
     addEditButtonAction(editOwnerButton);

     addButtonAction(deleteButton);
     addButtonAction(addButton);
     addButtonAction(saveButton);
     addButtonAction(fillWeightButton);

     // setup combobox
     addComboBoxAction(modelComboBox);
     addComboBoxAction(locationBox);

     // setup checkbox
     // build menu
     // JMenuBar menuBar = new JMenuBar();
     // JMenu toolMenu = new JMenu("Tools");
     // menuBar.add(toolMenu);
     // setJMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_LocomotivesAdd", true); // NOI18N

     // get notified if combo box gets modified
     //CarRoads.instance().addPropertyChangeListener(this);
     connect(((CarRoads*)InstanceManager::getDefault("CarRoads")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //engineModels.addPropertyChangeListener(this);
     connect(engineModels, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
//     engineTypes.addPropertyChangeListener(this);
     connect(engineTypes, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//     engineLengths.addPropertyChangeListener(this);
     //CarOwners::instance().addPropertyChangeListener(this);
     connect(((CarOwners*)InstanceManager::getDefault("CarOwners")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //locationManager.addPropertyChangeListener(this);
     connect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     //manager.addPropertyChangeListener(this);

     adjustSize();
     setMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
     setVisible(true);
 }

 /*public*/ void EngineEditFrame::loadEngine(Engine* engine)
 {
     _engine = engine;

     if (!((CarRoads*)InstanceManager::getDefault("CarRoads"))->containsName(engine->getRoadName()))
     {
         QString msg = tr("Road name \"%1\" does not exist in your roster, add?").arg(engine->getRoadName());
//         if (JOptionPane.showConfirmDialog(this, msg, tr("engineAddRoad"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
         if(QMessageBox::question(this, tr("Add road name?"), msg, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
         {
             ((CarRoads*)InstanceManager::getDefault("CarRoads"))->addName(engine->getRoadName());
         }
     }
     roadComboBox->setCurrentIndex(roadComboBox->findText(engine->getRoadName()));

     roadNumberTextField->setText(engine->getNumber());

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

     if (!engineTypes->containsName(engine->getTypeName())) {
         QString msg = tr("Type \"%1\" does not exist in your roster, add?").arg(engine
                 ->getTypeName());
//         if (JOptionPane.showConfirmDialog(this, msg, tr("engineAddType"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
         if(QMessageBox::question(this, tr("Add locomotive type?"), msg, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
         {
             engineTypes->addName(engine->getTypeName());
         }
     }
     typeComboBox->setCurrentIndex(typeComboBox->findText(engine->getTypeName()));

     if (!engineLengths->containsName(engine->getLength())) {
         QString msg = tr("Length \"%1\" does not exist in your roster, add?").arg(engine
                 ->getLength());
//         if (JOptionPane.showConfirmDialog(this, msg, tr("engineAddLength"),
//                 JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
         if(QMessageBox::question(this, tr("Add locomotive length?"), msg, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
         {
             engineLengths->addName(engine->getLength());
         }
     }

     lengthComboBox->setCurrentIndex(lengthComboBox->findText(engine->getLength()));
     weightTextField->setText(engine->getWeightTons());
     hpTextField->setText(engine->getHp());

     locationBox->setCurrentIndex(locationBox->findData(VPtr<Location>::asQVariant(engine->getLocation())));
     Location* l = locationManager->getLocationById(engine->getLocationId());
     if (l != NULL) {
         l->updateComboBox(trackLocationBox);
         trackLocationBox->setCurrentIndex(trackLocationBox->findText(engine->getTrack()->getName()));
     } else {
         trackLocationBox->clear();
     }

     builtTextField->setText(engine->getBuilt());

     if (!((CarOwners*)InstanceManager::getDefault("CarOwners"))->containsName(engine->getOwner())) {
         QString msg = tr("Owner \"%1\" does not exist in your roster, add?").arg(engine->getOwner());
//         if (JOptionPane.showConfirmDialog(this, msg, tr("addOwner"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
         if(QMessageBox::question(this, tr("Add Owner"), msg, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
         {
          ((CarOwners*)InstanceManager::getDefault("CarOwners"))->addName(engine->getOwner());
         }
     }

     consistComboBox->setCurrentIndex(consistComboBox->findText(engine->getConsistName()));

     ownerComboBox->setCurrentIndex(ownerComboBox->findText(engine->getOwner()));
     valueTextField->setText(engine->getValue());
     rfidComboBox->setCurrentIndex(rfidComboBox->findData(VPtr<DefaultIdTag>::asQVariant(engine->getIdTag())));
     commentTextField->setText(engine->getComment());

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
    Location* l = ((Location*) VPtr<Location>::asPtr(locationBox->itemData(locationBox->currentIndex())));
    l->updateComboBox(trackLocationBox);
   }
  }
 }

 /*public*/ void EngineEditFrame::checkBoxActionPerformed(QWidget* ae) {
     QCheckBox* b = (QCheckBox*) ae;
     log->debug("checkbox change " + b->text());
 }

 // Save, Delete, Add, Clear, Calculate buttons
 /*public*/ void EngineEditFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         // log->debug("engine save button activated");
         QString roadNum = roadNumberTextField->text();
         if (roadNum.length() > 10) {
//             JOptionPane.showMessageDialog(this, tr("engineRoadNum"), Bundle
//                     .getMessage("engineRoadLong"), JOptionPane.ERROR_MESSAGE);
          QMessageBox::information(this, tr("Locomotive road number too long!"), tr("Locomotive road number must be less than 10 characters"));
             return;
         }
         // check to see if engine with road and number already exists
         Engine* engine = manager->getByRoadAndNumber( roadComboBox->currentText(), roadNumberTextField
                 ->text());
         if (engine != NULL) {
             if (_engine == NULL || engine->getId()!=(_engine->getId())) {
//                 JOptionPane.showMessageDialog(this, tr("engineExists"), Bundle
//                         .getMessage("engineCanNotUpdate"), JOptionPane.ERROR_MESSAGE);
              QMessageBox::warning(this, tr("Can not update locomotive!"), tr("Locomotive with this road name and number already exists!"));
                 return;
             }
         }

         // if the road or number changes, the loco needs a new id
         if (_engine != NULL
                 && _engine->getRoadName() != NULL
                 && _engine->getRoadName()!=(Engine::NONE)
                 && (_engine->getRoadName()!=(roadComboBox->currentText()) || _engine
                         ->getNumber()!=(roadNumberTextField->text()))) {
             QString road =  roadComboBox->currentText();
             QString number = roadNumberTextField->text();
             manager->changeId(_engine, road, number);
             _engine->setRoadName(road);
             _engine->setNumber(number);
         }
         saveEngine();
         OperationsXml::save(); // save engine file
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
     if (source == deleteButton) {
         log->debug("engine delete button activated");
         if (_engine != NULL && _engine->getRoadName()==(roadComboBox->currentText())
                 && _engine->getNumber()==(roadNumberTextField->text())) {
             manager->deregister(_engine);
             _engine = NULL;
             OperationsXml::save(); // save engine file
         } else {
             Engine* e = manager->getByRoadAndNumber( roadComboBox->currentText(), roadNumberTextField->text());
             if (e != NULL) {
                 manager->deregister(e);
                 OperationsXml::save(); // save engine file
             }
         }
     }
     if (source == addButton) {
      if (!checkRoadNumber(roadNumberTextField->text())) {
          return;
      }

      // check to see if engine already exists
      Engine* existingEngine =
              manager->getByRoadAndNumber( roadComboBox->currentText(), roadNumberTextField
                      ->text());
      if (existingEngine != NULL) {
          log->info("Can not add, engine already exists");
          JOptionPane::showMessageDialog(this, tr("Locomotive with this road name and number already exists!"), tr("Can not update locomotive!"), JOptionPane::ERROR_MESSAGE);
          return;
      }

      // enable delete and save buttons
      deleteButton->setEnabled(true);
      saveButton->setEnabled(true);

      saveEngine();
      OperationsXml::save(); // save engine file
     }
     if (source == clearRoadNumberButton) {
         roadNumberTextField->setText("");
         //roadNumberTextField.requestFocus();
     }
 }

 /*private*/ void EngineEditFrame::addEngine() {
     if (roadComboBox->currentText() != NULL && roadComboBox->currentText()!=("")) {
         if (_engine == NULL || _engine->getRoadName()!=(roadComboBox->currentText())
                 || _engine->getNumber()!=(roadNumberTextField->text())) {
             _engine = (Engine*)manager->newRS( roadComboBox->currentText(), roadNumberTextField->text());
         }
         if (modelComboBox->currentText() != NULL) {
             _engine->setModel( modelComboBox->currentText());
         }
         if (typeComboBox->currentText() != NULL) {
             _engine->setTypeName( typeComboBox->currentText());
         }
         if (lengthComboBox->currentText() != NULL) {
             _engine->setLength( lengthComboBox->currentText());
         }
         _engine->setBuilt(builtTextField->text());
         if (ownerComboBox->currentText() != NULL) {
             _engine->setOwner( ownerComboBox->currentText());
         }
         if (consistComboBox->currentText() != NULL) {
             if (consistComboBox->currentText()==(EngineManager::NONE)) {
                 _engine->setConsist(NULL);
                 _engine->setBlocking(0);
             } else {
                 _engine->setConsist(manager->getConsistByName( consistComboBox->currentText()));
                 if (_engine->getConsist() != NULL) {
                     _engine->setBlocking(_engine->getConsist()->getSize());
                 }
             }
         }
         // confirm that weight is a number
         if (weightTextField->text()!=("")) {
             try {
                 weightTextField->text().toInt();
                 _engine->setWeightTons(weightTextField->text());
             } catch (Exception e) {
//                 JOptionPane.showMessageDialog(this, tr("engineWeight"), Bundle
//                         .getMessage("engineCanNotWeight"), JOptionPane.ERROR_MESSAGE);
           QMessageBox::information(this, tr("Can not save locomotive weight!"), tr("Locomotive weight must be a number"));
             }
         }
         // confirm that horsepower is a number
         if (hpTextField->text()!=("")) {
             bool ok;
                 hpTextField->text().toInt(&ok);
                 _engine->setHp(hpTextField->text());
                 if(!ok) {
//                 JOptionPane.showMessageDialog(this, tr("engineHorsepower"), Bundle
//                         .getMessage("engineCanNotHp"), JOptionPane.ERROR_MESSAGE);
           QMessageBox::warning(this, tr("Can not save locomotive horsepower!"), tr("Locomotive horsepower must be a number"));
             }
         }
         if (locationBox->currentText() == NULL) {
             _engine->setLocation(NULL, NULL);
         } else {
             if (trackLocationBox->currentText() == NULL) {
//                 JOptionPane.showMessageDialog(this, tr("rsFullySelect"), Bundle
//                         .getMessage("rsCanNotLoc"), JOptionPane.ERROR_MESSAGE);
              QMessageBox::warning(this, tr("Can not update locomotive location"), tr("To place a locomotive, you must select the location and track"));
             } else {
              QString status = _engine->setLocation((Location*) VPtr<Location>::asPtr(locationBox->itemData(locationBox->currentIndex())),
                         (Track*) VPtr<Track>::asPtr(trackLocationBox->itemData(locationBox->currentIndex())));
                 if (status!=(Track::OKAY)) {
                     log->debug(tr("Can't set engine's location because of %1").arg( status));
//                     JOptionPane.showMessageDialog(this, Bundle
//                             .getMessage("rsCanNotLocMsg"), new Object[]{_engine->toString(), status}), Bundle
//                             .getMessage("rsCanNotLoc"), JOptionPane.ERROR_MESSAGE);
                     QMessageBox::warning(this, tr("Can not update locomotive location"), tr("Can't set locomotive (%1) location due to %2").arg(_engine->toString()).arg(status) );
                     // does the user want to force the rolling stock to this track?
//                     int results = JOptionPane.showOptionDialog(this, Bundle
//                             .getMessage("rsForce"), new Object[]{_engine->toString(),
//                             (Track) trackLocationBox->currentText()}), Bundle
//                             .getMessage("rsOverride"), new Object[]{status}), JOptionPane.YES_NO_OPTION,
//                             JOptionPane.QUESTION_MESSAGE, NULL, NULL, NULL);
//                     if (results == JOptionPane.YES_OPTION) {
                     if(QMessageBox::question(this, tr("Do you want to override track''s %1?").arg(status), tr("Do you want to force locomotive (%1) to track (%2)?").arg(_engine->toString()).arg(trackLocationBox->currentText()), QMessageBox::Yes | QMessageBox ::No)!= QMessageBox::Yes)
                     {

                         log->debug("Force rolling stock to track");
                         _engine->setLocation((Location*) VPtr<Location>::asPtr(locationBox->itemData(locationBox->currentIndex())), (Track*) VPtr<Track>::asPtr(trackLocationBox
                                              ->itemData(locationBox->currentIndex())), true);
                     }
                 }
             }
         }
         _engine->setComment(commentTextField->text());
         _engine->setValue(valueTextField->text());
         _engine->setIdTag((DefaultIdTag*) VPtr<DefaultIdTag>::asPtr(rfidComboBox->itemData(rfidComboBox->currentIndex())));
     }
 }
/*private*/ bool EngineEditFrame::checkRoadNumber(QString roadNum) {
    if (!OperationsXml::checkFileName(roadNum)) { // NOI18N
        log->error("Road number must not contain reserved characters");
        JOptionPane::showMessageDialog(this,
                tr("Must not contain reserved characters") + NEW_LINE + tr("Must not contain reserved characters"),
                tr("Can't use road number!"),
                JOptionPane::ERROR_MESSAGE);
        return false;
    }
    if (roadNum.length() > Control::max_len_string_road_number) {
        JOptionPane::showMessageDialog(this, tr("Locomotive road number must be less than 10 characters"), tr("Locomotive road number too long!"), JOptionPane::ERROR_MESSAGE);
        return false;
    }
    return true;
}

/*private*/ void EngineEditFrame::saveEngine() {
    if (roadComboBox->currentText() != NULL && roadComboBox->currentText() != ("")) {
        if (_engine == NULL ||
                _engine->getRoadName() != (roadComboBox->currentText()) ||
                 _engine->getNumber() != (roadNumberTextField->text())) {
            _engine = (Engine*)manager->newRS( roadComboBox->currentText(), roadNumberTextField->text());
        }
        if (modelComboBox->currentText() != NULL) {
             _engine->setModel( modelComboBox->currentText());
        }
        if (typeComboBox->currentText() != NULL) {
             _engine->setTypeName( typeComboBox->currentText());
        }
         _engine->setBunit(bUnitCheckBox->isChecked());
        if (lengthComboBox->currentText() != NULL) {
             _engine->setLength( lengthComboBox->currentText());
        }
         _engine->setBuilt(builtTextField->text());
        if (ownerComboBox->currentText() != NULL) {
             _engine->setOwner( ownerComboBox->currentText());
        }
        if (consistComboBox->currentText() != NULL) {
            if (consistComboBox->currentText() == (EngineManager::NONE)) {
                 _engine->setConsist(NULL);
                if ( _engine->isBunit())
                     _engine->setBlocking(Engine::B_UNIT_BLOCKING);
                else
                     _engine->setBlocking(Engine::DEFAULT_BLOCKING_ORDER);
            } else {
                 _engine->setConsist(manager->getConsistByName( consistComboBox->currentText()));
                if ( _engine->getConsist() != NULL) {
                     _engine->setBlocking( _engine->getConsist()->getSize());
                }
            }
        }
        // confirm that weight is a number
        if (weightTextField->text() != ("")) {
            try {
          bool bok;
                (weightTextField->text().toInt(&bok));
          if(!bok) throw Exception();
                 _engine->setWeightTons(weightTextField->text());
            } catch (Exception e) {
                JOptionPane::showMessageDialog(this, tr("Locomotive weight must be a number"), tr("Can not save locomotive weight!"), JOptionPane::ERROR_MESSAGE);
            }
        }
        // confirm that horsepower is a number
        if (hpTextField->text() != ("")) {
            try {
          bool bok;
                (hpTextField->text().toInt(&bok));
                if(!bok) throw Exception();
                 _engine->setHp(hpTextField->text());
            } catch (Exception e) {
                JOptionPane::showMessageDialog(this, tr("Locomotive horsepower must be a number"), tr("Can not save locomotive horsepower!"), JOptionPane::ERROR_MESSAGE);
            }
        }
        if (locationBox->currentText() == NULL) {
             _engine->setLocation(NULL, NULL);
        } else {
            if (trackLocationBox->currentText() == NULL) {
                JOptionPane::showMessageDialog(this, tr("To place a locomotive, you must select the location and track"),tr("Can not update locomotive location"), JOptionPane::ERROR_MESSAGE);

            } else {
                QString status = _engine->setLocation(VPtr<Location>::asPtr( locationBox->currentData()),
                        VPtr<Track>::asPtr( trackLocationBox->currentData()));
                if (status != (Track::OKAY)) {
                    log->debug(tr("Can't set engine's location because of %1").arg(status));
                    JOptionPane::showMessageDialog(this, tr("Can''t set locomotive (%1) location due to %2").arg(_engine->toString()).arg( status), tr("Can not update locomotive location"),
                            JOptionPane::ERROR_MESSAGE);
                    // does the user want to force the rolling stock to this track?
                    int results = JOptionPane::showOptionDialog(this, tr("Do you want to force locomotive (%1) to track (%2)?").arg(_engine->toString()).arg(
                                    VPtr<Track>::asPtr( trackLocationBox->currentData())->toString()),
                            tr("Do you want to override track''s %1?").arg(status),
                            JOptionPane::YES_NO_OPTION,
                            JOptionPane::QUESTION_MESSAGE, QIcon(), QList<QVariant>(), QVariant());
                    if (results == JOptionPane::YES_OPTION) {
                        log->debug("Force rolling stock to track");
                         _engine->setLocation(VPtr<Location>::asPtr( locationBox->currentData()), VPtr<Track>::asPtr( trackLocationBox
                                ->currentData()), RollingStock::FORCE);
                    }
                }
            }
        }
         _engine->setComment(commentTextField->text());
         _engine->setValue(valueTextField->text());
        // save the IdTag for this engine
        IdTag* idTag = VPtr<IdTag>::asPtr( rfidComboBox->currentData());
        if (idTag != NULL) {
             _engine->setRfid(idTag->toString());
        }
    }
}

 /*private*/ void EngineEditFrame::addEditButtonAction(QPushButton* b) {
 //     b.addActionListener(new java.awt.event.ActionListener() {
 //         /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
 //             buttonEditActionPerformed(e);
 //         }
 //     });
  connect(b, SIGNAL(clicked()), buttonEditMapper, SLOT(map()));
  buttonEditMapper->setMapping(b,b);
 }

// edit buttons only one frame active at a time
 /*public*/ void EngineEditFrame::buttonEditActionPerformed(QWidget* ae)
{
 QPushButton* source = (QPushButton*)ae;

  if (editActive)
  {
      f->dispose();
  }
  f = new EngineAttributeEditFrame();
//     f->setLocationRelativeTo(this);
  //f->addPropertyChangeListener(this);
  connect(f, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  editActive = true;

  if (source == editRoadButton) {
      f->initComponents(ROAD,  roadComboBox->currentText());
  }
  if (source == editModelButton) {
      f->initComponents(MODEL,  modelComboBox->currentText());
  }
  if (source == editTypeButton) {
      f->initComponents(TYPE,  typeComboBox->currentText());
  }
  if (source == editLengthButton) {
      f->initComponents(LENGTH,  lengthComboBox->currentText());
  }
  if (source == editOwnerButton) {
      f->initComponents(OWNER,  ownerComboBox->currentText());
  }
  if (source == editConsistButton) {
      f->initComponents(CONSIST,  consistComboBox->currentText());
  }

 }

 /*public*/ void EngineEditFrame::dispose() {
     removePropertyChangeListeners();
     OperationsFrame::dispose();
 }

 /*private*/ void EngineEditFrame::removePropertyChangeListeners()
 {
  ((CarRoads*)InstanceManager::getDefault("CarRoads"))->removePropertyChangeListener(this);
  engineModels->removePropertyChangeListener(this);
  engineTypes->removePropertyChangeListener(this);
  engineLengths->removePropertyChangeListener(this);
  ((CarOwners*)InstanceManager::getDefault("CarOwners"))->removePropertyChangeListener(this);
  locationManager->removePropertyChangeListener(this);
  manager->removePropertyChangeListener(this);
 }

 /*public*/ void EngineEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg( e->getOldValue().toString()).arg(e->getNewValue().toString()));
     }

     if (e->getPropertyName()==(CarRoads::CARROADS_CHANGED_PROPERTY)) {
         ((CarRoads*)InstanceManager::getDefault("CarRoads"))->updateComboBox(roadComboBox);
         if (_engine != NULL) {
             roadComboBox->setCurrentIndex(roadComboBox->findText(_engine->getRoadName()));
         }
     }

     if (e->getPropertyName()==(EngineModels::ENGINEMODELS_CHANGED_PROPERTY)) {
         engineModels->updateComboBox(modelComboBox);
         if (_engine != NULL) {
             modelComboBox->setCurrentIndex(modelComboBox->findText(_engine->getModel()));
         }
     }

     if (e->getPropertyName()==(EngineTypes::ENGINETYPES_CHANGED_PROPERTY)) {
         engineTypes->updateComboBox(typeComboBox);
         if (_engine != NULL) {
             typeComboBox->setCurrentIndex(typeComboBox->findText(_engine->getTypeName()));
         }
     }
     if (e->getPropertyName()==(EngineLengths::ENGINELENGTHS_CHANGED_PROPERTY)) {
         engineLengths->updateComboBox(lengthComboBox);
         if (_engine != NULL) {
             lengthComboBox->setCurrentIndex(lengthComboBox->findText(_engine->getLength()));
         }
     }

     if (e->getPropertyName()==(EngineManager::CONSISTLISTLENGTH_CHANGED_PROPERTY)) {
         manager->updateConsistComboBox(consistComboBox);
         if (_engine != NULL) {
             consistComboBox->setCurrentIndex(consistComboBox->findText(_engine->getConsistName()));
         }
     }

     if (e->getPropertyName()==(CarOwners::CAROWNERS_CHANGED_PROPERTY)) {
         ((CarOwners*)InstanceManager::getDefault("CarOwners"))->updateComboBox(ownerComboBox);
         if (_engine != NULL) {
             ownerComboBox->setCurrentIndex(ownerComboBox->findText(_engine->getOwner()));
         }
     }

     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         ((LocationManager*)InstanceManager::getDefault("LocationManager"))->updateComboBox(locationBox);
         if (_engine != NULL) {
             locationBox->setCurrentIndex(locationBox->findText(_engine->getLocation()->getName()));
         }
     }
     if (e->getPropertyName()==(EngineAttributeEditFrame::DISPOSE)) {
         editActive = false;
     }
 }

 /*public*/ QString EngineEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.rollingstock.engines.EngineEditFrame";
 }

}
