#include "logix_emulator.h"
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


/*public*/  Logix_Emulator::Logix_Emulator(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent) {
    //super(sys, user);
     setObjectName("Logix");
    _expressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
            ->createFemaleSocket(this, this, "E");
    _actionSocket = ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))
            ->createFemaleSocket(this, this, "A");
}

//@Override
/*public*/  Base* Logix_Emulator::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    Logix_Emulator* copy = new Logix_Emulator(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category Logix_Emulator::getCategory() {
    return Category::OTHER;
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix_Emulator::execute() /*throws JmriException*/ {
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
/*public*/  void Logix_Emulator::setExecuteOnChange(bool b) {
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
/*public*/  bool Logix_Emulator::isExecuteOnChange() {
    return _executeOnChange;
}

/** {@inheritDoc} */
//@Override
/*public*/  FemaleSocket* Logix_Emulator::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
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
/*public*/  int Logix_Emulator::getChildCount() {
    return 2;
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix_Emulator::connected(FemaleSocket* socket) {
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
/*public*/  void Logix_Emulator::disconnected(FemaleSocket* socket) {
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
/*public*/  QString Logix_Emulator::getShortDescription(QLocale locale) {
    return tr(/*locale, */"Logix");
}

/** {@inheritDoc} */
//@Override
/*public*/  QString Logix_Emulator::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Logix %1 %2").arg(
            _expressionSocket->getName(),
            _actionSocket->getName());
}

/*public*/  FemaleDigitalExpressionSocket* Logix_Emulator::getExpressionSocket() {
    return _expressionSocket;
}

/*public*/  QString Logix_Emulator::getExpressionSocketSystemName() {
    return _expressionSocketSystemName;
}

/*public*/  void Logix_Emulator::setExpressionSocketSystemName(QString systemName) {
    _expressionSocketSystemName = systemName;
}

/*public*/  FemaleDigitalBooleanActionSocket* Logix_Emulator::getActionSocket() {
    return _actionSocket;
}

/*public*/  QString Logix_Emulator::getActionSocketSystemName() {
    return _actionSocketSystemName;
}

/*public*/  void Logix_Emulator::setActionSocketSystemName(QString systemName) {
    _actionSocketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix_Emulator::setup() {
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
/*public*/  void Logix_Emulator::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix_Emulator::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void Logix_Emulator::disposeMe() {
}

/*private*/ /*final*/ /*static*/Logger* Logix_Emulator::log = LoggerFactory::getLogger("Logix");

