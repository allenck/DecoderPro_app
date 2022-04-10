#include "not.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * An Expression that negates the result of its child expression.
 *
 * This expression returns False if the child returns True. It returns True
 * if the child returns False. It returns False if no child is connected.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class Not extends AbstractDigitalExpression implements FemaleSocketListener {


/*public*/  Not::Not(QString sys, QString user, QObject* parent) : AbstractDigitalExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {

    //super(sys, user);

    _socket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
            ->createFemaleSocket(this, this, tr("E"));
}

//@Override
/*public*/  Base* Not::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    Not* copy = new Not(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* Not::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool Not::evaluate() /*throws JmriException*/ {
    return !_socket->evaluate();
}

//@Override
/*public*/  FemaleSocket* Not::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    switch (index) {
        case 0:
            return _socket;

        default:
            throw new IllegalArgumentException(
                    QString("index has invalid value: %1").arg(index));
    }
}

//@Override
/*public*/  int Not::getChildCount() {
    return 1;
}

//@Override
/*public*/  void Not::connected(FemaleSocket* socket) {
    if (socket == _socket) {
        _socketSystemName = socket->getConnectedSocket()->getSystemName();
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

//@Override
/*public*/  void Not::disconnected(FemaleSocket* socket) {
    if (socket == _socket) {
        _socketSystemName = "";
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

//@Override
/*public*/  QString Not::getShortDescription(QLocale locale) {
    return tr(/*locale, */"Not");
}

//@Override
/*public*/  QString Not::getLongDescription(QLocale locale) {
    return tr(/*locale, */"Not");
}

/*public*/  QString Not::getSocketSystemName() {
    return _socketSystemName;
}

/*public*/  void Not::setSocketSystemName(QString systemName) {
    _socketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void Not::setup() {
    try {
        if ( !_socket->isConnected()
                || _socket->getConnectedSocket()->getSystemName()
                        != (_socketSystemName)) {

            QString socketSystemName = _socketSystemName;
            _socket->_disconnect();
            if (socketSystemName != "") {
                MaleSocket* maleSocket =(MaleSocket*)((DefaultDigitalExpressionManager*)
                        InstanceManager::getDefault("DigitalExpressionManager"))
                                ->getBySystemName(socketSystemName)->self();
                _socket->_disconnect();
                if (maleSocket != nullptr) {
                    _socket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load digital expression " + socketSystemName);
                }
            }
        } else {
            _socket->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException* ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void Not::registerListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void Not::unregisterListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void Not::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* Not::log = LoggerFactory::getLogger("Not");
