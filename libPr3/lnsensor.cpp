#include "lnsensor.h"
#include "sensor.h"
#include "loggerfactory.h"
#include "loconetmessageinterpret.h"

//LnSensor::LnSensor(QObject *parent) :
//    AbstractSensor(parent)
//{

//}
/**
 * Extend jmri.AbstractSensor for LocoNet layouts.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version         $Revision: 17977 $
 */
//public class LnSensor extends AbstractSensor implements LocoNetListener {


LnSensor::LnSensor(QString systemName, QString userName, LnTrafficController* tc, QString prefix,QObject *parent)
    : AbstractSensor(systemName, userName, parent)
{
 //super(systemName, userName);
 this->tc = tc;
 init(systemName, prefix.mid(0,1));
}

LnSensor::LnSensor(QString systemName, LnTrafficController* tc, QString prefix,QObject *parent)
    : AbstractSensor(systemName, parent)
{
 //super(systemName);
 this->tc = tc;
 init(systemName, prefix.mid(0,1));
}


/**
 * Common initialization for both constructors
 */
void LnSensor::init(QString systemName, QString prefix)
{
 // store address forms
 a = new LnSensorAddress(systemName, prefix);
 log->setDebugEnabled(true);
 if (log->isDebugEnabled()) log->debug("create address "+a->toString());

 // At construction, register for messages
 if(tc != NULL)
 {
  tc->addLocoNetListener(~0, (LocoNetListener*)this);
  connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 sensorDebounceGoingActive = 0L;
 sensorDebounceGoingInActive = 0L;
 _useDefaultTimerSettings = false;
 restartcount = 0;
 _inverted = false;
 // internal data members
 _knownState     = UNKNOWN;
 _rawState       = UNKNOWN;
 reporter = NULL;
 lastKnownState = _knownState;
 setObjectName("LnSensor");
}

/**
 * request an update on status by sending a loconet message
 */
void LnSensor::requestUpdateFromLayout() const {
    // the only known way to do this from LocoNet is to request the
    // status of _all_ devices, which is here considered too
    // heavyweight.  Perhaps this is telling us we need
    // a "update all" in the SensorManager (and/or TurnoutManager)
    // interface?
}

/**
 * User request to set the state, which means that we broadcast that to
 * all listeners by putting it out on LocoNet.
 * In turn, the code in this class should use setOwnState to handle
 * internal sets and bean notifies.
 * @param s
 * @throws JmriException
 */
void LnSensor::setKnownState(int s)// throws jmri.JmriException
{
    // send OPC_INPUT_REP with new state to this address
    LocoNetMessage* l = new LocoNetMessage(4);
    l->setOpCode(LnConstants::OPC_INPUT_REP);
    a->insertAddress(l);
    // set state
    if ((s==Sensor::ACTIVE)^ _inverted) {
        l->setElement(2, l->getElement(2)|0x10);
    } // otherwise is already OK
    l->setElement(2, l->getElement(2)|0x40);
    // send
    tc->sendLocoNetMessage(l);
    AbstractSensor::setOwnState(s);
}

/**
 * implementing classes will typically have a function/listener to get
 * updates from the layout, which will then call
 *      public void firePropertyChange(QString propertyName,
 *      					Object oldValue,
 *                                          Object newValue)
 * _once_ if anything has changed state (or set the commanded state directly)
 * @param l
 */
void LnSensor::message(LocoNetMessage* l)
{
 // parse message type
 switch (l->getOpCode())
 {
  case LnConstants::OPC_INPUT_REP: // 0xb2
  {               /* page 9 of Loconet PE */
   int sw1 = l->getElement(1);
   int sw2 = l->getElement(2);
   if (a->matchAddress(sw1, sw2))
   {
    // save the state
    bool state = ((sw2 & 0x10) != 0) ^ _inverted;
    if (log->isDebugEnabled())
        log->debug("INPUT_REP received with valid address, old state "
                    +QString("%1").arg(getRawState())+" new packet "+QString("%1").arg(state));
    if ( state && getRawState() != Sensor::ACTIVE)
    {
        if (log->isDebugEnabled()) log->debug(tr("Set %1 ACTIVE").arg(getSystemName()));
        setOwnState(Sensor::ACTIVE);
    }
    else if ( (!state) && getRawState() != Sensor::INACTIVE)
    {
        if (log->isDebugEnabled()) log->debug(tr("Set %2 INACTIVE").arg(getSystemName()));
        setOwnState(Sensor::INACTIVE);
    }
   }
   return;
  }
  // Added by ACK to set feedback sensors 10/03/2018
  case LnConstants::OPC_SW_REP:
  {
     int sw1 = l->getElement(1);
     int sw2 = l->getElement(2);

   int addr = (((sw2 & 0x0f) * 128) + (sw1 & 0x7f)) + 1;
   if(addr == thisAddr)
   {
   // save the state
   bool state = ((sw2 & 0x10) != 0) ^ _inverted;
   if (log->isDebugEnabled())
   {
     log->debug(tr("OPC_SW_REP received with address %1, old state ").arg(addr)
                   +QString("%1").arg(getRawState())+" new packet "+QString("%1\n").arg(state)+ LocoNetMessageInterpret::interpretOpcSwRep(l, "LS"));
   }
   if ( state && getRawState() != Sensor::ACTIVE)
   {
       if (log->isDebugEnabled()) log->debug(tr("Set %1 ACTIVE").arg(getSystemName()));
       setOwnState(Sensor::ACTIVE);
   }
   else if ( (!state) && getRawState() != Sensor::INACTIVE)
   {
       if (log->isDebugEnabled()) log->debug(tr("Set %2 INACTIVE").arg(getSystemName()));
       setOwnState(Sensor::INACTIVE);
   }
  }
  return;
 }
  default:
      return;
 }
 // reach here only in error
}

void LnSensor::dispose() {
    tc->removeLocoNetListener(~0, (LocoNetListener*)this);
    AbstractSensor::dispose();
}
/**
 * implementing classes will typically have a function/listener to get
 * updates from the layout, which will then call public void
 * firePropertyChange(String propertyName, Object oldValue, Object newValue)
 * _once_ if anything has changed state (or set the commanded state
 * directly)
 *
 */
/*public*/ void LnSensor::messageFromManager(LocoNetMessage* l) {
    // parse message type
    switch (l->getOpCode()) {
        case LnConstants::OPC_INPUT_REP: {               /* page 9 of LocoNet PE */

            int sw1 = l->getElement(1);
            int sw2 = l->getElement(2);
            if (a->matchAddress(sw1, sw2)) {
                // save the state
                bool state = ((sw2 & 0x10) != 0) ^ _inverted;
                if (log->isDebugEnabled()) {
                    log->debug("INPUT_REP received with valid address, old state "
                            + QString::number(getRawState()) + " new packet " + (state?"true":"false")); // NOI18N
                }
                if (state && getRawState() != Sensor::ACTIVE) {
                    if (log->isDebugEnabled()) {
                        log->debug("Set ACTIVE"); // NOI18N
                    }
                    setOwnState(Sensor::ACTIVE);
                } else if ((!state) && getRawState() != Sensor::INACTIVE) {
                    if (log->isDebugEnabled()) {
                        log->debug("Set INACTIVE"); // NOI18N
                    }
                    setOwnState(Sensor::INACTIVE);
                }
            }
            return;
        }
        default:
            return;
    }
    // reach here only in error
}

/*private*/ /*final*/ /*static*/ Logger* LnSensor::log = LoggerFactory::getLogger("LnSensor");
