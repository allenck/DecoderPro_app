#include "jmrisrcpserveraction.h"
#include "jmrisrcpservermanager.h"
#include "jmrisrcpserver.h"

/**
 * Swing action to create and register a JmriSRCPServerControlFrame object
 *
 * @author Paul Bender Copyright (C) 2009
 */
// /*public*/ class JmriSRCPServerAction extends AbstractAction {

/*public*/ JmriSRCPServerAction::JmriSRCPServerAction(QString s, QWidget* parent)
 :  AbstractAction(s, parent)
{
    //super(s);
 connect(this,SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ JmriSRCPServerAction::JmriSRCPServerAction(QWidget* parent)
: AbstractAction(tr("Start SRCP Jmri Server"), parent) {
   // this("Start SRCP Jmri Server");
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void JmriSRCPServerAction::actionPerformed(/*ActionEvent e*/) {

    //JmriSRCPServerFrame f = new JmriSRCPServerFrame();
    //f.setVisible(true);
    JmriSRCPServerManager::getInstance()->getServer()->start();
}

