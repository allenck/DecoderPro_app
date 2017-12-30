#ifndef ABSTRACTPREFERENCESMANAGER_H
#define ABSTRACTPREFERENCESMANAGER_H
#include "preferencesmanager.h"
#include "exceptions.h"


class AbstractPreferencesManager : public PreferencesManager
{
public:
 AbstractPreferencesManager(QObject* parent = 0);
 /*public*/ bool isInitialized(/*@Nonnull*/ Profile* profile);
 /*public*/ QList<Exception*>* getInitializationExceptions(/*@Nonnull*/ Profile* profile);
 /*public*/ bool isInitializedWithExceptions(/*@Nonnull*/ Profile* profile);
 /*public*/ QSet<QString>* getRequires();
 /*public*/ QSet<QString>* getProvides();

private:
 /*private*/ /*final*/ QHash<Profile*, bool>* initialized;// = new HashMap<>();
 /*private*/ /*final*/ QHash<Profile*, bool>* initializing;// = new HashMap<>();
 /*private*/ /*final*/ QHash<Profile*, QList<Exception*>* >* exceptions;// = new HashMap<>();

protected:
 /*protected*/ bool isInitializing(/*@Nonnull*/ Profile* profile);
 /*protected*/ void setInitialized(/*@Nonnull*/ Profile* profile, bool initialized);
 /*protected*/ void setInitializing(/*@Nonnull*/ Profile* profile, bool initializing);
 /*protected*/ void addInitializationException(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ Exception* exception);
 /*protected*/ void requiresNoInitializedWithExceptions(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ /*Set<Class<? extends PreferencesManager>> */QSet<QString>* classes, /*@Nonnull*/ QString message); //throws InitializationException
 /*protected*/ void requiresNoInitializedWithExceptions(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ QString message); //throws InitializationException


};

#endif // ABSTRACTPREFERENCESMANAGER_H
