#include "jmrisrcpservermenu.h"
#include "jmrisrcpserveraction.h"

/**
 * Create a "JMRI SRCP Server" menu containing the Server interface to the JMRI
 * system-independent tools
 *
 * @author Paul Bender Copyright 2009
 */
//public class JmriSRCPServerMenu extends JMenu {

/*public*/ JmriSRCPServerMenu::JmriSRCPServerMenu(QString name, QWidget* parent) : QMenu(parent) {
    common();
    setTitle(name);
}

/*public*/ JmriSRCPServerMenu::JmriSRCPServerMenu(QWidget *parent) : QMenu(parent) {

    common();
}
void JmriSRCPServerMenu::common()
{

   // ResourceBundle rb = ResourceBundle.getBundle("jmri.jmris.srcp.JmriSRCPServerBundle");

    setTitle(tr("Server"));
    addAction(new JmriSRCPServerAction(("Start Server"),this));

}
