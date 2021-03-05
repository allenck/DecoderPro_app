#include "engineattributeeditframe.h"
#include "control.h"
#include "jcombobox.h"
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
#include "instancemanager.h"

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
 /*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::ROAD = tr("Road");
 /*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::MODEL = tr("Model");
 /*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::TYPE = tr("Type");
 /*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::COLOR = tr("Color");
 /*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::LENGTH = tr("Length");
 /*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::OWNER = tr("Owner");
 /*public*/ /*static*/ /*final*/ QString EngineAttributeEditFrame::CONSIST = tr("Consist");

    /*public*/EngineAttributeEditFrame:: EngineAttributeEditFrame(QWidget *parent) :
  RollingStockAttributeEditFrame(parent)
{
 setObjectName("EngineAttributeEditFrame");
 log = new Logger("EngineAttributeEditFrame");
 engineManager = ((EngineManager*)InstanceManager::getDefault("EngineManager"));
}


 /*public*/ void EngineAttributeEditFrame::initComponents(QString attribute) {
     initComponents(attribute, NONE);
 }

 /*public*/ void EngineAttributeEditFrame::initComponents(QString attribute, QString name)
 {
  RollingStockAttributeEditFrame::initComponents(attribute, name);
  setTitle(tr("Edit Locomotive %1").arg(attribute ));

  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_Locomotives", true); // NOI18N

  initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight250));
 }

 //@Override
     /*protected*/ void EngineAttributeEditFrame::deleteAttributeName(QString deleteItem) {
         RollingStockAttributeEditFrame::deleteAttributeName(deleteItem);
         if (_attribute == (MODEL)) {
             ((EngineModels*)InstanceManager::getDefault("EngineModels"))->deleteName(deleteItem);
         }
         if (_attribute == (TYPE)) {
             ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->deleteName(deleteItem);
         }
         if (_attribute == (LENGTH)) {
             ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->deleteName(deleteItem);
         }
         if (_attribute == (CONSIST)) {
             engineManager->deleteConsist(deleteItem);
         }
     }

     //@Override
     /*protected*/ void EngineAttributeEditFrame::addAttributeName(QString addItem) {
         RollingStockAttributeEditFrame::addAttributeName(addItem);
         if (_attribute == (MODEL)) {
             ((EngineModels*)InstanceManager::getDefault("EngineModels"))->addName(addItem);
         }
         if (_attribute ==(TYPE)) {
             ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->addName(addItem);
         }
         if (_attribute == (LENGTH)) {
             QString length = convertLength(addItem);
             if (length!=(FAILED)) {
                 ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->addName(length);
                 comboBox->setCurrentText(length);
             }
         }
         if (_attribute == (CONSIST)) {
             engineManager->newConsist(addItem);
         }
     }

     //@Override
     /*protected*/ void EngineAttributeEditFrame::replaceItem(QString oldItem, QString newItem) {
         RollingStockAttributeEditFrame::replaceItem(oldItem, newItem);
         if (_attribute ==(MODEL)) {
             QList<RollingStock*>* engines = engineManager->getList();
             for (RollingStock* rs : *engines) {
                 Engine* engine = (Engine*)rs;
                 // we need to copy the old model attributes, so find an engine.
                 if (engine->getModel() == (oldItem)) {
                     // Has this model been configured?
                     if (((EngineModels*)InstanceManager::getDefault("EngineModels"))->getModelLength(newItem) != nullptr) {
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
             ((EngineModels*)InstanceManager::getDefault("EngineModels"))->replaceName(oldItem, newItem);
         }
         if (_attribute == (CONSIST)) {
             engineManager->replaceConsistName(oldItem, newItem);
         }
         if (_attribute == (TYPE)) {
             ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->replaceName(oldItem, newItem);
         }
         if (_attribute == (LENGTH)) {
             ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->replaceName(oldItem, newItem);
         }
     }

     //@Override
     /*protected*/ void EngineAttributeEditFrame::loadCombobox() {
         RollingStockAttributeEditFrame::loadCombobox();
         if (_attribute == (MODEL)) {
             comboBox = ((EngineModels*)InstanceManager::getDefault("EngineModels"))->getComboBox();
             ((EngineModels*)InstanceManager::getDefault("EngineModels"))->addPropertyChangeListener((PropertyChangeListener*)this);
         }
         if (_attribute == (TYPE)) {
             comboBox = ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->getComboBox();
             ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->addPropertyChangeListener((PropertyChangeListener*)this);
         }
         if (_attribute == LENGTH) {
             comboBox = ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->getComboBox();
             ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->addPropertyChangeListener((PropertyChangeListener*)this);
         }
         if (_attribute ==(CONSIST)) {
             comboBox = engineManager->getConsistComboBox();
             engineManager->addPropertyChangeListener((PropertyChangeListener*)this);
         }
     }

     //@Override
     /*public*/ void EngineAttributeEditFrame::dispose() {
         ((EngineModels*)InstanceManager::getDefault("EngineModels"))->removePropertyChangeListener((PropertyChangeListener*)this);
         ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->removePropertyChangeListener((PropertyChangeListener*)this);
         ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->removePropertyChangeListener((PropertyChangeListener*)this);
         engineManager->removePropertyChangeListener((PropertyChangeListener*)this);
         RollingStockAttributeEditFrame::dispose();
     }

     //@Override
     /*public*/ void EngineAttributeEditFrame::propertyChange(PropertyChangeEvent* e) {
         RollingStockAttributeEditFrame::propertyChange(e);
         if (Control::SHOW_PROPERTY) {
             log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(
                     e->getNewValue().toString()));
         }
         if (e->getPropertyName()==(EngineModels::ENGINEMODELS_CHANGED_PROPERTY)) {
             ((EngineModels*)InstanceManager::getDefault("EngineModels"))->updateComboBox(comboBox);
         }
         if (e->getPropertyName() == (EngineTypes::ENGINETYPES_CHANGED_PROPERTY)) {
             ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->updateComboBox(comboBox);
         }
         if (e->getPropertyName() == (EngineLengths::ENGINELENGTHS_CHANGED_PROPERTY)) {
             ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->updateComboBox(comboBox);
         }
         if (e->getPropertyName() == (EngineManager::CONSISTLISTLENGTH_CHANGED_PROPERTY)) {
             engineManager->updateConsistComboBox(comboBox);
         }
     }

     /*public*/ QString EngineAttributeEditFrame::getClassName() {return "jmri.jmrit.operations.engines.tools.EngineAttributeEditFrame";}
}
