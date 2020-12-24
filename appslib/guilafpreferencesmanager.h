#ifndef GUILAFPREFERENCESANAGER_H
#define GUILAFPREFERENCESANAGER_H
#include "preferencesmanager.h"
#include <QLocale>

class Exception ;
class InitializationException;
class Logger;
class GuiLafPreferencesManager : public PreferencesManager
{
public:
 Q_INVOKABLE GuiLafPreferencesManager();
 ~GuiLafPreferencesManager() {}
 GuiLafPreferencesManager(const GuiLafPreferencesManager&) : PreferencesManager() {}
 /*public*/ static /*final*/ QString FONT_SIZE;// = "fontSize";
 /*public*/ static /*final*/ QString LOCALE;// = "locale";
 /*public*/ static /*final*/ QString LOOK_AND_FEEL;// = "lookAndFeel";
 /*public*/ static /*final*/ QString NONSTANDARD_MOUSE_EVENT;// = "nonstandardMouseEvent";
 /*public*/ static /*final*/ QString GRAPHIC_TABLE_STATE;// = "graphicTableState";
 // Classic OBlock editor or tabbed tables
 /*public*/ static /*final*/ QString OBLOCK_EDIT_TABBED;// = "oblockEditTabbed";
 /*public*/ static /*final*/ QString VERTICAL_TOOLBAR;// = "verticalToolBar";
 /*public*/ /*final*/ static QString SHOW_TOOL_TIP_TIME;// = "showToolTipDismissDelay";
 /*public*/ /*final*/ static QString EDITOR_USE_OLD_LOC_SIZE;//= "editorUseOldLocSize";
 /*public*/ static /*final*/ int MIN_FONT_SIZE;// = 9;
 /*public*/ static /*final*/ int MAX_FONT_SIZE;// = 36;
 /*public*/ static /*final*/ QString PROP_DIRTY;// = "dirty";
 /*public*/ static /*final*/ QString PROP_RESTARTREQUIRED;// = "restartRequired";
 /*public*/ void initialize(Profile* profile)throw (InitializationException);
 /*public*/ bool isInitialized(Profile* profile);
 /*public*/ /*Iterable<Class<? extends PreferencesManager>> */ QSet<QString>* getRequires();
 /*public*/ /*Iterable<Class<?>>*/ QSet<QString>* getProvides();
 /*public*/ void savePreferences(Profile* profile);
 /*public*/ QLocale getLocale();
 /*public*/ void setLocale(QLocale locale);
 /*public*/ int getFontSize();
 /*public*/ void setFontSize(int newFontSize);
 /*public*/ int getDefaultFontSize();
 /*public*/ void setDefaultFontSize();
 /*private*/ void logAllFonts();
 /*public*/ void setToolTipDismissDelay(int time);
 /*public*/ int getToolTipDismissDelay();
 /*public*/ bool isNonStandardMouseEvent();
 /*public*/ void setNonStandardMouseEvent(bool nonStandardMouseEvent);
 /*public*/ QString getLookAndFeel();
 /*public*/ void setLookAndFeel(QString lookAndFeel);
 /*public*/ void applyLookAndFeel();
 /*public*/ bool isRestartRequired();
 /*public*/ bool isInitializedWithExceptions(Profile* profile);
 /*public*/ QList<Exception*>* getInitializationExceptions(Profile* profile);
 /*public*/ bool isDirty();
 /*public*/ bool isAssignableFromType() {return true;}
 /*public*/ bool isGraphicTableState();
 /*public*/ void setGraphicTableState(bool graphicTableState);
 /*public*/ bool isEditorUseOldLocSize();
 /*public*/ void setEditorUseOldLocSize(bool editorUseOldLocSize);
 /*public*/ bool isOblockEditTabbed();
 /*public*/ void setOblockEditTabbed(bool tabbed);

private:
 Logger* log;
 // preferences with default values
 /*private*/ QLocale locale;// = Locale.getDefault();
 /*private*/ int fontSize;// = 0;
 /*private*/ int defaultFontSize;// = 0;
 /*private*/ bool nonStandardMouseEvent;// = false;
 /*private*/ bool verticalToolBar;// = false;
 /*private*/ bool graphicTableState = false;
 /*private*/ bool oblockEditTabbed = false;
 /*private*/ bool editorUseOldLocSize = false;
 /*private*/ QString lookAndFeel;// = UIManager.getLookAndFeel().getClass().getName();
 /*private*/ int toolTipDismissDelay;// = ToolTipManager.sharedInstance().getDismissDelay();
 /*private*/ bool dirty;// = false;
 /*private*/ bool restartRequired;// = false;

 /*
  * Unlike most PreferencesProviders, the GUI Look & Feel preferences should
  * be per-application instead of per-profile.
  */
 /*private*/ bool initialized = false;
 /*private*/ /*final*/ QList<Exception*>* exceptions;// = new ArrayList<>();
 /*private*/ void applyFontSize();
 /*private*/ int getCalcFontSize(int oldSize);
 /*private*/ void setDirty(bool dirty);
 /*private*/ void setRestartRequired(bool restartRequired);
 Q_PROPERTY(MEMBER InstanceManagerAutoDefault )
};
Q_DECLARE_METATYPE(GuiLafPreferencesManager)
#endif // GUILAFPREFERENCESANAGER_H
