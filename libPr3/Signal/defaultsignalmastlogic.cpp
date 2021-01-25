#include "defaultsignalmastlogic.h"
#include "signalmastlogic.h"
#include "signalmast.h"
#include "../LayoutEditor/layouteditor.h"
#include "../LayoutEditor/panelmenu.h"
#include "instancemanager.h"
#include "runnable.h"
#include "exceptions.h"
#include "signalmastlogicmanager.h"
#include "signalspeedmap.h"
#include "abstractsensor.h"
#include "../LayoutEditor/connectivityutil.h"
#include "layoutblock.h"
#include "defaultsignalappearancemap.h"
#include "abstractsignalmast.h"
#include "signalheadsignalmast.h"
#include "turnoutsignalmast.h"
#include "virtualsignalmast.h"
#include "path.h"
#include "block.h"
#include "entrypoint.h"
#include "layouttrackexpectedstate.h"
#include "defaultsignalmastlogicmanager.h"
#include "loggerfactory.h"

class RunnableThis : public Runnable
{
 public:
    RunnableThis(DefaultSignalMastLogic* dsml)
    {
     this->dsml = dsml;
    }
    /*public*/ void run()
    {
     try
     {
        QThread::wait(((DefaultSignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalLogicDelay()/2);
        dsml->inWait=false;
        dsml->setMastAppearance();
     }
     catch (InterruptedException ex)
     {
        QThread::currentThread()->terminate();
        dsml->inWait=false;
     }
    }
    DefaultSignalMastLogic* dsml;
};

//DefaultSignalMastLogic::DefaultSignalMastLogic(QObject *parent) :
//    SignalMastLogic(parent)
//{
//}
/**
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU GeneDefaultral Public License
 * for more details.
 * <P>
 *
 * @author			Kevin Dickerson Copyright (C) 2011
 * @version			$Revision: 22310 $
 */

///*public*/ class DefaultSignalMastLogic : public SignalMastLogic {

/**
 * Initialise the signal mast logic
 * @param source - The signalmast we are configuring
 */
/*public*/ DefaultSignalMastLogic::DefaultSignalMastLogic (/*@Nonnull*/ SignalMast* source, QObject */*parent*/)
{
 if(source == nullptr)
  throw NullPointerException(tr("source is marked @NonNull but is null."));
 this->source = source;
 destList =  QHash<SignalMast*, DestinationMast*>();
 pcs = new PropertyChangeSupport(this);
 propertyDestinationMastListener = new PropertyDestinationMastListener(this);
 propertySourceMastListener = new PropertySourceMastListener(this);
 thr = nullptr;
 try
 {
  this->stopAspect = source->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER);
  this->source->addPropertyChangeListener(propertySourceMastListener);
  connect(this->source->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertySourceMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
  if(source->getAspect()=="")
    source->setAspect(stopAspect);
 }
 catch(Exception ex)
 {
  log->error(tr("Error while creating Signal Logic %1").arg(ex.getMessage()));
 }

}

/*public*/ void DefaultSignalMastLogic::setFacingBlock(LayoutBlock* facing){
    facingBlock = facing;
}

/*public*/ LayoutBlock* DefaultSignalMastLogic::getFacingBlock(){
    return facingBlock;
}

/*public*/ LayoutBlock* DefaultSignalMastLogic::getProtectingBlock(/*@Nonnull*/ SignalMast* mast) {
 if(mast == nullptr)
  throw NullPointerException(tr("dest is marked @NonNull but is null."));

 if (!destList.contains(mast)) {
     return nullptr;
 }
 return destList.value(mast)->getProtectingBlock();
}

/*public*/ SignalMast* DefaultSignalMastLogic::getSourceMast(){
    return source;
}

/*public*/ void DefaultSignalMastLogic::replaceSourceMast(SignalMast* oldMast, SignalMast* newMast)
{
 if(oldMast!=source)
 {
     //Old mast does not match new mast so will exit
     return;
 }
 source->removePropertyChangeListener(propertySourceMastListener);
 disconnect(source, SIGNAL(propertyChange(PropertyChangeEvent*)), propertySourceMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
 source = newMast;
 stopAspect = source->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER);
 source->addPropertyChangeListener(propertySourceMastListener);
 if(source->getAspect()==nullptr)
     source->setAspect(stopAspect);
 for (SignalMast* sm : getDestinationList())
 {
  DestinationMast* destMast = destList.value(sm);
  if (destMast->getAssociatedSection() != nullptr) {
      QString oldUserName = destMast->getAssociatedSection()->getUserName();
      QString newUserName = source->getDisplayName() + ":" + sm->getDisplayName();
      if (!oldUserName.isNull()) {
          ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->renameBean(oldUserName, newUserName, (NamedBean*)destMast->getAssociatedSection());
      } else {
          log->warn(tr("AssociatedSection oldUserName null for destination mast %1, skipped").arg(destMast->getDisplayName()));
      }
  }
 }
 firePropertyChange("updatedSource", VPtr<SignalMast>::asQVariant(oldMast), VPtr<SignalMast>::asQVariant(newMast));
}

/*public*/ void DefaultSignalMastLogic::replaceDestinationMast(SignalMast* oldMast, SignalMast* newMast)
{
 if(!destList.contains(oldMast))
 {
     return;
 }
 DestinationMast* destMast = destList.value(oldMast);
 destMast->updateDestinationMast(newMast);
 if(destination==oldMast)
 {
  oldMast->removePropertyChangeListener(propertyDestinationMastListener);
  disconnect(oldMast->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyDestinationMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
  newMast->addPropertyChangeListener(propertyDestinationMastListener);
  connect(newMast->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyDestinationMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
  destination=newMast;
  setSignalAppearance();
 }
 destList.remove(oldMast);
 if (destMast->getAssociatedSection() != nullptr)
 {
  QString oldUserName = destMast->getAssociatedSection()->getUserName();
  QString newUserName = source->getDisplayName() + ":" + newMast->getDisplayName();
  if (!oldUserName.isNull()) {
      ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->renameBean(oldUserName, newUserName, (NamedBean*)destMast->getAssociatedSection());
  } else {
      log->warn(tr("AssociatedSection oldUserName null for destination mast %1, skipped").arg(destMast->getDisplayName()));
  }
 }
 destList.insert(newMast, destMast);
 firePropertyChange("updatedDestination", VPtr<SignalMast>::asQVariant(oldMast), VPtr<SignalMast>::asQVariant(newMast));
}

/*public*/ void DefaultSignalMastLogic::setDestinationMast(SignalMast* dest)
{
 if(destList.contains(dest))
 {
  return;
 }
 int oldSize = destList.size();
 destList.insert(dest, new DestinationMast(dest, this));
 //InstanceManager::signalMastLogicManagerInstance().addDestinationMastToLogic(this, dest);
 firePropertyChange("length", QVariant(oldSize), QVariant(destList.size()));
 // make new dest mast appear in (update of) SignallingSourcePanel Table by having that table listen to PropertyChange Events from SML TODO
}

/*public*/ bool DefaultSignalMastLogic::isDestinationValid(SignalMast* dest)
{
 if(dest==nullptr)
  return false;
 return destList.contains(dest);
}

/*public*/ QList<SignalMast*> DefaultSignalMastLogic::getDestinationList()
{
 QList<SignalMast*> out =  QList<SignalMast*>();
 //Enumeration<SignalMast*> en = destList.keys();
 QListIterator<SignalMast*> en(destList.keys());
 while (en.hasNext())
 {
  out.append(en.next());
 }
 return out;
}

/*public*/ QString DefaultSignalMastLogic::getComment(SignalMast* dest)
{
 if(!destList.contains(dest)){
     return "";
 }
 return destList.value(dest)->getComment();
}

/*public*/ void DefaultSignalMastLogic::setComment(QString comment, SignalMast* dest)
{
 if(!destList.contains(dest)){
     return;
 }
 destList.value(dest)->setComment(comment);
}

/**
 * Use this to determine if the signalmast logic is stored in the panel file
 * and if all the information is stored.
 * @param store
 */
/*public*/ void DefaultSignalMastLogic::setStore(int store, SignalMast* destination)
{
 if(!destList.contains(destination)){
     return;
 }
 destList.value(destination)->setStore(store);
}

/**
 * returns where the signalmast logic should be stored, if so how much.
 */
/*public*/ int DefaultSignalMastLogic::getStoreState(SignalMast* destination)
{
 if(!destList.contains(destination)){
     return STORENONE;
 }
 return destList.value(destination)->getStoreState();
}

/**
* Sets the logic to the destination signal mast to be enabled.
*/
/*public*/ void DefaultSignalMastLogic::setEnabled(SignalMast* dest)
{
 if(!destList.contains(dest)){
     return;
 }
 destList.value(dest)->setEnabled();
}

/**
* Sets the logic to the destination signal mast to be disabled.
*/    
/*public*/ void DefaultSignalMastLogic::setDisabled(SignalMast* dest)
{
 if(!destList.contains(dest))
 {
  return;
 }
 destList.value(dest)->setDisabled();
}

/**
* Query if the signalmast logic to the destination signal mast is enabled or disabled.
*/
/*public*/ bool DefaultSignalMastLogic::isEnabled(SignalMast* dest) { 
    if(!destList.contains(dest)){
        return false;
    }
    return destList.value(dest)->isEnabled();
}

/**
* Query if the signalmast logic to the destination signal mast is active.
*/
/*public*/ bool DefaultSignalMastLogic::isActive(SignalMast* dest)
{
 if(!destList.contains(dest)){
     return false;
 }
 return destList.value(dest)->isActive();
}
/**
 *
 * @param dest Destination SignalMast.
 * @return true if there are no more destination signal masts
 */
/*public*/ bool DefaultSignalMastLogic::removeDestination(SignalMast* dest)
{
 int oldSize = destList.size();
 if(destList.contains(dest))
 {
  //InstanceManager::signalMastLogicManagerInstance().removeDestinationMastToLogic(this, dest);
  destList.value(dest)->dispose();
  destList.remove(dest);
  firePropertyChange("length", QVariant(oldSize), QVariant(destList.size()));
 }
 if (destList.isEmpty())
     return true;
 return false;
}

/*public*/ void DefaultSignalMastLogic::disableLayoutEditorUse()
{
 foreach(DestinationMast* dest, destList.values())
 {
  try {
      dest->useLayoutEditor(false);
  } catch (JmriException e){
      log->error("error" +e.getMessage());
  }
 }
}

/**
* Sets whether this logic should use the details stored in the layout editor
* to determine the which blocks, turnouts will make up the logic between
* the source and destination signal mast->
*
* @param boo Use the layout editor details to determine logic details.
* @param destination Destination SignalMast.
* 
*/
/*public*/ void DefaultSignalMastLogic::useLayoutEditor(bool boo, SignalMast* destination) throw (JmriException)
{
 if(!destList.contains(destination))
 {
  return;
 }
 if (boo)
 {
  log->debug("Set use layout editor");
  QList<LayoutEditor*>* layout =((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
  /*We don't care which layout editor panel the signalmast is on, just so long as
        as the routing is done via layout blocks*/
  log->debug(QString::number(layout->size()));
  for(int i = 0; i<layout->size(); i++)
  {
   if(log->isDebugEnabled())
    log->debug(layout->at(i)->getLayoutName());
   if (facingBlock==nullptr)
   {
    facingBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->
      getFacingBlockByMast(getSourceMast(), layout->at(i));
   }
  }
 }
 try
 {
  destList.value(destination)->useLayoutEditor(boo);
 }
 catch (JmriException e)
 {
  throw e;
 }
}

/**
* Query if we are using the layout editor panels to build the signal mast
* logic, blocks, turnouts .
*
* @param destination Destination SignalMast.
* @return true if we are using the layout editor to build the signal mast logic.
*/
/*public*/ bool DefaultSignalMastLogic::useLayoutEditor(SignalMast* destination)
{
 if(!destList.contains(destination)){
     return false;
 }
 return destList.value(destination)->useLayoutEditor();
}

/**
 * Add direction sensors to SML
 *
 * @return number of errors
 */
//@Override
/*public*/ int DefaultSignalMastLogic::setupDirectionSensors() {
    // iterrate over the signal masts
    int errorCount = 0;
    for (SignalMast* sm : getDestinationList()) {
        QString displayName = sm->getDisplayName();
        Section* sec = getAssociatedSection(sm);
        Block* facingBlock = nullptr;
        if (sec != nullptr) {
            Sensor* fwd = sec->getForwardBlockingSensor();
            Sensor* rev = sec->getReverseBlockingSensor();
            LayoutBlock* lBlock = getFacingBlock();
            if (lBlock == nullptr) {
                try {
                    useLayoutEditor(true, sm); // force a refind
                } catch (JmriException ex) {
                    continue;
                }
            }
            if (lBlock != nullptr) {
                facingBlock = lBlock->getBlock();
                EntryPoint* fwdEntryPoint = sec->getEntryPointFromBlock(facingBlock, Section::FORWARD);
                EntryPoint* revEntryPoint = sec->getEntryPointFromBlock(facingBlock, Section::REVERSE);
                log->debug(tr("Mast[%1] Sec[%2] Fwd[%3] Rev [%4]").arg(
                        displayName).arg(sec->getDisplayName()).arg(fwd?fwd->getDisplayName():"null").arg(rev?rev->getDisplayName():"null"));
                if (fwd != nullptr && fwdEntryPoint != nullptr) {
                    addSensor(fwd->getUserName(), Sensor::INACTIVE, sm);
                    log->debug(tr("Mast[%1] Sec[%2] Fwd[%3] fwdEP[%4] revEP[%5]").arg(
                            displayName).arg(sec->getDisplayName()).arg(fwd->getDisplayName()).arg(
                            fwdEntryPoint->getBlock()->getUserName()));

                } else if (rev != nullptr && revEntryPoint != nullptr) {
                    addSensor(rev->getUserName(), Sensor::INACTIVE, sm);
                    log->debug(tr("Mast[%1] Sec[%2] Rev [%3] fwdEP[%4] revEP[%5]").arg(
                            displayName).arg(sec->getDisplayName()).arg(fwd->getDisplayName()).arg(rev->getDisplayName()).arg(
                            revEntryPoint->getBlock()->getUserName()));

                } else {
                    log->error(tr("Mast[%1] Cannot Establish entry point to protected section").arg(displayName));
                    errorCount += 1;
                }
            } else {
                log->error(tr("Mast[%1] No Facing Block").arg(displayName));
                errorCount += 1;
            }
        } else {
            log->error(tr("Mast[%1] No Associated Section").arg(displayName));
            errorCount += 1;
        }
    }
    return errorCount;
}

//@Override
/*public*/ void DefaultSignalMastLogic::removeDirectionSensors() {
    //TODO find aaway of easilty identifying the ones we added.
    return ;
}

/**
* Sets whether we should use the information from the layout editor for either
* blocks or turnouts.
*
* @param destination Destination SignalMast.
* @param blocks set false if not to use the block information gathered from the layouteditor
* @param turnouts set false if not to use the turnout information gathered from the layouteditor
*/
/*public*/ void DefaultSignalMastLogic::useLayoutEditorDetails(bool turnouts, bool blocks, SignalMast* destination) throw (JmriException)
{
 if(!destList.contains(destination)){
     return;
 }
 try {
     destList.value(destination)->useLayoutEditorDetails(turnouts, blocks);
 } catch (JmriException e){
     throw e;
 }
}

/**
* Query if we are using the layout editor turnout information in the 
* signal mast logic.
*
* @param destination Destination SignalMast.
* @return true if we are using the turnout information from the layout editor.
*/
/*public*/ bool DefaultSignalMastLogic::useLayoutEditorTurnouts(SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->useLayoutEditorTurnouts();
}

/**
* Query if we are using the layout editor block information in the 
* signal mast logic.
*
* @param destination Destination SignalMast.
* @return true if we are using the block information from the layout editor.
*/    
/*public*/ bool DefaultSignalMastLogic::useLayoutEditorBlocks(SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->useLayoutEditorBlocks();
}

/*public*/ Section* DefaultSignalMastLogic::getAssociatedSection(SignalMast* destination) {
//    if (!destList.contains(destination)) {
//        return nullptr;
//    }
 foreach(SignalMast* m, destList.keys()) {
  if(m->equals(destination))
   return destList.value(m)->getAssociatedSection();
 }
 return nullptr;
}


/*public*/ void DefaultSignalMastLogic::setAssociatedSection(Section* sec, SignalMast* destination) {
//    if (!destList.contains(destination)) {
//        return;
//    }
//    destList.value(destination)->setAssociatedSection(sec);
 foreach (SignalMast* m, destList.keys()) {
  if(m->equals(destination))
   destList.value(m)->setAssociatedSection(sec);
 }
}

/**
* Query if we are allowing the system to automatically generated a list of
* conflicting SignalMast* that have a direct effect on our logic.
*
* @param destination Destination SignalMast.
* @return true if this is allowed.
*/
/*public*/ bool DefaultSignalMastLogic::allowAutoMaticSignalMastGeneration(SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->allowAutoSignalMastGen();
}

/**
* Sets whether we should allow the system to automatically generate a list of
* signal masts that could cause a conflicting route.
*
* @param destination Destination SignalMast.
* @param allow set true if we are to allow automatic generation.
*/
/*public*/ void DefaultSignalMastLogic::allowAutoMaticSignalMastGeneration(bool allow, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->allowAutoSignalMastGen(allow);
}

/**
* Sets whether we should lock all turnouts between the source and destination
* signal masts when the logic goes active, to prevent them from being changed.
* This is dependant upon the hardware allowing for this->
*
* @param destination Destination SignalMast.
* @param lock set true if the system should lock the turnout.
*/    
/*public*/ void DefaultSignalMastLogic::allowTurnoutLock(bool lock, SignalMast* destination)
{
 if(!destList.contains(destination)){
     return;
 }
 destList.value(destination)->allowTurnoutLock(lock);
}

/**
* Query if we are allowing the system to lock turnouts when the logic goes 
* active.
*
* @param destination Destination SignalMast.
* @return true if locking is allowed.
*/

/*public*/ bool DefaultSignalMastLogic::isTurnoutLockAllowed(SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->isTurnoutLockAllowed();
}

/**
 * Sets the states that each turnout must be in for signal not to be set at a stop aspect
 * @param turnouts
 */
/*public*/ void DefaultSignalMastLogic::setTurnouts(QHash<NamedBeanHandle<Turnout*>*, int> turnouts, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->setTurnouts(turnouts);
}

    /**
 * Sets which blocks must be inactive for the signal not to be set at a stop aspect
 * These Turnouts are not stored in the panel file.
 */
/*public*/ void DefaultSignalMastLogic::setAutoTurnouts(QHash<Turnout*, int> turnouts, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->setAutoTurnouts(turnouts);
}

/**
 * Sets which blocks must be inactive for the signal not to be set at a stop aspect
 * @param blocks
 */
/*public*/ void DefaultSignalMastLogic::setBlocks(QHash<Block*, int> blocks, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->setBlocks(blocks);
}

/**
 * Sets which blocks must be inactive for the signal not to be set at a stop aspect
 * These blocks are not stored in the panel file.
 * @param blocks
 */
///*public*/ void setLayoutBlocks
/*public*/ void DefaultSignalMastLogic::setAutoBlocks(QMap<Block*, int> blocks, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->setAutoBlocks(blocks);
}

/**
 * Sets which masts must be in a given state before our mast can be set.
 * @param masts
 */
/*public*/ void DefaultSignalMastLogic::setMasts(QHash<SignalMast*, QString> masts, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->setMasts(masts);
}

/**
 * Sets which masts must be in a given state before our mast can be set.
 * These masts are not stored in the panel file.
 * @param masts
 */
/*public*/ void DefaultSignalMastLogic::setAutoMasts(QHash<SignalMast*, QString>* masts, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->setAutoMasts(masts, true);
}

/**
 * Sets which sensors must be in a given state before our mast can be set.
 * @param sensors
 */
/*public*/ void DefaultSignalMastLogic::setSensors(QHash<NamedBeanHandle<Sensor*>*, int> sensors, SignalMast* destination){
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->setSensors(sensors);
}

/*public*/ void DefaultSignalMastLogic::addSensor(QString sensorName, int state, SignalMast* destination)
{
 if(!destList.contains(destination))
  return;
 Sensor* sen = ((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sensorName);
 if(sen!=nullptr)
 {
  NamedBeanHandle<Sensor*>* namedSensor = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sen);
        destList.value(destination)->addSensor(namedSensor, state);
    }
}

/*public*/ void DefaultSignalMastLogic::removeSensor(QString sensorName, SignalMast* destination){
    if(!destList.contains(destination))
        return;
    Sensor* sen = ((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sensorName);
    if(sen!=nullptr){
        NamedBeanHandle<Sensor*>* namedSensor = ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sen);
        destList.value(destination)->removeSensor(namedSensor);
    }
}

/*public*/ QList<Block*> DefaultSignalMastLogic::getBlocks(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<Block*>();
    }
    return destList.value(destination)->getBlocks();
}

/*public*/ QList<Block*> DefaultSignalMastLogic::getAutoBlocks(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<Block*>();
    }
    return destList.value(destination)->getAutoBlocks();
}

/*public*/ QList<Block*> DefaultSignalMastLogic::getAutoBlocksBetweenMasts(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<Block*>();
    }
    if(destList.value(destination)->xingAutoBlocks.size()==0){
        return destList.value(destination)->getAutoBlocks();
    }
    QList<Block*> returnList = destList.value(destination)->getAutoBlocks();
    log->info("before " + QString::number(returnList.size()));
    foreach(Block* blk, destList.value(destination)->getAutoBlocks())
    {
        if(destList.value(destination)->xingAutoBlocks.contains(blk)){
            returnList.removeAt(returnList.indexOf(blk));
        }
    }
    log->info("After " + returnList.size());
    return returnList;

}

/*public*/ QList<Turnout*> DefaultSignalMastLogic::getTurnouts(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<Turnout*>();
    }
    return destList.value(destination)->getTurnouts();
}

/*public*/ QList<NamedBeanHandle<Turnout*>* > DefaultSignalMastLogic::getNamedTurnouts(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<NamedBeanHandle<Turnout*>*>();
    }
    return destList.value(destination)->getNamedTurnouts();
}

/*public*/ QList<Turnout*> DefaultSignalMastLogic::getAutoTurnouts(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<Turnout*>();
    }
    return destList.value(destination)->getAutoTurnouts();
}

/*public*/ QList<Sensor*> DefaultSignalMastLogic::getSensors(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<Sensor*>();
    }
    return destList.value(destination)->getSensors();
}

/*public*/ QList<NamedBeanHandle<Sensor*>* > DefaultSignalMastLogic::getNamedSensors(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<NamedBeanHandle<Sensor*>* >();
    }
    return destList.value(destination)->getNamedSensors();
}

/*public*/ QList<SignalMast*> DefaultSignalMastLogic::getSignalMasts(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<SignalMast*>();
    }
    return destList.value(destination)->getSignalMasts();
}

/*public*/ QList<SignalMast*> DefaultSignalMastLogic::getAutoMasts(SignalMast* destination){
    if(!destList.contains(destination)){
        return  QList<SignalMast*>();
    }
    return destList.value(destination)->getAutoSignalMasts();
}

/*general method to initialise all*/
/*public*/ void DefaultSignalMastLogic::initialise(){
    //Enumeration<SignalMast*> en = destList.keys();
    QListIterator<SignalMast*> en(destList.keys());
    while (en.hasNext()) {
        destList.value(en.next())->initialise();
    }
}
/**
 * Initialise the signalmast after all the parameters have been set.
 */
/*public*/ void DefaultSignalMastLogic::initialise(SignalMast* destination){
    if (disposing) return;
    
    if(!destList.contains(destination)){
        return;
    }
    destList.value(destination)->initialise();
}
//@Override
/*public*/ QMap<Block*, int> DefaultSignalMastLogic::setupLayoutEditorTurnoutDetails(QList<LayoutBlock*> blks, SignalMast* destination) {
    if (disposing) {
        return QMap<Block*, int>();
    }

    if (!destList.contains(destination)) {
     return QMap<Block*, int>();
    }
    return destList.value(destination)->setupLayoutEditorTurnoutDetails(blks);
}

/*public*/ void DefaultSignalMastLogic::setupLayoutEditorDetails(){
    if(disposing) return;
    
    QListIterator<SignalMast*> en(destList.keys());
    while (en.hasNext()) {
        try{
            destList.value(en.next())->setupLayoutEditorDetails();
        } catch (JmriException e){
            //Considered normal if no route is valid on the layout editor
        }
    }
}


/**
 *
 * @return true if the path to the next signal is clear
 */
bool DefaultSignalMastLogic::checkStates(){
    SignalMast* oldActiveMast = destination;
    if (destination!=nullptr){
        firePropertyChange("state", VPtr<SignalMast>::asQVariant(oldActiveMast), QVariant());
        log->debug("Remove listener from destination");
        destination->removePropertyChangeListener(propertyDestinationMastListener);
        if(destList.contains(destination))
            destList.value(destination)->clearTurnoutLock();
    }
    
    QListIterator<SignalMast*> en ( destList.keys());
    while (en.hasNext()) {
        SignalMast* key = en.next();
        if(log->isDebugEnabled()){
            log->debug("Enabled " + (destList.value(key))->isEnabled());
            log->debug("Active " + destList.value(key)->isActive());
        }
        if ((destList.value(key))->isEnabled()&&(destList.value(key)->isActive())){
           destination = key;
           if(log->isDebugEnabled())
            log->debug("destination mast " + key->getDisplayName() + " Add listener to destination");
           destination->addPropertyChangeListener(propertyDestinationMastListener);
           connect(destination->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyDestinationMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
           firePropertyChange("state", VPtr<SignalMast>::asQVariant(oldActiveMast), VPtr<SignalMast>::asQVariant(destination));
           destList.value(key)->lockTurnouts();
           return true;
        }
    }
    return false;
}
/**
* Returns true if any of the blocks in the supplied list are included in any
* of the logics that set this signal.
*/
/*public*/ bool DefaultSignalMastLogic::areBlocksIncluded(QList<Block*> blks){
    QListIterator<SignalMast*> en(destList.keys());
    while (en.hasNext()) {
        SignalMast* dm = en.next();
        bool included = false;
        for(int i=0; i<blks.size(); i++){
            included = destList.value(dm)->isBlockIncluded(blks.at(i));
            if(included){
                return true;
            }
            destList.value(dm)->isAutoBlockIncluded(blks.at(i));
            if(included){
                return true;
            }
        }
    }
    return false;
}

/*public*/ int DefaultSignalMastLogic::getBlockState(Block* block, SignalMast* destination){
    if(!destList.contains(destination)){
        return -1;
    }
    return destList.value(destination)->getBlockState(block);
}

/*public*/ bool DefaultSignalMastLogic::isBlockIncluded(Block* block, SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->isBlockIncluded(block);
}

/*public*/ bool DefaultSignalMastLogic::isTurnoutIncluded(Turnout* turnout, SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->isTurnoutIncluded(turnout);
}

/*public*/ bool DefaultSignalMastLogic::isSensorIncluded(Sensor* sensor, SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->isSensorIncluded(sensor);
}

/*public*/ bool DefaultSignalMastLogic::isSignalMastIncluded(SignalMast* signal, SignalMast* destination){
    if(!destList.contains(destination)){
        return false;
    }
    return destList.value(destination)->isSignalMastIncluded(signal);
}

/*public*/ int DefaultSignalMastLogic::getAutoBlockState(Block* block, SignalMast* destination){
    if(!destList.contains(destination)){
        return -1;
    }
    return destList.value(destination)->getAutoBlockState(block);
}

/*public*/ int DefaultSignalMastLogic::getSensorState(Sensor* sensor, SignalMast* destination){
    if(!destList.contains(destination)){
        return -1;
    }
    return destList.value(destination)->getSensorState(sensor);
}

/*public*/ int DefaultSignalMastLogic::getTurnoutState(Turnout* turnout, SignalMast* destination){
    if(!destList.contains(destination)){
        return -1;
    }
    return destList.value(destination)->getTurnoutState(turnout);
}

/*public*/ int DefaultSignalMastLogic::getAutoTurnoutState(Turnout* turnout, SignalMast* destination){
    if(!destList.contains(destination)){
        return -1;
    }
    return destList.value(destination)->getAutoTurnoutState(turnout);
}

/*public*/ QString DefaultSignalMastLogic::getSignalMastState(SignalMast* mast, SignalMast* destination){
    if(!destList.contains(destination)){
        return nullptr;
    }
    return destList.value(destination)->getSignalMastState(mast);
}

/*public*/ QString DefaultSignalMastLogic::getAutoSignalMastState(SignalMast* mast, SignalMast* destination){
    if(!destList.contains(destination)){
        return nullptr;
    }
    return destList.value(destination)->getAutoSignalMastState(mast);
}

/*public*/ float DefaultSignalMastLogic::getMaximumSpeed(SignalMast* destination){
    if(!destList.contains(destination)){
        return -1;
    }
    return destList.value(destination)->getMinimumSpeed();
}


/* 
 * Before going active or checking that we can go active, we will wait 500ms
 * for things to settle down to help prevent a race condition
 */
/*synchronized*/ void DefaultSignalMastLogic::setSignalAppearance()
{
    QMutexLocker locker(&mutex);
    log->debug("In appearance called " + source->getDisplayName());
    if (inWait){
        log->debug("In wait for set appearance");
        return;
    }
    inWait=true;
    
//    Runnable* r = new Runnable() {
//        /*public*/ void run() {
//            try {
//                Thread.sleep((InstanceManager::signalMastLogicManagerInstance().getSignalLogicDelay()/2));
//                inWait=false;
//                setMastAppearance();
//            } catch (InterruptedException ex) {
//                Thread.currentThread().interrupt();
//                inWait=false;
//            }
//        }
//    };
    RunnableThis* r = new RunnableThis(this);
    
    thr = new QThread(r);
    thr->setObjectName(getSourceMast()->getDisplayName());
//    try{
        thr->start();
//    } catch (IllegalThreadStateException ex){
//        log->error("In Setting Signal Mast Appearance " + ex.at());
//    }
}

/**
 * Evaluates the destination signal mast appearance and sets ours accordingly
 */
void DefaultSignalMastLogic::setMastAppearance()
{
    //synchronized(this){
    QMutexLocker locker(&mutex);
        if(inWait){
            log->error("Set SignalMast* Appearance called while still in wait");
            return;
        }
//    }
    log->debug("Set Signal Appearances");
    if(getSourceMast()->getHeld()){
        log->debug("Signal is at a held state so will set to the aspect defined for held or danger");
        if(getSourceMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::HELD)!=nullptr)
        {
            getSourceMast()->setAspect(getSourceMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::HELD));
        } else {
            getSourceMast()->setAspect(getSourceMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER));
        }
        return;
    }
    if (!checkStates()){
        log->debug("advanced routes not clear");
        getSourceMast()->setAspect(stopAspect);
        return;
    }
    QVector<QString> advancedAspect;
    if(destination->getHeld()){
        if(destination->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::HELD)!=nullptr){
            advancedAspect = getSourceMast()->getAppearanceMap()->getValidAspectsForAdvancedAspect(destination->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::HELD));
        } else {
            advancedAspect = getSourceMast()->getAppearanceMap()->getValidAspectsForAdvancedAspect(destination->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER));
        }
    } else {
        advancedAspect = getSourceMast()->getAppearanceMap()->getValidAspectsForAdvancedAspect(destination->getAspect());
    }

    if(log->isDebugEnabled())
        log->debug("distant aspect is " + destination->getAspect());

    if (!advancedAspect.isEmpty())
    {
        QString aspect = stopAspect;
        if(destList.value(destination)->permissiveBlock) {
            //if a block is in a permissive state then we set the permissive appearance
            aspect = getSourceMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::PERMISSIVE);
        } else {
            for(int i = 0; i<advancedAspect.count(); i++){
                if(!getSourceMast()->isAspectDisabled(advancedAspect.at(i))){
                    aspect = advancedAspect.at(i);
                    break;
                }
            }
            QList<int> divergAspects =  QList<int>();
            QList<int> nonDivergAspects =  QList<int>();
            QList<int> eitherAspects =  QList<int>();
            if (advancedAspect.count()>1) {
                float maxSigSpeed = -1;
                float maxPathSpeed = destList.value(destination)->getMinimumSpeed();
                bool divergRoute = destList.value(destination)->turnoutThrown;
                
                log->debug("Diverging route? " + divergRoute);
                bool divergFlagsAvailable = false;
                    //We split the aspects into two lists, one with divering flag set, the other without.
                for(int i = 0; i<advancedAspect.count(); i++){
                    QString div = nullptr;
                    if(!getSourceMast()->isAspectDisabled(advancedAspect.at(i))){
                        div =  getSourceMast()->getSignalSystem()->getProperty(advancedAspect.at(i), "route").toString();
                    }
                    if(div!=nullptr){
                        if (div==("Diverging")){
                            log->debug("Aspect " + advancedAspect.at(i) + "added as Diverging Route");
                            divergAspects.append(i);
                            divergFlagsAvailable = true;
                            log->debug("Using Diverging Flag");
                        } else if (div==("Either")) {
                            log->debug("Aspect " + advancedAspect.at(i) + "added as Both Diverging and Normal Route");
                            nonDivergAspects.append(i);
                            divergAspects.append(i);
                            divergFlagsAvailable = true;
                            eitherAspects.append(i);
                            log->debug("Using Diverging Flag");
                        } else {
                            log->debug("Aspect " + advancedAspect.at(i) + "added as Normal Route");
                            nonDivergAspects.append(i);
                            log->debug("Aspect " + advancedAspect.at(i) + "added as Normal Route");
                        }
                    } else {
                        nonDivergAspects.append(i);
                        log->debug("Aspect " + advancedAspect.at(i) + "added as Normal Route");
                    }
                }
                if((eitherAspects==(divergAspects)) && (divergAspects.size()<nonDivergAspects.size())){
                    //There are no unique diverging aspects 
                    log->debug("'Either' aspects equals divergAspects and is less than non-diverging aspects");
                    divergFlagsAvailable = false;
                }
                log->debug("path max speed : " + QString::number(maxPathSpeed));
                for (int i = 0; i<advancedAspect.count(); i++){
                    if(!getSourceMast()->isAspectDisabled(advancedAspect.at(i))){
                        QString strSpeed = getSourceMast()->getSignalSystem()->getProperty(advancedAspect.at(i), "speed").toString();
                        if(log->isDebugEnabled())
                            log->debug("Aspect Speed = " + strSpeed + " for aspect " + advancedAspect.at(i));
                        /*  if the diverg flags available is set and the diverg aspect 
                            array contains the entry then we will check this aspect.
                            
                            If the diverg flag has not been set then we will check.
                        */
                        log->debug(advancedAspect.at(i));
                        if((divergRoute && (divergFlagsAvailable) && (divergAspects.contains(i))) || ((divergRoute && (!divergFlagsAvailable))||(!divergRoute)) && (nonDivergAspects.contains(i))){
                            log->debug("In list");
                            if (strSpeed!="")
                            {
                                float speed = 0.0f;
                                try {
                                    speed =  (strSpeed.toFloat());
                                }catch (NumberFormatException nx) {
                                    try{
                                        speed = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(strSpeed);
                                    } catch (Exception ex){
                                        //Considered Normal if the speed does not appear in the map
                                    }
                                }
                                //Integer state = Integer.parseInt(strSpeed);
                                /* This pics out either the highest speed signal if there
                                 * is no block speed specified or the highest speed signal
                                 * that is under the minimum block speed.
                                 */
                                if(log->isDebugEnabled())
                                    log->debug(destination->getDisplayName() + " signal state speed " + QString::number(speed) + " maxSigSpeed " + QString::number(maxSigSpeed) + " max Path Speed " + QString::number(maxPathSpeed));
                                if(maxPathSpeed==0){
                                    if (maxSigSpeed ==-1){
                                        log->debug("min speed on this route is equal to 0 so will set this as our max speed");
                                        maxSigSpeed=speed;
                                        aspect = advancedAspect.at(i);
                                        log->debug("Aspect to set is " + aspect);
                                    } else if (speed > maxSigSpeed){
                                        log->debug("new speed is faster than old will use this");
                                        maxSigSpeed=speed;
                                        aspect = advancedAspect.at(i);
                                        log->debug("Aspect to set is " + aspect);
                                    }
                                }
                                else if ((speed>maxSigSpeed) && (maxSigSpeed<maxPathSpeed) && (speed<=maxPathSpeed)){
                                    //Only set the speed to the lowest if the max speed is greater than the path speed
                                    //and the new speed is less than the last max speed
                                    log->debug("our minimum speed on this route is less than our state speed, we will set this as our max speed");
                                    maxSigSpeed = speed;
                                    aspect = advancedAspect.at(i);
                                    log->debug("Aspect to set is " + aspect);
                                } else if ((maxSigSpeed>maxPathSpeed) && (speed<maxSigSpeed)){
                                    log->debug("our max signal speed is greater than our path speed on this route, our speed is less that the maxSigSpeed");
                                    maxSigSpeed = speed;
                                    aspect = advancedAspect.at(i);
                                    log->debug("Aspect to set is " + aspect);
                                
                                } else if (maxSigSpeed == -1){
                                    log->debug("maxSigSpeed returned as -1");
                                    maxSigSpeed = speed;
                                    aspect = advancedAspect.at(i);
                                    log->debug("Aspect to set is " + aspect);
                                }
                            }
                        }
                    } else if(log->isDebugEnabled()){
                        log->debug("Aspect has been disabled " + advancedAspect.at(i));
                    }
                }
            }
        }
        if ( (aspect!=(""))){
            log->debug("set mast aspect called from set appearance");
            getSourceMast()->setAspect(aspect);
            return;
        }
    }
    log->debug("aspect returned is not valid");
    getSourceMast()->setAspect(stopAspect);
}
#if 1
/*public*/ void DefaultSignalMastLogic::setConflictingLogic(SignalMast* sm, LevelXing* lx){
    if(sm==nullptr)
        return;
    if(log->isDebugEnabled())
        log->debug("setConflicting logic mast " + sm->getDisplayName());
    if(sm==source){
        log->debug("source is us so exit");
        return;
    }
    QListIterator<SignalMast*> en(destList.keys());
    while (en.hasNext()) {
        SignalMast* dm = en.next();
        if(destList.value(dm)->isBlockIncluded(lx->getLayoutBlockAC()))
            destList.value(dm)->addAutoSignalMast(sm);
        else if (destList.value(dm)->isBlockIncluded(lx->getLayoutBlockBD()))
            destList.value(dm)->addAutoSignalMast(sm);
        else if(destList.value(dm)->isAutoBlockIncluded(lx->getLayoutBlockAC()))
            destList.value(dm)->addAutoSignalMast(sm);
        else if (destList.value(dm)->isAutoBlockIncluded(lx->getLayoutBlockBD()))
            destList.value(dm)->addAutoSignalMast(sm);
        else
            log->debug("Block not found");
    }
}

/*public*/ void DefaultSignalMastLogic::removeConflictingLogic(SignalMast* sm, LevelXing* lx){
    if(sm==source)
        return;
    
    QListIterator<SignalMast*> en(destList.keys());
    while (en.hasNext()) {
        SignalMast* dm = en.next();
        if(destList.value(dm)->isBlockIncluded(lx->getLayoutBlockAC()))
            destList.value(dm)->removeAutoSignalMast(sm);
        else if (destList.value(dm)->isBlockIncluded(lx->getLayoutBlockBD()))
            destList.value(dm)->removeAutoSignalMast(sm);
    }
}
#endif
//class DestinationMast{

    
DestinationMast::DestinationMast(SignalMast* destination, DefaultSignalMastLogic* dsml)
{
 this->destination=destination;
 this->dsml = dsml;
 userSetTurnouts =  QList<NamedBeanSetting*>();
 autoTurnouts =  QHash<Turnout*, int>();
 userSetMasts =  QList<NamedBeanSetting*>();
 autoMasts =  new QHash<SignalMast*, QString>();
 userSetSensors =  QList<NamedBeanSetting*>();
 userSetBlocks =  QList<NamedBeanSetting*>();
 turnoutThrown = false;
 permissiveBlock = false;
 disposed = false;
 autoBlocks = QMap<Block*, int>();

 xingAutoBlocks =  QList<Block*>();
 dblCrossoverAutoBlocks = QList<Block*>();

 active = false;
 destMastInit = false;

 minimumBlockSpeed = 0.0;

 _useLayoutEditor = false;
 _useLayoutEditorTurnouts = false;
 _useLayoutEditorBlocks = false;
 _lockTurnouts = false;
 blockInXings =  QList<LevelXing*>();
 enable = true;
 store = SignalMastLogic::STOREALL;
 inWait = false;
 thr = nullptr;
 allowAutoSignalMastGeneration = false;
 destinationBlock = nullptr;
 userSetTurnouts =  QList<NamedBeanSetting*>();
 autoTurnouts =  QHash<Turnout*, int>();
 userSetMasts =  QList<NamedBeanSetting*>();
 autoMasts =  new QHash<SignalMast*, QString>();
 userSetSensors =  QList<NamedBeanSetting*>();
 userSetBlocks =  QList<NamedBeanSetting*>();
 turnoutThrown = false;
 permissiveBlock = false;
 disposed = false;

 blockInXings =  QList<LevelXing*>();

 propertySensorListener = new PropertySensorListener(this) ;
 propertyTurnoutListener = new PropertyTurnoutListener(this) ;
 propertyBlockListener = new PropertyBlockListener(this);
 propertySignalMastListener = new PropertySignalMastListener(this) ;
 log = new Logger("DestinationMast");
 store = SignalMastLogic::STOREALL;
 allowAutoSignalMastGeneration = false;

 if(((AbstractSignalMast*)destination)->getAspect()==nullptr)
   ((AbstractSignalMast*)destination)->setAspect(((DefaultSignalAppearanceMap*)((AbstractSignalMast*)destination)->getAppearanceMap())->getSpecificAppearance(SignalAppearanceMap::DANGER));
 associatedSection = nullptr;
 _useLayoutEditor = false;
 _useLayoutEditorTurnouts = false;
 _useLayoutEditorBlocks = false;
 _lockTurnouts = false;

}
    
void DestinationMast::updateDestinationMast(SignalMast* newMast)
{
 destination=newMast;
 if(destination->getAspect()==nullptr)
     ((AbstractSignalMast*)destination)->setAspect(destination->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER));
}
    
LayoutBlock* DestinationMast::getProtectingBlock(){
    return protectingBlock;
}
    
QString DestinationMast::getDisplayName() {
    return destination->getDisplayName();
}

QString DestinationMast::getComment(){
    return comment;
}

void DestinationMast::setComment(QString comment){
    QString old = this->comment;
    this->comment=comment;
    dsml->firePropertyChange("Comment",QVariant(old), QVariant(comment));
}

bool DestinationMast::isActive(){
    if(disposed){
        log->error("checkState called even though this has been disposed of");
        return false;
    }
    return active;
}

float DestinationMast::getMinimumSpeed(){
    return minimumBlockSpeed;
}


void DestinationMast::setEnabled() {
    enable=true;
    dsml->firePropertyChange("Enabled", QVariant(false), VPtr<SignalMast>::asQVariant(this->destination));
}

void DestinationMast::setDisabled() {
    enable=false;
    dsml->firePropertyChange("Enabled", QVariant(true), VPtr<SignalMast>::asQVariant(this->destination));
}

bool DestinationMast::isEnabled() { return enable; }


/**
 * Use this to determine if the signalmast logic is stored in the panel file
 * and if all the information is stored.
 * @param store
 */

void DestinationMast::setStore(int store){
    this->store=store;
}

int DestinationMast::getStoreState(){
    return store;
}

void DestinationMast::setAssociatedSection(Section* section)
{
    if (section != nullptr && (!_useLayoutEditor || !_useLayoutEditorBlocks)) {
        log->warn("This Logic " + dsml->source->getDisplayName() + " to " + destination->getDisplayName() + " is not using the layout editor or its blocks, the associated section will not be populated correctly");
    }
    if (section == nullptr) {
        associatedSection = nullptr;
        return;
    }
    associatedSection = ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(section->getDisplayName(), section);
    if (!autoBlocks.isEmpty() && associatedSection != nullptr) {
        createSectionDetails();
    }
}

Section* DestinationMast::getAssociatedSection() {
    if (associatedSection != nullptr) {
        return associatedSection->getBean();
    }
    return nullptr;
}

void DestinationMast::createSectionDetails() {
    getAssociatedSection()->removeAllBlocksFromSection();
    foreach (Block* key, getAutoBlocksBetweenMasts()) {
        getAssociatedSection()->addBlock(key);
    }
    QString dir = Path::decodeDirection(dsml->getFacingBlock()->getNeighbourDirection(getProtectingBlock()));
    EntryPoint* ep = new EntryPoint(getProtectingBlock()->getBlock(), dsml->getFacingBlock()->getBlock(), dir);
    ep->setTypeForward();
    getAssociatedSection()->addToForwardList(ep);

    LayoutBlock* proDestLBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getProtectedBlockByNamedBean(destination, destinationBlock->getMaxConnectedPanel());
    if (proDestLBlock != nullptr) {
        if (log->isDebugEnabled()) {
            log->debug("Add protecting Block " + proDestLBlock->getDisplayName());
        }
        dir = Path::decodeDirection(proDestLBlock->getNeighbourDirection(destinationBlock));
        ep = new EntryPoint(destinationBlock->getBlock(), proDestLBlock->getBlock(), dir);
        ep->setTypeReverse();
        getAssociatedSection()->addToReverseList(ep);
    } else if (log->isDebugEnabled()) {
        log->debug(" ### Protecting Block not found ### ");
    }
}

bool DestinationMast::isTurnoutLockAllowed() { return _lockTurnouts; }

void DestinationMast::allowTurnoutLock(bool lock)
{
 if(_lockTurnouts==lock)
     return;
 if(!lock)
     clearTurnoutLock();
 _lockTurnouts = lock;
}

void DestinationMast::setTurnouts(QHash<NamedBeanHandle<Turnout*>*, int> turnouts)
{
 if (!this->userSetTurnouts.isEmpty())
 {
  foreach(NamedBeanSetting* nbh, userSetTurnouts)
  {
   nbh->getBean()->removePropertyChangeListener(propertyTurnoutListener);
  }
 }
 destMastInit = false;
 if(turnouts.isEmpty()){
     userSetTurnouts =  QList<NamedBeanSetting*>();
 }
 else
 {
  QListIterator<NamedBeanHandle<Turnout*>* > e(turnouts.keys());
  while(e.hasNext())
  {
      NamedBeanHandle<Turnout*>* nbh = e.next();
      NamedBeanSetting* nbs = new NamedBeanSetting((NamedBeanHandle<NamedBean*>*)nbh, turnouts.value(nbh));
      userSetTurnouts.append(nbs);
  }
 }
 dsml->firePropertyChange("turnouts", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

    /*void setTurnoutThroats(QHash<Turnout, Boolean> turnouts){
            if(this->turnoutThroats!=nullptr){
            Enumeration<Turnout> keys = this->turnouts.keys();
            while ( keys.hasNext() )
            {
               Turnout key = keys.next();
               key->removePropertyChangeListener(propertyTurnoutListener);
            }
        }
        destMastInit = false;
        if(turnouts==nullptr){
            this->turnoutThroats = new QHash<Turnout, Boolean>(0);
        } else {
            this->turnoutThroats=turnouts;
        }
        firePropertyChange("turnouts", nullptr, this->destination);
    }*/

    /*void setAutoTurnoutThroats(QHash<Turnout, Boolean> turnouts){
            if(this->turnoutThroats!=nullptr){
            Enumeration<Turnout> keys = this->turnouts.keys();
            while ( keys.hasNext() )
            {
               Turnout key = keys.next();
               key->removePropertyChangeListener(propertyTurnoutListener);
            }
        }
        destMastInit = false;
        if(turnouts==nullptr){
            this->autoTurnoutThroats = new QHash<Turnout, Boolean>(0);
        } else {
            this->autoTurnoutThroats=turnouts;
        }
        firePropertyChange("turnouts", nullptr, this->destination);
    }*/
    
/**
 * Sets which blocks must be inactive for the signal not to be set at a stop aspect
 */
void DestinationMast::setAutoTurnouts(QHash<Turnout*, int> turnouts){
    log->debug(destination->getDisplayName() + " setAutoTurnouts Called");
    if (!this->autoTurnouts.isEmpty()){
        QListIterator<Turnout*> keys(this->autoTurnouts.keys());
        while ( keys.hasNext() )
        {
           Turnout* key = keys.next();
           key->removePropertyChangeListener(propertyTurnoutListener);
        }
        //minimumBlockSpeed = 0;
    }
    destMastInit = false;
    if(turnouts.isEmpty()){
        this->autoTurnouts =  QHash<Turnout*, int>();
    } else {
        this->autoTurnouts=turnouts;
    }
    dsml->firePropertyChange("autoturnouts", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

/**
 * Sets which blocks must be inactive for the signal not to be set at a stop aspect
 * @param blocks
 */
void DestinationMast::setBlocks(QHash<Block*, int> blocks){
    log->debug(destination->getDisplayName() + " Set blocks called");
    if (!this->userSetBlocks.isEmpty()){
        foreach(NamedBeanSetting* nbh, userSetBlocks){
            nbh->getBean()->removePropertyChangeListener(propertyBlockListener);
        }
    }
    destMastInit = false;

    if(blocks.isEmpty()){
        userSetBlocks =  QList<NamedBeanSetting*>();
    } else {
        QListIterator<Block*> e(blocks.keys());
        while(e.hasNext()){
            Block* blk = e.next();
            NamedBeanHandle<NamedBean*>* nbh = ( NamedBeanHandle<NamedBean*>*)(NamedBeanHandle<Block*>*) ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(blk->getDisplayName(), blk);
            NamedBeanSetting* nbs = new NamedBeanSetting(nbh, blocks.value(blk));
            userSetBlocks.append(nbs);
        }
    }
    dsml->firePropertyChange("blocks", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

/**
 * Sets which blocks must be inactive for the signal not to be set at a stop aspect
 * @param blocks
 */
///*public*/ void DestinationMast::setLayoutBlocks
/*public*/ void DestinationMast::setAutoBlocks(QMap<Block*, int> blocks){
    if(log->isDebugEnabled())
        log->debug(destination->getDisplayName() + " setAutoBlocks Called");
    if (!this->autoBlocks.isEmpty())
    {
        QList<Block*> blockKeys = autoBlocks.keys();
        //while ( blockKeys.hasNext() )
        foreach(Block* key, blockKeys)
        {
       //Block key = blockKeys.next();
            key->removePropertyChangeListener(propertyBlockListener);
        }
        //minimumBlockSpeed = 0;
    }
    destMastInit = false;
    if (blocks.isEmpty())
    {
        this->autoBlocks=  QMap<Block*, int>();
    } else {
        this->autoBlocks=blocks;
        //We shall remove the facing block in the list.
        if(dsml->facingBlock!=nullptr){
            if(autoBlocks.contains(dsml->facingBlock->getBlock())){
                autoBlocks.remove(dsml->facingBlock->getBlock());
            }
        }
    }

    log->debug(QString::number(autoBlocks.size()));
    dsml->firePropertyChange("autoblocks", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

/**
 * Sets which masts must be in a given state before our mast can be set.
 * @param masts
 */
void DestinationMast::setMasts(QHash<SignalMast*, QString> masts){
    if (!this->userSetMasts.isEmpty()){
        foreach(NamedBeanSetting* nbh, userSetMasts){
            nbh->getBean()->removePropertyChangeListener(propertySignalMastListener);
        }
    }

    destMastInit = false;

    if(masts.isEmpty()){
        userSetMasts =  QList<NamedBeanSetting*>();
    } else {
        QListIterator<SignalMast*> e (masts.keys());
        while(e.hasNext()){
            SignalMast* mast = e.next();
            NamedBeanHandle<SignalMast*> * nbh = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(mast->getDisplayName(), mast);
            NamedBeanSetting* nbs = new NamedBeanSetting((NamedBeanHandle<NamedBean*>*)nbh, masts.value(mast));
            userSetMasts.append(nbs);
        }
    }
    dsml->firePropertyChange("masts", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

/**
 * Sets which signalMasts must be at Danager for the signal not to be set at a stop aspect
 */
void DestinationMast::setAutoMasts(QHash<SignalMast*, QString>* newAutoMasts, bool overright){
    if(log->isDebugEnabled())
        log->debug(destination->getDisplayName() + " setAutoMast Called");
    if (!this->autoMasts->isEmpty()){
        QListIterator<SignalMast*> keys(this->autoMasts->keys());
        while ( keys.hasNext() )
        {
           SignalMast* key = keys.next();
           key->removePropertyChangeListener(propertySignalMastListener);
        }
        //minimumBlockSpeed = 0;
    }
    destMastInit = false;
    if(overright){
        if(newAutoMasts->isEmpty()){
            this->autoMasts = new QHash<SignalMast*, QString>();
        } else {
            this->autoMasts=newAutoMasts;
        }
    } else {
        if (newAutoMasts->isEmpty()){
            this->autoMasts =  new QHash<SignalMast*, QString>();
        } else {
            QListIterator<SignalMast*> keys(newAutoMasts->keys());
            while ( keys.hasNext() )
            {
               SignalMast* key = keys.next();
               this->autoMasts->insert(key, newAutoMasts->value(key));
            }
        }
    }
    //kick off the process to add back in signalmasts at crossings.
    for(int i = 0; i<blockInXings.size(); i++)
    {
        blockInXings.at(i)->addSignalMastLogic(dsml->source);
    }

    dsml->firePropertyChange("automasts", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

/**
 * Sets which sensors must be in a given state before our mast can be set.
 * @param sensors
 */
void DestinationMast::setSensors(QHash<NamedBeanHandle<Sensor*>*, int> sensors){
    if (!this->userSetSensors.isEmpty()){
        foreach(NamedBeanSetting* nbh, userSetSensors){
            nbh->getBean()->removePropertyChangeListener(propertySensorListener);
        }
    }
    destMastInit = false;

    if(sensors.isEmpty()){
        userSetSensors =  QList<NamedBeanSetting*>();
    } else {
            QListIterator<NamedBeanHandle<Sensor*>* > e (sensors.keys());
            while(e.hasNext()){
                NamedBeanHandle<Sensor*>* nbh = e.next();
                NamedBeanSetting* nbs = new NamedBeanSetting((NamedBeanHandle<NamedBean*>*)nbh, sensors.value(nbh));
                userSetSensors.append(nbs);
            }
    }
    dsml->firePropertyChange("sensors", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

void DestinationMast::addSensor(NamedBeanHandle<Sensor*>* sen, int state){
    foreach(NamedBeanSetting* nbh, userSetSensors){
        if (nbh->getBean()==(sen->getBean()))
            return;
    }
    sen->getBean()->addPropertyChangeListener(propertySensorListener);
    connect(sen->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertySensorListener, SLOT(propertyChange(PropertyChangeEvent*)));
    NamedBeanSetting* nbs =  new NamedBeanSetting((NamedBeanHandle<NamedBean*>*)sen, state);
    userSetSensors.append(nbs);
    dsml->firePropertyChange("sensors", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

void DestinationMast::removeSensor(NamedBeanHandle<Sensor*>* sen){
    foreach(NamedBeanSetting* nbh, userSetSensors){
        if (nbh->getBean()==(sen->getBean())){
            sen->getBean()->removePropertyChangeListener(propertySensorListener);
            userSetSensors.removeAt(userSetSensors.indexOf(nbh));
            dsml->firePropertyChange("sensors", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
            return;
        }
    }
}

QList<Block*> DestinationMast::getBlocks(){
    QList<Block*> out =  QList<Block*>();
    foreach(NamedBeanSetting* nbh, userSetBlocks){
        out.append((Block*)nbh->getBean());
    }
    return out;
}

QList<Block*> DestinationMast::getAutoBlocks(){
    QList<Block*> out =  QList<Block*>();
    QList<Block*> blockKeys = autoBlocks.keys();
    //while ( blockKeys.hasNext() )
    foreach(Block* key, blockKeys)
    {
       //Block key = blockKeys.next();
        out.append(key);
    }
    return out;
}

QList<Block*> DestinationMast::getAutoBlocksBetweenMasts()
{
    if (dsml->destList.value(destination)->xingAutoBlocks.size() == 0 && dsml->destList.value(destination)->dblCrossoverAutoBlocks.size() == 0) {
        return getAutoBlocks();
    }
    QList<Block*> returnList = getAutoBlocks();
    foreach (Block* blk, getAutoBlocks()) {
        if (xingAutoBlocks.contains(blk)) {
            returnList.removeOne(blk);
        }
    }
    foreach (Block* blk, getAutoBlocks()) {
        if (dblCrossoverAutoBlocks.contains(blk)) {
            returnList.removeOne(blk);
        }
    }

    return returnList;
}

QList<Turnout*> DestinationMast::getTurnouts(){
    QList<Turnout*> out =  QList<Turnout*>();
    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        out.append((Turnout*)nbh->getBean());
    }
    return out;
}

//@SuppressWarnings("unchecked")
QList<NamedBeanHandle<Turnout*>* > DestinationMast::getNamedTurnouts(){
    QList<NamedBeanHandle<Turnout*>* > out =  QList<NamedBeanHandle<Turnout*>* >();
    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        out.append((NamedBeanHandle<Turnout*>*)nbh->getNamedBean());
    }
    return out;
}

QList<Turnout*> DestinationMast::getAutoTurnouts(){
    QList<Turnout*> out =  QList<Turnout*>();
    QListIterator<Turnout*> en (autoTurnouts.keys());
    while (en.hasNext()) {
        out.append(en.next());
    }
    return out;
}

QList<SignalMast*> DestinationMast::getSignalMasts(){
    QList<SignalMast*> out =  QList<SignalMast*>();
    foreach(NamedBeanSetting* nbh, userSetMasts){
        out.append((SignalMast*)nbh->getBean());
    }
    return out;
}

QList<SignalMast*> DestinationMast::getAutoSignalMasts(){
    QList<SignalMast*> out =  QList<SignalMast*>();
    QListIterator<SignalMast*> en (autoMasts->keys());
    while (en.hasNext()) {
        out.append(en.next());
    }
    return out;
}

QList<Sensor*> DestinationMast::getSensors(){
    QList<Sensor*> out =  QList<Sensor*>();
    foreach(NamedBeanSetting* nbh, userSetSensors){
        out.append((Sensor*)nbh->getBean());
    }
    return out;
}

//@SuppressWarnings("unchecked")
QList<NamedBeanHandle<Sensor*>* > DestinationMast::getNamedSensors(){
    QList<NamedBeanHandle<Sensor*>* > out =  QList<NamedBeanHandle<Sensor*>* >();
    foreach(NamedBeanSetting* nbh, userSetSensors){
        out.append((NamedBeanHandle<Sensor*>* )nbh->getNamedBean());
    }
    return out;
}

bool DestinationMast::isBlockIncluded(Block* block){
    foreach(NamedBeanSetting* nbh, userSetBlocks){
        if (nbh->getBean()==(block))
            return true;
    }
    return false;
}

bool DestinationMast::isAutoBlockIncluded(LayoutBlock* block){
    if(block!=nullptr)
        return autoBlocks.contains(block->getBlock());
    return false;
}

bool DestinationMast::isAutoBlockIncluded(Block* block){
    return autoBlocks.contains(block);
}

bool DestinationMast::isBlockIncluded(LayoutBlock* block){
    foreach(NamedBeanSetting* nbh, userSetBlocks){
        if (nbh->getBean()==(block->getBlock()))
            return true;
    }
    return false;
 }

bool DestinationMast::isTurnoutIncluded(Turnout* turnout){
    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        if (nbh->getBean()==(turnout))
            return true;
    }
    return false;
}

bool DestinationMast::isSensorIncluded(Sensor* sensor){
    foreach(NamedBeanSetting* nbh, userSetSensors){
        if (nbh->getBean()==(sensor))
            return true;
    }
    return false;
}

bool DestinationMast::isSignalMastIncluded(SignalMast* signal){
    foreach (NamedBeanSetting* nbh,userSetMasts){
        if (nbh->getBean()==(signal))
            return true;
    }
    return false;
}

int DestinationMast::getAutoBlockState(Block* block){
    if(autoBlocks.isEmpty())
        return -1;
    return autoBlocks.value(block);
}

int DestinationMast::getBlockState(Block* block){
    if(userSetBlocks.isEmpty())
        return -1;
    foreach(NamedBeanSetting* nbh, userSetBlocks){
        if (nbh->getBean()==(block))
            return nbh->getSetting();
    }
    return -1;
}
/*bool isBlockManualAssigned(Block block){
    return true;
}*/

int DestinationMast::getSensorState(Sensor* sensor){
    if(userSetSensors.isEmpty())
        return -1;
    foreach(NamedBeanSetting* nbh,userSetSensors){
        if (nbh->getBean()==(sensor))
            return nbh->getSetting();
    }
    return -1;
}

int DestinationMast::getTurnoutState(Turnout* turnout){
    if(userSetTurnouts.isEmpty())
        return -1;
    foreach(NamedBeanSetting* nbh,userSetTurnouts){
        if (nbh->getBean()==(turnout))
            return nbh->getSetting();
    }
    return -1;
}

int DestinationMast::getAutoTurnoutState(Turnout* turnout){
    if(autoTurnouts.isEmpty())
        return -1;
    if(autoTurnouts.contains(turnout))
        return autoTurnouts.value(turnout);
    return -1;
}

QString DestinationMast::getSignalMastState(SignalMast* mast){
    if(userSetMasts.isEmpty())
        return nullptr;
    foreach(NamedBeanSetting* nbh, userSetMasts){
        if (nbh->getBean()==(mast))
            return nbh->getStringSetting();
    }
    return nullptr;
}

QString DestinationMast::getAutoSignalMastState(SignalMast* mast){
    if(autoMasts->isEmpty())
        return "";
    return autoMasts->value(mast);
}


/*
 * Before going active or checking that we can go active, we will wait 500ms
 * for things to settle down to help prevent a race condition
 */
void DestinationMast::checkState(){
    if(disposed){
        log->error("checkState called even though this has been disposed of " + dsml->getSourceMast()->getDisplayName());
        return;
    }

    if(!enable)
        return;
    if (inWait){
        return;
    }

    log->debug("check Signal Dest State called");
    inWait=true;

//        Runnable r = new Runnable() {
//          /*public*/ void run() {
//            try {
////                    log->debug("Wait started");
//                Thread.sleep(InstanceManager::signalMastLogicManagerInstance().getSignalLogicDelay());
////                    log->debug("wait is over");
//                inWait=false;
//                checkStateDetails();
//            } catch (InterruptedException ex) {
//                Thread.currentThread().interrupt();
//                inWait=false;
//            }
//          }
//        };
    RunnableThis* r = new RunnableThis(dsml);
    thr = new QThread(r);
    /*try{
        thr.join();
    } catch (InterruptedException ex) {
//            log->debug("interrupted at join " + ex);
        inWait=false;
    }*/
    thr->setObjectName(dsml->getSourceMast()->getDisplayName() + " " + destination->getDisplayName());
    thr->start();
}


void DestinationMast::checkStateDetails() {
    turnoutThrown=false;
    permissiveBlock=false;
    if(disposed){
        log->error("checkStateDetails called even though this has been disposed of " + dsml->getSourceMast()->getDisplayName() + " " + destination->getDisplayName());
        return;
    }
    if(inWait){
        log->error("checkStateDetails called while we are waiting for things to settle");
        return;
    }
    if(!enable){
        return;
    }
    log->debug("From " + dsml->getSourceMast()->getDisplayName() + " to " + destination->getDisplayName() + " internal check state");
    active=false;
    if((_useLayoutEditor) && (autoTurnouts.size()==0) && (autoBlocks.size()==0)){
        return;
    }
    bool state = true;
    QListIterator<Turnout*> keys(autoTurnouts.keys());
    while ( keys.hasNext() )
    {
       Turnout* key = keys.next();
       if (key->getKnownState()!=autoTurnouts.value(key)){
            if (key->getState()!=autoTurnouts.value(key)){
                if (isTurnoutIncluded(key)){
                    if(key->getState()!=getTurnoutState(key)){
                        state=false;
                    } else if (key->getState()==Turnout::THROWN){
                        turnoutThrown=true;
                    }
                }
                 else {
                    state = false;
                }
            }
       } else if (key->getState()==Turnout::THROWN){
            turnoutThrown=true;
        }
    }

    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        Turnout* key = (Turnout*) nbh->getBean();
        if (key->getKnownState()!=nbh->getSetting())
           state=false;
        else if (key->getState()==Turnout::THROWN){
            turnoutThrown=true;
        }
    }

    QListIterator<SignalMast*> mastKeys(autoMasts->keys());
    while ( mastKeys.hasNext() )
    {
       SignalMast* key = mastKeys.next();
       if(log->isDebugEnabled())
        log->debug(key->getDisplayName() + " " + key->getAspect() + " " + autoMasts->value(key));
       if ((key->getAspect()!=nullptr) && (key->getAspect()!=(autoMasts->value(key)))){
           if (isSignalMastIncluded(key)){
            //Basically if we have a blank aspect, we don't care about the state of the signalmast
                if(getSignalMastState(key)!=("")){
                    if(key->getAspect()!=(getSignalMastState(key))){
                        state=false;
                    }
                }
            } else {
               state = false;
            }
       }
    }

    foreach(NamedBeanSetting* nbh, userSetMasts){
        SignalMast* key = (SignalMast*) nbh->getBean();
        if ((key->getAspect()==nullptr) || (key->getAspect()==(nbh->getStringSetting())))
           state=false;
    }

    foreach(NamedBeanSetting* nbh, userSetSensors){
        Sensor* key =(Sensor*) nbh->getBean();
        if (key->getKnownState()!=nbh->getSetting())
            state = false;
    }

    QList<Block*> blockAutoKeys = autoBlocks.keys();
    foreach(Block* key,blockAutoKeys)
    {
       if(log->isDebugEnabled())
            log->debug(key->getDisplayName() + " " + key->getState() + " " + autoBlocks.value(key));
       if (key->getState()!=autoBlocks.value(key)){
            if (isBlockIncluded(key)){
                if(getBlockState(key)!=0x03) {
                    if(key->getState()!=getBlockState(key)){
                        if(key->getState()==Block::OCCUPIED && key->getPermissiveWorking()){
                            permissiveBlock=true;
                        } else {
                            state=false;
                        }
                    }
                }
            } else {
                if(key->getState()==Block::OCCUPIED && key->getPermissiveWorking()){
                    permissiveBlock=true;
                } else {
                    state = false;
                }
            }
       }
    }

    foreach(NamedBeanSetting* nbh, userSetBlocks){
        Block* key = (Block*)nbh->getBean();
        if(nbh->getSetting()!=0x03){
            if (key->getState()!=nbh->getSetting()) {
                if(key->getState()==Block::OCCUPIED && key->getPermissiveWorking()){
                    permissiveBlock=true;
                } else {
                    state=false;
                }
            }
        }
    }
    if (permissiveBlock){
        /*If a block has been found to be permissive, but the source signalmast
        does not support a call-on/permissive aspect then the route can not be set*/
        if(dsml->getSourceMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::PERMISSIVE)==nullptr)
            state = false;
    }
    if(!state){
        turnoutThrown = false;
        permissiveBlock=false;
    }

    active=state;
    dsml->setSignalAppearance();
}

void DestinationMast::initialise(){
    if ((destMastInit) || (disposed)) { return;}

    active=false;
    turnoutThrown=false;
    permissiveBlock=false;
    bool routeclear = true;
    if((_useLayoutEditor) && (autoTurnouts.size()==0) && (autoBlocks.size()==0) && (autoMasts->size()==0)){
        return;
    }

    calculateSpeed();

    QListIterator<Turnout*> keys(autoTurnouts.keys());
    while ( keys.hasNext() )
    {
       Turnout* key = keys.next();
       key->addPropertyChangeListener(propertyTurnoutListener);
       connect(key->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyTurnoutListener, SLOT(propertyChange(PropertyChangeEvent*)));

       if (key->getKnownState()!=autoTurnouts.value(key)){
            if (key->getState()!=autoTurnouts.value(key)){
                if (isTurnoutIncluded(key)){
                    if(key->getState()!=getTurnoutState(key)){
                        routeclear=false;
                    } else if (key->getState()==Turnout::THROWN){
                        turnoutThrown=true;
                    }
                } else {
                    routeclear = false;
                }
            }
       } else if (key->getState()==Turnout::THROWN){
            turnoutThrown = true;
       }
    }

    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        Turnout* key = (Turnout*) nbh->getBean();
        key->addPropertyChangeListener(propertyTurnoutListener, nbh->getBeanName(), "Signal Mast Logic:" + dsml->source->getDisplayName() + " to " + destination->getDisplayName());
        connect(key->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyTurnoutListener, SLOT(propertyChange(PropertyChangeEvent*)));
        if (key->getKnownState()!=nbh->getSetting())
           routeclear=false;
        else if (key->getState()==Turnout::THROWN){
            turnoutThrown=true;
        }
    }

    QListIterator<SignalMast*> mastKeys(autoMasts->keys());
    while ( mastKeys.hasNext() )
    {
       SignalMast* key = mastKeys.next();
       //log->debug(destination->getDisplayName() + " auto mast add list " + key->getDisplayName());
       key->addPropertyChangeListener(propertySignalMastListener);
       connect(key->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertySignalMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
       if (key->getAspect()!=(autoMasts->value(key))){
            if(isSignalMastIncluded(key)){
                if(key->getAspect()==(getSignalMastState(key))){
                    routeclear = false;
                }
            } else {
                routeclear = false;
            }
        }
    }

    foreach(NamedBeanSetting* nbh, userSetMasts){
        SignalMast* key = (SignalMast*) nbh->getBean();
        key->addPropertyChangeListener(propertySignalMastListener);
        connect(key->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertySignalMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
        //log->debug(destination->getDisplayName() + " key asepct " + key->getAspect());
        //log->debug(destination->getDisplayName() + " key exepcted aspect " + masts.at(key));
        if ((key->getAspect()==nullptr) || (key->getAspect()!=(nbh->getStringSetting())))
            routeclear=false;
    }
    foreach(NamedBeanSetting* nbh, userSetSensors){
        AbstractSensor* sensor = (AbstractSensor*) nbh->getBean();
        ((AbstractNamedBean*)sensor)->addPropertyChangeListener((PropertyChangeListener*)propertySensorListener, nbh->getBeanName(), QString("Signal Mast Logic:") + dsml->source->getDisplayName() + " to " + destination->getDisplayName());
        connect(sensor, SIGNAL(propertyChange(PropertyChangeEvent*)), propertySensorListener, SLOT(propertyChange(PropertyChangeEvent*)));
        if (sensor->getKnownState()!=nbh->getSetting())
            routeclear = false;
    }

    QList<Block*> autoBlockKeys = autoBlocks.keys();
    foreach(Block* key, autoBlockKeys)
    {
       //log->debug(destination->getDisplayName() + " auto block add list " + key->getDisplayName());
       key->addPropertyChangeListener(propertyBlockListener);
       if (key->getState()!=autoBlocks.value(key)){
            if (isBlockIncluded(key)){
                if(key->getState()!=getBlockState(key)){
                    if(key->getState()==Block::OCCUPIED && key->getPermissiveWorking()){
                        permissiveBlock=true;
                    } else {
                        routeclear=false;
                    }
                }
            } else {
                if(key->getState()==Block::OCCUPIED && key->getPermissiveWorking()){
                    permissiveBlock=true;
                } else {
                    routeclear = false;
                }
            }
        }
    }

    foreach(NamedBeanSetting* nbh, userSetBlocks){
        Block* key = (Block*) nbh->getBean();
       key->addPropertyChangeListener(propertyBlockListener);
       connect(key->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertyBlockListener, SLOT(propertyChange(PropertyChangeEvent*)));
       if (key->getState()!=getBlockState(key)){
            if(key->getState()==Block::OCCUPIED && key->getPermissiveWorking()){
                permissiveBlock=true;
            } else {
                routeclear=false;
            }
        }
    }
    if (permissiveBlock){
        /*If a block has been found to be permissive, but the source signalmast
        does not support a call-on/permissive aspect then the route can not be set*/
        if(dsml->getSourceMast()->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::PERMISSIVE)==nullptr)
            routeclear = false;
    }
    if (routeclear){
        active=true;
        dsml->setSignalAppearance();
    } else {
        permissiveBlock=false;
        turnoutThrown =false;
    }
    destMastInit = true;
}


void DestinationMast::useLayoutEditor(bool boo) throw (JmriException) {
    if(log->isDebugEnabled())
        log->debug(destination->getDisplayName() + " use called " + QVariant(boo).toString() + " " + QVariant(_useLayoutEditor).toString());
    if (_useLayoutEditor == boo)
        return;
    _useLayoutEditor = boo;
    if ((boo) && (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->routingStablised())){
        try{
            setupLayoutEditorDetails();
        } catch (JmriException e){
            throw e;
            //Considered normal if there is no vlaid path using the layout editor.
        }
    } else {
        destinationBlock= nullptr;
        dsml->facingBlock = nullptr;
        dsml->protectingBlock = nullptr;
        setAutoBlocks(QMap<Block*, int>());
        setAutoTurnouts(QHash<Turnout*, int>() );
    }
}

void DestinationMast::useLayoutEditorDetails(bool turnouts, bool blocks) throw (JmriException){
    if(log->isDebugEnabled())
        log->debug(destination->getDisplayName() + " use layout editor details called " + QVariant(_useLayoutEditor).toString());
    _useLayoutEditorTurnouts=turnouts;
    _useLayoutEditorBlocks=blocks;
    if((_useLayoutEditor) && (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->routingStablised())){
        try{
            setupLayoutEditorDetails();
        } catch (JmriException e){
            throw e;
            //Considered normal if there is no valid path using the layout editor.
        }
    }
}

void DestinationMast::setupLayoutEditorDetails() throw (JmriException)
{
    log->debug(tr("setupLayoutEditorDetails: useLayoutEditor=%1 disposed=%2").arg(_useLayoutEditor?"true":"false").arg( disposed?"true":"false"));
    if ((!_useLayoutEditor) || (disposed)) {
        return;
    }
    LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
    if ((destinationBlock != nullptr) && (log->isDebugEnabled())) {
        log->debug(destination->getDisplayName() + " Set use layout editor");
    }
    QList<LayoutEditor*>* layout = static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
    QList<LayoutBlock*> protectingBlocks = QList<LayoutBlock*>();
    // We don't care which Layout Editor panel the signal mast is on, just so long as
    // the routing is done via layout blocks.
    LayoutBlock* remoteProtectingBlock = nullptr;
    for (int i = 0; i < layout->size(); i++) {
        if (log->isDebugEnabled()) {
            log->debug(destination->getDisplayName() + " Layout name " + layout->at(i)->getLayoutName());
        }
        if (facingBlock == nullptr) {
            facingBlock = lbm->getFacingBlockByNamedBean(dsml->getSourceMast(), layout->at(i));
        }
        if (protectingBlock == nullptr && protectingBlocks.isEmpty()) {
            //This is wrong
            protectingBlocks = lbm->getProtectingBlocksByNamedBean(dsml->getSourceMast(), layout->at(i));
        }
        if (destinationBlock == nullptr) {
            destinationBlock = lbm->getFacingBlockByNamedBean(destination, layout->at(i));
        }
        if (remoteProtectingBlock == nullptr) {
            remoteProtectingBlock = lbm->getProtectedBlockByNamedBean(destination, layout->at(i));
        }
    }
    // At this point, if we are not using the Layout Editor turnout or block
    // details then there is no point in trying to gather them.
    if ((!_useLayoutEditorTurnouts) && (!_useLayoutEditorBlocks)) {
        return;
    }
    if (facingBlock == nullptr) {
        log->error("No facing block found for source mast " + dsml->getSourceMast()->getDisplayName());
        throw JmriException("No facing block found for source mast " + dsml->getSourceMast()->getDisplayName());
    }
    if (destinationBlock == nullptr) {
        log->error("No facing block found for destination mast " + destination->getDisplayName());
        throw JmriException("No facing block found for destination mast " + destination->getDisplayName());
    }
    QList<LayoutBlock*> lblks = QList<LayoutBlock*>();
    if (protectingBlock == nullptr) {
        log->debug("protecting block is null");
        QString pBlkNames = "";
        QString lBlksNamesBuf;// = new StringBuffer();
        for (LayoutBlock* pBlk : protectingBlocks) {
            log->debug(tr("checking layoutBlock %1").arg(pBlk->getDisplayName()));
            pBlkNames = pBlkNames + pBlk->getDisplayName() + " (" + lbm->getLayoutBlockConnectivityTools()->checkValidDest(facingBlock, pBlk, destinationBlock, remoteProtectingBlock, LayoutBlockConnectivityTools::MASTTOMAST) + "), ";
            if (lbm->getLayoutBlockConnectivityTools()->checkValidDest(facingBlock, pBlk, destinationBlock, remoteProtectingBlock, LayoutBlockConnectivityTools::MASTTOMAST)) {
                try {
                    lblks = lbm->getLayoutBlockConnectivityTools()->getLayoutBlocks(facingBlock, destinationBlock, pBlk, true, LayoutBlockConnectivityTools::MASTTOMAST);
                    protectingBlock = pBlk;
                    log->debug("building path names...");
                    for (LayoutBlock* lBlk : lblks) {
                        lBlksNamesBuf.append(" ");
                        lBlksNamesBuf.append(lBlk->getDisplayName());
                    }
                    break;
                } catch (JmriException ee) {
                    log->debug("path not found this time");
                }
            }
        }
        QString lBlksNames = lBlksNamesBuf;//new String(lBlksNamesBuf);

        if (protectingBlock == nullptr) {
            throw JmriException("Path not valid, protecting block is null. Protecting block: " + pBlkNames + " not connected to " + facingBlock->getDisplayName() + ". Layout block names: " + lBlksNames);
        }
    }
    try {
        if (!lbm->getLayoutBlockConnectivityTools()->checkValidDest(facingBlock, protectingBlock, destinationBlock, remoteProtectingBlock, LayoutBlockConnectivityTools::MASTTOMAST)) {
            throw JmriException("Path not valid, destination check failed.");
        }
    } catch (JmriException e) {
        throw e;
    }
    if ( log->isDebugEnabled()) {
         log->debug(destination->getDisplayName() + " face " + facingBlock->metaObject()->className());
         log->debug(destination->getDisplayName() + " prot " + protectingBlock->metaObject()->className());
         log->debug(destination->getDisplayName() + " dest " + destinationBlock->metaObject()->className());
    }

    if (destinationBlock != nullptr && protectingBlock != nullptr && facingBlock != nullptr) {
        setAutoMasts(nullptr, true);
        if ( log->isDebugEnabled()) {
             log->debug(destination->getDisplayName() + " face " + facingBlock->getDisplayName());
             log->debug(destination->getDisplayName() + " prot " + protectingBlock->getDisplayName());
             log->debug(destination->getDisplayName() + " dest " + destinationBlock->getDisplayName());
        }

        try {
            lblks = lbm->getLayoutBlockConnectivityTools()->getLayoutBlocks(facingBlock, destinationBlock, protectingBlock, true, LayoutBlockConnectivityTools::MASTTOMAST);
        } catch (JmriException ee) {
             log->error(tr("No blocks found by the layout editor for pair %1-%2").arg(dsml->source->getDisplayName()).arg(destination->getDisplayName()));
        }
        //LinkedHashMap<Block*, int> block = setupLayoutEditorTurnoutDetails(lblks);
        QMap<Block*, int> block = setupLayoutEditorTurnoutDetails(lblks);

        for (int i = 0; i < blockInXings.size(); i++) {
            blockInXings.at(i)->removeSignalMastLogic(dsml->source);
        }
        blockInXings = QList<LevelXing*>(/*0*/);
        xingAutoBlocks = QList<Block*>();
        for (LayoutEditor* lay : *layout) {
            for (LayoutTrack* layoutTrack : lay->getLevelXings()) {
             LevelXing* levelXing = (LevelXing*)layoutTrack;
                //Looking for a crossing that both layout blocks defined and they are individual.
                if ((levelXing->getLayoutBlockAC() != nullptr)
                        && (levelXing->getLayoutBlockBD() != nullptr)
                        && (levelXing->getLayoutBlockAC() != levelXing->getLayoutBlockBD())) {
                    if (lblks.contains(levelXing->getLayoutBlockAC())) {
                        block.insert(levelXing->getLayoutBlockBD()->getBlock(), Block::UNOCCUPIED);
                        xingAutoBlocks.append(levelXing->getLayoutBlockBD()->getBlock());
                        blockInXings.append(levelXing);
                    } else if (lblks.contains(levelXing->getLayoutBlockBD())) {
                        block.insert(levelXing->getLayoutBlockAC()->getBlock(), Block::UNOCCUPIED);
                        xingAutoBlocks.append(levelXing->getLayoutBlockAC()->getBlock());
                        blockInXings.append(levelXing);
                    }
                }
            }
        }
        if (_useLayoutEditorBlocks) {
            setAutoBlocks(block);
        } else {
            setAutoBlocks(QMap<Block*, int>());
        }
        if (!_useLayoutEditorTurnouts) {
            setAutoTurnouts(QHash<Turnout*, int>());
        }

        setupAutoSignalMast(nullptr, false);
    }
    initialise();
}
/**
 * From a list of Layout Blocks, search for included Turnouts and their
 * Set To state.
 *
 * @param lblks List of Layout Blocks
 * @return a list of block - turnout state pairs
 */
QMap<Block*, int> DestinationMast::setupLayoutEditorTurnoutDetails(QList<LayoutBlock*> lblks) {
    ConnectivityUtil* connection;
    QList<LayoutTrackExpectedState<LayoutTurnout*>*> turnoutList;
    QHash<Turnout*, int> turnoutSettings = QHash<Turnout*, int>();
    QMap<Block*, int> block = QMap<Block*, int>();
    for (int i = 0; i < lblks.size(); i++) {
        if (log->isDebugEnabled()) {
            log->debug(lblks.at(i)->getDisplayName());
        }
        block.insert(lblks.at(i)->getBlock(), Block::UNOCCUPIED);
        if ((i > 0)) {
            int nxtBlk = i + 1;
            int preBlk = i - 1;
            if (i == lblks.size() - 1) {
                nxtBlk = i;
            }
            //We use the best connectivity for the current block;
            connection = new ConnectivityUtil(lblks.at(i)->getMaxConnectedPanel());
            turnoutList = connection->getTurnoutList(lblks.at(i)->getBlock(), lblks.at(preBlk)->getBlock(), lblks.at(nxtBlk)->getBlock());
            for (int x = 0; x < turnoutList.size(); x++) {
                LayoutTurnout* lt = turnoutList.at(x)->getObject();
                if (qobject_cast<LayoutSlip*>(lt)) {
                    LayoutSlip* ls = (LayoutSlip*) lt;
                    int slipState = turnoutList.at(x)->getExpectedState();
                    int taState = ls->getTurnoutState(slipState);
                    turnoutSettings.insert(ls->getTurnout(), taState);
                    int tbState = ls->getTurnoutBState(slipState);
                    turnoutSettings.insert(ls->getTurnoutB(), tbState);
                } else {
                    QString t = lt->getTurnoutName();
                    Turnout* turnout = InstanceManager::turnoutManagerInstance()->getTurnout(t);
                    if (log->isDebugEnabled()) {
                        if ((lt->getTurnoutType() <= 3) && (lt->getBlockName() != (""))) {
                            log->debug("turnout in list is straight left/right wye");
                            log->debug("turnout block Name " + lt->getBlockName());
                            log->debug("current " + lblks.at(i)->getBlock()->getDisplayName() + " - pre " + lblks.at(preBlk)->getBlock()->getDisplayName());
                            log->debug(QString("A ") + lt->getConnectA()->metaObject()->className());
                            log->debug(QString("B ") + lt->getConnectB()->metaObject()->className());
                            log->debug(QString("C ") + lt->getConnectC()->metaObject()->className());
                            log->debug(QString("D ") + lt->getConnectD()->metaObject()->className());
                        }
                    }
                    turnoutSettings.insert(turnout, turnoutList.at(x)->getExpectedState());
                    if (lt->getSecondTurnout() != nullptr) {
                        turnoutSettings.insert(lt->getSecondTurnout(), turnoutList.at(x)->getExpectedState());
                    }
                    /* TODO: We could do with a more inteligent way to deal with double crossovers, other than just looking at the state of the other conflicting blocks
                     such as looking at Signalmasts that protect the other blocks and the settings of any other turnouts along the way.
                     */
                    if (lt->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER) {
                        if (turnoutList.at(x)->getExpectedState() == Turnout::THROWN) {
                            if (lt->getLayoutBlock() == lblks.at(i) || lt->getLayoutBlockC() == lblks.at(i)) {
                                if (lt->getLayoutBlockB() != nullptr) {
                                    dblCrossoverAutoBlocks.append(lt->getLayoutBlockB()->getBlock());
                                    block.insert(lt->getLayoutBlockB()->getBlock(), Block::UNOCCUPIED);
                                }
                                if (lt->getLayoutBlockD() != nullptr) {
                                    dblCrossoverAutoBlocks.append(lt->getLayoutBlockD()->getBlock());
                                    block.insert(lt->getLayoutBlockD()->getBlock(), Block::UNOCCUPIED);
                                }
                            } else if (lt->getLayoutBlockB() == lblks.at(i) || lt->getLayoutBlockD() == lblks.at(i)) {
                                if (lt->getLayoutBlock() != nullptr) {
                                    dblCrossoverAutoBlocks.append(lt->getLayoutBlock()->getBlock());
                                    block.insert(lt->getLayoutBlock()->getBlock(), Block::UNOCCUPIED);
                                }
                                if (lt->getLayoutBlockC() != nullptr) {
                                    dblCrossoverAutoBlocks.append(lt->getLayoutBlockC()->getBlock());
                                    block.insert(lt->getLayoutBlockC()->getBlock(), Block::UNOCCUPIED);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (_useLayoutEditorTurnouts) {
        setAutoTurnouts(turnoutSettings);
    }
    return block;
}

/*
 * The generation of auto signalmast, looks through all the other logics
 * to see if there are any blocks that are in common and thus will add
 * the other signalmast protecting that Block::
 */
void DestinationMast::setupAutoSignalMast(SignalMastLogic* sml, bool overright){
    if(!allowAutoSignalMastGeneration)
        return;
    QList<SignalMastLogic*> smlList = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getLogicsByDestination(destination);
    QList<Block*> allBlock =  QList<Block*>();

    foreach(NamedBeanSetting* nbh, userSetBlocks){
        allBlock.append((Block*)nbh->getBean());
    }

    QList<Block*> blockKeys = autoBlocks.keys();
    foreach(Block* key, blockKeys)
    {
        if(!allBlock.contains(key))
            allBlock.append(key);
    }
    QHash<SignalMast*, QString>* masts;
    if(sml!=nullptr){
        masts = autoMasts;
        if(sml->areBlocksIncluded(allBlock)){
            SignalMast* mast = sml->getSourceMast();
            QString danger =  mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER);
            masts->insert(mast, danger);
        } else{
            //No change so will leave.
            return;
        }
    } else {
        masts =  new QHash<SignalMast*, QString>();
        for(int i = 0; i<smlList.size(); i++){
            if(smlList.at(i)->areBlocksIncluded(allBlock)){
                SignalMast* mast = smlList.at(i)->getSourceMast();
                QString danger =  mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER);
                masts->insert(mast, danger);
            }
        }
    }
    setAutoMasts(masts, overright);
}

void DestinationMast::addAutoSignalMast(SignalMast* mast){
    if(log->isDebugEnabled())
        log->debug(destination->getDisplayName() + " add mast to auto list " + mast->getDisplayName());
    QString danger = mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER);
    this->autoMasts->insert(mast, danger);
    if (destMastInit)
    {
        mast->addPropertyChangeListener(propertySignalMastListener);
        connect(mast->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), propertySignalMastListener, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    dsml->firePropertyChange("automasts", QVariant(), VPtr<SignalMast>::asQVariant(this->destination));
}

void DestinationMast::removeAutoSignalMast(SignalMast* mast){
    this->autoMasts->remove(mast);
    if(destMastInit)
        mast->removePropertyChangeListener(propertySignalMastListener);
    dsml->firePropertyChange("automasts", VPtr<SignalMast>::asQVariant(this->destination), QVariant());
}

bool DestinationMast::useLayoutEditor(){
    return _useLayoutEditor;
}

bool DestinationMast::useLayoutEditorBlocks(){
    return _useLayoutEditorBlocks;
}

bool DestinationMast::useLayoutEditorTurnouts(){
    return _useLayoutEditorTurnouts;
}


bool DestinationMast::allowAutoSignalMastGen(){
    return allowAutoSignalMastGeneration;
}

void DestinationMast::allowAutoSignalMastGen(bool gen) {
    if(allowAutoSignalMastGeneration==gen)
        return;
    allowAutoSignalMastGeneration = gen;
}

void DestinationMast::dispose(){
    disposed = true;
    clearTurnoutLock();
    destination->removePropertyChangeListener(propertyDestinationMastListener);
    setBlocks(QHash<Block*,int>());
    setAutoBlocks(QMap<Block*,int>());
    setTurnouts(QHash<NamedBeanHandle<Turnout*>*,int>());
    setAutoTurnouts(QHash<Turnout*,int>());
    setSensors(QHash<NamedBeanHandle<Sensor*>*,int>());
    setMasts(QHash<SignalMast*, QString>());
    setAutoMasts(new QHash<SignalMast*, QString>(), true);
}

void DestinationMast::lockTurnouts(){
    //We do not allow the turnouts to be locked, if we are disposed the logic,
    //the logic is not active, or if we do not allow the turnouts to be locked
    if((disposed) || (!_lockTurnouts) || (!active))
        return;

    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        Turnout* key = (Turnout*) nbh->getBean();
        key->setLocked(Turnout::CABLOCKOUT+Turnout::PUSHBUTTONLOCKOUT, true);
    }
    QListIterator<Turnout*> keys (autoTurnouts.keys());
    while ( keys.hasNext() )
    {
        Turnout* key = keys.next();
        key->setLocked(Turnout::CABLOCKOUT+Turnout::PUSHBUTTONLOCKOUT, true);
    }
}

void DestinationMast::clearTurnoutLock(){
    //We do not allow the turnout lock to be cleared, if we are not active,
    //and the lock flag has not been set.
    if((!_lockTurnouts) && (!active))
        return;

    QListIterator<Turnout*> keys (autoTurnouts.keys());
    while ( keys.hasNext() )
    {
        Turnout* key = keys.next();
       key->setLocked(Turnout::CABLOCKOUT+Turnout::PUSHBUTTONLOCKOUT, false);
    }

    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        Turnout* key = (Turnout*) nbh->getBean();
        key->setLocked(Turnout::CABLOCKOUT+Turnout::PUSHBUTTONLOCKOUT, false);
    }
}

/*protected*/ void DestinationMast::calculateSpeed(){
    if(log->isDebugEnabled())
        log->debug(destination->getDisplayName() + " calculate the speed setting for this logic ie what the signalmast will display");
    minimumBlockSpeed=0.0f;
    QListIterator<Turnout*> keys(autoTurnouts.keys());
    while ( keys.hasNext() )
    {
       Turnout* key = keys.next();
       if(log->isDebugEnabled())
            log->debug(destination->getDisplayName() + " turnout " + key->getDisplayName());
       //if(!turnouts.contains(key)){
        foreach(NamedBeanSetting* nbTurn, userSetTurnouts){
            if(nbTurn->getBean()!=(key)){
               if (key->getState()==Turnout::CLOSED){
                    if (((key->getStraightLimit()<minimumBlockSpeed) || (minimumBlockSpeed==0)) && (key->getStraightLimit()!=-1)){
                        minimumBlockSpeed = key->getStraightLimit();
                        if(log->isDebugEnabled())
                            log->debug(destination->getDisplayName() + " turnout " + key->getDisplayName() + " set speed to " + minimumBlockSpeed);
                    }
                } else {
                    if (((key->getDivergingLimit()<minimumBlockSpeed) || (minimumBlockSpeed==0)) && (key->getDivergingLimit()!=-1)){
                        minimumBlockSpeed = key->getDivergingLimit();
                        if(log->isDebugEnabled())
                            log->debug(destination->getDisplayName() + " turnout " + key->getDisplayName() + " set speed to " + minimumBlockSpeed);
                    }
                }
            }
        }
    }


    foreach(NamedBeanSetting* nbh, userSetTurnouts){
        Turnout* key = (Turnout*) nbh->getBean();
        if (key->getState()==Turnout::CLOSED){
            if (((key->getStraightLimit()<minimumBlockSpeed) || (minimumBlockSpeed==0)) && (key->getStraightLimit()!=-1)){
                minimumBlockSpeed = key->getStraightLimit();
                if(log->isDebugEnabled())
                    log->debug(destination->getDisplayName() + " turnout " + key->getDisplayName() + " set speed to " + minimumBlockSpeed);
            }
        } else if (key->getState()==Turnout::THROWN) {
            if (((key->getDivergingLimit()<minimumBlockSpeed) || (minimumBlockSpeed==0)) && (key->getDivergingLimit()!=-1)){
                minimumBlockSpeed = key->getDivergingLimit();
                if(log->isDebugEnabled())
                    log->debug(destination->getDisplayName() + " turnout " + key->getDisplayName() + " set speed to " + minimumBlockSpeed);
            }
        }
    }

    QList<Block*> autoBlockKeys = autoBlocks.keys();
    foreach(Block* key, autoBlockKeys)
    {
       log->debug(destination->getDisplayName() + " auto block add list " + key->getDisplayName());
       if(!isBlockIncluded(key)){
           if (((key->getSpeedLimit()<minimumBlockSpeed) || (minimumBlockSpeed==0)) && (key->getSpeedLimit()!=-1)){
               minimumBlockSpeed=key->getSpeedLimit();
               if(log->isDebugEnabled())
                    log->debug(destination->getDisplayName() + " block " + key->getDisplayName() + " set speed to " + minimumBlockSpeed);
            }
        }
    }
    foreach(NamedBeanSetting* nbh, userSetBlocks){
       Block* key = (Block*)nbh->getBean();
       if (((key->getSpeedLimit()<minimumBlockSpeed) || (minimumBlockSpeed==0)) && (key->getSpeedLimit()!=-1)){
           if(log->isDebugEnabled())
                log->debug(destination->getDisplayName() + " block " + key->getDisplayName() + " set speed to " + minimumBlockSpeed);
            minimumBlockSpeed=key->getSpeedLimit();
       }
    }
    /*if(minimumBlockSpeed==-0.1f)
        minimumBlockSpeed==0.0f;*/
}

//    protected PropertyChangeListener propertySensorListener = new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            Sensor sen = (Sensor) e.getSource();
//            log->debug(source.getDisplayName() + " to " + destination->getDisplayName() + " destination sensor "+ sen.getDisplayName() + "trigger " + e.getPropertyName());
//            if (e.getPropertyName()==("KnownState")) {
//                int now = ((Integer) e.getNewValue()).intValue();
//                log->debug("current value " + now + " value we want " + getSensorState(sen));
//                if (IsSensorIncluded(sen) && getSensorState(sen)!=now){
//                    //if(log->isDebugEnabled())
//                        log->debug("Sensor " + sen.getDisplayName() + " caused the signalmast to be set to danger");
//                    //getSourceMast().setAspect(stopAspect);
//                    if (active==true){
//                        active=false;
//                        setSignalAppearance();
//                    }
//                } else if (getSensorState(sen)==now) {
//                    //if(log->isDebugEnabled())
//                        log->debug(destination->getDisplayName() + " sensor " + sen.getDisplayName() + " triggers a calculation of change");
//                    checkState();
//                }
//            }
//        }
//    };

//    protected PropertyChangeListener propertyTurnoutListener = new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            Turnout turn = (Turnout) e.getSource();
//         //   log->debug(destination->getDisplayName() + " destination sensor "+ sen.getDisplayName() + "trigger");
//            if (e.getPropertyName()==("KnownState")) {
//                //Need to check this against the manual list vs auto list
//                //The manual list should over-ride the auto list
//                int now = ((Integer) e.getNewValue()).intValue();
//                if(isTurnoutIncluded(turn)){
//                    if (getTurnoutState(turn)!=now){
//                        if(log->isDebugEnabled()){
//                            log->debug("Turnout " + turn.getDisplayName() + " caused the signalmast to be set");
//                            log->debug("From " + getSourceMast().getDisplayName() + " to " + destination->getDisplayName() + " Turnout " + turn.getDisplayName() + " caused the signalmast to be set to danger");
//                        }
//                        if (active==true){
//                            active=false;
//                            setSignalAppearance();
//                        }
//                    } else {
//                        if(log->isDebugEnabled())
//                            log->debug(destination->getDisplayName() + " turnout " + turn.getDisplayName() + " triggers a calculation of change");
//                        checkState();
//                    }
//                } else if(autoTurnouts.contains(turn)){
//                    if (getAutoTurnoutState(turn)!=now){
//                        if(log->isDebugEnabled()){
//                            log->debug("Turnout " + turn.getDisplayName() + " auto caused the signalmast to be set");
//                            log->debug("From " + getSourceMast().getDisplayName() + " to" + destination->getDisplayName() + " Auto Turnout " + turn.getDisplayName() + " auto caused the signalmast to be set to danger");
//                        }
//                        if (active==true){
//                            active=false;
//                            setSignalAppearance();
//                        }
//                    } else {
//                        if(log->isDebugEnabled())
//                            log->debug("From " + getSourceMast().getDisplayName() + " to " + destination->getDisplayName() + " turnout " + turn.getDisplayName() + " triggers a calculation of change");
//                        checkState();
//                    }
//                }

//            } else if ((e.getPropertyName()==("TurnoutStraightSpeedChange")) || (e.getPropertyName()==("TurnoutDivergingSpeedChange"))){
//                calculateSpeed();
//            }
//        }
//    };

//    protected PropertyChangeListener propertyBlockListener = new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            Block block = (Block) e.getSource();
//            if(log->isDebugEnabled())
//                log->debug(destination->getDisplayName() + " destination block "+ Block::getDisplayName() + " trigger " +e.getPropertyName() + " " + e.getNewValue());
//            if (e.getPropertyName()==("state")) {
//                int now = ((Integer) e.getNewValue()).intValue();
//                if(log->isDebugEnabled()){
//                    log->debug(isBlockIncluded(block));
//                    log->debug(autoBlocks.contains(block));
//                }
//                if (isBlockIncluded(block)){
//                    if(log->isDebugEnabled()){
//                        log->debug(destination->getDisplayName() + " in manual block");
//                        log->debug(getBlockState(block) + "  " + now);
//                    }
//                    /*if (getBlockState(block) != now){
//                        if(log->isDebugEnabled()){
//                            log->debug("Block " + Block::getDisplayName() + " caused the signalmast to be set");
//                            log->debug(destination->getDisplayName() + " Block " + Block::getDisplayName() + " caused the signalmast to be set");
//                        }
//                        if (active==true){
//                            active=false;
//                            setSignalAppearance();
//                        }
//                    } else {
//                        if(log->isDebugEnabled())
//                            log->debug(destination->getDisplayName() + " block " + Block::getDisplayName() + " triggers a calculation of change");
//                        checkState();
//                    }*/
//                    checkState();
//                } else if (autoBlocks.contains(block)){
//                    if(log->isDebugEnabled()){
//                        log->debug(destination->getDisplayName() + " in auto block");
//                        log->debug(getAutoBlockState(block) + "  " + now);
//                    }
//                    /*if (getAutoBlockState(block) != now){
//                        if(log->isDebugEnabled()){
//                            log->debug("Block " + Block::getDisplayName() + " caused the signalmast to be set");
//                            log->debug(destination->getDisplayName() + " auto Block " + Block::getDisplayName() + " caused the signalmast to be set");
//                        }
//                        if (active==true){
//                            active=false;
//                            setSignalAppearance();

//                        }
//                    } else {
//                        if(log->isDebugEnabled())
//                            log->debug(destination->getDisplayName() + " auto block " + Block::getDisplayName() + " triggers a calculation of change");
//                        checkState();
//                    }*/
//                    checkState();
//                } else if(log->isDebugEnabled()) {
//                    log->debug(destination->getDisplayName() + " Not found");
//                }
//            } else if (e.getPropertyName()==("BlockSpeedChange")) {
//                calculateSpeed();
//            }
//        }
//    };

//    protected PropertyChangeListener propertySignalMastListener = new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent e) {

//            SignalMast* mast = (SignalMast) e.getSource();
//            if(log->isDebugEnabled())
//                log->debug(destination->getDisplayName() + " signalmast change " + mast->getDisplayName() + " " + e.getPropertyName());
//         //   log->debug(destination->getDisplayName() + " destination sensor "+ sen.getDisplayName() + "trigger");
//            if (e.getPropertyName()==("Aspect")) {

//                QString now = ((QString) e.getNewValue());
//                if(log->isDebugEnabled())
//                    log->debug(destination->getDisplayName() + " match property " + now);
//                if(isSignalMastIncluded(mast)){
//                    if (!now==(getSignalMastState(mast))){
//                        if(log->isDebugEnabled()) {
//                            log->debug(destination->getDisplayName() + " in mast list SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
//                            log->debug("SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
//                        }
//                        if (active){
//                            active=false;
//                            setSignalAppearance();
//                        }
//                    } else {
//                        if(log->isDebugEnabled())
//                            log->debug(destination->getDisplayName() + " in mast list signalmast change");
//                        checkState();
//                    }
//                } else if (autoMasts.contains(mast)){
//                    if (!now==(getAutoSignalMastState(mast))){
//                        if(log->isDebugEnabled()){
//                            log->debug("SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
//                            log->debug(destination->getDisplayName() + " in auto mast list SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
//                        }
//                        if (active){
//                            active=false;
//                            setSignalAppearance();
//                        }
//                    } else {
//                        if(log->isDebugEnabled())
//                            log->debug(destination->getDisplayName() + " in auto mast list signalmast change");
//                        checkState();
//                    }
//                }
//            }
//        }
//    };


/* Code currently not used commented out to remove unused error
protected PropertyChangeListener propertySignalMastLogicManagerListener = new PropertyChangeListener() {
    public void propertyChange(PropertyChangeEvent e) {
        if(log->isDebugEnabled())
            log->debug(destination->getDisplayName() + " Signal Mast Manager Listener");
     //   log->debug(destination->getDisplayName() + " destination sensor "+ sen.getDisplayName() + "trigger");
        if (e.getPropertyName()==("DestinationAdded")) {
            SignalMast* dest = ((SignalMast) e.getNewValue());
            if(dest==destination){
                jmri.SignalMastLogic sml = ((jmri.SignalMastLogic) e.getOldValue());
                setupAutoSignalMast(sml, false);
            }
        }
    }
};*/

/*protected*/ bool DestinationMast::IsSensorIncluded(Sensor* sen){
    foreach(NamedBeanSetting* nbh, userSetSensors){
        if (nbh->getBean()==sen)
            return true;
    }
    return false;
}
    

//};

//This is the listener on the destination signalMast
///*protected*/ PropertyChangeListener* propertyDestinationMastListener = new PropertyChangeListener(){
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            SignalMast* mast = (SignalMast) e.getSource();
//            if (mast==destination){
//                if(log->isDebugEnabled())
//                    log->debug("destination mast change " +mast->getDisplayName());
//                setSignalAppearance();
//            }
//        }
//};

//This is the listener on the source signalMast
///*protected*/ PropertyChangeListener* propertySourceMastListener = new PropertyChangeListener(){
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            SignalMast* mast = (SignalMast) e.getSource();
//            if ((mast==source) && (e.getPropertyName()==("Held"))){
//                if(log->isDebugEnabled())
//                    log->debug("source mast change " +mast->getDisplayName() + " " + e.getPropertyName());
//                setSignalAppearance();
//            }
//        }
//};

/*public*/ /*synchronized*/ void DefaultSignalMastLogic::addPropertyChangeListener(PropertyChangeListener* l)
{
 QMutexLocker locker(&mutex);
 pcs->addPropertyChangeListener(l);
}
/*public*/ /*synchronized*/ void DefaultSignalMastLogic::removePropertyChangeListener(PropertyChangeListener* l)
{
 QMutexLocker locker(&mutex);
 pcs->removePropertyChangeListener(l);
}
/*public*/ /*synchronized*/ int DefaultSignalMastLogic::getNumPropertyChangeListeners()
{
 QMutexLocker locker(&mutex);
 return pcs->getPropertyChangeListeners().count();
}
/*protected*/ void DefaultSignalMastLogic::firePropertyChange(QString p, QVariant old, QVariant n) { pcs->firePropertyChange(p,old,n);}

/*public*/ void DefaultSignalMastLogic::dispose()
{
    disposing=true;
    getSourceMast()->removePropertyChangeListener(propertySourceMastListener);
    QListIterator<SignalMast*> en(destList.keys());
    while (en.hasNext()) {
        SignalMast* dm = en.next();
        destList.value(dm)->dispose();
    }
}

//@Override
/*public*/ QString DefaultSignalMastLogic::getBeanType() {
    return tr("SignalMastLogic");
}

/**
 * No valid integer state, always return a constant.
 *
 * @return Always zero
 */
//@Override
/*public*/ int DefaultSignalMastLogic::getState() {
    return 0;
}

//@Override
/*public*/ void DefaultSignalMastLogic::setState(int /*i*/) {
}

//@Override
/*public*/ QList<NamedBeanUsageReport*> DefaultSignalMastLogic::getUsageReport(NamedBean* bean) {
    QList<NamedBeanUsageReport*> report = QList<NamedBeanUsageReport*>();
    if (bean != nullptr) {
        if (bean->equals(getSourceMast())) {
            report.append(new NamedBeanUsageReport("SMLSourceMast"));  // NOI18N
        }
        //getDestinationList().forEach((dest) ->
        foreach(SignalMast* dest, getDestinationList())
        {
            if (bean->equals(dest)) {
                report.append(new NamedBeanUsageReport("SMLDestinationMast"));  // NOI18N
            }
            //getAutoBlocks(dest).forEach((block) -> {
            foreach(Block* block, getAutoBlocks(dest))
            {
                if (bean->equals(block)) {
                    report.append(new NamedBeanUsageReport("SMLBlockAuto", dest));  // NOI18N
                }
            }//);
            //getBlocks(dest).forEach((block) -> {
            foreach(Block* block, getBlocks(dest))
            {
                if (bean->equals(block)) {
                    report.append(new NamedBeanUsageReport("SMLBlockUser", dest));  // NOI18N
                }
            }//);
            //getAutoTurnouts(dest).forEach((turnout) -> {
            foreach(Turnout* turnout, getAutoTurnouts(dest)   )
            {
                if (bean->equals(turnout)) {
                    report.append(new NamedBeanUsageReport("SMLTurnoutAuto", dest));  // NOI18N
                }
            }//);
            //getTurnouts(dest).forEach((turnout) -> {
            foreach(Turnout* turnout, getTurnouts(dest)   )
            {
                if (bean->equals(turnout)) {
                    report.append(new NamedBeanUsageReport("SMLTurnoutUser", dest));  // NOI18N
                }
            }//);
            //getSensors(dest).forEach((sensor) -> {
            foreach(Sensor* sensor, getSensors(dest)   )
            {
                if (bean->equals(sensor)) {
                    report.append(new NamedBeanUsageReport("SMLSensor", dest));  // NOI18N
                }
            }//);
            //getAutoMasts(dest).forEach((mast) -> {
            foreach(SignalMast* mast, getAutoMasts(dest)   )
            {
                if (bean->equals(mast)) {
                    report.append(new NamedBeanUsageReport("SMLMastAuto", dest));  // NOI18N
                }
            }//);
            //getSignalMasts(dest).forEach((mast) -> {
            foreach(SignalMast* mast, getSignalMasts(dest)   )
            {

                if (bean->equals(mast)) {
                    report.append(new NamedBeanUsageReport("SMLMastUser", dest));  // NOI18N
                }
            }//);
        }//);
    }
    return report;
}

/*static*/ Logger*  DefaultSignalMastLogic::log = LoggerFactory::getLogger("DefaultSignalMastLogic");
//}
