#include "lnturnout.h"
#include "turnout.h"
#include "loggerfactory.h"

//LnTurnout::LnTurnout(QObject *parent) :
//    AbstractTurnout(parent)
//{
//}
QTimer* LnTurnout::meterTimer =/* new QTimer()*/NULL;
QVector<QString> LnTurnout::modeNames;
QVector<int> LnTurnout::modeValues;
/**
 * Extend jmri.AbstractTurnout for LocoNet layouts
 * <P>
 * This implementation implements the "SENT" feedback,
 * where LocoNet messages originating on the layout can change both KnownState
 * and CommandedState.  We change both because we consider a LocoNet message to
 * reflect how the turnout should be, even if its a readback status message.
 * E.g. if you use a DS54 local input to change the state, resulting in a
 * status message, we still consider that to be a commanded state change.
 * <P>
 * Adds several additional feedback modes:
 *<UL>
 *<LI>MONITORING - listen to the LocoNet, so that commands
 * from other LocoNet sources (e.g. throttles) are properly reflected
 * in the turnout state.  This is the default for LnTurnout objects
 * as created.
 *<LI>INDIRECT - listen to the LocoNet for messages back from a
 *DS54 that has a microswitch attached to its Switch input.
 *<LI>EXACT - listen to the LocoNet for messages back from a
 * DS54 that has two microswitches, one connected to the Switch input
 * and one to the Aux input.  Note that this implementation does not
 * pass through the "UNKNOWN" or "INCONSISTENT" states while moving from
 * "THROWN" to "CLOSED" or vice versa. To do that, one would have to
 * add input state tracking information.
 *</UL>
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version			$Revision: 17977 $
 */

// public class LnTurnout extends AbstractTurnout implements LocoNetListener {

LnTurnout::LnTurnout(QString prefix, int number, LocoNetInterface* controller, QObject *parent) :
    AbstractTurnout(prefix+"T"+QString("%1").arg(number),parent)
{
 // a human-readable turnout number must be specified!
 //super(prefix+"T"+number);  // can't use prefix here, as still in construction
 log->debug(QString("new turnout %1").arg(number));
 modeNames.clear();
 modeValues.clear();
 pending = false;
 meterTimer = new QTimer();
 this->controller = controller;

 _number = number;
 // At construction, register for messages
 if (this->controller!=NULL)
 {
  this->controller->addLocoNetListener(~0, (LocoNetListener*)this);
  connect(this->controller, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 else
  log->warn("No LocoNet connection, turnout won't update");
 // update feedback modes
 _validFeedbackTypes |= Turnout::MONITORING|Turnout::EXACT|Turnout::INDIRECT;
 _activeFeedbackType = Turnout::MONITORING;

 // if needed, create the list of feedback mode
 // names with additional LocoNet-specific modes
 if (modeNames.isEmpty())
 {
    initFeedbackModes();
 }
 _validFeedbackNames = modeNames;
 _validFeedbackModes = modeValues;
}


//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//                    justification="Only used during creation of 1st turnout")
 /*private*/ void LnTurnout::initFeedbackModes() {
    if (_validFeedbackNames.length() != _validFeedbackModes.length())
        log->error("int and string feedback arrays different length");
    QVector<QString> tempModeNames; // = new String[_validFeedbackNames.length+3];
    QVector<int> tempModeValues;// = new int[_validFeedbackNames.length+3];
    for (int i = 0; i<_validFeedbackNames.length(); i++)
    {
     tempModeNames << _validFeedbackNames[i];
     tempModeValues << _validFeedbackModes[i];
    }
    tempModeNames<< "MONITORING";
    tempModeValues<<Turnout::MONITORING;
    tempModeNames<< "INDIRECT";
    tempModeValues<<Turnout::INDIRECT;
    tempModeNames<<"EXACT";
    tempModeValues<<Turnout::EXACT;

    modeNames = tempModeNames;
    modeValues = tempModeValues;
 }


 /*public*/ int LnTurnout::getNumber() { return _number; }

/*public*/ void LnTurnout::setUseOffSwReqAsConfirmation(bool state) {
    _useOffSwReqAsConfirmation = state;
}

 // Handle a request to change state by sending a LocoNet command
 /*protected*/ void LnTurnout::forwardCommandChangeToLayout(/*final*/ int newstate) {

     // send SWREQ for close/thrown ON
     sendOpcSwReqMessage(adjustStateForInversion(newstate), true);
     // schedule SWREQ for closed/thrown off, unless in basic mode
     if (!binaryOutput) {
#if 0 // Done:
         meterTimer->schedule(new java.util.TimerTask(){
            int state = newstate;
            public void run() {
                try {
                    sendSetOffMessage(state);
                } catch (Exception* e) {
                    log->error("Exception occured while sending delayed off to turnout: "+e);
                }
            }
         }, METERINTERVAL);
#endif
         meterTimer = new QTimer();
         meterTimer->isSingleShot();
         meterTimer->setInterval(METERINTERVAL);
         timerTask = new LnTurnoutTimerTask(newstate, this);
         connect(meterTimer, SIGNAL(timeout()), this, SLOT(meterTimerTimeout()));
    }
}
/*static*/ const int LnTurnout::METERINTERVAL = 100;  // msec wait before closed


LnTurnoutTimerTask::LnTurnoutTimerTask(int state, LnTurnout* turnout)
{
 this->turnout = turnout;
 this-> state = state;
}
/*public*/ void LnTurnoutTimerTask::run()
{
    try {
        turnout->sendSetOffMessage(state);
    } catch (Exception* e) {
        turnout->log->error("Exception occured while sending delayed off to turnout: "+e->getMessage());
    }
}
void LnTurnout::meterTimerTimeout()
{
 timerTask->start();
}

/**
 * Send a single OPC_SW_REQ message
 * for this turnout, with the CLOSED/THROWN
 * ON/OFF state.
 *<p>
 * Inversion is to already have been handled.
 */
void LnTurnout::sendOpcSwReqMessage(int state, bool on)
{
 LocoNetMessage* l = new LocoNetMessage(4);
 l->setOpCode(LnConstants::OPC_SW_REQ);

 // compute address fields
 int hiadr = (_number-1)/128;
 int loadr = (_number-1)-hiadr*128;

 // set closed (note that this can't handle both!  Not sure how to
 // say that in LocoNet.
 if ((state & Turnout::CLOSED) != 0)
 {
  hiadr |= 0x20;
  // thrown exception if also THROWN
  if ((state & Turnout::THROWN) != 0)
      log->error("LocoNet turnout logic can't handle both THROWN and CLOSED yet");
 }

 // load On/Off
if (on)
    hiadr |= 0x10;
else
    hiadr &= 0xEF;

 // store and send
 l->setElement(1,loadr);
 l->setElement(2,hiadr);

 this->controller->sendLocoNetMessage(l);
}


/**
 * Set the turnout OFF, e.g. after a timeout
 */
void LnTurnout::sendSetOffMessage(int state) {
    sendOpcSwReqMessage(adjustStateForInversion(state), false);
}

/*private*/ void LnTurnout::computeKnownStateOpSwAckReq(int sw2, int state) {
    bool on = ((sw2 & LnConstants::OPC_SW_REQ_OUT) != 0);
    switch (getFeedbackMode()) {
        case MONITORING:
            if ((!on) || (!_useOffSwReqAsConfirmation)) {
                newKnownState(state);
            }
            break;
        case DIRECT:
            newKnownState(state);
            break;
        default:
            break;
    }

}
/*private*/ void LnTurnout::setKnownStateFromOutputStateClosedReport() {
    newCommandedState(CLOSED);
    if (getFeedbackMode() == MONITORING || getFeedbackMode() == DIRECT) {
        newKnownState(CLOSED);
    }
}

/*private*/ void LnTurnout::setKnownStateFromOutputStateThrownReport() {
    newCommandedState(THROWN);
    if (getFeedbackMode() == MONITORING || getFeedbackMode() == DIRECT) {
        newKnownState(THROWN);
    }
}

/*private*/ void LnTurnout::setKnownStateFromOutputStateOddReport() {
    newCommandedState(CLOSED + THROWN);
    if (getFeedbackMode() == MONITORING || getFeedbackMode() == DIRECT) {
        newKnownState(CLOSED + THROWN);
    }
}

/*private*/ void LnTurnout::setKnownStateFromOutputStateReallyOddReport() {
    newCommandedState(0);
    if (getFeedbackMode() == MONITORING || getFeedbackMode() == DIRECT) {
        newKnownState(0);
    }
}

/*private*/ void LnTurnout::computeFromOutputStateReport(int sw2) {
    // LnConstants::OPC_SW_REP_INPUTS not set, these report outputs
    // sort out states
    int state;
    state = sw2
            & (LnConstants::OPC_SW_REP_CLOSED | LnConstants::OPC_SW_REP_THROWN);
    state = adjustStateForInversion(state);

    switch (state) {
        case LnConstants::OPC_SW_REP_CLOSED:
            setKnownStateFromOutputStateClosedReport();
            break;
        case LnConstants::OPC_SW_REP_THROWN:
            setKnownStateFromOutputStateThrownReport();
            break;
        case LnConstants::OPC_SW_REP_CLOSED | LnConstants::OPC_SW_REP_THROWN:
            setKnownStateFromOutputStateOddReport();
            break;
        default:
            setKnownStateFromOutputStateReallyOddReport();
            break;
    }
}

/*private*/ void LnTurnout::computeFeedbackFromSwitchReport(int sw2) {
    // Switch input report
    if ((sw2 & LnConstants::OPC_SW_REP_HI) != 0) {
        computeFeedbackFromSwitchOffReport();
    } else {
        computeFeedbackFromSwitchOnReport();
    }
}

/*private*/ void LnTurnout::computeFeedbackFromSwitchOffReport() {
    // switch input closed (off)
    if (getFeedbackMode() == EXACT) {
        // reached closed state
        newKnownState(adjustStateForInversion(CLOSED));
    } else if (getFeedbackMode() == INDIRECT) {
        // reached closed state
        newKnownState(adjustStateForInversion(CLOSED));
    } else if (!feedbackDeliberatelySet) {
        // don't have a defined feedback mode, but know we've reached closed state
        log->debug("setting CLOSED with !feedbackDeliberatelySet");
        newKnownState(adjustStateForInversion(CLOSED));
    }
}

/*private*/ void LnTurnout::computeFeedbackFromSwitchOnReport() {
    // switch input thrown (input on)
    if (getFeedbackMode() == EXACT) {
        // leaving CLOSED on way to THROWN, go INCONSISTENT if not already THROWN
        if (getKnownState() != THROWN) {
            newKnownState(INCONSISTENT);
        }
    } else if (getFeedbackMode() == INDIRECT) {
        // reached thrown state
        newKnownState(adjustStateForInversion(THROWN));
    } else if (!feedbackDeliberatelySet) {
        // don't have a defined feedback mode, but know we're not in closed state, most likely is actually thrown
        log->debug("setting THROWN with !feedbackDeliberatelySet");
        newKnownState(adjustStateForInversion(THROWN));
    }
}

/*private*/ void LnTurnout::computeFromSwFeedbackState(int sw2) {
    // LnConstants::OPC_SW_REP_INPUTS set, these are feedback messages from inputs
    // sort out states
    if ((sw2 & LnConstants::OPC_SW_REP_SW) != 0) {
        computeFeedbackFromSwitchReport(sw2);

    } else {
        computeFeedbackFromAuxInputReport(sw2);
    }
}

/*private*/ void LnTurnout::computeFeedbackFromAuxInputReport(int sw2) {
    // This is only valid in EXACT mode, so if we encounter it
    //  without a feedback mode set, we switch to EXACT
    if (!feedbackDeliberatelySet) {
        setFeedbackMode(EXACT);
        feedbackDeliberatelySet = false; // was set when setting feedback
    }

    if ((sw2 & LnConstants::OPC_SW_REP_HI) != 0) {
        // aux input closed (off)
        if (getFeedbackMode() == EXACT) {
            // reached thrown state
            newKnownState(adjustStateForInversion(THROWN));
        }
    } else {
        // aux input thrown (input on)
        if (getFeedbackMode() == EXACT) {
            // leaving THROWN on the way to CLOSED, go INCONSISTENT if not already CLOSED
            if (getKnownState() != CLOSED) {
                newKnownState(INCONSISTENT);
            }
        }
    }
}
/*private*/ void LnTurnout::handleReceivedOpSwRep(LocoNetMessage* l) {
    int sw1 = l->getElement(1);
    int sw2 = l->getElement(2);
    if (myAddress(sw1, sw2)) {

        log->debug("SW_REP received with valid address");
        // see if its a turnout state report
        if ((sw2 & LnConstants::OPC_SW_REP_INPUTS) == 0) {
            computeFromOutputStateReport(sw2);
        } else {
            computeFromSwFeedbackState(sw2);
        }
    }
}

/*private*/ void LnTurnout::handleReceivedOpSwAckReq(LocoNetMessage* l) {
        int sw2 = l->getElement(2);
        if (myAddress(l->getElement(1), sw2)) {

            log->debug("SW_REQ received with valid address");
            //sort out states
            int state;
            state = ((sw2 & LnConstants::OPC_SW_REQ_DIR) != 0) ? CLOSED : THROWN;
            state = adjustStateForInversion(state);

            newCommandedState(state);
            computeKnownStateOpSwAckReq(sw2, state);
        }
    }

 // implementing classes will typically have a function/listener to get
 // updates from the layout, which will then call
 //		public void firePropertyChange(String propertyName,
 //					      	Object oldValue,
 //						Object newValue)
 // _once_ if anything has changed state (or set the commanded state directly)
 /*public*/ void LnTurnout::message(LocoNetMessage* l) {
     // parse message type
     switch (l->getOpCode()) {
     case LnConstants::OPC_SW_REQ: {               /* page 9 of Loconet PE */
         int sw1 = l->getElement(1);
         int sw2 = l->getElement(2);
         if (myAddress(sw1, sw2)) {
             if (log->isDebugEnabled()) log->debug("SW_REQ received with valid address");
                 //sort out states
                 int state;
                 if ((sw2 & LnConstants::OPC_SW_REQ_DIR) != 0){
                     state = Turnout::CLOSED;
                 }else{
                     state = Turnout::THROWN;
             }
                 state = adjustStateForInversion(state);

                 newCommandedState(state);
                 if (getFeedbackMode()==Turnout::MONITORING || getFeedbackMode()==Turnout::DIRECT) newKnownState(state);
         }
         break;
     }
     case LnConstants::OPC_SW_REP: {               /* page 9 of Loconet PE */
         int sw1 = l->getElement(1);
         int sw2 = l->getElement(2);
         if (myAddress(sw1, sw2)) {
             if (log->isDebugEnabled()) log->debug("SW_REP received with valid address");
             // see if its a turnout state report
             if ((sw2 & LnConstants::OPC_SW_REP_INPUTS)==0) {
                 // LnConstants::OPC_SW_REP_INPUTS not set, these report outputs
                    // sort out states
                     int state;
                     state = sw2 &
                             (LnConstants::OPC_SW_REP_CLOSED|LnConstants::OPC_SW_REP_THROWN);
                     state = adjustStateForInversion(state);

                     switch (state) {
                 case 0x20: //LnConstants::OPC_SW_REP_CLOSED:
                     newCommandedState(Turnout::CLOSED);
                     if (getFeedbackMode()==Turnout::MONITORING || getFeedbackMode()==Turnout::DIRECT) newKnownState(Turnout::CLOSED);
                     break;
                 case 0x10: //LnConstants::OPC_SW_REP_THROWN:
                     newCommandedState(Turnout::THROWN);
                     if (getFeedbackMode()==Turnout::MONITORING || getFeedbackMode()==Turnout::DIRECT) newKnownState(Turnout::THROWN);
                     break;
                 case 0x30: //LnConstants::OPC_SW_REP_CLOSED|LnConstants::OPC_SW_REP_THROWN:
                     newCommandedState(Turnout::CLOSED+Turnout::THROWN);
                     if (getFeedbackMode()==Turnout::MONITORING || getFeedbackMode()==Turnout::DIRECT) newKnownState(Turnout::CLOSED+Turnout::THROWN);
                     break;
                 default:
                     newCommandedState(0);
                     if (getFeedbackMode()==Turnout::MONITORING || getFeedbackMode()==Turnout::DIRECT) newKnownState(0);
                     break;
                 }
             } else {
                // LnConstants::OPC_SW_REP_INPUTS set, these are feedback messages from inputs
                    // sort out states
                    // see EXACT feedback note at top
                if ((sw2 & LnConstants::OPC_SW_REP_SW) !=0) {
                    // Switch input report
                    if ((sw2 & LnConstants::OPC_SW_REP_HI)!=0) {
                        // switch input closed (off)
                        if (getFeedbackMode()==Turnout::EXACT) {
                            // reached closed state
                                 newKnownState(adjustStateForInversion(Turnout::CLOSED));
                        } else if (getFeedbackMode()==Turnout::INDIRECT) {
                            // reached closed state
                                 newKnownState(adjustStateForInversion(Turnout::CLOSED));
                        }
                    } else {
                        // switch input thrown (input on)
                        if (getFeedbackMode()==Turnout::EXACT) {
                            // leaving CLOSED on way to THROWN, but ignoring that for now
                        } else if (getFeedbackMode()==Turnout::INDIRECT) {
                            // reached thrown state
                                 newKnownState(adjustStateForInversion(Turnout::THROWN));
                        }
                    }
                } else {
                    // Aux input report
                    if ((sw2 & LnConstants::OPC_SW_REP_HI)!=0) {
                        // aux input closed (off)
                        if (getFeedbackMode()==Turnout::EXACT) {
                            // reached thrown state
                                 newKnownState(adjustStateForInversion(Turnout::THROWN));
                        }
                    } else {
                        // aux input thrown (input on)
                        if (getFeedbackMode()==Turnout::EXACT) {
                            // leaving THROWN on the way to CLOSED, but ignoring that for now
                        }
                    }
                }

             }
         }
         return;
     }
     default:
         return;
     }
     // reach here only in error
 }

// implementing classes will typically have a function/listener to get
// updates from the layout, which will then call
//        public void firePropertyChange(String propertyName,
//                              Object oldValue,
//                        Object newValue)
// _once_ if anything has changed state (or set the commanded state directly)
/*public*/ void LnTurnout::messageFromManager(LocoNetMessage* l) {
    // parse message type
    switch (l->getOpCode()) {
        case LnConstants::OPC_SW_ACK:
        case LnConstants::OPC_SW_REQ: {
            handleReceivedOpSwAckReq(l);
            return;
            }
        case LnConstants::OPC_SW_REP: {
            handleReceivedOpSwRep(l);
            return;
        }
        default:
            return;
    }
}

 /*protected*/ void LnTurnout::turnoutPushbuttonLockout(bool _pushButtonLockout){
    if (log->isDebugEnabled())
        log->debug(QString("Send command to %1 Pushbutton LT%2").arg(_pushButtonLockout ? "Lock" : "Unlock").arg(_number));
 }

 /*public*/ void LnTurnout::dispose() {
//     this->controller->removeLocoNetListener(~0, (LocoNetListener*)this);
     //super.dispose();
 }


 /*private*/ bool LnTurnout::myAddress(int a1, int a2) {
     // the "+ 1" in the following converts to throttle-visible numbering
     return (((a2 & 0x0f) * 128) + (a1 & 0x7f) + 1) == _number;
 }

 //ln turnouts do support inversion
 /*public*/ bool LnTurnout::canInvert() const{return true;}

 //method which takes a turnout state as a parameter and adjusts it  as necessary
 //to reflect the turnout invert property
 /*private*/ int LnTurnout::adjustStateForInversion(int rawState) {

     if (getInverted() && (rawState == Turnout::CLOSED || rawState == Turnout::THROWN)){
         if (rawState == Turnout::CLOSED) {
             return Turnout::THROWN;
         }else{
             return Turnout::CLOSED;
         }
     }else{
         return rawState;
     }

 }

/*private*/ /*final*/ /*static*/ Logger* LnTurnout::log = LoggerFactory::getLogger("LnTurnout");
