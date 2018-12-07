#include "rfidmenu.h"
#include "rfidsystemconnectionmemo.h"
#include "windowinterface.h"
#include "jmrijframeinterface.h"
#include "rfidnamedpaneaction.h"

/**
 * Create a "Systems" menu containing the Jmri RFID-specific tools.
 *
 * @author	Bob Jacobsen Copyright 2003, 2006, 2007, 2008
 * @author Matthew Harris Copyright 2011
 * @since 2.11.4
 */
// /*public*/ class RfidMenu extends JMenu {

//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ RfidMenu::RfidMenu(RfidSystemConnectionMemo* memo, QWidget* parent) : QMenu(parent)
{
  panelItems = QList<Item*>() <<
      new Item(tr("%1 Command Monitor").arg("RFID"), "jmri.jmrix.rfid.swing.serialmon.SerialMonPane");

    //super();

    if (memo != nullptr) {
        setTitle(memo->getUserName());
    } else {
        setTitle(tr("System"));
    }

    WindowInterface* wi = new JmriJFrameInterface();

    for (Item* item : panelItems) {
        if (item == nullptr) {
            //add(new JSeparator());
         addSeparator();
        } else {
            addAction(new RfidNamedPaneAction(item->name, wi, item->load, memo)); // NOI18N
        }
    }
}



