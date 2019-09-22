#include "rpsmenu.h"
#include "rpssystemconnectionmemo.h"

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
 /*public*/ RpsMenu::RpsMenu(RpsSystemConnectionMemo* memo, QWidget* parent) :  QMenu(parent){

         //super();
         if (memo != nullptr) {
             setTitle(memo->getUserName());
         } else {
             setTitle(tr("System"));
         }
         _memo = memo;
 #if 0
         // tools that work
         add(new jmri.jmrix.rps.rpsmon.RpsMonAction(_memo));
         add(new jmri.jmrix.rps.aligntable.AlignTableAction(_memo));
         add(new jmri.jmrix.rps.swing.polling.PollTableAction(_memo));
         add(new jmri.jmrix.rps.swing.debugger.DebuggerAction(_memo));
         add(new jmri.jmrix.rps.trackingpanel.RpsTrackingFrameAction(_memo));
         add(new jmri.jmrix.rps.swing.soundset.SoundSetAction(_memo));

         add(new JSeparator());

         // old, obsolete or not updated tools
         add(new jmri.jmrix.rps.reversealign.AlignmentPanelAction(_memo));
#endif
     }
