#include "triggeronce.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "malesocket.h"

/**
 * An Expression that returns True only once while its child expression returns
 * True.
 * <P>
 * The first time the child expression returns True, this expression returns
 * True. After that, this expression returns False until the child expression
 * returns False and again returns True.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class TriggerOnce extends AbstractDigitalExpression implements FemaleSocketListener {



/*public*/  TriggerOnce::TriggerOnce(QString sys, QString user, QObject* parent) : AbstractDigitalExpression(sys, user, parent){

    //super(sys, user);

    _childExpression = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
            ->createFemaleSocket(this, this, "E");
}

//@Override
/*public*/  Base* TriggerOnce::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    TriggerOnce* copy = new TriggerOnce(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category TriggerOnce::getCategory() {
    return Category::OTHER;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool TriggerOnce::evaluate() /*throws JmriException*/ {
    if (_childExpression->evaluate() && !_childLastState) {
        _childLastState = true;
        return true;
    }
    _childLastState = _childExpression->evaluate();
    return false;
}

//@Override
/*public*/  FemaleSocket* TriggerOnce::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
    if (index == 0) {
        return _childExpression;
    } else {
            throw new IllegalArgumentException(
                    QString("index has invalid value: %1").arg(index));
    }
}

//@Override
/*public*/  int TriggerOnce::getChildCount() {
    return 1;
}

//@Override
/*public*/  void TriggerOnce::connected(FemaleSocket* socket) {
    if (socket == _childExpression) {
        _childExpressionSystemName = socket->getConnectedSocket()->getSystemName();
    } else {
        throw new IllegalArgumentException("TriggerOnce: unkown socket");
    }
}

//@Override
/*public*/  void TriggerOnce::disconnected(FemaleSocket* socket) {
    if (socket == _childExpression) {
        _childExpressionSystemName = "null";
    } else {
        throw new IllegalArgumentException("TriggerOnce: unknown socket");
    }
}

//@Override
/*public*/  QString TriggerOnce::getShortDescription(QLocale locale) {
    return tr(/*locale, */"Trigger once");
}

//@Override
/*public*/  QString TriggerOnce::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Trigger once");
}

/*public*/  QString TriggerOnce::getChildSocketSystemName() {
    return _childExpressionSystemName;
}

/*public*/  void TriggerOnce::setChildSocketSystemName(QString systemName) {
    _childExpressionSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void TriggerOnce::setup() {
    try {
        if ( !_childExpression->isConnected()
                || _childExpression->getConnectedSocket()->getSystemName()
                         != (_childExpressionSystemName)) {

            QString socketSystemName = _childExpressionSystemName;
            _childExpression->_disconnect();
            if (socketSystemName != "") {
                MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalExpressionManager*)
                        InstanceManager::getDefault("DigitalExpressionManager"))
                                ->getBySystemName(socketSystemName)->self();
                if (maleSocket != nullptr) {
                    _childExpression->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load digital expression " + socketSystemName);
                }
            }
        } else {
            _childExpression->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException* ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void TriggerOnce::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void TriggerOnce::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void TriggerOnce::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* TriggerOnce::log = LoggerFactory::getLogger("TriggerOnce");
