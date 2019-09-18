#include "abstractturnoutmanager.h"
#include <QStringList>
#include "exceptions.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "userpreferencesmanager.h"
#include "signalspeedmap.h"

AbstractTurnoutManager::AbstractTurnoutManager(SystemConnectionMemo* memo, QObject *parent) :
    TurnoutManager(memo, parent)
{
 this->memo = memo;
 defaultClosedSpeed = "Normal";
 defaultThrownSpeed = "Restricted";
 //registerSelf(); //??
 TurnoutOperationManager::getInstance();		// force creation of an instance
 // ((SensorManager*)InstanceManager::sensorManagerInstance())->addVetoableChangeListener(this);
 // TODO:: connect(InstanceManager::sensorManagerInstance()->vcs, SIGNAL(vetoablePropertyChange(PropertyChangeEvent*)), this, SLOT(vetoableChange(PropertyChangeEvent*)));
}
/**
 * Abstract partial implementation of a TurnoutManager.
 *
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version			$Revision: 22324 $
 */
//public abstract class AbstractTurnoutManager extends AbstractManager
//    implements TurnoutManager {

//	public AbstractTurnoutManager() {
//        //super(Manager.TURNOUTS);
//		TurnoutOperationManager.getInstance();		// force creation of an instance
//	}

// @Override
/*public*/ SystemConnectionMemo* AbstractTurnoutManager::getMemo() {
    return memo;
}

int AbstractTurnoutManager::getXMLOrder(){
    return Manager::TURNOUTS;
}

//protected int xmlorder = 20;
char AbstractTurnoutManager::typeLetter() { return 'T'; }

Turnout* AbstractTurnoutManager::provideTurnout(QString name)
{
    Turnout* t = getTurnout(name);
    if (t!=nullptr) return t;
    if (name.startsWith(getSystemPrefix().mid(0,1)+QString(typeLetter())))
        return newTurnout(name, nullptr);
    else
        return newTurnout(makeSystemName(name), nullptr);
}

Turnout* AbstractTurnoutManager::getTurnout(QString name) {
    Turnout* t = getByUserName(name);
    if (t!=nullptr) return t;

    return getBySystemName(name);
}

Turnout* AbstractTurnoutManager::getBySystemName(QString name)
{
 NamedBean* bean = _tsys->value(name);
 //return nullptr;
 return (Turnout*)bean;
// if(turnoutMap.contains(name))
//     return (Turnout*)turnoutMap.value(name);
// return (Turnout*)nullptr;
}

Turnout* AbstractTurnoutManager::getByUserName(QString key)
{
 NamedBean* bean = _tuser->value(key);
 //return nullptr;
 return (Turnout*)bean;
// int addr = userName.toInt();
// QMapIterator<QString, Turnout*> i(turnoutMap);
// while(i.hasNext())
// {
//  i.next();
//  if(((LnTurnout*)i.value())->getNumber() == addr)
//   return (Turnout*)i.value();
//  return (Turnout*)nullptr;
// }
// return nullptr;
}

Turnout* AbstractTurnoutManager::newTurnout(QString systemName, QString userName)
{
 // add normalize? see AbstractSensor
 if (log->isDebugEnabled()) log->debug(QString("newTurnout: %1").arg(( (systemName=="") ? "null" : systemName)));

 // is system name in correct format?
 if (!systemName.startsWith(getSystemPrefix() + typeLetter())
                 || !(systemName.length() > (getSystemPrefix() + typeLetter()).length()))
 {
     log->error(tr("Invalid system name for turnout: %1 needed %2%3").arg(
             systemName).arg(getSystemPrefix()).arg(typeLetter()));
     throw IllegalArgumentException("Invalid system name for turnout: " + systemName
             + " needed " + getSystemPrefix() + typeLetter());
 }

 // return existing if there is one
 Turnout* s;
 if ( (userName!=nullptr) && ((s = getByUserName(userName)) != nullptr))
 {
  if (getBySystemName(systemName)!=s)
   log->error(QString("inconsistent user (%1) and system name (%2) results; userName related to (%3)").arg(userName).arg(systemName).arg(s->getSystemName()));
  return s;
 }
 if ( (s = getBySystemName(systemName)) != nullptr)
 {
  if ((s->getUserName() == nullptr) && (userName != nullptr))
   s->setUserName(userName);
  else if (userName != nullptr) log->warn(QString("Found turnout via system name (%1) with non-nullptr user name (%2)").arg(systemName).arg(userName));
  return s;
 }

 // doesn't exist, make a new one
 s = createNewTurnout(systemName, userName);

 // if that failed, blame it on the input arguements
 //if (s == nullptr) throw new IllegalArgumentException(QString("Unable to create turnout from %1").arg(systemName));
 if(s == nullptr)
 {
  throw IllegalArgumentException(tr("Unable to create turnout from %1 %2").arg(systemName).arg(userName));
 }

 emit newTurnoutCreated(this, s);

 // save in the maps if successful
 Register(s);
//    turnoutMap.insert(systemName, (LnTurnout*)s);
//    try {
        ((AbstractTurnout*)s)->setStraightSpeed("Global");
//    } catch (JmriException *ex){
//        log->error(ex->toString());
//    }

//    try {
        ((AbstractTurnout*)s)->setDivergingSpeed("Global");
//    } catch (JmriException *ex){
//        log->error(ex->toString());
//    }
 return s;
}

/*\\\\\\\\\\\ * Get text to be used for the Turnout.CLOSED state in user communication.
 * Allows text other than "CLOSED" to be use with certain hardware system
 * to represent the Turnout.CLOSED state.
 */
QString AbstractTurnoutManager::getClosedText() { return tr("Closed"); }

/**
 * Get text to be used for the Turnout.THROWN state in user communication.
 * Allows text other than "THROWN" to be use with certain hardware system
 * to represent the Turnout.THROWN state.
 */
QString AbstractTurnoutManager::getThrownText() { return tr("Thrown"); }

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
int AbstractTurnoutManager::askNumControlBits(QString systemName) {Q_UNUSED(systemName); return 1; }

bool AbstractTurnoutManager::isNumControlBitsSupported(QString systemName)
 { Q_UNUSED(systemName); return false; }

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
int AbstractTurnoutManager::askControlType(QString systemName) { Q_UNUSED(systemName); return 0; }

 bool AbstractTurnoutManager::isControlTypeSupported(QString systemName) { Q_UNUSED(systemName);  return false; }

/**
 * Internal method to invoke the factory, after all the
 * logic for returning an existing method has been invoked.
 * @return never nullptr
 */
//Turnout AbstractTurnoutManager::createNewTurnout(QString systemName, QString userName);

/*
 * Provide list of supported operation types.
 * <p>
 * Order is important because
 * they will be tried in the order specified.
 */
QStringList AbstractTurnoutManager::getValidOperationTypes()
{

 if (InstanceManager::getDefault("CommandStation")!=nullptr)
 {
  return QString("Sensor,Raw,NoFeedback").split(",");
 }
 else
 {
  return  QString("Sensor,NoFeedback").split(",");
 }
}

/**
* A temporary method that determines if it is possible to add a range
* of turnouts in numerical order eg 10 to 30
**/

//bool AbstractTurnoutManager::allowMultipleAdditions(QString systemName) { return true;  }

QString AbstractTurnoutManager::createSystemName(QString curAddress, QString prefix)
// throws JmriException
{
    try {
        //Integer.parseInt(curAddress);
    int i = curAddress.toInt();
    Q_UNUSED(i);
    } catch (NumberFormatException *ex)
    {
     log->warn(tr("Hardware Address passed should be a number, was %1").arg(curAddress));
     throw  JmriException("Hardware Address passed should be a number");
    }
    return prefix+typeLetter()+curAddress;
}

QString AbstractTurnoutManager::getNextValidAddress(QString curAddress, QString prefix)// throws JmriException
{
 //If the hardware address past does not already exist then this can
 //be considered the next valid address.
 QString tmpSName = "";
 try {
     tmpSName = createSystemName(curAddress, prefix);
 }
 catch (JmriException *ex)
 {
  static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))->showErrorMessage(tr("Error"),tr("Unable to convert %1 to a valid Hardware Address %2").arg(curAddress),nullptr, "", true, false);
  return nullptr;
 }

 Turnout* t = getBySystemName(tmpSName);
 if(t==nullptr)
 {
  return curAddress;
 }

 // This bit deals with handling the curAddress, and how to get the next address.
 int iName = 0;
 bool bok;
     iName = curAddress.toInt(&bok);
 if(!bok)
 {
  log->error(tr("Unable to convert %1 Hardware Address to a number").arg(curAddress));
  static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))->showErrorMessage(tr("Error"),tr("Unable to convert ") + curAddress + tr(" to a valid Hardware Address"),nullptr, "", true, false);
  return nullptr;
 }
 //The Number of Output Bits of the previous turnout will help determine the next
 //valid address.
 iName = iName + t->getNumberOutputBits();
 //Check to determine if the systemName is in use, return nullptr if it is,
 //otherwise return the next valid address.
 t = getBySystemName(prefix+typeLetter()+iName);
 if(t!=nullptr)
 {
  for(int x = 1; x<10; x++)
  {
   iName = iName + t->getNumberOutputBits();
   t = getBySystemName(prefix+typeLetter()+iName);
   if(t==nullptr)
       return QString("%1").arg(iName);
  }
  return nullptr;
 } else {
     return QString("%1").arg(iName);
 }
}



//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="NP_nullptr_PARAM_DEREF", justification="We are validating user input however the value is stored in its original format")
void AbstractTurnoutManager::setDefaultClosedSpeed(QString speed) //throws JmriException
{
//    if(speed==nullptr)
//        throw new JmriException("Value of requested turnout default closed speed can not be nullptr");
 if(defaultClosedSpeed ==(speed))
  return;
 if (speed.contains("Block"))
 {
  speed="Block";
  if(defaultClosedSpeed == (speed))
   return;
 }
 else
 {
  bool bok;
   //Float.parseFloat(speed);
   speed.toFloat(&bok);
  if(!bok)
  {
   try
   {
    static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(speed);
   }
   catch (Exception ex)
   {
    throw JmriException("Value of requested turnout default closed speed is not valid");
   }
  }
 }
 QString oldSpeed = defaultClosedSpeed;
 defaultClosedSpeed = speed;
 firePropertyChange("DefaultTurnoutClosedSpeedChange", oldSpeed, speed);
}

void AbstractTurnoutManager::setDefaultThrownSpeed(QString speed)// throws JmriException
{
//    if(speed==nullptr)
//        throw new JmriException("Value of requested turnout default thrown speed can not be nullptr");
 if (defaultThrownSpeed ==(speed))
  return;
 if (speed.contains("Block"))
 {
  speed="Block";
  if(defaultThrownSpeed==(speed))
   return;

 }
 else
 {
  bool bok;
   //Float.parseFloat(speed);
   speed.toFloat(&bok);
  if(!bok)
  {
   try{
       static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(speed);
   } catch (Exception ex){
       throw  JmriException("Value of requested turnout default thrown speed is not valid");
   }
  }
 }
 QString oldSpeed = defaultThrownSpeed;
 defaultThrownSpeed = speed;
 firePropertyChange("DefaultTurnoutThrownSpeedChange", oldSpeed, speed);
}

QString AbstractTurnoutManager::getDefaultThrownSpeed(){
    return defaultThrownSpeed;
}

QString AbstractTurnoutManager::getDefaultClosedSpeed(){
    return defaultClosedSpeed;
}

/*private*/ /*final*/ /*static*/ Logger* AbstractTurnoutManager::log = LoggerFactory::getLogger("AbstractTurnoutManager");
