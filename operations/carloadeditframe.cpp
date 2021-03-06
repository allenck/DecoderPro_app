#include "carloadeditframe.h"
#include "carloads.h"
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include "jcombobox.h"
#include "jtextfield.h"
#include "control.h"
#include "gridbaglayout.h"
#include "propertychangeevent.h"
#include "car.h"
#include "carmanager.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include "operationsxml.h"
#include "setup.h"
#include "trainmanager.h"
#include "cartypes.h"
#include "locationmanager.h"
#include "schedulemanager.h"
#include "printcarloadsaction.h"
#include "carloadattributeaction.h"
#include "instancemanager.h"
namespace Operations
{
/**
 * Frame for adding and editing the car roster for operations.
 *
 * @author Daniel Boudreau Copyright (C) 2009, 2010, 2011
 * @version $Revision: 29493 $
 */
///*public*/ class CarLoadEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

    /**
     *
     */
 ///*private*/ static final long serialVersionUID = -8066884161999922218L;

 /*public*/ /*static*/ /*final*/ QString CarLoadEditFrame::NONE = "";


 /*public*/ CarLoadEditFrame::CarLoadEditFrame(QWidget* parent) : OperationsFrame(parent)
 {
  log = new Logger("CarEditFrame");
  setObjectName("CarEditFrame");
  carLoads = ((CarLoads*)InstanceManager::getDefault("CarLoads"));

  // labels
  textSep = new QLabel();
  quanity = new QLabel("0");

  // major buttons
  addButton = new QPushButton(tr("Add"));
  deleteButton = new QPushButton(tr("Delete"));
  replaceButton = new QPushButton(tr("Replace"));
  saveButton = new QPushButton(tr("Save"));

  // text boxes
  addTextBox = new JTextField(10);
  pickupCommentTextField = new JTextField(35);
  dropCommentTextField = new JTextField(35);
  menuActive = false;
  showQuanity = false;

  loadTypeComboBox = carLoads->getLoadTypesComboBox();

 }


 /*public*/ void CarLoadEditFrame::initComponents(QString type, QString select)
 {
  //getContentPane().removeAll();
  QLayout* _layout = getContentPane()->layout();
  QLayoutItem* item;
  if(_layout!= NULL)
  {
   while ( ( item = _layout->takeAt( 0 ) ) != NULL )
   {
       delete item->widget();
       delete item;
   }
  }
  else
   getContentPane()->setLayout(new QVBoxLayout);

  setTitle(tr("Edit Car Load %1").arg(type));

  // track which combo box is being edited
  _type = type;
  loadComboboxes();
  loadComboBox->setCurrentIndex(loadComboBox->findText(select));
  updateLoadType();
  updatePriority();

  // general GUI config
  quanity->setVisible(showQuanity);

  // load panel
  QGroupBox* pLoad = new QGroupBox();
  pLoad->setLayout(new GridBagLayout());
  pLoad->setStyleSheet(gbStyleSheet);
  pLoad->setTitle(tr("Load"));
  //pLoad.setBorder(BorderFactory.createTitledBorder(tr("Load")));

  // row 2
  addItem(pLoad, addTextBox, 2, 2);
  addItem(pLoad, addButton, 3, 2);

  // row 3
  addItem(pLoad, quanity, 1, 3);
  addItem(pLoad, loadComboBox, 2, 3);
  addItem(pLoad, deleteButton, 3, 3);

  // row 4
  addItem(pLoad, replaceButton, 3, 4);

  // row 6
  QGroupBox* pLoadType = new QGroupBox();
  pLoadType->setLayout(new GridBagLayout); //(pLoadType, BoxLayout.Y_AXIS));
  //pLoadType.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutLoadType")));
  pLoadType->setStyleSheet(gbStyleSheet);
  pLoadType->setTitle(tr("Load Type"));
  addItem(pLoadType, loadTypeComboBox, 0, 0);

  // row 8
  QGroupBox* pPriority = new QGroupBox();
  pPriority->setLayout(new GridBagLayout); //(pPriority, BoxLayout.Y_AXIS));
  //pPriority.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutPriority")));
  pPriority->setStyleSheet(gbStyleSheet);
  pPriority->setTitle(tr("Priority"));
  addItem(pPriority, priorityComboBox, 0, 0);

  // row 10
  // optional panel
  QGroupBox* pOptionalPickup = new QGroupBox();
  pOptionalPickup->setLayout(new QVBoxLayout); //(pOptionalPickup, BoxLayout.Y_AXIS));
  //pOptionalPickup.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutOptionalPickup")));
  pOptionalPickup->setStyleSheet(gbStyleSheet);
  pOptionalPickup->setTitle(tr("Optional Pickup"));
  addItem(pOptionalPickup, pickupCommentTextField, 0, 0);

  // row 12
  QGroupBox* pOptionalDrop = new QGroupBox();
  pOptionalDrop->setLayout(new QVBoxLayout); //(pOptionalDrop, BoxLayout.Y_AXIS));
  //pOptionalDrop.setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutOptionalDrop")));
  pOptionalDrop->setStyleSheet(gbStyleSheet);
  pOptionalDrop->setTitle(tr("Optional Drop"));
  addItem(pOptionalDrop, dropCommentTextField, 0, 0);

  // row 14
  QWidget* pControl = new QWidget();
  pControl->setLayout(new QVBoxLayout); //(pControl, BoxLayout.Y_AXIS));
  addItem(pControl, saveButton, 0, 0);

  // add panels
  getContentPane()->setLayout(new QVBoxLayout); //(getContentPane(), BoxLayout.Y_AXIS));
  getContentPane()->layout()->addWidget(pLoad);
  getContentPane()->layout()->addWidget(pLoadType);
  getContentPane()->layout()->addWidget(pPriority);
  getContentPane()->layout()->addWidget(pOptionalPickup);
  getContentPane()->layout()->addWidget(pOptionalDrop);
  getContentPane()->layout()->addWidget(pControl);

  addButtonAction(addButton);
  addButtonAction(deleteButton);
  addButtonAction(replaceButton);
  addButtonAction(saveButton);

  addComboBoxAction(loadComboBox);

  updateCarCommentFields();

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));
  toolMenu->addAction(new CarLoadAttributeAction(tr("CarQuanity"), this));
  toolMenu->addAction(new PrintCarLoadsAction(tr("Preview"), true, this));
  toolMenu->addAction(new PrintCarLoadsAction(tr("Print"), false, this));

  menuBar->addMenu(toolMenu);
  setMenuBar(menuBar);

  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_EditCarLoads", true); // NOI18N

  initMinimumSize(QSize(Control::panelWidth300, Control::panelHeight500));
 }

 // add, delete, replace, and save buttons
 /*public*/ void CarLoadEditFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == addButton) {
         QString addLoad = addTextBox->text().trimmed();
         if (addLoad==(NONE)) {
             return;
         }
         if (addLoad.length() > Control::max_len_string_attibute) {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("carAttribute"),
//                     new Object[]{Control.max_len_string_attibute}), MessageFormat.format(Bundle
//                             .getMessage("canNotAdd"), new Object[]{tr("Load")}),
//                     JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this,tr("Can not add %1").arg(tr("Load")), tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_attibute) );
             return;
         }
         addLoadToCombobox(_type, addLoad);
     }
     if (source == deleteButton) {
         QString deleteLoad =  loadComboBox->currentText();
         if (deleteLoad==(carLoads->getDefaultEmptyName()) || deleteLoad==(carLoads->getDefaultLoadName())) {
//             JOptionPane.showMessageDialog(this, tr("carLoadDefault"), MessageFormat.format(Bundle
//                     .getMessage("canNotDelete"), new Object[]{tr("Load")}),
//                     JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Can not delete %1").arg(tr("Load")), tr("Can not delete default Load or Empty"));
             return;
         }
         replaceLoad(_type, deleteLoad, NULL);
         deleteLoadFromCombobox(_type, deleteLoad);
     }
     if (source == replaceButton) {
         QString newLoad = addTextBox->text().trimmed();
         if (newLoad==(NONE)) {
             return;
         }
         if (newLoad.length() > Control::max_len_string_attibute) {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("carAttribute"),
//                     new Object[]{Control.max_len_string_attibute}), MessageFormat.format(Bundle
//                             .getMessage("canNotReplace"), new Object[]{tr("Load")}),
//                     JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Can not replace %1").arg(tr("Load")), tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_attibute));
             return;
         }
         QString oldLoad =  loadComboBox->currentText();

         if (oldLoad==(carLoads->getDefaultEmptyName())) {
//             if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("replaceDefaultEmpty"),
//                     new Object[]{oldLoad, newLoad}), tr("replaceAll"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
          if(QMessageBox::critical(this, tr("Replace All?"), tr("Are you sure you want to replace the default empty \"%1\" with \"%2\"").arg(oldLoad).arg(newLoad), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
          {
                 return;
             }
             // don't allow the default names for load and empty to be the same
             if (newLoad==(carLoads->getDefaultEmptyName()) || newLoad==(carLoads->getDefaultLoadName())) {
//                 JOptionPane.showMessageDialog(this, tr("carDefault"), MessageFormat.format(Bundle
//                         .getMessage("canNotReplace"), new Object[]{tr("Load")}),
//                         JOptionPane.ERROR_MESSAGE);
              QMessageBox::critical(this, tr("Can not replace %1").arg(tr("Load")), tr("Load and Empty default names must be unique"));
                 return;
             }
             carLoads->setDefaultEmptyName(newLoad);
             replaceAllLoads(oldLoad, newLoad);
             return;
         }
         if (oldLoad==(carLoads->getDefaultLoadName())) {
//             if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("replaceDefaultLoad"),
//                     new Object[]{oldLoad, newLoad}), tr("replaceAll"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
          if(QMessageBox::critical(this, tr("Replace All?"), tr("Are you sure you want to replace the default load \"%1\" with \"%2\"").arg(oldLoad).arg(newLoad), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
          {

                 return;
             }
             // don't allow the default names for load and empty to be the same
             if (newLoad==(carLoads->getDefaultEmptyName()) || newLoad==(carLoads->getDefaultLoadName())) {
//                 JOptionPane.showMessageDialog(this, tr("carDefault"), MessageFormat.format(Bundle
//                         .getMessage("canNotReplace"), new Object[]{tr("Load")}),
//                         JOptionPane.ERROR_MESSAGE);
              QMessageBox::critical(this,tr("Can not replace %1").arg(tr("Load")), tr("Load and Empty default names must be unique"));
                 return;
             }
             carLoads->setDefaultLoadName(newLoad);
             replaceAllLoads(oldLoad, newLoad);
             return;
         }
//         if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("replaceMsg"), new Object[]{
//             oldLoad, newLoad}), tr("replaceAll"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
         if(QMessageBox::critical(this, tr("Replace All?"), tr("Replace \"%1\" with \"%2\"").arg(oldLoad).arg(newLoad), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
         {
             return;
         }
         addLoadToCombobox(_type, newLoad);
         replaceLoad(_type, oldLoad, newLoad);
         deleteLoadFromCombobox(_type, oldLoad);
     }
     if (source == saveButton) {
         log->debug("CarLoadEditFrame save button pressed");
         carLoads->setLoadType(_type,  loadComboBox->currentText(),  loadTypeComboBox
                 ->currentText());
         carLoads->setPriority(_type,  loadComboBox->currentText(),  priorityComboBox->currentText());
         carLoads->setPickupComment(_type,  loadComboBox->currentText(), pickupCommentTextField->text());
         carLoads->setDropComment(_type,  loadComboBox->currentText(), dropCommentTextField->text());
         //CarManagerXml.instance().setDirty(true); // save car files
         OperationsXml::save(); // save all files that have been modified;
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 /*protected*/ void CarLoadEditFrame::comboBoxActionPerformed(QWidget* ae) {
     log->debug("Combo box action");
     updateCarQuanity();
     updateLoadType();
     updatePriority();
     updateCarCommentFields();
 }

 // replace the default empty and load for all car types
 /*private*/ void CarLoadEditFrame::replaceAllLoads(QString oldLoad, QString newLoad) {
     foreach (QString type, ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getNames()) {
         addLoadToCombobox(type, newLoad);
         replaceLoad(type, oldLoad, newLoad);
         deleteLoadFromCombobox(type, oldLoad);
     }
 }

 /*private*/ void CarLoadEditFrame::deleteLoadFromCombobox(QString type, QString name) {
     carLoads->deleteName(type, name);
 }

 /*private*/ void CarLoadEditFrame::addLoadToCombobox(QString type, QString name) {
     carLoads->addName(type, name);
 }

 /*private*/ void CarLoadEditFrame::replaceLoad(QString type, QString oldLoad, QString newLoad) {
     // adjust all cars
     ((CarManager*)InstanceManager::getDefault("CarManager"))->replaceLoad(type, oldLoad, newLoad);
     // now adjust schedules

     ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->replaceLoad(type, oldLoad, newLoad);

     // now adjust trains
     ((TrainManager*)InstanceManager::getDefault("TrainManager"))->replaceLoad(type, oldLoad, newLoad);
     // now adjust tracks
     ((LocationManager*)InstanceManager::getDefault("LocationManager"))->replaceLoad(type, oldLoad, newLoad);
 }

/*private*/ void CarLoadEditFrame::loadComboboxes() {
     loadComboBox = carLoads->getComboBox(_type);
     //carLoads.addPropertyChangeListener(this);
     connect(carLoads, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     priorityComboBox = carLoads->getPriorityComboBox();
 }

 /*public*/ void CarLoadEditFrame::toggleShowQuanity() {
     if (showQuanity) {
         showQuanity = false;
     } else {
         showQuanity = true;
     }
     quanity->setVisible(showQuanity);
     updateCarQuanity();
 }

 /*private*/ void CarLoadEditFrame::updateCarQuanity() {
     if (!showQuanity) {
         return;
     }
     int number = 0;
     QString item =  loadComboBox->currentText();
     foreach (RollingStock* rs, *((CarManager*)InstanceManager::getDefault("CarManager"))->getList()) {
         Car* car = (Car*) rs;
         if (car->getLoadName()==(item)) {
             number++;
         }
     }
     quanity->setText(QString::number(number));
 }

/*private*/ void CarLoadEditFrame::updateLoadType() {
        QString loadName =  loadComboBox->currentText();
        QString loadType = carLoads->getLoadType(_type, loadName);
        int ix = loadTypeComboBox->findText(loadType);
        loadTypeComboBox->setCurrentIndex(ix);
        if (loadName != NULL
                && (loadName==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName()) || loadName==(((CarLoads*)InstanceManager::getDefault("CarLoads"))
                        ->getDefaultLoadName()))) {
            loadTypeComboBox->setEnabled(false);
        } else {
            loadTypeComboBox->setEnabled(true);
        }
    }

    /*private*/ void CarLoadEditFrame::updatePriority() {
        priorityComboBox->setCurrentIndex(priorityComboBox->findText(carLoads->getPriority(_type,  loadComboBox->currentText())));
    }

 /*private*/ void CarLoadEditFrame::updateCarCommentFields() {
     pickupCommentTextField->setText(carLoads->getPickupComment(_type,  loadComboBox->currentText()));
     dropCommentTextField->setText(carLoads->getDropComment(_type, loadComboBox->currentText()));
 }

 /*public*/ void CarLoadEditFrame::dispose() {
     //carLoads.removePropertyChangeListener(this);
 disconnect(carLoads, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }

 /*public*/ void CarLoadEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarLoads::LOAD_CHANGED_PROPERTY)) {
         carLoads->updateComboBox(_type, loadComboBox);
     }
 }

 /*public*/ QString CarLoadEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.rollingstock.cars.CarLoadEditFrame";
 }

}
