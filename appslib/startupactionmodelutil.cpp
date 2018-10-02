#include "startupactionmodelutil.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "class.h"
#include "startupactionfactory.h"
#include "startupmodelfactory.h"
#include "abstractaction.h"
#include "loconetmenu.h"

StartupActionModelUtil::StartupActionModelUtil(QObject* parent) : Bean(parent)
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
 {
  util = new StartupActionModelUtil();
  InstanceManager::setDefault("StartupActionModelUtil", util);
 }
 return util;
}

//@CheckForNull
/*public*/ QString StartupActionModelUtil::getActionName(/*@NonNULL Class<?>*/Class* clazz)
{
 this->prepareActionsHashMap();
 ActionAttributes* attrs = this->actions->value(clazz);
 return attrs != NULL ? attrs->name : NULL;
}

//@CheckForNull
/*public*/ QString StartupActionModelUtil::getActionName(/*@NonNULL*/ QString className)
{
 if (!className.isEmpty())
 {
  try
  {
   //return this->getActionName(Class::forName(className));
   return className;
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
 if (this->actions->contains(clazz)) {
     return this->actions->value(clazz)->isSystemConnectionAction;
 }
 return false;
}

/*public*/ bool StartupActionModelUtil::isSystemConnectionAction(/*@NonNULL*/ QString className) {
    if (!className.isEmpty()) {
        try {
            return this->isSystemConnectionAction(Class::forName(className));
        } catch (ClassNotFoundException ex) {
            log->error(tr("Did not find class \"%1\"").arg(className));
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
  QMapIterator<Class*, ActionAttributes*>entry(*this->actions);
  while(entry.hasNext())
  {
entry.next();
   if (entry.value()->name==(name))
   {
    if(qobject_cast<AbstractAction*>((QObject*)entry.key())!= NULL)
     return ((AbstractAction*)entry.key())->getClassname();
    else
    return entry.key()->metaObject()->className();
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
/*public*/ QVector<Class*> StartupActionModelUtil::getClasses() {
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
 actions->insert(clazz, attrs);
 this->firePropertyChange("length", QVariant(), QVariant());
}

/*public*/ void StartupActionModelUtil::addAction(Class* clazz, QString name)
{
 ActionAttributes* attrs =  new ActionAttributes(name, clazz);
 actions->insert(clazz, attrs);
 this->firePropertyChange("length", QVariant(), QVariant());
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
 actions->remove(clazz);
 this->firePropertyChange("length", QVariant(), QVariant());
}

/*private*/ void StartupActionModelUtil::prepareActionsHashMap()
{
 if (this->actions == NULL)
 {
  this->actions = new QMap<Class*, ActionAttributes*>();
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
  // NOTE: For these actions to become available, they must be able to be loaded via Class::forName() and must return the original java class name for the getClassName function.
  actionListBundle = QMap<QString, QString>();
  actionListBundle.insert("apps.CheckForUpdateAction", "Check for Updates");
  actionListBundle.insert("apps.RestartAction", "Restart JMRI");
  actionListBundle.insert("apps.SystemConsoleAction", "Open JMRI System console");
  actionListBundle.insert("apps.gui3.TabbedPreferencesAction", "Preferences...");
  actionListBundle.insert("apps.gui3.TabbedPreferencesProfileAction", "Profiles...");
  actionListBundle.insert("jmri.configurexml.LoadXmlConfigAction", "Open Panel File...");
  actionListBundle.insert("jmri.jmris.json.JsonServerAction", "Start JMRI JSON Server");
  actionListBundle.insert("jmri.jmris.simpleserver.SimpleServerAction", "Start Simple JMRI Server");
  actionListBundle.insert("jmri.jmris.srcp.JmriSRCPServerAction", "Start JMRI SRCP Server");
  actionListBundle.insert("jmri.jmrit.MemoryFrameAction", "Open Memory Monitor");
  actionListBundle.insert("jmri.jmrit.XmlFileValidateAction", "Validate XML File");
  actionListBundle.insert("jmri.jmrit.analogclock.AnalogClockAction", "Open Analog Clock");
  actionListBundle.insert("jmri.jmrit.automat.monitor.AutomatTableAction", "Open Thread Monitor");
  actionListBundle.insert("jmri.jmrit.beantable.AudioTableAction", "Open Audio Table");
  actionListBundle.insert("jmri.jmrit.beantable.BlockTableAction", "Open Block Table");
  actionListBundle.insert("jmri.jmrit.beantable.IdTagTableAction", "Open ID Tag Table");
  actionListBundle.insert("jmri.jmrit.beantable.LightTableAction", "Open Light Table");
  actionListBundle.insert("jmri.jmrit.beantable.ListedTableAction", "Open Tables");
  actionListBundle.insert("jmri.jmrit.beantable.LogixTableAction", "Open Logix Table");
  actionListBundle.insert("jmri.jmrit.beantable.MemoryTableAction", "Open Memory Table");
  actionListBundle.insert("jmri.jmrit.beantable.OBlockTableAction", "Open OBlock Table");
  actionListBundle.insert("jmri.jmrit.beantable.ReporterTableAction", "Open Reporter Table");
  actionListBundle.insert("jmri.jmrit.beantable.RouteTableAction", "Open Route Table");
  actionListBundle.insert("jmri.jmrit.beantable.SectionTableAction", "Open Section Table");
  actionListBundle.insert("jmri.jmrit.beantable.SensorTableAction", "Open Sensor Table");
  actionListBundle.insert("jmri.jmrit.beantable.SignalGroupTableAction", "Open Signal Group Table");
  actionListBundle.insert("jmri.jmrit.beantable.SignalHeadTableAction", "Open Signal Head Table");
  actionListBundle.insert("jmri.jmrit.beantable.SignalMastTableAction", "Open Signal Mast Table");
  actionListBundle.insert("jmri.jmrit.beantable.TransitTableAction", "Open Transit Table");
  actionListBundle.insert("jmri.jmrit.blockboss.BlockBossAction", "Open SSL Tool");
  actionListBundle.insert("jmri.jmrit.consisttool.ConsistToolAction", "Open Consisting Tool");
  actionListBundle.insert("jmri.jmrit.dispatcher.DispatcherAction", "Open Dispatcher");
  actionListBundle.insert("jmri.jmrit.display.panelEditor.PanelEditorAction", "New Panel");
  actionListBundle.insert("jmri.jmrit.dualdecoder.DualDecoderToolAction", "Open Multi-Decoder Control");
  actionListBundle.insert("jmri.jmrit.jython.InputWindowAction", "Open Script Entry Window");
  actionListBundle.insert("jmri.jmrit.jython.JythonWindow", "Open Script Output Window");
  actionListBundle.insert("jmri.jmrit.lcdclock.LcdClockAction", "Open LCD Clock");
  actionListBundle.insert("jmri.jmrit.nixieclock.NixieClockAction", "Open Nixie Clock");
  actionListBundle.insert("jmri.jmrit.operations.automation.AutomationsTableFrameAction", "Open Operations Automations Window");
  actionListBundle.insert("jmri.jmrit.operations.locations.LocationsTableAction", "Open Operations Locations Window");
  actionListBundle.insert("jmri.jmrit.operations.rollingstock.cars.CarsTableAction", "Open Operations Cars Window");
  actionListBundle.insert("jmri.jmrit.operations.rollingstock.engines.EnginesTableAction", "Open Operations Engines Window");
  actionListBundle.insert("jmri.jmrit.operations.routes.RoutesTableAction", "Open Operations Routes Window");
  actionListBundle.insert("jmri.jmrit.operations.setup.OperationsSetupAction", "Open Operations Setup Window");
  actionListBundle.insert("jmri.jmrit.operations.trains.TrainsTableAction", "Open Operations Trains Window");
  actionListBundle.insert("jmri.jmrit.powerpanel.PowerButtonAction", "Power Button");
  actionListBundle.insert("jmri.jmrit.powerpanel.PowerPanelAction", "Open Power Control");
  actionListBundle.insert("jmri.jmrit.roster.RecreateRosterAction", "Rebuild Roster");
  actionListBundle.insert("jmri.jmrit.roster.swing.RosterFrameAction", "Open Roster");
  actionListBundle.insert("jmri.jmrit.sendpacket.SendPacketAction", "Open DCC Packet Tool");
  actionListBundle.insert("jmri.jmrit.simpleclock.SimpleClockAction", "Open Fast Clock Configuration");
  actionListBundle.insert("jmri.jmrit.simplelightctrl.SimpleLightCtrlAction", "Open Light Control");
  actionListBundle.insert("jmri.jmrit.simpleprog.SimpleProgAction", "Open Single CV Programmer");
  actionListBundle.insert("jmri.jmrit.simpleturnoutctrl.SimpleTurnoutCtrlAction", "Open Turnout Control");
  actionListBundle.insert("jmri.jmrit.speedometer.SpeedometerAction", "Open Speedometer");
  actionListBundle.insert("jmri.jmrit.symbolicprog.tabbedframe.PaneOpsProgAction", "Open DecoderPro Operations Mode");
  actionListBundle.insert("jmri.jmrit.symbolicprog.tabbedframe.PaneProgAction", "Open DecoderPro Service Mode");
  actionListBundle.insert("jmri.jmrit.throttle.LoadDefaultXmlThrottlesLayoutAction", "Load Default Throttle Layout");
  actionListBundle.insert("jmri.jmrit.throttle.ThrottleCreationAction", "Open Throttle");
  actionListBundle.insert("jmri.jmrit.withrottle.WiThrottleCreationAction", "Start WiThrottle Server");
  actionListBundle.insert("jmri.jmrix.jinput.treecontrol.TreeAction", "Open USB Input Control");
  actionListBundle.insert("jmri.jmrix.libusb.UsbViewAction", "Open USB Device Viewer");
  actionListBundle.insert("jmri.jmrix.loconet.locormi.LnMessageServerAction", "Start LocoNet Server");
  actionListBundle.insert("jmri.web.server.WebServerAction", "Start Web Server");
  actionListBundle.insert("jmri.jmrix.loconet.loconetovertcp.LnTcpServerAction", "Start LocoNet Over Tcp Server");

  // add selected actions in the LocoNetMenu
  actionListBundle.insert("LocoNetMenuStartupAction", "Monitor LocoNet");
  actionListBundle.insert("LocoNetMenuStartupAction", "Monitor Slots");
  actionListBundle.insert("LocoNetMenuStartupAction", "Clock Monitor");
  actionListBundle.insert("LocoNetMenuStartupAction", "Monitor LocoNet Stats");

  foreach(QString key, actionListBundle.keys())
  {
   try
   {
    Class* clazz  = Class::forName(key);
    ((AbstractAction*)clazz)->setClassname(key);
    ActionAttributes* attrs = new ActionAttributes(actionListBundle.value(key), clazz);
    actions->insert(clazz, attrs);
    if(key == "LocoNetMenuStartupAction")
     ((AbstractAction*)clazz)->setText(key);
   } catch (ClassNotFoundException ex) {
    log->error(tr("Did not find class \"%1\"").arg(key));
   }
  }

#if 0
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
#endif

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
     this->clazz = clazz;
//     Class* cls = Class::forName("SystemConnectionAction");
//        this->isSystemConnectionAction = cls->isAssignableFrom(QString(((QObject*)clazz)->metaObject()->className()));
     this->isSystemConnectionAction = clazz->isAssignableFrom("SystemConnectionAction");
    }
//}
