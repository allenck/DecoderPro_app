#include "pr4selectpane.h"

Pr4SelectPane::Pr4SelectPane(QWidget* parent)
 : Pr3SelectPane(parent)
{

}
/**
 * Pane for downloading software updates to PRICOM products
 *
 * @author Bob Jacobsen Copyright (C) 2005
 */
// class Pr4SelectPane extends jmri.jmrix.loconet.pr3.swing.Pr3SelectPane {

    //@Override
    /*public*/ QString Pr4SelectPane::getHelpTarget() {
        return "package.jmri.jmrix.loconet.pr4.swing.Pr4Select"; // NOI18N
    }

    //@Override
    /*public*/ QString Pr4SelectPane::getTitle() {
        return tr("MenuItemPr4ModeSelect");
    }
#if 0
    /**
     * Nested class to create one of these using old-style defaults
     */
    static public class Default extends jmri.jmrix.loconet.swing.LnNamedPaneAction {

        public Default() {
            super(Bundle.getMessage("MenuItemPr4ModeSelect"),
                    new jmri.util.swing.sdi.JmriJFrameInterface(),
                    Pr4SelectPane.class.getName(),
                    jmri.InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
        }
    }
#endif
//    private final static Logger log = LoggerFactory.getLogger(Pr4SelectPane.class);


