#ifndef JMRICONFIGURATIONMANAGER_H
#define JMRICONFIGURATIONMANAGER_H

#include "configuremanager.h"

class ConfigXmlManager;
class PreferencesManager;
class InitializationException;
class JmriConfigurationManager : public ConfigureManager
{
public:
 JmriConfigurationManager(QObject* parent = 0);
 /*public*/ void registerPref(QObject* o);
 /*public*/ void removePrefItems();
 /*public*/ void registerConfig(QObject* o);
 /*public*/ void registerConfig(QObject* o, int x) ;
 /*public*/ void registerTool(QObject* o);
 /*public*/ void registerUser(QObject* o);
 /*public*/ void registerUserPrefs(QObject* o);
 /*public*/ void deregister(QObject* o);

private:
 /*private*/ /*final*/ Logger* log;// = LoggerFactory.getLogger(JmriConfigurationManager.class);
 /*private*/ /*final*/ ConfigXmlManager* legacy;// = new ConfigXmlManager();
 /*private*/ /*final*/ QMap<PreferencesManager*, InitializationException*> initializationExceptions;// = new HashMap<>();


};

#endif // JMRICONFIGUREMANAGER_H
