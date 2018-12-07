#include "rfidnamedpaneaction.h"
#include "loggerfactory.h"
#include "rfidsystemconnectionmemo.h"
#include "rfidpanelinterface.h"

/**
 * Action to create and load a JmriPanel from just its name.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
///*public*/ class RfidNamedPaneAction extends jmri.util.swing.JmriNamedPaneAction {

/**
 * Enhanced constructor for placing the pane in various GUIs
 */
/*public*/ RfidNamedPaneAction::RfidNamedPaneAction(QString s, WindowInterface* wi, QString paneClass, RfidSystemConnectionMemo* memo) : JmriNamedPaneAction(s, wi, paneClass)
{
    //super(s, wi, paneClass);
    this->memo = memo;
}

/*public*/ RfidNamedPaneAction::RfidNamedPaneAction(QString s, QIcon i, WindowInterface* wi, QString paneClass, RfidSystemConnectionMemo* memo) : JmriNamedPaneAction(s, i, wi, paneClass)
{
    //super(s, i, wi, paneClass);
    this->memo = memo;
}


//@Override
/*public*/ JmriPanel* RfidNamedPaneAction::makePanel() {
    JmriPanel* p = JmriNamedPaneAction::makePanel();
    if (p == nullptr) {
        return nullptr;
    }

    try {
        ((RfidPanelInterface*) p)->initComponents(memo);
        return p;
    } catch (Exception ex) {
        log->warn(tr("could not init pane class: %1").arg(paneClass)+ ex.getMessage());
    }

    return p;
}

/*private*/ /*static*/ /*final*/ Logger* RfidNamedPaneAction::log = LoggerFactory::getLogger("RfidNamedPaneAction");


