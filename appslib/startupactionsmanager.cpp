#include "startupactionsmanager.h"
#include "loggerfactory.h"
#include "profileutils.h"
#include <QtXml>
#include "configxmlmanager.h"
#include "auxiliaryconfiguration.h"
#include "startupmodel.h"
#include "vptr.h"
#include "startupactionmodelutil.h"
#include "class.h"
#include <QList>
#include "serviceloader.h"
#include "startupmodelfactory.h"
#include "classloader.h"
#include "profile.h"
#include "profilemanager.h"
#include "instancemanager.h"
#include "jsonservicefactory.h"
#include "performactionmodelfactory.h"
#include "createbuttonmodelfactory.h"
#include "triggerroutemodelfactory.h"
#include "scriptbuttonmodelfactory.h"
#include "performfilemodelfactory.h"

//StartupActionsManager::StartupActionsManager()
//{

//}
/**
 * Manager for Startup Actions. Reads preferences at startup and triggers
 * actions, and is responsible for saving the preferences later.
 *
 * @author Randall Wood (C) 2015, 2016
 */
///*public*/ class StartupActionsManager extends AbstractPreferencesManager {

/*public*/ /*final*/ /*static*/ QString StartupActionsManager::STARTUP = "startup"; // NOI18N
/*public*/ /*final*/ /*static*/ QString StartupActionsManager::NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/startup-4-3-5.xsd"; // NOI18N
/*public*/ /*final*/ /*static*/ QString StartupActionsManager::NAMESPACE_OLD = "http://jmri.org/xml/schema/auxiliary-configuration/startup-2-9-6.xsd"; // NOI18N
/*private*/ /*final*/ /*static*/ Logger* StartupActionsManager::log = LoggerFactory::getLogger("StartupActionsManager");

/*public*/ StartupActionsManager::StartupActionsManager() {
    //super();
 setObjectName("StartupActionsManager");
    actions = new QList<StartupModel*>();
    factories = new QMap<QString, StartupModelFactory*>();
    _isDirty = false;
    restartRequired = false;
#if 0
    foreach (StartupModelFactory* factory,  ServiceLoader<StartupModelFactory*>::load("StartupModelFactory")) {
        factory->initialize();
        this->factories->insert(factory->getModelClass(), factory);
    }
#else
    loadFactories();
# if 0
    QStringList lst;
    lst
     << "StartupActionsManager" << "GuiLafPreferencesManager" << "SystemConsolePreferencesManager"
        << "FileLocationsPreferences" << "ManagerDefaultSelector" << "WarrantPreferences" << "RosterConfigManager"
        << "ProgrammerConfigManager" << "ConnectionConfigManager" << "JmriJTablePersistenceManager";
    ProfileManager* profileManager = (ProfileManager*) ProfileManager::getDefault();

    foreach (QString clazz, lst)
    {
     if(clazz == "StartupActionsManager" )
      continue;
     PreferencesManager* mgr = (PreferencesManager*)InstanceManager::getDefault(clazz);
     if(mgr != NULL && profileManager != NULL)
      mgr->initialize(profileManager->getActiveProfile());
     else
      log->error(tr("Class %1 does not have default initializer. "));
    }
    // Now do the JsonServiceFactory classes
    lst << "JsonThrottleServiceFactory" << "JsonSensorServiceFactory" <<
           "JsonPowerServiceFactory" << "JsonBlockServiceFactory" <<
           "JsonLayoutBlockServiceFactory" << "JsonLightServiceFactory" <<
           "JsonMemoryServiceFactory" << "JsonReporterServiceFactory" <<
           "JsonRosterServiceFactory" << "JsonSignalHeadServiceFactory" <<
           "JsonSignalMastServiceFactory" << "JsonTimeServiceFactory" <<
           "JsonTurnoutServiceFactory" << "JsonUtilServiceFactory";
    foreach (QString clazz, lst)
    {
     JsonServiceFactory* mgr = (JsonServiceFactory*)InstanceManager::getDefault(clazz);
     if(mgr == NULL)
      log->error(tr("Class %s does not have default initializer. "));
    }
# endif
#endif
}
#if 1
/**
 * {@inheritDoc}
 *
 * Loads the startup action preferences and, if all required managers have
 * initialized without exceptions, performs those actions. Startup actions
 * are only performed if {@link apps.startup.StartupModel#isValid()} is true
 * for the action. It is assumed that the action has retained an Exception
 * that can be used to explain why isValid() is false.
 */
//@Override
/*public*/ void StartupActionsManager::initialize(Profile* profile) throw (InitializationException)
{
 if (!this->isInitialized(profile))
 {
  bool perform = true;
  try
  {
   this->requiresNoInitializedWithExceptions(profile, tr("Unable to run startup actions due to earlier failures."));
  }
  catch (InitializationException ex)
  {
   perform = false;
  }
  try
  {
   QDomElement startup;
   try
   {
    startup = /*JDOMUtil.toJDOMElement*/(ProfileUtils::getAuxiliaryConfiguration(profile)->getConfigurationFragment(STARTUP, NAMESPACE, true));
   }
   catch (NullPointerException ex)
   {
    log->debug("Reading element from version 2.9.6 namespace...");
    startup = /*JDOMUtil.toJDOMElement*/(ProfileUtils::getAuxiliaryConfiguration(profile)->getConfigurationFragment(STARTUP, NAMESPACE_OLD, true));
   }
   //for (Element action : startup.getChildren())
   QDomNodeList nl = startup.childNodes();
   for(int i=0; i < nl.size(); i++)
   {
    QDomElement action = nl.at(i).toElement();
    QString adapter = action.attribute("class"); // NOI18N
    QString name = action.attribute("name"); // NOI18N
    QString override = StartupActionModelUtil::getDefault()->getOverride(name);
    if (override != "")
    {
     action.setAttribute("name", override);
     log->info(tr("Overridding startup action class %1 with %2").arg(name).arg(override));
     this->addInitializationException(profile, new InitializationException(tr(/*QLocale::English,*/ "<html>Startup action class %1 has been updated to %2.<br>Please save preferences to make this permanent.</html>").arg(name).arg(override),
             tr(/*Locale.ENGLISH,*/ "<html>Startup action class %1 has been updated to %2.<br>Please save preferences to make this permanent.</html>").arg(name).arg(override), NULL));
     name = override; // after logging difference and creating error message
    }
    QString type = action.attribute("type"); // NOI18N
    log->debug(tr("Read %1 %2 adapter %3").arg(type).arg(name).arg(adapter));
    try
    {
     log->debug(tr("Creating %1 %2 adapter %3...").arg(type).arg(name).arg(adapter));
     ((XmlAdapter*) Class::forName(adapter/*)newInstance()*/))->load(action, QDomElement()); // no perNode preferences
    }
    catch (ClassNotFoundException /*| InstantiationException | IllegalAccessException*/ ex)
    {
     log->error(tr("Unable to create %1 for %2").arg(adapter).arg(action.tagName()) + ex.getMessage());
     this->addInitializationException(profile, new InitializationException(tr(/*Locale.ENGLISH, */"Unable to create loader \"%1\" for Startup Action class \"%2\".").arg(adapter).arg(name),
             tr("Unable to create loader \"%1\" for Startup Action class \"%2\".").arg(adapter).arg(name),NULL)); // NOI18N
    }
    catch (Exception ex)
    {
     log->error(tr("Unable to load %1 into %2").arg(action.tagName()).arg(adapter) + ex.getMessage());
     this->addInitializationException(profile, new InitializationException(tr(/*Locale.ENGLISH, */"Unable to load Startup action \"%1\" using \"%3\".").arg(adapter).arg(name),
             tr("Unable to load Startup action \"%2\" using \"%1\".").arg(adapter).arg(name),NULL)); // NOI18N
    }
   }
  }
  catch (NullPointerException ex)
  {
   // ignore - this indicates migration has not occured
   log->debug("No element to read");
  }
  if (perform)
  {
//            this->actions.stream().filter((action) -> (action.isValid())).forEachOrdered((action) ->
   foreach(StartupModel* action, *this->actions)
   {
    try
    {
     action->performAction(action->getTitle());
    }
    catch (JmriException ex)
    {
     this->addInitializationException(profile, &ex);
    }
   }//);
  }
  this->_isDirty = false;
  this->restartRequired = false;
  this->setInitialized(profile, true);
  QList<Exception*>* exceptions = this->getInitializationExceptions(profile);
  if (exceptions->size() == 1)
  {
      throw  InitializationException(exceptions->at(0));
  } else if (exceptions->size() > 1)
  {
   throw  InitializationException(tr(/*Locale.ENGLISH,*/ "There are multiple errors running Startup Actions."),
              tr("There are multiple errors running Startup Actions."),NULL); // NOI18N
  }
 }
}
#endif
/*public*/ void StartupActionsManager::loadFactories()
{
 QStringList factoryList = QStringList();
 factoryList << "PerformActionModelFactory" << "StartupPauseFactory" <<
                "CreateButtonModelFactory" << "TriggerRouteModelFactory" <<
                "ScriptButtonModelFactory" << "PerformFileModelFactory";
//                "RestartStartupActionFactory";

 foreach (QString clazz, factoryList)
 {
  StartupModelFactory* factory = (StartupModelFactory*)InstanceManager::getDefault(clazz);
  if(factory != NULL )
  {
   factory->initialize();
   this->factories->insert(factory->getModelClass(), factory);
  }
  else
   log->error(tr("Class %1 does not have default initializer. ").arg(clazz));
 }
}

void StartupActionsManager::loadPreferencesmanagers()
{
 QStringList lst;
 lst
  << "StartupActionsManager" << "GuiLafPreferencesManager"
  << "SystemConsolePreferencesManager" << "FileLocationsPreferences"
  << "ManagerDefaultSelector" << "WarrantPreferences"
  << "RosterConfigManager" << "ProgrammerConfigManager"
  << "ConnectionConfigManager" << "JmriJTablePersistenceManager"
  << "JmriConfigurationManager";

 ProfileManager* profileManager = (ProfileManager*) ProfileManager::getDefault();

 foreach (QString clazz, lst)
 {
  if(clazz == "StartupActionsManager" )
   continue;
  PreferencesManager* mgr = (PreferencesManager*)InstanceManager::getDefault(clazz);
  if(mgr != NULL && profileManager != NULL)
  {
   mgr->initialize(profileManager->getActiveProfile());
  }
  else
   log->error(tr("Class %1 does not have default initializer. "));
 }
 // Now do the JsonServiceFactory classes
 lst <<  "JsonThrottleServiceFactory" <<  "JsonSensorServiceFactory"
     <<  "JsonUtilServiceFactory" <<  "JsonThrottleServiceFactory"
     <<  "JsonPowerServiceFactory" <<  "JsonTurnoutServiceFactory"
     <<  "JsonRosterServiceFactory" <<  "JsonBlockServiceFactory"
     <<  "JsonLightServiceFactory" <<  "JsonLayoutBlockServiceFactory"
     <<  "JsonMemoryServiceFactory" <<  "JsonSignalHeadServiceFactory"
     <<  "JsonSignalMastServiceFactory" <<  "JsonReporterServiceFactory";
 foreach (QString clazz, lst)
 {
  JsonServiceFactory* mgr = (JsonServiceFactory*)InstanceManager::getDefault(clazz);
  if(mgr == NULL)
   log->error(tr("Class %s does not have default initializer. "));
 }
}

//@Override
/*public*/ /*Set<Class<? extends PreferencesManager>>*/QSet<QString>* StartupActionsManager::getRequires() {
    /*Set<Class<? extends PreferencesManager>> */QSet<QString>* requires = AbstractPreferencesManager::getRequires();
    requires->insert("ManagerDefaultSelector");
    requires->insert("FileLocationsPreferences");
    requires->insert("RosterConfigManager");
    requires->insert("ProgrammerConfigManager");
    requires->insert("GuiLafPreferencesManager");
    return requires;
}
#if 1
//@Override
/*public*/ /*synchronized*/ void StartupActionsManager::savePreferences(Profile* profile)
{
 QDomDocument doc = QDomDocument();
 QDomElement element = doc.createElementNS(NAMESPACE, STARTUP);
 //actions.stream().forEach((action) ->
 foreach(StartupModel* action, *actions)
 {
  log->debug(tr("model is %1 (%2)").arg(action->getName()).arg(action->toString()));
  if (action->getName() != NULL)
  {
   QDomElement e = ConfigXmlManager::elementFromObject((QObject*)action, true);
   if (e != QDomElement())
   {
    element.appendChild(e);
   }
  }
  else
  {
   // get an error with a stack trace if this occurs
   log->error("model does not have a name.", (new Exception())->getMessage());
  }
 }//);
 try
 {
     ProfileUtils::getAuxiliaryConfiguration(profile)->putConfigurationFragment(/*JDOMUtil.toW3CElement*/(element), true);
     this->_isDirty = false;
 } catch (JDOMException ex) {
     log->error("Unable to create create XML"+ ex.getMessage());
 }
}
#endif
/*public*/ QList<StartupModel*>* StartupActionsManager::getActions() {
    return this->actions; //.toArray(new StartupModel[this->actions->size()]);
}

/*public*/ /*<T extends StartupModel>*/ QList<StartupModel*>* StartupActionsManager::getActions(QString type)
{
 //@SuppressWarnings("unchecked")
 QList<StartupModel*>* result = new QList<StartupModel*>();
 //this->actions.stream().filter((action) -> (type.isInstance(action))).forEach((action) ->
 foreach(StartupModel* action, *this->actions)
 {
  if(QString(action->metaObject()->className()) == type)
  {
   result->append(action);
   break;
  }
 } //);
 return result;
}

/*public*/ StartupModel* StartupActionsManager::getActions(int index) {
    return this->actions->at(index);
}

/**
 * Insert a {@link apps.StartupModel} at the given position. Triggers an
 * {@link java.beans.IndexedPropertyChangeEvent} where the old value is null
 * and the new value is the inserted model.
 *
 * @param index The position where the model will be inserted
 * @param model The model to be inserted
 */
/*public*/ void StartupActionsManager::setActions(int index, StartupModel* model)
{
 this->setActions(index, model, true);
}

/*private*/ void StartupActionsManager::setActions(int index, StartupModel* model, bool fireChange)
{
 if (!this->actions->contains(model))
 {
  this->actions->insert(index, model);
  this->setRestartRequired();
  if (fireChange)
  {
//   this->fireIndexedPropertyChange(STARTUP, index, QVariant(), VPtr<StartupModel>::asQVariant(model));
   emit propertyChange((PropertyChangeEvent*)(new IndexedPropertyChangeEvent(this, STARTUP,  QVariant(), VPtr<StartupModel>::asQVariant(model),index)));
  }
 }
}

/**
 * Move a {@link apps.StartupModel} from position start to position end.
 * Triggers an {@link java.beans.IndexedPropertyChangeEvent} where the index
 * is end, the old value is start and the new value is the moved model.
 *
 * @param start the original position
 * @param end   the new position
 */
/*public*/ void StartupActionsManager::moveAction(int start, int end)
{
 StartupModel* model = this->getActions(start);
 this->removeAction(model, false);
 this->setActions(end, model, false);
 //this->fireIndexedPropertyChange(STARTUP, end, start, VPtr<StartupModel>::asQVariant(model));
 emit propertyChange((PropertyChangeEvent*)(new IndexedPropertyChangeEvent(this,STARTUP, start, VPtr<StartupModel>::asQVariant(model), end)));
}

/*public*/ void StartupActionsManager::addAction(StartupModel* model)
{
 this->setActions(this->actions->size(), model);
}

/**
 * Remove a {@link apps.StartupModel}. Triggers an
 * {@link java.beans.IndexedPropertyChangeEvent} where the index is the
 * position of the removed model, the old value is the model, and the new
 * value is null.
 *
 * @param model The startup action to remove
 */
/*public*/ void StartupActionsManager::removeAction(StartupModel* model) {
    this->removeAction(model, true);
}

/*private*/ void StartupActionsManager::removeAction(StartupModel* model, bool fireChange)
{
 int index = this->actions->indexOf(model);
 this->actions->removeOne(model);
 this->setRestartRequired();
 if (fireChange)
 {
  //this->fireIndexedPropertyChange(STARTUP, index, VPtr<StartupModel>::asQVariant(model), QVariant());
  emit propertyChange((PropertyChangeEvent*)(new IndexedPropertyChangeEvent(this, STARTUP,  VPtr<StartupModel>::asQVariant(model), QVariant(), index)));
 }
}

/*public*/ QMap</*Class<? extends StartupModel>*/QString, StartupModelFactory*>* StartupActionsManager::getFactories() {
    return  new QMap<QString, StartupModelFactory*>(*this->factories);
}

/*public*/ StartupModelFactory* StartupActionsManager::getFactories(/*Class<? extends StartupModel>*/QString model) {
    return this->factories->value(model);
}

/*public*/ bool StartupActionsManager::isDirty() {
    return this->_isDirty;
}

/**
 * Mark that a change requires a restart. As a side effect, marks this
 * manager dirty.
 */
/*public*/ void StartupActionsManager::setRestartRequired() {
    this->restartRequired = true;
    this->_isDirty = true;
}

/**
 * Indicate if a restart is required for preferences to be applied.
 *
 * @return true if a restart is required, false otherwise
 */
/*public*/ bool StartupActionsManager::isRestartRequired() {
    return this->_isDirty || this->restartRequired;
}

