#include "locomonpane.h"
#include "loconetsystemconnectionmemo.h"
#include "llnmon.h"

/*static*/ LocoMonPane* LocoMonPane::_instance = NULL;

LocoMonPane::LocoMonPane(QWidget *parent) :
    AbstractMonPane(parent)
{
 llnmon = new LlnMon();
 log = new Logger("LocoMonPane");
 memo = NULL;
 _instance = this;
}
/**
 * LocoNet Monitor pane displaying (and logging) LocoNet messages
 * @author	   Bob Jacobsen   Copyright (C) 2001, 2008, 2010
 * @version   $Revision: 22622 $
 */
// /*public*/ class LocoMonPane extends jmri.jmrix.AbstractMonPane implements LocoNetListener, LnPanelInterface {

///*public*/ LocoMonPane() {
//    super();
//}

LocoMonPane::~LocoMonPane()
{
 dispose();
}
void LocoMonPane::closeEvent(QCloseEvent *)
{
 dispose();
}

/*public*/ QString LocoMonPane::getHelpTarget() { return "package.jmri.jmrix.loconet.locomon.LocoMonFrame"; }

/*public*/ QString LocoMonPane::getTitle()
{
 QString uName = "";
 if (memo!=NULL)
 {
  uName = memo->getUserName();
  if ("LocoNet" != (uName))
  {
   uName = uName+": ";
  }
  else
  {
   uName = "";
  }
 }
 return uName+tr("Monitor LocoNet");
}

/*public*/ void LocoMonPane::dispose()
{
 if(memo->getLnTrafficController()!=NULL)
 {
  // disconnect from the LnTrafficController
//        memo->getLnTrafficController()->removeLocoNetListener(~0,this);
  disconnect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 // and unwind swing
 AbstractMonPane::dispose();
}

/*public*/ void LocoMonPane::init() {}


/*public*/ void LocoMonPane::initContext(QObject* context) throw (Exception)
{
 //if (context instanceof LocoNetSystemConnectionMemo )
 if(qobject_cast<LocoNetSystemConnectionMemo*>(context) != NULL)
 {
  initComponents((LocoNetSystemConnectionMemo*) context);
 }
}

/*public*/ void LocoMonPane::initComponents(LocoNetSystemConnectionMemo* memo)
{
 this->memo = memo;
 // connect to the LnTrafficController
 if(memo->getLnTrafficController()==NULL)
 {
  log->error("No traffic controller is available");
  return;
 }
 //memo->getLnTrafficController()->addLocoNetListener(~0, this);
 connect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 if(memo->provides("TurnoutManager"))
  llnmon->setLocoNetTurnoutManager((LnTurnoutManager*)memo->get("TurnoutManager"));
 if(memo->provides("SensorManager"))
  llnmon->setLocoNetSensorManager((LnSensorManager*)memo->get("SensorManager"));
 if(memo->provides("ReporterManager"))
  llnmon->setLocoNetReporterManager((LnReporterManager*)memo->get("ReporterManager"));
 //AbstractMonPane::initComponents();
}


/*public*/ /*synchronized*/ void LocoMonPane::message(LocoNetMessage* l)
{  // receive a LocoNet message and log it
 // send the raw data, to display if requested
 QString raw = l->toString();

 // display the decoded data
 // we use Llnmon to format, expect it to provide consistent \n after each line
 nextLine(llnmon->displayMessage(*l), raw );
}

LocoMonPane* LocoMonPane::instance() { return _instance; }
#if 0
/**
 * Nested class to create one of these using old-style defaults
 */
static /*public*/ class Default extends jmri.jmrix.loconet.swing.LnNamedPaneAction {
    /*public*/ Default() {
        super(LocoNetBundle.bundle().getString("MenuItemLocoNetMonitor"),
            new jmri.util.swing.sdi.JmriJFrameInterface(),
            LocoMonPane.class.getName(),
            jmri.InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
    }
}
#endif
