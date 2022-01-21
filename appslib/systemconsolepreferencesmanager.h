#ifndef SYSTEMCONSOLEPREFERENCESMANAGER_H
#define SYSTEMCONSOLEPREFERENCESMANAGER_H
#include "preferencesmanager.h"
#include "bean.h"

class Exception;
class Logger;
class InitializationException;
class SystemConsolePreferencesManager : public Bean, public PreferencesManager
{
 Q_OBJECT
  Q_INTERFACES(PreferencesManager)
public:
 Q_INVOKABLE SystemConsolePreferencesManager();
 ~SystemConsolePreferencesManager() {}
 SystemConsolePreferencesManager(const SystemConsolePreferencesManager&) : PreferencesManager() {}
 /*public*/ static /*final*/ QString SCHEME;// = "scheme";
 /*public*/ static /*final*/ QString FONT_SIZE;// = "fontSize";
 /*public*/ static /*final*/ QString FONT_STYLE;// = "fontStyle";
 /*public*/ static /*final*/ QString FONT_FAMILY;// = "fontFamily";
 /*public*/ static /*final*/ QString WRAP_STYLE;// = "wrapStyle";
 /*public*/ void initialize(Profile* profile)throw (InitializationException);
 /*public*/ void savePreferences(Profile* profile);
 /*public*/ bool isInitialized(Profile* profile);
 /*public*/ QSet<QString>* /*Iterable<Class<? extends PreferencesManager>> */getRequires();
 /*public*/ QSet<QString>* /*Iterable<Class<?>>*/ getProvides();
 /*public*/ int getScheme();
 /*public*/ void setScheme(int scheme) ;
 /*public*/ int getFontSize();
 /*public*/ void setFontSize(int fontSize);
 /*public*/ int getFontStyle();
 /*public*/ void setFontStyle(int fontStyle);
 /*public*/ QString getFontFamily();
 /*public*/ void setFontFamily(QString fontFamily);
 /*public*/ int getWrapStyle() ;
 /*public*/ void setWrapStyle(int wrapStyle);
 /*public*/ bool isInitializedWithExceptions(Profile* profile);
 /*public*/ QList<Exception*> getInitializationExceptions(Profile* profile);

 QObject* self() override {return (QObject*)this;}

private:
 // default settings
 /*private*/ int scheme;// = 0; // Green on Black
 /*private*/ int fontSize;// = 12;
 /*private*/ int fontStyle;// = Font.PLAIN;
 /*private*/ QString fontFamily;// = "Monospaced";  //NOI18N
 /*private*/ int wrapStyle;// = SystemConsole::WRAP_STYLE_WORD;
 /*private*/ bool initialized;// = false;
 /*private*/ /*final*/ QList<Exception*> exceptions = QList<Exception*>();
 /*private*/ /*static*/ /*final*/ Logger* log;// = LoggerFactory.getLogger(SystemConsolePreferencesManager.class);

};
Q_DECLARE_METATYPE(SystemConsolePreferencesManager)
#endif // SYSTEMCONSOLEPREFERENCESMANAGER_H
