#include "lncvdevicesmanager.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"
#include "lncvdevices.h"
#include "lncvmessagecontents.h"
#include "roster.h"
#include "joptionpane.h"
#include "lncvdevicesmanager.h"
#include "lncvprogpane.h"
#include "programmer.h"
#include "lnprogrammermanager.h"

/**
 * LocoNet LNCV Devices Manager
 *
 * A centralized resource to help identify LocoNet "LNCV Format"
 * devices and "manage" them.
 *
 * Supports the following features:
 *  - LNCV "discovery" process ? not supported
 *  - LNCV Device "destination address" change ? not supported
 *  - LNCV Device "reconfigure/reset" ? not supported
 *  - identification of devices with conflicting "destination address"es
 *  - identification of a matching JMRI "decoder definition" for each discovered
 *    device, if an appropriate definition exists
 *  - identification of matching JMRI "roster entry" which matches each
 *    discovered device, if an appropriate roster entry exists
 *  - ability to open a symbolic programmer for a given discovered device, if
 *    an appropriate roster entry exists
 *
 * @author B. Milhaupt Copyright (c) 2020
 */

// /*public*/ class LncvDevicesManager extends PropertyChangeSupport
//        implements LocoNetListener {
///*private*/ List<Integer> readLncvAddressList;
///*private*/ java.util.TimerTask delayTask = null;
///*private*/ volatile boolean waitingForDiscoveryReplies;

/*public*/ LncvDevicesManager::LncvDevicesManager(LocoNetSystemConnectionMemo* memo, QObject *parent) : PropertyChangeSupport(memo,parent) {
    this->memo = memo;
    if (memo->getLnTrafficController() != nullptr) {
        memo->getLnTrafficController()->addLocoNetListener(~0, (LocoNetListener*)this);
    } else {
        log->error("No LocoNet connection available, this tool cannot function"); // NOI18N
    }
    lncvDevices = new LncvDevices();
    //readLncvAddressList = new ArrayList<>();
    //waitingForDiscoveryReplies = false;
}

/*public*/ LncvDevices* LncvDevicesManager::getDeviceList() {
    return lncvDevices;
}

/*public*/ int LncvDevicesManager::getDeviceCount() {
    return lncvDevices->size();
}

/*public*/ void LncvDevicesManager::clearDevicesList() {
    lncvDevices->removeAllDevices();

    //jmri.util.ThreadingUtil.runOnLayoutEventually( ()-> firePropertyChange("DeviceListChanged", true, false));
    firePropertyChange("DeviceListChanged", true, false);
}

/*public*/ void LncvDevicesManager::sendLncvDiscoveryRequest() {
    memo->getLnTrafficController()->sendLocoNetMessage(
            LncvMessageContents::createAllProgStartRequest(0));
}

/*public*/ void LncvDevicesManager::message(LocoNetMessage* m) {
    if (LncvMessageContents::isSupportedLncvMessage(m)) {
        if (LncvMessageContents::extractMessageType(m)->getCmd() == LncvCommand(LncvCommand::LNCV_READ_REPLY).cmd) {
            // it's an LNCV ReadReply message, decode contents:
            LncvMessageContents* contents = new LncvMessageContents(m);
            int art = contents->getLncvArticleNum();
            int addr = -1;
            int cv = contents->getCvNum();
            int val = contents->getCvValue();
            log->debug(tr("LNCV read reply: art:%1, address:%2 cv:%3 val:%4").arg(art).arg(addr).arg(cv).arg(val));
            if (cv == 0) { // trust last used address
                addr = val; // if cvNum = 0, this is the LNCV module address
                log->debug(tr("LNCV read reply: device address %1 of LNCV returns %2").arg(addr).arg(val));

                lncvDevices->addDevice(new LncvDevice(art, addr, cv, val, "", "", -1));
                log->debug("new LncvDevice added to table");
                //firePropertyChange("DeviceListChanged", true, false);
//                    waitingForDiscoveryReplies = true;
//                    if (delayTask == null) {
//                        delayTask = new java.util.TimerTask() {
//                            @Override
//                            /*public*/ void run() {
//                                if (!waitingForDiscoveryReplies) {
//                                    if (readLncvAddressList.size() > 0) {
//                                        queryLncvValues();
//                                    }
//                                } else {
//                                    waitingForDiscoveryReplies = false;
//                                }
//                            }};
//                        jmri.util.TimerUtil.scheduleAtFixedRateOnLayoutThread(delayTask, 500, 500);
//                    }
//                    if (addr > 0) {
//                        readLncvAddressList.add(addr); // TODO check for identical addresses? see SV2
//                    }

                // Annotate the discovered device LNCV data based on address
                int count = lncvDevices->size();
                for (int i = 0; i < count; ++ i) {
                    LncvDevice* dev = lncvDevices->getDevice(i);
                    if ((dev->getProductID() == art) && (dev->getDestAddr() == addr)) {
                        // need to find a corresponding roster entry?
                        if (dev->getRosterName() != nullptr && dev->getRosterName().length() == 0) {
                            // Yes. Try to find a roster entry which matches the device characteristics
                            log->debug(tr("Looking for prodID %1/adr %2 in Roster").arg(dev->getProductID()).arg(dev->getDestAddr()));
                            QList<RosterEntry*> l = Roster::getDefault()->matchingList(
                                    QString::number(dev->getDestAddr()),
                                    QString::number(dev->getProductID()));
                            log->debug(tr("LncvDeviceManager found %1 matches in roster").arg(l.size()));
                            if (l.size() == 0) {
                                log->debug("Did not find a corresponding roster entry");
                            } else if (l.size() == 1) {
                                log->debug("Found a matching roster entry.");
                                dev->setRosterEntry(l.at(0)); // link this device to the entry
                            } else {
                                JOptionPane::showMessageDialog(nullptr, // TODO I18N
                                        "The Roster contains multiple LNCV art. " + QString::number(addr)
                                        + " modules with address " + QString::number(l.size()) + ".\nMake sure each module"
                                        + "has a unique address.\n(disconnect all but 1 of these modules,"
                                        + "open new Module Programming Session and write new address to CV0)",
                                        "Open Roster Entry", JOptionPane::WARNING_MESSAGE);
                                log->info(QString("Found multiple matching roster entries. ")
                                        + "Cannot associate any one to this device.");
                            }
                        }
                        // notify listeners of pertinent change to device
                        firePropertyChange("DeviceListChanged", true, false);
                    }
                }
            } else {
                log->debug("LNCV device check skipped as value not CV0/module address");
            }
        }
    }
}

/*public*/ LncvDevice* LncvDevicesManager::getDevice(int art, int addr) {
    int count = lncvDevices->size();
    for (int i = 0; i < count; ++ i) {
        LncvDevice* dev = lncvDevices->getDevice(i);
        if ((dev->getProductID() == art) && (dev->getDestAddr() == addr)) {
            return dev;
        }
    }
    return nullptr;
}

/*public*/ LncvDevicesManager::ProgrammingResult LncvDevicesManager::prepareForSymbolicProgrammer(LncvDevice* dev, ProgrammingTool* t) {

    if (lncvDevices->isDeviceExistant(dev) < 0) {
        return ProgrammingResult::FAIL_NO_SUCH_DEVICE;
    }
    int destAddr = dev->getDestAddr();
    if (destAddr == 0) {
        return ProgrammingResult::FAIL_DESTINATION_ADDRESS_IS_ZERO;
    }
    int deviceCount = 0;
    for (LncvDevice* d: lncvDevices->getDevices()) {
        if (destAddr == d->getDestAddr()) {
            deviceCount++;
        }
    }
    log->debug(tr("prepareForSymbolicProgrammer found %1 matches").arg(deviceCount));
    if (deviceCount > 1) {
        return ProgrammingResult::FAIL_MULTIPLE_DEVICES_SAME_DESTINATION_ADDRESS;
    }

    if ((dev->getRosterName() == "") || (dev->getRosterName().length() == 0)) {
        return ProgrammingResult::FAIL_NO_MATCHING_ROSTER_ENTRY;
    }

    DefaultProgrammerManager* pm = memo->getProgrammerManager();
    if (pm == nullptr) {
        return ProgrammingResult::FAIL_NO_APPROPRIATE_PROGRAMMER;
    }
    Programmer* p = (Programmer* )pm->getAddressedProgrammer(false, dev->getDestAddr());
    if (p == nullptr) {
        return ProgrammingResult::FAIL_NO_ADDRESSED_PROGRAMMER;
    }

    if (p->self()->/*getClass()*/metaObject()->className() != "ProgDebugger") {
        // ProgDebugger used for LocoNet HexFile Sim, setting progMode not required so skip allows testing of LNCV Tool
        if (!p->getSupportedModes().contains("LOCONETLNCVMODE")) {
            return ProgrammingResult::FAIL_NO_LNCV_PROGRAMMER;
        }
        p->setMode(LnProgrammerManager::LOCONETLNCVMODE);
        ProgrammingMode* prgMode = p->getMode();
        if (!prgMode->equals(LnProgrammerManager::LOCONETLNCVMODE)) {
            return ProgrammingResult::FAIL_NO_LNCV_PROGRAMMER;
        }
    }
    RosterEntry* re = Roster::getDefault()->entryFromTitle(dev->getRosterName());
    QString name = re->getId();

    t->openPaneOpsProgFrame(re, name, "programmers/Comprehensive.xml", p); // NOI18N
    return ProgrammingResult::SUCCESS_PROGRAMMER_OPENED;
}

///*public*/ void LncvDevicesManager::addPropertyChangeListener(PropertyChangeListener* l)
//{
// pcs->addPropertyChangeListener(l);
//}

///*public*/ void LncvDevicesManager::removePropertyChangeListener(PropertyChangeListener* l){
// pcs->removePropertyChangeListener(l);
//}

/*private*/ /*final*/ /*static*/ Logger* LncvDevicesManager::log = LoggerFactory::getLogger("LncvDevicesManager");
