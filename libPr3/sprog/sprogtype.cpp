#include "sprogtype.h"
#include "loggerfactory.h"

using namespace Sprog;

/**
 * Class to hold SPROG type
 *
 * @author	Andrew crosland Copyright (C) 2012
 */
///*public*/ class SprogType {



/**
 * Construct a new SPROG type of a given type.
 *
 * @param type int, one of SprogType.xxx constants
 */
/*public*/ SprogType::SprogType(int type, QObject* parent) : QObject(parent)
 {
  _sprogType = UNKNOWN;
    if (log->isDebugEnabled()) {
        log->debug("SprogType(int) ctor, type: " + type);
    }
    _sprogType = type;
}

/**
 * Check for any SPROG type
 *
 * @return true if this object holds a SPROG type
 */
/*public*/ bool SprogType::isSprog() {
    if (_sprogType < SPROGV4) {
        return false;
    }
    return true;
}

/**
 * Check for a SPROG II type
 *
 * @return true if this object holds a SPROG II type
 */
/*public*/ bool SprogType::isSprogII() {
    if ((_sprogType >= SPROGII) && (_sprogType <= SPROGIIv4)) {
        return true;
    }
    return false;
}

/**
 * Return the multiplier for scaling the current limit from hardware units
 * to physical units (mA).
 *
 * @return the multiplier for the current limit
 */
/*public*/ double SprogType::getCurrentMultiplier()
{
    switch (_sprogType) {
        case PISPROGONE:
            // Value returned is number of ADC steps 0f 3.22mV across 0.47
            // ohms, or equivalent
            return 3220.0/470;

        default:
            // Value returned is number of ADC steps 0f 4.88mV across 0.47
            // ohms, or equivalent
            return 4880.0/470;
    }
}

/**
 * Get the Flash memory block Length for bootloader.
 *
 * @return blocklen
 */
/*public*/ int SprogType::getBlockLen() {
    switch (_sprogType) {
        case NO_PROMPT_FOUND:
        case NOT_A_SPROG:
        case NOT_RECOGNISED:
        case TIMEOUT:
        default:
            return -1;

        case SPROGV4:
        case SPROGIIUSB:
        case SPROGII:
            return 8;

        case SPROGIIv3:
        case SPROGIIv4:
        case SPROG3:
        case SPROGIV:
        case SPROG5:
        case PISPROGONE:
        case NANO:
        case PISPROGNANO:
        case SNIFFER:
            return 16;
    }
}

/**
 * Get the Flash memory block Length for bootloader.
 *
 * @param bootVer the bootloader version
 * @return length in bytes
 */
/*static*/ /*public*/ int SprogType::getBlockLen(int bootVer) {
    switch (bootVer) {
        case 10:
        case 11:
            return 8;
        case 13:
            return 16;
        default:
            return -1;
    }
}

/**
 * Check if an address is one which should be reprogrammed during bootloader
 * operation. Checks if address is above the bootloader's address space and
 * below the debug executive's address space.
 *
 * @param addr int
 * @return true or false
 */
/*public*/ bool SprogType::isValidFlashAddress(int addr) {
    switch (_sprogType) {
        case SPROGV4:

        case SPROGIIUSB:
        case SPROGII:
            if (addr >= 0x200) {
                return true;
            }
            break;

        case SPROGIIv3:
        case SPROGIIv4:
        case SPROG3:
        case SPROGIV:
        case SPROG5:
        case NANO:
        case SNIFFER:
            if ((addr >= 0x2200) && (addr < 0x3F00)) {
                return true;
            }
            break;

        case PISPROGNANO:
            if ((addr >= 0x0C00) && (addr < 0x1FF0)) {
                return true;
            }
            break;

        case PISPROGONE:
            if ((addr >= 0x1000) && (addr < 0x3F00)) {
                return true;
            }
            break;

        default:
            return false;
    }
    return false;
}

/*public*/ int SprogType::getEraseStart() {
    switch (_sprogType) {
        case SPROGIIUSB:
        case SPROGII:
            return 0x200;

        case SPROGIIv3:
        case SPROGIIv4:
        case SPROG3:
        case SPROGIV:
        case SPROG5:
        case NANO:
        case SNIFFER:
            return 0x2200;

        case PISPROGNANO:
            return 0x0C00;

        case PISPROGONE:
            return 0x1000;

        default:
            break;
    }
    log->error("Can't determine erase start adress");
    return -1;
}

/**
 *
 * @return String representation of a SPROG type
 */
//@Override
/*public*/ QString SprogType::toString() {
    return this->toString(_sprogType);
}

/**
 *
 * @return String representation of a SPROG type
 */
/*public*/ QString SprogType::toString(int t) {
    //if (log->isDebugEnabled()) { log->debug("Integer {}", t); }
    switch (t) {
        case NO_PROMPT_FOUND:
            return tr("No SPROG prompt found");
        case NOT_A_SPROG:
            return tr("Not connected to a SPROG");
        case NOT_RECOGNISED:
            return tr("Unrecognised SPROG");
        case TIMEOUT:
            return tr("Timeout talking to SPROG");
        case SPROGV4:
            return "SPROG ";
        case SPROGIIUSB:
            return "SPROG II USB ";
        case SPROGII:
            return "SPROG II ";
        case SPROGIIv3:
            return "SPROG IIv3 ";
        case SPROGIIv4:
            return "SPROG IIv4 ";
        case SPROG3:
            return "SPROG 3 ";
        case SPROGIV:
            return "SPROG IV ";
        case SPROG5:
            return "SPROG 5 ";
        case PISPROGONE:
            return "Pi-SPROG One ";
        case NANO:
            return "SPROG Nano ";
        case PISPROGNANO:
            return "Pi-SPROG Nano ";
        case SNIFFER:
            return "SPROG Sniffer ";
        default:
            return tr("Unknown Hardware");
    }
}

/*private*/ /*final*/ /*static*/ Logger* SprogType::log = LoggerFactory::getLogger("SprogType");
