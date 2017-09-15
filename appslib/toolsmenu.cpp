#include "toolsmenu.h"
#include "jseparator.h"
#include "tabbedpreferencesaction.h"
#include "instancemanager.h"
#include "simpleprogaction.h"
#include "paneprogaction.h"
#include "paneopsprogaction.h"
#include "throttlecreationaction.h"
#include "throttleslistaction.h"
#include "powerpanelaction.h"
#include "simpleturnoutctrlaction.h"
#include "simpleclockaction.h"
#include "analogclockaction.h"
#include "listedtableaction.h"
#include "nixieclockaction.h"
#include "lcdclockaction.h"
#include "consistmanager.h"
#include "consisttoolaction.h"
#include "dualdecodertoolaction.h"
#include "oblocktableaction.h"
#include "blockbossaction.h"
#include "sensorgroupaction.h"
#include "operationsmenu.h"
#include "simplelightctrlaction.h"
#include "speedometeraction.h"
#include "sendpacketaction.h"
#include "lighttabletabaction.h"
#include "ds64panel.h"
#include "dispatcheraction.h"

//ToolsMenu::ToolsMenu(QWidget *parent) :
//  QMenu(parent)
//{
//}
/**
 * Create a "Tools" menu containing the Jmri system-independent tools
 * <P>
 * As a best practice, we are migrating the action names (constructor arguments)
 * out of this class and into the contructors themselves.
 *
 * @author	Bob Jacobsen Copyright 2003, 2008
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28746 $
 */
// /*public*/ class ToolsMenu extends JMenu {

/**
 *
 */
//private static final long serialVersionUID = -2981121278089960823L;

/*public*/ ToolsMenu::ToolsMenu(QString name, QWidget *parent) :
  QMenu(name, parent)
{
    //this();
    //setText(name);
 common();
}


/*protected*/ void ToolsMenu::doPreferences()
{
 ((TabbedPreferencesAction*) prefsAction)->actionPerformed();
}

/*public*/ ToolsMenu::ToolsMenu(QWidget *parent) :
  QMenu(tr("Tools"),parent)
{

// super();

// setText(tr("MenuTools"));
 common();
}

void ToolsMenu::common()
{

 QMenu* programmerMenu = new QMenu(tr("Programmers"));
 programmerMenu->addAction(new SimpleProgAction((QObject*)this));
 programmerMenu->addAction(new PaneProgAction(tr("Service-Mode Programmer"),this));
 programmerMenu->addAction(new PaneOpsProgAction(tr("Ops-Mode Programmer"),this));
 programmerMenu->addAction(new DualDecoderToolAction(this));
 addMenu(programmerMenu);

 // disable programmer menu if there's no programmer manager
 if (InstanceManager::programmerManagerInstance() == NULL) {
     programmerMenu->setEnabled(false);
 }

 QMenu* tableMenu = new QMenu(tr("Tables"));
 //tableMenu->addMenu(tableMenu);
 tableMenu->addAction(new ListedTableAction(tr("Turnouts"), "jmri.jmrit.beantable.TurnoutTableTabAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Sensors"), "jmri.jmrit.beantable.SensorTableTabAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Lights"), "jmri.jmrit.beantable.LightTableTabAction",this));
 QMenu* signalMenu = new QMenu(tr("Signals"));
 signalMenu->addAction(new ListedTableAction(tr("Signal Heads"), "jmri.jmrit.beantable.SignalHeadTableAction",this));
 signalMenu->addAction(new ListedTableAction(tr("Signal Masts"), "jmri.jmrit.beantable.SignalMastTableAction",this));
 signalMenu->addAction(new ListedTableAction(tr("Signal Groups"), "jmri.jmrit.beantable.SignalGroupTableAction",this));
 signalMenu->addAction(new ListedTableAction(tr("Signal Mast Logic"), "jmri.jmrit.beantable.SignalMastLogicTableAction",this));
 tableMenu->addMenu(signalMenu);
 tableMenu->addAction(new ListedTableAction(tr("Reporters"), "jmri.jmrit.beantable.ReporterTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Memory Variables"), "jmri.jmrit.beantable.MemoryTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Routes"), "jmri.jmrit.beantable.RouteTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("LRoutes"), "jmri.jmrit.beantable.LRouteTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Logix"), "jmri.jmrit.beantable.LogixTableAction",this));
 tableMenu->addAction(new OBlockTableAction(tr("Occupancy Blocks"),this));
 tableMenu->addAction(new ListedTableAction(tr("Blocks"), "jmri.jmrit.beantable.BlockTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Sections"), "jmri.jmrit.beantable.SectionTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Transits"), "jmri.jmrit.beantable.TransitTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Audio"), "jmri.jmrit.beantable.AudioTableAction",this));
 tableMenu->addAction(new ListedTableAction(tr("Id Tags"), "jmri.jmrit.beantable.IdTagTableAction",this));
 addMenu(tableMenu);
 LightTableTabAction* ta = new LightTableTabAction(this);
addAction(ta);

 QMenu* throttleMenu = new QMenu(tr("Throttles"));
 throttleMenu->addAction(new ThrottleCreationAction(tr("New Throttle"),(WindowInterface*)this));
 throttleMenu->addAction(new ThrottlesListAction(tr("Throttles List Window"),this));
 throttleMenu->addSeparator();
#if 0
 throttleMenu.add(new StoreXmlThrottlesLayoutAction(tr("MenuItemSaveThrottleLayout")));
 throttleMenu.add(new LoadXmlThrottlesLayoutAction(tr("MenuItemLoadThrottleLayout")));
 throttleMenu.addSeparator();
 throttleMenu.add(new StoreDefaultXmlThrottlesLayoutAction(tr("MenuItemSaveAsDefaultThrottleLayout")));
 throttleMenu.add(new LoadDefaultXmlThrottlesLayoutAction(tr("MenuItemLoadDefaultThrottleLayout")));
 //throttleMenu.addSeparator();
 //throttleMenu.add(new jmri.jmrit.throttle.ThrottlesPreferencesAction(tr("MenuItemThrottlesPreferences"))); // now in tabbed preferences
 throttleMenu.add(new JSeparator());
 throttleMenu.add(new jmri.jmrit.withrottle.WiThrottleCreationAction(tr("MenuItemStartWiThrottle")));
#endif
 addMenu(throttleMenu);


 // disable the throttle menu if there is no throttle Manager
 if (InstanceManager::throttleManagerInstance() == NULL)
 {
  throttleMenu->setEnabled(false);
 }

 QAction* consistAction = new ConsistToolAction(tr("Consisting Tool..."),this);

 addAction(consistAction);

 // disable the consist tool if there is no consist Manager
 if (InstanceManager::getDefault("ConsistManager") == NULL)
 {
  consistAction->setEnabled(false);
 }

 QMenu* clockMenu = new QMenu(tr("Clocks"));
 clockMenu->addAction(new SimpleClockAction(tr("Setup Fast Clock..."),this));
 clockMenu->addAction(new NixieClockAction(tr("Nixie Clock"), this));
 clockMenu->addAction(new LcdClockAction(tr("Lcd Clock"), this));
 clockMenu->addAction(new AnalogClockAction(tr("Analog Clock"),this));

 addMenu(clockMenu);

 addSeparator();

 addAction(new PowerPanelAction(tr("Power Control..."),this));
 addAction(new SimpleTurnoutCtrlAction(tr("Turnout Control..."),this));
 addAction(new BlockBossAction(tr("Simple Signal Logic"),this));
 addAction(new SensorGroupAction(tr("Sensor Groups..."),this));
 addAction(new SpeedometerAction(tr("Speedometer..."),this));
 addAction(new SimpleLightCtrlAction(tr("Light Control..."),this));
#if 1
 addAction(new DispatcherAction(tr("Dispatcher..."),this));
#endif
 addSeparator();

 addAction(new SendPacketAction(tr("Send DCC Packet"),this));

 addSeparator();
#if 0
 // US&S CTC subsystem tools
 addMenu(new jmri.jmrit.ussctc.ToolsMenu());
#endif
 // operations menu
 addMenu(new OperationsMenu());
#if 0
 add(new JSeparator());
 // add start web server
 addMenu(new jmri.web.server.WebServerAction());
#endif
}


