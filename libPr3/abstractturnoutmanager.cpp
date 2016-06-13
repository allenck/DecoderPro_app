#include "abstractturnoutmanager.h"
#include <QStringList>
#include "exceptions.h"
#include "instancemanager.h"

AbstractTurnoutManager::AbstractTurnoutManager(QObject *parent) :
    TurnoutManager(parent)
{
 log = new Logger("AbstractTurnoutManager");
 registerSelf();
 TurnoutOperationManager::getInstance();		// force creation of an instance
 defaultClosedSpeed = "Normal";
 defaultThrownSpeed = "Restricted";
 //turnoutMap.clear();
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

int AbstractTurnoutManager::getXMLOrder(){
    return Manager::TURNOUTS;
}
    //protected int xmlorder = 20;
char AbstractTurnoutManager::typeLetter() { return 'T'; }

Turnout* AbstractTurnoutManager::provideTurnout(QString name)
{
    Turnout* t = getTurnout(name);
    if (t!=NULL) return t;
    if (name.startsWith(getSystemPrefix().mid(0,1)+QString(typeLetter())))
        return newTurnout(name, NULL);
    else
        return newTurnout(makeSystemName(name), NULL);
}

Turnout* AbstractTurnoutManager::getTurnout(QString name) {
    Turnout* t = getByUserName(name);
    if (t!=NULL) return t;

    return getBySystemName(name);
}

Turnout* AbstractTurnoutManager::getBySystemName(QString name)
{
 NamedBean* bean = _tsys->value(name);
 //return NULL;
 return (Turnout*)bean;
// if(turnoutMap.contains(name))
//     return (Turnout*)turnoutMap.value(name);
// return (Turnout*)NULL;
}

Turnout* AbstractTurnoutManager::getByUserName(QString key)
{
 NamedBean* bean = _tuser->value(key);
 //return NULL;
 return (Turnout*)bean;
// int addr = userName.toInt();
// QMapIterator<QString, Turnout*> i(turnoutMap);
// while(i.hasNext())
// {
//  i.next();
//  if(((LnTurnout*)i.value())->getNumber() == addr)
//   return (Turnout*)i.value();
//  return (Turnout*)NULL;
// }
// return NULL;
}

Turnout* AbstractTurnoutManager::newTurnout(QString systemName, QString userName)
{
 //if (log->isDebugEnabled()) log->debug(QString("newTurnout: %1").arg(( (systemName==NULL) ? "NULL" : systemName)));
 if (systemName == NULL)
 {
  log->error(QString("SystemName cannot be NULL. UserName was %1").arg(( (userName==NULL) ? "NULL" : userName)));
  throw new IllegalArgumentException(QString("SystemName cannot be NULL. UserName was %1").arg(( (userName==NULL) ? "NULL" : userName)));
 }
 // is system name in correct format?
 QString neededPrefix = QString("%1%2").arg(getSystemPrefix().mid(0,1)).arg(QString(typeLetter()));
 if (!systemName.startsWith(neededPrefix))
 {
  log->error(QString("Invalid system name for turnout: %1").arg(systemName
                        +" needed "+ neededPrefix));
  throw new IllegalArgumentException(QString("Invalid system name for turnout: %1  needed %2").arg(systemName).arg(neededPrefix));
 }

 // return existing if there is one
 Turnout* s;
 if ( (userName!=NULL) && ((s = getByUserName(userName)) != NULL))
 {
  if (getBySystemName(systemName)!=s)
   log->error(QString("inconsistent user (%1) and system name (%2) results; userName related to (%3)").arg(userName).arg(systemName).arg(s->getSystemName()));
  return s;
 }
 if ( (s = getBySystemName(systemName)) != NULL)
 {
  if ((s->getUserName() == NULL) && (userName != NULL))
   s->setUserName(userName);
  else if (userName != NULL) log->warn(QString("Found turnout via system name (%1) with non-NULL user name (%2)").arg(systemName).arg(userName));
  return s;
 }

 // doesn't exist, make a new one
 s = createNewTurnout(systemName, userName);

 // if that failed, blame it on the input arguements
 //if (s == NULL) throw new IllegalArgumentException(QString("Unable to create turnout from %1").arg(systemName));
 if(s == NULL)
 {
  log->error(QString("Unable to create turnout from %1 %2").arg(systemName).arg(userName));
  return NULL;
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
 * @return never NULL
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

 if (InstanceManager::commandStationInstance()!=NULL)
 {
  return QString("Sensor,Raw,NoFeedback").split(",");
 }
 else
 {
  return  QString("Sensor,NoFeedback").split(",");
 }

 return QStringList();
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
     log->error("Hardware Address passed should be a number", "ex");
     //throw new JmriException("Hardware Address passed should be a number");
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
    } catch (JmriException *ex) {
//        InstanceManager::getDefault("UserPreferencesManager")->
//            showInfoMessage(QString("Error","Unable to convert %1 to a valid Hardware Address %2").arg(curAddress).arg(ex);
        return NULL;
    }

    Turnout* t = getBySystemName(tmpSName);
    if(t==NULL){
        return curAddress;
    }

    // This bit deals with handling the curAddress, and how to get the next address.
    int iName = 0;
    try {
        iName = curAddress.toInt();
    } catch (NumberFormatException *ex) {
//        log->error("Unable to convert %1 Hardware Address to a number").arg(curAddress);
//        InstanceManager.getDefault(jmri.UserPreferencesManager.class).
//                            showInfoMessage("Error","Unable to convert " + curAddress + " to a valid Hardware Address",""+ex, "",true, false, org.apache.log4j.Level.ERROR);
        return NULL;
    }
    //The Number of Output Bits of the previous turnout will help determine the next
    //valid address.
    iName = iName + t->getNumberOutputBits();
    //Check to determine if the systemName is in use, return NULL if it is,
    //otherwise return the next valid address.
    t = getBySystemName(prefix+typeLetter()+iName);
    if(t!=NULL){
        for(int x = 1; x<10; x++){
            iName = iName + t->getNumberOutputBits();
            t = getBySystemName(prefix+typeLetter()+iName);
            if(t==NULL)
                return QString("%1").arg(iName);
        }
        return NULL;
    } else {
        return QString("%1").arg(iName);
    }
}



//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="NP_NULL_PARAM_DEREF", justification="We are validating user input however the value is stored in its original format")
void AbstractTurnoutManager::setDefaultClosedSpeed(QString speed) //throws JmriException
{
//    if(speed==NULL)
//        throw new JmriException("Value of requested turnout default closed speed can not be NULL");
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
  try
  {
   //Float.parseFloat(speed);
   speed.toFloat();
  }
  catch (NumberFormatException *nx)
  {
//            try{
//                jmri.implementation.SignalSpeedMap.getMap().getSpeed(speed);
//            } catch (Exception ex){
//                throw new JmriException("Value of requested turnout default closed speed is not valid");
//            }
  }
 }
 QString oldSpeed = defaultClosedSpeed;
 defaultClosedSpeed = speed;
 firePropertyChange("DefaultTurnoutClosedSpeedChange", oldSpeed, speed);
}
void AbstractTurnoutManager::setDefaultThrownSpeed(QString speed)// throws JmriException
{
//    if(speed==NULL)
//        throw new JmriException("Value of requested turnout default thrown speed can not be NULL");
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
  try
  {
   //Float.parseFloat(speed);
   speed.toFloat();
  }
  catch (NumberFormatException *nx)
  {
//            try{
//                jmri.implementation.SignalSpeedMap.getMap().getSpeed(speed);
//            } catch (Exception ex){
//                throw new JmriException("Value of requested turnout default thrown speed is not valid");
//            }
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

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractTurnoutManager.class.getName());
