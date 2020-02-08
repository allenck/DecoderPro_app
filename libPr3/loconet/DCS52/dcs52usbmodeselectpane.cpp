#include "dcs52usbmodeselectpane.h"

Dcs52UsbModeSelectPane::Dcs52UsbModeSelectPane(QWidget *parent)
 : Pr3SelectPane(parent)
{

}
/**
 * Pane for downloading software updates to PRICOM products
 *
 * @author Bob Jacobsen Copyright (C) 2005
 */
///*public*/ class Dcs52UsbModeSelectPane extends jmri.jmrix.loconet.pr3.swing.Pr3SelectPane {

    //@Override
    /*public*/ QString Dcs52UsbModeSelectPane::getHelpTarget() {
        return "package.jmri.jmrix.loconet.usb_dcs52.swing.Dcs52UsbModeSelect"; // NOI18N
    }

    //@Override
    /*public*/ QString Dcs52UsbModeSelectPane::getTitle() {
        return LnPanel::getTitle(tr("MenuItemUsbDcs52ModeSelect"));
    }
#if 0
    /**
     * Nested class to create one of these using old-style defaults
     */
    static /*public*/ class Default extends jmri.jmrix.loconet.swing.LnNamedPaneAction {

        /*public*/ Default() {
            super(Bundle.getMessage("MenuItemUsbDcs52ModeSelect"),
                    new jmri.util.swing.sdi.JmriJFrameInterface(),
                    Dcs52UsbModeSelectPane.class.getName(),
                    jmri.InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
        }
    }
#endif
