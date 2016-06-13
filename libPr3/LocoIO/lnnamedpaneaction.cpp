#include "lnnamedpaneaction.h"
#include "loconetsystemconnectionmemo.h"
#include "windowinterface.h"
#include "lnpanelinterface.h"

LnNamedPaneAction::LnNamedPaneAction(QObject *parent) :
  JmriNamedPaneAction(parent)
{
 log = new Logger("LnNamedPaneAction");
}
/**
 * Action to create and load a JmriPanel from just its name.
 *
 * @author	Bob Jacobsen Copyright (C) 2010
 * @version	$Revision: 28746 $
 */
///*public*/ class LnNamedPaneAction extends jmri.util.swing.JmriNamedPaneAction {

//    /**
//     *
//     */
//    private static final long serialVersionUID = 3189519475374368759L;

/**
 * Enhanced constructor for placing the pane in various GUIs
 */
/*public*/ LnNamedPaneAction::LnNamedPaneAction(QString s, WindowInterface* wi, QString paneClass, LocoNetSystemConnectionMemo* memo)
 : JmriNamedPaneAction(s, wi, paneClass)
{
 //super(s, wi, paneClass);
 this->memo = memo;
 log = new Logger("LnNamedPaneAction");
}

/*public*/ LnNamedPaneAction::LnNamedPaneAction(QString s, QIcon i, WindowInterface* wi, QString paneClass, LocoNetSystemConnectionMemo* memo)
 : JmriNamedPaneAction(s, i, wi, paneClass)
{
 //super(s, i, wi, paneClass);
 this->memo = memo;
 log = new Logger("LnNamedPaneAction");
}


/*public*/ JmriPanel* LnNamedPaneAction::makePanel()
{
 JmriPanel* p = JmriNamedPaneAction::makePanel();
 if (p == NULL)
 {
  return NULL;
 }

 //try {
 ((LnPanelInterface*) p)->initComponents(memo);
//     return p;
// } catch (Exception ex) {
 if(p == NULL)
 {
  log->warn("could not init pane class: " + paneClass /*+ " due to:" + ex.getMessage()*/);
     //ex.printStackTrace();
 }

 return p;
}
