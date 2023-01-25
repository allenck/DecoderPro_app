#include "hold.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"

/**
 * An Expression that keeps its status even if its child expression doesn't.
 *
 * This expression stays False until both the 'hold' expression and the 'trigger'
 * expression becomes True. It stays true until the 'hold' expression goes to
 * False. The 'trigger' expression can for example be a push button that stays
 * True for a short time.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class Hold extends AbstractDigitalExpression implements FemaleSocketListener {


    /*public*/  Hold::Hold(QString sys, QString user, QObject *parent) : AbstractDigitalExpression(sys, user,parent)
            /*throws BadUserNameException, BadSystemNameException*/ {

        //super(sys, user);

        _triggerExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Trigger"));
        _holdExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Hold"));
    }

    //@Override
    /*public*/  Base* Hold::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        Hold* copy = new Hold(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category Hold::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool Hold::evaluate() /*throws JmriException */{
        if (_isActive) {
            _isActive = _holdExpressionSocket->evaluate()
                    || _triggerExpressionSocket->evaluate();
        } else {
            _isActive = _triggerExpressionSocket->evaluate();
        }
        return _isActive;
    }

    //@Override
    /*public*/  FemaleSocket* Hold::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        switch (index) {
            case 0:
                return _triggerExpressionSocket;

            case 1:
                return _holdExpressionSocket;

            default:
                throw new IllegalArgumentException(
                        QString("index has invalid value: %1").arg(index));
        }
    }

    //@Override
    /*public*/  int Hold::getChildCount() {
        return 2;
    }

    //@Override
    /*public*/  void Hold::connected(FemaleSocket* socket) {
        if (socket == _triggerExpressionSocket) {
            _triggerExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _holdExpressionSocket) {
            _holdExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/  void Hold::disconnected(FemaleSocket* socket) {
        if (socket == _triggerExpressionSocket) {
            _triggerExpressionSocketSystemName = "";
        } else if (socket == _holdExpressionSocket) {
            _holdExpressionSocketSystemName = nullptr;
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/  QString Hold::getShortDescription(QLocale locale) {
        return tr(/*locale, */"Hold");
    }

    //@Override
    /*public*/  QString Hold::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Trigger on expression %1. Hold while expression %2").arg(
                _triggerExpressionSocket->getName(),
                _holdExpressionSocket->getName());
    }

    /*public*/  QString Hold::getTriggerExpressionSocketSystemName() {
        return _triggerExpressionSocketSystemName;
    }

    /*public*/  void Hold::setTriggerExpressionSocketSystemName(QString systemName) {
        _triggerExpressionSocketSystemName = systemName;
    }

    /*public*/  QString Hold::getHoldActionSocketSystemName() {
        return _holdExpressionSocketSystemName;
    }

    /*public*/  void Hold::setHoldActionSocketSystemName(QString systemName) {
        _holdExpressionSocketSystemName = systemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Hold::setup() {
        try {
            if ( !_triggerExpressionSocket->isConnected()
                    || _triggerExpressionSocket->getConnectedSocket()->getSystemName()
                            != (_triggerExpressionSocketSystemName)) {

                QString socketSystemName = _triggerExpressionSocketSystemName;
                _triggerExpressionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalExpressionManager*)
                            InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
                    _triggerExpressionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _triggerExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                _triggerExpressionSocket->getConnectedSocket()->setup();
            }

            if ( !_holdExpressionSocket->isConnected()
                    || _holdExpressionSocket->getConnectedSocket()->getSystemName()
                            != (_holdExpressionSocketSystemName)) {

                QString socketSystemName = _holdExpressionSocketSystemName;
                _holdExpressionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket =(MaleSocket*)((DefaultDigitalExpressionManager*)
                            InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
                    if (maleSocket != nullptr) {
                        _holdExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                _holdExpressionSocket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Hold::registerListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Hold::unregisterListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Hold::disposeMe() {
    }

    /*private*/ /*final*/ /*static*/ Logger* Hold::log = LoggerFactory::getLogger("Hold");

