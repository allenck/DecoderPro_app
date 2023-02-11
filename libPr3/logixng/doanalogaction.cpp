#include "doanalogaction.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultanalogactionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "runtimeexception.h"

/**
 * Executes an analog action with the result of an analog expression.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DoAnalogAction
//        extends AbstractDigitalAction
//        implements FemaleSocketListener {


/*public*/  DoAnalogAction::DoAnalogAction(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent){
    //super(sys, user);
  setObjectName("DoAnalogAction");
    _analogExpressionSocket = ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))
            ->createFemaleSocket(this, this, "E");
    _analogActionSocket = ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))
            ->createFemaleSocket(this, this, "A");
}

//@Override
/*public*/  Base* DoAnalogAction::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException */{
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    DoAnalogAction* copy = new DoAnalogAction(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category DoAnalogAction::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoAnalogAction::execute() /*throws JmriException */{
    double result = _analogExpressionSocket->evaluate();

    _analogActionSocket->setValue(result);
}

//@Override
/*public*/  FemaleSocket* DoAnalogAction::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    switch (index) {
        case 0:
            return _analogExpressionSocket;

        case 1:
            return _analogActionSocket;

        default:
            throw new IllegalArgumentException(
                    tr("index has invalid value: %1").arg(index));
    }
}

//@Override
/*public*/  int DoAnalogAction::getChildCount() {
    return 2;
}

//@Override
/*public*/  void DoAnalogAction::connected(FemaleSocket* socket) {
    if (socket == _analogExpressionSocket) {
        _analogExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
    } else if (socket == _analogActionSocket) {
        _analogActionSocketSystemName = socket->getConnectedSocket()->getSystemName();
    } else {
        throw new IllegalArgumentException("DoAnalogAction: unknown socket");
    }
}

//@Override
/*public*/  void DoAnalogAction::disconnected(FemaleSocket* socket) {
    if (socket == _analogExpressionSocket) {
        _analogExpressionSocketSystemName = "";
    } else if (socket == _analogActionSocket) {
        _analogActionSocketSystemName = "";
    } else {
        throw new IllegalArgumentException("DoAnalogAction: unknown socket");
    }
}

//@Override
/*public*/  QString DoAnalogAction::getShortDescription(QLocale locale) {
    return tr(/*locale, */"DoAnalogAction");
}

//@Override
/*public*/  QString DoAnalogAction::getLongDescription(QLocale locale) {
    return tr(/*locale, */"Read analog %1 and set analog %2").arg(_analogExpressionSocket->getName(), _analogActionSocket->getName());
}

/*public*/  FemaleAnalogActionSocket* DoAnalogAction::getAnalogActionSocket() {
    return _analogActionSocket;
}

/*public*/  QString DoAnalogAction::getAnalogActionSocketSystemName() {
    return _analogActionSocketSystemName;
}

/*public*/  void DoAnalogAction::setAnalogActionSocketSystemName(QString systemName) {
    _analogActionSocketSystemName = systemName;
}

/*public*/  FemaleAnalogExpressionSocket* DoAnalogAction::getAnalogExpressionSocket() {
    return _analogExpressionSocket;
}

/*public*/  QString DoAnalogAction::getAnalogExpressionSocketSystemName() {
    return _analogExpressionSocketSystemName;
}

/*public*/  void DoAnalogAction::setAnalogExpressionSocketSystemName(QString systemName) {
    _analogExpressionSocketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoAnalogAction::setup() {
    try {
        if (!_analogExpressionSocket->isConnected()
                || _analogExpressionSocket->getConnectedSocket()->getSystemName()
                        !=(_analogExpressionSocketSystemName)) {

            QString socketSystemName = _analogExpressionSocketSystemName;

            _analogExpressionSocket->_disconnect();

            if (socketSystemName != nullptr) {
                MaleSocket* maleSocket = (MaleSocket*)((DefaultAnalogExpressionManager*)
                        InstanceManager::getDefault("AnalogExpressionManager"))
                                ->getBySystemName(socketSystemName);
                if (maleSocket != nullptr) {
                    _analogExpressionSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load analog expression " + socketSystemName);
                }
            }
        } else {
            _analogExpressionSocket->getConnectedSocket()->setup();
        }

        if (!_analogActionSocket->isConnected()
                || _analogActionSocket->getConnectedSocket()->getSystemName()
                        !=(_analogActionSocketSystemName)) {

            QString socketSystemName = _analogActionSocketSystemName;

            _analogActionSocket->_disconnect();

            if (socketSystemName != "") {
                MaleSocket* maleSocket =(MaleSocket*)((DefaultAnalogActionManager*)
                        InstanceManager::getDefault("AnalogActionManager"))
                                ->getBySystemName(socketSystemName)->self();
                if (maleSocket != nullptr) {
                    _analogActionSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load analog action " + socketSystemName);
                }
            }
        } else {
            _analogActionSocket->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException* ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoAnalogAction::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoAnalogAction::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoAnalogAction::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* DoAnalogAction::log = LoggerFactory::getLogger("DoAnalogAction");
