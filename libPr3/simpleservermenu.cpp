#include "simpleservermenu.h"
#include "simpleserveraction.h"
/**
 * Create a "JMRI Simple Server" menu containing the Server interface to the
 * JMRI system-independent tools
 *
 * @author Paul Bender Copyright 2009
 */
///*public*/ class SimpleServerMenu extends JMenu {

/*public*/ SimpleServerMenu::SimpleServerMenu(QString name, QWidget* parent)  : QMenu(parent){
    //this();
    setTitle(name);
}

/*public*/ SimpleServerMenu::SimpleServerMenu(QWidget* parent) : QMenu(parent) {

    //super();

    //ResourceBundle rb = ResourceBundle.getBundle("jmri.jmris.simpleserver.SimpleServerBundle");

    setTitle(tr("Simple Server"));
    addAction(new SimpleServerAction(tr("Start Server"),parent));

}
