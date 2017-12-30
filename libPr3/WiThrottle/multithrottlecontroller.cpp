#include "multithrottlecontroller.h"
#include "propertychangeevent.h"
#include "exceptions.h"
#include "controllerinterface.h"
#include "dccthrottle.h"
#include "loggerfactory.h"
#include "rosterentry.h"

/**
 * @author Brett Hoffman Copyright (C) 2011
 */
// /*public*/ class MultiThrottleController extends ThrottleController {


/*public*/ MultiThrottleController::MultiThrottleController(QChar id, QString key, ThrottleControllerListener* tcl, ControllerInterface* ci, QObject* parent) : ThrottleController(id, tcl, ci, parent)
{
    //super(id, tcl, ci);
    log->debug("New MT controller");
    locoKey = key;
}

/**
 * Builds a header to send to the wi-fi device for use in a message.
 * Includes a separator - {@literal <;>}
 *
 * @param chr the character indicating what action is performed
 * @return a pre-assembled header for this DccThrottle
 */
/*public*/ QString MultiThrottleController::buildPacketWithChar(QChar chr) {
    return (QString("M") + whichThrottle + QString(chr) + locoKey + "<;>");
}


/*
 * Send a message to the wi-fi device that a bound property of a DccThrottle
 * has changed.  Currently only handles function state.
 * Current Format:  Header + F(0 or 1) + function number
 *
 * Event may be from regular throttle or consist throttle, but is handled the same.
 *
 * Bound params: SpeedSteps, IsForward, SpeedSetting, F##, F##Momentary
 */
//@Override
/*public*/ void MultiThrottleController::propertyChange(PropertyChangeEvent* event) {
    QString eventName = event->getPropertyName();
    if (log->isDebugEnabled()) {
        log->debug("property change: " + eventName);
    }
    if (eventName.startsWith("F")) {

        if (eventName.contains("Momentary")) {
            return;
        }
        QString message = QString(buildPacketWithChar('A'));

        try {
            if ( event->getNewValue().toBool()) {
                message.append("F1");
            } else {
                message.append("F0");
            }
            message.append(eventName.mid(1));
        }
//        catch (ClassCastException cce)
//        {
//            log->debug("Invalid event value. " + cce);
//        }
        catch (IndexOutOfBoundsException oob) {
            log->debug("Invalid event name. " + oob.getMessage());
        }

        foreach (ControllerInterface* listener, *controllerListeners) {
            listener->sendPacketToDevice(message);
        }
    }
    if (eventName == ("SpeedSteps")) {
        sendSpeedStepMode(throttle);
    }

}

//@Override
/*public*/ void MultiThrottleController::sendFunctionLabels(RosterEntry* re) {

    if (re != NULL) {
        QString functionString = QString(buildPacketWithChar('L'));

        int i;
        for (i = 0; i < 29; i++) {
            functionString.append("]\\[");
            if ((re->getFunctionLabel(i) != NULL)) {
                functionString.append(re->getFunctionLabel(i));
            }
        }
        foreach (ControllerInterface* listener, *controllerListeners) {
            listener->sendPacketToDevice(functionString);
        }
    }

}

/**
 * This replaces the previous method of sending a string of function states,
 * and now sends them individually, the same as a property change would.
 *
 * @param t the throttle to send the staes of
 */
//@Override
/*public*/ void MultiThrottleController::sendAllFunctionStates(DccThrottle* t) {
    log->debug("Sending state of all functions");
#if 0
    try {
        for (int cnt = 0; cnt < 29; cnt++) {
            //Method getF = t.getClass().getMethod("getF" + cnt, (Class[]) NULL);



            QString message = new QString(buildPacketWithChar('A'));
            if ((Boolean) getF.invoke(t, (Object[]) NULL)) {
                message.append("F1");
            } else {
                message.append("F0");
            }
            message.append(cnt);
            foreach (ControllerInterface* listener, *controllerListeners) {
                listener->sendPacketToDevice(message.toString());
            }
        }

    } catch (NoSuchMethodException ea) {
        log->warn(ea.getLocalizedMessage(), ea);
        return;
    } catch (IllegalAccessException eb) {
        log->warn(eb.getLocalizedMessage(), eb);
        return;
    } catch (InvocationTargetException ec) {
        log->warn(ec.getLocalizedMessage(), ec);
        return;
    }
#endif
}

//@Override
/*protected*/ void MultiThrottleController::sendCurrentSpeed(DccThrottle* t) {
    QString message =  QString(buildPacketWithChar('A'));
    message.append("V");
    message.append(qRound(t->getSpeedSetting() / speedMultiplier));
    foreach (ControllerInterface* listener,  *controllerListeners) {
        listener->sendPacketToDevice(message);
    }
}

//@Override
/*protected*/ void MultiThrottleController::sendCurrentDirection(DccThrottle* t) {
    QString message =  QString(buildPacketWithChar('A'));
    message.append("R");
    message.append(t->getIsForward() ? "1" : "0");
    foreach (ControllerInterface* listener, *controllerListeners) {
        listener->sendPacketToDevice(message);
    }
}

//@Override
/*protected*/ void MultiThrottleController::sendSpeedStepMode(DccThrottle* t) {
    QString message =  QString(buildPacketWithChar('A'));
    message.append("s");
    message.append(throttle->getSpeedStepMode());
    foreach (ControllerInterface* listener, *controllerListeners) {
        listener->sendPacketToDevice(message);
    }
}

//@Override
/*protected*/ void MultiThrottleController::sendAllMomentaryStates(DccThrottle* t) {
    log->debug("Sending momentary state of all functions");
#if 0
    try {
        for (int cnt = 0; cnt < 29; cnt++) {
            Method getF = t.getClass().getMethod("getF" + cnt + "Momentary", (Class[]) NULL);

            QString message = new QString(buildPacketWithChar('A'));
            if ((Boolean) getF.invoke(t, (Object[]) NULL)) {
                message.append("m1");
            } else {
                message.append("m0");
            }
            message.append(cnt);
            foreach (ControllerInterface* listener, *controllerListeners) {
                listener->sendPacketToDevice(message.toString());
            }
        }

    } catch (NoSuchMethodException ea) {
        log->warn(ea.getLocalizedMessage(), ea);
        return;
    } catch (IllegalAccessException eb) {
        log->warn(eb.getLocalizedMessage(), eb);
        return;
    } catch (InvocationTargetException ec) {
        log->warn(ec.getLocalizedMessage(), ec);
        return;
    }
#endif
}

/**
 * + indicates the address was acquired, - indicates released
 */
//@Override
/*public*/ void MultiThrottleController::sendAddress() {
    foreach (ControllerInterface* listener, *controllerListeners) {
        if (isAddressSet) {
            listener->sendPacketToDevice(buildPacketWithChar('+'));
        } else {
            listener->sendPacketToDevice(buildPacketWithChar('-'));
        }
    }
}

/*private*/ /*final*/ /*static*/ Logger* MultiThrottleController::log = LoggerFactory::getLogger("MultiThrottleController");
