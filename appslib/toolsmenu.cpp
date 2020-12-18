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
#include "withrottlecreationaction.h"
#include "webserveraction.h"
#include "storexmlthrottleslayoutaction.h"
#include "storedefaultxmlthrottleslayoutaction.h"
#include "loadxmlthrottleslayoutaction.h"
#include "loaddefaultxmlthrottleslayoutaction.h"
//#include "ampmeteraction.h"
#include "cabsignalaction.h"
#include "whereusedaction.h"
#include "timetable/timetableaction.h"
#include "servermenu.h"
#include "pragotronclockaction.h"
#include "meteraction.h"
#include "ctc/ctceditoraction.h"
#include "ctc/ctcrunaction.h"

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
 if (InstanceManager::getNullableDefault("AddressedProgrammerManager") == nullptr
         && InstanceManager::getNullableDefault("GlobalProgrammerManager") == nullptr) {
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
 throttleMenu->addAction(new StoreXmlThrottlesLayoutAction(tr("Save Throttle Layout"),this));
 throttleMenu->addAction(new LoadXmlThrottlesLayoutAction(tr("Open Throttles Layout..."),this));
 throttleMenu->addSeparator();
 throttleMenu->addAction(new StoreDefaultXmlThrottlesLayoutAction(tr("Save As Default Throttles Layout"),this));
 throttleMenu->addAction(new LoadDefaultXmlThrottlesLayoutAction(tr("Load Default Throttles Layout"),this));
 //throttleMenu.addSeparator();
 //throttleMenu.add(new jmri.jmrit.throttle.ThrottlesPreferencesAction(tr("MenuItemThrottlesPreferences"))); // now in tabbed preferences
 throttleMenu->addSeparator();
 throttleMenu->addAction(new WiThrottleCreationAction(tr("Start WiThrottle"),this));
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
 clockMenu->addAction(new PragotronClockAction(tr("Pragotron Clock"),this));

 addMenu(clockMenu);

 addSeparator();
 // single-pane tools
 addAction(new PowerPanelAction(tr("Power Control..."),this));
 addAction(new SimpleTurnoutCtrlAction(tr("Turnout Control..."),this));
 addAction(new SimpleLightCtrlAction(tr("Light Control..."),this));
 addAction(new SpeedometerAction(tr("Speedometer..."),this));
 //addAction(new AmpMeterAction(tr("Amp Meter"),this));
 addAction(new MeterAction(tr("Voltage / Current meter"),this));
 addAction(new SensorGroupAction(tr("Sensor Groups..."),this));
 addAction(new BlockBossAction(tr("Simple Signal Logic"),this));
 addAction(new SendPacketAction(tr("Send DCC Packet"),this));

 addSeparator();
 // more complex multi-window tools
 addMenu(new OperationsMenu());
 addAction(new DispatcherAction(tr("Dispatcher..."),this));
 addAction(new TimeTableAction(tr("Timetable"), this));
 addAction(new WhereUsedAction(tr("Where Used"), this));
 // CTC menu item with submenus
#if 1
 QMenu* ctcMenu = new QMenu(tr("CTC"));
 ctcMenu->addAction(new CtcEditorAction(tr("Open CTC Configuration Editor."),this));
 ctcMenu->addAction(new CtcRunAction(tr("Run CTC"),this));
 addMenu(ctcMenu);
 // US&S CTC subsystem tools
 //add(new jmri.jmrit.ussctc.ToolsMenu());
#endif
         // add cab signals
 addAction(new CabSignalAction(this));
 addSeparator();
 // add start web server
 addAction(new WebServerAction(this));
 // add the server menu
 addMenu(new ServerMenu());
}


