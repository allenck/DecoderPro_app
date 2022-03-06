#include "dostringaction.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultstringexpressionmanager.h"
#include "defaultstringactionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "femalestringexpressionsocket.h"
#include "femalestringactionsocket.h"
#include "stringexpressionmanager.h"
#include "runtimeexception.h"

/**
 * Executes an string action with the result of an string expression.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class DoStringAction
//        extends AbstractDigitalAction
//        implements FemaleSocketListener {


/*public*/  DoStringAction::DoStringAction(QString sys, QString user, QObject *parent )
   : AbstractDigitalAction(sys, user, parent){
    //super(sys, user);
    setObjectName("DoStringAction");
    _stringExpressionSocket = ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))
            ->createFemaleSocket(this, this, "E");
    _stringActionSocket = ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))
            ->createFemaleSocket(this, this, "A");
}

//@Override
/*public*/  Base* DoStringAction::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames.value(AbstractNamedBean::getSystemName());
    QString userName = userNames.value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    DoStringAction* copy = new DoStringAction(sysName, userName);
    copy->AbstractBase::setComment(AbstractBase::getComment());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* DoStringAction::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoStringAction::execute() /*throws JmriException*/ {
    QString result = _stringExpressionSocket->evaluate();

    _stringActionSocket->setValue(result);
}

//@Override
/*public*/  FemaleSocket* DoStringAction::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    switch (index) {
        case 0:
            return _stringExpressionSocket;

        case 1:
            return _stringActionSocket;

        default:
            throw new IllegalArgumentException(
                    tr("index has invalid value: %!").arg(index));
    }
}

//@Override
/*public*/  int DoStringAction::getChildCount() {
    return 2;
}

//@Override
/*public*/  void DoStringAction::connected(FemaleSocket* socket) {
    if (socket == _stringExpressionSocket) {
        _stringExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
    } else if (socket == _stringActionSocket) {
        _stringActionSocketSystemName = socket->getConnectedSocket()->getSystemName();
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

//@Override
/*public*/  void DoStringAction::disconnected(FemaleSocket* socket) {
    if (socket == _stringExpressionSocket) {
        _stringExpressionSocketSystemName = "";
    } else if (socket == _stringActionSocket) {
        _stringActionSocketSystemName = "";
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

//@Override
/*public*/  QString DoStringAction::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Read string and set string");
}

//@Override
/*public*/  QString DoStringAction::getLongDescription(QLocale locale) {
    return tr(/*locale, */"Read string %1 and set string %2").arg(_stringExpressionSocket->getName(), _stringActionSocket->getName());
}

/*public*/  FemaleStringActionSocket* DoStringAction::getStringActionSocket() {
    return _stringActionSocket;
}

/*public*/  QString DoStringAction::getStringActionSocketSystemName() {
    return _stringActionSocketSystemName;
}

/*public*/  void DoStringAction::setStringActionSocketSystemName(QString systemName) {
    _stringActionSocketSystemName = systemName;
}

/*public*/  FemaleStringExpressionSocket* DoStringAction::getStringExpressionSocket() {
    return _stringExpressionSocket;
}

/*public*/  QString DoStringAction::getStringExpressionSocketSystemName() {
    return _stringExpressionSocketSystemName;
}

/*public*/  void DoStringAction::setStringExpressionSocketSystemName(QString systemName) {
    _stringExpressionSocketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoStringAction::setup() {
    try {
        if (!_stringExpressionSocket->isConnected()
                || _stringExpressionSocket->getConnectedSocket()->getSystemName()
                        !=(_stringExpressionSocketSystemName)) {

            QString socketSystemName = _stringExpressionSocketSystemName;

            _stringExpressionSocket->_disconnect();

            if (socketSystemName != "") {
                MaleSocket* maleSocket =
                     (MaleSocket*)   ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))
                                ->getBySystemName(socketSystemName)->self();
                if (maleSocket != nullptr) {
                    _stringExpressionSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load string expression " + socketSystemName);
                }
            }
        } else {
            _stringExpressionSocket->getConnectedSocket()->setup();
        }

        if (!_stringActionSocket->isConnected()
                || _stringActionSocket->getConnectedSocket()->getSystemName()
                        !=(_stringActionSocketSystemName)) {

            QString socketSystemName = _stringActionSocketSystemName;

            _stringActionSocket->_disconnect();

            if (socketSystemName != "") {
                MaleSocket* maleSocket =
                     (MaleSocket* )  ((StringActionManager*)InstanceManager::getDefault("StringActionManager"))
                                ->getBySystemName(socketSystemName)->self();
                if (maleSocket != nullptr) {
                    _stringActionSocket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load string action " + socketSystemName);
                }
            }
        } else {
            _stringActionSocket->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException* ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoStringAction::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoStringAction::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void DoStringAction::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* DoStringAction::log = LoggerFactory::getLogger("DoStringAction");
