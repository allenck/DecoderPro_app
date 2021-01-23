#include "loconetmenu.h"
#include "loconetsystemconnectionmemo.h"
#include "windowinterface.h"
#include "jmrijframeinterface.h"
#include "../libPr3/LocoIO/lnnamedpaneaction.h"
#include "locoiodata.h"
#include "locoiomodules.h"
#include "../libPr3/loconet/lntcpserveraction.h"
#include "locoiomodules.h"
#include "startupactionmodelutil.h"

//LocoNetMenu::LocoNetMenu(QWidget *parent) :
//  QMenu(parent)
//{
//}
/**
 * Create a "Systems" menu containing the Jmri LocoNet-specific tools.
 *
 * @author	Bob Jacobsen Copyright 2003, 2010
 * @version $Revision: 28746 $
 */
// /*public*/ class LocoNetMenu extends JMenu {
LocoNetMenu* LocoNetMenu::_instance = nullptr;
/*public*/ LocoNetMenu* LocoNetMenu::instance(LocoNetSystemConnectionMemo* memo, QWidget* parent)
{
 if(_instance == nullptr)
  _instance = new LocoNetMenu(memo, parent);
 return _instance;
}
/*public*/ LocoNetMenu* LocoNetMenu::instance()
{
 return _instance;
}
/**
 *
 */
//private static final long serialVersionUID = 5699192434035288187L;

/**
 * Create a LocoNet menu. Preloads the TrafficController to certain actions.
 * Actions will open new windows.
 */
// Need to Sort out the Loconet server menu items;
/*public*/ LocoNetMenu::LocoNetMenu(LocoNetSystemConnectionMemo* memo, QWidget *parent) : QMenu(parent)
{
 //super();
 this->parent = parent;
 this->memo = memo;
 if(LocoNetMenu::_instance == nullptr)
  LocoNetMenu::_instance = this;

 //ResourceBundle rb = LocoNetBundle.bundle();

 if (memo != nullptr)
 {
  setTitle(memo->getUserName());
 } else {
  setTitle(tr("LocoNet"));
 }

 WindowInterface* wi = new JmriJFrameInterface(parent);

 panelItems = QList<LocoNetMenuItem*>()
   << new LocoNetMenuItem(tr("Monitor LocoNet"), "jmri.jmrix.loconet.locomon.LocoMonPane")
   << new LocoNetMenuItem(tr("Monitor Slots"), "jmri.jmrix.loconet.slotmon.SlotMonPane")
   << new LocoNetMenuItem(tr("Clock Monitor"), "jmri.jmrix.loconet.clockmon.ClockMonPane")
   << new LocoNetMenuItem(tr("Monitor LocoNet Stats"), "jmri.jmrix.loconet.locostats.LocoStatsPanel")
   << nullptr
   << new LocoNetMenuItem(tr("Configure BDL16/BDL162/BDL168"), "jmri.jmrix.loconet.bdl16.BDL16Panel")
   << new LocoNetMenuItem(tr("Configure LocoIO"), "jmri.jmrix.loconet.locoio.LocoIOPanel")
   << new LocoNetMenuItem(tr("Configure PM4/PM42"), "jmri.jmrix.loconet.pm4.PM4Panel")
   << new LocoNetMenuItem(tr("Configure SE8c"), "jmri.jmrix.loconet.se8.SE8Panel")
   << new LocoNetMenuItem(tr("Configure DS64"), "jmri.jmrix.loconet.ds64.DS64Panel")
   << new LocoNetMenuItem(tr("Configure Command Station"), "jmri.jmrix.loconet.cmdstnconfig.CmdStnConfigPane")
   << new LocoNetMenuItem(tr("Configure LocoNet ID"), "jmri.jmrix.loconet.locoid.LocoIdPanel")
   << new LocoNetMenuItem(tr("Configure Duplex Group"), "jmri.jmrix.loconet.duplexgroup.swing.DuplexGroupTabbedPanel")
   //new Item("Start LocoNet Server",  "jmri.jmrix.loconet.locormi.LnMessageServerPanel"),
   //<< new LocoNetMenuItem("Start LocoNetOverTCP Server","jmri.jmrix.loconet.loconetovertcp.ServerPanel")
   << nullptr
   << new LocoNetMenuItem(tr("Send Throttle Messages"), "jmri.jmrix.loconet.swing.throttlemsg.MessagePanel")
   //<< new LocoNetMenuItem(tr("Send LocoNet Packet"), "jmri.jmrix.loconet.locogen.LocoGenPanel")
   << new LocoNetMenuItem(tr("Send LocoNet Packet"), "LocoNetMsgDialog")
   << new LocoNetMenuItem("Configure LNCV Modules", "jmri.jmrix.loconet.swing.lncvprog.LncvProgPane") // NOI18N
   << new LocoNetMenuItem(tr("Select PR3 Mode"), "jmri.jmrix.loconet.pr3.swing.Pr3SelectPane")
   << nullptr
   << new LocoNetMenuItem(tr("Download Firmware"), "jmri.jmrix.loconet.downloader.LoaderPane")
   << new LocoNetMenuItem(tr("Download Sounds"), "jmri.jmrix.loconet.soundloader.SoundLoaderPane")
   << new LocoNetMenuItem(tr("Edit SPJ Sound File"), "jmri.jmrix.loconet.soundloader.EditorPane")
   << nullptr
   << new LocoNetMenuItem(tr("Query Cv"), "QueryCvDialog");
 LnNamedPaneAction* act;
 foreach (LocoNetMenuItem* item, panelItems)
 {
  if (item == nullptr)
  {
   addSeparator();
  }
  else
  {
   addAction(act = new LnNamedPaneAction((item->name), wi, item->load, memo));
//   if(item->load == "jmri.jmrix.loconet.locomon.LocoMonPane")
//   {
//    act->trigger();
//    //wi->hide();
//   }
   if(item->load == "jmri.jmrix.loconet.locoio.LocoIOPanel")
   {
    addMenu(LocoIOModules::instance()->getMenu());
   }
  }
 }
 addSeparator();
// add(new jmri.jmrix.loconet.locormi.LnMessageServerAction(rb.getString("MenuItemStartLocoNetServer")));
 addAction(new LnTcpServerAction(tr("Start LocoNetOverTCP Server"),this));
QAction* probeAct = new QAction(tr("Probe"), wi);
addAction(probeAct);
connect(probeAct, SIGNAL(triggered()), this, SLOT(on_probeAction()));

#if 0
LocoNetMenuItem[] panelItems = new Item[]{
    new LocoNetMenuItem(tr("MenuItemLocoNetMonitor", "jmri.jmrix.loconet.locomon.LocoMonPane"),
    new LocoNetMenuItem(tr("MenuItemSlotMonitor", "jmri.jmrix.loconet.slotmon.SlotMonPane"),
    new LocoNetMenuItem(tr("MenuItemClockMon", "jmri.jmrix.loconet.clockmon.ClockMonPane"),
    new LocoNetMenuItem(tr("MenuItemLocoStats", "jmri.jmrix.loconet.locostats.LocoStatsPanel"),
    NULL,
    new LocoNetMenuItem(tr("MenuItemBDL16Programmer", "jmri.jmrix.loconet.bdl16.BDL16Panel"),
    new LocoNetMenuItem(tr("MenuItemLocoIOProgrammer", "jmri.jmrix.loconet.locoio.LocoIOPanel"),
    new LocoNetMenuItem(tr("MenuItemPM4Programmer", "jmri.jmrix.loconet.pm4.PM4Panel"),
    new LocoNetMenuItem(tr("MenuItemSE8cProgrammer", "jmri.jmrix.loconet.se8.SE8Panel"),
    new LocoNetMenuItem(tr("MenuItemDS64Programmer", "jmri.jmrix.loconet.ds64.DS64Panel"),
    new LocoNetMenuItem(tr("MenuItemCmdStnConfig", "jmri.jmrix.loconet.cmdstnconfig.CmdStnConfigPane"),
    new LocoNetMenuItem(tr("MenuItemSetID", "jmri.jmrix.loconet.locoid.LocoIdPanel"),
    new LocoNetMenuItem(tr("MenuItemDuplex", "jmri.jmrix.loconet.duplexgroup.swing.DuplexGroupTabbedPanel"),
    //new Item("MenuItemStartLocoNetServer",  "jmri.jmrix.loconet.locormi.LnMessageServerPanel"),
    //new Item("MenuItemLocoNetOverTCPServer","jmri.jmrix.loconet.loconetovertcp.ServerPanel"),
    NULL,
    new LocoNetMenuItem(tr("MenuItemThrottleMessages", "jmri.jmrix.loconet.swing.throttlemsg.MessagePanel"),
    new LocoNetMenuItem(tr("MenuItemSendPacket", "jmri.jmrix.loconet.locogen.LocoGenPanel"),
    new LocoNetMenuItem(tr("MenuItemPr3ModeSelect", "jmri.jmrix.loconet.pr3.swing.Pr3SelectPane"),
    NULL,
    new LocoNetMenuItem(tr("MenuItemDownload", "jmri.jmrix.loconet.downloader.LoaderPane"),
    new LocoNetMenuItem(tr("MenuItemSoundload", "jmri.jmrix.loconet.soundloader.LoaderPane"),
    new LocoNetMenuItem(tr("MenuItemSoundEditor", "jmri.jmrix.loconet.soundloader.EditorPane")
};
#endif
}
//    static class Item {

LocoNetMenuItem::LocoNetMenuItem(QString name, QString load)
{
 this->name = name;
 this->load = load;
}
//        String name;
//        String load;
//    }
//}

void LocoNetMenu::on_probeAction()
{
// LocoIOData* data = new LocoIOData(0x51, 1, memo->getLnTrafficController());
// data->startProbe();
 LocoIOModules::instance()->startProbe();
}
QList<LocoNetMenuItem*> LocoNetMenu::getMenuItems()
{
 return panelItems;
}
