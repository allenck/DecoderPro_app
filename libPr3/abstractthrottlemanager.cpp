#include "abstractthrottlemanager.h"
#include "locoaddress.h"
#include "Roster/rosterentry.h"
#include "loconetthrottle.h"
#include "Throttle/throttlewindow.h"
#include "addresspanel.h"
#include "speedprofilepanel.h"
#include "abstractautomaton.h"
#include "jsonthrottle.h"
#include "loggerfactory.h"
#include "throttlelistener.h"
#include "vptr.h"
#include <QSet>

/**
 * Abstract implementation of a ThrottleManager.
 * <P>
 * Based on Glen Oberhauser's original LnThrottleManager implementation.
 *
 * @author	Bob Jacobsen  Copyright (C) 2001
 * @version     $Revision: 22484 $
 */

AbstractThrottleManager::AbstractThrottleManager(QObject *parent)
    : ThrottleManager(parent)
{
    this->parent = parent;
    log->setDebugEnabled(true);
    throttleListeners = new QMap<uint,  QList<WaitingThrottle*>* >();
    listenerOnly = new QMap<uint,QList<WaitingThrottle*>* >();
    addressThrottles = new QMap<uint,Addresses*>();
    userName = "Internal";
}
//abstract public class AbstractThrottleManager implements ThrottleManager {


    //public AbstractThrottleManager(){}

/*public*/ AbstractThrottleManager::AbstractThrottleManager(SystemConnectionMemo* memo,QObject* parent) : ThrottleManager(parent)
{
    this->parent = parent;
    log = new Logger("AbstractThrottleManager");
    log->setDebugEnabled(true);
    adapterMemo = memo;
    userName = "Internal";
    throttleListeners = new QMap<uint,QList<WaitingThrottle*>* >();
    listenerOnly = new QMap<uint,QList<WaitingThrottle*>* >();
    addressThrottles = new QMap<uint,Addresses*>();
}


/*public*/ QString AbstractThrottleManager::getUserName(){
    if(adapterMemo!=NULL)
        return adapterMemo->getUserName();
    return userName;
}

/**
 * By default, only DCC in this implementation
 */
/*public*/ QStringList AbstractThrottleManager::getAddressTypes(){
QStringList list;
list << "dcc" <<"dcc_short" << "dcc_long";
 return list;
}

/**
 * By default, only DCC in this implementation
 */
/*public*/ QString AbstractThrottleManager::getAddressTypeString(LocoAddress::Protocol prot){
    return LocoAddress::getPeopleName(prot);
}

/*public*/ QList<LocoAddress::Protocol> AbstractThrottleManager::getAddressProtocolTypes(){
    QList<LocoAddress::Protocol> list;
    list << LocoAddress::DCC<< LocoAddress::DCC_SHORT<< LocoAddress::DCC_LONG;
    return list;
}

/*public*/ LocoAddress* AbstractThrottleManager::getAddress(QString value, LocoAddress::Protocol protocol)
{
 if (value == NULL) return NULL;
 //if (protocol == NULL) return NULL;
 int num = value.toInt();

 // if DCC long and can't be, or short and can't be, fix
 if ((LocoAddress::DCC == protocol || LocoAddress::DCC_SHORT == protocol) && !canBeShortAddress(num))
  protocol = LocoAddress::DCC_LONG;
 if ((LocoAddress::DCC == protocol || LocoAddress::DCC_LONG == protocol) && !canBeLongAddress(num))
  protocol = LocoAddress::DCC_SHORT;

 // if still ambiguous, prefer short
 if (protocol == LocoAddress::DCC)
  protocol = LocoAddress::DCC_SHORT;

 return new DccLocoAddress(num,protocol);
}
/*public*/ LocoAddress* AbstractThrottleManager::getAddress(QString value, QString protocol) {
    if (value == NULL) return NULL;
    if (protocol == NULL) return NULL;
    LocoAddress::Protocol p = getProtocolFromString(protocol);

    return getAddress(value, p);
}

/*public*/ LocoAddress::Protocol AbstractThrottleManager::getProtocolFromString(QString selection){
    return  LocoAddress::getByPeopleName(selection);
}

/**
 * Does this DCC system allow a Throttle (e.g. an address) to be used
 * by only one user at a time?
 */
/*protected*/ bool AbstractThrottleManager::singleUse() { return true; }

/**
     * @deprecated since 4.15.7; use
     * #requestThrottle(BasicRosterEntry, ThrottleListener, boolean) instead
     */
    //@Deprecated
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(BasicRosterEntry* re, ThrottleListener* l) {
        return requestThrottle(re, l, false);
    }

    /**
     * @deprecated since 4.15.7; use
     * #requestThrottle(BasicRosterEntry, ThrottleListener, boolean) instead
     */
    //@Deprecated
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(int address, bool isLongAddress, ThrottleListener* l) {
        DccLocoAddress* la = new DccLocoAddress(address, isLongAddress);
        return requestThrottle(la, l, false);
    }

    /**
     * @deprecated since 4.15.7; use
     * #requestThrottle(LocoAddress, ThrottleListener, boolean) instead
     */
    //@Deprecated
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(LocoAddress* la, ThrottleListener* l) {
        return requestThrottle(la, l, false);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(int address, bool isLongAddress, ThrottleListener* l, bool canHandleDecisions) {
        DccLocoAddress* la = new DccLocoAddress(address, isLongAddress);
        return requestThrottle(la, nullptr, l, canHandleDecisions);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(/*@Nonnull*/ BasicRosterEntry* re, ThrottleListener* l, bool canHandleDecisions) {
        return requestThrottle(re->getDccLocoAddress(), re, l, canHandleDecisions);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(LocoAddress* la, ThrottleListener* l, bool canHandleDecisions) {
        return requestThrottle(la, nullptr, l, canHandleDecisions);
    }

    /**
     * @deprecated since 4.15.7; use
     * #requestThrottle(LocoAddress, ThrottleListener, boolean) instead
     */
    //@Deprecated
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(LocoAddress* /*la*/, BasicRosterEntry* re, ThrottleListener* l) {
        return requestThrottle(re, l, false);
    }

    /**
     * Request a throttle, given a decoder address.
     * <p>
     * When the decoder address is
     * located, the ThrottleListener gets a callback via the
     * ThrottleListener.notifyThrottleFound method.
     *
     * @param la LocoAddress of the decoder desired.
     * @param l  The ThrottleListener awaiting notification of a found throttle.
     * @param re A BasicRosterEntry can be passed, this is attached to a throttle after creation.
     * @param canHandleDecisions true if theThrottleListener can make a steal or share decision, else false.
     * @return True if the request will continue, false if the request will not
     *         be made. False may be returned if a the throttle is already in
     *         use.
     */
    /*protected*/ bool AbstractThrottleManager::requestThrottle(LocoAddress* la, BasicRosterEntry* re, ThrottleListener* l, bool canHandleDecisions)
    {
        bool throttleFree = true;

        // check for a valid throttle address
        if (!canBeLongAddress(la->getNumber()) && !canBeShortAddress(la->getNumber())) {
            return false;
        }

        // put the list in if not present
        if (!throttleListeners->contains(la->hashCode()))
        {
            throttleListeners->insert(la->hashCode(), new QList<WaitingThrottle*>());
        }
        // get the corresponding list to check length
        QList<WaitingThrottle*>* a = throttleListeners->value(la->hashCode());

        if (addressThrottles->contains(la->hashCode()))
        {
         log->debug(tr("A throttle to address %1 already exists, so will return that throttle").arg(la->getNumber()));
         a->append(new WaitingThrottle(l, re, canHandleDecisions));
         notifyThrottleKnown(addressThrottles->value(la->hashCode())->getThrottle(), la);
         return throttleFree;
        } else {
            log->debug(tr("%1 has not been created before").arg(la->getNumber() ));
        }

        log->debug(tr("After request in ATM: %1").arg(a->size()));

        // check length
        if (singleUse() && (a->size() > 0)) {
            throttleFree = false;
            log->debug("singleUser() is true, and the list of WaitingThrottles isn't empty, returning false");
        } else if (a->size() == 0) {
            a->append(new WaitingThrottle(l, re, canHandleDecisions));
            log->debug(tr("list of WaitingThrottles is empty: %1; %2").arg(la->toString()).arg(a->size()));
            log->debug("calling requestThrottleSetup()");
            requestThrottleSetup(la, true);
        } else {
            a->append(new WaitingThrottle(l, re, canHandleDecisions));
            log->debug("singleUse() returns false and there are existing WaitThrottles, adding a one to the list");
        }
        return throttleFree;
    }


    /**
     * Request Throttle with no Steal / Share Callbacks
     * {@inheritDoc}
     * Request a throttle, given a decoder address. When the decoder address is
     * located, the ThrottleListener gets a callback via the
     * ThrottleListener.notifyThrottleFound method.
     * <p>
     * This is a convenience version of the call, which uses system-specific
     * logic to tell whether the address is a short or long form.
     *
     * @param address The decoder address desired.
     * @param l       The ThrottleListener awaiting notification of a found
     *                throttle.
     * @return True if the request will continue, false if the request will not
     *         be made. False may be returned if a the throttle is already in
     *         use.
     */
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(int address, ThrottleListener* l) {
        bool isLong = true;
        if (canBeShortAddress(address)) {
            isLong = false;
        }
        return requestThrottle(new DccLocoAddress(address,isLong), nullptr, l, false);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool AbstractThrottleManager::requestThrottle(int address, ThrottleListener* l, bool canHandleDecisions) {
        bool isLong = true;
        if (canBeShortAddress(address)) {
            isLong = false;
        }
        return requestThrottle(new DccLocoAddress(address,isLong), nullptr, l, canHandleDecisions);
    }

    /**
     * Abstract member to actually do the work of configuring a new throttle,
     * usually via interaction with the DCC system
     * @param a  address
     * @param control  false  - read only.
     */
    // /*abstract*/ /*public*/ void requestThrottleSetup(LocoAddress* a, bool control);

 /**
 * Abstract member to actually do the work of configuring a new throttle,
 * usually via interaction with the DCC system
 */
/*public*/ void AbstractThrottleManager::requestThrottleSetup(LocoAddress* a)
{
 requestThrottleSetup(a, true);
}

/**
 * Cancel a request for a throttle
 * @param address The decoder address desired.
 * @param isLong True if this is a request for a DCC long (extended) address.
 * @param l The ThrottleListener cancelling request for a Throttle::
 */
/*public*/ void AbstractThrottleManager::cancelThrottleRequest(int address, bool isLong, ThrottleListener* l) {
    if(throttleListeners!=NULL){
        DccLocoAddress* la = new DccLocoAddress(address, isLong);
        cancelThrottleRequest(la, l);
    }
    /*if (addressThrottles.contains(la)){
        addressThrottles.get(la).decrementUse();
    }*/
}

/*public*/ void AbstractThrottleManager::cancelThrottleRequest(BasicRosterEntry* re, ThrottleListener* l){
    if(throttleListeners!=NULL){
        cancelThrottleRequest(re->getDccLocoAddress(), l);
    }
}

/*private*/ void AbstractThrottleManager::cancelThrottleRequest(LocoAddress* la, ThrottleListener* l)
{
 if (throttleListeners != NULL)
 {
  QList<WaitingThrottle*>* a = throttleListeners->value(la->hashCode());
  if (a == NULL) return;
  for (int i = 0; i<a->size(); i++)
  {
   if (l == a->value(i)->getListener())
    a->removeAt(i);
  }
 }
}

/**
 * Cancel a request for a Throttle::
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 * @param address The decoder address desired.
 * @param l The ThrottleListener cancelling request for a Throttle::
 */
/*public*/ void AbstractThrottleManager::cancelThrottleRequest(int address, ThrottleListener* l) {
    bool isLong = true;
   // if (canBeShortAddress(address)) isLong = false;
    cancelThrottleRequest(address, isLong, l);
}
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractThrottleManager::responseThrottleDecision(int address, bool isLong, ThrottleListener* l, ThrottleListener::DecisionType decision) {
    DccLocoAddress* la = new DccLocoAddress(address, isLong);
    responseThrottleDecision(la,l,decision);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractThrottleManager::responseThrottleDecision(LocoAddress* address, ThrottleListener* /*l*/, ThrottleListener::DecisionType /*decision*/) {
    log->debug("Received response from ThrottleListener, this method should be overridden by a hardware type");
}
/**
 * If the system-specific ThrottleManager has been unable to create the DCC
 * throttle then it needs to be removed from the throttleListeners, otherwise
 * any subsequent request for that address results in the address being reported
 * as already in use, if singleUse is set->
 * This also sends a notification message back to the requestor with a string
 * reason as to why the request has failed.
 * @param address The DCC Loco Address that the request failed on.
 * @param reason A text string passed by the ThrottleManae as to why
 */
/*public*/ void AbstractThrottleManager::failedThrottleRequest(LocoAddress* address, QString reason)
{
 QList<WaitingThrottle*>* a = throttleListeners->value(address->hashCode());
 if (a == nullptr)
 {
     log->warn("notifyThrottleKnown with zero-length listeners: "+address->toString());
 }
 else
 {
  for (int i = 0; i<a->size(); i++)
  {
   ThrottleListener* l = a->at(i)->getListener();
   l->notifyFailedThrottleRequest(address, reason);
  }
 }
 throttleListeners->remove(address->hashCode());
 QList<WaitingThrottle*>* p = listenerOnly->value(address->hashCode());
 if (p == nullptr || p->isEmpty())
 {
  log->debug("notifyThrottleKnown with zero-length PropertyChange listeners: "+address->toString());
 }
 else
 {
  for (int i = 0; i<p->size(); i++)
  {
   PropertyChangeListener* l = p->value(i)->getPropertyChangeListener();
   l->propertyChange(new PropertyChangeEvent(this, "attachFailed", VPtr<LocoAddress>::asQVariant(address), QVariant()));
  }
 }
 listenerOnly->remove(address->hashCode());
}

/**
 * Handle throttle information when it's finally available, e.g. when
 * a new Throttle object has been created.
 * <P>
 * This method creates a throttle for all ThrottleListeners of that address
 * and notifies them via the ThrottleListener.notifyThrottleFound method.
 */
/*public*/ void AbstractThrottleManager::notifyThrottleKnown(DccThrottle* throttle, LocoAddress* addr)
{
 log->debug(tr("notifyThrottleKnown for %1").arg(addr->toString()));
 Addresses* ads = nullptr;
 if (!addressThrottles->contains(addr->hashCode()))
 {
     log->debug(tr("Address %1 doesn't already exists so will add").arg(addr->toString()));
     ads = new Addresses(throttle);
     addressThrottles->insert(addr->hashCode(), ads);
 } else {
     addressThrottles->value(addr->hashCode())->setThrottle(throttle);
 }
 QList<WaitingThrottle*>* a = throttleListeners->value(addr->hashCode());
 if (a == nullptr)
 {
  log->debug(tr("notifyThrottleKnown with zero-length listeners: %1").arg(addr->toString()));
 }
 else
 {
  for (int i = 0; i < a->size(); i++)
  {
   ThrottleListener* l = a->value(i)->getListener();
   log->debug(tr("Notify listener %1 of %2").arg(i + 1).arg(a->size() ));
   l->notifyThrottleFound(throttle);
   addressThrottles->value(addr->hashCode())->incrementUse();
   addressThrottles->value(addr->hashCode())->addListener(l);
   if (ads != nullptr && a->value(i)->getRosterEntry() != nullptr && throttle->getRosterEntry() == nullptr) {
       throttle->setRosterEntry(a->value(i)->getRosterEntry());
   }
   updateNumUsers(addr,addressThrottles->value(addr->hashCode())->getUseCount());
  }
  throttleListeners->remove(addr->hashCode());
 }
 QList<WaitingThrottle*>* p = listenerOnly->value(addr->hashCode());
 if (p == nullptr) {
     log->debug(tr("notifyThrottleKnown with zero-length propertyChangeListeners: %1").arg(addr->toString()));
 } else {
     for (int i = 0; i < p->size(); i++) {
         PropertyChangeListener* l = p->at(i)->getPropertyChangeListener();
         log->debug("Notify propertyChangeListener");
         l->propertyChange(new PropertyChangeEvent(this, "throttleAssigned", 0, VPtr<LocoAddress>::asQVariant(addr)));
         if (ads != nullptr && p->value(i)->getRosterEntry() != nullptr && throttle->getRosterEntry() == nullptr) {
             throttle->setRosterEntry(p->at(i)->getRosterEntry());
         }
         throttle->addPropertyChangeListener(l);
     }
     listenerOnly->remove(addr->hashCode());
 }
}


/**
 * For when a steal / share decision is needed and the ThrottleListener has delegated
 * this decision to the ThrottleManager.
 * <p>
 * Responds to the question by requesting a Throttle "Steal" by default.
 * <p>
 * Can be overridden by hardware types which do not wish the default behaviour to Steal.
 * <p>
 * This applies only to those systems where "stealing" or "sharing" applies, such as LocoNet.
 * <p>
 * @param address The LocoAddress the steal / share question relates to
 * @param question The Question to be put to the ThrottleListener
 */
/*protected*/ void AbstractThrottleManager::makeHardwareDecision(LocoAddress* address, ThrottleListener::DecisionType /*question*/){
    responseThrottleDecision(address, nullptr, ThrottleListener::DecisionType::STEAL );
}

/**
 * When the system-specific ThrottleManager has been unable to create the DCC
 * throttle because it is already in use and must be "stolen" or "shared" to take control,
 * it needs to notify the listener of this situation.
 * <p>
 * This applies only to those systems where "stealing" or "sharing" applies, such as LocoNet.
 * <p>
 * @param address The LocoAddress the steal / share question relates to
 * @param question The Question to be put to the ThrottleListener
 * This applies only to those systems where "stealing" applies, such as LocoNet.
 */
/*protected*/ void AbstractThrottleManager::notifyDecisionRequest(LocoAddress* address, ThrottleListener::DecisionType question) {

    if (throttleListeners != nullptr) {
        QList<WaitingThrottle*>* a = throttleListeners->value(address->hashCode());
        if (a == nullptr) {
            log->debug(tr("Cannot issue question, No throttle listeners registered for address %1").arg(address->getNumber()));
            return;
        }
        ThrottleListener* l;
        log->debug(tr("%1 listener(s) registered for address %2").arg(a->size()).arg(address->getNumber()));
        for (int i = 0; i < a->size(); i++) {
            if (a->value(i)->canHandleDecisions() ){
                l = a->value(i)->getListener();
                log->debug(tr("Notifying a throttle listener (address %1) of the steal share situation").arg(address->getNumber()));
                l->notifyDecisionRequired(address,question);
            }
            else {
                log->debug(tr("Passing %1 to hardware steal / share decision making").arg(address->getNumber()));
                makeHardwareDecision(address,question);
            }
        }
    }
}

/**
 * Check to see if the Dispatch Button should be enabled or not
 * Default to true, override if necessary
 **/
/*public*/ bool AbstractThrottleManager::hasDispatchFunction() { return true; }

/**
 * What speed modes are supported by this system?
 * value should be xor of possible modes specifed by the
 * DccThrottle interface
 */
/*public*/ QSet<SpeedStepMode::SSMODES> AbstractThrottleManager::supportedSpeedModes() {
    //return(DccThrottle::SpeedStepMode128);
 QSet<SpeedStepMode::SSMODES>modes = QSet<SpeedStepMode::SSMODES>();
 modes.insert(SpeedStepMode::NMRA_DCC_128);

 return modes;
}

/*public*/ void AbstractThrottleManager::attachListener(LocoAddress* la,PropertyChangeListener* p)
{

 if (addressThrottles->contains(la->hashCode()))
 {
  addressThrottles->value(la->hashCode())->getThrottle()->addPropertyChangeListener(p);
  p->propertyChange(new PropertyChangeEvent(this, "throttleAssigned", NULL, la));
  return;
 }
 else
 {
  if (!listenerOnly->contains(la->hashCode()))
   listenerOnly->insert(la->hashCode(), new QList<WaitingThrottle*>());

  // get the corresponding list to check length
  QList<WaitingThrottle*>* a = listenerOnly->value(la->hashCode());
  a->append(new WaitingThrottle(p, nullptr, false));
  //Only request that the throttle is set up if it hasn't already been
  //requested.
  if ((!throttleListeners->contains(la->hashCode())) && (a->size()==1))
  {
   requestThrottleSetup(la, false);
  }
 }

}

/*public*/ void AbstractThrottleManager::removeListener(LocoAddress* la, PropertyChangeListener* p)
{
#if 1 // TODO:
 if (addressThrottles->contains(la->hashCode()))
 {
  addressThrottles->value(la->hashCode())->getThrottle()->removePropertyChangeListener(p);
  p->propertyChange(new PropertyChangeEvent(this, "throttleRemoved", la, NULL));
  return;
 }
 p->propertyChange(new PropertyChangeEvent(this, "throttleNotFoundInRemoval", la, NULL));
#endif
}

/*public*/ bool AbstractThrottleManager::addressStillRequired(LocoAddress* la)
{
 if (addressThrottles->contains(la->hashCode()))
 {
  log->debug("usage count is " + QString("%1").arg(addressThrottles->value(la->hashCode())->getUseCount()));
  if(addressThrottles->value(la->hashCode())->getUseCount()>0)
  {
   return true;
  }
 }
 return false;
}

/*public*/ void AbstractThrottleManager::releaseThrottle(DccThrottle* t, ThrottleListener* l)
{
 disposeThrottle(t, l);
}

/*public*/ bool AbstractThrottleManager::disposeThrottle(DccThrottle* t, ThrottleListener* l)
{
//        if (!active) log->error("Dispose called when not active");  <-- might need to control this in the sub class
 if(t == NULL) 
  return false;

 DccLocoAddress* la = (DccLocoAddress*) t->getLocoAddress();
 if (addressReleased(la, l))
 {
  log->debug("Address " + QString::number(((DccLocoAddress*)t->getLocoAddress())->getNumber()) + " still has active users");
  return false;
 }
 if(t->getListeners()->size()>0)
 {
  log->debug("Throttle " + QString::number(((DccLocoAddress*)t->getLocoAddress())->getNumber()) + " still has active propertyChangeListeners registered to the throttle");
  return false;
 }
 if (addressThrottles->contains(la->hashCode()))
 {
  addressThrottles->remove(la->hashCode());
  log->debug("Loco Address removed from the stack " + QString::number(la->getNumber()));
 }
 else
 {
  log->debug("Loco Address not found in the stack " + QString::number(la->getNumber()));
 }
 return true;
}

/*public*/ void AbstractThrottleManager::dispatchThrottle(DccThrottle* t, ThrottleListener* l){
    releaseThrottle(t, l);
}

/*protected*/ bool AbstractThrottleManager::addressReleased(LocoAddress* la, ThrottleListener* l)
{
 if (addressThrottles->contains(la->hashCode()))
 {
  if(addressThrottles->value(la->hashCode())->containsListener(l))
  {
   //log->debug("decrementUse called with listener " + ((QObject*)l)->objectName());
   addressThrottles->value(la->hashCode())->decrementUse();
   addressThrottles->value(la->hashCode())->removeListener(l);
  }
  else if (l==NULL)
  {
   log->debug("decrementUse called withOUT listener");
            /*The release release has been called, but as no listener has
            been specified, we can only decrement the use flag*/
   addressThrottles->value(la->hashCode())->decrementUse();
  }
 }
 if (addressThrottles->contains(la->hashCode()))
 {
  if(addressThrottles->value(la->hashCode())->getUseCount()>0)
  {
   return true;
  }
 }
 return false;
}
/**
 * The number of users of this throttle has been updated
 * <p>
 * Typically used to update dispatch / release availablility
 * specific implementations can override this function to get updates
 *
 * @param la the Loco Address which has been updated
 */
/*protected*/ void AbstractThrottleManager::updateNumUsers( LocoAddress* la, int numUsers ){
    log->debug(tr("Throttle %1 now has %2 users").arg(la->toString()).arg(numUsers));
}

/*public*/ QVariant AbstractThrottleManager::getThrottleInfo(LocoAddress* la, QString item)
{
 DccThrottle* t;
 LocoNetThrottle* ln;
 if (addressThrottles->contains(la->hashCode()))
 {
  t = addressThrottles->value(la->hashCode())->getThrottle();
  ln = (LocoNetThrottle*)t;
 }
 else
 {
     return QVariant();
 }
 if (item == (Throttle::ISFORWARD)) {
     return t->getIsForward();
 } else if (item.startsWith("Speed")) {
     if (item ==(Throttle::SPEEDSETTING)) {
         return t->getSpeedSetting();
     } else if (item == (Throttle::SPEEDINCREMENT)) {
         return t->getSpeedIncrement();
     } else if (item == (Throttle::SPEEDSTEPMODE)) {
         return t->getSpeedStepMode();
     }
 }
 for ( int i = 0; i< t->getFunctions().length(); i++ ) {
     if (item == (Throttle::getFunctionString(i))) {
         return t->getFunction(i);
     }
 }
 return QVariant();
}

 WaitingThrottle::WaitingThrottle(ThrottleListener* _l, BasicRosterEntry* _re,  bool _canHandleDecisions)
 {
  setObjectName("WaitingThrottle");
  pl=NULL;
  l = _l;
  re = _re;
  this->_canHandleDecisions = _canHandleDecisions;
 }
 WaitingThrottle::WaitingThrottle(PropertyChangeListener* _pl, BasicRosterEntry* _re,  bool _canHandleDecisions)
 {
  setObjectName("WaitingThrottle");
  l=NULL;
  pl = _pl;
  re = _re;
  this->_canHandleDecisions = _canHandleDecisions;

 }

 PropertyChangeListener* WaitingThrottle::getPropertyChangeListener()
 {
  return pl;
 }

 ThrottleListener* WaitingThrottle::getListener()
 {
  return l;
 }

 BasicRosterEntry* WaitingThrottle::getRosterEntry()
 {
  return re;
 }

/**
 * This subClass, keeps track of which loco address have been requested and
 * by whom, it primarily uses a increment count to keep track of all the the
 * Addresses in use as not all external code will have been refactored over
 * to use the new disposeThrottle::
 */
  /*protected*/ Addresses::Addresses(DccThrottle* throttle)
  {
   setObjectName("Addresses");
   this->throttle = throttle;
   re = NULL;
   useActiveCount = 0;
   listeners = new QList<ThrottleListener*>();
  }
  void Addresses::incrementUse()
  {
   useActiveCount++;
   if(qobject_cast<LocoNetThrottle*>(throttle)!= NULL)
   {
    LocoNetThrottle* lnThrottle = (LocoNetThrottle*)throttle;
    log.debug(QString::number(((DccLocoAddress*) lnThrottle->getLocoAddress())->getNumber()) + " increased Use Size to " + QString::number(useActiveCount));
   }
  }

  void Addresses::decrementUse()
  {
   //Do want to go below 0 on the usage front!
   if (useActiveCount >0)
    useActiveCount--;
   if(qobject_cast<LocoNetThrottle*>(throttle)!= NULL)
   {
    LocoNetThrottle* lnThrottle = (LocoNetThrottle*)throttle;
    log.debug(QString::number(((DccLocoAddress*) lnThrottle->getLocoAddress())->getNumber()) + " decreased Use Size to " + QString::number(useActiveCount));
   }
  }

  int Addresses::getUseCount() { return useActiveCount; }

  DccThrottle* Addresses::getThrottle()
  {
   return throttle;
  }

  void Addresses::setThrottle(DccThrottle* throttle)
  {
   DccThrottle* old = this->throttle;
   this->throttle = throttle;
   if ((old==NULL) || (old==throttle))
   {
    return;
   }

   //As the throttle has changed, we need to inform the listeners
   //However if a throttle hasn't used the new code, it will not have been
   //removed and will get a notification.
   if(qobject_cast<LocoNetThrottle*>(throttle)!= NULL)
   {
    LocoNetThrottle* lnThrottle = (LocoNetThrottle*)throttle;
    log.debug(QString::number(((DccLocoAddress*) lnThrottle->getLocoAddress())->getNumber()) + " throttle assigned " +
                 "has been changed need to notify throttle users");
   }
   this->throttle = throttle;
   for (int i = 0; i<listeners->size(); i++)
   {
    listeners->value(i)->notifyThrottleFound(throttle);
   }
   //This handles moving the listeners from the old throttle to the new one
   DccLocoAddress* la = dynamic_cast<DccLocoAddress*>(this->throttle->getLocoAddress());
   QVector<PropertyChangeListener*>* v = old->getListeners();
   foreach (PropertyChangeListener* prop , *v)
   {
    if(qobject_cast<LocoNetThrottle*>(throttle)!= NULL)
     ((LocoNetThrottle*)this->throttle)->addPropertyChangeListener(prop);
#if 1 //TODO:
     prop->propertyChange(new PropertyChangeEvent((QObject*)this, "throttleAssignmentChanged", QString(""), VPtr<DccLocoAddress>::asQVariant(la)));
#endif
   }
  }

  void Addresses::setRosterEntry(BasicRosterEntry* _re)
  {
   re = _re;
  }

  BasicRosterEntry* Addresses::getRosterEntry()
  {
   return re;
  }

  void Addresses::addListener(ThrottleListener* l){
   // Check for duplication here
   if (listeners->contains(l))
       log.debug(tr("this Addresses listeners already includes listener %1").arg(l->self()->metaObject()->className()));
   else
         listeners->append(l);
  }

  void Addresses::removeListener(ThrottleListener* l){

         listeners->removeAt(listeners->indexOf(l));
  }

  bool Addresses::containsListener(ThrottleListener* l){
         return listeners->contains(l);
  }

/*static*/ Logger* AbstractThrottleManager::log = LoggerFactory::getLogger("AbstractThrottleManager");
