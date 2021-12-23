#include "zeroconfpreferences.h"
#include "loggerfactory.h"
#include "preferences.h"
#include "profileutils.h"
#include "preferences.h"

/**
 * Preferences manager for ZeroConf networking.
 * <p>
 * <strong>NOTE:</strong> preferences are immediately changed and stored when
 * set, although not all code that reads these preferences responds to changes
 * in the preferences immediately.
 * <p>
 * <strong>NOTE:</strong> these preferences apply to all JMRI applications and
 * all profiles on the computer on which they are set.
 *
 * @author Randall Wood (C) 2018
 */
// /*public*/ class ZeroConfPreferences extends PreferencesBean {

    // Setting and default values
    // API constants
    /**
     * Deprecated name in profile.properties.
     *
     * @deprecated since 4.15.1; use {@link #USE_IP_V4} instead
     */
    //@Deprecated
    /*private*/ /*static*/ /*final*/ QString ZeroConfPreferences::IPv4 = "IPv4";
    /**
     * Deprecated name in profile.properties.
     *
     * @deprecated since 4.15.1; use {@link #USE_IP_V6} instead
     */
    //@Deprecated
    /*private*/ /*static*/ /*final*/ QString ZeroConfPreferences::IPv6 = "IPv6";
    /**
     * Preferences name in profile.properties and property to subscribe to
     * notification changes for.
     * <p>
     * {@value #USE_IP_V4}
     */
    /*public*/ /*static*/ /*final*/ QString ZeroConfPreferences::USE_IP_V4 = "useIPv4";
    /**
     * Preferences name in profile.properties and property to subscribe to
     * notification changes for.
     * <p>
     * {@value #USE_IP_V6}
     */
    /*public*/ /*static*/ /*final*/ QString ZeroConfPreferences::USE_IP_V6 = "useIPv6";
    /**
     * Preferences name in profile.properties and property to subscribe to
     * notification changes for.
     * <p>
     * {@value #USE_LOOPBACK}
     */
    /*public*/ /*static*/ /*final*/ QString ZeroConfPreferences::USE_LOOPBACK = "useLoopback";
    /**
     * Preferences name in profile.properties and property to subscribe to
     * notification changes for.
     * <p>
     * {@value #USE_LINK_LOCAL}
     */
    /*public*/ /*static*/ /*final*/ QString ZeroConfPreferences::USE_LINK_LOCAL = "useLinkLocal";
    /*private*/ /*final*/ /*static*/ Logger* ZeroConfPreferences::log = LoggerFactory::getLogger("ZeroConfPreferences");

    /*public*/ ZeroConfPreferences::ZeroConfPreferences(Profile* profile) : PreferencesBean(profile){
        //super(profile);
        Preferences* localPreferences = ProfileUtils::getPreferences(nullptr, this->getClass(), false);
        Preferences* privatePreferences = ProfileUtils::getPreferences(profile, this->getClass(), false);
        Preferences* sharedPreferences = ProfileUtils::getPreferences(profile, this->getClass(), true);
        // read IPv4/IPv6 preferences from all-profile local, then per-profile local, then per-profile shared
        // using first preference setting encountered, defaulting to true
        this->useIPv4 = localPreferences->getBoolean(USE_IP_V4, privatePreferences->getBoolean(IPv4, sharedPreferences->getBoolean(IPv4, this->useIPv4)));
        this->useIPv6 = localPreferences->getBoolean(USE_IP_V6, privatePreferences->getBoolean(IPv6, sharedPreferences->getBoolean(IPv6, this->useIPv6)));
        this->useLinkLocal = localPreferences->getBoolean(USE_LINK_LOCAL, this->useLinkLocal);
        this->useLoopback = localPreferences->getBoolean(USE_LOOPBACK, this->useLoopback);
    }

    /*public*/ bool ZeroConfPreferences::isUseIPv4() {
        return useIPv4;
    }

    /*public*/ void ZeroConfPreferences::setUseIPv4(bool useIPv4) {
        bool old = this->useIPv4;
        this->useIPv4 = useIPv4;
        savePreferences(getProfile());
        firePropertyChange(USE_IP_V4, old, useIPv4);
    }

    /*public*/ bool ZeroConfPreferences::isUseIPv6() {
        return useIPv6;
    }

    /*public*/ void ZeroConfPreferences::setUseIPv6(bool useIPv6) {
        bool old = this->useIPv6;
        this->useIPv6 = useIPv6;
        savePreferences(getProfile());
        firePropertyChange(USE_IP_V6, old, useIPv6);
    }

    /*public*/ bool ZeroConfPreferences::isUseLoopback() {
        return useLoopback;
    }

    /*public*/ void ZeroConfPreferences::setUseLoopback(bool useLoopback) {
        bool old = this->useLoopback;
        this->useLoopback = useLoopback;
        savePreferences(getProfile());
        firePropertyChange(USE_LOOPBACK, old, useIPv6);
    }

    /*public*/ bool ZeroConfPreferences::isUseLinkLocal() {
        return useLinkLocal;
    }

    /*public*/ void ZeroConfPreferences::setUseLinkLocal(bool useLinkLocal) {
        bool old = this->useLinkLocal;
        this->useLinkLocal = useLinkLocal;
        savePreferences(getProfile());
        firePropertyChange(USE_LINK_LOCAL, old, useLinkLocal);
    }

    /*public*/ void ZeroConfPreferences::savePreferences(Profile* profile) {
        Preferences* localPreferences = ProfileUtils::getPreferences(nullptr, this->getClass(), false);
        localPreferences->putBoolean(USE_IP_V4, useIPv4);
        localPreferences->putBoolean(USE_IP_V6, useIPv6);
        localPreferences->putBoolean(USE_LINK_LOCAL, useLinkLocal);
        localPreferences->putBoolean(USE_LOOPBACK, useLoopback);
        try {
            localPreferences->sync();
        } catch (BackingStoreException* ex) {
            log->error("Unable to save preferences", ex);
        }
        // remove errant preferences elsewhere
        try {
            localPreferences->remove(IPv4);
            localPreferences->remove(IPv6);
            Preferences* sharedPreferences = ProfileUtils::getPreferences(profile, this->getClass(), true);
            sharedPreferences->remove(IPv4);
            sharedPreferences->remove(IPv6);
            Preferences* privatePreferences = ProfileUtils::getPreferences(profile, this->getClass(), false);
            privatePreferences->remove(IPv4);
            privatePreferences->remove(IPv6);
        } catch (IllegalStateException* ex) {
            log->error("Unable to remove no-longer-use preferences", ex);
        }
    }

    /*public*/ QString ZeroConfPreferences::getClass() { return "jmri.util.zeroconf.ZeroConfPreferences";}
