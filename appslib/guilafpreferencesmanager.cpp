#include "guilafpreferencesmanager.h"
#include "exceptions.h"
#include "preferences.h"
#include "profileutils.h"
#include <QSet>
#include "logger.h"
#include "propertychangesupport.h"
#include "language.h"
#include "exceptions.h"

GuiLafPreferencesManager::GuiLafPreferencesManager()
{
 log = new Logger("GuiLafPreferencesManager");
 setObjectName("GuiLafPreferencesManager");
 // preferences with default values
 locale = QLocale();
 fontSize = 0;
 defaultFontSize = 0;
 nonStandardMouseEvent = false;
 verticalToolBar = false;
 lookAndFeel = "na"; //UIManager.getLookAndFeel().getClass().getName();
 toolTipDismissDelay = 20; //ToolTipManager.sharedInstance().getDismissDelay();
 dirty = false;
 restartRequired = false;
 /*
  * Unlike most PreferencesProviders, the GUI Look & Feel preferences should
  * be per-application instead of per-profile.
  */
 initialized = false;
 exceptions = new QList<Exception*>();
}
/**
 *
 * @author Randall Wood (C) 2015
 */
// /*public*/ class GuiLafPreferencesManager extends Bean implements PreferencesManager, InstanceManagerAutoDefault {

/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::FONT_SIZE = "fontSize";
/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::LOCALE = "locale";
/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::LOOK_AND_FEEL = "lookAndFeel";
/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::NONSTANDARD_MOUSE_EVENT = "nonstandardMouseEvent";
/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::GRAPHIC_TABLE_STATE = "graphicTableState";
// Classic OBlock editor or tabbed tables
/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::OBLOCK_EDIT_TABBED = "oblockEditTabbed";/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::VERTICAL_TOOLBAR = "verticalToolBar";
/*public*/ /*final*/ /*static*/ QString GuiLafPreferencesManager::SHOW_TOOL_TIP_TIME = "showToolTipDismissDelay";
/*public*/ /*final*/ /*static*/ QString GuiLafPreferencesManager::EDITOR_USE_OLD_LOC_SIZE= "editorUseOldLocSize";

/**
 * Smallest font size a user can set the font size to other than zero
 * ({@value}). A font size of 0 indicates that the system default font size
 * will be used.
 *
 * @see apps.GuiLafConfigPane#MIN_DISPLAYED_FONT_SIZE
 */
/*public*/ /*static*/ /*final*/ int GuiLafPreferencesManager::MIN_FONT_SIZE = 9;
/**
 * Largest font size a user can set the font size to ({@value}).
 *
 * @see apps.GuiLafConfigPane#MAX_DISPLAYED_FONT_SIZE
 */
/*public*/ /*static*/ /*final*/ int GuiLafPreferencesManager::MAX_FONT_SIZE = 36;
/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::PROP_DIRTY = "dirty";
/*public*/ /*static*/ /*final*/ QString GuiLafPreferencesManager::PROP_RESTARTREQUIRED = "restartRequired";

//@Override
/*public*/ void GuiLafPreferencesManager::initialize(Profile* profile) throw (InitializationException)
{
    if (!this->initialized) {
        Preferences* preferences = ProfileUtils::getPreferences(profile, "apps.gui.GuiLafPreferencesManager", true);
//        this->setLocale(Locale.forLanguageTag(preferences->get(LOCALE, this->getLocale().toLanguageTag())));
        this->setLookAndFeel(preferences->get(LOOK_AND_FEEL, this->getLookAndFeel()));
        this->setDefaultFontSize(); // before we change anything
        this->setFontSize(preferences->getInt(FONT_SIZE, this->getDefaultFontSize()));
        if (this->getFontSize() == 0) {
            this->setFontSize(this->getDefaultFontSize());
        }
        this->setNonStandardMouseEvent(preferences->getBoolean(NONSTANDARD_MOUSE_EVENT, this->isNonStandardMouseEvent()));
        this->setGraphicTableState(preferences->getBoolean(GRAPHIC_TABLE_STATE, this->isGraphicTableState()));
        this->setOblockEditTabbed(preferences->getBoolean(OBLOCK_EDIT_TABBED, this->isOblockEditTabbed()));
        this->setEditorUseOldLocSize(preferences->getBoolean(EDITOR_USE_OLD_LOC_SIZE, this->isEditorUseOldLocSize()));
        this->setToolTipDismissDelay(preferences->getInt(SHOW_TOOL_TIP_TIME, this->getToolTipDismissDelay()));
//        Locale.setDefault(this->getLocale());

        this->applyLookAndFeel();
        this->applyFontSize();
//        SwingSettings.setNonStandardMouseEvent(this->isNonStandardMouseEvent());
        this->setDirty(false);
        this->setRestartRequired(false);
        this->initialized = true;
    }
}

//@Override
/*public*/ bool GuiLafPreferencesManager::isInitialized(Profile* /*profile*/) {
    return this->initialized && this->exceptions->isEmpty();
}

//@Override
/*public*/ /*Iterable<Class<? extends PreferencesManager>> */ QSet<QString>* GuiLafPreferencesManager::getRequires() {
    return new QSet<QString>();
}

//@Override
/*public*/ /*Iterable<Class<?>>*/ QSet<QString>* GuiLafPreferencesManager::getProvides() {
    //Set<Class<?>> provides = new HashSet<>();
 QSet<QString>* provides = new QSet<QString>();
    provides->insert(this->metaObject()->className());
    return provides;
}

//@Override
/*public*/ void GuiLafPreferencesManager::savePreferences(Profile* profile)
{
 Preferences* preferences = ProfileUtils::getPreferences(profile, "apps.gui.GuiLafPreferencesManager", true);
//    preferences->put(LOCALE, /*this->getLocale().toLanguageTag()*/this->getLocale().language().});
 preferences->put(LOOK_AND_FEEL, this->getLookAndFeel());
 int temp = this->getFontSize();
 if (temp == this->getDefaultFontSize()) {
     temp = 0;
 }
 if (temp != preferences->getInt(FONT_SIZE, -1)) {
     preferences->putInt(FONT_SIZE, temp);
 }
 preferences->putBoolean(NONSTANDARD_MOUSE_EVENT, this->isNonStandardMouseEvent());
 preferences->putBoolean(GRAPHIC_TABLE_STATE, this->isGraphicTableState()); // use graphic icons in bean table state column
 preferences->putBoolean(OBLOCK_EDIT_TABBED, this->isOblockEditTabbed());
 preferences->putBoolean(EDITOR_USE_OLD_LOC_SIZE, this->isEditorUseOldLocSize());
 preferences->putInt(SHOW_TOOL_TIP_TIME, this->getToolTipDismissDelay());
 try {
     preferences->sync();
 } catch (BackingStoreException ex) {
     log->error("Unable to save preferences->", ex);
 }
 this->setDirty(false);
}

/**
 * @return the locale
 */
/*public*/ QLocale GuiLafPreferencesManager::getLocale() {
    return locale;
}

/**
 * @param locale the locale to set
 */
/*public*/ void GuiLafPreferencesManager::setLocale(QLocale locale) {
    QLocale oldLocale = this->locale;
    this->locale = locale;
    this->setDirty(true);
    this->setRestartRequired(true);
    firePropertyChange(LOCALE, oldLocale, locale);
}

/**
 * @return the currently selected font size
 */
/*public*/ int GuiLafPreferencesManager::getFontSize() {
    return fontSize;
}

/**
 * Sets a new font size
 *
 * @param newFontSize the new font size to set
 */
/*public*/ void GuiLafPreferencesManager::setFontSize(int newFontSize) {
    int oldFontSize = this->fontSize;
    this->fontSize = (newFontSize == 0) ? 0 : ((newFontSize < MIN_FONT_SIZE) ? MIN_FONT_SIZE : ((newFontSize > MAX_FONT_SIZE) ? MAX_FONT_SIZE : newFontSize));
    if (this->fontSize != oldFontSize) {
        firePropertyChange(FONT_SIZE, oldFontSize, this->fontSize);
    }
    this->setDirty(true);
    this->setRestartRequired(true);
}

/**
 * @return the current {@literal Look & Feel} default font size
 */
/*public*/ int GuiLafPreferencesManager::getDefaultFontSize() {
    return defaultFontSize;
}

/**
 * Called to load the current {@literal Look & Feel} default font size,
 * based on looking up the "List.font" size
 * <br><br>
 * The value can be can be read by calling {@link #getDefaultFontSize()}
 */
/*public*/ void GuiLafPreferencesManager::setDefaultFontSize()
{
#if 0
    java.util.Enumeration<Object> keys = UIManager.getDefaults().keys();
    while (keys.hasMoreElements()) {
        Object key = keys.nextElement();
        Object value = UIManager.get(key);

        if (value instanceof javax.swing.plaf.FontUIResource && key.toString().equals("List.font")) {
            Font f = UIManager.getFont(key);
            log->debug("Key:" + key.toString() + " Font: " + f.getName() + " size: " + f.getSize());
            defaultFontSize = f.getSize();
            return;
        }
    }
#endif
    defaultFontSize = 11;   // couldn't find the default return a reasonable font size
}

/**
 * Logs LAF fonts at the TRACE level.
 */
/*private*/ void GuiLafPreferencesManager::logAllFonts()
{
#if 0
    // avoid any activity if logging at this level is disabled to avoid
    // the unnessesary overhead of getting the fonts
    if (log->isTraceEnabled()) {
        log->trace("******** LAF={}", UIManager.getLookAndFeel().getClass().getName());
        java.util.Enumeration<Object> keys = UIManager.getDefaults().keys();
        while (keys.hasMoreElements()) {
            Object key = keys.nextElement();
            Object value = UIManager.get(key);
            if (value instanceof javax.swing.plaf.FontUIResource || value instanceof java.awt.Font || key.toString().endsWith(".font")) {
                Font f = UIManager.getFont(key);
                log->trace("Class={}; Key: {} Font: {} size: {}", value.getClass().getName(), key, f.getName(), f.getSize());
            }
        }
    }
#endif
}

/**
 * Sets the time a tooltip is displayed before it goes away.
 *
 * Note that this preference takes effect immediately.
 *
 * @param time the delay in seconds.
 */
/*public*/ void GuiLafPreferencesManager::setToolTipDismissDelay(int time) {
    this->toolTipDismissDelay = time;
#if 0
    ToolTipManager.sharedInstance().setDismissDelay(time);
#endif
    this->setDirty(true);
}

/**
 *
 * @return the int
 */
/*public*/ int GuiLafPreferencesManager::getToolTipDismissDelay() {
    return this->toolTipDismissDelay;
}

/**
 * @return the nonStandardMouseEvent
 */
/*public*/ bool GuiLafPreferencesManager::isNonStandardMouseEvent() {
    return nonStandardMouseEvent;
}

/**
 * @param nonStandardMouseEvent the nonStandardMouseEvent to set
 */
/*public*/ void GuiLafPreferencesManager::setNonStandardMouseEvent(bool nonStandardMouseEvent) {
    bool oldNonStandardMouseEvent = this->nonStandardMouseEvent;
    this->nonStandardMouseEvent = nonStandardMouseEvent;
    this->setDirty(true);
    this->setRestartRequired(true);
    firePropertyChange(NONSTANDARD_MOUSE_EVENT, oldNonStandardMouseEvent, nonStandardMouseEvent);
}

/**
 * @return the graphicTableState
 */
/*public*/ bool GuiLafPreferencesManager::isGraphicTableState() {
    return graphicTableState;
}

/**
 * @param graphicTableState the graphicTableState to set
 */
/*public*/ void GuiLafPreferencesManager::setGraphicTableState(bool graphicTableState) {
    bool oldGraphicTableState = this->graphicTableState;
    this->graphicTableState = graphicTableState;
    this->setDirty(true);
    this->setRestartRequired(true);
    firePropertyChange(GRAPHIC_TABLE_STATE, oldGraphicTableState, graphicTableState);
}

/**
* @return the graphicTableState
*/
/*public*/ bool GuiLafPreferencesManager::isOblockEditTabbed() {
   return oblockEditTabbed;
}

/**
* @param tabbed the Editor interface to set (fasle  = desktop)
*/
/*public*/ void GuiLafPreferencesManager::setOblockEditTabbed(bool tabbed) {
   bool oldOblockTabbed = this->oblockEditTabbed;
   this->oblockEditTabbed = tabbed;
   firePropertyChange(OBLOCK_EDIT_TABBED, oldOblockTabbed, tabbed);
}
/**
 * @return the editorUseOldLocSize value
 */
/*public*/ bool GuiLafPreferencesManager::isEditorUseOldLocSize() {
    return editorUseOldLocSize;
}

/**
 * @param editorUseOldLocSize the editorUseOldLocSize value to set
 */
/*public*/ void GuiLafPreferencesManager::setEditorUseOldLocSize(bool editorUseOldLocSize) {
    bool oldEditorUseOldLocSize = this->editorUseOldLocSize;
    this->editorUseOldLocSize = editorUseOldLocSize;
    this->setDirty(true);
    this->setRestartRequired(false);
    firePropertyChange(EDITOR_USE_OLD_LOC_SIZE, oldEditorUseOldLocSize, editorUseOldLocSize);
}

/**
 * @return the lookAndFeel
 */
/*public*/ QString GuiLafPreferencesManager::getLookAndFeel() {
    return lookAndFeel;
}

/**
 * @param lookAndFeel the lookAndFeel to set
 */
/*public*/ void GuiLafPreferencesManager::setLookAndFeel(QString lookAndFeel) {
    QString oldLookAndFeel = this->lookAndFeel;
    this->lookAndFeel = lookAndFeel;
    this->setDirty(true);
    this->setRestartRequired(true);
    firePropertyChange(LOOK_AND_FEEL, oldLookAndFeel, lookAndFeel);
}

/**
 * Apply the existing look and feel.
 */
/*public*/ void GuiLafPreferencesManager::applyLookAndFeel() {
    QString lafClassName = "";
#if 0
    for (LookAndFeelInfo LAF : UIManager.getInstalledLookAndFeels()) {
        if (LAF.getName().equals(this->lookAndFeel)) {
            lafClassName = LAF.getClassName();
        }
    }
    log->debug("Look and feel selection \"{}\" ({})", this->lookAndFeel, lafClassName);
    if (lafClassName != null) {
        if (!lafClassName.equals(UIManager.getLookAndFeel().getClass().getName())) {
            log->debug("Apply look and feel \"{}\" ({})", this->lookAndFeel, lafClassName);
            try {
                UIManager.setLookAndFeel(lafClassName);
            } catch (ClassNotFoundException ex) {
                log->error("Could not find look and feel \"{}\".", this->lookAndFeel);
            } catch (IllegalAccessException | InstantiationException ex) {
                log->error("Could not load look and feel \"{}\".", this->lookAndFeel);
            } catch (UnsupportedLookAndFeelException ex) {
                log->error("Look and feel \"{}\" is not supported on this platform.", this->lookAndFeel);
            }
        } else {
            log->debug("Not updating look and feel {} matching existing look and feel" + lafClassName);
        }
    }
#endif
}

/**
 * Applies a new calculated font size to all found fonts.
 * <br><br>
 * Calls {@link #getCalcFontSize(int) getCalcFontSize} to calculate new size
 * for each.
 */
/*private*/ void GuiLafPreferencesManager::applyFontSize() {
    if (log->isTraceEnabled()) {
        logAllFonts();
    }
#if 0
    if (this->getFontSize() != this->getDefaultFontSize()) {
//            UIManager.getDefaults().keySet().stream().forEach((key) -> {
        Enumeration<Object> keys = UIManager.getDefaults().keys();
        while (keys.hasMoreElements()) {
            Object key = keys.nextElement();
            Object value = UIManager.get(key);
            if (value instanceof javax.swing.plaf.FontUIResource || value instanceof java.awt.Font || key.toString().endsWith(".font")) {
                UIManager.put(key, UIManager.getFont(key).deriveFont(((Font) value).getStyle(), getCalcFontSize(((Font) value).getSize())));
            }
        }
        if (log->isTraceEnabled()) {
            logAllFonts();
        }
    }
#endif
}

/**
 * @return a new calculated font size based on difference between default
 *         size and selected size
 *
 * @param oldSize the old font size
 */
/*private*/ int GuiLafPreferencesManager::getCalcFontSize(int oldSize) {
    return oldSize + (this->getFontSize() - this->getDefaultFontSize());
}

/**
 * Check if preferences need to be saved.
 *
 * @return true if preferences need to be saved
 */
/*public*/ bool GuiLafPreferencesManager::isDirty() {
    return dirty;
}

/**
 * Set dirty state.
 *
 * @param dirty true if preferences need to be saved
 */
/*private*/ void GuiLafPreferencesManager::setDirty(bool dirty) {
    bool oldDirty = this->dirty;
    this->dirty = dirty;
    if (oldDirty != dirty) {
        propertyChangeSupport->firePropertyChange(PROP_DIRTY, oldDirty, dirty);
    }
}

/**
 * Check if application needs to restart to apply preferences->
 *
 * @return true if preferences are only applied on application start
 */
/*public*/ bool GuiLafPreferencesManager::isRestartRequired() {
    return restartRequired;
}

/**
 * Set restart required state.
 *
 * @param restartRequired true if application needs to restart to apply
 *                        preferences
 */
/*private*/ void GuiLafPreferencesManager::setRestartRequired(bool restartRequired) {
    bool oldRestartRequired = this->restartRequired;
    this->restartRequired = restartRequired;
    if (oldRestartRequired != restartRequired) {
        propertyChangeSupport->firePropertyChange(PROP_RESTARTREQUIRED, oldRestartRequired, restartRequired);
    }
}

//@Override
/*public*/ bool GuiLafPreferencesManager::isInitializedWithExceptions(Profile* /*profile*/) {
    return this->initialized && !this->exceptions->isEmpty();
}

//@Override
/*public*/ QList<Exception*>* GuiLafPreferencesManager::getInitializationExceptions(Profile* /*profile*/) {
    return new QList<Exception*>(*this->exceptions);
}
