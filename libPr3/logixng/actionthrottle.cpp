#include "actionthrottle.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultanalogexpressionmanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "abstractthrottlemanager.h"

/**
 * Runs an engine.
 * This action reads an analog expression with the loco address and sets its
 * speed according to an alaog expression and the direction according to a
 * digital expression.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/ class ActionThrottle extends AbstractDigitalAction
//        implements FemaleSocketListener {




/*public*/ ActionThrottle::ActionThrottle(QString sys, QString user, QObject *parent) : AbstractDigitalAction(sys, user, parent) {
    //super(sys, user);
    _locoAddressSocket = ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))
            ->createFemaleSocket(this, this, tr("Address"));
    _locoSpeedSocket = ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))
            ->createFemaleSocket(this, this, tr("Speed"));
    _locoDirectionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
            ->createFemaleSocket(this, this, tr("Direction"));
}

//@Override
/*public*/ Base* ActionThrottle::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    ActionThrottle* copy = new ActionThrottle(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/ Category ActionThrottle::getCategory() {
    return Category::ITEM;
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionThrottle::execute() /*throws JmriException*/ {

    int currentLocoAddress = -1;
    int newLocoAddress = -1;

    if (_throttle != nullptr) {
        currentLocoAddress = _throttle->getLocoAddress()->getNumber();
    }

    if (_locoAddressSocket->isConnected()) {
        newLocoAddress =
                (int) ((MaleAnalogExpressionSocket*)_locoAddressSocket->getConnectedSocket()->bself())
                ->evaluate();
    }

    if (newLocoAddress != currentLocoAddress) {

        if (_throttle != nullptr) {
            // Stop the loco
            _throttle->setSpeedSetting(0);
            // Release the loco
            ((AbstractThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->releaseThrottle(_throttle, _throttleListener);
            _throttle = nullptr;
        }

        if (newLocoAddress != -1) {

            _throttleListener =  new AT_ThrottleListener(this);
//            {
//                //@Override
//                /*public*/ void notifyThrottleFound(DccThrottle t) {
//                    _throttle = t;
//                    executeConditionalNG();
//                }

//                //@Override
//                /*public*/ void notifyFailedThrottleRequest(LocoAddress address, String reason) {
//                    log.warn("loco {} cannot be aquired", address.getNumber());
//                }

//                //@Override
//                /*public*/ void notifyDecisionRequired(LocoAddress address, ThrottleListener.DecisionType question) {
//                    log.warn("Loco {} cannot be aquired. Decision required.", address.getNumber());
//                }
//            };

            bool result = ((AbstractThrottleManager*)InstanceManager::getDefault("ThrottleManager"))
                    ->requestThrottle(newLocoAddress, _throttleListener);

            if (!result) {
                log->warn(tr("loco %1 cannot be aquired").arg(newLocoAddress));
            }
        }

    }

    // We have a throttle if _throttle is not null
    if (_throttle != nullptr) {

        double speed = 0;
        bool isForward = true;

        if (_locoSpeedSocket->isConnected()) {
            speed =
                    ((MaleAnalogExpressionSocket*)_locoSpeedSocket->getConnectedSocket()->bself())
                    ->evaluate();
        }

        if (_locoDirectionSocket->isConnected()) {
            isForward =
                    ((MaleDigitalExpressionSocket*)_locoDirectionSocket->getConnectedSocket()->bself())
                    ->evaluate();
        }

        DccThrottle* throttle = _throttle;
        float spd = (float) speed;
        bool fwd = isForward;
//        ThreadingUtil.runOnLayoutWithJmriException(() -> {
//            throttle.setSpeedSetting(spd);
//            throttle.setIsForward(fwd);
//        });
        ThreadingUtil* tu = new AT_ThreadingUtil(throttle,spd,fwd);

    }
}

//@Override
/*public*/ FemaleSocket* ActionThrottle::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    switch (index) {
        case LOCO_ADDRESS_SOCKET:
            return _locoAddressSocket;

        case LOCO_SPEED_SOCKET:
            return _locoSpeedSocket;

        case LOCO_DIRECTION_SOCKET:
            return _locoDirectionSocket;

        default:
            throw new IllegalArgumentException(
                    tr("index has invalid value: %1").arg(index));
    }
}

//@Override
/*public*/ int ActionThrottle::getChildCount() {
    return 3;
}

//@Override
/*public*/ void ActionThrottle::connected(FemaleSocket* socket) {
    if (socket == _locoAddressSocket) {
        _locoAddressSocketSystemName = socket->getConnectedSocket()->getSystemName();
        executeConditionalNG();
    } else if (socket == _locoSpeedSocket) {
        _locoSpeedSocketSystemName = socket->getConnectedSocket()->getSystemName();
        executeConditionalNG();
    } else if (socket == _locoDirectionSocket) {
        _locoDirectionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        executeConditionalNG();
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

//@Override
/*public*/ void ActionThrottle::disconnected(FemaleSocket* socket) {
    if (socket == _locoAddressSocket) {
        if (_throttle != nullptr) {
            // Stop the loco
            _throttle->setSpeedSetting(0);
            // Release the loco
            ((AbstractThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->releaseThrottle(_throttle, _throttleListener);
        }
        _locoAddressSocketSystemName = "";
        executeConditionalNG();
    } else if (socket == _locoSpeedSocket) {
        _locoSpeedSocketSystemName = "";
        executeConditionalNG();
    } else if (socket == _locoDirectionSocket) {
        _locoDirectionSocketSystemName = "";
        executeConditionalNG();
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

/*private*/ void ActionThrottle::executeConditionalNG() {
    if (_listenersAreRegistered) {
        ConditionalNG* c = getConditionalNG();
        if (c != nullptr) {
            c->execute();
        }
    }
}

//@Override
/*public*/ QString ActionThrottle::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "ActionThrottle");
}

//@Override
/*public*/ QString ActionThrottle::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Throttle %1").arg(_locoAddressSocket->getName());
}

/*public*/ FemaleAnalogExpressionSocket*ActionThrottle:: getLocoAddressSocket() {
    return _locoAddressSocket;
}

/*public*/ QString ActionThrottle::getLocoAddressSocketSystemName() {
    return _locoAddressSocketSystemName;
}

/*public*/ void ActionThrottle::setLocoAddressSocketSystemName(QString systemName) {
    _locoAddressSocketSystemName = systemName;
}

/*public*/ FemaleAnalogExpressionSocket* ActionThrottle::getLocoSpeedSocket() {
    return _locoSpeedSocket;
}

/*public*/ QString ActionThrottle::getLocoSpeedSocketSystemName() {
    return _locoSpeedSocketSystemName;
}

/*public*/ void ActionThrottle::setLocoSpeedSocketSystemName(QString systemName) {
    _locoSpeedSocketSystemName = systemName;
}

/*public*/ FemaleDigitalExpressionSocket* ActionThrottle::getLocoDirectionSocket() {
    return _locoDirectionSocket;
}

/*public*/ QString ActionThrottle::getLocoDirectionSocketSystemName() {
    return _locoDirectionSocketSystemName;
}

/*public*/ void ActionThrottle::setLocoDirectionSocketSystemName(QString systemName) {
    _locoDirectionSocketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionThrottle::setup() {
    try {
        if ( !_locoAddressSocket->isConnected()
             || _locoAddressSocket->getConnectedSocket()->getSystemName()
                         != (_locoAddressSocketSystemName)) {

            QString socketSystemName = _locoAddressSocketSystemName;
            _locoAddressSocket->_disconnect();
            if (socketSystemName != nullptr) {
                MaleSocket* maleSocket = (AbstractMaleSocket*)
                        ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))
                        ->getBySystemName(socketSystemName)->self();
                _locoAddressSocket->_disconnect();
                if (maleSocket != nullptr) {
                    _locoAddressSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load analog expression " + socketSystemName);
                }
            }
        } else {
            _locoAddressSocket->getConnectedSocket()->setup();
        }

        if ( !_locoSpeedSocket->isConnected()
             || _locoSpeedSocket->getConnectedSocket()->getSystemName()
                        != (_locoSpeedSocketSystemName)) {

            QString socketSystemName = _locoSpeedSocketSystemName;
            _locoSpeedSocket->_disconnect();
            if (socketSystemName != nullptr) {
                MaleSocket* maleSocket =(AbstractMaleSocket*)((DefaultAnalogExpressionManager*)
                        InstanceManager::getDefault("AnalogExpressionManager"))
                        ->getBySystemName(socketSystemName)->self();
                _locoSpeedSocket->_disconnect();
                if (maleSocket != nullptr) {
                    _locoSpeedSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load analog expression " + socketSystemName);
                }
            }
        } else {
            _locoSpeedSocket->getConnectedSocket()->setup();
        }

        if ( !_locoDirectionSocket->isConnected()
             || _locoDirectionSocket->getConnectedSocket()->getSystemName()
                        !=(_locoDirectionSocketSystemName)) {

            QString socketSystemName = _locoDirectionSocketSystemName;
            _locoDirectionSocket->_disconnect();
            if (socketSystemName != "") {
                MaleSocket* maleSocket = (AbstractMaleSocket*)((DefaultDigitalExpressionManager*)
                        InstanceManager::getDefault("DigitalExpressionManager"))
                        ->getBySystemName(socketSystemName)->self();
                _locoDirectionSocket->_disconnect();
                if (maleSocket != nullptr) {
                    _locoDirectionSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load digital expression " + socketSystemName);
                }
            }
        } else {
            _locoDirectionSocket->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException* ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionThrottle::registerListenersForThisClass() {
    _listenersAreRegistered = true;
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionThrottle::unregisterListenersForThisClass() {
    _listenersAreRegistered = false;
}

/** {@inheritDoc} */
//@Override
/*public*/ void ActionThrottle::disposeMe() {
    if (_throttle != nullptr) {
        ((AbstractThrottleManager*)InstanceManager::getDefault("ThrottleManager"))
                ->releaseThrottle(_throttle, _throttleListener);
    }
}

/*private*/ /*final*/ /*static*/ Logger* ActionThrottle::log = LoggerFactory::getLogger("ActionThrottle");
