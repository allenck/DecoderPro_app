#include "multithrottle.h"
#include "loggerfactory.h"
#include "throttlecontrollerlistener.h"
#include "controllerinterface.h"
#include "multithrottlecontroller.h"

/**
 * Keeps track of what locos are being controlled by a throttle, and passes the
 * control messages on to them. Creates a new MultiThrottleController for each
 * loco requested on this throttle. Each loco will then be able to be controlled
 * individually. '*' is a wildcard loco key. Forwards to all locos on this
 * MultiThrottle.
 * <p>
 * Sample messages:<ul>
 * <li> {@literal MT+L757<;>L757} On T throttle, add loco L757.
 * <li> {@literal MT+L1234<;>L1234} On T throttle, add loco L1234.
 * <li> {@literal MTAL757<;>R1} On T throttle, loco L757, set direction to
 * forward.
 * <li> {@literal MTAL1234<;>R0} On T throttle, loco L1234, set direction to
 * reverse.
 * <li> {@literal MTAL757<;>V42} On T throttle, loco L757, set speed to 42.
 * <li> {@literal MTAL1234<;>V42} On T throttle, loco L1234, set speed to 42.
 * <li> {@literal MTA*<;>V16} On T throttle, all locos, set speed to 16.
 * <li> {@literal MT-L757<;>L757} On T throttle, remove loco L757. (Still has
 * L1234)
 * </ul>
 *
 * @author Brett Hoffman Copyright (C) 2011
 */
// /*public*/ class MultiThrottle {


/*public*/ MultiThrottle::MultiThrottle(QChar id, ThrottleControllerListener* tcl, ControllerInterface* ci, QObject *parent) : QObject(parent)
{
 parentTCL = NULL;
 parentController = NULL;

    if (log->isDebugEnabled()) {
        log->debug("Creating new MultiThrottle for id: " + QString(id));
    }
 throttles =   new QHash<QString, MultiThrottleController*>(/*1*/);
    whichThrottle = id;
    parentTCL = tcl;
    parentController = ci;
}

/**
 * Handle a message sent from the device. A key is used to send an action to
 * the correct loco. '*' is a wildcard key, sends action to all locos in
 * this MultiThrottle.
 *
 * @param message Consists of a control character, the loco's key, a
 *                separator {@literal "<;>"}, and the action to forward to
 *                the MultiThrottleController.
 */
/*public*/ void MultiThrottle::handleMessage(QString message) {
    log->debug("MT handleMessage: " + message);
    QStringList unit = (message.mid(1).split("<;>"));
    QString key = unit.at(0);
    QString action = unit.at(1);
    if ((key == NULL) || (action == NULL)) {
        return;
    }

   QChar c = message.at(0);
   if(c == 'A')  //  'A'ction
     passActionsToControllers(key, action);
   else if(c == '+') //  add loco
     addThrottleController(key, action);
   else if(c ==  '-') //  remove loco
     removeThrottleController(key, action);
}

/*public*/ bool MultiThrottle::addThrottleController(QString key, QString action) {   //  key is address format L#### or S##
    if (throttles == NULL) {
        throttles = new QHash<QString, MultiThrottleController*>(/*1*/);
    }

    if (throttles->contains(key)) {
        if (log->isDebugEnabled()) {
            log->debug("Throttle: " + key + " already in MultiThrottle consist.");
        }
        return false;
    }
    MultiThrottleController* mtc = new MultiThrottleController(whichThrottle, key, parentTCL, parentController);
    throttles->insert(key, mtc);

    //  This will request the loco as a DccTrottle
    mtc->sort(action);

    if (log->isDebugEnabled()) {
        log->debug("Throttle: " + key + " added to MultiThrottle consist.");
    }
    return true;
}

/*public*/ bool MultiThrottle::removeThrottleController(QString key, QString action) {

    if (throttles == NULL) {
        log->debug("No MultiThrottle to remove " + key + " from.");
        return false;
    }
    if (key == ("*")) {
        //for (Enumeration<String> e = throttles.keys(); e.hasMoreElements();)
        QStringListIterator e(throttles->keys());
        while (e.hasNext())
        {
            removeThrottleController(e.next(), action);
            //  Runs each loco through this method individually
        }
        return true;
    }
    if (!throttles->contains(key)) {
        if (log->isDebugEnabled()) {
            log->debug("Throttle: " + key + " not in MultiThrottle.");
        }
        return false;
    }
    MultiThrottleController* mtc = throttles->value(key);
    mtc->sort(action);
    mtc->shutdownThrottle();
    mtc->removeControllerListener(parentController);
    mtc->removeThrottleControllerListener(parentTCL);
    throttles->remove(key);
    if (log->isDebugEnabled()) {
        log->debug("Throttle: " + key + " removed from MultiThrottle.");
    }
    return true;
}

/*public*/ void MultiThrottle::passActionsToControllers(QString key, QString action) {
    if (throttles == NULL) {
        log->debug("No throttles in MultiThrottle to receive action.");
        return;
    }
    if (log->isDebugEnabled()) {
        log->debug("MultiThrottle key: " + key + ", action: " + action);
    }

    if (key == ("*")) {
        //for (Enumeration<String> e = throttles.keys(); e.hasMoreElements();)
     QStringListIterator e(throttles->keys());
     while (e.hasNext())
     {
            passActionsToControllers(e.next(), action);
            //  Runs each loco through this method individually
        }
        return;
    }
    if (throttles->contains(key)) {
        throttles->value(key)->sort(action);
    }
}

/*public*/ void MultiThrottle::dispose() {
    if (throttles == NULL) {
        return;
    }
    //for (Enumeration<String> e = throttles.keys(); e.hasMoreElements();)
    QStringListIterator e(throttles->keys());
    while (e.hasNext())
    {
        removeThrottleController(e.next(), "r");
    }
}

/*public*/ void MultiThrottle::eStop() {
    if (throttles == NULL) {
        return;
    }
    //for (Enumeration<String> e = throttles.keys(); e.hasMoreElements();)
    QStringListIterator e(throttles->keys());
    while (e.hasNext())
    {
        passActionsToControllers(e.next(), "X");
    }
}

/*private*/ /*final*/ /*static*/ Logger* MultiThrottle::log = LoggerFactory::getLogger("MultiThrottle");
