#include "simpleserveraction.h"
#include "simpleservermanager.h"
#include "simpleserver.h"

/**
 * Swing action to create and register a SimpleServerControlFrame object
 *
 * @author Paul Bender Copyright (C) 2010
 */
///*public*/ class SimpleServerAction extends AbstractAction {

/*public*/ SimpleServerAction::SimpleServerAction(QString s, QObject *parent)  :
AbstractAction(s, parent){
    //super(s);
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ SimpleServerAction::SimpleServerAction(QObject *parent) : AbstractAction("Start Simple Jmri Server", parent) {
    //this("Start Simple Jmri Server");
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void SimpleServerAction::actionPerformed(JActionEvent *e) {

    // SimpleServerFrame f = new SimpleServerFrame();
    // f.setVisible(true);
    SimpleServerManager::getInstance()->getServer()->start();
}
