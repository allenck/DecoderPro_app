#include "sprogcsmenu.h"
#include "sprogversionaction.h"
#include "sprogconsoleaction.h"
#include "sprogpacketgenaction.h"
#include "sprogmonaction.h"
#include "sprogiiupdateaction.h"
#include "sprogslotmonaction.h"

using namespace Sprog;

/**
 * Create a Systems menu containing the Jmri SPROG-specific tools.
 *
 * @author	Andrew Crosland Copyright 2006
 */
///*public*/ class SPROGCSMenu extends JMenu {


/*public*/ SPROGCSMenu::SPROGCSMenu::SPROGCSMenu(SprogSystemConnectionMemo* memo, QWidget* frame) : Menu() {
    //super();
    _memo = memo;

    setTitle(memo->getUserName());
    addAction(new SprogSlotMonAction(tr("Sprog Slot Monitor"), _memo,frame));
    addAction(new SprogMonAction(tr("MonitorX %1").arg("SPROG"), _memo, frame));
    addAction(new SprogPacketGenAction(tr("Enter command as ASCII string (hex input not yet available)"), _memo, frame));

    //add(new jmri.jmrix.sprog.console.SprogConsoleAction(tr("SprogConsoleTitle"), _memo));
    addAction(new SprogConsoleAction(tr("SPROG Console"),memo, frame));

    addSeparator();
//    add(new jmri.jmrix.sprog.update.SprogVersionAction(tr("GetSprogFirmwareVersion"), _memo));
    addAction(new SprogVersionAction(tr("Get SPROG Firmware Version"), _memo, frame));
#if 0
    add(new jmri.jmrix.sprog.update.Sprogv4UpdateAction(tr("SprogXFirmwareUpdate", " v3/v4"), _memo));
#endif
    addAction(new SprogIIUpdateAction(tr("Sprog%1 Firmware Update").arg(" II"), _memo, frame));

}

