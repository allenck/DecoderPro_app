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
#include "instancemanager.h"
#include "carattributeaction.h"
#include "cardeleteattributeaction.h"
#include "joptionpane.h"
#include "locationsbycartypeframe.h"
#include "trainsbycartypeframe.h"
#include "loggerfactory.h"

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

 // valid attributes for this frame
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::ROAD = tr("Road");
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::TYPE = tr("Type");
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::COLOR = tr("Color");
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::LENGTH = tr("Length");
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::OWNER = tr("Owner");
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::KERNEL = tr("Kernel");

 // property change
 /*public*/ /*static*/ /*final*/ QString CarAttributeEditFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ CarAttributeEditFrame::CarAttributeEditFrame(QWidget* parent)
  : RollingStockAttributeEditFrame(parent)
 {
  setObjectName("CarAttributeEditFrame");
  log = new Logger("CarAttributeEditFrame");
  pcs = new PropertyChangeSupport(this);
  carManager = CarManager::instance();
 }


 /*public*/ void CarAttributeEditFrame::initComponents(QString attribute) {
     initComponents(attribute, NONE);
 }

 /*public*/ void CarAttributeEditFrame::initComponents(QString attribute, QString name)
 {
  RollingStockAttributeEditFrame::initComponents(attribute, name);

       setTitle(tr("Edit Car %1").arg(attribute ));
       carManager->addPropertyChangeListener((PropertyChangeListener*)this);

       addComboBoxAction(comboBox);

       // build menu
       QMenuBar* menuBar = new QMenuBar();
       QMenu* toolMenu = new QMenu(tr("Tools"));
       toolMenu->addAction(new CarAttributeAction(this));
       toolMenu->addAction(new CarDeleteAttributeAction(this));
       menuBar->addMenu(toolMenu);
       setMenuBar(menuBar);
       // add help menu to window
       addHelpMenu("package.jmri.jmrit.operations.Operations_EditCarAttributes", true); // NOI18N
   }

   //@Override
   /*protected*/ void CarAttributeEditFrame::comboBoxActionPerformed(QWidget* ae) {
       log->debug("Combo box action");
       updateCarQuanity();
   }

   //@Override
   /*protected*/ void CarAttributeEditFrame::deleteAttributeName(QString deleteItem) {
       RollingStockAttributeEditFrame::deleteAttributeName(deleteItem);
       if (_attribute ==(TYPE)) {
           ((CarTypes*)InstanceManager::getDefault("CarTypes"))->deleteName(deleteItem);
       }
       if (_attribute == (COLOR)) {
           ((CarColors*)InstanceManager::getDefault("CarColors"))->deleteName(deleteItem);
       }
       if (_attribute == (LENGTH)) {
           ((CarLengths*)InstanceManager::getDefault("CarLengths"))->deleteName(deleteItem);
       }
       if (_attribute == (KERNEL)) {
           carManager->deleteKernel(deleteItem);
       }
   }

   //@Override
   //@SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD", justification = "GUI ease of use")
   /*protected*/ void CarAttributeEditFrame::addAttributeName(QString addItem) {
       RollingStockAttributeEditFrame::addAttributeName(addItem);
       if (_attribute == (TYPE)) {
           ((CarTypes*)InstanceManager::getDefault("CarTypes"))->addName(addItem);
           if (showDialogBox) {
               int results = JOptionPane::showOptionDialog(this, tr("Add new car type to service?"),
                       tr("Modify locations?"), JOptionPane::YES_NO_CANCEL_OPTION,
                       JOptionPane::QUESTION_MESSAGE, QIcon(), QVariantList() = { tr("Yes"),
                               tr("No"), tr("Don't show again") },
                       tr("No"));
               if (results == JOptionPane::YES_OPTION) {
                   LocationsByCarTypeFrame* lf = new LocationsByCarTypeFrame();
                   lf->initComponents(addItem);
               }
               if (results == JOptionPane::CANCEL_OPTION) {
                   showDialogBox = false;
               }
               results = JOptionPane::showOptionDialog(this, tr("Add new car type to service?"),
                       tr("Modify trains?"), JOptionPane::YES_NO_CANCEL_OPTION,
                       JOptionPane::QUESTION_MESSAGE, QIcon(), QVariantList() = { tr("Yes"),
                       tr("No"), tr("Don't show again") },
                       tr("No"));
               if (results == JOptionPane::YES_OPTION) {
                   TrainsByCarTypeFrame* lf = new TrainsByCarTypeFrame();
                   lf->initComponents(addItem);
               }
               if (results == JOptionPane::CANCEL_OPTION) {
                   showDialogBox = false;
               }
           }
       }
       if (_attribute == (COLOR)) {
           ((CarColors*)InstanceManager::getDefault("CarColors"))->addName(addItem);
       }
       if (_attribute == (LENGTH)) {
           QString length = convertLength(addItem);
           if (length != (FAILED)) {
               ((CarLengths*)InstanceManager::getDefault("CarLengths"))->addName(length);
               comboBox->setCurrentText(length);
           }
       }
       if (_attribute == (KERNEL)) {
           carManager->newKernel(addItem);
       }
       if (_attribute == (OWNER)) {
           ((CarOwners*)InstanceManager::getDefault("CarOwners"))->addName(addItem);
       }
   }

   //@Override
   /*protected*/ void CarAttributeEditFrame::replaceItem(QString oldItem, QString newItem) {
       RollingStockAttributeEditFrame::replaceItem(oldItem, newItem);
       // replace kernel
       if (_attribute == (KERNEL)) {
           carManager->replaceKernelName(oldItem, newItem);
       }
       // now adjust cars, locations and trains
       if (_attribute == (TYPE)) {
           ((CarTypes*)InstanceManager::getDefault("CarTypes"))->replaceName(oldItem, newItem);
           ((CarLoads*)InstanceManager::getDefault("CarLoads"))->replaceType(oldItem, newItem);
       }
       if (_attribute == (LENGTH)) {
           ((CarLengths*)InstanceManager::getDefault("CarLengths"))->replaceName(oldItem, newItem);
       }
       if (_attribute == (COLOR)) {
           ((CarColors*)InstanceManager::getDefault("CarColors"))->replaceName(oldItem, newItem);
       }
   }

   //@Override
   /*protected*/ void CarAttributeEditFrame::loadCombobox() {
       RollingStockAttributeEditFrame::loadCombobox();
       if (_attribute == (TYPE)) {
           comboBox = ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getComboBox();
           ((CarTypes*)InstanceManager::getDefault("CarTypes"))->addPropertyChangeListener((PropertyChangeListener*)this);
       }
       if (_attribute == (COLOR)) {
           comboBox = ((CarColors*)InstanceManager::getDefault("CarColors"))->getComboBox();
           ((CarColors*)InstanceManager::getDefault("CarColors"))->addPropertyChangeListener((PropertyChangeListener*)this);
       }
       if (_attribute == (LENGTH)) {
           comboBox = ((CarLengths*)InstanceManager::getDefault("CarLengths"))->getComboBox();
           ((CarLengths*)InstanceManager::getDefault("CarLengths"))->addPropertyChangeListener((PropertyChangeListener*)this);
       }
       if (_attribute == (KERNEL)) {
           comboBox = carManager->getKernelComboBox();
       }
   }

   /*public*/ void CarAttributeEditFrame::toggleShowQuanity() {
       showQuanity = !showQuanity;
       quanity->setVisible(showQuanity);
       updateCarQuanity();
   }

   /*private*/ void CarAttributeEditFrame::updateCarQuanity() {
       if (!showQuanity) {
           return;
       }
       int number = 0;
       QString item = comboBox->currentText();
       log->debug(tr("Selected item %1").arg(item));
       for (RollingStock* rs : *carManager->getList()) {
           Car* car = (Car*)rs;
           if (_attribute == (ROAD)) {
               if (car->getRoadName() == (item)) {
                   number++;
               }
           }
           if (_attribute == (TYPE)) {
               if (car->getTypeName() == (item)) {
                   number++;
               }
           }
           if (_attribute == (COLOR)) {
               if (car->getColor() == (item)) {
                   number++;
               }
           }
           if (_attribute == (LENGTH)) {
               if (car->getLength() == (item)) {
                   number++;
               }
           }
           if (_attribute == (OWNER)) {
               if (car->getOwner() == (item)) {
                   number++;
               }
           }
           if (_attribute == (KERNEL)) {
               if (car->getKernelName() == (item)) {
                   number++;
               }
           }
       }
       quanity->setText(QString::number(number));
       // Tool to delete all attributes that haven't been assigned to a car
       if (number == 0 && deleteUnused) {
           // need to check if an engine is using the road name
           if (_attribute == (ROAD)) {
               for (RollingStock* rs : *((EngineManager*)InstanceManager::getDefault("EngineManager"))->getList()) {
                   if (rs->getRoadName() == (item)) {
                       log->info(tr("Engine (%1 %2) is assigned road name (%3)").arg(rs->getRoadName()).arg(rs->getNumber()).arg(item)); // NOI18N
                       return;
                   }
               }
           }
           // need to check if an engine is using the road name
           if (_attribute == (OWNER)) {
               for (RollingStock* rs : *((EngineManager*)InstanceManager::getDefault("EngineManager"))->getList()) {
                   if (rs->getOwner() == (item)) {
                       log->info(tr("Engine (%1 %2) is assigned owner name (%3)").arg(rs->getRoadName()).arg(rs->getNumber()).arg(item)); // NOI18N
                       return;
                   }
               }
           }
           // confirm that attribute is to be deleted
           if (!cancel) {
               int results = JOptionPane::showOptionDialog(nullptr,
                       tr("Do you really want to delete %1 %2?").arg(_attribute).arg(item ),
                       tr("Delete Attribute Name?"), JOptionPane::YES_NO_CANCEL_OPTION,
                       JOptionPane::QUESTION_MESSAGE, QIcon(), QVariantList() = { tr("Yes"),
                               tr("o"), tr("Cancel") },
                       tr("Yes"));
               if (results == JOptionPane::YES_OPTION) {
                   deleteAttributeName( comboBox->currentText());
               }
               if (results == JOptionPane::CANCEL_OPTION || results == JOptionPane::CLOSED_OPTION) {
                   cancel = true;
               }
           }
       }
   }

   /*public*/ void CarAttributeEditFrame::deleteUnusedAttributes() {
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
       comboBox->setCurrentIndex(0);
   }

   //@Override
   /*public*/ void CarAttributeEditFrame::dispose() {
       ((CarTypes*)InstanceManager::getDefault("CarTypes"))->removePropertyChangeListener((PropertyChangeListener*)this);
       ((CarColors*)InstanceManager::getDefault("CarColors"))->removePropertyChangeListener((PropertyChangeListener*)this);
       ((CarLengths*)InstanceManager::getDefault("CarLengths"))->removePropertyChangeListener((PropertyChangeListener*)this);
       carManager->removePropertyChangeListener((PropertyChangeListener*)this);
       RollingStockAttributeEditFrame::dispose();
   }

   //@Override
   /*public*/ void CarAttributeEditFrame::propertyChange(PropertyChangeEvent* e) {
       RollingStockAttributeEditFrame::propertyChange(e);
       if (Control::SHOW_PROPERTY) {
           log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(
                    e->getNewValue().toString()));
       }
       if ( e->getPropertyName() == (CarTypes::CARTYPES_CHANGED_PROPERTY)) {
           ((CarTypes*)InstanceManager::getDefault("CarTypes"))->updateComboBox(comboBox);
       }
       if ( e->getPropertyName() == (CarColors::CARCOLORS_CHANGED_PROPERTY)) {
           ((CarColors*)InstanceManager::getDefault("CarColors"))->updateComboBox(comboBox);
       }
       if ( e->getPropertyName() == (CarLengths::CARLENGTHS_CHANGED_PROPERTY)) {
           ((CarLengths*)InstanceManager::getDefault("CarLengths"))->updateComboBox(comboBox);
       }
       if ( e->getPropertyName() == (CarManager::KERNEL_LISTLENGTH_CHANGED_PROPERTY)) {
           carManager->updateKernelComboBox(comboBox);
       }
       if ( e->getPropertyName() == (CarManager::LISTLENGTH_CHANGED_PROPERTY)) {
           updateCarQuanity();
       }
   }

 /*public*/ QString CarAttributeEditFrame::getClassName() {return "jmri.jmrit.operations.rollingstock.cars.tools.CarAttributeEditFrame";}

   /*private*/ /*final*/ /*static*/ Logger* CarAttributeEditFrame::log = LoggerFactory::getLogger("CarAttributeEditFrame");
}
