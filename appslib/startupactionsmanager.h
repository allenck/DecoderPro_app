#ifndef STARTUPACTIONSMANAGER_H
#define STARTUPACTIONSMANAGER_H
#include "abstractpreferencesmanager.h"
#include "class.h"

class Logger;
class StartupModel;
class StartupModelFactory;
class StartupActionsManager : public AbstractPreferencesManager
{
 Q_OBJECT
public:
 StartupActionsManager();
 ~StartupActionsManager() {}
 StartupActionsManager(const StartupActionsManager& ) : AbstractPreferencesManager() {}
 /*public*/ /*final*/ static QString STARTUP;// = "startup"; // NOI18N
 /*public*/ /*final*/ static QString NAMESPACE;// = "http://jmri.org/xml/schema/auxiliary-configuration/startup-4-3-5.xsd"; // NOI18N
 /*public*/ /*final*/ static QString NAMESPACE_OLD;// = "http://jmri.org/xml/schema/auxiliary-configuration/startup-2-9-6.xsd"; // NOI18N
 /*public*/ QList<StartupModel*>* getActions();
 /*public*/ /*<T extends StartupModel>*/ QList<StartupModel*>* getActions(QString type);
 /*public*/ /*Set<Class<? extends PreferencesManager>>*/QSet<QString>* getRequires();
 /*public*/ /*synchronized*/ void savePreferences(Profile* profile);
 /*public*/ void addAction(StartupModel* model);
 /*public*/ StartupModel* getActions(int index);
 /*public*/ void setActions(int index, StartupModel* model);
 /*public*/ void setRestartRequired();
 /*public*/ void removeAction(StartupModel* model);
 /*public*/ bool isRestartRequired();
 /*public*/ bool isDirty();
 /*public*/ void moveAction(int start, int end);
 /*public*/ QMap</*Class<? extends StartupModel>*/QString, StartupModelFactory*>* getFactories();
 /*public*/ StartupModelFactory* getFactories(/*Class<? extends StartupModel>*/QString model);
 /*public*/ void initialize(Profile* profile) throw (InitializationException);

 QObject* self() override {return (QObject*)this;}

signals:
 void propertyChange(PropertyChangeEvent *);

public slots:
 void loadPreferencesmanagers();
 /*public*/ void loadFactories();

private:
 /*private*/ /*final*/ QList<StartupModel*>* actions;// = new QList<StartupModel>();
 /*private*/ /*final*/ /*HashMap<Class<? extends StartupModel>, StartupModelFactory>*/ QMap<QString, StartupModelFactory*>* factories;// = new HashMap<>();
 /*private*/ bool _isDirty;// = false;
 /*private*/ bool restartRequired;// = false;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(StartupActionsManager.class);
 /*private*/ void setActions(int index, StartupModel* model, bool fireChange);
 /*private*/ void removeAction(StartupModel* model, bool fireChange);


};
Q_DECLARE_METATYPE(StartupActionsManager)
#endif // STARTUPACTIONSMANAGER_H
