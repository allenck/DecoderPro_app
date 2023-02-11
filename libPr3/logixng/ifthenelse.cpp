#include "ifthenelse.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "runtimeexception.h"

/**
 * Executes an action when the expression is True.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class IfThenElse extends AbstractDigitalAction
//        implements FemaleSocketListener {


    /*public*/  IfThenElse::IfThenElse(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent) {
        //super(sys, user);
        setObjectName("IfThenElse");
        _ifExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, "If");
        _thenActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                ->createFemaleSocket(this, this, "Then");
        _elseActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                ->createFemaleSocket(this, this, "Else");
    }

    //@Override
    /*public*/  Base* IfThenElse::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException */{
        DigitalActionManager* manager = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"));
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        IfThenElse* copy = new IfThenElse(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setType(_type);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category IfThenElse::getCategory() {
        return Category::COMMON;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void IfThenElse::execute() /*throws JmriException*/ {
        bool result = _ifExpressionSocket->evaluate();
        TriState _expressionResult = result?True:False;//TriState::getValue(result);


        // _lastExpressionResult may be Unknown
        if ((_type == Type::AlwaysExecute) || (_expressionResult != _lastExpressionResult)) {
            if (result) {
                _thenActionSocket->execute();
            } else {
                _elseActionSocket->execute();
            }

            // Last expression result must be stored as a tri state value, since
            // we must know if the old value is known or not.
            _lastExpressionResult = _expressionResult;
        }
    }

    /**
     * Get the type.
     * @return the type
     */
    /*public*/  IfThenElse::Type::ETYPE IfThenElse::getType() {
        return _type;
    }

    /**
     * Set the type.
     * @param type the type
     */
    /*public*/  void IfThenElse::setType(Type::ETYPE type) {
        _type = type;
    }

    //@Override
    /*public*/  FemaleSocket* IfThenElse::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        switch (index) {
            case 0:
                return _ifExpressionSocket;

            case 1:
                return _thenActionSocket;

            case 2:
                return _elseActionSocket;

            default:
                throw new IllegalArgumentException(
                        tr("index has invalid value: %1").arg(index));
        }
    }

    //@Override
    /*public*/  int IfThenElse::getChildCount() {
        return 3;
    }

    //@Override
    /*public*/  void IfThenElse::connected(FemaleSocket* socket) {
        if (socket == _ifExpressionSocket) {
            _ifExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _thenActionSocket) {
            _thenActionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _elseActionSocket) {
            _elseActionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            throw new IllegalArgumentException("IfThenElse: unknown socket");
        }
    }

    //@Override
    /*public*/  void IfThenElse::disconnected(FemaleSocket* socket) {
        if (socket == _ifExpressionSocket) {
            _ifExpressionSocketSystemName = "";
        } else if (socket == _thenActionSocket) {
            _thenActionSocketSystemName = "";
        } else if (socket == _elseActionSocket) {
            _elseActionSocketSystemName = "";
        } else {
            throw new IllegalArgumentException("IfThenElse: unknown socket");
        }
    }

    //@Override
    /*public*/  QString IfThenElse::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "IfThenElse");
    }

    //@Override
    /*public*/  QString IfThenElse::getLongDescription(QLocale locale) {
        return tr(/*locale, */"If Then Else. %1").arg(Type::toString(_type));
    }

    /*public*/  FemaleDigitalExpressionSocket* IfThenElse::getIfExpressionSocket() {
        return _ifExpressionSocket;
    }

    /*public*/  QString IfThenElse::getIfExpressionSocketSystemName() {
        return _ifExpressionSocketSystemName;
    }

    /*public*/  void IfThenElse::setIfExpressionSocketSystemName(QString systemName) {
        _ifExpressionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalActionSocket* IfThenElse::getThenActionSocket() {
        return _thenActionSocket;
    }

    /*public*/  QString IfThenElse::getThenActionSocketSystemName() {
        return _thenActionSocketSystemName;
    }

    /*public*/  void IfThenElse::setThenActionSocketSystemName(QString systemName) {
        _thenActionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalActionSocket* IfThenElse::getElseActionSocket() {
        return _elseActionSocket;
    }

    /*public*/  QString IfThenElse::getElseActionSocketSystemName() {
        return _elseActionSocketSystemName;
    }

    /*public*/  void IfThenElse::setElseActionSocketSystemName(QString systemName) {
        _elseActionSocketSystemName = systemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void IfThenElse::setup() {
        try {
            if ( !_ifExpressionSocket->isConnected()
                    || _ifExpressionSocket->getConnectedSocket()->getSystemName()
                            !=(_ifExpressionSocketSystemName)) {

                QString socketSystemName = _ifExpressionSocketSystemName;
                _ifExpressionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)((DigitalExpressionManager*)
                            InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
                    if (maleSocket != nullptr) {
                        _ifExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                _ifExpressionSocket->getConnectedSocket()->setup();
            }

            if ( !_thenActionSocket->isConnected()
                    || _thenActionSocket->getConnectedSocket()->getSystemName()
                            !=(_thenActionSocketSystemName)) {

                QString socketSystemName = _thenActionSocketSystemName;
                _thenActionSocket->_disconnect();
                if (socketSystemName != nullptr) {
                    MaleSocket* maleSocket =(MaleSocket*)((DigitalExpressionManager*)
                                     InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
                    _thenActionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _thenActionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital action " + socketSystemName);
                    }
                }
            } else {
                _thenActionSocket->getConnectedSocket()->setup();
            }

            if ( !_elseActionSocket->isConnected()
                    || _elseActionSocket->getConnectedSocket()->getSystemName()
                            !=(_elseActionSocketSystemName)) {

                QString socketSystemName = _elseActionSocketSystemName;
                _elseActionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket =(MaleSocket*)((DigitalExpressionManager*)
                                    InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
                    _elseActionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _elseActionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital action " + socketSystemName);
                    }
                }
            } else {
                _elseActionSocket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void IfThenElse::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void IfThenElse::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void IfThenElse::disposeMe() {
    }

    #if 0
    /**
     * The type of Action. If the type is changed, the action is aborted if it
     * is currently running.
     */
    /*public*/  enum Type {
        /**
         * The "then" or "else" action is executed when the expression changes
         * its result. If the expression has returned "false", but now returns
         * "true", the "then" action is executed. If the expression has
         * returned "true", but now returns "false", the "else" action is executed.
         */
        ExecuteOnChange(Bundle.getMessage("IfThenElse_ExecuteOnChange")),

        /**
         * The "then" or "else" action is always executed when this action is
         * executed. If the expression returns "true", the "then" action is
         * executed. If the expression returns "false", the "else" action is
         * executed.
         */
        AlwaysExecute(Bundle.getMessage("IfThenElse_AlwaysExecute"));

        /*private*/ /*final*/ String _text;

        /*private*/ Type(String text) {
            this._text = text;
        }

        //@Override
        /*public*/  QString toString() {
            return _text;
        }

    }

    #endif



    /*private*/ /*final*/ /*static*/ Logger* IfThenElse::log = LoggerFactory::getLogger("IfThenElse");

