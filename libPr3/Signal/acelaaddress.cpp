#include "acelaaddress.h"
#include "loggerfactory.h"
#include "acelanode.h"
#include "acelasystemconnectionmemo.h"
#include "namedbean.h"
#include "acelatrafficcontroller.h"
#include "instancemanager.h"
#include "light.h"

/**
* Utility Class supporting parsing and testing of addresses for Acela.
* <p>
* One address format is supported: Atxxxx where: t is the type code, 'T' for
* turnouts, 'S' for sensors, and 'L' for lights xxxx is a bit number of the
* input or output bit (0-16383) examples: AT2 (bit 2), AS1003 (bit 1003), AL134
* (bit134).<p>
* Note: Not fully supporting long system connection prefix yet
*
* @author Dave Duchamp, Copyright (C) 2004 - 2006
* @author Bob Coleman Copyright (C) 2007, 2008, 2009 Based on CMRI serial
* example, modified to establish Acela support.
*/
// /*public*/  class AcelaAddress {

/*public*/  AcelaAddress::AcelaAddress(QObject *parent) :QObject(parent){
}

/*static*/ /*final*/ int AcelaAddress::MINSENSORADDRESS = 0;
/*static*/ /*final*/ int AcelaAddress::MAXSENSORADDRESS = AcelaNode::MAXSENSORBITS * AcelaNode::MAXNODE -1;
/*static*/ /*final*/ int AcelaAddress::MINOUTPUTADDRESS = 0;
/*static*/ /*final*/ int AcelaAddress::MAXOUTPUTADDRESS = AcelaNode::MAXOUTPUTBITS * AcelaNode::MAXNODE -1;

/**
 * public  static method to parse an Acela system name and return the Acela
 * Node Address.
 * <p>
 * Note: Returns '-1' if illegal systemName format or if the
 * node is not found.
 * Nodes are numbered from 0 - {@value AcelaNode#MAXNODE}.
 * @param systemName system name.
 * @param memo system connection.
 * @return node address number.
 */
/*public*/  /*static*/ int AcelaAddress::getNodeAddressFromSystemName(QString systemName, AcelaSystemConnectionMemo* memo) {
    // validate the system Name leader characters
    if (validSystemNameFormat(systemName, systemName.at(memo->getSystemPrefix().length()), memo->getSystemPrefix()) != Manager::NameValidity::VALID) {
        // No point in trying if a valid system name format is not present
        return (-1);
    }
    int num = getBitFromSystemName(systemName, memo->getSystemPrefix());
    if (num < 0) {
        log->error(tr("invalid Acela system name: %1").arg(systemName));
        return (-1);
    }
    // This is a ALnnxxx address
    int nodeaddress = -1;
    if (systemName.at(memo->getSystemPrefix().length()) == 'S') {
        // Acela has two address spaces: true == sensor address space; false == output address space
        nodeaddress = memo->getTrafficController()->lookupAcelaNodeAddress(num, true);
    } else {
        // Acela has two address spaces: true == sensor address space; false == output address space
        nodeaddress = memo->getTrafficController()->lookupAcelaNodeAddress(num, false);
    }
    return (nodeaddress);
}

/**
 * public  static method to parse an Acela system name.
 *
 * @param systemName system name to parse.
 * @param memo system connection.
 * @return the Acela Node number, return 'null' if illegal systemName format or if the node is
 * not found
 */
/*public*/  /*static*/ AcelaNode* AcelaAddress::getNodeFromSystemName(QString systemName, AcelaSystemConnectionMemo* memo) {
    // get the node address
    int ua;

    ua = getNodeAddressFromSystemName(systemName, memo);
    if (ua == -1) {
        // error messages have already been issued by getNodeAddressFromSystemName
        return nullptr;
    }

    AcelaNode* tempnode;
    tempnode = (AcelaNode*) (memo->getTrafficController()->getNodeFromAddress(ua));

    return tempnode;
}

/**
 * public  static method to parse an Acela system name and return the bit number.
 * Note: Bits are numbered from 1.
 *
 * @param systemName system name.
 * @param prefix bean type, S, T, L or H.
 * @return the bit number, return -1 if an error is found (0 is a valid bit?)
 */
/*public*/  /*static*/ int AcelaAddress::getBitFromSystemName(QString systemName, QString prefix) {
    // validate the System Name leader characters
    if (!(systemName.startsWith(prefix)) || ((systemName.at(prefix.length()) != 'L')
            && (systemName.at(prefix.length()) != 'S') && (systemName.at(prefix.length()) != 'T')
            && (systemName.at(prefix.length()) != 'H'))) {
        // here if an invalid Acela format
        log->error(tr("illegal character in header field of system name: %1").arg(systemName));
        return (-1);
    }
    // try to parse remaining system name part
    int num = -1;
    bool ok;
        num = systemName.mid(prefix.length() + 1).toInt(&ok); // multi char prefix
    if(!ok) {
        log->warn(tr("invalid character in number field of system name: %1").arg(systemName));
        return (-1);
    }
    if (num < 0) {
        log->warn(tr("invalid Acela system name: %1").arg(systemName));
        return (-1);
    }
    return (num);
}

/**
 * public  static method to validate system name format.
 * Logging of handled cases no higher than WARN.
 *
 * @param systemName system name to validate.
 * @param type bean type, S, T or L.
 * @param prefix system prefix.
 * @return 'true' if system name has a valid format, else return 'false'
 */
/*public*/  /*static*/ Manager::NameValidity AcelaAddress::validSystemNameFormat(/*@Nonnull*/ QString systemName, QChar type, QString prefix) {
    // validate the system Name leader characters
    if (!systemName.startsWith(prefix + type )) {
        // here if an illegal format
        log->error(tr("invalid character in header field of system name: %1").arg(systemName));
        return Manager::NameValidity::INVALID;
    }
    int num;
    bool ok;
        num = systemName.mid(prefix.length() + 1).toInt(&ok);
    if(!ok) {
        log->debug(tr("invalid character in number field of system name: %1").arg(systemName));
        return Manager::NameValidity::INVALID;
    }
    if (num >= 0) {
        // This is an ALnnxxx address
        return Manager::NameValidity::VALID;
    } else {
        log->debug(tr("invalid Acela system name: ").arg(systemName));
        return Manager::NameValidity::INVALID;
    }
}

/**
 * public  static method to validate Acela system name for configuration.
 *
 * @param systemName system name to validate.
 * @param type bean type, S, T or L.
 * @param memo system connection.
 * @return 'true' if system name has a valid meaning in current
 * configuration, else return 'false'
 */
//@SuppressFBWarnings(value = "DB_DUPLICATE_SWITCH_CLAUSES", justification="additional check for valid bit value")
/*public*/  /*static*/ bool AcelaAddress::validSystemNameConfig(QString systemName, QChar type, AcelaSystemConnectionMemo* memo) {
    if (validSystemNameFormat(systemName, type, memo->getSystemPrefix()) != Manager::NameValidity::VALID) {
        // No point in trying if a valid system name format is not present
        return false;
    }
    AcelaNode* node = getNodeFromSystemName(systemName, memo);
    if (node == nullptr) {
        // The node indicated by this system address is not present
        return false;
    }
    int bit = getBitFromSystemName(systemName, memo->getSystemPrefix());
    switch (type.toLatin1()) {
        case 'T':
        case 'L':
            if ((bit >= MINOUTPUTADDRESS) && (bit <= MAXOUTPUTADDRESS)) {
                // The bit is within valid range for this defined Acela node
                return true;
            }
            break;
        case 'S':
            if ((bit >= MINSENSORADDRESS) && (bit <= MAXSENSORADDRESS)) {
                // The bit is within valid range for this defined Acela node
                return true;
            }
            break;
        default:
            log->error("Invalid type specification in validSystemNameConfig call");
            return false;
    }
    // System name has failed all tests
    log->warn(tr("Acela hardware address out of range in system name: %1").arg(systemName));
    return false;
}

/*public*/  /*static*/ bool AcelaAddress::validSystemNameConfig(QString systemName, AcelaSystemConnectionMemo* memo) {
    QChar type = systemName.at(memo->getSystemPrefix().length());
    return validSystemNameConfig(systemName, type, memo);
}

/**
 * public  static method to convert one format Acela system name for the
 * alternate format.
 *
 * @param systemName system name to convert.
 * @param prefix system prefix.
 * @return name (string) in alternate format, or empty string if the supplied
 * system name does not have a valid format, or if there is no representation
 * in the alternate naming scheme.
 */
/*public*/  /*static*/ QString AcelaAddress::convertSystemNameToAlternate(QString systemName, QString prefix) {
    // ensure that input system name has a valid format
    if (validSystemNameFormat(systemName, systemName.at(prefix.length()), prefix) != Manager::NameValidity::VALID) {
        // No point in trying if a valid system name format is not present
        return "";
    }
    QString altName = "";
    altName = systemName;
    return altName;
}

/**
 * public  static method to normalize an Acela system name.
 * <p>
 * This routine is used to ensure that each system name is uniquely linked
 * to one Acela bit, by removing extra zeros inserted by the user.
 *
 * @param systemName system name to normalize.
 * @param prefix system prefix.
 * @return a normalized name is returned in the same format as the input name,
 * or an empty string if the supplied system name does not have a valid format.
 */
/*public*/  /*static*/ QString AcelaAddress::normalizeSystemName(QString systemName, QString prefix) {
    // ensure that input system name has a valid format
    if (validSystemNameFormat(systemName, systemName.at(prefix.length()), prefix) != Manager::NameValidity::VALID) {
        // No point in normalizing if a valid system name format is not present
        return "";
    }
    // check if bit number is within the valid range
    int bitNum = getBitFromSystemName(systemName, prefix);
    QChar type = systemName.at(prefix.length());
    if (bitNum < 0) {
        return "";
    }
    // everything OK, normalize the address
    QString nName = "";
    nName = prefix + type + QString::number(bitNum);
    return nName;
}

/**
 * public  static method to construct an Acela system name from type
 * character, node address, and bit number.
 *
 * @param type bean type letter, S, T or L.
 * @param nAddress node address.
 * @param bitNum bit number.
 * @param memo system connection.
 * @return a system name in the ALxxxx, ATxxxx, or ASxxxx
 * format. The returned name is normalized.
 * Return the null string "" if the supplied character is not valid,
 * or if the node address is out of the 0 - 127 range, or the bit number is
 * out of the 1 - 2048 range and an error message is logged.
 */
/*public*/  /*static*/ QString AcelaAddress::makeSystemName(QString type, int nAddress, int bitNum, AcelaSystemConnectionMemo* memo) {
    QString nName = "";
    // check the type character
    if ((type.toUpper() != "S") && (type.toUpper() != "L") && (type.toUpper()!="T")) {
        // here if an illegal type character
        log->error(tr("invalid type character proposed for system name"));
        return (nName);
    }
    // check the node address
    if ((nAddress < memo->getTrafficController()->getMinimumNodeAddress()) || (nAddress > memo->getTrafficController()->getMaximumNumberOfNodes())) {
        // here if an illegal node address
        log->warn("invalid node adddress proposed for system name");
        return (nName);
    }
    // check the bit number
    if (type.toUpper() == "S" && ((bitNum < 0) || (bitNum > MAXSENSORADDRESS))) {
        // here if an illegal bit number
        log->warn("invalid bit number proposed for Acela Sensor");
        return (nName);
    }
    if ((type.toUpper() ==("L") || type.toUpper()==("T")) && ((bitNum < 0) || (bitNum > MAXOUTPUTADDRESS))) {
        // here if an illegal bit number
        log->warn(tr("invalid bit number proposed for Acela Turnout or Light"));
        return (nName);
    }
    // construct the address
    nName = memo->getSystemPrefix() + type + QString::number((bitNum));
    return (nName);
}

/**
 * public  static method to check the user name for a valid system name.
 *
 * @param systemName system name to check.
 * @param prefix bean prefix, S, T or L.
 * @return "" (null string) if the system name is not valid or does not exist
 */
/*public*/  /*static*/ QString AcelaAddress::getUserNameFromSystemName(QString systemName, QString prefix) {
    // check for a valid system name
    if ((systemName.length() < (prefix.length() + 2)) || (!systemName.startsWith(prefix))) {
        // not a valid system name for Acela
        return ("");
    }
    // check for a sensor
    if (systemName.at(prefix.length() + 1) == 'S') {
        Sensor* s = nullptr;
        s = (Sensor*)InstanceManager::sensorManagerInstance()->getBySystemName(systemName);
        if (s != nullptr) {
            return s->getUserName();
        } else {
            return ("");
        }
    } // check for a turnout
    else if (systemName.at(prefix.length() + 1) == 'T') {
        Turnout* t = nullptr;
        t = (Turnout*)InstanceManager::turnoutManagerInstance()->getBySystemName(systemName);
        if (t != nullptr) {
            return t->getUserName();
        } else {
            return ("");
        }
    } // check for a light
    else if (systemName.at(prefix.length() + 1) == 'L') {
        Light* lgt = nullptr;
        lgt = (Light*)InstanceManager::lightManagerInstance()->getBySystemName(systemName);
        if (lgt != nullptr) {
            return lgt->getUserName();
        } else {
            return ("");
        }
    }

    // not any known sensor, light, or turnout
    return ("");
}

/*private*/ /*final*/ /*static*/ Logger* AcelaAddress::log = LoggerFactory::getLogger("AcelaAddress");
