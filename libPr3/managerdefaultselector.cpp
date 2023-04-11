#include "managerdefaultselector.h"
#include "systemconnectionmemo.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "internalsystemconnectionmemo.h"
#include "preferences.h"
#include "profileutils.h"
#include "class.h"
#include "configuremanager.h"
#include "systemconnectionmemomanager.h"
#include "vptr.h"
#include "defaultsystemconnectionmemo.h"
#include "throttlemanager.h"

/**
 * Records and executes a desired set of defaults for the JMRI InstanceManager
 * and ProxyManagers
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2010
 * @author Randall Wood Copyright (C) 2015
 * @since 2.9.4
 */
///*public*/ class ManagerDefaultSelector extends AbstractPreferencesManager {

/*private*/ /*final*/ /*static*/ Logger* ManagerDefaultSelector::log = LoggerFactory::getLogger("ManagerDefaultSelector");


/*public*/ ManagerDefaultSelector::ManagerDefaultSelector(QObject *parent) : AbstractPreferencesManager(parent)
{
 setProperty("JavaClassName", "jmri.managers.ManagerDefaultSelector");
 setObjectName("ManagerDefaultSelector");
 memoListener = new MemoListener(this);
 //SystemConnectionMemoManager::getDefault()->SwingPropertyChangeSupport::addPropertyChangeListener((PropertyChangeListener*)this);

 if(log == NULL)
  log = LoggerFactory::getLogger("ManagerDefaultSelector");

 SystemConnectionMemoManager::getDefault()-> addPropertyChangeListener(this->memoListener);

 //InstanceManager::getList("SystemConnectionMemo").forEach((memo) ->
 QList<QObject*>* list = InstanceManager::getList("SystemConnectionMemo");
 foreach(QObject* obj, *list)
 {
  SystemConnectionMemo* memo = (SystemConnectionMemo*)obj;
  memo->addPropertyChangeListener(this->memoListener);
  connect(memo->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), memoListener, SLOT(propertyChange(PropertyChangeEvent*)));
 }//);

}

//    SystemConnectionMemo::addPropertyChangeListener((PropertyChangeEvent e) ->
/*public*/ void ManagerDefaultSelector::propertyChange(PropertyChangeEvent *e)
{
 if (e->getPropertyName()== "ConnectionRemoved")
 {
  if(qobject_cast<SystemConnectionMemo*>(VPtr<QObject>::asPtr(e->getOldValue())))
  {
   SystemConnectionMemo* memo = qobject_cast<SystemConnectionMemo*>(VPtr<QObject>::asPtr(e->getOldValue()));
   QString removedName =  memo->getUserName();
   log->debug(tr("ConnectionRemoved for \"%1\"").arg(removedName));
   removeConnectionAsDefault(removedName);
   disconnect(memo->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), memoListener, SLOT(propertyChange(PropertyChangeEvent*)) );
  }
 }
 if (e->getPropertyName()=="ConnectionAdded")
 {
  if(qobject_cast<SystemConnectionMemo*>(VPtr<QObject>::asPtr(e->getNewValue())))
  {
   SystemConnectionMemo* memo = VPtr<SystemConnectionMemo>::asPtr( e->getNewValue());
   //memo->SwingPropertyChangeSupport::addPropertyChangeListener(this->memoListener);
   connect((DefaultSystemConnectionMemo*)memo->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   // check for special case of anything else then Internal
   QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
   if((list->size() == 1 && !(qobject_cast<InternalSystemConnectionMemo*>(list->at(0))) ||
      ((list->size() == 2 && !(qobject_cast<InternalSystemConnectionMemo*>(list->at(0))) && (qobject_cast<InternalSystemConnectionMemo*>(list->at(1)) ))))) // ACK change from 1 to 0; Internal is last!
   {
    log->debug("First real system added, reset defaults");
    QString name = ((SystemConnectionMemo*)list->at(1))->getUserName();
    removeConnectionAsDefault(name);
   }
  }
 }
 else
 {
  log->debug(tr("ignoring notification of \"%1\"").arg(e->getPropertyName()));
 }
}

// remove connection's record
void ManagerDefaultSelector::removeConnectionAsDefault(QString removedName)
{
 QVector<QString> tmpArray = QVector<QString>();
  //defaults.keys().stream().forEach((c) ->
 foreach(QString c, defaults.keys())
 {
  QString connectionName = this->defaults.value(c);
  if (connectionName==(removedName))
  {
   log->debug("Connection " + removedName + " has been removed as the default for " + c);
   tmpArray.append(c);
  }
 }//);
  //tmpArray.stream().forEach((tmpArray1) ->
 foreach(QString tmpArray1, tmpArray)
 {
  this->defaults.remove(tmpArray1);
 }//);
}

/**
 * Return the userName of the system that provides the default instance for
 * a specific class.
 *
 * @param managerClass the specific type, e.g. TurnoutManager, for which a
 *                     default system is desired
 * @return userName of the system, or  NULL if none set
 */
/*public*/ QString ManagerDefaultSelector::getDefault(QString managerClass) {
    return defaults.value(managerClass);
}

/**
 * Record the userName of the system that provides the default instance for
 * a specific class.
 *
 * To ensure compatibility of different preference versions, only classes
 * that are current registered are preserved. This way, reading in an old
 * file will just have irrelevant items ignored.
 *
 * @param managerClass the specific type, e.g. TurnoutManager, for which a
 *                     default system is desired
 * @param userName     of the system, or  NULL if none set
 */
/*public*/ void ManagerDefaultSelector::setDefault(QString managerClass, QString userName)
{
 foreach (Item item, knownManagers)
 {
  if (item.managerClass == (managerClass))
  {
   log->debug(tr("   setting default for \"%1\" to \"%2\" by request").arg( managerClass).arg(userName));
   defaults.insert(managerClass, userName);
   return;
  }
 }
 log->warn(tr("Ignoring preference for class %1 with name %2").arg(managerClass).arg(userName));
}
#if 0
/**
 * Load into InstanceManager
 *
 * @return an exception that can be passed to the user or  NULL if no errors
 *         occur
 */
//@CheckForNull
/*public*/ void ManagerDefaultSelector::configure()
{
 InitializationException* error =  NULL;
 QObjectList* connList = InstanceManager::getList("SystemConnectionMemo");
 if (connList == nullptr) {
     return; // nothing to do
 }
 log->debug(tr("configure defaults into InstanceManager from %1 memos, %2 defaults").arg(connList->size()).arg(defaults.keys().size()));
 foreach (QString c, defaults.keys())
 {
  // 'c' is the class to load
  QString connectionName = this->defaults.value(c);
  // have to find object of that type from proper connection
  bool found = false;
  for (int x = 0; x < connList->size(); x++)
  {
   DefaultSystemConnectionMemo* memo = static_cast<DefaultSystemConnectionMemo*>(connList->at(x));
   QString testName = ((SystemConnectionMemo*)memo)->getUserName();
   if (testName == memo->getUserName())
   {
    found = true;
    // match, store
    InstanceManager::setDefault(c, memo->get(c)->self());
    break;
   }
   else
   {
    log->debug(tr("   memo name didn't match: %1 vs %2").arg(testName).arg(connectionName));
   }
  }
  /*
   * If the set connection can not be found then we shall set the manager default to use what
   * has currently been set.
   */
  if (!found) {
      log->debug("!found, so resetting");
      QString currentName =  NULL;
      if (c == "ThrottleManager" && InstanceManager::getNullableDefault("ThrottleManager") !=  NULL) {
       currentName = ((ThrottleManager*)InstanceManager::throttleManagerInstance())->getUserName();
      }
      else if (c == "PowerManager" && InstanceManager::getNullableDefault("PowerManager") !=  NULL) {
       currentName =((PowerManager*) InstanceManager::getDefault("PowerManager"))->getUserName();
      }
      if (currentName != "")
      {
         log->warn(tr("The configured %1 for %2 can not be found so will use the default %3").arg(connectionName).arg(c).arg(currentName));
         this->defaults.insert(c, currentName);
      }
  }
 }
}
#endif
/**
 * Load into InstanceManager
 *
 * @param profile the profile to configure against
 * @return an exception that can be passed to the user or null if no errors
 *         occur
 */
//@CheckForNull
/*public*/ InitializationException* ManagerDefaultSelector::configure(Profile* profile) {
    InitializationException* error = nullptr;
    QList</*SystemConnectionMemo*/QObject*>* connList = InstanceManager::getList("SystemConnectionMemo");
    log->debug(tr("configure defaults into InstanceManager from %1 memos, %2 defaults").arg(connList->size(), defaults.keys().size()));
    // Takes a copy to avoid ConcurrentModificationException.
    QSet<QString> keys = QSet<QString>(defaults.keys().toSet());
    for (QString c : keys) {
        // 'c' is the class to load
        QString connectionName = defaults.value(c);
        // have to find object of that type from proper connection
        bool found = false;
        for (QObject* obj : *connList) {
         SystemConnectionMemo* memo = (SystemConnectionMemo*)obj;
            QString testName = memo->getUserName();
            if (testName == (connectionName)) {
                found = true;
                // match, store
                try {
                    if (memo->provides(c)) {
                        log->debug(tr("   setting default for \"%1\" to \"%2\" in configure").arg(c, memo->get(c)->toString()));
                        InstanceManager::setDefault(c, (QObject*)memo->get(c));
                    }
                } catch (NullPointerException ex) {
                    QString englishMsg = tr("System connection %1 provides a null manager for %2").arg(memo->getUserName(), c); // NOI18N
                    QString localizedMsg = tr("System connection %1 provides a null manager for %2").arg(memo->getUserName(), c); // NOI18N
                    error = new InitializationException(englishMsg, localizedMsg);
                    log->warn(tr("SystemConnectionMemo for %1 (%2) provides a null %3 instance").arg(memo->getUserName(), memo->getClass(), c));
                }
                break;
            } else {
                log->debug(tr("   memo name didn't match: %1 vs %2").arg(testName, connectionName));
            }
        }
        /*
         * If the set connection can not be found then we shall set the manager default to use what
         * has currently been set.
         */
        if (!found) {
            log->debug("!found, so resetting");
            QString currentName = "";
            if (c == "ThrottleManager" && InstanceManager::getOptionalDefault("ThrottleManager")/*.isPresent()*/) {
                currentName = InstanceManager::throttleManagerInstance()->getUserName();
            } else if (c == "PowerManager" && InstanceManager::getOptionalDefault("PowerManager")/*.isPresent()*/) {
                currentName = ((PowerManager*)InstanceManager::getDefault("PowerManager"))->getUserName();
            }
            if (currentName != "") {
                log->warn(tr("The configured %1 for %2 can not be found so will use the default %3").arg(connectionName, c, currentName));
                this->defaults.insert(c, currentName);
            }
        }
    }
    if (!isPreferencesValid(profile, connList)) {
        error = new InitializationException(tr( "JMRI is defaulting to internal systems for all purposes. Usually this is indicates a misconfiguration."), tr("JMRI is defaulting to internal systems for all purposes. Usually this is indicates a misconfiguration."));
    }
    return error;
}

//@Override
/*public*/ void ManagerDefaultSelector::initialize(Profile* profile) /*throws InitializationException*/ {
 if (!this->isInitialized(profile)) {
     Preferences* preferences = ProfileUtils::getPreferences(profile, this->getClass(), true); // NOI18N
     Preferences* defaultsPreferences = preferences->node("defaults");
     try {
         for (QString name : defaultsPreferences->keys()) {
             QString connection = defaultsPreferences->get(name, "");
             QString cls = this->classForName(name);
             log->debug(tr("Loading default %1 for %2").arg(connection, name));
             if (cls != "") {
                 this->defaults.insert(cls, connection);
                 log->debug(tr("Loaded default %1 for %2").arg(connection, cls));
             }
         }
         this->allInternalDefaultsValid = preferences->getBoolean(ALL_INTERNAL_DEFAULTS, this->allInternalDefaultsValid);
     } catch (BackingStoreException* ex) {
         log->info("Unable to read preferences for Default Selector.");
     }
     InitializationException* ex = this->configure(profile);
     ConfigureManager* manager = (ConfigureManager*)InstanceManager::getOptionalDefault("ConfigureManager");//.ifPresent((manager) -> {
     if(manager)
         manager->registerPref(this); // allow profile configuration to be written correctly
     //});
     this->setInitialized(profile, true);
     if (ex != nullptr) {
         this->addInitializationException(profile, ex);
         throw ex;
     }
 }
}
/*public*/ /*final*/ /*static*/ QString ManagerDefaultSelector::ALL_INTERNAL_DEFAULTS = "allInternalDefaults";

//@Override
/*public*/ void ManagerDefaultSelector::savePreferences(Profile* profile) {
    Preferences* preferences = ProfileUtils::getPreferences(profile, this->getClass(), true); // NOI18N
    Preferences* defaultsPreferences = preferences->node("defaults");
    try {
//        this.defaults.keySet().stream().forEach((cls) -> {
//            defaultsPreferences.put(this.nameForClass(cls), this.defaults.get(cls));
//        });
        preferences->putBoolean(ALL_INTERNAL_DEFAULTS, this->allInternalDefaultsValid);
        preferences->sync();
    } catch (BackingStoreException* ex) {
        log->error("Unable to save preferences for Default Selector.", ex);
    }
}

/*private*/ bool ManagerDefaultSelector::isPreferencesValid(Profile* profile, QList<QObject *> *connections) {
    log->trace("isPreferencesValid start");
    if (allInternalDefaultsValid) {
        log->trace("allInternalDefaultsValid returns true");
        return true;
    }
    bool usesExternalConnections = false;

    // classes of managers being provided, and set of which SystemConnectionMemos can provide each
    QMap</*Class<?>*/QString, QSet<SystemConnectionMemo*> > providing = QMap</*Class<?>*/QString, QSet<SystemConnectionMemo*> >();

    // list of all external providers (i.e. SystemConnectionMemos) that provide at least one known manager type
    QSet<SystemConnectionMemo*> providers = QSet<SystemConnectionMemo*>();

    if (connections->size() > 1) {
        //connections.stream().filter((memo) -> (!(memo instanceof InternalSystemConnectionMemo))).forEachOrdered((memo) -> {
     foreach(QObject* obj, *connections)
     {
      if(qobject_cast<InternalSystemConnectionMemo*>(obj))
      {
         SystemConnectionMemo* memo = (SystemConnectionMemo*)obj;
            // populate providers by adding all external (non-internal) connections that provide at least one default
            for (Item item : knownManagers) {
                if (memo->provides(item.managerClass)) {
                    providers.insert(memo);
                    break;
                }
            }
       }
      }//);
        // if there are no external providers of managers, no further checks are needed
        if (providers.size() >= 1) {
            // build a list of defaults provided by external connections
            //providers.stream().forEach((memo) -> {
            foreach(SystemConnectionMemo* memo, providers){
                for (Item item : knownManagers) {
                    if (memo->provides(item.managerClass)) {
                        QSet<SystemConnectionMemo*> provides = providing.value(item.managerClass, QSet<SystemConnectionMemo*>());
                        provides.insert(memo);
                        providing.insert(item.managerClass, provides);
                    }
                }
            }//);

            if (log->isDebugEnabled()) {
                // avoid unneeded overhead of looping through providers
                //providing.forEach((cls, clsProviders) -> {
             QMapIterator</*Class<?>*/QString, QSet<SystemConnectionMemo*> > iter(providing);
             while(iter.hasNext()){
              iter.next();
              QString cls = iter.key();
                    log->debug(tr("%1 default provider is %2, is provided by:").arg(cls/*getName()*/, defaults.value(cls)));
                    //clsProviders.forEach((provider) -> {
                    foreach(SystemConnectionMemo* provider, providers){
                        log->debug(tr("    %1").arg(provider->getUserName()));
                    }//);
                }//);
            }

            for (SystemConnectionMemo* memo : providers) {
                //if (providing.keySet().stream().filter((cls) -> {
                foreach(QString cls, providing.keys()){
                    QSet<SystemConnectionMemo*> provides = providing.value(cls);
                    log->debug(tr("%1 is provided by %2 out of %3 connections").arg(cls/*.getName()*/, provides.size(), providers.size()));
                    log->trace(tr("memo stream returns %1 due to producers.size() %2").arg((provides.size() > 0), provides.size()));
                    return (provides.size() > 0);
                }
//                ).anyMatch((cls) -> {
//                    log->debug(tr("%1 has an external default").arg(cls));
//                    if (defaults.get(cls) == nullptr) {
//                        log->trace("memo stream returns true because there's no default defined and an external provider exists");
//                        return true;
//                    }
//                    log->trace(tr("memo stream returns %1 due to memo.getUserName() %2 and %3").arg((memo->getUserName() == (defaults.value(cls))), memo->getUserName(), defaults.value(cls)));
//                    return memo->getUserName() == (defaults.value(cls));
//                })) {
//                    log->trace("setting usesExternalConnections true");
//                    usesExternalConnections = true;
//                    // no need to check further
//                    break;
//                }
            }
        }
    }
    log->trace(tr("method end returns %1 due to providers.size() %2 and usesExternalConnections %3").arg((providers.size() >= 1 ? usesExternalConnections : true)?"true":"false").arg(providers.size()).arg(usesExternalConnections?"true":"false"));
    return providers.size() >= 1 ? usesExternalConnections : true;
}

/*public*/ bool ManagerDefaultSelector::isPreferencesValid(Profile* profile) {
    return isPreferencesValid(profile, InstanceManager::getList("SystemConnectionMemo"));
}
///*public*/ static class Item {

//    /*public*/ String typeName;
//    /*public*/ Class<?> managerClass;

    ManagerDefaultSelector::Item::Item(QString typeName, QString managerClass) {
        this->typeName = typeName;
        this->managerClass = managerClass;
    }
//}

/*private*/ QString ManagerDefaultSelector::nameForClass(/*@Non NULL*/ QString cls)
{
 return cls; //.getCanonicalName().replace('.', '-');
}

/*private*/ QString ManagerDefaultSelector::classForName(/*@Non NULL*/ QString name)
{
 try
 {
  return Class::forName(name/*.replace('-', '.')*/)->metaObject()->className();
 }
 catch (ClassNotFoundException* ex)
 {
  log->error(tr("Could not find class for %1").arg(name));
  return  NULL;
 }
}

void  MemoListener::propertyChange(PropertyChangeEvent *e)
{
 mds->log->trace(tr("memoListener fired via %1").arg(e->toString()));
  if(e->getPropertyName() == SystemConnectionMemo::USER_NAME)
  {
    QString oldName = e->getOldValue().toString();
    QString newName = e->getNewValue().toString();
    mds->log->debug(tr("ConnectionNameChanged from \"%1\" to \"%2\"").arg(oldName).arg(newName));
    // Takes a copy of the keys to avoid ConcurrentModificationException.
//    new HashSet<>(defaults.keySet()).forEach((c) -> {
//        String connectionName = this.defaults.get(c);
//        if (connectionName.equals(oldName)) {
//            ManagerDefaultSelector.this.defaults.put(c, newName);
//        }
//    });
    foreach (QString c, mds->defaults.keys())
    {
     QString connectionName = mds->defaults.value(c);
     if (connectionName == (oldName)) {
         mds->defaults.insert(c, newName);
     }
    }
    mds->firePropertyChange("Updated", QVariant(), QVariant());
  }
   else if(e->getPropertyName() == SystemConnectionMemo::DISABLED)
   {
    bool newState = e->getNewValue().toBool();
    if (newState) {
        QString disabledName = ((SystemConnectionMemo*) e->getSource())->getUserName();
        mds->log->debug(tr("ConnectionDisabled true: \"%1\"").arg(disabledName));
        mds->removeConnectionAsDefault(disabledName);
    }
   }
   else
    {
       mds->log->debug(tr("ignoring notification of \"%1\"").arg(e->getPropertyName()));
    }
}
