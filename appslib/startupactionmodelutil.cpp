#include "startupactionmodelutil.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "class.h"
#include "startupactionfactory.h"
#include "startupmodelfactory.h"

StartupActionModelUtil::StartupActionModelUtil()
{
 actions = NULL;
 overrides = NULL;
 actionNames = NULL;
}
/**
 * Maintain a list of actions that can be used by
 * {@link apps.startup.AbstractActionModel} and it's descendants. This list is
 * populated by {@link apps.startup.StartupActionFactory} instances registered
 * with a {@link java.util.ServiceLoader}.
 *
 * @author Randall Wood (c) 2016
 */
// /*public*/ class StartupActionModelUtil extends Bean {
/*private*/ /*final*/ /*static*/ Logger* StartupActionModelUtil::log = LoggerFactory::getLogger("StartupActionModelUtil");


/**
 * Get the default StartupActionModelUtil instance, creating it if
 * necessary.
 *
 * @return the default instance
 */
//@NonNULL
/*static*/ /*public*/ StartupActionModelUtil* StartupActionModelUtil::getDefault()
{
 //        return InstanceManager::getOptionalDefault("StartupActionModelUtil").orElseGet(() -> {
 //            return InstanceManager.setDefault(StartupActionModelUtil.class, new StartupActionModelUtil());
 //        });
 StartupActionModelUtil* util = (StartupActionModelUtil*)InstanceManager::getOptionalDefault("StartupActionModelUtil");
 if(util == NULL)
  util = new StartupActionModelUtil();
 return util;
}

//@CheckForNull
/*public*/ QString StartupActionModelUtil::getActionName(/*@NonNULL Class<?>*/Class* clazz)
{
 this->prepareActionsHashMap();
 ActionAttributes* attrs = this->actions->value(QString(clazz->metaObject()->className()));
 return attrs != NULL ? attrs->name : NULL;
}

//@CheckForNull
/*public*/ QString StartupActionModelUtil::getActionName(/*@NonNULL*/ QString className)
{
 if (!className.isEmpty())
 {
  try
  {
   return this->getActionName(Class::forName(className.mid(className.lastIndexOf(".")+1)));
  }
  catch (ClassNotFoundException ex)
  {
   log->error(tr("Did not find class \"%1\"").arg(className));
  }
 }
 return NULL;
}

/*public*/ bool StartupActionModelUtil::isSystemConnectionAction(/*@NonNULL*/ Class* clazz)
{
 this->prepareActionsHashMap();
 if (this->actions->contains(clazz->metaObject()->className())) {
     return this->actions->value(clazz->metaObject()->className())->isSystemConnectionAction;
 }
 return false;
}

/*public*/ bool StartupActionModelUtil::isSystemConnectionAction(/*@NonNULL*/ QString className) {
    if (!className.isEmpty()) {
        try {
            return this->isSystemConnectionAction(Class::forName(className));
        } catch (ClassNotFoundException ex) {
            log->error("Did not find class \"{}\"", className);
        }
    }
    return false;
}

//@CheckForNull
/*public*/ QString StartupActionModelUtil::getClassName(/*@NonNULL*/ QString name)
{
 this->prepareActionsHashMap();
 if (!name.isEmpty())
 {
  //for (Entry<Class<?>, ActionAttributes> entry : this->actions.entrySet())
  QMapIterator<QString, ActionAttributes*>entry(*this->actions);
  while(entry.hasNext())
  {
entry.next();
   if (entry.value()->name==(name))
   {
    return entry.key();
   }
  }
 }
 return NULL;
}

//@CheckForNull
/*public*/ QStringList StartupActionModelUtil::getNames()
{
 this->prepareActionsHashMap();
 if (this->actionNames == NULL)
 {
  this->actionNames = new QList<QString>();
//        this->actions.values().stream().forEach((attrs) ->
  foreach(ActionAttributes* attrs, this->actions->values())
  {
   this->actionNames->append(attrs->name);
  }//);
//  this->actionNames->sort(NULL);
 }
 //return this->actionNames.toArray(new String[this->actionNames.size()]);
 return *this->actionNames;
}

//@NonNULL
/*public*/ QVector<QString> StartupActionModelUtil::getClasses() {
    this->prepareActionsHashMap();
   // return actions->keys().toArray(new Class<?>[actions.size()]);
 return actions->keys().toVector();
}

/*public*/ void StartupActionModelUtil::addAction(/*@NonNULL*/ QString strClass, /*@NonNULL*/ QString name) throw (ClassNotFoundException)
{
 this->prepareActionsHashMap();
 this->actionNames = NULL;
 Class* clazz;
 try {
     clazz = Class::forName(strClass);
 } catch (ClassNotFoundException ex) {
     log->error(tr("Did not find class \"%1\"").arg(strClass));
     throw ex;
 }
 ActionAttributes* attrs =  new ActionAttributes(name, clazz);
 actions->insert(strClass, attrs);
 this->firePropertyChange("length", NULL, NULL);
}

/*public*/ void StartupActionModelUtil::removeAction(/*@NonNULL*/ QString strClass) throw (ClassNotFoundException)
{
 this->prepareActionsHashMap();
 this->actionNames = NULL;
 /*Class<?>*/Class* clazz;
 try {
     clazz = Class::forName(strClass);
 } catch (ClassNotFoundException ex) {
     log->error("Did not find class \"{}\"", strClass);
     throw ex;
 }
 actions->remove(strClass);
 this->firePropertyChange("length", QVariant(), QVariant());
}

/*private*/ void StartupActionModelUtil::prepareActionsHashMap()
{
 if (this->actions == NULL)
 {
  this->actions = new QMap<QString, ActionAttributes*>();
  this->overrides = new QMap<QString, Class*>();

//        ResourceBundle rb = ResourceBundle.getBundle("apps.ActionListBundle");
//     rb.keySet().stream().filter((key) -> (!key.isEmpty())).forEach((key) -> {
//         try {
//             Class<?> clazz = Class.forName(key);
//             ActionAttributes attrs = new ActionAttributes(rb.getString(key), clazz);
//             this->actions.put(clazz, attrs);
//         } catch (ClassNotFoundException ex) {
//             log->error(tr{"Did not find class \"%1\"").arg(key));
//         }
//     });

   QStringList factoryList = QStringList();
   factoryList << "PerformActionModelFactory" << "StartupPauseFactory" <<
                  "CreateButtonModelFactory" << "TriggerRouteModelFactory" <<
                  "ScriptButtonModelFactory" << "PerformFileModelFactory" <<
                  "RestartStartupActionFactory";

   foreach (QString clazz, factoryList)
   {
    try
    {
     StartupModelFactory* factory = (StartupModelFactory*)Class::forName(clazz);
     ActionAttributes* attrs = new ActionAttributes(clazz, (Class*)factory);
     this->actions->insert(clazz, attrs);
    }
    catch (FileNotFoundException ex)
    {
     log->error(tr("Did not find class \"%1\"").arg(clazz));
    }
   }


//     ServiceLoader<StartupActionFactory> loader = ServiceLoader.load(StartupActionFactory.class);
//     loader.forEach(factory -> {
//         for (Class<?> clazz : factory.getActionClasses()) {
//             ActionAttributes attrs = new ActionAttributes(factory.getTitle(clazz), clazz);
//             this->actions.put(clazz, attrs);
//             for (String overridden : factory.getOverriddenClasses(clazz)) {
//                 this->overrides.put(overridden, clazz);
//             }
//         }
//     });
//     loader.reload(); // allow factories to be garbage collected

 }
}

//@CheckForNull
/*public*/ QString StartupActionModelUtil::getOverride(/*@Nullable */QString name) {
    this->prepareActionsHashMap();
    if (name != NULL && this->overrides->contains(name)) {
        return this->overrides->value(name)->metaObject()->className();
    }
    return NULL;
}

///*private*/ static class ActionAttributes {

//    final String name;
//    final boolean isSystemConnectionAction;

    ActionAttributes::ActionAttributes(QString name, Class* clazz) {
        this->name = name;
     Class* cls = Class::forName("SystemConnectionAction");
        this->isSystemConnectionAction = cls->isAssignableFrom(clazz->metaObject()->className());
    }
//}
