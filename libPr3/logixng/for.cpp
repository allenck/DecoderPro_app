#include "for.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultdigitalactionmanager.h"

/**
 * Executes an action when the expression is True.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class For extends AbstractDigitalAction
//        implements FemaleSocketListener {


    /*public*/  For::For(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent) {
        //super(sys, user);
     setObjectName("For");
        _initActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                ->createFemaleSocket(this, this, tr("Init"));
        _whileExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("While"));
        _afterEachActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                ->createFemaleSocket(this, this, tr("AfterEach"));
        _doActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                ->createFemaleSocket(this, this, tr("Do"));
    }

    //@Override
    /*public*/  Base* For::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        For* copy = new For(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* For::getCategory() {
        return Category::COMMON;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void For::execute() /*throws JmriException*/ {
        _initActionSocket->execute();
        while (_whileExpressionSocket->evaluate()) {
            _doActionSocket->execute();
            _afterEachActionSocket->execute();
        }
    }

    //@Override
    /*public*/  FemaleSocket* For::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        switch (index) {
            case 0:
                return _initActionSocket;

            case 1:
                return _whileExpressionSocket;

            case 2:
                return _afterEachActionSocket;

            case 3:
                return _doActionSocket;

            default:
                throw new IllegalArgumentException(
                        QString("index has invalid value: %1").arg(index));
        }
    }

    //@Override
    /*public*/  int For::getChildCount() {
        return 4;
    }

    //@Override
    /*public*/  void For::connected(FemaleSocket* socket) {
        if (socket == _initActionSocket) {
            _initActionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _whileExpressionSocket) {
            _whileExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _afterEachActionSocket) {
            _afterEachActionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _doActionSocket) {
            _doActionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/  void For::disconnected(FemaleSocket* socket) {
        if (socket == _initActionSocket) {
            _initActionSocketSystemName = "";
        } else if (socket == _whileExpressionSocket) {
            _whileExpressionSocketSystemName = "";
        } else if (socket == _afterEachActionSocket) {
            _afterEachActionSocketSystemName = "";
        } else if (socket == _doActionSocket) {
            _doActionSocketSystemName = "";
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/  QString For::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "For");
    }

    //@Override
    /*public*/  QString For::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "For (%1; %2; %3) do %4").arg(
                _initActionSocket->getName(),
                _whileExpressionSocket->getName(),
                _afterEachActionSocket->getName(),
                _doActionSocket->getName());
    }

    /*public*/  FemaleDigitalActionSocket* For::getInitActionSocket() {
        return _initActionSocket;
    }

    /*public*/  QString For::getInitActionSocketSystemName() {
        return _initActionSocketSystemName;
    }

    /*public*/  void For::setInitActionSocketSystemName(QString systemName) {
        _initActionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalExpressionSocket* For::getWhileExpressionSocket() {
        return _whileExpressionSocket;
    }

    /*public*/  QString For::getWhileExpressionSocketSystemName() {
        return _whileExpressionSocketSystemName;
    }

    /*public*/  void For::setWhileExpressionSocketSystemName(QString systemName) {
        _whileExpressionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalActionSocket* For::getAfterEachActionSocket() {
        return _afterEachActionSocket;
    }

    /*public*/  QString For::getAfterEachExpressionSocketSystemName() {
        return _afterEachActionSocketSystemName;
    }

    /*public*/  void For::setAfterEachActionSocketSystemName(QString systemName) {
        _afterEachActionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalActionSocket* For::getDoActionSocket() {
        return _doActionSocket;
    }

    /*public*/  QString For::getDoExpressionSocketSystemName() {
        return _doActionSocketSystemName;
    }

    /*public*/  void For::setDoActionSocketSystemName(QString systemName) {
        _doActionSocketSystemName = systemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void For::setup() {
        try {
            if ( !_initActionSocket->isConnected()
                    || _initActionSocket->getConnectedSocket()->getSystemName()
                            !=(_initActionSocketSystemName)) {

                QString socketSystemName = _initActionSocketSystemName;
                _initActionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalActionManager*)
                            InstanceManager::getDefault("DigitalActionManager"))
                                    ->getBySystemName(socketSystemName);
                    _initActionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _initActionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital action " + socketSystemName);
                    }
                }
            } else {
                _initActionSocket->getConnectedSocket()->setup();
            }

            if ( !_whileExpressionSocket->isConnected()
                    || _whileExpressionSocket->getConnectedSocket()->getSystemName()
                            != (_whileExpressionSocketSystemName)) {

                QString socketSystemName = _whileExpressionSocketSystemName;
                _whileExpressionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*) ((DefaultDigitalExpressionManager*)
                            InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
                    if (maleSocket != nullptr) {
                        _whileExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                _whileExpressionSocket->getConnectedSocket()->setup();
            }

            if ( !_afterEachActionSocket->isConnected()
                    || _afterEachActionSocket->getConnectedSocket()->getSystemName()
                            != (_afterEachActionSocketSystemName)) {

                QString socketSystemName = _afterEachActionSocketSystemName;
                _afterEachActionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket =(MaleSocket*)((DefaultDigitalActionManager*)
                            InstanceManager::getDefault("DigitalActionManager"))
                                    ->getBySystemName(socketSystemName);
                    _afterEachActionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _afterEachActionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital action " + socketSystemName);
                    }
                }
            } else {
                _afterEachActionSocket->getConnectedSocket()->setup();
            }

            if ( !_doActionSocket->isConnected()
                    || _doActionSocket->getConnectedSocket()->getSystemName()
                            != (_doActionSocketSystemName)) {

                QString socketSystemName = _doActionSocketSystemName;
                _doActionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalActionManager*)
                            InstanceManager::getDefault("DigitalActionManager"))
                                    ->getBySystemName(socketSystemName);
                    _doActionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _doActionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital action " + socketSystemName);
                    }
                }
            } else {
                _doActionSocket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void For::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void For::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void For::disposeMe() {
    }

    /*private*/ /*final*/ /*static*/ Logger* For::log = LoggerFactory::getLogger("For");
