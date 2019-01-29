#ifndef JMRICONFIGURATIONMANAGER_H
#define JMRICONFIGURATIONMANAGER_H
#include "configxmlmanager.h"
#include "xmlfile.h"
#include "jdialog.h"

class Profile;
class InitializationException;
//class ConfigXmlManager;
class PreferencesManager;
class JmriConfigurationManager : public ConfigXmlManager
{
 Q_OBJECT
public:
 JmriConfigurationManager(QObject* parent = 0);
 ~JmriConfigurationManager() {}
 JmriConfigurationManager(const JmriConfigurationManager&) : ConfigXmlManager(){}
 /*public*/ void registerPref(QObject* o);
 /*public*/ void removePrefItems() ;
 /*public*/ void registerConfig(QObject* o);
 /*public*/ void registerConfig(QObject* o, int x);
 /*public*/ void registerTool(QObject* o);
 /*public*/ void registerUser(QObject* o);
 /*public*/ void registerUserPrefs(QObject* o);
 /*public*/ void deregister(QObject* o);
 /*public*/ QObject* findInstance(QString c, int index);
 /*public*/ QList<QObject*> getInstanceList(QString c);
 /*public*/ bool storeAll(File* file);
 /*public*/ void storePrefs();
 /*public*/ void storePrefs(File* file) ;
 /*public*/ void storeUserPrefs(File* file);
 /*public*/ bool storeConfig(File* file);
 /*public*/ bool storeUser(File* file);
 /*public*/ bool load(File* file)  throw (JmriException);
 /*public*/ bool load( QUrl file)  throw (JmriException);
 /*public*/ bool load(File* file, bool registerDeferred)  throw (JmriException);
 /*public*/ bool load( QUrl file, bool registerDeferred)  throw (JmriException);
 /*public*/ bool loadDeferred(File* file)  throw (JmriException);
 /*public*/ bool loadDeferred( QUrl file)  throw (JmriException);
 /*public*/ QUrl find(QString filename);
 /*public*/ bool makeBackup(File* file);
 /*public*/ QHash<PreferencesManager*, InitializationException*> getInitializationExceptions();
 /*public*/ void setValidate(Validate v);
 /*public*/ XmlFile::Validate getValidate();

private:
 /*private*/ void initializeProvider( PreferencesManager* provider, Profile* profile);
 static /*private*/ Logger* log;// = LoggerFactory.getLogger(JmriConfigurationManager.class);
 /*private*/ /*final*/ ConfigXmlManager* legacy;// = new ConfigXmlManager();
 /*private*/ /*final*/ QHash<PreferencesManager*, InitializationException*>* initializationExceptions;// = new HashMap<>();
 /*private*/ /*final*/ QList<PreferencesManager*>* initialized;// = new ArrayList<>();

};

/*private*/ /*static*/ /*final*/ class ErrorDialog : public JDialog {
 Q_OBJECT

public:
    enum Result {
        EXIT_PROGRAM,
        RESTART_PROGRAM,
        NEW_PROFILE,
        EDIT_CONNECTIONS,
    };
    Result result;// = Result.EXIT_PROGRAM;
    ErrorDialog(QStringList list);

public slots:
    void onExitProgram();
    void onRestartProgram();
    void onNewProfile();
    void onEditConnections();

};

Q_DECLARE_METATYPE(JmriConfigurationManager)
#endif // JMRICONFIGURATIONMANAGER_H
