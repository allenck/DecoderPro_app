#include "abstractsensormanager.h"
#include <QDebug>
#include "abstractmanager.h"
#include "sensor.h"
#include "jmriexception.h"


AbstractSensorManager::AbstractSensorManager(QObject *parent) :
    AbstractManager(nullptr, parent)
{
 sensorDebounceGoingActive = 0L;
 sensorDebounceGoingInActive = 0L;
 //numberMatcher =  new QRegExp("\\d++")/*.matcher("")*/;
 log = new Logger("AbstractSensorManager");
}

AbstractSensorManager::AbstractSensorManager(SystemConnectionMemo* memo, QObject *parent) :
    AbstractManager(memo, parent)
{
 sensorDebounceGoingActive = 0L;
 sensorDebounceGoingInActive = 0L;
 //numberMatcher =  new QRegExp("\\d++")/*.matcher("")*/;
 log = new Logger("AbstractSensorManager");
}

/**
 * Abstract base implementation of the SensorManager interface.
 * @author			Bob Jacobsen Copyright (C) 2001, 2003
 * @version			$Revision: 19561 $
 */
//public abstract class AbstractSensorManager extends AbstractManager implements SensorManager {

/*public AbstractSensorManager(){
    super(Manager.SENSORS);
}*/

/*public*/ int AbstractSensorManager::getXMLOrder()const{
    return Manager::SENSORS;
}

/*public*/ QChar AbstractSensorManager::typeLetter() const { return 'S'; }

/*public*/ Sensor* AbstractSensorManager::provideSensor(QString name)
{
 Sensor* t = getSensor(name);
 if (t!=nullptr) return t;
 if (isNumber(name))
     return newSensor(AbstractManager::makeSystemName(name), nullptr);
 else
     return newSensor(name, nullptr);
}

/*public*/ Sensor* AbstractSensorManager::getSensor(QString name)
{
 Sensor* t = ( Sensor*)getByUserName(name);
 if (t!=nullptr) return t;

 return ( Sensor*)getBySystemName(name);
}

//static final java.util.regex.Matcher numberMatcher = java.util.regex.Pattern.compile("\\d++").matcher("");
bool AbstractSensorManager::isNumber(QString s) const
{
 //        synchronized(numberMatcher) {
 //            return numberMatcher.reset(s).matches();
 //        }
 if(s.isEmpty())
   return false;
 QStringList list;
 int pos =0;
 QRegExp nm("\\d+");
 //numberMatcher.setPattern("\\d++");
 while((pos = nm.indexIn(s,pos))!=-1)
 {
  list << nm.cap(1);
  pos += nm.matchedLength();
 }
 return(list.count()==1);
}

/*public*/ NamedBean* AbstractSensorManager::getBySystemName(QString key) {
 if (isNumber(key))
  key = AbstractManager::makeSystemName(key);
 QString name = normalizeSystemName(key);
 if(!_tsys->contains(name))
  return nullptr;
 NamedBean* bean = _tsys->value(name);
 NamedBean* s = (bean);
//        Sensor * s = sensorMap.value(key);
 return s;
}

/*protected*/ NamedBean* AbstractSensorManager::getInstanceBySystemName(QString systemName)
{
 return getBySystemName(systemName);
}

/*public*/ NamedBean* AbstractSensorManager::getByUserName(QString key)
{
 if(_tuser == nullptr)
  return nullptr;
 return (_tuser->value(key));
}

/*protected*/ QString AbstractSensorManager::normalizeSystemName(QString sysName) const {
    return sysName;
}

/*public*/ Sensor* AbstractSensorManager::newSensor(QString sysName, QString userName)
{
 QString systemName = sysName; //normalizeSystemName(sysName);
 if (log->isDebugEnabled()) log->debug("newSensor:"
                                     +( (systemName=="") ? "NULL" : systemName)
                                     +";"+( (userName=="") ? "NULL" : userName));
 if (systemName == "")
 {
  log->error("SystemName cannot be NULL. UserName was "
             +( (userName=="") ? "null" : userName));
  throw new IllegalArgumentException(QString("SystemName cannot be NULL. UserName was %1").arg(( (userName=="") ? "NULL" : userName)));
 }

 systemName = AbstractManager::validateSystemNameFormat(sysName);
 // return existing if there is one
  NamedBean* s = nullptr;
  if ((userName != "") && ((s = getByUserName(userName)) != nullptr))
  {
     if (getBySystemName(sysName) != s) {
         log->error(tr("inconsistent user (%1) and system name (%2) results; userName related to (%3)").arg(userName).arg(sysName).arg(s->getSystemName()));
     }
     return (Sensor*)s;
  }
  if ((s = getBySystemName(sysName)) != nullptr)
  {
      if ((s->getUserName() == "") && (userName != "")) {
          s->setUserName(userName);
      } else if (userName != "") {
          log->warn(tr("Found sensor via system name (%1) with non-null user name (%2). Sensor \"%3(%4)\" cannot be used.").arg(
                  sysName).arg(s->getUserName()).arg(sysName).arg(userName));
      }
      return (Sensor*)s;
  }

 // doesn't exist, make a new one
 s = createNewSensor(systemName, userName);

 //emit newSensorCreated(this, s);

 //  if that failed, blame it on the input arguements
 if (s == nullptr) throw  IllegalArgumentException();

 // save in the maps
 AbstractManager::Register(s);
 emit propertyChange(new PropertyChangeEvent((QObject*)this, "length", QVariant(), QVariant(_tsys->size()))); // is this necessary here?
 //emit newSensorCreated(this, s);
 return (Sensor*)s;
}

/** {@inheritDoc} */
//@Override
/*public*/ QString AbstractSensorManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "Sensors" : "Sensor");
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString AbstractSensorManager::getNamedBeanClass() const {
    return "Sensor";
}
/**
 * Requests status of all layout sensors under this Sensor Manager.
 * This method may be invoked whenever the status of sensors needs to be updated from
 *		the layout, for example, when an XML configuration file is read in.
 * Note that this NULL implementation only needs be implemented in system-specific
 *		Sensor Managers where readout of sensor status from the layout is possible.
 */
/*public*/ void AbstractSensorManager::updateAll() const { }

/**
* A method that determines if it is possible to add a range of sensors in numerical
* order eg 10 to 30, primarily used to enable/disable the add range box in the add sensor panel
**/

/*public*/ bool AbstractSensorManager::allowMultipleAdditions(QString systemName) { return false;  }

/*public*/ QString AbstractSensorManager::createSystemName(QString curAddress, QString prefix) /*throw (JmriException)*/{
 try
 {
  bool bOk;
  int iCurAddress = curAddress.toInt(&bOk);
  //Integer.parseInt(curAddress);
  if(!bOk) throw new NumberFormatException("Hardware Address passed should be a number");
 }
 catch (NumberFormatException* ex)
 {
  log->error(tr("Hardware Address passed should be a number"));
  throw new JmriException("Hardware Address passed should be a number");
 }
 return prefix+typeLetter()+curAddress;
}

/*public*/ QString AbstractSensorManager::getNextValidAddress(QString curAddress, QString prefix)
{
 //If the hardware address passed does not already exist then this can
 //be considered the next valid address.
 QString tmpSName = "";

//        try {
 tmpSName = createSystemName(curAddress, prefix);
//        } catch (JmriException* ex) {
//            jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).
//                    showInfoMessage("Error","Unable to convert " + curAddress + " to a valid Hardware Address",""+ex, "",true, false, org.apache.log4j.Level.ERROR);
//            return NULL;
//        }
 NamedBean* s = getBySystemName(tmpSName);
 if(s==nullptr)
 {
  return curAddress;
 }

 // This bit deals with handling the curAddress, and how to get the next address.
 int iName = 0;
 //try {
    //iName = Integer.parseInt(curAddress);
 iName = curAddress.toInt();
//        } catch (NumberFormatException* ex) {
//            log.error("Unable to convert " + curAddress + " Hardware Address to a number");
//            jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).
//                                showInfoMessage("Error","Unable to convert " + curAddress + " to a valid Hardware Address",""+ex, "",true, false, org.apache.log4j.Level.ERROR);
//            return NULL;
//        }

 //Check to determine if the systemName is in use, return NULL if it is,
 //otherwise return the next valid address.
 s = getBySystemName(prefix+typeLetter()+iName);
 if(s!=nullptr)
 {
  for(int x = 1; x<10; x++)
  {
   iName++;
   s = getBySystemName(prefix+typeLetter()+iName);
   if(s==nullptr)
//                    return Integer.toString(iName);
    return QString("%1").arg(iName);
  }
  return nullptr;
 }
 else
 {
  //return Integer.toString(iName);
  return QString("%1").arg(iName);
 }
}


/*public*/ long AbstractSensorManager::getDefaultSensorDebounceGoingActive() { return sensorDebounceGoingActive; }
/*public*/ long AbstractSensorManager::getDefaultSensorDebounceGoingInActive() { return sensorDebounceGoingInActive; }

/*public*/ void AbstractSensorManager::setDefaultSensorDebounceGoingActive(long timer)
{
 if(timer == sensorDebounceGoingActive)
  return;
 sensorDebounceGoingActive=timer;
 //Enumeration<QString> en = _tsys.keys();
 QMapIterator<QString, NamedBean*> en(*_tsys);
 //QMapIterator<QString, Sensor*> en(sensorMap);
 while (en.hasNext())
 {
  en.next();
  //Sensor* sen = dynamic_cast<Sensor*>(_tsys->value(en.key()));
  Sensor* sen = (Sensor*)en.value();

  if(sen->useDefaultTimerSettings())
   sen->setSensorDebounceGoingActiveTimer(timer);
 }
}

/*public*/ void AbstractSensorManager::setDefaultSensorDebounceGoingInActive(long timer)
{
 if(timer == sensorDebounceGoingInActive)
  return;
 sensorDebounceGoingInActive=timer;
 //Enumeration<String> en = _tsys.keys();
 QMapIterator<QString, NamedBean*> en(*_tsys);
 //QMapIterator<QString, Sensor*> en(sensorMap);
 while (en.hasNext())
  {
   en.next();
   //            Sensor* sen = dynamic_cast<Sensor*>(_tsys->value(en.key()));
   Sensor* sen = (Sensor*)en.value();
   if(sen->useDefaultTimerSettings())
    sen->setSensorDebounceGoingInActiveTimer(timer);
  }
}

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractSensorManager.class.getName());
