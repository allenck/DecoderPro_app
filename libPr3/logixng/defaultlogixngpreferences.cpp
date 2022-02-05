#include "defaultlogixngpreferences.h"
#include "profileutils.h"
#include "preferences.h"
/**
 * Preferences for LogixNG
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  /*final*/ class DefaultLogixNGPreferences extends PreferencesBean implements LogixNGPreferences {

    /*public*/  /*static*/ /*final*/ QString DefaultLogixNGPreferences::START_LOGIXNG_ON_LOAD = "startLogixNGOnStartup";
    /*public*/  /*static*/ /*final*/ QString DefaultLogixNGPreferences::USE_GENERIC_FEMALE_SOCKETS = "useGenericFemaleSockets";
    /*public*/  /*static*/ /*final*/ QString DefaultLogixNGPreferences::INSTALL_DEBUGGER = "installDebugger";
    /*public*/  /*static*/ /*final*/ QString DefaultLogixNGPreferences::SHOW_SYSTEM_USER_NAMES = "showSystemUserNames";
    /*public*/  /*static*/ /*final*/ QString DefaultLogixNGPreferences::ERROR_HANDLING_TYPE = "errorHandlingType";
    /*public*/  /*static*/ /*final*/ QString DefaultLogixNGPreferences::TREE_EDITOR_HIGHLIGHT_ROW = "treeEditorHighlightRow";


    /*public*/  DefaultLogixNGPreferences::DefaultLogixNGPreferences(QObject* parent)
     : PreferencesBean(ProfileManager::getDefault()->getActiveProfile(),parent)
    {
        //super(ProfileManager.getDefault().getActiveProfile());
//        System.out.format("LogixNG preferences%n");
        Preferences* sharedPreferences = ProfileUtils::getPreferences(
                PreferencesBean::getProfile(), this->getClass(), true);
        this->readPreferences(sharedPreferences);
    }

    /*private*/ void DefaultLogixNGPreferences::readPreferences(Preferences* sharedPreferences) {
        _startLogixNGOnLoad = sharedPreferences->getBoolean(START_LOGIXNG_ON_LOAD, _startLogixNGOnLoad);
        _installDebugger = sharedPreferences->getBoolean(INSTALL_DEBUGGER, _installDebugger);
        _showSystemUserNames = sharedPreferences->getBoolean(SHOW_SYSTEM_USER_NAMES, _showSystemUserNames);
        _errorHandlingType = ErrorHandlingType::valueOf(
                sharedPreferences->get(ERROR_HANDLING_TYPE, ErrorHandlingType::toString(_errorHandlingType)));
        _treeEditorHighlightRow = sharedPreferences->getBoolean(TREE_EDITOR_HIGHLIGHT_ROW, _treeEditorHighlightRow);

/*
        this->allowRemoteConfig = sharedPreferences.getbool(ALLOW_REMOTE_CONFIG, this->allowRemoteConfig);
        this->clickDelay = sharedPreferences.getInt(CLICK_DELAY, this->clickDelay);
        this->simple = sharedPreferences.getbool(SIMPLE, this->simple);
        this->railroadName = sharedPreferences.get(RAILROAD_NAME, this->railroadName);
        this->readonlyPower = sharedPreferences.getbool(READONLY_POWER, this->readonlyPower);
        this->refreshDelay = sharedPreferences.getInt(REFRESH_DELAY, this->refreshDelay);
        this->useAjax = sharedPreferences.getbool(USE_AJAX, this->useAjax);
        this->disableFrames = sharedPreferences.getbool(DISABLE_FRAME_SERVER, this->disableFrames);
        this->redirectFramesToPanels = sharedPreferences.getbool(REDIRECT_FRAMES, this->redirectFramesToPanels);
        try {
            Preferences frames = sharedPreferences.node(DISALLOWED_FRAMES);
            if (frames.keys().length != 0) {
                this->disallowedFrames.clear();
                for (String key : frames.keys()) { // throws BackingStoreException
                    String frame = frames.get(key, null);
                    if (frame != null && !frame.trim().isEmpty()) {
                        this->disallowedFrames.add(frame);
                    }
                }
            }
        } catch (BackingStoreException ex) {
            // this is expected if sharedPreferences have not been written previously,
            // so do nothing.
        }
        this->port = sharedPreferences.getInt(PORT, this->port);
        this->useZeroConf = sharedPreferences.getbool(USE_ZERO_CONF, this->useZeroConf);
*/
        setIsDirty(false);
    }

    //@Override
    /*public*/  bool DefaultLogixNGPreferences::compareValuesDifferent(LogixNGPreferences* prefs) {
        if (getStartLogixNGOnStartup() != prefs->getStartLogixNGOnStartup()) {
            return true;
        }
        if (getInstallDebugger() != prefs->getInstallDebugger()) {
            return true;
        }
        if (getShowSystemUserNames() != prefs->getShowSystemUserNames()) {
            return true;
        }
        if (getTreeEditorHighlightRow() != prefs->getTreeEditorHighlightRow()) {
            return true;
        }
        return (getErrorHandlingType() != prefs->getErrorHandlingType());
    }

    //@Override
    /*public*/  void DefaultLogixNGPreferences::apply(LogixNGPreferences* prefs) {
        setStartLogixNGOnStartup(prefs->getStartLogixNGOnStartup());
        setInstallDebugger(prefs->getInstallDebugger());
        setShowSystemUserNames(prefs->getShowSystemUserNames());
        this->setErrorHandlingType(prefs->getErrorHandlingType());
        setTreeEditorHighlightRow(prefs->getTreeEditorHighlightRow());
    }

    //@Override
    /*public*/  void DefaultLogixNGPreferences::save() {
        Preferences* sharedPreferences = ProfileUtils::getPreferences(this->getProfile(), this->getClass(), true);
        sharedPreferences->putBoolean(START_LOGIXNG_ON_LOAD, this->getStartLogixNGOnStartup());
        sharedPreferences->putBoolean(INSTALL_DEBUGGER, this->getInstallDebugger());
        sharedPreferences->putBoolean(SHOW_SYSTEM_USER_NAMES, this->getShowSystemUserNames());
        sharedPreferences->put(ERROR_HANDLING_TYPE, ErrorHandlingType::toString(this->getErrorHandlingType()));
        sharedPreferences->putBoolean(TREE_EDITOR_HIGHLIGHT_ROW, this->getTreeEditorHighlightRow());
    }

    //@Override
    /*public*/  void DefaultLogixNGPreferences::setStartLogixNGOnStartup(bool value) {
        _startLogixNGOnLoad = value;
        setIsDirty(true);
    }

    //@Override
    /*public*/  bool DefaultLogixNGPreferences::getStartLogixNGOnStartup() {
        return _startLogixNGOnLoad;
    }

    //@Override
    /*public*/  void DefaultLogixNGPreferences::setShowSystemUserNames(bool value) {
        _showSystemUserNames = value;
        setIsDirty(true);
    }

    //@Override
    /*public*/  bool DefaultLogixNGPreferences::getShowSystemUserNames() {
        return _showSystemUserNames;
    }

    //@Override
    /*public*/  void DefaultLogixNGPreferences::setInstallDebugger(bool value) {
        _installDebugger = value;
        setIsDirty(true);
    }

    //@Override
    /*public*/  bool DefaultLogixNGPreferences::getInstallDebugger() {
        return _installDebugger;
    }

    //@Override
    /*public*/  void DefaultLogixNGPreferences::setErrorHandlingType(ErrorHandlingType::TYPES type) {
        _errorHandlingType = type;
        setIsDirty(true);
    }

    //@Override
    /*public*/  ErrorHandlingType::TYPES DefaultLogixNGPreferences::getErrorHandlingType() {
        return _errorHandlingType;
    }

    //@Override
    /*public*/  void DefaultLogixNGPreferences::setTreeEditorHighlightRow(bool value) {
        _treeEditorHighlightRow = value;
        setIsDirty(true);
    }

    //@Override
    /*public*/  bool DefaultLogixNGPreferences::getTreeEditorHighlightRow() {
        return _treeEditorHighlightRow;
    }

//    /*private*/ /*final*/ static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LogixNGPreferences.class);
