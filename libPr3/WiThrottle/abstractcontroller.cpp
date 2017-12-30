#include "abstractcontroller.h"
#include "manager.h"
#include "controllerinterface.h"
#include <QVector>

AbstractController::AbstractController(QObject *parent) : QObject(parent)
{
 listeners = NULL;
}
/**
 * Abstract for controllers that want to recieve or send communications to a
 * connected wi-fi device.
 *
 *
 * @author Brett Hoffman Copyright (C) 2010
 */
//abstract /*public*/ class AbstractController {



/**
 * Build list only if there are no controller listeners. This way the list
 * is not changed while in use. This should only be called by a subclass of
 * jmri.Manager *Manager can implement specifics in register().
 *
 */
/*public*/ void AbstractController::buildList(Manager* manager) {
    if (sysNameList.isEmpty()) {
        sysNameList = manager->getSystemNameList();
        filterList();   //  To remove unwanted objects
        _register();
        canBuildList = false;
    }

}

/*public*/ void AbstractController::filterList() {
    //  Override to filter by wifiControlled field of turnout or route object.
}

/**
 * If no listeners, clear sysNameList pointer and allow list to be re-built
 * *Manager can implement specifics in deregister().
 */
/*public*/ void AbstractController::checkCanBuildList() {
    if (listeners->isEmpty()) {
        if (!sysNameList .isEmpty()) {
            deregister();
            sysNameList = QStringList();
        }
        canBuildList = true;
    }
}

/**
 * Add a listener to handle: listener.sendPacketToDevice(message);
 *
 */
/*public*/ void AbstractController::addControllerListener(ControllerInterface* listener) {
    if (listeners == NULL) {
        listeners = new QVector<ControllerInterface*>();
    }
    if (!listeners->contains(listener)) {
        listeners->append(listener);
    }
}

/*public*/ void AbstractController::removeControllerListener(ControllerInterface* listener) {
    if (listeners == NULL) {
        return;
    }
    if (listeners->contains(listener)) {
        listeners->removeOne(listener);
    }
    checkCanBuildList();
}
