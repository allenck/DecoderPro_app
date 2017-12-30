#include "usbviewaction.h"
#include "usbview.h"
#include "exceptions.h"
#include "joptionpane.h"

//UsbViewAction::UsbViewAction()
//{

//}
/**
 * Invoke the UsbView tool from libusb-java.
 *
 * @author Bob Jacobsen Copyright 2008
  */
// /*public*/ class UsbViewAction extends javax.swing.AbstractAction {

/*public*/ UsbViewAction::UsbViewAction(QString s, QObject* parent) :AbstractAction(s, parent) {
    //super(s);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ UsbViewAction::UsbViewAction(QObject* parent) : AbstractAction(tr("USB Device Viewer"), parent)
{
 //this(java.util.ResourceBundle.getBundle("jmri.jmrix.libusb.UsbViewActionBundle").getString("USB_Device_Viewer"));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void UsbViewAction::actionPerformed() {
    // create and display
    try {
        (new UsbView())->setVisible(true);
    } catch (UnsatisfiedLinkError ex) {
        log->error(ex.getMessage());
        JOptionPane::showMessageDialog(NULL, "Unable to find the libusb-win32 package.\nFor more details on how to installed it please check http://www.jmri.org/install/USB.shtml");
    }
}
Logger* UsbViewAction::log = new Logger("UsbViewAction");
