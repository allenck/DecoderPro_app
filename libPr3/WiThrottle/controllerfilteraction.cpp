#include "controllerfilteraction.h"
#include "instancemanager.h"
#include "routemanager.h"
#include "turnoutmanager.h"
#include "loggerfactory.h"
#include "controllerfilterframe.h"

/**
 * @author Brett Hoffman Copyright (C) 2010
 */
// /*public*/ class ControllerFilterAction extends AbstractAction {

/*public*/ ControllerFilterAction::ControllerFilterAction(QString name, QObject* parent) : AbstractAction(name,  parent)
{
   // super(name);
    if ((InstanceManager::getNullableDefault("TurnoutManager") == NULL) && (InstanceManager::getNullableDefault("RouteManager") == NULL)) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ ControllerFilterAction::ControllerFilterAction(QObject* parent) : AbstractAction(tr("Routes & Turnouts..."), parent) {
    //this(Bundle.getMessage("MenuMenuFilter"));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

/*public*/ QString ControllerFilterAction::getName() {
    return "jmri.jmrit.withrottle.ControllerFilterFrame";
}

//@Override
/*public*/ void ControllerFilterAction::actionPerformed(ActionEvent* ae) {
    JmriJFrame* frame = new ControllerFilterFrame();
    try {
        frame->initComponents();
        frame->setVisible(true);
    } catch (Exception ex) {
        log->error("Could not create Route & Turnout Filter frame");
    }

}

/*private*/ /*final*/ /*static*/ Logger* ControllerFilterAction::log = LoggerFactory::getLogger("ControllerFilterAction");
