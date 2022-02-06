#include "proxysensormanager.h"
#include "internalsystemconnectionmemo.h"
#include "instancemanager.h"
#include "abstractsensormanager.h"

ProxySensorManager::ProxySensorManager(QObject *parent) : AbstractProvidingProxyManager(parent)
{
 setObjectName("ProxySensorManager");
 //qDebug() << "ProxySensorManger created";
 //internalManager = makeInternalManager();
 //registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!
 //propertyChangeSupport = new SwingPropertyChangeSupport(this,this);

}
/**
 * Implementation of a SensorManager that can serves as a proxy
 * for multiple system-specific implementations.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2010
 * @version	$Revision: 21120 $
 */
//public class ProxySensorManager extends AbstractProxyManager
//                            implements SensorManager {

//    public ProxySensorManager() {
//        super();
//    }

//@Override
/*protected*/ AbstractManager* ProxySensorManager::makeInternalManager() const
{
 AbstractManager* manager = (AbstractManager*)((InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo"))->getSensorManager();
 return manager;
}

/**
     * Locate via user name, then system name if needed.
     *
     * @return Null if nothing by that name exists
     */
//@Override
//@CheckForNull
/*public*/ Sensor* ProxySensorManager::getSensor(QString name) {
 return (Sensor*)AbstractProxyManager::getNamedBean(name);
}


/** {@inheritDoc} */
//@Override
//@Nonnull
/*protected*/ Sensor* ProxySensorManager::makeBean(AbstractManager* manager, QString systemName, QString userName)
{
 return ((AbstractSensorManager*) manager)->newSensor(systemName, userName);
}

//@Override
//@Nonnull
/*public*/ Sensor* ProxySensorManager::provideSensor(QString sName)
{
 return (Sensor*)(provideNamedBean(sName));
}

/** {@inheritDoc} */
 //@Override
 //@Nonnull
 /*public*/ Sensor* ProxySensorManager::provide(/*@Nonnull*/ QString name) /*throws IllegalArgumentException*/ { return provideSensor(name); }
/**
 * Locate an instance based on a system name.  Returns null if no
 * instance already exists.
 * @return requested Turnout object or null if none exists
 */
///*public*/ Sensor *ProxySensorManager::getBySystemName(QString sName) const{
//    return (Sensor*) AbstractProxySensorManager::getBeanBySystemName(sName);
//}

/**
 * Locate an instance based on a user name.  Returns null if no
 * instance already exists.
 * @return requested Turnout object or null if none exists
 */
///*public*/ Sensor* ProxySensorManager::getByUserName(QString userName) const{
//    return (Sensor*) AbstractProxySensorManager::getBeanByUserName(userName);
//}


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
/*public*/ Sensor* ProxySensorManager::newSensor(QString systemName, QString userName) {
    return (Sensor*) newNamedBean(systemName, userName);
}

///*public*/ NamedBean* ProxySensorManager::newNamedBean(QString systemName, QString userName) {
//    // if the systemName is specified, find that system
//    int i = matchTentative(systemName);
//    if (i >= 0)
//        return makeBean(i, systemName, userName);

//    // did not find a manager, allow it to default to the primary
//    log.debug("Did not find manager for system name "+systemName+", delegate to primary");
//    return makeBean(0, systemName, userName);
//}

// null implementation to satisfy the SensorManager interface
/*public*/ void ProxySensorManager::updateAll() const {  }

/*public*/ bool ProxySensorManager::allowMultipleAdditions(QString systemName)
{
 return ((SensorManager*) getManagerOrDefault(systemName))->allowMultipleAdditions(systemName);
}

///*public*/ QString ProxySensorManager::createSystemName(QString curAddress, QString prefix) const /*throw (JmriException)*/
//{
// for (int i=0; i<nMgrs(); i++)
// {
//  if ( prefix==( ((SensorManager*)getMgr(i))->getSystemPrefix()) )
//  {
//   try
//   {
//    return ((AbstractSensorManager*)getMgr(i))->createSystemName(curAddress, prefix);
//   } catch (JmriException* ex)
//   {
//    log.error(ex.toString());
//    throw ex;
//   }
//  }
// }
// throw new JmriException("Sensor Manager could not be found for System Prefix " + prefix);
//}

//@SuppressWarnings("deprecation") // user warned by actual manager class
//@Override
/*public*/ QString ProxySensorManager::getNextValidAddress(QString curAddress, QString prefix) /*throw (JmriException)*/
{
 return AbstractProxyManager::getNextValidAddress(curAddress, prefix, AbstractProxyManager::typeLetter());
}

//@Override
/*public*/ QString ProxySensorManager::getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting) /*throw (JmriException)*/ {
    return AbstractProxyManager::getNextValidAddress(curAddress, prefix, ignoreInitialExisting, AbstractProxyManager::typeLetter());
}
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString ProxySensorManager::getEntryToolTip() {
    return "Enter a number from 1 to 9999"; // Basic number format help
}

//@Override
/*public*/ long ProxySensorManager::getDefaultSensorDebounceGoingActive(){
 return ((SensorManager*) getDefaultManager())->getDefaultSensorDebounceGoingActive();
}
//@Override
/*public*/ long ProxySensorManager::getDefaultSensorDebounceGoingInActive(){
 return ((SensorManager*) getDefaultManager())->getDefaultSensorDebounceGoingInActive();
}
//@Override
/*public*/ void ProxySensorManager::setDefaultSensorDebounceGoingActive(long timer){
    for (Manager/*<E>*/* m : getManagerList()) {
        ((AbstractSensorManager*)m->self())->setDefaultSensorDebounceGoingActive(timer);
    }
}
//@Override
/*public*/ void ProxySensorManager::setDefaultSensorDebounceGoingInActive(long timer){
    for (Manager/*<E>*/* m : getManagerList()) {
        ((AbstractSensorManager*)m->self())->setDefaultSensorDebounceGoingInActive(timer);
    }
}

//@Override
/*public*/ int ProxySensorManager::getXMLOrder() const{
    return Manager::SENSORS;
}

// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ProxySensorManager.class.getName());
//}

/* @(#)ProxySensorManager.java */
///*private*/ AbstractManager* ProxySensorManager::getInternal()
//{
// if (internalManager == NULL)
//  internalManager = makeInternalManager();
// return internalManager;
//}
QCompleter* ProxySensorManager::getCompleter(QString text)
{
 if(text.length()>0)
 {
  QStringList nameList = AbstractProxyManager::getSystemNameList();
  QStringList completerList;
  bool bOk;
  foreach(QString systemName, nameList)
  {
   Sensor* s = (Sensor*)AbstractProxyManager::getBySystemName(systemName);
   if(s->getUserName().startsWith(text,Qt::CaseInsensitive))
    completerList.append(s->getUserName());
   if(systemName.startsWith(text,Qt::CaseInsensitive))
    completerList.append(systemName);

   int iNum = text.toInt(&bOk);
   Q_UNUSED(iNum);
   if(bOk && systemName.contains(text))
    completerList.append(systemName);
   if(bOk && s->getUserName().contains(text))
    completerList.append(s->getUserName());
  }
  if(completerList.size() > 0)
  {
   QCompleter* completer = new QCompleter(completerList, this);
    return completer;
  }
 }
 return nullptr;
}

/**
 * Do the sensor objects provided by this manager support configuring
 * an internal pull up or pull down resistor?
 *
 * @return true if pull up/pull down configuration is supported,
 * default to false to satisfy the SensorManager interface
 */
//@Override
/*public*/ bool ProxySensorManager::isPullResistanceConfigurable(){
   return false;
}
