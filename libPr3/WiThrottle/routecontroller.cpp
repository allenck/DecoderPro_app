#include "routecontroller.h"
#include "route.h"
#include "routemanager.h"
#include "logger.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "controllerinterface.h"
#include "defaultroute.h"

//RouteController::RouteController()
//{

//}
/**
 *
 *
 * @author Brett Hoffman Copyright (C) 2010
 */
///*public*/ class RouteController extends AbstractController implements PropertyChangeListener {


/*public*/ RouteController::RouteController()
{
 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");

    manager = (RouteManager*)InstanceManager::getNullableDefault("RouteManager");
    if (manager == NULL) {
        log->info("No route manager instance.");
        isValid = false;
    } else {
        indication = new QHash<NamedBeanHandle<Sensor*>*, Route*>();
        isValid = true;
    }
}

//Override
bool RouteController::verifyCreation() {

    return isValid;
}

//Override
/*public*/ void RouteController::filterList() {
    QStringList tempList = QStringList(0);
    foreach (QString sysName, sysNameList) {
        Route* r = (Route*)manager->getBySystemName(sysName);
        QVariant o = ((DefaultRoute*)r)->getProperty("WifiControllable");
        if ((o == QVariant()) || (o.toString().toLower()!=("false"))) {
            //  Only skip if 'false'
            tempList.append(sysName);
        }
    }
    sysNameList = tempList;
}

//Override
void RouteController::handleMessage(QString message) {
    try {
        if (message.at(0) == 'A') {
            if (message.at(1) == '2') {
                Route* r = (Route*)manager->getBySystemName(message.mid(2));
                if (r != NULL) {
                    r->setRoute();
                } else {
                    log->warn(tr("Message \"%1\" contained invalid system name.").arg(message));
                }
            } else {
                log->warn(tr("Message \"") + message + "\" does not match a route.");
            }
        }
    } catch (NullPointerException exb) {
        log->warn(tr("Message \"") + message + "\" does not match a route.");
    }
}

/**
 * Send Info on routes to devices, not specific to any one route.
 *
 * Format: PRT]\[value}|{routeKey]\[value}|{ActiveKey]\[value}|{InactiveKey
 */
/*public*/ void RouteController::sendTitles() {
    if (listeners == NULL) {
        return;
    }

    QString labels = QString("PRT");    //  Panel Turnout Titles

    labels.append(QString("]\\[") +tr("Route Table") + "}|{Route");
    labels.append(QString("]\\[") + "Active" + "}|{2");
    labels.append(QString("]\\[") + "Inactive" + "}|{4");

    QString message = labels;

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }

}


/**
 * Send list of routes Format:
 * PRL]\[SysName}|{UsrName}|{CurrentState]\[SysName}|{UsrName}|{CurrentState
 *
 * States: 1 - UNKNOWN, 2 - ACTIVE, 4 - INACTIVE (based on turnoutsAligned
 * sensor, if used)
 */
/*public*/ void RouteController::sendList() {
    if (listeners == NULL) {
        return;
    }
    if (canBuildList) {
        buildList(manager);
    }
    if (sysNameList.isEmpty()) {
        return;
    }

    QString list =  QString("PRL");  //  Panel Route List

    foreach (QString sysName, sysNameList) {
        Route* r = (Route*)manager->getBySystemName(sysName);
        list.append(QString("]\\[") + sysName);
        list.append("}|{");
        if (((DefaultRoute*)r)->getUserName() != NULL) {
            list.append(((DefaultRoute*)r)->getUserName());
        }
        list.append("}|{");
        QString turnoutsAlignedSensor = r->getTurnoutsAlignedSensor();
        if (turnoutsAlignedSensor!=("")) {  //only set if found
            try {
                Sensor* routeAligned = InstanceManager::sensorManagerInstance()->provideSensor(turnoutsAlignedSensor);
                list.append(routeAligned->getKnownState());
            } catch (IllegalArgumentException ex) {
                log->warn(tr("Failed to provide turnoutsAlignedSensor \"%1\" in sendList").arg(turnoutsAlignedSensor));
            }
        }

    }
    QString message = list;

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }
}

/**
 * This is on the aligned sensor, not the route itself.
 *
 */
//Override
/*public*/ void RouteController::propertyChange(PropertyChangeEvent* evt) {
    if (evt->getPropertyName()==("KnownState")) {
        Sensor* s = (Sensor*) evt->getSource();
        QListIterator<NamedBeanHandle<Sensor*>*> en(indication->keys());
        while (en.hasNext()) {
            NamedBeanHandle<Sensor*>* namedSensor = en.next();
            if (namedSensor->getBean() == s) {
                Route* r = indication->value(namedSensor);
                QString message = "PRA" + s->getKnownState() + ((DefaultRoute*)r)->getSystemName();

                foreach (ControllerInterface* listener, *listeners) {
                    listener->sendPacketToDevice(message);
                }
                return;
            }
        }
    }
}

/**
 * Register this as a listener of each managed route's aligned sensor
 */
//Override
/*public*/ void RouteController::_register() {
    foreach (QString sysName, sysNameList) {
        Route* r = (Route*)manager->getBySystemName(sysName);
        QString turnoutsAlignedSensor = r->getTurnoutsAlignedSensor();
        if (turnoutsAlignedSensor!=("")) {  //only set if found
            Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(turnoutsAlignedSensor);
            NamedBeanHandle<Sensor*>* routeAligned = nbhm->getNamedBeanHandle(turnoutsAlignedSensor, sensor);
            if (routeAligned != NULL) {
                indication->insert(routeAligned, r);
                //sensor.addPropertyChangeListener(this, routeAligned.getName(), "Wi Throttle Route Controller");
                connect(sensor, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                if (log->isDebugEnabled()) {
                    log->debug("Add listener to Sensor: " + routeAligned->getName() + " for Route: " + ((DefaultRoute*)r)->getSystemName());
                }
            }
        }

    }
}

/**
 * Remove this from each managed route's aligned sensor.
 */
//Override
/*public*/ void RouteController::deregister() {
    if (sysNameList.isEmpty()) {
        return;
    }

    QListIterator<NamedBeanHandle<Sensor*>*> en(indication->keys());
    while (en.hasNext()) {
        NamedBeanHandle<Sensor*>* namedSensor = en.next();
        //namedSensor->getBean().removePropertyChangeListener(this);
        connect(namedSensor->getBean(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        if (log->isDebugEnabled()) {
            log->debug("Removing listener from Sensor: " + namedSensor->getName() + " for Route: " + ((NamedBean*)(indication->value(namedSensor)))->getSystemName());
        }
    }
    indication = new QHash<NamedBeanHandle<Sensor*>*, Route*>();
}

/*private*/ /*final*/ /*static*/ Logger* RouteController::log = LoggerFactory::getLogger("RouteController");

