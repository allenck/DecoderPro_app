#ifndef PREFERENCESMANAGER_H
#define PREFERENCESMANAGER_H
#include "jmriserviceproviderinterface.h"
#include <QObject>
#include "exceptions.h"

class Exception;
class Profile;
class PreferencesManager : public JmriServiceProviderInterface
{
 //Q_OBJECT
  Q_INTERFACES(JmriServiceProviderInterface)
public:
 //PreferencesManager(QObject* parent = 0);
 /*public*/ virtual void initialize(/*@Nonnull*/ Profile* profile) /*throw (InitializationException)*/=0;
 /*public*/ virtual bool isInitialized(/*@Nonnull*/ Profile* profile);
 /*public*/ virtual bool isInitializedWithExceptions(/*@Nonnull */Profile* profile);
 virtual QList<Exception*> getInitializationExceptions(/*@Nonnull */Profile* profile)=0;
// template <class T>
// /*public*/ QList<T>* getRequires();
 virtual QSet<QString> getRequires();
// template <class T>
// /*public*/ QList<T>* getProvides();
 virtual QSet<QString> getProvides();
 /*public*/ virtual void savePreferences(/*@Nonnull*/ Profile* /*profile*/) {}

 virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(PreferencesManager, "PreferencesManager")
#endif // PREFERENCESMANAGER_H
