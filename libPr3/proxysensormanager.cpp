#include "proxysensormanager.h"
#include "internalsystemconnectionmemo.h"
#include "instancemanager.h"
#include "abstractsensormanager.h"

ProxySensorManager::ProxySensorManager(QObject *parent) : AbstractProxySensorManager(parent)
{
 setObjectName("ProxySensorManager");
 //qDebug() << "ProxySensorManger created";
 //internalManager = makeInternalManager();
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

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

/*protected*/ Manager* ProxySensorManager::makeInternalManager() const
{
 Manager* manager = (Manager*)((InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo"))->getSensorManager();
 return manager;
}

/**
 * Locate via user name, then system name if needed.
 *
 * @param name
 * @return Null if nothing by that name exists
 */
/*public*/ Sensor* ProxySensorManager::getSensor(QString name) {
 return (Sensor*)AbstractProxySensorManager::getNamedBean(name);
}

/*protected*/ Sensor* ProxySensorManager::makeBean(int i, QString systemName, QString userName)
{
 log.debug(tr("makeBean(%1, \"%2\", \"%3\"").arg(i).arg(systemName).arg(userName));
 Sensor* sensor =  ((SensorManager*)getMgr(i))->newSensor(systemName, userName);
 //emit newSensorCreated((AbstractSensorManager*)getMgr(i),sensor);
 return sensor;
}

/*public*/ Sensor* ProxySensorManager::provideSensor(QString sName)
{
 return static_cast<Sensor*>(AbstractProxySensorManager::provideNamedBean(sName));
}


/**
 * Locate an instance based on a system name.  Returns null if no
 * instance already exists.
 * @return requested Turnout object or null if none exists
 */
/*public*/ Sensor *ProxySensorManager::getBySystemName(QString sName) {
    return (Sensor*) AbstractProxySensorManager::getBeanBySystemName(sName);
}

/**
 * Locate an instance based on a user name.  Returns null if no
 * instance already exists.
 * @return requested Turnout object or null if none exists
 */
/*public*/ Sensor* ProxySensorManager::getByUserName(QString userName) {
    return (Sensor*) AbstractProxySensorManager::getBeanByUserName(userName);
}


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
/*public*/ void ProxySensorManager::updateAll() {  }

/*public*/ bool ProxySensorManager::allowMultipleAdditions(QString systemName)
{
    int i = matchTentative(systemName);
    if (i >= 0)
        return ((SensorManager*)getMgr(i))->allowMultipleAdditions(systemName);
    return ((SensorManager*)getMgr(0))->allowMultipleAdditions(systemName);
}

/*public*/ QString ProxySensorManager::createSystemName(QString curAddress, QString prefix) throw (JmriException)
{
 for (int i=0; i<nMgrs(); i++)
 {
  if ( prefix==( ((SensorManager*)getMgr(i))->getSystemPrefix()) )
  {
   try
   {
    return ((AbstractSensorManager*)getMgr(i))->createSystemName(curAddress, prefix);
   } catch (JmriException ex)
   {
    log.error(ex.toString());
    throw ex;
   }
  }
 }
 throw new JmriException("Sensor Manager could not be found for System Prefix " + prefix);
}

/*public*/ QString ProxySensorManager::getNextValidAddress(QString curAddress, QString prefix) throw (JmriException)
{
 for (int i=0; i<nMgrs(); i++)
 {
  if ( prefix==( ((SensorManager*)getMgr(i))->getSystemPrefix()) )
  {
   try
   {
    return ((SensorManager*)getMgr(i))->getNextValidAddress(curAddress, prefix);
   }
   catch (JmriException ex)
   {
    throw ex;
   }
  }
 }
 return nullptr;
}

/*public*/ long ProxySensorManager::getDefaultSensorDebounceGoingActive(){
    return ((AbstractSensorManager*)getMgr(0))->getDefaultSensorDebounceGoingActive();
}
/*public*/ long ProxySensorManager::getDefaultSensorDebounceGoingInActive(){
    return ((AbstractSensorManager*)getMgr(0))->getDefaultSensorDebounceGoingInActive();
}

/*public*/ void ProxySensorManager::setDefaultSensorDebounceGoingActive(long timer){
    for (int i=0; i<nMgrs(); i++) {
        ((AbstractSensorManager*)getMgr(i))->setDefaultSensorDebounceGoingActive(timer);
    }
}

/*public*/ void ProxySensorManager::setDefaultSensorDebounceGoingInActive(long timer){
    for (int i=0; i<nMgrs(); i++) {
        ((AbstractSensorManager*)getMgr(i))->setDefaultSensorDebounceGoingInActive(timer);
    }
}

/*public*/ int ProxySensorManager::getXMLOrder(){
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
  QStringList nameList = getSystemNameList();
  QStringList completerList;
  bool bOk;
  foreach(QString systemName, nameList)
  {
   Sensor* s = getBySystemName(systemName);
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
