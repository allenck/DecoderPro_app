#ifndef PREFERENCESMANAGER_H
#define PREFERENCESMANAGER_H
#include "jmriserviceproviderinterface.h"
#include <QObject>

class Profile;
class PreferencesManager : public JmriServiceProviderInterface
{
 Q_OBJECT
public:
 PreferencesManager();
 /*public*/ virtual void initialize(/*@Nonnull*/ Profile* profile);
 /*public*/ virtual bool isInitialized(/*@Nonnull*/ Profile* profile);
 template <class T>
 /*public*/ QList<T> getRequires();
 template <class T>
 /*public*/ QList<T>* getProvides();
 /*public*/ virtual void savePreferences(/*@Nonnull*/ Profile* profile);

};

#endif // PREFERENCESMANAGER_H
