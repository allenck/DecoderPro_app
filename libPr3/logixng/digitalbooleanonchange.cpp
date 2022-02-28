#include "digitalbooleanonchange.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "runtimeexception.h"

/**
 * Executes an action depending on the parameter.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class DigitalBooleanOnChange extends AbstractDigitalBooleanAction
//        implements FemaleSocketListener {



/*public*/  DigitalBooleanOnChange::DigitalBooleanOnChange(QString sys, QString user, Trigger::TargetAction trigger, QObject* parent)
 : AbstractDigitalBooleanAction(sys, user, parent){
    //super(sys, user);
    _socket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
            ->createFemaleSocket(this, this, "A");
    _trigger = trigger;
}

//@Override
/*public*/  Base* DigitalBooleanOnChange::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException */{
    DigitalBooleanActionManager* manager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
    QString sysName = systemNames.value(getSystemName());
    QString userName = userNames.value(getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    DigitalBooleanOnChange* copy = new DigitalBooleanOnChange(sysName, userName, _trigger);
    copy->setComment(getComment());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* DigitalBooleanOnChange::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanOnChange::execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ {
    if (_socket->isConnected()) {
        switch (_trigger) {
            case Trigger::CHANGE_TO_TRUE:
                // Call execute() if change to true
                if (hasChangedToTrue) {
                    _socket->execute();
                }
                break;
            case Trigger::CHANGE_TO_FALSE:
                // Call execute() if change to false
                if (hasChangedToFalse) {
                    _socket->execute();
                }
                break;
            case Trigger::CHANGE:
                // Always call execute()
                _socket->execute();
                break;
            default:
                throw new UnsupportedOperationException("_whichChange has unknown value: "+_trigger);
        }
    }
}

/**
 * Get the type.
 * @return the trigger
 */
/*public*/  DigitalBooleanOnChange::Trigger::TargetAction DigitalBooleanOnChange::getTrigger() {
    return _trigger;
}

/**
 * Set the type.
 * @param trigger the trigger
 */
/*public*/  void DigitalBooleanOnChange::setTrigger(Trigger::TargetAction trigger) {
    _trigger = trigger;
}

//@Override
/*public*/  FemaleSocket* DigitalBooleanOnChange::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    switch (index) {
        case 0:
            return _socket;

        default:
            throw new IllegalArgumentException(
                    tr("index has invalid value: %1").arg(index));
    }
}

//@Override
/*public*/  int DigitalBooleanOnChange::getChildCount() {
    return 1;
}

//@Override
/*public*/  void DigitalBooleanOnChange::connected(FemaleSocket* socket) {
    if (socket == _socket) {
        _socketSystemName = socket->getConnectedSocket()->getSystemName();
    } else {
        throw new IllegalArgumentException("unknown socket");
    }
}

//@Override
/*public*/  void DigitalBooleanOnChange::disconnected(FemaleSocket* socket) {
    if (socket == _socket) {
        _socketSystemName = "";
    } else {
        throw new IllegalArgumentException("unknown socket");
    }
}

//@Override
/*public*/  QString DigitalBooleanOnChange::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "On change");
}

//@Override
/*public*/  QString DigitalBooleanOnChange::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "%1").arg(Trigger::toString(_trigger));
}

/*public*/  FemaleDigitalActionSocket* DigitalBooleanOnChange::getSocket() {
    return _socket;
}

/*public*/  QString DigitalBooleanOnChange::getSocketSystemName() {
    return _socketSystemName;
}

/*public*/  void DigitalBooleanOnChange::setActionSocketSystemName(QString systemName) {
    _socketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanOnChange::setup() {
    try {
        if ( !_socket->isConnected()
                || _socket->getConnectedSocket()->getSystemName()
                         !=(_socketSystemName)) {

            QString socketSystemName = _socketSystemName;
            _socket->_disconnect();
            if (socketSystemName != nullptr) {
                MaleSocket* maleSocket =
                        (MaleSocket*)((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                ->getBySystemName(socketSystemName)->self();
                _socket->_disconnect();
                if (maleSocket != nullptr) {
                    _socket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load digital action " + socketSystemName);
                }
            }
        } else {
            _socket->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanOnChange::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanOnChange::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanOnChange::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* DigitalBooleanOnChange::log = LoggerFactory::getLogger("DigitalBooleanOnChange");

