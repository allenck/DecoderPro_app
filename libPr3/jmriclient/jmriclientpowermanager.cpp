#include "jmriclientpowermanager.h"
#include "jmriclienttrafficcontroller.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientmessage.h"
#include "jmriclientreply.h"

/**
 * PowerManager implementation for controlling layout power
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008
 * @author Paul Bender Copyright (C) 2010
  */
///*public*/ class JMRIClientPowerManager implements PowerManager, JMRIClientListener {


/*public*/ JMRIClientPowerManager::JMRIClientPowerManager(JMRIClientSystemConnectionMemo* memo, QObject* parent) {
    // connect to the TrafficManager
 // to hear of changes
 pcs = new PropertyChangeSupport(this);

    this->memo = memo;
    tc = this->memo->getJMRIClientTrafficController();
    tc->addJMRIClientListener((JMRIClientListener*)this);

}

//@Override
/*public*/ QString JMRIClientPowerManager::getUserName() {
    return this->memo->getUserName();
}


//@Override
/*public*/ void JMRIClientPowerManager::setPower(int v) throw (JmriException) {
    power = UNKNOWN; // while waiting for reply
    checkTC();
    if (v == ON) {
        // send "Enable main track"
        JMRIClientMessage* l = JMRIClientMessage::getEnableMain();
        tc->sendJMRIClientMessage(l, (JMRIClientListener*)this);
    } else if (v == OFF) {
        // send "Kill main track"
        JMRIClientMessage* l = JMRIClientMessage::getKillMain();
        tc->sendJMRIClientMessage(l, (JMRIClientListener*)this);
    }
    firePropertyChange("Power", QVariant(), QVariant());
}

//@Override
/*public*/ int JMRIClientPowerManager::getPower() {
    return power;
}

// to free resources when no longer used
//@Override
/*public*/ void JMRIClientPowerManager::dispose() throw (JmriException) {
    tc->removeJMRIClientListener((JMRIClientListener*)this);
    tc = nullptr;
}

/*private*/ void JMRIClientPowerManager::checkTC() throw (JmriException) {
    if (tc == nullptr) {
        throw JmriException("attempt to use JMRIClientPowerManager after dispose");
    }
}


//@Override
/*public*/  void JMRIClientPowerManager::addPropertyChangeListener(PropertyChangeListener* l) {
    pcs->PropertyChangeSupport::addPropertyChangeListener(l);
}

/*protected*/ void JMRIClientPowerManager::firePropertyChange(QString p, QVariant old, QVariant n) {
    pcs->firePropertyChange(p, old, n);
}

//@Override
/*public*/ /*synchronized*/ void JMRIClientPowerManager::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}


// to listen for status changes from JMRIClient system
//@Override
/*public*/ void JMRIClientPowerManager::reply(JMRIClientReply* m) {
    if (m->toString().contains("ON")) {
        power = PowerManager::ON;
    } else {
        power = PowerManager::OFF;
    }
    firePropertyChange("Power", QVariant(), QVariant());
}

//@Override
/*public*/ void JMRIClientPowerManager::message(JMRIClientMessage* m) {
}
