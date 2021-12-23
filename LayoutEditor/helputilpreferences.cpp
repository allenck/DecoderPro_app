#include "helputilpreferences.h"
#include "profilemanager.h"
#include "preferences.h"
#include "profileutils.h"

/**
 * Preferences for HelpUtil
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ final class HelpUtilPreferences extends PreferencesBean implements InstanceManagerAutoDefault {

    /*public*/ /*static*/ /*final*/ QString HelpUtilPreferences::OPEN_HELP_ONLINE = "openHelpOnline";
    /*public*/ /*static*/ /*final*/ QString HelpUtilPreferences::OPEN_HELP_ON_FILE = "openHelpOnFile";
    /*public*/ /*static*/ /*final*/ QString HelpUtilPreferences::OPEN_HELP_ON_JMRI_WEB_SERVER = "openHelpOnJMRIWebServer";



    /*public*/ HelpUtilPreferences::HelpUtilPreferences(QObject *parent) : PreferencesBean(ProfileManager::getDefault()->getActiveProfile(), parent){
        //super(ProfileManager.getDefault().getActiveProfile());
        Preferences* sharedPreferences = ProfileUtils::getPreferences(
                PreferencesBean::getProfile(), /*this.getClass()*/"jmri.util.HelpUtilPreferences", true);
        this->readPreferences(sharedPreferences);
    }

    /*private*/ void HelpUtilPreferences::readPreferences(Preferences* sharedPreferences) {
        _openHelpOnline = sharedPreferences->getBoolean(OPEN_HELP_ONLINE, _openHelpOnline);
        _openHelpOnFile = sharedPreferences->getBoolean(OPEN_HELP_ON_FILE, _openHelpOnFile);
        _openHelpOnJMRIWebServer = sharedPreferences->getBoolean(OPEN_HELP_ON_JMRI_WEB_SERVER, _openHelpOnJMRIWebServer);

/*
        this.allowRemoteConfig = sharedPreferences.getbool(ALLOW_REMOTE_CONFIG, this.allowRemoteConfig);
        this.clickDelay = sharedPreferences.getInt(CLICK_DELAY, this.clickDelay);
        this.simple = sharedPreferences.getbool(SIMPLE, this.simple);
        this.railroadName = sharedPreferences.get(RAILROAD_NAME, this.railroadName);
        this.readonlyPower = sharedPreferences.getbool(READONLY_POWER, this.readonlyPower);
        this.refreshDelay = sharedPreferences.getInt(REFRESH_DELAY, this.refreshDelay);
        this.useAjax = sharedPreferences.getbool(USE_AJAX, this.useAjax);
        this.disableFrames = sharedPreferences.getbool(DISABLE_FRAME_SERVER, this.disableFrames);
        this.redirectFramesToPanels = sharedPreferences.getbool(REDIRECT_FRAMES, this.redirectFramesToPanels);
        try {
            Preferences frames = sharedPreferences.node(DISALLOWED_FRAMES);
            if (frames.keys().length != 0) {
                this.disallowedFrames.clear();
                for (String key : frames.keys()) { // throws BackingStoreException
                    String frame = frames.get(key, null);
                    if (frame != null && !frame.trim().isEmpty()) {
                        this.disallowedFrames.add(frame);
                    }
                }
            }
        } catch (BackingStoreException* ex) {
            // this is expected if sharedPreferences have not been written previously,
            // so do nothing.
        }
        this.port = sharedPreferences.getInt(PORT, this.port);
        this.useZeroConf = sharedPreferences.getbool(USE_ZERO_CONF, this.useZeroConf);
*/
        setIsDirty(false);
    }

    /*public*/ bool HelpUtilPreferences::compareValuesDifferent(HelpUtilPreferences* prefs) {
        if (getOpenHelpOnline() != prefs->getOpenHelpOnline()) {
            return true;
        }
        if (getOpenHelpOnFile() != prefs->getOpenHelpOnFile()) {
            return true;
        }
        return (getOpenHelpOnJMRIWebServer() != prefs->getOpenHelpOnJMRIWebServer());
    }

    /*public*/ void HelpUtilPreferences::apply(HelpUtilPreferences* prefs) {
        setOpenHelpOnline(prefs->getOpenHelpOnline());
        setOpenHelpOnFile(prefs->getOpenHelpOnFile());
        setOpenHelpOnJMRIWebServer(prefs->getOpenHelpOnJMRIWebServer());
    }

    /*public*/ void HelpUtilPreferences::save() {
        Preferences* sharedPreferences = ProfileUtils::getPreferences(this->getProfile(), /*this.getClass()*/"jmri.util.HelpUtilPreferences", true);
        sharedPreferences->putBoolean(OPEN_HELP_ONLINE, this->getOpenHelpOnline());
        sharedPreferences->putBoolean(OPEN_HELP_ON_FILE, this->getOpenHelpOnFile());
        sharedPreferences->putBoolean(OPEN_HELP_ON_JMRI_WEB_SERVER, this->getOpenHelpOnJMRIWebServer());
    }

    /*public*/ void HelpUtilPreferences::setOpenHelpOnline(bool value) {
        _openHelpOnline = value;
        setIsDirty(true);
    }

    /*public*/ bool HelpUtilPreferences::getOpenHelpOnline() {
        return _openHelpOnline;
    }

    /*public*/ void HelpUtilPreferences::setOpenHelpOnFile(bool value) {
        _openHelpOnFile = value;
        setIsDirty(true);
    }

    /*public*/ bool HelpUtilPreferences::getOpenHelpOnFile() {
        return _openHelpOnFile;
    }

    /*public*/ void HelpUtilPreferences::setOpenHelpOnJMRIWebServer(bool value) {
        _openHelpOnJMRIWebServer = value;
        setIsDirty(true);
    }

    /*public*/ bool HelpUtilPreferences::getOpenHelpOnJMRIWebServer() {
        return _openHelpOnJMRIWebServer;
    }
