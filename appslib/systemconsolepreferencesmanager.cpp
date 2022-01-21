#include "systemconsolepreferencesmanager.h"
#include "systemconsole.h"
#include "logger.h"
#include "preferences.h"
#include "profileutils.h"
#include <QSet>

SystemConsolePreferencesManager::SystemConsolePreferencesManager()
{
 setObjectName("SystemConsolePreferencesManager");
 // default settings
 scheme = 0; // Green on Black
 fontSize = 12;
 fontStyle = /*Font.PLAIN*/ QFont::Normal;
 fontFamily = "Monospaced";  //NOI18N
 wrapStyle = SystemConsole::WRAP_STYLE_WORD;

 initialized = false;
 log = new Logger("SystemConsolePreferencesManager");

}
/**
 * Manage preferences for the {@link apps.SystemConsole}.
 *
 * @author Randall Wood
 */
///*public*/ class SystemConsolePreferencesManager extends Bean implements PreferencesManager {

/*public*/ /*static*/ /*final*/ QString SystemConsolePreferencesManager::SCHEME = "scheme";
/*public*/ /*static*/ /*final*/ QString SystemConsolePreferencesManager::FONT_SIZE = "fontSize";
/*public*/ /*static*/ /*final*/ QString SystemConsolePreferencesManager::FONT_STYLE = "fontStyle";
/*public*/ /*static*/ /*final*/ QString SystemConsolePreferencesManager::FONT_FAMILY = "fontFamily";
/*public*/ /*static*/ /*final*/ QString SystemConsolePreferencesManager::WRAP_STYLE = "wrapStyle";


/*
 * Unlike most PreferencesProviders, the SystemConsole preferences should be
 * per-application instead of per-profile.
 */

//@Override
/*public*/ void SystemConsolePreferencesManager::initialize(Profile* profile) throw (InitializationException)
{
 if (!this->initialized)
 {
  Preferences* preferences = ProfileUtils::getPreferences(profile, "apps/systemconsole/SystemConsolePreferencesManager", true);
  this->setFontFamily(preferences->get(FONT_FAMILY, this->getFontFamily()));
  this->setFontSize(preferences->getInt(FONT_SIZE, this->getFontSize()));
  this->setFontStyle(preferences->getInt(FONT_STYLE, this->getFontStyle()));
  this->setScheme(preferences->getInt(SCHEME, this->getScheme()));
  this->setWrapStyle(preferences->getInt(WRAP_STYLE, this->getWrapStyle()));
  this->initialized = true;
 }
}

//@Override
/*public*/ void SystemConsolePreferencesManager::savePreferences(Profile* profile) {
    Preferences* preferences = ProfileUtils::getPreferences(profile, "apps.systemconsole.SystemConsolePreferencesManager", true);
    preferences->put(FONT_FAMILY, this->getFontFamily());
    preferences->putInt(FONT_SIZE, this->getFontSize());
    preferences->putInt(FONT_STYLE, this->getFontStyle());
    preferences->putInt(SCHEME, this->getScheme());
    preferences->putInt(WRAP_STYLE, this->getWrapStyle());
    try
    {
        preferences->sync();
    } catch (BackingStoreException* ex) {
        log->error("Unable to save preferences->", ex);
    }
}

//@Override
/*public*/ bool SystemConsolePreferencesManager::isInitialized(Profile* profile) {
    return this->initialized && this->exceptions.isEmpty();
}

//@Override
/*public*/ QSet<QString>* /*Iterable<Class<? extends PreferencesManager>> */SystemConsolePreferencesManager::getRequires() {
    return new QSet<QString>();
}

//@Override
/*public*/ QSet<QString>* /*Iterable<Class<?>>*/ SystemConsolePreferencesManager::getProvides() {
    //Set<Class<?>> provides = new HashSet<>();
    QSet<QString>* provides = new QSet<QString>();
    provides->insert(this->metaObject()->className());
    return provides;
}

/**
 * @return the scheme
 */
/*public*/ int SystemConsolePreferencesManager::getScheme() {
    return scheme;
}

/**
 * @param scheme the scheme to set
 */
/*public*/ void SystemConsolePreferencesManager::setScheme(int scheme) {
    int oldScheme = this->scheme;
    this->scheme = scheme;
    this->firePropertyChange(SCHEME, oldScheme, scheme);
    SystemConsole::getInstance()->setScheme(scheme);
}

/**
 * @return the fontSize
 */
/*public*/ int SystemConsolePreferencesManager::getFontSize() {
    return fontSize;
}

/**
 * Sets the fontSize.
 *
 * If the parameter is less than 6, the fontSize is set to 6. If the
 * parameter is greater than 24, the fontSize is set to 24.
 *
 * @param fontSize the fontSize to set
 */
/*public*/ void SystemConsolePreferencesManager::setFontSize(int fontSize) {
    int oldFontSize = this->fontSize;
    this->fontSize = fontSize < 6 ? 6 : fontSize > 24 ? 24 : fontSize;
    if (this->fontSize != oldFontSize) {
        this->firePropertyChange(FONT_SIZE, oldFontSize, this->fontSize);
        SystemConsole::getInstance()->setFontSize(this->fontSize);
    }
}

/**
 * @return the fontStyle
 */
/*public*/ int SystemConsolePreferencesManager::getFontStyle() {
    return fontStyle;
}

/**
 * @param fontStyle one of
 *                  {@link java.awt.Font#BOLD}, {@link java.awt.Font#ITALIC},
 *                  or {@link java.awt.Font#PLAIN}.
 */
/*public*/ void SystemConsolePreferencesManager::setFontStyle(int fontStyle) {
    if (fontStyle == QFont::Bold || fontStyle == QFont::StyleItalic || fontStyle == QFont::StyleNormal || fontStyle == (QFont::Bold | QFont::StyleItalic)) {
        int oldFontStyle = this->fontStyle;
        this->fontStyle = fontStyle;
        if (this->fontStyle != oldFontStyle) {
            this->firePropertyChange(FONT_STYLE, oldFontStyle, fontStyle);
            SystemConsole::getInstance()->setFontStyle(this->fontStyle);
        }
    }
}

/**
 * @return the fontFamily
 */
/*public*/ QString SystemConsolePreferencesManager::getFontFamily() {
    return fontFamily;
}

/**
 * @param fontFamily the fontFamily to set
 */
/*public*/ void SystemConsolePreferencesManager::setFontFamily(QString fontFamily) {
#if 0
    if (FontComboUtil::getFonts(FontComboUtil.MONOSPACED).contains(fontFamily)) {
        String oldFontFamily = this->fontFamily;
        this->fontFamily = fontFamily;
        this->firePropertyChange(FONT_FAMILY, oldFontFamily, fontFamily);
        SystemConsole.getInstance().setFontFamily(this->getFontFamily());
    } else {
        log->warn("Incompatible console font \"{}\" - using \"{}\"", fontFamily, this->getFontFamily());
    }
#endif
}

/**
 * @return the wrapStyle
 */
/*public*/ int SystemConsolePreferencesManager::getWrapStyle() {
    return wrapStyle;
}

/**
 * @param wrapStyle One of
 *                  {@link apps.SystemConsole#WRAP_STYLE_LINE}, {@link apps.SystemConsole#WRAP_STYLE_NONE},
 *                  or {@link apps.SystemConsole#WRAP_STYLE_WORD}.
 */
/*public*/ void SystemConsolePreferencesManager::setWrapStyle(int wrapStyle) {
    if (wrapStyle == SystemConsole::WRAP_STYLE_LINE
            || wrapStyle == SystemConsole::WRAP_STYLE_NONE
            || wrapStyle == SystemConsole::WRAP_STYLE_WORD) {
        int oldWrapStyle = this->wrapStyle;
        this->wrapStyle = wrapStyle;
        this->firePropertyChange(WRAP_STYLE, oldWrapStyle, wrapStyle);
        SystemConsole::getInstance()->setWrapStyle(this->getWrapStyle());
    }
}

//@Override
/*public*/ bool SystemConsolePreferencesManager::isInitializedWithExceptions(Profile* profile) {
    return this->initialized && !this->exceptions.isEmpty();
}

//@Override
/*public*/ QList<Exception *> SystemConsolePreferencesManager::getInitializationExceptions(Profile* profile) {
    return QList<Exception*>(this->exceptions);
}
