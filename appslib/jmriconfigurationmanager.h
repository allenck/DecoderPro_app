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
 QT_DEPRECATED JmriConfigurationManager(QObject* parent = 0);
 ~JmriConfigurationManager() {}
 JmriConfigurationManager(const JmriConfigurationManager&) : ConfigXmlManager(){}
 /*public*/ void registerPref(QObject* o) override;
 /*public*/ void removePrefItems()  override;
 /*public*/ void registerConfig(QObject* o) override;
 /*public*/ void registerConfig(QObject* o, int x) override;
 /*public*/ void registerTool(QObject* o) override;
 /*public*/ void registerUser(QObject* o) override;
 /*public*/ void registerUserPrefs(QObject* o) override;
 /*public*/ void deregister(QObject* o) override;
 /*public*/ QObject* findInstance(QString c, int index) override;
 /*public*/ QList<QObject*> getInstanceList(QString c) override;
 /*public*/ bool storeAll(File* file)const override;
 /*public*/ void storePrefs() override;
 /*public*/ void storePrefs(File* file)  override;
 /*public*/ void storeUserPrefs(File* file) override;
 /*public*/ bool storeConfig(File* file) override;
 /*public*/ bool storeUser(File* file) override;
 /*public*/ bool load(File* file)  throw (JmriException) override;
 /*public*/ bool load( QUrl file)  throw (JmriConfigureXmlException);
 /*public*/ bool load(File* file, bool registerDeferred)  throw (JmriConfigureXmlException) override;
 /*public*/ bool load( QUrl file, bool registerDeferred)  throw (JmriConfigureXmlException) override;
 /*public*/ bool loadDeferred(File* file)  throw (JmriException) override;
 /*public*/ bool loadDeferred( QUrl file)  throw (JmriConfigureXmlException) override;
 /*public*/ QUrl find(QString filename) override;
 /*public*/ bool makeBackup(File* file)const override;
 /*public*/ QHash<PreferencesManager*, InitializationException*> getInitializationExceptions();
 /*public*/ void setValidate(Validate v) override;
 /*public*/ XmlFile::Validate getValidate() override;

private:
 /*private*/ void initializeProvider( PreferencesManager* provider, Profile* profile);
 static /*private*/ Logger* log;// = LoggerFactory.getLogger(JmriConfigurationManager.class);
 /*private*/ /*final*/ ConfigXmlManager* legacy;// = new ConfigXmlManager();
 /*private*/ /*final*/ QHash<PreferencesManager*, InitializationException*>* initializationExceptions;// = new HashMap<>();
 /*private*/ /*final*/ QList<PreferencesManager*>* initialized;// = new ArrayList<>();
 /*private*/ void handleConnectionError(QList<QString> *errors, QVariant list);

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
