#include "withrottlecreationaction.h"
#include "instancemanager.h"
#include "userinterface.h"
//WiThrottleCreationAction::WiThrottleCreationAction()
//{

//}
/**
 * WiThrottle GUI
 *
 * @author Brett Hoffman Copyright (C) 2009
 *
 */
// /*public*/ class WiThrottleCreationAction extends JmriAbstractAction {

/*public*/ WiThrottleCreationAction::WiThrottleCreationAction(QString s, WindowInterface* wi)
    : JmriAbstractAction(s,wi)
{
    //super(s, wi);
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ WiThrottleCreationAction::WiThrottleCreationAction(QString s, QIcon i, WindowInterface* wi)
    : JmriAbstractAction(s, i,wi)
{
    //super(s, i, wi);
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

/*static*/ UserInterface* WiThrottleCreationAction::UI = NULL;

/**
 * Create a new network server.
 *
 * @param name Labels frame in GUI
 */
/*public*/WiThrottleCreationAction::WiThrottleCreationAction(QString name, QObject* parent)
    : JmriAbstractAction(name, parent)
{
    //super(name);
    if (InstanceManager::getNullableDefault("ThrottleManager") == NULL) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

/**
 * Create a new network server.
 */
/*public*/ WiThrottleCreationAction::WiThrottleCreationAction(QObject* parent) : JmriAbstractAction(tr("Start WiThrottle Server"),parent)
{
    //this(Bundle.getMessage("MenuStartWiThrottleServer"));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

/**
 * Start the server end of WiThrottle.
 *
 * @param e The event causing the action.
 */
//@Override
/*public*/ void WiThrottleCreationAction::actionPerformed(ActionEvent* e) {
//    GraphicsEnvironment.getLocalGraphicsEnvironment();
    // create GUI, unless running in headless mode
//    if (!GraphicsEnvironment.isHeadless()) {
        //start the normal GUI interface and server
        if (UI == NULL) {    //  Only allow one to be created
            UI = new UserInterface();
        } else {
            //Jeffrey Machacek added to re-show UI after first closing.
            UI->setVisible(true);
        }
//    } else {
//        new FacelessServer(); // start server thread with no UI
//    }
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* WiThrottleCreationAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
