#ifndef ABSTRACTPREFERENCESMANAGER_H
#define ABSTRACTPREFERENCESMANAGER_H
#include "preferencesmanager.h"
#include <QtCore>
#include "exceptions.h"
#include "bean.h"

class Logger;
class AbstractPreferencesManager : public Bean, public PreferencesManager
{
  Q_OBJECT
  Q_INTERFACES(PreferencesManager)
public:
 AbstractPreferencesManager(QObject* parent = 0);
 /*public*/ bool isInitialized(/*@Nonnull*/ Profile* profile);
 /*public*/ QList<Exception*> getInitializationExceptions(/*@Nonnull*/ Profile* profile);
 /*public*/ bool isInitializedWithExceptions(/*@Nonnull*/ Profile* profile);
 /*public*/ QSet<QString>* getRequires();
 /*public*/ QSet<QString>* getProvides();

private:
 /*private*/ /*final*/ QHash<Profile*, bool> initialized = QHash<Profile*, bool>();
 /*private*/ /*final*/ QHash<Profile*, bool> initializing = QHash<Profile*, bool>();
 /*private*/ /*final*/ QHash<Profile*, QList<Exception*>* > exceptions = QHash<Profile*, QList<Exception*>* >();
 static Logger* log;

protected:
 /*protected*/ bool isInitializing(/*@Nonnull*/ Profile* profile);
 /*protected*/ void setInitialized(/*@Nonnull*/ Profile* profile, bool initialized);
 /*protected*/ void setInitializing(/*@Nonnull*/ Profile* profile, bool initializing);
 /*protected*/ void addInitializationException(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ Exception* exception);
 /*protected*/ void requiresNoInitializedWithExceptions(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ /*Set<Class<? extends PreferencesManager>> */QSet<QString>* classes, /*@Nonnull*/ QString message); //throws InitializationException
 /*protected*/ void requiresNoInitializedWithExceptions(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ QString message); //throws InitializationException


};

#endif // ABSTRACTPREFERENCESMANAGER_H
