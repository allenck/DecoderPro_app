#include "engineattributeeditframe.h"
#include "control.h"
#include <QComboBox>
#include <QPushButton>
#include "jtextfield.h"
#include <QLabel>
#include <QBoxLayout>
#include "engineeditframe.h"
#include <QMessageBox>
#include "trainmanager.h"
#include "enginemanager.h"
#include "enginemodels.h"
#include "engine.h"
#include "propertychangesupport.h"
#include "carroads.h"
#include "enginelengths.h"
#include "enginetypes.h"
#include "setup.h"
#include "carowners.h"

//EngineAttributeEditFrame::EngineAttributeEditFrame(QWidget *parent) :
//  OperationsFrame(parent)
//{
//}
namespace Operations
{
/**
 * Frame for adding and editing the engine roster for operations.
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29493 $
 */
///*public*/ class EngineAttributeEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

    /**
     *
     */
    ///*private*/ static final long serialVersionUID = 6682092348083316799L;
/*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::DISPOSE = "dispose"; // NOI18N

    /*public*/EngineAttributeEditFrame:: EngineAttributeEditFrame(QWidget *parent) :
  OperationsFrame(parent)
{
 setObjectName("EngineAttributeEditFrame");
 log = new Logger("EngineAttributeEditFrame");
 engineManager = EngineManager::instance();

 // labels
 textAttribute = new QLabel();
 textSep = new QLabel();

 // major buttons
 addButton = new QPushButton();
 deleteButton = new QPushButton();
 replaceButton = new QPushButton();

  // combo box
  comboBox = NULL;

  // text box
  addTextBox = new JTextField(Control::max_len_string_attibute);
  menuActive = false;
  pcs = new PropertyChangeSupport(this);

 }


 /*public*/ void EngineAttributeEditFrame::initComponents(QString comboboxName) {
     initComponents(comboboxName, "");
 }

 /*public*/ void EngineAttributeEditFrame::initComponents(QString comboboxName, QString select)
 {
  //getContentPane().removeAll();
  QLayout * l = getContentPane()->layout();
  if(l != NULL)
  {
   QObjectList ol = l->children();
   foreach(QObject* o, ol)
   {
    if(qobject_cast<QWidget*>(o)!=NULL)
    {
     l->removeWidget((QWidget*)o);
     delete o;
    }
   }
  }

  setTitle(tr("Edit Locomotive %1").arg(comboboxName));

  // track which combo box is being edited
  _comboboxName = comboboxName;
  loadCombobox();
  comboBox->setCurrentIndex(comboBox->findText(select));

  // general GUI config
  //getContentPane().setLayout(new GridBagLayout());
  QGridLayout* thisLayout = new QGridLayout(getContentPane());

  textAttribute->setText(comboboxName);

  addButton->setText(tr("Add"));
  addButton->setVisible(true);
  deleteButton->setText(tr("Delete"));
  deleteButton->setVisible(true);
  replaceButton->setText(tr("Replace"));
  replaceButton->setVisible(true);

  // row 1
  thisLayout->addWidget(textAttribute, 1, 1);
  // row 2
  thisLayout->addWidget(addTextBox, 1, 2);
  thisLayout->addWidget(addButton, 2, 2);

  // row 3
  thisLayout->addWidget(comboBox, 1, 3);
  thisLayout->addWidget(deleteButton, 2, 3);

  // row 4
  thisLayout->addWidget(replaceButton, 2, 4);

  addButtonAction(addButton);
  addButtonAction(deleteButton);
  addButtonAction(replaceButton);

  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_Locomotives", true); // NOI18N

  initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight250));
 }

 // add, delete or replace button
 /*public*/ void EngineAttributeEditFrame::buttonActionPerformed(QWidget* ae)
 {
     log->debug("edit frame button activated");
     QPushButton* source = (QPushButton*)ae;
     if (source == addButton) {
         QString addItem = addTextBox->text();
         if (addItem==("")) {
             return;
         }
         if (addItem.length() > Control::max_len_string_attibute) {
//             JOptionPane.showMessageDialog(this, tr("engineAttribute"),
//                     new Object[]{Control::max_len_string_attibute}), MessageFormat.format(Bundle
//                             .getMessage("canNotAdd"), new Object[]{_comboboxName}), JOptionPane.ERROR_MESSAGE);
             return;
             QMessageBox::critical(this, tr("Can not add %1").arg(_comboboxName), tr("Locomotive attribute must be %1 characters or less").arg(Control::max_len_string_attibute));
         }
         addItemToCombobox(addItem);
     }
     if (source == deleteButton) {
         QString deleteItem =  comboBox->currentText();
         deleteItemFromCombobox(deleteItem);
     }
     if (source == replaceButton) {
         QString newItem = addTextBox->text();
         if (newItem==("")) {
             return;
         }
         if (newItem.length() > Control::max_len_string_attibute) {
//             JOptionPane.showMessageDialog(this, tr("engineAttribute"),
//                     new Object[]{Control::max_len_string_attibute}), MessageFormat.format(Bundle
//                             .getMessage("canNotReplace"), new Object[]{_comboboxName}), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Can not replace %1").arg(_comboboxName), tr("Locomotive attribute must be %1 characters or less").arg(Control::max_len_string_attibute));
             return;
         }
         QString oldItem =  comboBox->currentText();
//         if (JOptionPane.showConfirmDialog(this, tr("replaceMsg"), new Object[]{
//             oldItem, newItem}), tr("replaceAll"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
         if(QMessageBox::critical(this, tr("Replace All?"), tr("Replace \"%1\" with \"%2\"").arg(oldItem).arg(newItem),  QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
         {

             return;
         }
         if (newItem==(oldItem)) {
             return;
         }
         // need to make sure locations and trains are loaded
         TrainManager::instance();
         addItemToCombobox(newItem);
         replaceItem(oldItem, newItem);
         deleteItemFromCombobox(oldItem);
     }
 }

 /*private*/ void EngineAttributeEditFrame::deleteItemFromCombobox(QString deleteItem)
{

     if (_comboboxName == EngineEditFrame::ROAD)
     {
         // purge train and locations by using replace
         CarRoads::instance()->replaceName(deleteItem, NULL);
     }

     if (_comboboxName == EngineEditFrame::MODEL) \
     {
         EngineModels::instance()->deleteName(deleteItem);
     }

     if (_comboboxName == EngineEditFrame::TYPE)
     {
         EngineTypes::instance()->deleteName(deleteItem);
     }
     if (_comboboxName == EngineEditFrame::LENGTH)
     {
         EngineLengths::instance()->deleteName(deleteItem);
     }

     if (_comboboxName == EngineEditFrame::OWNER)
     {
         CarOwners::instance()->deleteName(deleteItem);
     }

     if (_comboboxName == EngineEditFrame::CONSIST)
     {
         engineManager->deleteConsist(deleteItem);
     }
 }

 /*private*/ void EngineAttributeEditFrame::addItemToCombobox(QString addItem)
{

     if (_comboboxName == EngineEditFrame::ROAD) {
         CarRoads::instance()->addName(addItem);
     }

     if (_comboboxName == EngineEditFrame::MODEL) {
         EngineModels::instance()->addName(addItem);
     }

     if (_comboboxName == EngineEditFrame::TYPE) {
         EngineTypes::instance()->addName(addItem);
     }
     if (_comboboxName == EngineEditFrame::LENGTH) {
         // convert from inches to feet if needed
         if (addItem.endsWith("\"")) { // NOI18N
             addItem = addItem.mid(0, addItem.length() - 1);
             //try {
             bool ok;
                 double inches = addItem.toDouble(&ok);
                 int feet = (int) (inches * Setup::getScaleRatio() / 12);
                 addItem = QString::number(feet);
             if(!ok) {
                 log->error("can not convert from inches to feet");
//                    JOptionPane.showMessageDialog(this, tr("CanNotConvertFeet"), Bundle
//                            .getMessage("ErrorEngineLength"), JOptionPane.ERROR_MESSAGE);
              QMessageBox::critical(this, tr("Error Engine length"), tr("can not convert from inches to feet"));
              return;
             }
         }
         if (addItem.endsWith("cm")) { // NOI18N
             addItem = addItem.mid(0, addItem.length() - 2);
             //try {
             bool ok;
                 double cm = addItem.toDouble(&ok);
                 int meter = (int) (cm * Setup::getScaleRatio() / 100);
                 addItem = QString::number(meter);
             if(!ok) {
                 log->error("Can not convert from cm to meters");
//                    JOptionPane.showMessageDialog(this, tr("CanNotConvertMeter"), Bundle
//                            .getMessage("ErrorEngineLength"), JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(this, tr("Error Engine length"), tr("Can not convert from cm to meters"));
                return;
             }
         }
         // confirm that length is a number and less than 10000 feet
         //try {
         bool ok;
             int length = addItem.toInt(&ok);
             if (length < 0) {
                 log->error("engine length has to be a positive number");
                 return;
             }
             if (addItem.length() > Control::max_len_string_length_name) {
//                    JOptionPane.showMessageDialog(this, tr("engineAttribute"),
//                            new Object[]{Control::max_len_string_length_name}), MessageFormat.format(Bundle
//                                    .getMessage("canNotAdd"), new Object[]{_comboboxName}), JOptionPane.ERROR_MESSAGE);
              QMessageBox::critical(this, tr("Can not add %1").arg(_comboboxName), tr("Engine attribute %1").arg(Control::max_len_string_length_name));
                 return;
             }
         if(!ok) {
             log->error("length not an integer");
             return;
         }
         EngineLengths::instance()->addName(addItem);
         comboBox->setCurrentIndex(comboBox->findText(addItem));
     }

     if (_comboboxName == EngineEditFrame::CONSIST) {
         engineManager->newConsist(addItem);
     }

     if (_comboboxName == EngineEditFrame::OWNER) {
         CarOwners::instance()->addName(addItem);
     }
 }

 /*private*/ void EngineAttributeEditFrame::replaceItem(QString oldItem, QString newItem) {
     QList<RollingStock*>* engines = engineManager->getList();
     foreach (RollingStock* rs, *engines) {
         Engine* engine = (Engine*) rs;
         if (_comboboxName == EngineEditFrame::MODEL) {
             // we need to copy the old model attributes, so find an engine->
             if (engine->getModel()==(oldItem)) {
                 // Has this model been configured?
                 if (EngineModels::instance()->getModelLength(newItem) != NULL) {
                     engine->setModel(newItem);
                 } else {
                     // get the old configuration for this model
                     QString length = engine->getLength();
                     QString hp = engine->getHp();
                     QString type = engine->getTypeName();
                     // now update the new model
                     engine->setModel(newItem);
                     engine->setLength(length);
                     engine->setHp(hp);
                     engine->setTypeName(type);
                 }
             }
         }
     }
     if (_comboboxName == EngineEditFrame::CONSIST) {
         engineManager->replaceConsistName(oldItem, newItem);
     }

     // now adjust locations and trains
     if (_comboboxName == EngineEditFrame::TYPE) {
         EngineTypes::instance()->replaceName(oldItem, newItem);
     }

     if (_comboboxName == EngineEditFrame::ROAD) {
         CarRoads::instance()->replaceName(oldItem, newItem);
     }

     if (_comboboxName == EngineEditFrame::OWNER) {
         CarOwners::instance()->replaceName(oldItem, newItem);
     }

     if (_comboboxName == EngineEditFrame::LENGTH) {
         EngineLengths::instance()->replaceName(oldItem, newItem);
     }

     if (_comboboxName == EngineEditFrame::MODEL) {
         EngineModels::instance()->replaceName(oldItem, newItem);
     }
 }

/*private*/ void  EngineAttributeEditFrame::loadCombobox()
{
  if (_comboboxName == EngineEditFrame::ROAD) {
      comboBox = CarRoads::instance()->getComboBox();
      //CarRoads::instance().addPropertyChangeListener(this);
      connect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }

  if (_comboboxName == EngineEditFrame::MODEL) {
      comboBox = EngineModels::instance()->getComboBox();
      //EngineModels::instance().addPropertyChangeListener(this);
      connect(EngineModels::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }

  if (_comboboxName == EngineEditFrame::TYPE) {
      comboBox = EngineTypes::instance()->getComboBox();
      //EngineTypes::instance().addPropertyChangeListener(this);
      connect(EngineTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  if (_comboboxName == EngineEditFrame::LENGTH) {
      comboBox = EngineLengths::instance()->getComboBox();
      //EngineLengths::instance().addPropertyChangeListener(this);
      connect(EngineLengths::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }

  if (_comboboxName == EngineEditFrame::OWNER) {
      comboBox = CarOwners::instance()->getComboBox();
      //CarOwners::instance().addPropertyChangeListener(this);
      connect(CarOwners::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }

  if (_comboboxName == EngineEditFrame::CONSIST) {
      comboBox = engineManager->getConsistComboBox();
      //engineManager.addPropertyChangeListener(this);
      connect(engineManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }

 /*public*/ void EngineAttributeEditFrame::dispose()
 {
  //        CarRoads.instance().removePropertyChangeListener(this);
  disconnect(CarRoads::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //EngineModels.instance().removePropertyChangeListener(this);
  disconnect(EngineModels::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //        EngineTypes.instance().removePropertyChangeListener(this);
  disconnect(EngineTypes::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //        EngineLengths.instance().removePropertyChangeListener(this);
  disconnect(EngineLengths::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //        CarOwners.instance().removePropertyChangeListener(this);
  disconnect(CarOwners::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //engineManager.removePropertyChangeListener(this);
  disconnect(engineManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  firePcs(DISPOSE, _comboboxName, QVariant());
  OperationsFrame::dispose();
 }

 /*public*/ void EngineAttributeEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::showProperty) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }

     if (e->getPropertyName()==(CarRoads::CARROADS_CHANGED_PROPERTY)) {
         CarRoads::instance()->updateComboBox(comboBox);
     }

     if (e->getPropertyName()==(EngineModels::ENGINEMODELS_CHANGED_PROPERTY)) {
         EngineModels::instance()->updateComboBox(comboBox);
     }

     if (e->getPropertyName()==(EngineTypes::ENGINETYPES_CHANGED_PROPERTY)) {
         EngineTypes::instance()->updateComboBox(comboBox);
     }
     if (e->getPropertyName()==(EngineLengths::ENGINELENGTHS_CHANGED_PROPERTY)) {
         EngineLengths::instance()->updateComboBox(comboBox);
     }

     if (e->getPropertyName()==(CarOwners::CAROWNERS_CHANGED_PROPERTY)) {
         CarOwners::instance()->updateComboBox(comboBox);
     }

     if (e->getPropertyName()==(EngineManager::CONSISTLISTLENGTH_CHANGED_PROPERTY)) {
         engineManager->updateConsistComboBox(comboBox);
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
 /*private*/ void EngineAttributeEditFrame::firePcs(QString p, QVariant old, QVariant n)
 {
     log->debug(tr("EngineAttribute firePropertyChange %1").arg(p));
     pcs->firePropertyChange(p, old, n);
 }
}
