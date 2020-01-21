#include "carattributeeditframe.h"
#include "control.h"
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QBoxLayout>
#include "jtextfield.h"
#include "gridbaglayout.h"
#include "carmanager.h"
#include <QMenu>
#include <QMenuBar>
#include "careditframe.h"
#include <QMessageBox>
#include "trainmanager.h"
#include "carroads.h"
#include "propertychangesupport.h"
#include "cartypes.h"
#include "carmanager.h"
#include "carattributeaction.h"
#include "carloads.h"
#include "car.h"
#include "enginemanager.h"
#include "cardeleteattributeaction.h"
#include "carlengths.h"
#include "carowners.h"
#include "carcolors.h"
#include "setup.h"

//CarAttributeEditFrame::CarAttributeEditFrame()
//{

//}
namespace Operations
{
/**
 * Frame for adding and editing the car roster for operations.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarAttributeEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -8817198567309887518L;


 // property change
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ CarAttributeEditFrame::CarAttributeEditFrame(QWidget* parent) : OperationsFrame(parent)
 {
  setObjectName("CarAttributeEditFrame");
  log = new Logger("CarAttributeEditFrame");
  pcs = new PropertyChangeSupport(this);
  carManager = CarManager::instance();

  // labels
  textAttribute = new QLabel();
  textSep = new QLabel();
  quanity = new QLabel("0");

  // major buttons
  addButton = new QPushButton();
  deleteButton = new QPushButton();
  replaceButton = new QPushButton();

  // combo box
  comboBox  = NULL;

  // text box
  addTextBox = new JTextField(Control::max_len_string_attibute);
  showQuanity = false;
  deleteUnused = false;
  cancel = false;


 }


 /*public*/ void CarAttributeEditFrame::initComponents(QString comboboxName) {
     initComponents(comboboxName, NONE);
 }

 /*public*/ void CarAttributeEditFrame::initComponents(QString comboboxName, QString select)
 {
 //getContentPane().removeAll();
 if(getContentPane()!= NULL && getContentPane()->layout()!= NULL)
 {
  QObjectList ol = getContentPane()->layout()->children();
  foreach (QObject* o, ol) {
   if(qobject_cast<QWidget*>(o) != NULL)
   {
    getContentPane()->layout()->removeWidget((QWidget*)o);
    delete o;
   }
  }
 }

 setTitle(tr("Edit Car %1").arg(comboboxName));

  // track which combo box is being edited
  _comboboxName = comboboxName;
  loadCombobox();
  comboBox->setCurrentIndex(comboBox->findText(select));

  // general GUI config
  //getContentPane()->setLayout(new GridBagLayout());
  GridBagLayout* thisLayout = new GridBagLayout(getContentPane());

  textAttribute->setText(comboboxName);

  addButton->setText(tr("Add"));
  addButton->setVisible(true);
  deleteButton->setText(tr("Delete"));
  deleteButton->setVisible(true);
  replaceButton->setText(tr("Replace"));
  replaceButton->setVisible(true);

  quanity->setVisible(showQuanity);

  // row 1
  addItem(textAttribute, 2, 1);
  // row 2
  addItem(addTextBox, 2, 2);
  addItem(addButton, 3, 2);

  // row 3
  addItem(quanity, 1, 3);
  addItem(comboBox, 2, 3);
  addItem(deleteButton, 3, 3);

  // row 4
  addItem(replaceButton, 3, 4);

  addButtonAction(addButton);
  addButtonAction(deleteButton);
  addButtonAction(replaceButton);

  addComboBoxAction(comboBox);
  //carManager.addPropertyChangeListener(this);
  connect(carManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));
  toolMenu->addAction(new CarAttributeAction(tr("Show the number of cars with this attribute"), this));
  toolMenu->addAction(new CarDeleteAttributeAction(tr("Delete unused attributes"), this));
  menuBar->addMenu(toolMenu);
  setMenuBar(menuBar);
  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_EditCarAttributes", true); // NOI18N

  initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight250));

 }

 // add, delete, or replace button
 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void CarAttributeEditFrame::buttonActionPerformed(QWidget* ae) {
     log->debug("edit frame button activated");
     QPushButton* source = (QPushButton*)ae;
     if (source == addButton) {
         QString addItem = addTextBox->text().trimmed();
         if (addItem==(NONE)) {
             return;
         }
         //String[] item = {addItem};
         QStringList item = QStringList() << addItem;
         if (_comboboxName == CarEditFrame::TYPE) {
             item = addItem.split("-");
         }
         if (item[0].length() > Control::max_len_string_attibute)
         {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("carAttribute"),
//                     new Object[]{Control::max_len_string_attibute}), MessageFormat.format(Bundle
//                             .getMessage("canNotAdd"), new Object[]{_comboboxName}), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Can not add %1").arg(_comboboxName), tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_attibute));
             return;
         }
         addItemToCombobox(addItem);
     }
     if (source == deleteButton) {
         deleteItemFromCombobox( comboBox->currentText());
     }
     if (source == replaceButton) {
         QString newItem = addTextBox->text().trimmed();
         if (newItem==(NONE)) {
             return;
         }
         QStringList item = QStringList() << newItem;
         if (_comboboxName == CarEditFrame::TYPE) {
             item = newItem.split("-");
         }
         if (item[0].length() > Control::max_len_string_attibute) {
//             JOptionPane.showMessageDialog(this, MessageFormat.format(tr("carAttribute"),
//                     new Object[]{Control::max_len_string_attibute}), MessageFormat.format(Bundle
//                             .getMessage("canNotReplace"), new Object[]{_comboboxName}), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Can not replace %1").arg(_comboboxName), tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_attibute));
             return;
         }
         QString oldItem =  comboBox->currentText();
//         if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("replaceMsg"), new Object[]{
//             oldItem, newItem}), tr("replaceAll"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
         if(QMessageBox::question(this, tr("Replace All?"),tr("Replace \"%1\" with \"%2\"").arg(oldItem).arg(newItem), QMessageBox::Yes | QMessageBox::No)!= QMessageBox::Yes)
         {
             return;
         }
         if (newItem==(oldItem)) {
             return;
         }
         // need to make sure locations and trains are loaded
         TrainManager::instance();
         // LocationManager.instance();
         // don't show dialog, save current state
         bool oldShow = showDialogBox;
         showDialogBox = false;
         addItemToCombobox(newItem);
         showDialogBox = oldShow;
         replaceItem(oldItem, newItem);
         deleteItemFromCombobox(oldItem);
     }
 }

 /*protected*/ void CarAttributeEditFrame::comboBoxActionPerformed(QWidget* ae) {
     log->debug("Combo box action");
     updateCarQuanity();
 }

 /*private*/ void CarAttributeEditFrame::deleteItemFromCombobox(QString deleteItem) {
     log->debug(tr("delete attribute %1").arg(deleteItem));
     if (_comboboxName == CarEditFrame::ROAD) {
         // purge train and locations by using replace
         CarRoads::instance()->replaceName(deleteItem, NULL);
     }
     if (_comboboxName == CarEditFrame::TYPE) {
         CarTypes::instance()->deleteName(deleteItem);
     }

     if (_comboboxName == CarEditFrame::COLOR) {
         CarColors::instance()->deleteName(deleteItem);
     }

     if (_comboboxName == CarEditFrame::LENGTH) {
         CarLengths::instance()->deleteName(deleteItem);
     }
     if (_comboboxName == CarEditFrame::OWNER) {
         CarOwners::instance()->deleteName(deleteItem);
     }
     if (_comboboxName == CarEditFrame::KERNEL) {
         carManager->deleteKernel(deleteItem);
     }
 }
/*static*/ bool CarAttributeEditFrame::showDialogBox = true;


 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*private*/ void CarAttributeEditFrame::addItemToCombobox(QString addItem) {
     if (_comboboxName == CarEditFrame::ROAD) {
         CarRoads::instance()->addName(addItem);
     }
     if (_comboboxName == CarEditFrame::TYPE) {
         CarTypes::instance()->addName(addItem);
         if (showDialogBox) {
//             int results = JOptionPane.showOptionDialog(this, tr("AddNewCarType"), Bundle
//                     .getMessage("ModifyLocations"), JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE,
//                     NULL, new Object[]{tr("ButtonYes"), tr("ButtonNo"),
//                         tr("ButtonDontShow")}, tr("ButtonNo"));
//             if (results == JOptionPane.YES_OPTION) {
          int results = QMessageBox::question(this, tr("Don't show again"), tr("Add new car type to service?"), QMessageBox::Yes| QMessageBox::No | QMessageBox::Cancel);
          if(results != QMessageBox::Yes)
          {
// TODO:                LocationsByCarTypeFrame lf = new LocationsByCarTypeFrame();
//                 lf.initComponents(addItem);

          }
             if (results == QMessageBox::Cancel) {
                 showDialogBox = false;
             }
//             results = JOptionPane.showOptionDialog(this, tr("AddNewCarType"), Bundle
//                     .getMessage("ModifyTrains"), JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE,
//                     NULL, new Object[]{tr("ButtonYes"), tr("ButtonNo"),
//                         tr("ButtonDontShow")}, tr("ButtonNo"));
             results = QMessageBox::question(this, tr("Don't show again"), tr("Add new car type to service?"), QMessageBox::Yes| QMessageBox::No | QMessageBox::Cancel);
             if (results == QMessageBox::Yes)
             {
    #if 0
                 TrainsByCarTypeFrame lf = new TrainsByCarTypeFrame();
                 lf.initComponents(addItem);
    #endif
             }
             if (results == QMessageBox::Cancel) {
                 showDialogBox = false;
             }
         }
     }

     if (_comboboxName == CarEditFrame::COLOR) {
         CarColors::instance()->addName(addItem);
     }
     if (_comboboxName == CarEditFrame::LENGTH) {
         // convert from inches to feet if needed
         if (addItem.endsWith("\"")) { // NOI18N
             addItem = addItem.mid(0, addItem.length() - 1);
             //try {
             bool ok;
                 double inches = (addItem.toDouble(&ok));
                 int feet = (int) (inches * Setup::getScaleRatio() / 12);
                 addItem = QString::number(feet);
             if(!ok) {
                 log->error("can not convert from inches to feet");
//                 JOptionPane.showMessageDialog(this, tr("CanNotConvertFeet"), Bundle
//                         .getMessage("ErrorCarLength"), JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(this, tr("Car length incorrect!"), tr("Can not convert from inches to feet"));
                 return;
             }
         }
         if (addItem.endsWith("cm")) { // NOI18N
             addItem = addItem.mid(0, addItem.length() - 2);
             //try {
             bool ok;
                 double cm = (addItem.toDouble(&ok));
                 int meter = (int) (cm * Setup::getScaleRatio() / 100);
                 addItem = QString::number(meter);
             if(!ok) {
                 log->error("Can not convert from cm to meters");
//                 JOptionPane.showMessageDialog(this, tr("CanNotConvertMeter"), Bundle
//                         .getMessage("ErrorCarLength"), JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(this, tr("Car length incorrect!"), tr("Can not convert from cm to meters"));
                 return;
             }
         }
         // confirm that length is a number and less than 10000 feet
         //try {
         bool ok;
             int length = (addItem.toInt(&ok));
             if (length < 0) {
                 log->error(tr("length (%1) has to be a positive number").arg(addItem));
                 return;
             }
             if (addItem.length() > Control::max_len_string_length_name) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(tr("carAttribute"),
//                         new Object[]{Control::max_len_string_length_name}), MessageFormat.format(Bundle
//                                 .getMessage("canNotAdd"), new Object[]{_comboboxName}), JOptionPane.ERROR_MESSAGE);
              QMessageBox::critical(this, tr("Can not add %1").arg(_comboboxName), tr("Car attribute must be {0} characters or less").arg(Control::max_len_string_length_name));
                 return;
             }
         if(!ok) {
             log->error(tr("length (%1) is not an integer").arg(addItem));
             return;
         }
         CarLengths::instance()->addName(addItem);
         comboBox->setCurrentIndex(comboBox->findText(addItem));
     }

     if (_comboboxName == CarEditFrame::KERNEL) {
         carManager->newKernel(addItem);
     }

     if (_comboboxName == CarEditFrame::OWNER) {
         CarOwners::instance()->addName(addItem);
     }

 }

 /*private*/ void CarAttributeEditFrame::replaceItem(QString oldItem, QString newItem) {
     // replace kernel
     if (_comboboxName == CarEditFrame::KERNEL) {
         carManager->replaceKernelName(oldItem, newItem);
     }
     // now adjust cars, locations and trains
     if (_comboboxName == CarEditFrame::TYPE) {
         CarTypes::instance()->replaceName(oldItem, newItem);
         CarLoads::instance()->replaceType(oldItem, newItem);
     }
     if (_comboboxName == CarEditFrame::ROAD) {
         CarRoads::instance()->replaceName(oldItem, newItem);
     }

     if (_comboboxName == CarEditFrame::OWNER) {
         CarOwners::instance()->replaceName(oldItem, newItem);
     }
     if (_comboboxName == CarEditFrame::LENGTH) {
         CarLengths::instance()->replaceName(oldItem, newItem);
     }

     if (_comboboxName == CarEditFrame::COLOR) {
         CarColors::instance()->replaceName(oldItem, newItem);
     }

 }

 /*private*/ void CarAttributeEditFrame::loadCombobox() {
     if (_comboboxName == CarEditFrame::ROAD) {
         comboBox = CarRoads::instance()->getComboBox();
         //CarRoads::instance().addPropertyChangeListener(this);
         connect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     if (_comboboxName == CarEditFrame::TYPE) {
         comboBox = CarTypes::instance()->getComboBox();
         //CarTypes::instance().addPropertyChangeListener(this);
         connect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

     if (_comboboxName == CarEditFrame::COLOR) {
         comboBox = CarColors::instance()->getComboBox();
         //CarColors::instance().addPropertyChangeListener(this);
         connect(CarColors::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

     if (_comboboxName == CarEditFrame::LENGTH) {
         comboBox = CarLengths::instance()->getComboBox();
         //CarLengths::instance().addPropertyChangeListener(this);
         connect(CarLengths::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     if (_comboboxName == CarEditFrame::OWNER) {
         comboBox = CarOwners::instance()->getComboBox();
         //CarOwners::instance().addPropertyChangeListener(this);
         connect(CarOwners::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

     if (_comboboxName == CarEditFrame::KERNEL) {
         comboBox = carManager->getKernelComboBox();
     }
 }


 /*public*/ void CarAttributeEditFrame::toggleShowQuanity() {
     if (showQuanity) {
         showQuanity = false;
     } else {
         showQuanity = true;
     }
     quanity->setVisible(showQuanity);
     updateCarQuanity();
 }

 /*private*/ void CarAttributeEditFrame::updateCarQuanity() {
     if (!showQuanity) {
         return;
     }
     int number = 0;
     QString item =  comboBox->currentText();
     log->debug(tr("Selected item %1").arg(item));
     foreach (RollingStock* rs, *carManager->getList()) {
         Car* car = (Car*) rs;

         if (_comboboxName == CarEditFrame::ROAD) {
             if (car->getRoadName()==(item)) {
                 number++;
             }
         }
         if (_comboboxName == CarEditFrame::TYPE) {
             if (car->getTypeName()==(item)) {
                 number++;
             }
         }
         if (_comboboxName == CarEditFrame::COLOR) {
             if (car->getColor()==(item)) {
                 number++;
             }
         }
         if (_comboboxName == CarEditFrame::LENGTH) {
             if (car->getLength()==(item)) {
                 number++;
             }
         }
         if (_comboboxName == CarEditFrame::OWNER) {
             if (car->getOwner()==(item)) {
                 number++;
             }
         }
         if (_comboboxName == CarEditFrame::KERNEL) {
             if (car->getKernelName()==(item)) {
                 number++;
             }
         }
     }
     quanity->setText(QString::number(number));
     // Tool to delete all attributes that haven't been assigned to a car
     if (number == 0 && deleteUnused) {
         // need to check if an engine is using the road name
         if (_comboboxName == CarEditFrame::ROAD) {
             foreach (RollingStock* rs, *EngineManager::instance()->getList()) {
                 if (rs->getRoadName()==(item)) {
                     log->info("Engine (" + rs->getRoadName() + " " + rs->getNumber()
                             + ") has assigned road name (" + item + ")"); // NOI18N
                     return;
                 }
             }
         }
         // confirm that attribute is to be deleted
         if (!cancel) {
//             int results = JOptionPane.showOptionDialog(NULL, MessageFormat.format(Bundle
//                     .getMessage("ConfirmDeleteAttribute"), new Object[]{_comboboxName, item}), Bundle
//                     .getMessage("DeleteAttribute?"), JOptionPane.YES_NO_CANCEL_OPTION,
//                     JOptionPane.QUESTION_MESSAGE, NULL, new Object[]{tr("ButtonYes"),
//                         tr("ButtonNo"), tr("ButtonCancel")}, Bundle
//                     .getMessage("ButtonYes"));
          int results = QMessageBox::question(this, tr("Delete?"), tr("Do you really want to delete %1 %2?").arg(_comboboxName).arg(item),QMessageBox::Yes| QMessageBox::No | QMessageBox::Cancel);
             if (results == QMessageBox::Yes) {
                 deleteItemFromCombobox( comboBox->currentText());
             }
             if (results == QMessageBox::Cancel || results == QMessageBox::No) {
                 cancel = true;
             }
         }
     }
 }


 /*public*/ void CarAttributeEditFrame::deleteUnusedAttribures() {
     if (!showQuanity) {
         toggleShowQuanity();
     }
     deleteUnused = true;
     cancel = false;
     int items = comboBox->count() - 1;
     for (int i = items; i >= 0; i--) {
         comboBox->setCurrentIndex(i);
     }
     deleteUnused = false; // done
     comboBox->setCurrentIndex(0); // update count
 }

 /*public*/ void CarAttributeEditFrame::dispose()
 {
     //CarRoads::instance().removePropertyChangeListener(this);
  disconnect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarTypes.instance().removePropertyChangeListener(this);
  disconnect(CarTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     //CarColors::instance().removePropertyChangeListener(this);
  disconnect(CarColors::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     //CarLengths.instance().removePropertyChangeListener(this);
     disconnect(CarLengths::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarOwners.instance().removePropertyChangeListener(this);
     disconnect(CarOwners::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     //carManager.removePropertyChangeListener(this);
   disconnect(carManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     firePcs(DISPOSE, _comboboxName, QVariant());
     OperationsFrame::dispose();
 }

 /*public*/ void CarAttributeEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::showProperty) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarRoads::CARROADS_CHANGED_PROPERTY)) {
         CarRoads::instance()->updateComboBox(comboBox);
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)) {
         CarTypes::instance()->updateComboBox(comboBox);
     }

     if (e->getPropertyName()==(CarColors::CARCOLORS_CHANGED_PROPERTY)) {
         CarColors::instance()->updateComboBox(comboBox);
     }

     if (e->getPropertyName()==(CarLengths::CARLENGTHS_CHANGED_PROPERTY)) {
         CarLengths::instance()->updateComboBox(comboBox);
     }
     if (e->getPropertyName()==(CarOwners::CAROWNERS_CHANGED_PROPERTY)) {
         CarOwners::instance()->updateComboBox(comboBox);
     }
     if (e->getPropertyName()==(CarManager::KERNEL_LISTLENGTH_CHANGED_PROPERTY)) {
         carManager->updateKernelComboBox(comboBox);
     }
     if (e->getPropertyName()==(CarManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateCarQuanity();
     }
 }
#if 0

 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 // note firePropertyChange occurs during frame creation
 /*private*/ void CarAttributeEditFrame::firePcs(QString p, QVariant old, QVariant n) {
     log->debug(tr("CarAttribute firePropertyChange %1").arg(p));
     pcs->firePropertyChange(p, old, n);
 }

 /*public*/ QString CarAttributeEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.rollingstock.cars.CarAttributeEditFrame";
 }

}
