#include "sprogmenu.h"
#include "sprogconsoleaction.h"
#include "sprogversionaction.h"
#include "sprogpacketgenaction.h"
#include "sprogmonaction.h"
#include "sprogiiupdateaction.h"

using namespace Sprog;
/**
 * Create a Systems menu containing the Jmri SPROG-specific tools.
 *
 * @author Bob Jacobsen Copyright 2003
 */
///*public*/ class SPROGMenu extends JMenu {

/*public*/ SPROGMenu::SPROGMenu(SprogSystemConnectionMemo* memo, QWidget* frame) : Menu(){
    //super();

    if (memo != NULL) {
        setTitle(memo->getUserName());
    } else {
        setTitle("Sprog");
    }

    if (memo != NULL) {

        addAction(new SprogMonAction(tr("Monitor %1").arg("SPROG"), memo, frame));
        addAction(new SprogPacketGenAction(tr("Enter command as ASCII string (hex input not yet available)"), memo, frame));
        addAction(new SprogConsoleAction(tr("Sprog Console"), memo,frame));
        addSeparator();
        addAction(new SprogVersionAction(tr("Get Sprog Firmware Version"), memo,frame));
        // Removed to avoid confusion with newer SPROG II and 3 that have now reached v3 and v4:
        //add(new jmri.jmrix.sprog.update.Sprogv4UpdateAction(Bundle.getMessage("SprogXFirmwareUpdate", " v3/v4"), memo));
        addAction(new SprogIIUpdateAction(tr("Sprog%1 Firmware Update").arg("II/SPROG 3"), memo, frame));
    }
}
