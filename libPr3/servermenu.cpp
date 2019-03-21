#include "servermenu.h"
#include "simpleservermenu.h"
#include "jmrisrcpservermenu.h"
/**
 * Create a "Server" menu containing the Server interface to the JMRI
 * system-independent tools
 *
 * @author Paul Bender Copyright 2010
 */
// /*public*/ class ServerMenu extends JMenu {

/*public*/ ServerMenu::ServerMenu(QString name, QWidget* parent) : QMenu(parent){
    //this();
    setTitle(name);
}

/*public*/ ServerMenu::ServerMenu(QWidget* parent) {

    //super();

    //ResourceBundle rb = ResourceBundle.getBundle("jmri.jmris.JmriServerBundle");

    setTitle(tr("Server"));
    // This first menu item is for connection testing only.
    // It provides no parsing.
    //add(new jmri.jmris.JmriServerAction(rb.getString("MenuItemStartServer")));
    addMenu(new SimpleServerMenu(parent));
    addMenu(new JmriSRCPServerMenu(parent));

}

