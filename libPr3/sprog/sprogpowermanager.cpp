#include "sprogpowermanager.h"

using namespace Sprog;
/**
 * PowerManager implementation for controlling SPROG layout power.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 */
///*public*/ class SprogPowerManager extends jmri.managers.AbstractPowerManager
//        implements PowerManager, SprogListener {


/*public*/ SprogPowerManager::SprogPowerManager(SprogSystemConnectionMemo* memo, QObject* parent) : AbstractPowerManager(memo, parent)
{
    //super(memo);
    trafficController = NULL;
    power = UNKNOWN;

    waiting = false;
    onReply = UNKNOWN;

    // connect to the TrafficManager
    trafficController = memo->getSprogTrafficController();
    trafficController->addSprogListener((SprogListener*)this);
}


//@Override
/*public*/ void SprogPowerManager::setPower(int v) throw (JmriException)
{
 power = UNKNOWN; // while waiting for reply
 checkTC();
 if (v == ON)
 {
  // configure to wait for reply
  waiting = true;
  onReply = PowerManager::ON;
  // send "Enable main track"
  SprogMessage* l = SprogMessage::getEnableMain();
  trafficController->sendSprogMessage(l, (SprogListener*)this);
 }
 else if (v == OFF)
 {
  // configure to wait for reply
  waiting = true;
  onReply = PowerManager::OFF;
  firePropertyChange("Power", QVariant(), QVariant());
  // send "Kill main track"
  SprogMessage* l = SprogMessage::getKillMain();
  for (int i = 0; i < 3; i++) {
      trafficController->sendSprogMessage(l, (SprogListener*)this);
  }
 }
 firePropertyChange("Power", QVariant(), QVariant());
}

/**
 * Update power state after service mode programming operation
 * without sending a message to the SPROG.
 */
/*public*/ void SprogPowerManager::notePowerState(int v) {
    power = v;
    firePropertyChange("Power", QVariant(), QVariant());
}

//@Override
/*public*/ int SprogPowerManager::getPower() {
    return power;
}

/**
 * Free resources when no longer used.
 */
//@Override
/*public*/ void SprogPowerManager::dispose() throw (JmriException) {
    trafficController->removeSprogListener((SprogListener*)this);
    trafficController = NULL;
}

/*private*/ void SprogPowerManager::checkTC() throw (JmriException) {
    if (trafficController == NULL) {
        throw new JmriException("attempt to use SprogPowerManager after dispose");
    }
}

/**
 * Listen for status changes from Sprog system.
 */
//@Override
/*public*/ void SprogPowerManager::notifyReply(SprogReply* /*m*/) {
    if (waiting) {
        power = onReply;
        firePropertyChange("Power", QVariant(), QVariant());
    }
    waiting = false;
}

//@Override
/*public*/ void SprogPowerManager::notifyMessage(SprogMessage* m) {
    if (m->isKillMain()) {
        // configure to wait for reply
        waiting = true;
        onReply = PowerManager::OFF;
    } else if (m->isEnableMain()) {
        // configure to wait for reply
        waiting = true;
        onReply = PowerManager::ON;
    }
}

/*public*/ void SprogPowerManager::notify(AbstractMessage* m) {
    if (qobject_cast<SprogMessage*>(m)!= NULL) {
        this->notifyMessage((SprogMessage*) m);
    } else {
        this->notifyReply((SprogReply*) m);
    }
}
