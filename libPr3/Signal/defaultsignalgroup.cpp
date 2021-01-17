#include "defaultsignalgroup.h"
#include "signalhead.h"
#include "signalmast.h"
#include "instancemanager.h"
#include "propertychangeevent.h"
#include "singleturnoutsignalhead.h"
#include "signalmastmanager.h"
#include "signalheadmanager.h"
#include "turnout.h"
#include "sensor.h"
#include "defaultsignalmastmanager.h"
#include "abstractsignalheadmanager.h"

//DefaultSignalGroup::DefaultSignalGroup(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}

/**
 * Conditional.java
 *
 * A Conditional type to provide runtime support for Densor Groups.
 * <P>
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
 * @author			Pete Cressman Copyright (C) 2009
 * @version			$Revision 1.0 $
 */


// *public*/ class DefaultSignalGroup extends AbstractNamedBean implements jmri.SignalGroup{

/*public*/ DefaultSignalGroup::DefaultSignalGroup(QString systemName, QString userName, QObject *parent) : SignalGroup(systemName, userName, parent)
{
  //super(systemName, userName);
 _signalMast = NULL;
  _signalMastAppearances =  QStringList();
  headactive=false;
  enabled=true;
  log = new Logger("DefaultSignalGroup");
  _signalHeadItem =  QList<SignalHeadItem*>();
  pcs = new PropertyChangeSupport(this);
}

///*public*/ DefaultSignalGroup(String systemName) {
//    super(systemName, NULL);
//}


/*public*/ void DefaultSignalGroup::setEnabled(bool boo){
    enabled = boo;
}

/*public*/ bool DefaultSignalGroup::getEnabled(){
    return enabled;
}


/*public*/ void DefaultSignalGroup::setSignalMast(QString pName){

    SignalMast* mMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getBySystemName(pName);
    if (mMast == NULL) mMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName(pName);
    if (mMast == NULL) {
        log->warn("did not find a SignalHead named "+pName);
        return;
    }
    setSignalMast(mMast, pName);
}

/*public*/ void DefaultSignalGroup::setSignalMast(SignalMast* mMast, QString pName)
{
 if (_signalMast!=NULL)
 {
     getSignalMast()->removePropertyChangeListener(/*mSignalMastListener*/(PropertyChangeListener*)this);
 }
 _signalMast = new NamedBeanHandle<SignalMast*>(pName, mMast);
  getSignalMast()->addPropertyChangeListener(/*mSignalMastListener = new PropertyChangeListener()*/(PropertyChangeListener*)this);
  connect(getSignalMast()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}
//        /*public*/ void propertyChange(PropertyChangeEvent* e) {
//            if (e->getPropertyName()==("Aspect")){
//                QString now = ( e->getNewValue().toString());
//                if (isSignalMastAppearanceIncluded(now)){
//                    setHead();
//                } else {
//                    resetHeads();
//                }
//            }
//        }
//    });

//}

/*public*/ SignalMast* DefaultSignalGroup::getSignalMast(){
    return _signalMast->getBean();
}

/*public*/ QString DefaultSignalGroup::getSignalMastName(){
    return _signalMast->getName();
}

/*public*/ void DefaultSignalGroup::addSignalMastAspect(QString aspect){
    if(isSignalMastAspectIncluded(aspect)){
        return;
    }
    _signalMastAppearances.append(aspect);
}

/*public*/ bool DefaultSignalGroup::isSignalMastAspectIncluded(QString aspect)
{
 for (int i=0; i<_signalMastAppearances.size(); i++)
 {
  if ( _signalMastAppearances.at(i)==(aspect) )
  {
   // Found Appearance
   return true;
  }
 }
 return false;
}

/*public*/ void DefaultSignalGroup::deleteSignalMastAspect(QString aspect){
    _signalMastAppearances.removeOne(aspect);
}

/*public*/ int DefaultSignalGroup::getNumSignalMastAspects() {
    return _signalMastAppearances.size();
}

/*public*/ QString DefaultSignalGroup::getSignalMastAspectByIndex(int x){
    try {
        return _signalMastAppearances.at(x);
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*public*/ void DefaultSignalGroup::clearSignalMastAspect(){
    _signalMastAppearances = QStringList();
}

/*
    Add a new signalhead to the group
*/
/*public*/ void DefaultSignalGroup::addSignalHead(NamedBeanHandle<SignalHead*>* sh)
{
    SignalHeadItem* signalitem = new SignalHeadItem(sh);
    _signalHeadItem.append(signalitem);
}
/*
    Add a new signalhead to the group
*/
/*public*/ void DefaultSignalGroup::addSignalHead(QString pName){
    SignalHead* mHead = (SignalHead*)((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(pName);
    if (mHead == NULL) mHead = (SignalHead*)((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getByUserName(pName);
    if (mHead == NULL) log->warn("did not find a SignalHead named "+pName);
    else {
        addSignalHead(new NamedBeanHandle<SignalHead*>(pName, mHead));
    }
}

/*public*/ void DefaultSignalGroup::addSignalHead(SignalHead* mHead){
    addSignalHead(new NamedBeanHandle<SignalHead*>(mHead->getDisplayName(), mHead));
}

//protected PropertyChangeListener mSignalMastListener = NULL;

/*public*/ void DefaultSignalGroup::setSignalHeadAlignTurnout(SignalHead* mHead, Turnout* mTurn, int state){
    SignalHeadItem* sh = getSignalHeadItem(mHead);
    sh->addTurnout(mTurn, state);
}

/*public*/ void DefaultSignalGroup::setSignalHeadAlignSensor(SignalHead* mHead, Sensor* mSen, int state){
    SignalHeadItem* sh = getSignalHeadItem(mHead);
    sh->addSensor(mSen, state);
}

/*
Returns the 'n' signalheaditem
*/
/*private*/ SignalHeadItem* DefaultSignalGroup::getSignalHeadItemByIndex(int n)
{
    try {
        return _signalHeadItem.at(n);
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}


/*public*/ QString DefaultSignalGroup::getSignalHeadItemNameByIndex(int n)
{
    try {
        return getSignalHeadItemByIndex(n)->getName();
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*public*/ SignalHead* DefaultSignalGroup::getSignalHeadItemBeanByIndex(int n)
{
    try {
        return getSignalHeadItemByIndex(n)->getSignal();
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*
    Returns the number of signalheads in this group
*/
/*public*/ int DefaultSignalGroup::getNumSignalHeadItems() {
    return _signalHeadItem.size();
}

/*public*/ int DefaultSignalGroup::getSignalHeadOffState(SignalHead* bean){
    try {
        return getSignalHeadItem(bean)->getOffAppearance();
    } catch (NullPointerException e) {
        return -1;
    }
}

/*public*/ int DefaultSignalGroup::getSignalHeadOnState(SignalHead* bean){
    try {
        return getSignalHeadItem(bean)->getOnAppearance();
    } catch (NullPointerException e) {
        return -1;
    }
}

/*public*/ int DefaultSignalGroup::getSignalHeadOnStateByIndex(int n){
    try {
        return getSignalHeadItemByIndex(n)->getOnAppearance();
    } catch (IndexOutOfBoundsException ioob) {
        return -1;
    }
}

/*public*/ int DefaultSignalGroup::getSignalHeadOffStateByIndex(int n){
    try {
        return getSignalHeadItemByIndex(n)->getOffAppearance();
    } catch (IndexOutOfBoundsException ioob) {
        return -1;
    }
}

/*public*/ void DefaultSignalGroup::deleteSignalHead(SignalHead* pSignal){
    _signalHeadItem.removeOne(getSignalHeadItem(pSignal));
}

/*public*/ void DefaultSignalGroup::deleteSignalHead(NamedBeanHandle<SignalHead*>* sh){
    _signalHeadItem.removeOne(getSignalHeadItem(sh->getName()));
}

/*public*/ void DefaultSignalGroup::setSignalHeadOnState(SignalHead* head, int state){
    getSignalHeadItem(head)->setOnAppearance(state);
    firePropertyChange("UpdateCondition", QVariant(),QVariant());
}

/*public*/ void DefaultSignalGroup::setSignalHeadOffState(SignalHead* head, int state){
    getSignalHeadItem(head)->setOffAppearance(state);
    firePropertyChange("UpdateCondition", QVariant(),QVariant());
}

/*public*/ bool DefaultSignalGroup::isSignalIncluded(SignalHead* bean)
{
 for (int i=0; i<_signalHeadItem.size(); i++)
 {
  if ( _signalHeadItem.at(i)->getSignal() == bean )
  {
   // Found turnout
   return true;
  }
 }
 return false;
}

/*
    Returns a signalhead item
*/
/*private*/ SignalHeadItem* DefaultSignalGroup::getSignalHeadItem(QString name) {
    for (int i=0; i<_signalHeadItem.size(); i++) {
        if ( _signalHeadItem.at(i)->getName()==(name) ) {
            return _signalHeadItem.at(i);
        }
    }
    return NULL;
}

/*private*/ SignalHeadItem* DefaultSignalGroup::getSignalHeadItem(NamedBean* bean) {
    for (int i=0; i<_signalHeadItem.size(); i++) {
        if ( _signalHeadItem.at(i)->getSignal()==(bean) ) {
            return _signalHeadItem.at(i);
        }
    }
    return NULL;
}

/*public*/ bool DefaultSignalGroup::isTurnoutIncluded(SignalHead* pSignal, Turnout* pTurnout){
    return getSignalHeadItem(pSignal)->isTurnoutIncluded(pTurnout);
}

/*public*/ int DefaultSignalGroup::getTurnoutState(SignalHead* pSignal, Turnout* pTurnout){
    SignalHeadItem* sig = getSignalHeadItem(pSignal);
    if (sig != NULL)
        return sig->getTurnoutState(pTurnout);
    return -1;
}

/*public*/ int DefaultSignalGroup::getTurnoutStateByIndex(int x, Turnout* pTurnout){
    try {
        return getSignalHeadItemByIndex(x)->getTurnoutState(pTurnout);
    } catch (IndexOutOfBoundsException ioob) {
        return -1;
    }
}

/*public*/ int DefaultSignalGroup::getTurnoutStateByIndex(int x, int pTurnout){
    try {
        return getSignalHeadItemByIndex(x)->getTurnoutState(pTurnout);
    } catch (IndexOutOfBoundsException ioob) {
        return -1;
    }
}
/*public*/ QString DefaultSignalGroup::getTurnoutNameByIndex(int x, int pTurnout){
    try {
        return getSignalHeadItemByIndex(x)->getTurnoutName(pTurnout);
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*public*/ Turnout* DefaultSignalGroup::getTurnoutByIndex(int x, int pTurnout){
    try {
        return getSignalHeadItemByIndex(x)->getTurnout(pTurnout);
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*public*/ int DefaultSignalGroup::getSensorStateByIndex(int x, int pSensor){
    try {
        return getSignalHeadItemByIndex(x)->getSensorState(pSensor);
    } catch (IndexOutOfBoundsException ioob) {
        return -1;
    }
}

/*public*/ QString DefaultSignalGroup::getSensorNameByIndex(int x, int pSensor){
    try {
        return getSignalHeadItemByIndex(x)->getSensorName(pSensor);
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*public*/ Sensor* DefaultSignalGroup::getSensorByIndex(int x, int pSensor){
    try {
        return getSignalHeadItemByIndex(x)->getSensor(pSensor);
    } catch (IndexOutOfBoundsException ioob) {
        return NULL;
    }
}

/*public*/ bool DefaultSignalGroup::isSensorIncluded(SignalHead* pSignal, Sensor* pSensor){
    return getSignalHeadItem(pSignal)->isSensorIncluded(pSensor);
}

/*public*/ int DefaultSignalGroup::getSensorState(SignalHead* pSignal, Sensor* pSensor){
    SignalHeadItem* sig = getSignalHeadItem(pSignal);
    if (sig != NULL)
        return sig->getSensorState(pSensor);
    return -1;
}

/*public*/ bool DefaultSignalGroup::getSensorTurnoutOper(SignalHead* pSignal){
    return getSignalHeadItem(pSignal)->getSensorTurnoutOper();
}

/*public*/ bool DefaultSignalGroup::getSensorTurnoutOperByIndex(int x){
    return getSignalHeadItemByIndex(x)->getSensorTurnoutOper();
}

/*public*/ void DefaultSignalGroup::setSensorTurnoutOper(SignalHead* pSignal, bool boo){
    getSignalHeadItem(pSignal)->setSensorTurnoutOper(boo);
    firePropertyChange("UpdateCondition", QVariant(),QVariant());
}

/*public*/ void DefaultSignalGroup::clearSignalTurnout(SignalHead* pSignal){
    getSignalHeadItem(pSignal)->clearSignalTurnouts();
}
/*public*/ void DefaultSignalGroup::clearSignalSensor(SignalHead* pSignal){
    getSignalHeadItem(pSignal)->clearSignalSensors();
}

/*private*/ void DefaultSignalGroup::resetHeads(){
    if (!headactive)
        return;
    for (int i=0; i<_signalHeadItem.size(); i++) {
        _signalHeadItem.at(i)->getSignal()->setAppearance(_signalHeadItem.at(i)->getOffAppearance());
    }
    headactive=false;
}

/*private*/ void DefaultSignalGroup::setHead(){
    bool active = false;
    for (int i=0; i<_signalHeadItem.size(); i++) {
        if ( _signalHeadItem.at(i)->checkActive() ) {
            if (active)
                log->warn("two signal heads in the group should not be active at once");
            active = true;
            headactive = true;
        }
    }
}

/*public*/ int DefaultSignalGroup::getNumSignalHeadSensorsByIndex(int x){
    try {

        return getSignalHeadItemByIndex(x)->getNumSensors();
    } catch (IndexOutOfBoundsException ioob) {
        return -1;
    }
}

/*public*/ int DefaultSignalGroup::getNumSignalHeadTurnoutsByIndex(int x){
    try {
        return getSignalHeadItemByIndex(x)->getNumTurnouts();
    } catch (IndexOutOfBoundsException ioob) {
        return -1;
    }
}
///*private*/ static class SignalHeadItem implements java.io.Serializable
//{
SignalHeadItem::SignalHeadItem(NamedBeanHandle<SignalHead*>* sh)
{
 log = new Logger("SignalHeadItem");
 onAppearance = 0x00;
 offAppearance = 0x00;
 namedHead = sh;
 turnoutSensorOper = true;
 _signalTurnoutList = new QList<SignalTurnout*>();
 _signalSensorList = new QList<SignalSensor*>();

 if (QString(namedHead->getBean()->metaObject()->className()).contains("SingleTurnoutSignalHead"))
 {
  SingleTurnoutSignalHead* Signal = (SingleTurnoutSignalHead(*)) namedHead->getBean();
  if ((onAppearance==0x00) && (offAppearance==0x00))
  {
   onAppearance=Signal->getOnAppearance();
   offAppearance=Signal->getOffAppearance();
  }
 }
}

/*public*/ QString SignalHeadItem::getName(){
    return namedHead->getName();
}

/*public*/ SignalHead* SignalHeadItem::getSignal(){
    return namedHead->getBean();
}

/*public*/ void SignalHeadItem::setOnAppearance(int app){
    onAppearance = app;
}

/*public*/ int SignalHeadItem::getOnAppearance(){
    return onAppearance;
}

/*public*/ void SignalHeadItem::setOffAppearance(int app){
    offAppearance = app;
}

/*public*/ int SignalHeadItem::getOffAppearance(){
    return offAppearance;
}
/*public*/ bool SignalHeadItem::getSensorTurnoutOper(){ return turnoutSensorOper;}
/*public*/ void SignalHeadItem::setSensorTurnoutOper(bool boo) { turnoutSensorOper=boo; }

//Don't yet have the AND or OR set yet.
/*public*/ bool SignalHeadItem::checkActive()
{
 bool state = false;
 for (int x = 0; x<_signalTurnoutList->size(); x++)
 {
  log->debug ("Real state " + _signalTurnoutList->at(x)->getName()+ " " + _signalTurnoutList->at(x)->getTurnout()->getKnownState() + " state we testing for " + _signalTurnoutList->at(x)->getState());
        if (_signalTurnoutList->at(x)->getTurnout()->getKnownState()==_signalTurnoutList->at(x)->getState())
            state = true;
        else {
            state = false;
            break;
        }
    }

    for (int x = 0; x<_signalSensorList->size(); x++){
        if (_signalSensorList->at(x)->getSensor()->getKnownState()==_signalSensorList->at(x)->getState())
            state = true;
        else {
            state = false;
            break;
        }
    }
    if (state)
        getSignal()->setAppearance(onAppearance);
    else
        getSignal()->setAppearance(offAppearance);
    return state;
}

///*private*/ static class SignalTurnout implements java.io.Serializable {
//    NamedBeanHandle<Turnout> _turnout;
//    int _state;

    SignalHeadItem::SignalTurnout::SignalTurnout(Turnout* turn, int state)
    {
        log = new Logger("SignalTurnout");
     _turnout = ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turn->getDisplayName(), turn);
        setState(state);
    }

    QString SignalHeadItem::SignalTurnout::getName() {
        if (_turnout != NULL)
        {
            return _turnout->getName();
        }
        return NULL;
    }

    bool SignalHeadItem::SignalTurnout::setState(int state) {
        if (_turnout == NULL) {
            return false;
        }
        if ((state!=Turnout::THROWN) && (state!=Turnout::CLOSED)) {
            log->warn("Illegal Turnout state " +QString::number(state) + ": "+getName() );
            return false;
        }
        _state = state;
        return true;
    }
    int SignalHeadItem::SignalTurnout::getState() {
        return _state;
    }
    Turnout* SignalHeadItem::SignalTurnout::getTurnout() {
        return _turnout->getBean();
    }
//};

void SignalHeadItem::addTurnout(Turnout* turn, int state){
    SignalTurnout* signalTurnout = new SignalTurnout(turn, state);
    _signalTurnoutList->append(signalTurnout);
}

Turnout* SignalHeadItem::getTurnout(int x){
    return _signalTurnoutList->at(x)->getTurnout();
}

int SignalHeadItem::getTurnoutState(Turnout* turn)
{
 for (int i=0; i<_signalTurnoutList->size(); i++)
 {
  if( _signalTurnoutList->at(i)->getTurnout() == turn )
  {
   return _signalTurnoutList->at(i)->getState();
  }
 }
 return -1;
}

int SignalHeadItem::getNumTurnouts() {
    return _signalTurnoutList->size();
}

QString SignalHeadItem::getTurnoutName(int x){
    return _signalTurnoutList->at(x)->getName();
}

int SignalHeadItem::getTurnoutState(int x){
    return _signalTurnoutList->at(x)->getState();
}

bool SignalHeadItem::isTurnoutIncluded(Turnout* pTurnout)
{
 for (int i=0; i<_signalTurnoutList->size(); i++)
 {
  if ( _signalTurnoutList->at(i)->getTurnout()==pTurnout )
  {
   return true;
  }
 }
 return false;
}

void SignalHeadItem::clearSignalTurnouts() {
    _signalTurnoutList = new QList<SignalTurnout*>();
}

void SignalHeadItem::clearSignalSensors() {
    _signalSensorList = new QList<SignalSensor*>();
}

///*private*/ static class SignalSensor implements java.io.Serializable {
//    NamedBeanHandle<Sensor> _Sensor;
//    int _state;

    SignalHeadItem::SignalSensor::SignalSensor(Sensor* sen, int state)
    {
        log = new Logger("SignalSensor");
     _Sensor = ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sen->getDisplayName(), sen);
     setState(state);
    }

    QString SignalHeadItem::SignalSensor::getName() {
        if (_Sensor != NULL)
        {
            return _Sensor->getName();
        }
        return NULL;
    }

    bool SignalHeadItem::SignalSensor::setState(int state) {
        if (_Sensor == NULL) {
            return false;
        }
        if ((state!=Sensor::ACTIVE) && (state!=Sensor::INACTIVE)) {
            log->warn("Illegal Sensor state "+QString::number(state) +" for : "+getName() );
            return false;
        }
        _state = state;
        return true;
    }
    int SignalHeadItem::SignalSensor::getState() {
        return _state;
    }
    Sensor* SignalHeadItem::SignalSensor::getSensor() {
        return _Sensor->getBean();
    }

//};

void SignalHeadItem::addSensor(Sensor* sen, int state){
    SignalSensor* signalSensor = new SignalSensor(sen, state);
    _signalSensorList->append(signalSensor);
}

int SignalHeadItem::getSensorState(Sensor* sen)
{
 for (int i=0; i<_signalSensorList->size(); i++)
 {
  if( _signalSensorList->at(i)->getSensor() == sen )
  {
   return _signalSensorList->at(i)->getState();
  }
 }
 return -1;
}

int SignalHeadItem::getNumSensors() {
    return _signalSensorList->size();
}

/*SignalSensor getSignalSensorByIndex(int x){
    return _signalSensorList.get(x);
}*/

QString SignalHeadItem::getSensorName(int x){
    return _signalSensorList->value(x)->getName();
}

Sensor* SignalHeadItem::getSensor(int x){
    return _signalSensorList->value(x)->getSensor();
}

int SignalHeadItem::getSensorState(int x){
    return _signalSensorList->value(x)->getState();
}

bool SignalHeadItem::isSensorIncluded(Sensor* pSensor)
{
 for (int i=0; i<_signalSensorList->size(); i++)
 {
  if ( _signalSensorList->value(i)->getSensor()==pSensor )
  {
   // Found Sensor
   return true;
  }
 }
 return false;
}
//};

/*public*/ int DefaultSignalGroup::getState() {
    return 0x00;
}

/*public*/ void DefaultSignalGroup::setState(int /*state*/) {

}

    /**
 * Number of current listeners. May return -1 if the
 * information is not available for some reason.
 */
/*public*/ /*synchronized*/ int DefaultSignalGroup::getNumPropertyChangeListeners() {
    return pcs->getPropertyChangeListeners().length();
}

/*public*/ /*synchronized*/ QVector<PropertyChangeListener*> DefaultSignalGroup::getPropertyChangeListeners() {
    return pcs->getPropertyChangeListeners();
}

/*protected*/ void DefaultSignalGroup::firePropertyChange(QString p, QVariant old, QVariant n) {
    if (pcs!=NULL) pcs->firePropertyChange(p,old,n);
}

/*public*/ /*synchronized*/ void DefaultSignalGroup::addPropertyChangeListener(PropertyChangeListener* l) {
    pcs->addPropertyChangeListener(l);
}

/*public*/ /*synchronized*/ void DefaultSignalGroup::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}

/*public*/ void DefaultSignalGroup::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("Aspect"))
 {
  QString now = ( e->getNewValue().toString());
  if (isSignalMastAspectIncluded(now))
  {
   setHead();
  }
  else
  {
   resetHeads();
  }
 }
}
