#include "lnpr2powermanager.h"
#include "instancemanager.h"
#include "lnpr2throttlemanager.h"
#include "lnopsmodeprogrammer.h"

/**
 * PowerManager implementation for controlling layout power via PR2.
 * <p>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 */
// /*public*/ class LnPr2PowerManager extends LnPowerManager {

/*public*/ LnPr2PowerManager::LnPr2PowerManager(LocoNetSystemConnectionMemo* memo, QObject* parent) :LnPowerManager(memo, parent){
    //super(memo);
    this->sm = memo->getSlotManager();
    this->tc = memo->getLnTrafficController();
    this->memo = memo;
}


//@Override
/*public*/ void LnPr2PowerManager::setPower(int v) /*throw (JmriException)*/ {
    power = UNKNOWN;

    // Instead of GPON/GPOFF, PR2 uses ops-mode writes to CV 128 for control
    if (v == ON) {
        // get current active address
        DccLocoAddress* activeAddress = ((LnPr2ThrottleManager*) InstanceManager::throttleManagerInstance())->getActiveAddress();
        if (activeAddress != nullptr) {
            pm = new LnOpsModeProgrammer(memo, activeAddress->getNumber(), activeAddress->isLongAddress());
            checkOpsProg();

            // set bit 1 in CV 128
            pm->writeCV("128", 1, nullptr);
            power = ON;
            firePropertyChange("Power", 0, 0); // NOI18N
            // start making sure that the power is refreshed
            if (timer == nullptr) {
                timer = new QTimer(); //2 * 1000, new java.awt.event.ActionListener() {
//                    @Override
//                    /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                        refresh();
//                    }
//                });
                connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
                //timer.setInitialDelay(2 * 1000);
                timer->setInterval(2 * 1000);
                //timer.setRepeats(true);     // in case we run by
                timer->setSingleShot(false);
            }
            timer->start();
        }
    } else if (v == OFF) {
        if (timer != nullptr) {
            timer->stop();
        }

        // get current active address
        DccLocoAddress* activeAddress = ((LnPr2ThrottleManager*) InstanceManager::throttleManagerInstance())->getActiveAddress();
        if (activeAddress != nullptr) {
            pm = new LnOpsModeProgrammer(memo, activeAddress->getNumber(), activeAddress->isLongAddress());
            checkOpsProg();

            // reset bit 1 in CV 128
            pm->writeCV("128", 0, nullptr);
            power = OFF;
        }
    }
    // notify of change
    firePropertyChange("Power", 0, 0); // NOI18N
}

void LnPr2PowerManager::refresh() {
    // send inquiry message to keep power alive
    LocoNetMessage* msg = new LocoNetMessage(2);
    msg->setOpCode(LnConstants::OPC_GPBUSY);
    tc->sendLocoNetMessage(msg);
}


/*private*/ void LnPr2PowerManager::checkOpsProg() /*throw (JmriException)*/ {
    if (pm == nullptr) {
        throw  JmriException("Use PR2 power manager after dispose"); // NOI18N
    }
}

// to listen for status changes from LocoNet
//@Override
/*public*/ void LnPr2PowerManager::message(LocoNetMessage* m) {
    if (m->getOpCode() == LnConstants::OPC_GPON) {
        power = ON;
        firePropertyChange("Power", 0, 0); // NOI18N
    } else if (m->getOpCode() == LnConstants::OPC_GPOFF) {
        power = OFF;
        timer->stop();
        firePropertyChange("Power", 0, 0); // NOI18N
    } else if (m->getOpCode() == 0xEF) {
        // if this is a service mode write, drop out of power on mode
        if ((m->getElement(1) == 0x0E)
                && (m->getElement(2) == 0x7C)
                && ((m->getElement(3) & 0x04) == 0x00)) {
            // go to power off due to service mode op
            if (power == ON) {
                power = OFF;
                timer->stop();
                firePropertyChange("Power", 0, 0); // NOI18N
            }
        }
    } else if ( // check for status showing going off
            (m->getOpCode() == LnConstants::OPC_PEER_XFER)
            && (m->getElement(1) == 0x10)
            && (m->getElement(2) == 0x22)
            && (m->getElement(3) == 0x22)
            && (m->getElement(4) == 0x01)) {  // PR2 form
        QVector<int> data = m->getPeerXfrData();
        if ((data[2] & 0x40) != 0x40) {
            // dropped off
            if (power == ON) {
                power = OFF;
                if (timer != nullptr) {
                    timer->stop();
                }
                firePropertyChange("Power", 0, 0); // NOI18N
            }
        }
    }
}

