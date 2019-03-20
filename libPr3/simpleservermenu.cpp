#include "simpleservermenu.h"
#include "simpleserveraction.h"
/**
 * Create a "JMRI Simple Server" menu containing the Server interface to the
 * JMRI system-independent tools
 *
 * @author Paul Bender Copyright 2009
 */
///*public*/ class SimpleServerMenu extends JMenu {

/*public*/ SimpleServerMenu::SimpleServerMenu(QString name) {
    //this();
    setTitle(name);
}

/*public*/ SimpleServerMenu::SimpleServerMenu() {

    //super();

    //ResourceBundle rb = ResourceBundle.getBundle("jmri.jmris.simpleserver.SimpleServerBundle");

    setTitle(tr("Simple Server"));
    addAction(new SimpleServerAction(tr("Start Server"),this));

}
