#include "proxyturnoutmanager.h"
#include <QCompleter>
#include "internalsystemconnectionmemo.h"
#include "instancemanager.h"

ProxyTurnoutManager::ProxyTurnoutManager(QObject* parent)
    : AbstractProxyTurnoutManager(parent)
{
 setObjectName("ProxyTurnoutManager");
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

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

/*protected*/ Manager* ProxyTurnoutManager::makeInternalManager() const
{
 return ((InternalSystemConnectionMemo*) InstanceManager::getDefault("InternalSystemConnectionMemo"))->getTurnoutManager();

}

/**
 * Revise superclass behavior: support TurnoutOperations
 */
//@Override
/*public*/ void ProxyTurnoutManager::addManager(Manager* m)
{
    AbstractProxyTurnoutManager::addManager(m);
    ((TurnoutOperationManager*)InstanceManager::getDefault("TurnoutOperationManager"))->loadOperationTypes();

#if 0
    if (defaultManager == nullptr) defaultManager = m;  // 1st one is default

//    propertyVetoListenerList.stream().forEach((l) -> {
//        m.addVetoableChangeListener(l);
//    });
//    propertyListenerList.stream().forEach((l) -> {
//        m.addPropertyChangeListener(l);
//    });

//    m.addDataListener(this);
    updateOrderList();
//    updateNamedBeanSet();

    if (log.isDebugEnabled()) {
        log.debug(QString("added manager ") + m->metaObject()->className());
    }
#endif
}

/**
 * Locate via user name, then system name if needed.
 *
 * @param name
 * @return Null if nothing by that name exists
 */
/*public*/ Turnout* ProxyTurnoutManager::getTurnout(QString name) const
{
 return (Turnout*)AbstractProxyTurnoutManager::getNamedBean(name);
}

/*protected*/ NamedBean* ProxyTurnoutManager::makeBean(int i, QString systemName, QString userName) const
{
    //return ((AbstractProxyTurnoutManager*)((AbstractProxyTurnoutManager*)getMgr(i)))->newTurnout(systemName, userName);
 Manager* m = getMgr(i);
 NamedBean* bean = ((AbstractTurnoutManager*)m)->newTurnout(systemName, userName);
 return bean;
}

/*public*/ Turnout *ProxyTurnoutManager::provideTurnout(QString name) const {
    return  (Turnout*)AbstractProxyTurnoutManager::provideNamedBean(name);
}
//@Override
/** {@inheritDoc} */
/*public*/ Turnout* ProxyTurnoutManager::provide(/*@Nonnull */QString name) const throw (IllegalArgumentException)
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
/*public*/ Turnout* ProxyTurnoutManager::newTurnout(QString systemName, QString userName) const {
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
    return ((AbstractTurnoutManager*)getMgr(0))->getClosedText();
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
    return ((AbstractTurnoutManager*)getMgr(0))->getThrownText();
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
    int i = matchTentative(systemName);
    if (i >= 0)
        return ((TurnoutManager*)getMgr(i))->askNumControlBits(systemName);
    return ((AbstractTurnoutManager*)getMgr(0))->askNumControlBits(systemName);
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
    int i = matchTentative(systemName);
    if (i >= 0)
        return ((TurnoutManager*)getMgr(i))->askControlType(systemName);
    return ((AbstractTurnoutManager*)getMgr(0))->askControlType(systemName);
}

/*public*/ bool ProxyTurnoutManager::isControlTypeSupported(QString systemName) {
    int i = matchTentative(systemName);
    if (i >= 0)
        return ((TurnoutManager*)getMgr(i))->isControlTypeSupported(systemName);
    return ((AbstractTurnoutManager*)getMgr(0))->isControlTypeSupported(systemName);
}

/*public*/ bool ProxyTurnoutManager::isNumControlBitsSupported(QString systemName) {
    int i = matchTentative(systemName);
    if (i >= 0)
        return ((TurnoutManager*)getMgr(i))->isNumControlBitsSupported(systemName);
    return ((AbstractTurnoutManager*)getMgr(0))->isNumControlBitsSupported(systemName);
}

/**
 * TurnoutOperation support. Return a list which is just the concatenation of
 * all the valid operation types
 */
/*public*/ QStringList ProxyTurnoutManager::getValidOperationTypes() {
    QStringList typeList;
    for (int i=0; i<nMgrs(); ++i)
    {
     QStringList thisTypes = ((AbstractTurnoutManager*)getMgr(i))->getValidOperationTypes();
     // TODO:        typeList.addAll(Arrays.asList(thisTypes));
     foreach (QString s, thisTypes)
     {
      typeList.append(s);
     }
    }
// TODO:    return TurnoutOperationManager::concatenateTypeLists(typeList.toArray(new QString[0]));
    return typeList;
}

/*public*/ bool ProxyTurnoutManager::allowMultipleAdditions(QString systemName) {
    int i = matchTentative(systemName);
    if (i >= 0)
        return ((AbstractTurnoutManager*)getMgr(i))->allowMultipleAdditions(systemName);
    return ((TurnoutManager*)getMgr(0))->allowMultipleAdditions(systemName);
}

/*public*/ QString ProxyTurnoutManager::createSystemName(QString curAddress, QString prefix)const throw (JmriException)
{
 for (int i=0; i<nMgrs(); i++)
 {
  if ( prefix==(((AbstractTurnoutManager*)getMgr(i))->getSystemPrefix()) )
  {
   try
   {
    return ((AbstractTurnoutManager*)getMgr(i))->createSystemName(curAddress, prefix);
   }
   catch (JmriException ex)
   {
    throw ex;
   }
  }
 }
 throw new JmriException("Turnout Manager could not be found for System Prefix " + prefix);
}

/*public*/ QString ProxyTurnoutManager::getNextValidAddress(QString curAddress, QString prefix) const throw (JmriException)
{
 for (int i=0; i<nMgrs(); i++)
 {
  if ( prefix==( ((AbstractTurnoutManager*)getMgr(i))->getSystemPrefix()) )
  {
   try
   {
    return ((AbstractTurnoutManager*)getMgr(i))->getNextValidAddress(curAddress, prefix);
   }
   catch (JmriException ex)
   {
    throw ex;
   }
  }
 }
 return NULL;
}

/*public*/ void ProxyTurnoutManager::setDefaultClosedSpeed(QString speed) const throw (JmriException) {
    for (int i=0; i<nMgrs(); i++) {
        try {
            ((AbstractTurnoutManager*)getMgr(i))->setDefaultClosedSpeed(speed);
        } catch (JmriException ex) {
            log.error(ex.toString());
            throw ex;
        }
    }
}

/*public*/ void ProxyTurnoutManager::setDefaultThrownSpeed(QString speed) const throw (JmriException){
    for (int i=0; i<nMgrs(); i++) {
        try {
            ((AbstractTurnoutManager*)getMgr(i))->setDefaultThrownSpeed(speed);
        } catch (JmriException ex) {
            log.error(ex.toString());
            throw ex;
        }
    }
}

/*public*/ QString ProxyTurnoutManager::getDefaultThrownSpeed() const{
    return ((AbstractTurnoutManager*)getMgr(0))->getDefaultThrownSpeed();
}

/*public*/ QString ProxyTurnoutManager::getDefaultClosedSpeed() const{
    return ((AbstractTurnoutManager*)getMgr(0))->getDefaultClosedSpeed();
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
  QStringList nameList = getSystemNameList();
  QStringList completerList;
  foreach(QString systemName, nameList)
  {
   Turnout* b = (Turnout*)getBySystemName(systemName);
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
