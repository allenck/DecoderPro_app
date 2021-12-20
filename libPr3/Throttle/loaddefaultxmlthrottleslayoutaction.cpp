#include "loaddefaultxmlthrottleslayoutaction.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include "loadxmlthrottleslayoutaction.h"
#include "throttlewindow.h"
#include "throttleframemanager.h"
#include "file.h"

/**
 * Create a new throttle.
 *
 * @author Lionel Jeanson Copyright 2009
 */
///*public*/ class LoadDefaultXmlThrottlesLayoutAction extends JmriAbstractAction {

/*public*/ LoadDefaultXmlThrottlesLayoutAction::LoadDefaultXmlThrottlesLayoutAction(QString s, WindowInterface* wi) : JmriAbstractAction(s, wi){
    //super(s, wi);
    // disable the ourselves if there is no throttle Manager
    if (InstanceManager::getNullableDefault("ThrottleManager") == nullptr) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ LoadDefaultXmlThrottlesLayoutAction::LoadDefaultXmlThrottlesLayoutAction(QString s, QIcon i, WindowInterface* wi)
 : JmriAbstractAction(s, i, wi)
{
    //super(s, i, wi);
    // disable the ourselves if there is no throttle Manager
 if (InstanceManager::getNullableDefault("ThrottleManager") == nullptr) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ LoadDefaultXmlThrottlesLayoutAction::LoadDefaultXmlThrottlesLayoutAction(QString s, QObject* parent) : JmriAbstractAction(s, parent) {
    //super(s);
    // disable the ourselves if there is no throttle Manager
 if (InstanceManager::getNullableDefault("ThrottleManager") == nullptr) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

/*public*/ LoadDefaultXmlThrottlesLayoutAction::LoadDefaultXmlThrottlesLayoutAction( QObject* parent)
 : JmriAbstractAction(tr("Load default throttle layout..."), parent)
{
    //this("Load default throttle layout...");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * The action is performed. Create a new ThrottleFrame.
 *
 * @param e The event causing the action.
 */
//@Override
/*public*/ void LoadDefaultXmlThrottlesLayoutAction::actionPerformed(JActionEvent *) {
    // load throttle preference
    LoadXmlThrottlesLayoutAction* lxta = new LoadXmlThrottlesLayoutAction(parent());
    try {
        if (lxta->loadThrottlesLayout(new File(ThrottleWindow::getDefaultThrottleFilename()))) {
            return;
        }
    } catch (IOException ex) {
        log->error("No default throttle layout, creating an empty throttle window");
    }
    // need to create a new one
    ThrottleWindow* tf = ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->createThrottleFrame();
    tf->toFront();
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* LoadDefaultXmlThrottlesLayoutAction::log = LoggerFactory::getLogger("ThrottleCreationAction");

//@Override
/*public*/ JmriPanel* LoadDefaultXmlThrottlesLayoutAction::makePanel() {
    throw  IllegalArgumentException("Should not be invoked");
}
