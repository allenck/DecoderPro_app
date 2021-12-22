#include "pointdetails.h"
#include "source.h"
#include "destinationpoints.h"
#include "../LayoutEditor/layouteditor.h"
#include "abstractsensor.h"
#include "signalmast.h"
#include "sensor.h"
#include "signalhead.h"
#include "defaultsignalmastmanager.h"
#include "abstractsignalheadmanager.h"
#include <QThread>
#include <QVector>
#include "panelmenu.h"
#include "layouteditorfinditems.h"
#include <QHash>
#include "positionablepoint.h"

//PointDetails::PointDetails(QObject *parent) :
//    QObject(parent)
//{
//}
///*public*/ class PointDetails {
    //May want to look at putting a listener on the refLoc to listen to updates to blocks, signals and sensors attached to it

    /*static*/ int PointDetails::nxButtonTimeout = 10;

/*public*/ PointDetails::PointDetails(LayoutBlock* facing, QList<LayoutBlock*> protecting, QObject *parent): QObject(parent)
{
    panel = NULL;
    routeToSet = false;
    routeFromSet = false;
    destinations = new QHash<DestinationPoints*, Source*>() ;//(5);
    nxButtonState = EntryExitPairs::NXBUTTONINACTIVE;
    extendedtime = false;
    log = new Logger("PointDetails");
    pcs = new PropertyChangeSupport(this);
    nxButtonListener = new NxButtonListener(this);//new PropertyChangeListener(this);

    this->facing=facing;
    protectingBlocks = protecting;
    if(protectingBlocks.isEmpty())
     log->debug(tr("layoutBlock %1 protecting is empty.").arg(facing->getDisplayName()));

    setObjectName(facing->getUserName());
}

LayoutBlock* PointDetails::getFacing()
{
 return facing;
}

QList<LayoutBlock *> PointDetails::getProtecting()
{
 return protectingBlocks;
}

//This might be better off a ref to the source pointdetail.
void PointDetails::setRouteTo(bool boo){
    routeToSet = boo;
}

void PointDetails::setRouteFrom(bool boo){
    routeFromSet = boo;
}

/*public*/ void PointDetails::setPanel(LayoutEditor* panel){
    this->panel = panel;
 // find the panel that actually contains this sensor, default to the supplied panel
 for (LayoutEditor* layout : *((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList())
 {
  for (SensorIcon* si : *layout->sensorList)
  {
   if (sensor == si->getNamedBean()) {
       this->panel = layout;
       return;
   }
  }
 }
}

void PointDetails::setSensor(Sensor* sen)
{
 if(sensor==sen)
     return;
 if(sensor!=NULL)
 {
     sensor->removePropertyChangeListener(nxButtonListener);
//        AbstractSensor* s = (AbstractSensor*)sensor;
//        disconnect(s, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(nxButtonListener(PropertyChangeEvent*)));
 }
 sensor = sen;
 if(sensor!=NULL)
 {
  sensor->addPropertyChangeListener(nxButtonListener);
//     AbstractSensor* s = (AbstractSensor*)sensor;
//     connect(s, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(nxButtonListener(PropertyChangeEvent*)));
 }

}

void PointDetails::addSensorList(){
    sensor->addPropertyChangeListener(nxButtonListener);
//    AbstractSensor* s = (AbstractSensor*)sensor;
//    connect(s, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(nxButtonListener(PropertyChangeEvent*)));
}

void PointDetails::removeSensorList(){
    sensor->removePropertyChangeListener(nxButtonListener);
//    AbstractSensor* s = (AbstractSensor*)sensor;
//    disconnect(s, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(nxButtonListener(PropertyChangeEvent*)));
}

//Sensor getSensor() { return sensor; }

//protected PropertyChangeListener nxButtonListener = new PropertyChangeListener() {
//First off if we were inactive, and now active
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
/*private*/ void PointDetails::nxButtonStateChange(PropertyChangeEvent* e)
{
    if(e->getPropertyName()!=("KnownState"))
        return;
    int now = e->getNewValue().toInt();
    int old = e->getOldValue().toInt();

    if((old==Sensor::UNKNOWN) || (old==Sensor::INCONSISTENT)){
        setButtonState(EntryExitPairs::NXBUTTONINACTIVE);
        return;
    }

    DestinationPoints* destPoint = NULL;

    //for(Entry<DestinationPoints, Source> dp: destinations->entrySet()){
    QHashIterator<DestinationPoints*, Source*> dp(*destinations);
    while(dp.hasNext())
    {
     dp.next();
        destPoint = dp.key();
        if(destPoint->isEnabled() && dp.value()->getPoint()->getNXState()==EntryExitPairs::NXBUTTONSELECTED){
            setButtonState(EntryExitPairs::NXBUTTONSELECTED);
            destPoint->activeBean(false);
            return;
        }
    }

    if(sourceRoute!=NULL)
    {
     if(now==Sensor::ACTIVE && getNXState()==EntryExitPairs::NXBUTTONINACTIVE)
     {
      setButtonState(EntryExitPairs::NXBUTTONSELECTED);
      //for(Entry<PointDetails, DestinationPoints> en : sourceRoute->pointToDest.entrySet()){
      QHashIterator<PointDetails*, DestinationPoints*> en(*sourceRoute->pointToDest);
      while(en.hasNext())
      {
       en.next();
                //Sensor sen = getSensorFromPoint(en.getKey().getPoint());
                //Set a time out on the source sensor, so that if its state hasn't been changed, then we will clear it out.
                if(en.value()->isEnabled() && !en.value()->getUniDirection()){
                    if(en.key()->getNXState()==EntryExitPairs::NXBUTTONSELECTED){
                        sourceRoute->activeBean(en.value(), true);
                    }
                }
            }
        } else if (now==Sensor::INACTIVE && getNXState()==EntryExitPairs::NXBUTTONSELECTED){
            //sensor inactive, nxbutton state was selected, going to set back to inactive - ie user cancelled button
            setButtonState(EntryExitPairs::NXBUTTONINACTIVE);
        } else if (now==Sensor::INACTIVE && getNXState()==EntryExitPairs::NXBUTTONACTIVE){
            //Sensor gone inactive, while nxbutton was selected - potential start of user either clear route or setting another
            setButtonState(EntryExitPairs::NXBUTTONSELECTED);
            //for(Entry<PointDetails, DestinationPoints> en : sourceRoute->pointToDest.entrySet())
            QHashIterator<PointDetails*, DestinationPoints*> en(*sourceRoute->pointToDest);
            while(en.hasNext())
            {
                en.next();
                //Sensor sen = getSensorFromPoint(en.getKey().getPoint());
                //Set a time out on the source sensor, so that if its state hasn't been changed, then we will clear it out.
                if(en.value()->isEnabled() && !en.value()->getUniDirection()){
                    if(en.key()->getNXState()==EntryExitPairs::NXBUTTONSELECTED){
                        sourceRoute->activeBean(en.value(), false);
                    }
                }
            }
        }
    } else if (destPoint!=NULL){
        //Button set as a destination but has no source, it has had a change in state
        if(now==Sensor::ACTIVE){
            //State now is Active will set flashing
            setButtonState(EntryExitPairs::NXBUTTONSELECTED);
        } else if(getNXState()==EntryExitPairs::NXBUTTONACTIVE){
            //Sensor gone inactive while it was previosly active
            setButtonState(EntryExitPairs::NXBUTTONSELECTED);
        } else if(getNXState()==EntryExitPairs::NXBUTTONSELECTED){
            //Sensor gone inactive while it was previously selected therefore will cancel
            setButtonState(EntryExitPairs::NXBUTTONINACTIVE);
        }
    }
}
//    };

void PointDetails::setSignalMast(SignalMast* mast) {
    signalmast = mast;
}

void PointDetails::setSource(Source* src){
    if(sourceRoute==src)
        return;
    sourceRoute=src;
}

void PointDetails::setDestination(DestinationPoints* srcdp, Source* src)
{
 if(!destinations->contains(srcdp)){
     destinations->insert(srcdp, src);
 }
}

void PointDetails::removeDestination(DestinationPoints* srcdp){
    destinations->remove(srcdp);
    if(sourceRoute==NULL && destinations->size()==0){
        stopFlashSensor();
        sensor->removePropertyChangeListener(nxButtonListener);
//        AbstractSensor* s = (AbstractSensor*)sensor;
//        disconnect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(nxButtonListener(PropertyChangeEvent*)));
        setSensor(NULL);
    }
}

void PointDetails::removeSource(Source* /*src*/){
    sourceRoute=NULL;
    if(destinations->size()==0) {
        stopFlashSensor();
        sensor->removePropertyChangeListener(nxButtonListener);
//        AbstractSensor* s = (AbstractSensor*)sensor;
//        disconnect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(nxButtonListener(PropertyChangeEvent*)));
        setSensor(NULL);
    }
}


void PointDetails::setButtonState(int state){
    setNXButtonState(state);
}

void PointDetails::setNXState(int state){
    if(state==nxButtonState)
        return;
    if(state==EntryExitPairs::NXBUTTONSELECTED) {
        nxButtonTimeOut();
        flashSensor();
    } else {
        cancelNXButtonTimeOut();
        stopFlashSensor();
    }
    nxButtonState=state;
}

int PointDetails::getNXState(){
    return nxButtonState;
}

SignalMast* PointDetails::getSignalMast()
{
 return signalmast;
}

void PointDetails::setSignalHead(SignalHead* head){
    signalhead = head;
}

SignalHead* PointDetails::getSignalHead()
{
 return signalhead;
}

/*public*/ LayoutEditor* PointDetails::getPanel()
{
 return panel;
}

/*public*/ void PointDetails::setRefObject(NamedBean* refObs){
 QList<LayoutEditor*>* panels = static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->
         getLayoutEditorPanelList();
 for (LayoutEditor* pnl : *panels) {
     if (refLoc == nullptr) {
         setRefObjectByPanel(refObs, pnl);
     }
 }
}

/*public*/ void PointDetails::setRefObjectByPanel(NamedBean* refObs, LayoutEditor* pnl)
{
 refObj = refObs;
 if (pnl != nullptr && refObj != nullptr)
 {
     if (static_cast<SignalMast*>(refObj) || static_cast<Sensor*>(refObj)) {
         //String mast = ((SignalMast)refObj).getUserName();
         refLoc = pnl->getFinder()->findPositionablePointByEastBoundBean(refObj);
         if (refLoc == nullptr) {
             refLoc = pnl->getFinder()->findPositionablePointByWestBoundBean(refObj);
         }
         if (refLoc == nullptr) {
             refLoc = pnl->getFinder()->findLayoutTurnoutByBean(refObj);
         }
         if (refLoc == nullptr) {
             refLoc = pnl->getFinder()->findLevelXingByBean(refObj);
         }
         if (refLoc == nullptr) {
             refLoc = pnl->getFinder()->findLayoutSlipByBean(refObj);
         }
         if (static_cast<Sensor*>(refObj)) {
             setSensor((Sensor*) refObj);
         }
     } else if (static_cast<SignalHead*>(refObj)) {
         QString signal = ((SignalHead*) refObj)->getDisplayName();
         refLoc = pnl->getFinder()->findPositionablePointByEastBoundSignal(signal);
         if (refLoc == nullptr) {
             refLoc = pnl->getFinder()->findPositionablePointByWestBoundSignal(signal);
         }
     }
 }
// if (refLoc != nullptr) {
//     if (qobject_cast<PositionablePoint*>(refLoc)) {
//         //((PositionablePoint)refLoc).addPropertyChangeListener(this);
//     } else if (qobject_cast<LayoutTurnout*>(refLoc)) {  //<== this includes LayoutSlips
//         //((LayoutTurnout)refLoc).addPropertyChangeListener(this);
//     } else if (qobject_cast<LevelXing*>(refLoc)) {
//         //((LevelXing)refLoc).addPropertyChangeListener(this);
//     }
// }
 //With this set ref we can probably add a listener to it, so that we can detect when a change to the point details takes place
}

/*public*/ NamedBean* PointDetails::getRefObject()
{
 return refObj;
}

/*public*/ QObject* PointDetails::getRefLocation()
{
 return refLoc;
}

//LayoutEditor getLayoutEditor() { return panel; }

bool PointDetails::isRouteToPointSet()
{
 return routeToSet;
}

bool PointDetails::isRouteFromPointSet()
{
 return routeFromSet;
}

/*public*/ QString PointDetails::getDisplayName()
{
 if(sensor!=NULL)
 {
  QString description = sensor->getDisplayName();
  if(signalmast!=NULL){
      description = description + " (" + signalmast->getDisplayName() +")";
  }
  return description;
 }

 //if(refObj instanceof SignalMast)
 if(static_cast<SignalMast*>(refObj)!=NULL)
 {
  return ((SignalMast*)refObj)->getDisplayName();
 }
 else
     //if (refObj instanceof Sensor)
     if(qobject_cast<Sensor*>(refLoc)!=NULL)
 {
     return ((Sensor*)refObj)->getDisplayName();
 }
     //else if (refObj instanceof SignalHead)
 if(qobject_cast<SignalHead*>(refLoc)!=NULL)
     {
     return ((SignalHead*)refObj)->getDisplayName();
 }
 return "no display name";
}

void PointDetails::nxButtonTimeOut(){
    if((nxButtonTimeOutThr!=NULL) && (nxButtonTimeOutThr->isRunning())){
        return;
    }
    extendedtime = true;
    ButtonTimeOut* t = new ButtonTimeOut(this);
    nxButtonTimeOutThr = new QThread(t);
    nxButtonTimeOutThr->setObjectName( "NX Button Timeout " + getSensor()->getDisplayName());

    nxButtonTimeOutThr->start();
}

void PointDetails::cancelNXButtonTimeOut(){
    if(nxButtonTimeOutThr!=NULL)
        nxButtonTimeOutThr->exit();

}


/*public*/ void PointDetails::flashSensor(){
    foreach(SensorIcon* si, *getPanel()->sensorList){
     if(qobject_cast<SensorIcon*>(si))
     {
        if(si->getSensor()==getSensor()){
            si->flashSensor(2, Sensor::ACTIVE, Sensor::INACTIVE);
        }
     }
    }
}

/*public*/ void PointDetails::stopFlashSensor(){
    foreach(SensorIcon* si, *getPanel()->sensorList)
    {
     if(qobject_cast<SensorIcon*>(si))
     {
        if(si->getSensor()==getSensor()){
            si->stopFlash();
        }
     }
    }
}

/*synchronized*/ /*public*/ void PointDetails::setNXButtonState(int state)
{
    QMutexLocker locker(&mutex);
    if(getSensor()==NULL)
        return;
    if(state==EntryExitPairs::NXBUTTONINACTIVE){
        //If a route is set to or from out point then we need to leave/set the sensor to ACTIVE
        if(isRouteToPointSet()){
            state=EntryExitPairs::NXBUTTONACTIVE;
        } else if(isRouteFromPointSet()){
            state=EntryExitPairs::NXBUTTONACTIVE;
        }
    }
    setNXState(state);
    int sensorState = Sensor::UNKNOWN;
    switch(state){
        case EntryExitPairs::NXBUTTONINACTIVE : sensorState = Sensor::INACTIVE;
                                                break;
    case EntryExitPairs::NXBUTTONACTIVE   : sensorState = Sensor::ACTIVE;
                                                break;
    case EntryExitPairs::NXBUTTONSELECTED : sensorState = Sensor::ACTIVE;
                                                break;
    default                             : sensorState = Sensor::UNKNOWN;
                                                break;
    }

    //Might need to clear listeners at the stage and then reapply them after.
    if(((AbstractSensor*)getSensor())->getKnownState()!=sensorState){
        removeSensorList();
        try {
            ((AbstractSensor*)getSensor())->setKnownState(sensorState);
        } catch (JmriException ex){
            log->error(ex.getMessage());
        }
        addSensorList();
    }
}

Sensor* PointDetails::getSensor(){
    if (getRefObject()==NULL)
        return NULL;
    if((getPanel()!=NULL) && (!getPanel()->isEditable()) && (sensor!=NULL))
        return sensor;

    //if (getRefObject() instanceof Sensor)
    if(static_cast<Sensor*>(getRefObject())!= NULL)
        return (Sensor*)getRefObject();

    QObject* objLoc = getRefLocation();
    NamedBean* objRef = getRefObject();
    SignalMast* mast=nullptr;
    SignalHead* head=nullptr;
    QString username = "";
    QString systemname = "";
    Sensor* foundSensor = nullptr;
    //if(objRef instanceof SignalMast)
    if(static_cast<SignalMast*>(objRef)!= NULL)
    {
        mast = (SignalMast*)objRef;
    }
    //if(objRef instanceof SignalHead)
    if(static_cast<SignalHead*>(objRef)!= NULL)
    {
        head = (SignalHead*)objRef;
        username = head->getUserName();
        systemname = head->getSystemName();
    }
    SensorManager* sm = InstanceManager::sensorManagerInstance();
    //if (objLoc instanceof PositionablePoint)
    if(qobject_cast<PositionablePoint*>(objLoc)!= NULL)
    {
     PositionablePoint* p = (PositionablePoint*)objLoc;
     if(mast!=nullptr) {
      if (p->getEastBoundSignalMast() == objRef) {
          foundSensor = p->getEastBoundSensor();
      } else if (p->getWestBoundSignalMast() == objRef) {
          foundSensor = p->getWestBoundSensor();
      }
     }
     else if(head!=nullptr) {
      if ((p->getEastBoundSignal() == (username))
              || p->getEastBoundSignal() == (systemname)) {
          foundSensor = p->getEastBoundSensor();
      } else if ((p->getWestBoundSignal() == (username))
              || p->getWestBoundSignal() == (systemname)) {
          foundSensor = p->getWestBoundSensor();
      }
     }
    }
    else
        //if (objLoc instanceof LayoutTurnout)
        if(qobject_cast<LayoutSlip*>(objLoc)!= NULL)
        {
        LayoutSlip* sl = (LayoutSlip*)objLoc;
        if(mast!=NULL)
        {
         if (sl->getSignalAMast() == objRef)
         {
             foundSensor = sl->getSensorA();
         } else if (sl->getSignalBMast() == objRef) {
             foundSensor = sl->getSensorB();
         } else if (sl->getSignalCMast() == objRef) {
             foundSensor = sl->getSensorC();
         } else if (sl->getSignalDMast() == objRef) {
             foundSensor = sl->getSensorD();
         }
        }
        if(head != NULL){
         if ((sl->getSignalA1Name() == (username)) || (sl->getSignalA1Name() == (systemname))) {
             foundSensor = sm->getSensor(sl->getSensorAName());
         } else if ((sl->getSignalB1Name() == (username)) || (sl->getSignalB1Name() == (systemname))) {
             foundSensor = sm->getSensor(sl->getSensorBName());
         } else if ((sl->getSignalC1Name() == (username)) || (sl->getSignalC1Name() == (systemname))) {
             foundSensor = sm->getSensor(sl->getSensorCName());
         } else if ((sl->getSignalD1Name() == (username)) || (sl->getSignalD1Name() == (systemname))) {
             foundSensor = sm->getSensor(sl->getSensorDName());
         }
        }
    }
     else //note: you have to do this after LayoutSlip
         // because LayoutSlip extends LayoutTurnout
         // (So a LayoutSlip would be an instance of LayoutTurnout.)
         if (qobject_cast<LayoutTurnout*>(objLoc)) {  //<== this includes LayoutSlips
             LayoutTurnout* t = (LayoutTurnout*) objLoc;
             if (mast != nullptr) {
                 if (t->getSignalAMast() == objRef) {
                     foundSensor = t->getSensorA();
                 } else if (t->getSignalBMast() == objRef) {
                     foundSensor = t->getSensorB();
                 } else if (t->getSignalCMast() == objRef) {
                     foundSensor = t->getSensorC();
                 } else if (t->getSignalDMast() == objRef) {
                     foundSensor = t->getSensorD();
                 }
             }
             if (head != nullptr) {
                 if (( t->getSignalA1Name() == (username)) || ( t->getSignalA1Name() == (systemname))) {
                     foundSensor =  t->getSensorA();
                 } else if (( t->getSignalA2Name() == (username)) || ( t->getSignalA2Name() == (systemname))) {
                     foundSensor =  t->getSensorA();
                 } else if (( t->getSignalA3Name() == (username)) || ( t->getSignalA3Name() == (systemname))) {
                     foundSensor =  t->getSensorA();
                 } else if (( t->getSignalB1Name() == (username)) || ( t->getSignalB1Name() == (systemname))) {
                     foundSensor =  t->getSensorB();
                 } else if (( t->getSignalB2Name() == (username)) || ( t->getSignalB2Name() == (systemname))) {
                     foundSensor =  t->getSensorB();
                 } else if (( t->getSignalC1Name() == (username)) || ( t->getSignalC1Name() == (systemname))) {
                     foundSensor =  t->getSensorC();
                 } else if (( t->getSignalC2Name() == (username)) || ( t->getSignalC2Name() == (systemname))) {
                     foundSensor =  t->getSensorC();
                 } else if (( t->getSignalD1Name() == (username)) || ( t->getSignalD1Name() == (systemname))) {
                     foundSensor =  t->getSensorD();
                 } else if (( t->getSignalD2Name() == (username)) || ( t->getSignalD2Name() == (systemname))) {
                     foundSensor =  t->getSensorD();
                 }
             }
    }
    else if (qobject_cast<LevelXing*>(objLoc))
    {
     LevelXing* x = (LevelXing*) objLoc;
     if (mast != nullptr) {
         if ( x->getSignalAMast() == objRef) {
             foundSensor =  x->getSensorA();
         } else if ( x->getSignalBMast() == objRef) {
             foundSensor =  x->getSensorB();
         } else if ( x->getSignalCMast() == objRef) {
             foundSensor =  x->getSensorC();
         } else if ( x->getSignalDMast() == objRef) {
             foundSensor =  x->getSensorD();
         }
     }
     if(head!=NULL){
      if ((x->getSignalAName() == (username)) || (x->getSignalAName() == (systemname))) {
          foundSensor = x->getSensorA();
      } else if ((x->getSignalBName() == (username)) || (x->getSignalBName() == (systemname))) {
          foundSensor = x->getSensorB();
      } else if ((x->getSignalCName() == (username)) || (x->getSignalCName() == (systemname))) {
          foundSensor = x->getSensorC();
      } else if ((x->getSignalDName() == (username)) || (x->getSignalDName() == (systemname))) {
          foundSensor = x->getSensorD();
      }
     }
    }
    setSensor(foundSensor);
    return foundSensor;
}

NamedBean* PointDetails::getSignal(){
    if((getPanel()!=NULL) && (!getPanel()->isEditable()) && (getSignalMast()!=NULL))
        return getSignalMast();
    if((getPanel()!=NULL) && (!getPanel()->isEditable()) && (getSignalHead()!=NULL))
        return getSignalHead();
    SignalMastManager* sm = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"));
    SignalHeadManager* sh = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"));
    NamedBean* signal = NULL;

    if(getRefObject()==NULL) {
        log->error("Signal not found at point");
        return NULL;
    }
    else
        //if (getRefObject() instanceof SignalMast)
        if(static_cast<SignalMast*>(getRefObject())!= NULL)
        {
        signal =  getRefObject();
        setSignalMast(((SignalMast*)getRefObject()));
        return signal;
    }
        else
            //if (getRefObject() instanceof SignalHead)
       if(static_cast<SignalHead*>(getRefObject())!= NULL)

        {
        signal =  getRefObject();
        setSignalHead(((SignalHead*)getRefObject()));
        return signal;
    }


    Sensor* sen = (Sensor*) getRefObject();
    log->debug("looking at Sensor " + sen->getDisplayName());
    QString username = sen->getUserName();
    QString systemname = sen->getSystemName();
    //if(getRefLocation() instanceof PositionablePoint)
    if(qobject_cast<PositionablePoint*>(getRefLocation())!= NULL)
    {
        PositionablePoint* p = (PositionablePoint*)getRefLocation();
        if (p->getEastBoundSensor() == sen)
        {
         if (p->getEastBoundSignalMast() != nullptr) {
             signal = p->getEastBoundSignalMast();
         } else if (p->getEastBoundSignal()!=("")) {
             signal = sh->getSignalHead(p->getEastBoundSignal());
         }
     } else if (p->getWestBoundSensor() == sen) {
         if (p->getWestBoundSignalMast() != nullptr) {
             signal = p->getWestBoundSignalMast();
         } else if (p->getWestBoundSignal()!=("")) {
             signal = sh->getSignalHead(p->getWestBoundSignal());
         }
     }
    }
    else
        //if(getRefLocation() instanceof LayoutTurnout)
        if(qobject_cast<LayoutTurnout*>(getRefLocation())!= NULL)
        {
        LayoutTurnout* t = (LayoutTurnout*)getRefLocation();
        if (t->getSensorA() == sen)
        {
         if (t->getSignalAMast() != nullptr) {
             signal = t->getSignalAMast();
         } else if (t->getSignalA1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalA1Name());
         }
     } else if (t->getSensorB() == sen) {
         if (t->getSignalBMast() != nullptr) {
             signal = t->getSignalBMast();
         } else if (t->getSignalB1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalB1Name());
         }
     } else if (t->getSensorC() == sen) {
         if (t->getSignalCMast() != nullptr) {
             signal = t->getSignalCMast();
         } else if (t->getSignalC1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalC1Name());
         }
     } else if (t->getSensorD() == sen) {
         if (t->getSignalDMast() != nullptr) {
             signal = t->getSignalDMast();
         } else if (t->getSignalD1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalD1Name());
         }
     }
    }

    else
            //if(getRefLocation() instanceof LevelXing)
    if(qobject_cast<LevelXing*>(getRefLocation())!= NULL)
    {
        LevelXing* x = (LevelXing*)getRefLocation();
        if((x->getSensorA() == sen))
        {
         if(x->getSignalAMast() !=nullptr)
             signal =  x->getSignalAMast();
         else if(x->getSignalAName()!=(""))
             signal =  sh->getSignalHead(x->getSignalAName());
        }
        else if(x->getSensorB() == sen)
        {
          if(x->getSignalBMast() !=nullptr)
           signal =   x->getSignalBMast();
          else if(x->getSignalBName()!=(""))
           signal =  sh->getSignalHead(x->getSignalBName());
        }
        else if(x->getSensorC() == sen)
        {
            if(x->getSignalCMast() !=nullptr)
                signal =   x->getSignalCMast();
            else if(x->getSignalCName()!=(""))
                signal =  sh->getSignalHead(x->getSignalCName());
        }
         else if(x->getSensorD() == sen)
         {
            if(x->getSignalDMast()!=nullptr)
                signal =   x->getSignalDMast();
            else if(x->getSignalDName()!=(""))
                signal =  sh->getSignalHead(x->getSignalDName());
         }
    }
    else//note: you have to do this after LayoutSlip
     // because LayoutSlip extends LayoutTurnout
     // (So a LayoutSlip would be an instance of LayoutTurnout.)
     if (qobject_cast<LayoutTurnout*>(getRefLocation()))
     {  //<== this includes LayoutSlips
        LayoutTurnout* t = (LayoutTurnout*)getRefLocation();
        if (t->getSensorA() == sen)
        {
         if (t->getSignalAMast() != nullptr) {
             signal = t->getSignalAMast();
         } else if (t->getSignalA1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalA1Name());
         }
     } else if (t->getSensorB() == sen) {
         if (t->getSignalBMast() != nullptr) {
             signal = t->getSignalBMast();
         } else if (t->getSignalB1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalB1Name());
         }
     } else if (t->getSensorC() == sen) {
         if (t->getSignalCMast() != nullptr) {
             signal = t->getSignalCMast();
         } else if (t->getSignalC1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalC1Name());
         }
     } else if (t->getSensorD() == sen) {
         if (t->getSignalDMast() != nullptr) {
             signal = t->getSignalDMast();
         } else if (t->getSignalD1Name() != ("")) {
             signal = sh->getSignalHead(t->getSignalD1Name());
         }
     }
    }
    else if (qobject_cast<LevelXing*>(getRefLocation() )) {
      LevelXing* x = (LevelXing*) getRefLocation();
      if ( x->getSensorA() == sen) {
          if ( x->getSignalAMast() != nullptr) {
              signal =  x->getSignalAMast();
          } else if (x->getSignalAName() != ("")) {
              signal = sh->getSignalHead( x->getSignalAName());
          }
      } else if ( x->getSensorB() == sen) {
          if ( x->getSignalBMast() != nullptr) {
              signal =  x->getSignalBMast();
          } else if (x->getSignalBName() != ("")) {
              signal = sh->getSignalHead( x->getSignalBName());
          }
      } else if ( x->getSensorC() == sen) {
          if ( x->getSignalCMast() != nullptr) {
              signal =  x->getSignalCMast();
          } else if (x->getSignalCName() != ("")) {
              signal = sh->getSignalHead( x->getSignalCName());
          }
      } else if ( x->getSensorD() == sen) {
          if ( x->getSignalDMast() != nullptr) {
              signal =  x->getSignalDMast();
          } else if (x->getSignalDName() !=("")) {
              signal = sh->getSignalHead( x->getSignalDName());
          }
      }
  }
    //if(signal instanceof SignalMast)
    if(static_cast<SignalMast*>(signal)!= NULL)
        setSignalMast(((SignalMast*)signal));
    else
        //if (signal instanceof SignalHead)
        if(static_cast<SignalHead*>(signal)!= NULL)
        setSignalHead(((SignalHead*)signal));
    return signal;
}

//@Override
/*public*/ bool PointDetails::equals(QObject* obj){
    if(obj ==this)
        return true;
    if(obj ==NULL)
        return false;

        if(!(metaObject()->className()==obj->metaObject()->className()))
            return false;
        else{
            PointDetails* tmp = (PointDetails*)obj;
            if(tmp->getFacing()!=this->facing)
                return false;
            if(tmp->getProtecting()!=this->protectingBlocks)
                return false;
            if(tmp->getPanel()!=this->panel)
                return false;
        }
    return true;
}

//@Override
/*public*/ uint PointDetails::hashCode() {
    uint hash = 7;
//    hash = 37 * hash + (this->panel != NULL ? /*this->panel->hashCode()*/ qHash(panel->title(), (uint)qGlobalQHashSeed()) : 0);
    hash = 37 * hash + (this->facing != NULL ? this->facing->hashCode() : 0);
//    hash = 37 * hash + (this->protectingBlocks != NULL ? this->protectingBlocks.hashCode() : 0);
    return hash;
}

/*public*/ /*synchronized*/ void PointDetails::addPropertyChangeListener(PropertyChangeListener* l) {
    pcs->PropertyChangeSupport::addPropertyChangeListener(l);
}
/*public*/ /*synchronized*/ void PointDetails::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}
/*protected*/ void PointDetails::firePropertyChange(QString p, QVariant old, QVariant n) { pcs->firePropertyChange(p,old,n);}

