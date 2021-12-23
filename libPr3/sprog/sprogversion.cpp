#include "sprogversion.h"
#include "loggerfactory.h"
#include "sprogtype.h"
#include "exceptions.h"

using namespace Sprog;
/**
 * Class to hold SPROG type and firmware version.
 *
 * @author	Andrew Crosland Copyright (C) 2012
 */
///*public*/ class SprogVersion {


/**
 * Construct a new SPROG version object from a SPROG type
 *
 * @param t SprogType the type of SPROG
 */
/*public*/ SprogVersion::SprogVersion(SprogType* t, QObject* parent) : QObject(parent) {
 common();
    if (log->isDebugEnabled()) {
        log->debug("SprogVersion(SprogType) ctor: " + t->toString());
    }
    sprogType = t;
    sprogVersion = "";
}

/**
 * Construct a new SPROG version object from a SPROG type and version.
 *
 * @param t SprogType the type of SPROG
 * @param s String version in "major.minor" format, e.g. "3.1"
 */
/*public*/ SprogVersion::SprogVersion(SprogType* t, QString s, QObject* parent)
{
 common();
    if (log->isDebugEnabled()) {
        log->debug("SprogVersion(SprogType, String) ctor: " + t->toString() + "v" + s);
    }
    if (log->isDebugEnabled()) {
        log->debug("sprogType: " + t->_sprogType);
    }
    sprogType = t;
    sprogVersion = s;
}

void SprogVersion::common()
{
sprogType = NULL;
sprogVersion = "";
}

/**
 * Return major version number for a known SPROG.
 *
 * @return major version
 */
/*public*/ int SprogVersion::getMajorVersion() {
    int major = 0;
    if (sprogType->isSprog()) {
        try {
      bool ok;
            major = sprogVersion.mid(sprogVersion.indexOf(".")
                    - 1, sprogVersion.indexOf(".")).toInt(&ok);
            if(!ok) throw NumberFormatException();
        } catch (NumberFormatException* e) {
            log->error("Cannot parse SPROG major version number");
        }
    }
    return major;
}

/**
 * Return minor version number for a known SPROG.
 *
 * @return minor version
 */
/*public*/ int SprogVersion::getMinorVersion() {
    int minor = 0;
    if (sprogType->isSprog()) {
        try {
      bool ok;
            minor = sprogVersion.mid(sprogVersion.indexOf(".")
                    + 1, sprogVersion.indexOf(".") + 2).toInt(&ok);
            if(!ok) throw NumberFormatException();
        } catch (NumberFormatException* e) {
            log->error("Cannot parse SPROG minor version number");
        }
    }
    return minor;
}

/**
 * Check if the SPROG has various extra features that were not present in
 * the original firmware. This means later SPROG II versions or any type
 * equal or higher than SPROG 3.
 *
 * @return bool if the current SPROG has extra features
 */
/*public*/ bool SprogVersion::hasExtraFeatures() {
    int major = this->getMajorVersion();
    int minor = this->getMinorVersion();
    if (log->isDebugEnabled()) {
        log->debug("Major: " + QString::number(major) + " Minor: " + QString::number(minor));
    }
    if (this->sprogType->isSprogII() && (((major == 1) && (minor >= 6))
            || ((major == 2) && (minor >= 1))
            || (major >= 3))
            || ((this->sprogType->_sprogType >= SprogType::SPROGIIv3)
                && (this->sprogType->_sprogType < SprogType::NANO))) {
        if (log->isDebugEnabled()) {
            log->debug("This version has extra features");
        }
        return true;
    }
    if (log->isDebugEnabled()) {
        log->debug("This version does not have extra features");
    }
    return false;
}

/**
 * Check if the SPROG has blueline decoder mode.
 *
 * @return true if the SPROG has blueline decoder support
 */
/*public*/ bool SprogVersion::hasBlueLine() {
    return this->hasExtraFeatures();
}

/**
 * Check if the SPROG has an adjustable current limit.
 *
 * @return true if the SPROG has adjustable current limit
 */
/*public*/ bool SprogVersion::hasCurrentLimit() {
    return this->hasExtraFeatures();
}

/**
 * Check if the SPROG has an interlock for the bootloader.
 *
 * @return true if the SPROG has firmware interlock
 */
/*public*/ bool SprogVersion::hasFirmwareLock() {
    return (this->hasExtraFeatures() || (this->sprogType->_sprogType <= SprogType::NANO));
}

/*public*/ bool SprogVersion::hasZTCMode() {
    return (this->sprogType->_sprogType < SprogType::NANO);
}

/**
 *
 * @return String representation of SPROG version
 */
//@Override
/*public*/ QString SprogVersion::toString() {
    return this->toString(this);
}

/**
 *
 * @return String representation of SPROG version
 */
/*public*/ QString SprogVersion::toString(SprogVersion* s) {
    if (log->isDebugEnabled()) {
        log->debug("sprogType: " + s->sprogType->_sprogType);
    }
    return (s->sprogType->toString() +" v"+ sprogVersion);
}

/*private*/ /*final*/ /*static*/ Logger* SprogVersion::log = LoggerFactory::getLogger("SprogVersion");
