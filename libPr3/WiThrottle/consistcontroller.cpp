#include "consistcontroller.h"
#include "consistmanager.h"
#include "loggerfactory.h"
#include "withrottlemanager.h"
#include "instancemanager.h"
#include "withrottlepreferences.h"
#include "wificonsistmanager.h"
#include "wificonsistfile.h"
#include "controllerinterface.h"
#include "addressedprogrammer.h"
#include "addressedprogrammermanager.h"

/**
 * @author Brett Hoffman Copyright (C) 2010
 */
// /*public*/ class ConsistController extends AbstractController implements ProgListener {


/*public*/ ConsistController::ConsistController(QObject *parent) : AbstractController(parent) {
    //  writeFile needs to be separate method
    if (WiThrottleManager::withrottlePreferencesInstance()->isUseWiFiConsist()) {
        manager = new WiFiConsistManager();
        InstanceManager::store((QObject*)manager,"ConsistManager");
        log->debug("Using WiFiConsisting");
    } else {
        manager = qobject_cast<AbstractConsistManager*>(InstanceManager::getNullableDefault("ConsistManager"));
        log->debug("Using JMRIConsisting");
    }

    if (manager == NULL) {
        log->info("No consist manager instance.");
        isValid = false;
    } else {
        if (WiThrottleManager::withrottlePreferencesInstance()->isUseWiFiConsist()) {
            file = new WiFiConsistFile(manager);
        } else {
            file = new ConsistFile();
            try {
                file->readFile();
            } catch (Exception e) {
                log->warn("error reading consist file: " + e.getMessage());
            }
        }
        isValid = true;
    }
}

/**
 * Allows device to decide how to handle consisting. Just selection or
 * selection and Make {@literal &} Break. .size() indicates how many
 * consists are being sent so the device can wait before displaying them
 */
/*public*/ void ConsistController::sendConsistListType() {
    if (listeners == NULL) {
        return;
    }
    QString message;

    int numConsists = manager->getConsistList()->size();  //number of JMRI consists found
    if (log->isDebugEnabled()) {
        log->debug(numConsists + " consists found.");
    }

    if (isConsistAllowed) {  //  Allow Make & Break consists
        message = ("RCC" + numConsists);  //  Roster Consist Controller
    } else {  //  Just allow selection list
        message = ("RCL" + numConsists);  //  Roster Consist List
    }

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }
}

/*public*/ void ConsistController::sendAllConsistData() {
    // Loop thru JMRI consists and send consist detail for each
    foreach (DccLocoAddress* conAddr, manager->getConsistList()->toList()) {
        sendDataForConsist(manager->getConsist(conAddr));
    }

    // Loop through the NCE consists and send consist detail for each
 /* dboudreau 2/26/2012 added consist manager for NCE
     NceConsistRoster r = NceConsistRoster.getDefault();
     List<NceConsistRosterEntry> l = r.matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); // take all
     int i=-1;
     for (i = 0; i<l.size(); i++) {
     sendDataForNCEConsist(l.get(i));
     }
     */
}

//send consist detail record for a single NCE consist, e.g. RCD}|{127(S)}|{2591]\[2591(L)}|{true]\[6318(L)}|{true]\[2608(L)}|{false
/* dboudreau 2/26/2012 added consist manager for NCE
 public void sendDataForNCEConsist(NceConsistRosterEntry con){
 if (listeners == NULL) return;
 StringBuilder list = new StringBuilder("RCD");  //  Roster Consist Data
 list.append("}|{");
 list.append(con.getConsistNumber());  //address
 list.append("(S)}|{");  //consist address is always short
 if (con.getId().length() > 0){
 list.append(con.getId());   //id
 }

 //append entries for each loco (if set)
 list.append("]\\[");
 list.append(con.getLoco1DccAddress());  //loco address
 list.append(con.isLoco1LongAddress() ? "(L)" : "(S)");  //include length
 list.append("}|{");
 list.append((con.getLoco1Direction().equals("normal")));  //forward is true, reverse is false
 if (!con.getLoco2DccAddress().equals("")) {
 list.append("]\\[");
 list.append(con.getLoco2DccAddress());
 list.append(con.isLoco2LongAddress() ? "(L)" : "(S)");
 list.append("}|{");
 list.append((con.getLoco2Direction().equals("normal")));
 }
 if (!con.getLoco3DccAddress().equals("")) {
 list.append("]\\[");
 list.append(con.getLoco3DccAddress());
 list.append(con.isLoco3LongAddress() ? "(L)" : "(S)");
 list.append("}|{");
 list.append((con.getLoco3Direction().equals("normal")));
 }
 if (!con.getLoco4DccAddress().equals("")) {
 list.append("]\\[");
 list.append(con.getLoco4DccAddress());
 list.append(con.isLoco4LongAddress() ? "(L)" : "(S)");
 list.append("}|{");
 list.append((con.getLoco4Direction().equals("normal")));
 }
 if (!con.getLoco5DccAddress().equals("")) {
 list.append("]\\[");
 list.append(con.getLoco5DccAddress());
 list.append(con.isLoco5LongAddress() ? "(L)" : "(S)");
 list.append("}|{");
 list.append((con.getLoco5Direction().equals("normal")));
 }
 if (!con.getLoco6DccAddress().equals("")) {
 list.append("]\\[");
 list.append(con.getLoco6DccAddress());
 list.append(con.isLoco6LongAddress() ? "(L)" : "(S)");
 list.append("}|{");
 list.append((con.getLoco6Direction().equals("normal")));
 }

 String message = list.toString();

 for (ControllerInterface listener : listeners){
 listener.sendPacketToDevice(message);
 }
 }
 */
/*public*/ void ConsistController::sendDataForConsist(Consist* con) {
    if (listeners == NULL) {
        return;
    }
    QString list = QString("RCD");  //  Roster Consist Data
    list.append("}|{");
    list.append(con->getConsistAddress()->toString());
    list.append("}|{");
    if (con->getConsistID().length() > 0) {
        list.append(con->getConsistID());
    }

    foreach (DccLocoAddress*loco, con->getConsistList()) {
        list.append("]\\[");
        list.append(loco->toString());
        list.append("}|{");
        list.append(con->getLocoDirection(loco));
    }

    QString message = list;

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }
}

/*public*/ void ConsistController::setIsConsistAllowed(bool b) {
    isConsistAllowed = b;
}

//@Override
bool ConsistController::verifyCreation() {
    return isValid;
}

/**
 *
 * @param message string containing new consist information
 */
//@Override
void ConsistController::handleMessage(QString message) {
    try {
        if (message.at(0) == 'P') {  //  Change consist 'P'ositions
            reorderConsist(message);

        }
        if (message.at(0) == 'R') {  //  'R'emove consist
            removeConsist(message);

        }
        if (message.at(0) == '+') {  //  Add loco to consist and/or set relative direction
            addLoco(message);

        }
        if (message.at(0) == '-') {  //  remove loco from consist
            removeLoco(message);

        }
        if (message.at(0) == 'F') {   //  program CV 21 & 22 'F'unctions
            setConsistCVs(message);
        }
    } catch (NullPointerException exb) {
        log->warn("Message \"" + message + "\" does not match a consist command.");
    }
}

/**
 * Change the sequence of locos in this consist-> Reorders the consistList,
 * instead of setting the 'position' value. Lead and Trail are set on first
 * and last locos by DccConsist.
 *
 * @param message RCP<;>consistAddress<:>leadLoco<;>nextLoco<;>...
 * ...<;>nextLoco<;>trailLoco
 */
/*private*/ void ConsistController::reorderConsist(QString message) {
    Consist* consist;
    QStringList headerAndLocos = message.split("<:>");

    if (headerAndLocos.size() < 2) {
        log->warn("reorderConsist missing data in message: " + message);
        return;
    }

    try {
        QStringList headerData = (headerAndLocos.at(0).split("<;>"));
        //
        consist = manager->getConsist(stringToDcc(headerData.at(1)));

        QStringList locoData = (headerAndLocos.at(1).split("<;>"));
        /*
         * Reorder the consistList:
         * For each loco sent, remove it from the consistList
         * and reinsert it at the front of the list.
         */
        foreach (QString loco, locoData) {
            QList<DccLocoAddress*> conList = consist->getConsistList();
            int index = conList.indexOf(stringToDcc(loco));
            if (index != -1)
            {
             DccLocoAddress* val = conList.at(index);
                conList.append(val);
            }

        }

    } catch (NullPointerException e) {
        log->warn("reorderConsist error for message: " + message);
        return;
    }

    writeFile();

}

/**
 * remove a consist by it's Dcc address. Wiil remove all locos in the
 * process.
 *
 * @param message RCR<;>consistAddress
 */
/*private*/ void ConsistController::removeConsist(QString message) {
    QStringList header = message.split("<;>");
    Consist* consist = NULL;
    try {
        consist = manager->getConsist(stringToDcc(header.at(1)));
        while (!consist->getConsistList().isEmpty()) {
            DccLocoAddress* loco = consist->getConsistList().at(0);
            if (log->isDebugEnabled()) {
                log->debug("Remove loco: " + loco->toString() + ", from consist: " + consist->getConsistAddress()->toString());
            }
            consist->remove(loco);
        }
    } catch (NullPointerException noCon) {
        log->warn("Consist: " + header.at(1) + " not found. Cannot delete.");
        return;
    }

    try {
        manager->delConsist(stringToDcc(header.at(1)));
    } catch (NullPointerException noCon) {
        log->warn("Consist: " + header.at(1) + " not found. Cannot delete.");
        return;
    }

    writeFile();

}

/**
 * Add a loco or change it's direction. Creates a new consist if one does
 * not already exist
 *
 * @param message RC+<;>consistAddress<;>ID<:>locoAddress<;>directionNormal
 */
/*private*/ void ConsistController::addLoco(QString message) {
    Consist* consist;

    QStringList headerAndLoco =message.split("<:>");

    try {
        //  Break out header and either get existing consist or create new
        QStringList headerData = (headerAndLoco.at(0).split("<;>"));

        consist = manager->getConsist(stringToDcc(headerData.at(1)));
        consist->setConsistID(headerData.at(2));

        QStringList locoData = headerAndLoco.at(1).split("<;>");

        if (consist->isAddressAllowed(stringToDcc(locoData.at(0)))) {
            consist->add(stringToDcc(locoData.at(0)), locoData.at(1)=="true");
            if (log->isDebugEnabled()) {
                log->debug("add loco: " + locoData.at(0) + ", to consist: " + headerData.at(1));
            }
        }

    } catch (NullPointerException e) {
        log->warn("addLoco error for message: " + message);
        return;
    }

    writeFile();
}

/**
 * remove a loco if it exist in this consist->
 *
 * @param message RC-<;>consistAddress<:>locoAddress
 */
/*private*/ void ConsistController::removeLoco(QString message) {
    Consist* consist;

    QStringList headerAndLoco = message.split("<:>");

    if (log->isDebugEnabled()) {
        log->debug("remove loco string: " + message);
    }

    try {
        QStringList headerData = headerAndLoco.at(0).split("<;>");

        consist = manager->getConsist(stringToDcc(headerData.at(1)));

        QStringList locoData = headerAndLoco.at(1).split("<;>");

        DccLocoAddress* loco = stringToDcc(locoData.at(0));
        if (checkForBroadcastAddress(loco)) {
            return;
        }

        if (consist->contains(loco)) {
            consist->remove(loco);
            if (log->isDebugEnabled()) {
                log->debug("Remove loco: " + loco->toString() + ", from consist: " + headerData.at(1));
            }
        }
    } catch (NullPointerException e) {
        log->warn("removeLoco error for message: " + message);
        return;
    }

    writeFile();
}

/*private*/ void ConsistController::writeFile() {
#if 1
    try {
        if (WiThrottleManager::withrottlePreferencesInstance()->isUseWiFiConsist()) {
            file->writeFile(manager->getConsistList()->toList(), WiFiConsistFile::getFileLocation() + "wifiConsist.xml");
        } else {
            file->writeFile(manager->getConsistList()->toList());
        }
    } catch (IOException e) {
        log->warn("Consist file could not be written!");
    }
#endif
}

/**
 * set CV 21&22 for consist functions send each CV individually
 *
 * @param message RCF<;> locoAddress <:> CV# <;> value
 */
/*private*/ void ConsistController::setConsistCVs(QString message) {

    DccLocoAddress* loco;

    QStringList headerAndCVs = (message.split("<:>"));

    if (log->isDebugEnabled()) {
        log->debug("setConsistCVs string: " + message);
    }

    try {
        QStringList headerData = (headerAndCVs.at(0).split("<;>"));

        loco = stringToDcc(headerData.at(1));
        if (checkForBroadcastAddress(loco)) {
            return;
        }

    } catch (NullPointerException e) {
        log->warn("setConsistCVs error for message: " + message);

        return;
    }
    AddressedProgrammer* pom = ((AddressedProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->getAddressedProgrammer(loco);

    // loco done, now get CVs
    for (int i = 1; i < headerAndCVs.size(); i++) {
        QStringList CVData = (headerAndCVs.at(i).split("<;>"));

        try {
            int CVValue = CVData.at(1).toInt();
            try {
                pom->writeCV(CVData.at(0), CVValue, (ProgListener*)this);
            } catch (ProgrammerException e) {
            }
        } catch (NumberFormatException nfe) {
            log->warn("Error in setting CVs: " + nfe.getMessage());
        }
    }
    ((AddressedProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->releaseAddressedProgrammer(pom);

}

//@Override
/*public*/ void ConsistController::programmingOpReply(int value, int status) {

}

/*public*/ DccLocoAddress* ConsistController::stringToDcc(QString s) {
    int num = (s.mid(1).toInt());
    bool isLong = (s.at(0) == 'L');
    return (new DccLocoAddress(num, isLong));
}

/**
 * Check to see if an address will try to broadcast (0) a programming
 * message.
 *
 * @param addr The address to check
 * @return true if address is no good, otherwise false
 */
/*public*/ bool ConsistController::checkForBroadcastAddress(DccLocoAddress* addr) {
    if (addr->getNumber() < 1) {
        log->warn("Trying to use broadcast address!");
        return true;
    }
    return false;
}

//@Override
void ConsistController::_register() {
    throw new UnsupportedOperationException("Not used.");
}

//@Override
void deregister() {
    throw new UnsupportedOperationException("Not used.");
}

/*private*/ /*final*/ /*static*/ Logger* ConsistController::log = LoggerFactory::getLogger("ConsistController");
