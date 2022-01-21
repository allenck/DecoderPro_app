#include "proxyturnoutmanager.h"
#include <QCompleter>
#include "internalsystemconnectionmemo.h"
#include "instancemanager.h"
#include "signalspeedmap.h"

ProxyTurnoutManager::ProxyTurnoutManager(QObject* parent)
    : AbstractProvidingProxyManager(parent)
{
 setObjectName("ProxyTurnoutManager");
 //registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!
 //propertyChangeSupport = new SwingPropertyChangeSupport(this,this);

}
/**
 * Implementation of a TurnoutManager that can serves as a proxy
 * for multiple system-specific implementations.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2010
 * @version	$Revision: 22324 $
 */
///*public*/ class ProxyTurnoutManager extends AbstractProxyManager implements TurnoutManager {

//    /*public*/ ProxyTurnoutManager() {
//        super();
//    }

/*protected*/ AbstractManager *ProxyTurnoutManager::makeInternalManager()
{
 return ((InternalSystemConnectionMemo*) InstanceManager::getDefault("InternalSystemConnectionMemo"))->getTurnoutManager();
}

/**
 * Revise superclass behavior: support TurnoutOperations
 */
//@Override
/*public*/ void ProxyTurnoutManager::addManager(AbstractManager *m)
{
 AbstractProxyManager::addManager(m);
 ((TurnoutOperationManager*)InstanceManager::getDefault("TurnoutOperationManager"))->loadOperationTypes();
}

/**
 * Locate via user name, then system name if needed.
 *
 * @param name
 * @return Null if nothing by that name exists
 */
/*public*/ Turnout* ProxyTurnoutManager::getTurnout(QString name)
{
 return (Turnout*)AbstractProxyManager::getNamedBean(name);
}

/**
 * {@inheritDoc}
 */
//@Override
//@Nonnull
/*protected*/ Turnout* ProxyTurnoutManager::makeBean(AbstractManager *manager, QString systemName, QString userName) /*throws IllegalArgumentException*/ {
    return ((AbstractTurnoutManager*) manager)->newTurnout(systemName, userName);
}

/*public*/ Turnout * ProxyTurnoutManager::provideTurnout(QString name)  {
 return (Turnout*)AbstractProvidingProxyManager::provideNamedBean(name);
}
//@Override
/** {@inheritDoc} */
/*public*/ Turnout* ProxyTurnoutManager::provide(/*@Nonnull */QString name) /*throw (IllegalArgumentException)*/
{ return (Turnout*)provideTurnout(name); }

#if 0
/**
 * Locate an instance based on a system name.  Returns null if no
 * instance already exists.
 * @return requested Turnout object or null if none exists
 */
/*public*/ Turnout *ProxyTurnoutManager::getBySystemName(QString systemName) const
{
 return (Turnout*) AbstractProxyTurnoutManager::getBeanBySystemName(systemName);
}

/**
 * Locate an instance based on a user name.  Returns null if no
 * instance already exists.
 * @return requested Turnout object or null if none exists
 */
/*public*/ Turnout *ProxyTurnoutManager::getByUserName(QString userName) const {
    return (Turnout*) AbstractProxyTurnoutManager::getBeanByUserName(userName);
}
#endif
/**
 * Return an instance with the specified system and user names.
 * Note that two calls with the same arguments will get the same instance;
 * there is only one Sensor object representing a given physical turnout
 * and therefore only one with a specific system or user name.
 *<P>
 * This will always return a valid object reference for a valid request;
 * a new object will be
 * created if necessary. In that case:
 *<UL>
 *<LI>If a null reference is given for user name, no user name will be associated
 *    with the Turnout object created; a valid system name must be provided
 *<LI>If a null reference is given for the system name, a system name
 *    will _somehow_ be inferred from the user name.  How this is done
 *    is system specific.  Note: a future extension of this interface
 *    will add an exception to signal that this was not possible.
 *<LI>If both names are provided, the system name defines the
 *    hardware access of the desired turnout, and the user address
 *    is associated with it.
 *</UL>
 * Note that it is possible to make an inconsistent request if both
 * addresses are provided, but the given values are associated with
 * different objects.  This is a problem, and we don't have a
 * good solution except to issue warnings.
 * This will mostly happen if you're creating Sensors when you should
 * be looking them up.
 * @return requested Sensor object (never null)
 */
/*public*/ Turnout* ProxyTurnoutManager::newTurnout(QString systemName, QString userName)  {
    return (Turnout*) newNamedBean(systemName, userName);
}
///*public*/ NamedBean* ProxyTurnoutManager::newNamedBean(QString systemName, QString userName) {
//    // if the systemName is specified, find that system
//    int i = matchTentative(systemName);
//    if (i >= 0)
//        return makeBean(i, systemName, userName);

//    // did not find a manager, allow it to default to the primary
//    log.debug("Did not find manager for system name "+systemName+", delegate to primary");
//    return makeBean(1, systemName, userName);
//}

/**
 * Get text to be used for the Turnout.CLOSED state in user communication.
 * Allows text other than "CLOSED" to be use with certain hardware system
 * to represent the Turnout.CLOSED state.
 * Defaults to the primary manager.  This means that the primary manager sets the terminology
 * used.  Note: the primary manager need not override the method in AbstractTurnoutManager if
 * "CLOSED" is the desired terminology.
 */
/*public*/ QString ProxyTurnoutManager::getClosedText() {
 //return ((AbstractTurnoutManager*) getDefaultManager())->getClosedText();
 AbstractManager* dm =  AbstractProxyManager::getDefaultManager();
 QString s = ((AbstractTurnoutManager*)((AbstractTurnoutManager*)dm))->getClosedText();
 return s;
}

/**
 * Get text to be used for the Turnout.THROWN state in user communication.
 * Allows text other than "THROWN" to be use with certain hardware system
 * to represent the Turnout.THROWN state.
 * Defaults to the primary manager.  This means that the primary manager sets the terminology
 * used.  Note: the primary manager need not override the method in AbstractTurnoutManager if
 * "THROWN" is the desired terminology.
 */
/*public*/ QString ProxyTurnoutManager::getThrownText() {
    return((AbstractTurnoutManager*) AbstractProxyManager::getDefaultManager())->getThrownText();
}

/**
 * Get from the user, the number of addressed bits used to control a turnout.
 * Normally this is 1, and the default routine returns 1 automatically.
 * Turnout Managers for systems that can handle multiple control bits
 * should override this method with one which asks the user to specify the
 * number of control bits.
 * If the user specifies more than one control bit, this method should
 * check if the additional bits are available (not assigned to another object).
 * If the bits are not available, this method should return 0 for number of
 * control bits, after informing the user of the problem.
 */
 /*public*/ int ProxyTurnoutManager::askNumControlBits(QString systemName) {
 return ((AbstractTurnoutManager*) AbstractProxyManager::getManagerOrDefault(systemName))->askNumControlBits(systemName);
}

/**
 * Get from the user, the type of output to be used bits to control a turnout.
 * Normally this is 0 for 'steady state' control, and the default routine
 * returns 0 automatically.
 * Turnout Managers for systems that can handle pulsed control as well as
 * steady state control should override this method with one which asks
 * the user to specify the type of control to be used.  The routine should
 * return 0 for 'steady state' control, or n for 'pulsed' control, where n
 * specifies the duration of the pulse (normally in seconds).
 */
 /*public*/ int ProxyTurnoutManager::askControlType(QString systemName) {
 return ((TurnoutManager*) getManagerOrDefault(systemName))->askControlType(systemName);
}

/*public*/ bool ProxyTurnoutManager::isControlTypeSupported(QString systemName) {
 return ((TurnoutManager*) getManagerOrDefault(systemName))->isControlTypeSupported(systemName);
}

/*public*/ bool ProxyTurnoutManager::isNumControlBitsSupported(QString systemName) {
 return ((TurnoutManager*) getManagerOrDefault(systemName))->isNumControlBitsSupported(systemName);
}

/**
 * TurnoutOperation support. Return a list which is just the concatenation of
 * all the valid operation types
 */
/*public*/ QStringList ProxyTurnoutManager::getValidOperationTypes() {
    QStringList typeList;
    for (Manager* m : getManagerList())
    {
     QStringList thisTypes = ((AbstractTurnoutManager*)m->self())->getValidOperationTypes();
     // typeList.addAll(Arrays.asList(thisTypes));
     foreach (QString s, thisTypes)
     {
      typeList.append(s);
     }
    }
    //return TurnoutOperationManager.concatenateTypeLists(typeList.toArray(new String[0]));
    return TurnoutOperationManager::concatenateTypeLists(typeList);
}

/*public*/ bool ProxyTurnoutManager::allowMultipleAdditions(QString systemName) {
 return ((TurnoutManager*) getManagerOrDefault(systemName))->allowMultipleAdditions(systemName);
}
#if 1
/*public*/ QString ProxyTurnoutManager::createSystemName(QString curAddress, QString prefix) /*throw (JmriException)*/
{
 return AbstractProxyManager::createSystemName(curAddress, prefix);
}
#endif
/*public*/ QString ProxyTurnoutManager::getNextValidAddress(QString curAddress, QString prefix)  /*throw (JmriException)*/
{
 return AbstractProxyManager::getNextValidAddress(curAddress, prefix, AbstractProxyManager::typeLetter());
}

//@Override
/*public*/ QString ProxyTurnoutManager::getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting) /*throws jmri.JmriException*/ {
    return AbstractProxyManager::getNextValidAddress(curAddress, prefix, ignoreInitialExisting, AbstractProxyManager::typeLetter());
}

/*public*/ void ProxyTurnoutManager::setDefaultClosedSpeed(QString speed)  /*throw (JmriException)*/ {
 if (defaultClosedSpeed == (speed)) {
     return;
 }
 if (speed.contains("Block")) {
     speed = "Block";
     if (defaultClosedSpeed == (speed)) {
         return;
     }
 } else {
     bool ok;
         speed.toFloat(&ok);
     if(!ok) {
         try {
             ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(speed);
         } catch (IllegalArgumentException* ex) {
             throw new JmriException("Value of requested turnout default closed speed is not valid");
         }
     }
 }
 QString oldSpeed = defaultClosedSpeed;
 defaultClosedSpeed = speed;
 firePropertyChange("DefaultTurnoutClosedSpeedChange", oldSpeed, speed);
}

/*public*/ void ProxyTurnoutManager::setDefaultThrownSpeed(QString speed)  /*throw (JmriException)*/{
 if (defaultThrownSpeed == (speed)) {
             return;
         }
         if (speed.contains("Block")) {
             speed = "Block";
             if (defaultThrownSpeed ==(speed)) {
                 return;
             }

         } else {
          bool ok;
              speed.toFloat(&ok);
          if(!ok) {
                 try {
                     ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(speed);
                 } catch (IllegalArgumentException* ex) {
                     throw new JmriException("Value of requested turnout default thrown speed is not valid");
                 }
             }
         }
         QString oldSpeed = defaultThrownSpeed;
         defaultThrownSpeed = speed;
         firePropertyChange("DefaultTurnoutThrownSpeedChange", oldSpeed, speed);}

/*public*/ QString ProxyTurnoutManager::getDefaultThrownSpeed() const{
 return defaultThrownSpeed;
}

/*public*/ QString ProxyTurnoutManager::getDefaultClosedSpeed() const{
 return defaultClosedSpeed;
}

/*public*/ int ProxyTurnoutManager::getXMLOrder() const{
    return Manager::TURNOUTS;
}

// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ProxyTurnoutManager.class.getName());
//}

/* @(#)ProxyTurnoutManager.java */
QCompleter* ProxyTurnoutManager::getCompleter(QString text)
{
 if(text.length()>1)
 {
  QStringList nameList = AbstractProxyManager::getSystemNameList();
  QStringList completerList;
  foreach(QString systemName, nameList)
  {
   Turnout* b = (Turnout*)AbstractProxyManager::getBySystemName(systemName);
   if(b->getUserName().startsWith(text,Qt::CaseInsensitive))
    completerList.append(b->getUserName());
   if(b->getSystemName().startsWith(text,Qt::CaseInsensitive))
    completerList.append(b->getSystemName());
  }
  if(completerList.size() > 0)
  {
   QCompleter* completer = new QCompleter(completerList, this);
    return completer;
  }
 }
 return NULL;
}
