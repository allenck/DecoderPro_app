#include "defaultsignalmastlogicmanager.h"
#include "instancemanager.h"
#include "signalspeedmap.h"
#include "propertychangelistener.h"
#include "../LayoutEditor/layoutblockmanager.h"
#include "defaultsignalmastlogic.h"
#include "../LayoutEditor/configxmlmanager.h"
#include "signalmastmanager.h"

//DefaultSignalMastLogicManager::DefaultSignalMastLogicManager(QObject *parent) :
//    SignalMastLogicManager(parent)
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
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Kevin Dickerson Copyright (C) 2011
 * @version			$Revision: 20228 $
 */

// /*public*/ class DefaultSignalMastLogicManager implements jmri.SignalMastLogicManager {

/*public*/ DefaultSignalMastLogicManager::DefaultSignalMastLogicManager(QObject *parent) : SignalMastLogicManager(parent)
{
 setObjectName("DefaultSignalMastLogicManager");
 setProperty("JavaClassName", "jmri.managers.DefaultSignalMastLogicManager");
    log = new Logger("DefaultSignalMastLogicManager");
    _speedMap = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"));
    signalMastLogic =  QList<SignalMastLogic*>();
    pcs = new PropertyChangeSupport(this);
    signalLogicDelay = 500L;
    runWhenStablised = false;
    propertyBlockManagerListener = new PropertyBlockManagerListener(this);
    registerSelf();
//    InstanceManager::layoutBlockManagerInstance()->addPropertyChangeListener(propertyBlockManagerListener);
    connect(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager")), SIGNAL(propertyChange(PropertyChangeEvent*)), propertyBlockManagerListener, SLOT(propertyChange(PropertyChangeEvent*)));
    ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->addPropertyChangeListener(propertyBlockManagerListener);
    ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
    InstanceManager::turnoutManagerInstance()->addVetoableChangeListener((VetoableChangeListener*)this);
    //_speedMap = jmri.implementation.SignalSpeedMap.getMap();
}

/*public*/ int DefaultSignalMastLogicManager::getXMLOrder() const{
    return Manager::SIGNALMASTLOGICS;
}


/*public*/ /*final*/ /*static*/ SignalSpeedMap* DefaultSignalMastLogicManager::getSpeedMap() {
    return _speedMap;
}

/*public*/ SignalMastLogic* DefaultSignalMastLogicManager::getSignalMastLogic(SignalMast* source)
{
 for(int i = 0; i <signalMastLogic.size(); i++)
 {
  if (((DefaultSignalMastLogic*)signalMastLogic.at(i))->getSourceMast()==source)
    return signalMastLogic.at(i);
 }
 return NULL;
}

/*public*/ SignalMastLogic* DefaultSignalMastLogicManager::newSignalMastLogic(SignalMast* source)
{
 for(int i = 0; i <signalMastLogic.size(); i++)
 {
  if (((DefaultSignalMastLogic*)signalMastLogic.at(i))->getSourceMast()==source)
            return signalMastLogic.at(i);
 }
 SignalMastLogic* logic = new DefaultSignalMastLogic(source);
 signalMastLogic.append(logic);
 firePropertyChange("length", QVariant(), QVariant(signalMastLogic.size()));
 emit on_newSignalMastLogicCreated(logic);
 return logic;
}


//Hashtable<SignalMast, QList<SignalMastLogic>> destLocationList = new Hashtable<SignalMast, QList<SignalMastLogic>>();

/*public*/ void DefaultSignalMastLogicManager::replaceSignalMast(SignalMast* oldMast, SignalMast* newMast)
{
 if(oldMast==NULL || newMast==NULL)
     return;
 foreach(SignalMastLogic* source, signalMastLogic)
 {
  if(((DefaultSignalMastLogic*)source)->getSourceMast()==oldMast)
  {
   ((DefaultSignalMastLogic*)source)->replaceSourceMast(oldMast, newMast);
  }
  else
  {
   ((DefaultSignalMastLogic*)source)->replaceDestinationMast(oldMast, newMast);
  }
 }
}

/*public*/ void DefaultSignalMastLogicManager::swapSignalMasts(SignalMast* mastA, SignalMast* mastB)
{
 if(mastA==NULL || mastB==NULL){
     return;
 }
 QList<SignalMastLogic*> mastALogicList = getLogicsByDestination(mastA);
 SignalMastLogic* mastALogicSource = getSignalMastLogic(mastA);

 QList<SignalMastLogic*> mastBLogicList = getLogicsByDestination(mastB);
 SignalMastLogic* mastBLogicSource = getSignalMastLogic(mastB);

 if(mastALogicSource!=NULL)
     ((DefaultSignalMastLogic*)mastALogicSource)->replaceSourceMast(mastA, mastB);
 if(mastBLogicSource!=NULL)
     ((DefaultSignalMastLogic*)mastBLogicSource)->replaceSourceMast(mastB, mastA);

 foreach(SignalMastLogic* mastALogic, mastALogicList){
     ((DefaultSignalMastLogic*)mastALogic)->replaceDestinationMast(mastA, mastB);
 }
 foreach(SignalMastLogic* mastBLogic, mastBLogicList){
     ((DefaultSignalMastLogic*)mastBLogic)->replaceDestinationMast(mastB, mastA);
 }
}

/**
* Gather a list of all the signal mast logics, by destination signal mast
*/

/*public*/ QList<SignalMastLogic*> DefaultSignalMastLogicManager::getLogicsByDestination(SignalMast* destination){
   QList<SignalMastLogic*> list =QList<SignalMastLogic*>();
    foreach(SignalMastLogic* source, signalMastLogic){
        if(((DefaultSignalMastLogic*)source)->isDestinationValid(destination))
            list.append(source);
    }
    return list;
    /*isDestinationValid(SignalMast dest)
    if(!destLocationList.contains(destination))
        return new QList<SignalMastLogic>();
    return destLocationList.get(destination);*/
}

/**
 * Returns an arraylist of signalmastlogic
 * @return An QList of SignalMast logics
 */
/*public*/ QList<SignalMastLogic*> DefaultSignalMastLogicManager::getSignalMastLogicList() {
    return signalMastLogic;
}


/*public*/ bool DefaultSignalMastLogicManager::isSignalMastUsed(SignalMast* mast){
    if(getSignalMastLogic(mast)!=NULL){
        /*Although the we might have it registered as a source, it may not have
          any valid destination, so therefore it can be returned as not in use */
        if(((DefaultSignalMastLogic*)getSignalMastLogic(mast))->getDestinationList().size()!=0)
            return true;
    }
    if(getLogicsByDestination(mast).size()!=0)
        return true;
    return false;
}

/**
 * Remove a destination mast from the signalmast logic
 * @param sml The signalmast logic of the source signal
 * @param dest The destination mast
 */
/*public*/ void DefaultSignalMastLogicManager::removeSignalMastLogic(SignalMastLogic* sml, SignalMast* dest){
    if(((DefaultSignalMastLogic*)sml)->removeDestination(dest)){
        removeSignalMastLogic(sml);
    }
}

/**
* Completely remove the signalmast logic.
*/
/*public*/ void DefaultSignalMastLogicManager::removeSignalMastLogic(SignalMastLogic* sml){
    if(sml==NULL)
        return;
    //Need to provide a method to delete and dispose.
    sml->dispose();

    signalMastLogic.removeAt(signalMastLogic.indexOf(sml));
    firePropertyChange("length", QVariant(), QVariant(signalMastLogic.size()));
}

/*
* Procedure for completely remove a signalmast out of all the logics
*/
/*public*/ void DefaultSignalMastLogicManager::removeSignalMast(SignalMast* mast){
    if(mast==NULL)
        return;

    foreach(SignalMastLogic* source, signalMastLogic){
         if (((DefaultSignalMastLogic*)source)->isDestinationValid(mast)){
            ((DefaultSignalMastLogic*)source)->removeDestination(mast);
        }
    }
    removeSignalMastLogic(getSignalMastLogic(mast));
}

/*public*/ void DefaultSignalMastLogicManager::disableLayoutEditorUse(SignalMast* mast){
    SignalMastLogic* source = getSignalMastLogic(mast);
    if(source!=NULL)
        ((DefaultSignalMastLogic*)source)->disableLayoutEditorUse();
    foreach(SignalMastLogic* sml,  getLogicsByDestination(mast))
    {
        try {
            ((DefaultSignalMastLogic*)sml)->useLayoutEditor(false, mast);
        } catch (JmriException e){
            log->error("Error occured while trying to disable layout editor use " + e.getMessage());
        }
    }
}
/**
 * By default, register this manager to store as configuration
 * information.  Override to change that.
 **/
/*protected*/ void DefaultSignalMastLogicManager::registerSelf() {
     if (static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))!=NULL) {
        static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerConfig(this, Manager::SIGNALMASTLOGICS);
        log->debug("register for config");
    }
}

// abstract methods to be extended by subclasses
// to free resources when no longer used
/*public*/ void DefaultSignalMastLogicManager::dispose() {
    if (static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))!= NULL)
        static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->deregister(this);
    signalMastLogic.clear();
}

/**
 * Used to initialise all the signalmast logics. primarily used after loading.
 */
/*public*/ void DefaultSignalMastLogicManager::initialise(){
    for(int i = 0; i <signalMastLogic.size(); i++){
        ((DefaultSignalMastLogic*)signalMastLogic.at(i))->initialise();
    }
}

/*public*/ NamedBean* DefaultSignalMastLogicManager::getBeanBySystemName(QString /*systemName*/) const{
    throw  UnsupportedOperationException("Not supported yet.");
}

/*public*/ NamedBean* DefaultSignalMastLogicManager::getBeanByUserName(QString /*userName*/)const{
    throw  UnsupportedOperationException("Not supported yet.");
}

/*public*/ NamedBean* DefaultSignalMastLogicManager::getNamedBean(QString /*name*/)const{
    throw  UnsupportedOperationException("Not supported yet.");
}

//@Deprecated
///*public*/ char systemLetter() {
//    throw new UnsupportedOperationException("Not supported yet.");
//}

/*public*/ QString DefaultSignalMastLogicManager::getSystemPrefix() const {
    throw new UnsupportedOperationException("Not supported yet.");
}

/*public*/ char DefaultSignalMastLogicManager::typeLetter()const  {
    throw new UnsupportedOperationException("Not supported yet.");
}

/*public*/ QString DefaultSignalMastLogicManager::makeSystemName(QString /*s*/)const {
    throw new UnsupportedOperationException("Not supported yet.");
}

/*public*/ QStringList DefaultSignalMastLogicManager::getSystemNameArray() {
    throw new UnsupportedOperationException("Not supported yet.");
}

/*public*/ QStringList DefaultSignalMastLogicManager::getSystemNameList()
{
    throw new UnsupportedOperationException("Not supported yet.");
}

/** {@inheritDoc} */
//@Override
///*public*/ QSet<NamedBean*> DefaultSignalMastLogicManager::getNamedBeanSet(){
//    throw new UnsupportedOperationException("Not supported yet.");
//}
/*public*/ /*synchronized*/ void DefaultSignalMastLogicManager::addPropertyChangeListener(PropertyChangeListener* l) {
    QMutexLocker locker(&mutex);

    pcs->addPropertyChangeListener(l);
}
/*public*/ /*synchronized*/ void DefaultSignalMastLogicManager::removePropertyChangeListener(PropertyChangeListener* l) {
    QMutexLocker locker(&mutex);
    pcs->removePropertyChangeListener(l);
}
/*protected*/ void DefaultSignalMastLogicManager::firePropertyChange(QString p, QVariant old, QVariant n)
{
    //pcs->firePropertyChange(p,old,n);
    emit propertyChange(new PropertyChangeEvent((QObject*)this, p, old, n));
}

/*public*/ void DefaultSignalMastLogicManager::Register(NamedBean* /*n*/) const{
    throw  UnsupportedOperationException("Not supported yet.");
}

/*public*/ void DefaultSignalMastLogicManager::deregister(NamedBean* /*n*/) const{
    throw  UnsupportedOperationException("Not supported yet.");
}

/*public*/ long DefaultSignalMastLogicManager::getSignalLogicDelay(){ return signalLogicDelay; }
/*public*/ void DefaultSignalMastLogicManager::setSignalLogicDelay(long l){ signalLogicDelay=l; }



/**
* Discover valid destination signalmasts for a given source signal on a
* given layout editor panel.
* @param source Source SignalMast
* @param layout Layout Editor panel to check.
*/
/*public*/ void DefaultSignalMastLogicManager::discoverSignallingDest(SignalMast* source, LayoutEditor* layout) throw (JmriException)
{
 firePropertyChange("autoSignalMastGenerateStart", QVariant(), QVariant(source->getDisplayName()));

 QHash<NamedBean*, QList<NamedBean*> > validPaths =  QHash<NamedBean*, QList<NamedBean*> >();
 LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 if(!lbm->isAdvancedRoutingEnabled())
 {
  //log.debug("advanced routing not enabled");
  throw new JmriException("advanced routing not enabled");
 }
 if(!lbm->routingStablised())
 {
  //throw new JmriException("routing not stablised");
     log->error(tr("routing not stabilised"));
 }
 try
 {
  validPaths.insert((NamedBean*)source, lbm->getLayoutBlockConnectivityTools()->discoverPairDest(source, layout, "SignalMast", LayoutBlockConnectivityTools::MASTTOMAST));
 }
 catch (JmriException e)
 {
   throw e;
 }

 QListIterator<NamedBean*> en (validPaths.keys());
 while (en.hasNext())
 {
  SignalMast* key = (SignalMast*)en.next();
  SignalMastLogic* sml = getSignalMastLogic(key);
  if(sml==NULL)
  {
   sml=newSignalMastLogic(key);
  }
  QList<NamedBean*> validDestMast = validPaths.value(key);
  for(int i = 0; i<validDestMast.size(); i++)
  {
   if(!((DefaultSignalMastLogic*)sml)->isDestinationValid((SignalMast*)validDestMast.value(i)))
   {
    try
    {
     ((DefaultSignalMastLogic*)sml)->setDestinationMast((SignalMast*)validDestMast.value(i));
     ((DefaultSignalMastLogic*)sml)->useLayoutEditorDetails(true, true, (SignalMast*)validDestMast.at(i));
     ((DefaultSignalMastLogic*)sml)->useLayoutEditor(true, (SignalMast*)validDestMast.value(i));
    }
    catch (JmriException e)
    {
     //log.debug("We shouldn't get an exception here");
     log->error("Exception found " + e.getMessage());
     throw e;
    }
   }
  }
 }
 firePropertyChange("autoSignalMastGenerateComplete", QVariant(), QVariant(source->getDisplayName()));
}

/**
* Discover all possible valid source and destination signalmasts past pairs
* on all layout editor panels.
*/

/*public*/ void DefaultSignalMastLogicManager::automaticallyDiscoverSignallingPairs() throw (JmriException)
{
 runWhenStablised=false;
 LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 if(!lbm->isAdvancedRoutingEnabled()){
  throw JmriException("advanced routing not enabled");
 }
 if(!lbm->routingStablised()){
  runWhenStablised=true;
  log->info("Layout block routing has not yet stabilsed discovery will happen once it has");
  return;
 }

 QHash<NamedBean*, QList<NamedBean*> > validPaths = lbm->getLayoutBlockConnectivityTools()->discoverValidBeanPairs(NULL, "SignalMast",LayoutBlockConnectivityTools::MASTTOMAST);
 QListIterator<NamedBean*> en ( validPaths.keys());
 firePropertyChange("autoGenerateUpdate", "", ("Found " + QString::number(validPaths.size()) + " masts as sources for logic"));
 for (NamedBean* nb : ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getNamedBeanSet()) {
     nb->removeProperty("intermediateSignal");
 }

 while (en.hasNext()) {
  SignalMast* key = (SignalMast*)en.next();
  SignalMastLogic* sml = getSignalMastLogic(key);
  if(sml==NULL){
   sml=newSignalMastLogic(key);
  }
  QList<NamedBean*> validDestMast = validPaths.value(key);
  for(int i = 0; i<validDestMast.size(); i++){
   if(!sml->isDestinationValid((SignalMast*)validDestMast.value(i))){
    try{
     ((DefaultSignalMastLogic*)sml)->setDestinationMast((SignalMast*)validDestMast.value(i));
     ((DefaultSignalMastLogic*)sml)->useLayoutEditorDetails(true, true, (SignalMast*)validDestMast.value(i));
     ((DefaultSignalMastLogic*)sml)->useLayoutEditor(true, (SignalMast*)validDestMast.value(i));
    } catch (JmriException ex){
     //log.debug("we shouldn't get an exception here!");
     log->debug(ex.getMessage());
    }
   }
  }
  if (sml->getDestinationList().size() == 1 && sml->getAutoTurnouts(sml->getDestinationList().at(0)).isEmpty()) {
      key->setProperty("intermediateSignal", true);
  }

 }
 initialise();
 firePropertyChange("autoGenerateComplete", QVariant(), QVariant());
}

/*public*/ void DefaultSignalMastLogicManager::generateSection()
{
    SectionManager* sm = (SectionManager*)InstanceManager::getDefault("SectionManager");
    foreach (NamedBean* nb, *sm->getNamedBeanList()) {
        if (((Section*) nb)->getSectionType() == Section::SIGNALMASTLOGIC) {
            nb->removeProperty("intermediateSection");
        }
        nb->removeProperty("forwardMast");
    }
    foreach (SignalMastLogic* sml, getSignalMastLogicList()) {
        LayoutBlock* faceLBlock = sml->getFacingBlock();
        if (faceLBlock != NULL) {
            bool sourceIntermediate = false;
            if (sml->getSourceMast()->getProperty("intermediateSignal") != QVariant()) {
                sourceIntermediate = ( sml->getSourceMast()->getProperty("intermediateSignal")).toBool();
            }
            foreach (SignalMast* destMast, sml->getDestinationList()) {
                if (sml->getAutoBlocksBetweenMasts(destMast).size() != 0) {
                    Section* sec = sm->createNewSection(sml->getSourceMast()->getDisplayName() + ":" + destMast->getDisplayName());
                    if (sec == NULL) {
                        //A Section already exists, lets grab it and check that it is one used with the SML, if so carry on using that.
                        sec = sm->getSection(sml->getSourceMast()->getDisplayName() + ":" + destMast->getDisplayName());
                        if ( sec->getSectionType() != Section::SIGNALMASTLOGIC) {
                            break;
                        }
                    } else {
                         sec->setSectionType(Section::SIGNALMASTLOGIC);
                        //Auto running requires forward/reverse sensors, but at this stage SML does not support that, so just create dummy internal ones for now.
                        Sensor* sen = InstanceManager::sensorManagerInstance()->provideSensor("IS:" +  sec->getSystemName() + ":forward");
                        sen->setUserName( sec->getSystemName() + ":forward");

                        sen = InstanceManager::sensorManagerInstance()->provideSensor("IS:" +  sec->getSystemName() + ":reverse");
                        sen->setUserName( sec->getSystemName() + ":reverse");
                        sec->setForwardBlockingSensorName( sec->getSystemName() + ":forward");
                        sec->setReverseBlockingSensorName( sec->getSystemName() + ":reverse");
                    }
                    sml->setAssociatedSection(sec, destMast);
                    sec->setProperty("forwardMast", destMast->getDisplayName());
                    bool destIntermediate = false;
                    if (destMast->getProperty("intermediateSignal") != QVariant()) {
                        destIntermediate = (destMast->getProperty("intermediateSignal")).toBool();
                    }
                    if (sourceIntermediate || destIntermediate) {
                         sec->setProperty("intermediateSection", true);
                    } else {
                         sec->setProperty("intermediateSection", false);
                    }
                    //Not 100% sure about this for now so will comment out
                    //sml.addSensor( sec->getSystemName()+":forward", Sensor.INACTIVE, destMast);
                }
            }
        } else {
            log->info("No facing block found " + sml->getSourceMast()->getDisplayName());
        }
    }
}
/** {@inheritDoc} */
//@Override
/*public*/ QString DefaultSignalMastLogicManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "SignalMastLogics" : "SignalMastLogic");
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ /*Class<SignalMastLogic>*/QString DefaultSignalMastLogicManager::getNamedBeanClass() const {
    return "SignalMastLogic";
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ int DefaultSignalMastLogicManager::setupSignalMastsDirectionSensors() {
    int errorCount = 0;
    for (SignalMastLogic* sml : getSignalMastLogicList()) {
        errorCount += sml->setupDirectionSensors();
    }
    return errorCount;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void DefaultSignalMastLogicManager::removeSignalMastsDirectionSensors() {
    for (SignalMastLogic* sml : getSignalMastLogicList()) {
        sml->removeDirectionSensors();
    }
    return;
}
/*private*/ /*static*/ SignalSpeedMap* DefaultSignalMastLogicManager::_speedMap = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"));
