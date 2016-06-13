#include "lnsensormanager.h"
#include "lnsensor.h"
#include "instancemanager.h"
#include "level.h"
#include "userpreferencesmanager.h"

/**
 * Manage the LocoNet-specific Sensor implementation.
 *
 * System names are "LSnnn", where nnn is the sensor number without padding.
 *
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version			$Revision: 18178 $
 */
/**
 * Class providing a thread to update sensor states
 */
class LnSensorUpdateThread : public QThread
{
public:
/**
 * Constructs the thread
 */
LnSensorUpdateThread (LnSensorManager* sm, LocoNetInterface* tc) {
 this->sm = sm;
 this->tc = tc;
}

/**
 * Runs the thread - sends 8 commands to query status of all stationary sensors
 *     per LocoNet PE Specs, page 12-13
 * Thread waits 500 msec between commands.
 */
void run ()
{
 sm->setUpdateBusy();
 char sw1[] = {0x78,0x79,0x7a,0x7b,0x78,0x79,0x7a,0x7b};
 char sw2[] = {0x27,0x27,0x27,0x27,0x07,0x07,0x07,0x07};
 // create and initialize loconet message
 LocoNetMessage* m = new LocoNetMessage(4);
 m->setOpCode(LnConstants::OPC_SW_REQ);
 for (int k = 0; k < 8; k++)
 {
  try
  {
   sm->thread()->msleep(500);
  }
  catch (InterruptedException e)
  {
// TODO:               QThread.currentThread().interrupt(); // retain if needed later
  }
   m->setElement(1,sw1[k]);
   m->setElement(2,sw2[k]);
   if(tc != NULL)
    tc->sendLocoNetMessage(m);
  }
  sm->setUpdateNotBusy();
 }

 LnSensorManager* sm;// = NULL;
 LocoNetInterface* tc;// = NULL;
};

LnSensorManager::LnSensorManager(LnTrafficController* tc, QString prefix, QObject *parent) :
    AbstractSensorManager(parent)
{
 setObjectName("LnSensorManager");
 registerSelf();
 this->prefix = prefix.mid(0,1);
 this->tc = tc;
 busy = false;
 defaultSensorState = Sensor::UNKNOWN;

 // ctor has to register for LocoNet events
 if(tc != NULL)
 {
  tc->addLocoNetListener(~0, (LocoNetListener*)this);
  connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 // start the update sequence.  Until JMRI 2.9.4, this waited
 // until files have been read, but was stated automatically
 // in 2.9.5 for multi-system support.
 updateAll();
}
//public class LnSensorManager extends jmri.managers.AbstractSensorManager implements LocoNetListener {

//    public LnSensorManager(LnTrafficController tc, String prefix) {
//        this.prefix = prefix;
//        this.tc = tc;
//        // ctor has to register for LocoNet events
//        tc.addLocoNetListener(~0, this);

//        // start the update sequence.  Until JMRI 2.9.4, this waited
//        // until files have been read, but was stated automatically
//        // in 2.9.5 for multi-system support.
//        updateAll();
//    }

QString LnSensorManager::getSystemPrefix()
{
 return prefix;
}

// to free resources when no longer used
void LnSensorManager::dispose() {
    tc->removeLocoNetListener(~0, (LocoNetListener*)this);
    //super.dispose();
}

    // LocoNet-specific methods

Sensor* LnSensorManager::createNewSensor(QString systemName, QString userName)
{
 LnSensor* s = new LnSensor(systemName, userName, tc, prefix);
 s->AbstractNamedBean::setUserName(userName);
 if(defaultSensorState!=Sensor::UNKNOWN){
     try {
         s->setKnownState(defaultSensorState);
     } catch (JmriException e) { log.warn("Error setting state: "+e.getMessage()); }
 }
 return (Sensor*)s;
}

// listen for sensors, creating them as needed
void LnSensorManager::message(LocoNetMessage* l)
{
 // parse message type
 LnSensorAddress* a;
 switch (l->getOpCode())
 {
  case LnConstants::OPC_INPUT_REP:                /* page 9 of Loconet PE */
  {
   int sw1 = l->getElement(1);
   int sw2 = l->getElement(2);
   a = new LnSensorAddress(sw1, sw2, prefix.mid(0,1));
   if (log.isDebugEnabled())
    log.debug("INPUT_REP received with address "+a->toString());
   break;
  }
  default:  // here we didn't find an interesting command
   return;
 }
 // reach here for loconet sensor input command; make sure we know about this one
 QString s = a->getNumericAddress();
 if (NULL == getBySystemName(s))
 {
  // need to store a new one
  if (log.isDebugEnabled()) log.debug("Create new LnSensor as "+s);
   LnSensor* ns = (LnSensor*)newSensor(s, NULL);
  ns->message(l);  // have it update state
 }
}

//    @SuppressWarnings("unused")
int LnSensorManager::address(int a1, int a2) {
    // the "+ 1" in the following converts to throttle-visible numbering
    return (((a2 & 0x0f) * 128) + (a1 & 0x7f) + 1);
}

/**
 * Requests status updates from all layout sensors.
 */
void LnSensorManager::updateAll() {
    if (!busy) {
        setUpdateBusy();
        LnSensorUpdateThread* thread = new LnSensorUpdateThread(this, tc);
        if(tc != NULL)
         thread->start();
    }
}

/**
 * Method to set Route busy when commands are being issued to
 *   Route turnouts
 */
void LnSensorManager::setUpdateBusy() {
    busy = true;
}

/**
 * Method to set Route not busy when all commands have been
 *   issued to Route turnouts
 */
void LnSensorManager::setUpdateNotBusy() {
    busy = false;
}


bool LnSensorManager::allowMultipleAdditions(QString systemName) { Q_UNUSED(systemName);  return true;  }

QString LnSensorManager::createSystemName(QString curAddress, QString prefix) // throws JmriException
{
    if(curAddress.contains(":")){
        int board = 0;
        int channel = 0;
        //Address format passed is in the form of board:channel or T:turnout address
        int seperator = curAddress.indexOf(":");
        bool turnout = false;
        if (curAddress.mid(0,seperator).toUpper()==("T")){
            turnout = true;
        } else {
            try {
                board = curAddress.mid(0,seperator).toInt();
            } catch (NumberFormatException ex) {
                log.error("Unable to convert " + curAddress + " into the cab and channel format of nn:xx");
                throw new JmriException("Hardware Address passed should be a number");
            }
        }
        try {
            channel = curAddress.mid(seperator+1).toInt();
        } catch (NumberFormatException ex) {
            log.error("Unable to convert " + curAddress + " into the cab and channel format of nn:xx");
            throw new JmriException("Hardware Address passed should be a number");
        }
        if (turnout){
            iName = 2 * (channel-1)+1;
        } else {
            iName = 16*board + channel - 16;
        }
    } else {
        //Entered in using the old format
        try {
            iName = curAddress.toInt();
        } catch (NumberFormatException ex) {
            log.error("Unable to convert " + curAddress + " Hardware Address to a number");
            throw new JmriException("Hardware Address passed should be a number");
        }
    }
    return prefix+typeLetter()+iName;

}
int iName;


QString LnSensorManager::getNextValidAddress(QString curAddress, QString prefix){

    QString tmpSName = "";

    try {
        tmpSName = createSystemName(curAddress, prefix);
    } catch (JmriException ex) {
#if 1 // TODO:
        ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                showInfoMessage("Error","Unable to convert " + curAddress + " to a valid Hardware Address",""+ex.getMessage(), "",true, false, Level::_ERROR);
#endif
        return NULL;
    }

    //Check to determine if the systemName is in use, return NULL if it is,
    //otherwise return the next valid address.
    Sensor* s = getBySystemName(tmpSName);
    if(s!=NULL){
        for(int x = 1; x<10; x++){
            iName=iName+1;
            s = getBySystemName(prefix+typeLetter()+iName);
            if(s==NULL){
                return QString("%1").arg(iName);
            }
        }
        return NULL;
    } else {
        return QString("%1").arg(iName);
    }
}

/*public*/ void LnSensorManager::setDefaultSensorState(QString state){
    if (state==(tr("Inactive")))
        defaultSensorState=Sensor::INACTIVE;
    else if (state==(tr("Active")))
        defaultSensorState=Sensor::ACTIVE;
    else
        defaultSensorState = Sensor::UNKNOWN;
}
    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnSensorManager.class.getName());



