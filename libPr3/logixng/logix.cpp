#include "logix.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "runtimeexception.h"

/**
 * Emulates Logix.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class Logix extends AbstractDigitalAction
//        implements FemaleSocketListener {


/*public*/  Logix::Logix(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent) {
    //super(sys, user);
 setObjectName("Logix");
    _expressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
            ->createFemaleSocket(this, this, "E");
    _actionSocket = ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))
            ->createFemaleSocket(this, this, "A");
}

//@Override
/*public*/  Base* Logix::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames.value(AbstractBase::getSystemName());
    QString userName = userNames.value(AbstractBase::getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    Logix* copy = new Logix(sysName, userName);
    copy->AbstractBase::setComment(AbstractBase::getComment());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* Logix::getCategory() {
    return Category::OTHER;
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix::execute() /*throws JmriException*/ {
    bool result = _expressionSocket->evaluate();
    bool hasChangedToTrue = result && !_lastExpressionResult;
    bool hasChangedToFalse = !result && _lastExpressionResult;

    if (!_executeOnChange || (result != _lastExpressionResult)) {
        _actionSocket->execute(hasChangedToTrue, hasChangedToFalse);
    }
    _lastExpressionResult = result;
}

/**
 * Sets whenether actions should only be executed when the result of the
 * evaluation of the expression changes, or if the actions should always
 * be executed.
 * <p>
 * This is the counterpart of Conditional.setTriggerOnChange()
 *
 * @param b if true, execution is only done on change. if false, execution
 *          is always done.
 */
/*public*/  void Logix::setExecuteOnChange(bool b) {
    _executeOnChange = b;
}

/**
 * Determines whenether actions should only be executed when the result of
 * the evaluation of the expression changes, or if the actions should always
 * be executed.
 * <p>
 * This is the counterpart of Conditional.getTriggerOnChange()
 *
 * @return true if execution is only done on change, false otherwise
 */
/*public*/  bool Logix::isExecuteOnChange() {
    return _executeOnChange;
}

/** {@inheritDoc} */
//@Override
/*public*/  FemaleSocket* Logix::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    switch (index) {
        case 0:
            return _expressionSocket;

        case 1:
            return _actionSocket;

        default:
            throw new IllegalArgumentException(
                    tr("index has invalid value: %1").arg(index));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  int Logix::getChildCount() {
    return 2;
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix::connected(FemaleSocket* socket) {
    if (socket == _expressionSocket) {
        _expressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
    } else if (socket == _actionSocket) {
        _actionSocketSystemName = socket->getConnectedSocket()->getSystemName();
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix::disconnected(FemaleSocket* socket) {
    if (socket == _expressionSocket) {
        _expressionSocketSystemName = "";
    } else if (socket == _actionSocket) {
        _actionSocketSystemName = "null";
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString Logix::getShortDescription(QLocale locale) {
    return tr(/*locale, */"Logix");
}

/** {@inheritDoc} */
//@Override
/*public*/  QString Logix::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Logix %1 %2").arg(
            _expressionSocket->getName(),
            _actionSocket->getName());
}

/*public*/  FemaleDigitalExpressionSocket* Logix::getExpressionSocket() {
    return _expressionSocket;
}

/*public*/  QString Logix::getExpressionSocketSystemName() {
    return _expressionSocketSystemName;
}

/*public*/  void Logix::setExpressionSocketSystemName(QString systemName) {
    _expressionSocketSystemName = systemName;
}

/*public*/  FemaleDigitalBooleanActionSocket* Logix::getActionSocket() {
    return _actionSocket;
}

/*public*/  QString Logix::getActionSocketSystemName() {
    return _actionSocketSystemName;
}

/*public*/  void Logix::setActionSocketSystemName(QString systemName) {
    _actionSocketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix::setup() {
    try {
        if ( !_expressionSocket->isConnected()
                || _expressionSocket->getConnectedSocket()->getSystemName()
                        != (_expressionSocketSystemName)) {

            QString socketSystemName = _expressionSocketSystemName;
            _expressionSocket->_disconnect();
            if (socketSystemName != nullptr) {
                MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalExpressionManager*)
                                         InstanceManager::getDefault("DigitalExpressionManager"))
                                ->getBySystemName(socketSystemName)->self();
                if (maleSocket != nullptr) {
                    _expressionSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load digital expression " + socketSystemName);
                }
            }
        } else {
            _expressionSocket->getConnectedSocket()->setup();
        }

        if ( !_actionSocket->isConnected()
                || _actionSocket->getConnectedSocket()->getSystemName()
                        != (_actionSocketSystemName)) {

            QString socketSystemName = _actionSocketSystemName;
            _actionSocket->_disconnect();
            if (socketSystemName != "") {
                MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalBooleanActionManager*)
                        InstanceManager::getDefault("DigitalBooleanActionManager"))
                                ->getBySystemName(socketSystemName)->self();
                _actionSocket->_disconnect();
                if (maleSocket != nullptr) {
                    _actionSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load digital boolean action " + socketSystemName);
                }
            }
        } else {
            _actionSocket->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException* ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix::disposeMe() {
}

/*private*/ /*final*/ /*static*/Logger* Logix::log = LoggerFactory::getLogger("Logix");

