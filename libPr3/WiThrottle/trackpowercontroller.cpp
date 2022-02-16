#include "trackpowercontroller.h"
#include "powermanager.h"
#include "instancemanager.h"
#include "logger.h"
#include "loggerfactory.h"
#include "controllerinterface.h"
#include "jmriexception.h"

/**
 * Handle two-way communications regarding track power.
 *
 * @author Brett Hoffman Copyright (C) 2010
 */
// /*public*/ class TrackPowerController extends AbstractController implements PropertyChangeListener {


/*public*/ TrackPowerController::TrackPowerController() : AbstractController()
{
    pwrMgr = (PowerManager*)InstanceManager::getNullableDefault("PowerManager");
    if (pwrMgr == NULL) {
        log->info("No power manager instance.");
        isValid = false;
    } else {
        _register();
        isValid = true;
    }
}

//@Override
/*public*/ bool TrackPowerController::verifyCreation() {
    return isValid;
}

//@Override
/*public*/ void TrackPowerController::handleMessage(QString message) {
    if (message.at(0) == 'A') {
        if (message.at(1) == '1') {
            setTrackPowerOn();
        } else if (message.at(1) == '0') {
            setTrackPowerOff();
        } else {
            log->warn("Unknown Track Power message from wi-fi device");
        }
    }
}

/*private*/ void TrackPowerController::setTrackPowerOn() {
    if (pwrMgr != NULL) {
        try {
            pwrMgr->setPower(PowerManager::ON);
        } catch (JmriException* e) {
            log->error("Cannot turn power on.");
        }
    }
}

/*private*/ void TrackPowerController::setTrackPowerOff() {
    if (pwrMgr != NULL) {
        try {
            pwrMgr->setPower(PowerManager::OFF);
        } catch (JmriException* e) {
            log->error("Cannot turn power off.");
        }
    }
}

/*public*/ void TrackPowerController::sendCurrentState() {
    if (listeners == NULL) {
        return;
    }
    QString message = NULL;
    try {
        if (pwrMgr->getPower() == PowerManager::ON) {
            message = "PPA1";
        } else if (pwrMgr->getPower() == PowerManager::OFF) {
            message = "PPA0";
        } else if (pwrMgr->getPower() == PowerManager::UNKNOWN) {
            message = "PPA2";
        } else {
            log->error("Unexpected state value: +" + pwrMgr->getPower());
        }
    } catch (JmriException* e) {
        log->error("Power Manager exception");
    }

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }

}

//@Override
/*public*/ void TrackPowerController::propertyChange(PropertyChangeEvent* event) {
    sendCurrentState();
}

//@Override
/*public*/ void TrackPowerController::_register() {
    //pwrMgr.addPropertyChangeListener(this);
 connect(pwrMgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

//@Override
/*public*/ void TrackPowerController::deregister() {
    //pwrMgr.removePropertyChangeListener(this);
 disconnect(pwrMgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(propertyChangeEvent*)));
}

/*private*/ /*final*/ /*static*/ Logger* TrackPowerController::log = LoggerFactory::getLogger("TrackPowerController");
