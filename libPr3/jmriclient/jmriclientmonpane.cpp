#include "jmriclientmonpane.h"
#include "jmriclienttrafficcontroller.h"
#include "jmriclientreply.h"
/**
 * Pane displaying (and logging) JMRIClient command messages
 *
 * @author Bob Jacobsen Copyright (C) 2008
  */
// /*public*/ class JMRIClientMonPane extends jmri.jmrix.AbstractMonPane implements JMRIClientListener {


/*public*/ JMRIClientMonPane::JMRIClientMonPane(QWidget* parent) : AbstractMonPane(parent) {
    //super();
}

//@Override
/*public*/ QString JMRIClientMonPane::getTitle() {
    return tr("Jmri Client CommandMonitor");
}

//@Override
/*protected*/ void JMRIClientMonPane::init() {
}

//@Override
/*public*/ void JMRIClientMonPane::initContext(QObject* context)
{
 if (qobject_cast<JMRIClientSystemConnectionMemo*>(context))
 {
     JMRIClientSystemConnectionMemo* memo = (JMRIClientSystemConnectionMemo*) context;
     // connect to TrafficController
     tc = memo->getJMRIClientTrafficController();
     tc->addJMRIClientListener((JMRIClientListener*)this);
 }
}

//@Override
/*public*/ void JMRIClientMonPane::dispose() {
    tc->removeJMRIClientListener((JMRIClientListener*)this);
    tc = nullptr;
AbstractMonPane::dispose();
}

//@Override
/*public*/ /*synchronized*/ void JMRIClientMonPane::message(AbstractMRMessage* l, AbstractMRListener* listener) {  // receive a message and log it
    logMessage("cmd: ", (Message*)l);
}

//@Override
/*public*/ /*synchronized*/ void JMRIClientMonPane::reply(AbstractMRMessage* l) {  // receive a reply message and log it
    logMessage("rep: ",l);
}

/**
 * Nested class to create one of these using old-style defaults
 */
///*static*/ /*public*/ class Default extends jmri.util.swing.JmriNamedPaneAction {

//    /*public*/ Default() {
//        super(Bundle.getMessage("MenuItemJmriClientCommandMonitorTitle"), JMRIClientMonPane.class.getName());
//        setContext(jmri.InstanceManager.
//                getDefault(JMRIClientSystemConnectionMemo.class));
//    }
//}
