#include "turnoutcontroller.h"
#include "logger.h"
#include "loggerfactory.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include "controllerinterface.h"

//TurnoutController::TurnoutController()
//{

//}
/**
 *
 *
 * @author Brett Hoffman Copyright (C) 2010
 */
// /*public*/ class TurnoutController extends AbstractController implements PropertyChangeListener {


/*public*/ TurnoutController::TurnoutController() {
    manager = (ProxyTurnoutManager*)InstanceManager::getNullableDefault("TurnoutManager");
    if (manager == NULL) {
        log->info("No turnout manager instance.");
        isValid = false;
    } else {

        isValid = true;
    }
}

//@Override
bool TurnoutController::verifyCreation() {

    return isValid;
}

//@Override
/*public*/ void TurnoutController::filterList() {
    QStringList tempList = QStringList();
    foreach (QString sysName, sysNameList) {
        Turnout* t = (Turnout*)manager->getBySystemName(sysName);
        QVariant o = t->getProperty("WifiControllable");
        if ((o == QVariant()) || (o.toString()/*.equalsIgnoreCase*/ !=("false"))) {
            //  Only skip if 'false'
            tempList.append(sysName);
        }
    }
    sysNameList = tempList;
}

//@Override
void TurnoutController::handleMessage(QString message) {
    try {
        if (message.at(0) == 'A') {
            if (message.at(1) == '2') {
                Turnout* t =(Turnout*) manager->getBySystemName(message.mid(2));
                if (t->getCommandedState() == Turnout::CLOSED) {
                    t->setCommandedState(Turnout::THROWN);
                } else {
                    t->setCommandedState(Turnout::CLOSED);
                }
            } else if (message.at(1) == 'C') {
                Turnout* t = (Turnout*)manager->getBySystemName(message.mid(2));
                t->setCommandedState(Turnout::CLOSED);

            } else if (message.at(1) == 'T') {
                Turnout* t =(Turnout*) manager->getBySystemName(message.mid(2));
                t->setCommandedState(Turnout::THROWN);

            } else {
                log->warn("Message \"" + message + "\" unknown.");
            }
        }
    } catch (NullPointerException exb) {
        log->warn("Message \"" + message + "\" does not match a turnout.");
    }
}

/**
 * Send Info on turnouts to devices, not specific to any one turnout.
 *
 * Format: PTT]\[value}|{turnoutKey]\[value}|{closedKey]\[value}|{thrownKey
 */
/*public*/ void TurnoutController::sendTitles() {
    if (listeners == NULL) {
        return;
    }

    QString labels = QString("PTT");    //  Panel Turnout Titles

    labels.append("]\\[" + tr("No turnout manager instance.") + "}|{Turnout");
    labels.append("]\\[" + manager->getClosedText() + "}|{2");
    labels.append("]\\[" + manager->getThrownText() + "}|{4");

    QString message = labels;

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }

}

/**
 * Send list of turnouts Format:
 * PTL]\[SysName}|{UsrName}|{CurrentState]\[SysName}|{UsrName}|{CurrentState
 *
 * States: 1 - UNKNOWN, 2 - CLOSED, 4 - THROWN
 */
/*public*/ void TurnoutController::sendList() {
    if (listeners == NULL) {
        return;
    }
    if (canBuildList) {
        buildList(manager);
    }

    if (sysNameList.isEmpty()) {
        return;
    }

    QString list = QString("PTL");  //  Panel Turnout List

    foreach (QString sysName, sysNameList) {
        Turnout* t = (Turnout*)manager->getBySystemName(sysName);
        list.append("]\\[" + sysName);
        list.append("}|{");
        if (t->getUserName() != NULL) {
            list.append(t->getUserName());
        }
        list.append("}|{" + QString::number(t->getKnownState()));
        if (canBuildList) {
           //->PropertyChangeSupport::addPropertyChangeListener(this);
         connect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }

    }
    QString message = list;

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }
}

/**
 *
 */
//@Override
/*public*/ void TurnoutController::propertyChange(PropertyChangeEvent*evt) {
    if (evt->getPropertyName() == ("KnownState")) {
        Turnout* t = (Turnout*) evt->getSource();
        sendTurnoutState(t);
    }
}

/*public*/ void TurnoutController::sendTurnoutState(Turnout* t) {
    QString message;

    message = "PTA" + QString::number(t->getKnownState()) + t->getSystemName();

    foreach (ControllerInterface* listener, *listeners) {
        listener->sendPacketToDevice(message);
    }
}

//@Override
/*public*/ void TurnoutController::_register() {
    foreach (QString sysName, sysNameList) {
        Turnout* t = (Turnout*)manager->getBySystemName(sysName);
        if (t != NULL) {
            //t.addPropertyChangeListener(this);
         connect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
            if (log->isDebugEnabled()) {
                log->debug("Add listener to Turnout: " + t->getSystemName());
            }
        }

    }
}

//@Override
/*public*/ void TurnoutController::deregister() {
    if (sysNameList.isEmpty()) {
        return;
    }

    foreach (QString sysName, sysNameList) {
        Turnout* t = (Turnout*)manager->getBySystemName(sysName);

        if (t != NULL) {
            //t->removePropertyChangeListener(this);
         disconnect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
            if (log->isDebugEnabled()) {
                log->debug("Remove listener from Turnout: " + t->getSystemName());
            }
        }

    }
}

/*private*/ /*final*/ /*static*/ Logger* TurnoutController::log = LoggerFactory::getLogger("TurnoutController");
