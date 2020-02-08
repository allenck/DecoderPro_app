#include "dcs240usbmodeselectpane.h"

Dcs240UsbModeSelectPane::Dcs240UsbModeSelectPane(QWidget *parent)
 : Pr3SelectPane(parent)
{

}
/**
 * Pane for downloading software updates to PRICOM products
 *
 * @author Bob Jacobsen Copyright (C) 2005
 */
//public class Dcs240UsbModeSelectPane extends jmri.jmrix.loconet.pr3.swing.Pr3SelectPane {

    //@Override
    /*public*/ QString Dcs240UsbModeSelectPane::getHelpTarget() {
        return "package.jmri.jmrix.loconet.usb_dcs240.swing.Dcs240UsbModeSelect"; // NOI18N
    }

    //@Override
    /*public*/ QString Dcs240UsbModeSelectPane::getTitle() {
        return LnPanel::getTitle(tr("UsbDcs240ModeSelect"));
    }
#if 0
    /**
     * Nested class to create one of these using old-style defaults
     */
    static public class Default extends jmri.jmrix.loconet.swing.LnNamedPaneAction {

        public Default() {
            super(Bundle.getMessage("MenuItemUsbDcs240ModeSelect"),
                    new jmri.util.swing.sdi.JmriJFrameInterface(),
                    Dcs240UsbModeSelectPane.class.getName(),
                    jmri.InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
        }
    }
#endif
