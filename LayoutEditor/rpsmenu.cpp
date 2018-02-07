#include "rpsmenu.h"

/**
 * Create a "RPS" menu containing the Jmri RPS-specific tools.
 *
 * @author	Bob Jacobsen Copyright 2006, 2007, 2008
 */
// /*public*/ class RpsMenu extends JMenu {

/*public*/ RpsMenu::RpsMenu(QString name, QWidget* parent) : QMenu(name, parent) {
//        this();
//        setText(name);
common();
}

/*public*/ RpsMenu::RpsMenu(QWidget* parent) : QMenu("RPS", parent) {

//    super();

//    setText("RPS");  // Product name, not translated.
 common();
}

 void RpsMenu::common()
 {
    // tools that work
#if 0
    add(new jmri.jmrix.rps.rpsmon.RpsMonAction());
    add(new jmri.jmrix.rps.aligntable.AlignTableAction());
    add(new jmri.jmrix.rps.swing.polling.PollTableAction());
    add(new jmri.jmrix.rps.swing.debugger.DebuggerAction());
    add(new jmri.jmrix.rps.trackingpanel.RpsTrackingFrameAction());
    add(new jmri.jmrix.rps.swing.soundset.SoundSetAction());

    add(new JSeparator());

    // old, obsolete or not updated tools
    add(new jmri.jmrix.rps.reversealign.AlignmentPanelAction());
#endif
}
