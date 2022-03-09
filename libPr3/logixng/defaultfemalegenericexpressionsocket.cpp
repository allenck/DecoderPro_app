#include "defaultfemalegenericexpressionsocket.h"
#include "runtimeexception.h"
#include "femalegenericexpressionsocket.h"
#include "maledigitalexpressionsocket.h"
#include "maleanalogexpressionsocket.h"
#include "malestringexpressionsocket.h"
#include "analogexpressionmanager.h"
#include "digitalexpressionmanager.h"
#include "instancemanager.h"
#include "stringexpressionmanager.h"
#include "defaultfemaleanalogexpressionsocket.h"
#include "defaultfemaledigitalexpressionsocket.h"
#include "defaultfemalestringexpressionsocket.h"

/**
 * Default implementation of the FemaleGenericExpressionSocket
 */
///*public*/  class DefaultFemaleGenericExpressionSocket
//        extends AbstractFemaleSocket
//        implements FemaleGenericExpressionSocket, FemaleSocketListener {


    /*public*/  DefaultFemaleGenericExpressionSocket::DefaultFemaleGenericExpressionSocket(
            SocketType socketType,
            Base* parent,
            FemaleSocketListener* listener,
            QString name, QObject* parentObject) : AbstractFemaleSocket(parent, listener, name, parentObject){

        //super(parent, listener, name);
        setObjectName("DefaultFemaleGenericExpressionSocket");
        _analogSocket = new DefaultFemaleAnalogExpressionSocket(this, this, "A");
        _digitalSocket = new DefaultFemaleDigitalExpressionSocket(this, this, "D");
        _stringSocket = new DefaultFemaleStringExpressionSocket(this, this, "S");

        _socketType = socketType;
        _currentSocketType = socketType;

        switch (_socketType) {
            case SocketType::ANALOG:
                _currentActiveSocket = _analogSocket;
                break;

            case DIGITAL:
                _currentActiveSocket = _digitalSocket;
                break;

            case STRING:
                _currentActiveSocket = _stringSocket;
                break;

            case GENERIC:
                _currentActiveSocket = nullptr;
                break;

            default:
                throw new RuntimeException(QString("_socketType has invalid value: ")+FemaleGenericExpressionSocket::toString(socketType));
        }
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleSocket* DefaultFemaleGenericExpressionSocket::getCurrentActiveSocket() {
        return _currentActiveSocket;
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleGenericExpressionSocket::isCompatible(MaleSocket* socket) {
        return (qobject_cast<MaleAnalogExpressionSocket*>(socket->bself()))
                || (dynamic_cast<MaleDigitalExpressionSocket*>(socket->bself()))
                || (qobject_cast<MaleStringExpressionSocket*>(socket->bself()));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket::setSocketType(SocketType socketType)
            /*throws SocketAlreadyConnectedException*/ {

        if (socketType == _socketType) {
            return;
        }

        if ((_currentActiveSocket != nullptr) && (_currentActiveSocket->isConnected())) {
            throw new SocketAlreadyConnectedException("Socket is already connected");
        }

        switch (socketType) {
            case DIGITAL:
                _socketType = SocketType::DIGITAL;
                _currentSocketType = SocketType::DIGITAL;
                _currentActiveSocket = _digitalSocket;
                break;

            case ANALOG:
                _socketType = SocketType::ANALOG;
                _currentSocketType = SocketType::ANALOG;
                _currentActiveSocket = _analogSocket;
                break;

            case STRING:
                _socketType = SocketType::STRING;
                _currentSocketType = SocketType::STRING;
                _currentActiveSocket = _stringSocket;
                break;

            case GENERIC:
                _socketType = SocketType::GENERIC;
                _currentSocketType = SocketType::GENERIC;
                _currentActiveSocket = nullptr;
                break;

            default:
                throw new RuntimeException(QString("socketType has invalid value: ")+FemaleGenericExpressionSocket::toString(socketType));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleGenericExpressionSocket::SocketType DefaultFemaleGenericExpressionSocket::getSocketType() {
        return _socketType;
    }

    /*public*/  void DefaultFemaleGenericExpressionSocket::setDoI18N(bool do_i18n) {
        _do_i18n = do_i18n;
    }

    /*public*/  bool DefaultFemaleGenericExpressionSocket::getDoI18N() {
        return _do_i18n;
    }

    //@Override
    //@CheckForNull
    /*public*/  QVariant DefaultFemaleGenericExpressionSocket::evaluateGeneric() /*throws JmriException*/ {
        if (AbstractFemaleSocket::isConnected()) {
            switch (_currentSocketType) {
                case DIGITAL:
                    return ((MaleDigitalExpressionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())
                            ->evaluate();

                case ANALOG:
                    return ((MaleAnalogExpressionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())
                            ->evaluate();

                case STRING:
                    return ((MaleStringExpressionSocket*)AbstractFemaleSocket::getConnectedSocket()->bself())
                            ->evaluate();

                default:
                    throw new RuntimeException(QString("_currentSocketType has invalid value: ")+FemaleGenericExpressionSocket::toString(_currentSocketType));
            }
        } else {
            return QVariant();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleGenericExpressionSocket::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "?*");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultFemaleGenericExpressionSocket::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "?~ %1").arg(getName());
    }

    /*private*/ void DefaultFemaleGenericExpressionSocket::addClassesToMap(
     QHash<Category*, QList</*Class<? extends Base>*/QString> > destinationClasses,
     QHash<Category*, QList</*Class<? extends Base>*/QString> > sourceClasses){

        for (Category* category : Category::values()) {
            // Some categories might not have any expression.
            if (sourceClasses.value(category).isEmpty()) continue;

            for (/*Class<? extends Base>*/QString clazz : sourceClasses.value(category)) {
             //destinationClasses.value(category).append(clazz);
             QList<QString> c = destinationClasses.value(category);
             c.append(clazz);
             destinationClasses.insert(category, c); // this replaces!
            }
        }
    }

    //@Override
    /*public*/  QHash<Category *, QList<QString> > DefaultFemaleGenericExpressionSocket::getConnectableClasses() {
        QHash<Category*, QList</*Class<? extends Base>*/QString>> classes = QHash<Category*, QList</*Class<? extends Base>*/QString>>();

        for (Category* category : Category::values()) {
            classes.insert(category, QList<QString>());
        }

        addClassesToMap(classes, ((AnalogExpressionManager*)InstanceManager::getDefault(/*AnalogExpressionManager*/))->getExpressionClasses());
        addClassesToMap(classes, ((DigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getExpressionClasses());
        addClassesToMap(classes, ((StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->getExpressionClasses());

        return classes;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket::_connect(MaleSocket* socket) /*throws SocketAlreadyConnectedException*/ {

        if (socket == nullptr) {
            throw new NullPointerException("socket cannot be null");
        }

        // If _currentActiveSocket is not null, the socket is either connected
        // or locked to a particular type.
        if (_currentActiveSocket != nullptr) {
            if (_currentActiveSocket->isConnected()) {
                throw new SocketAlreadyConnectedException("Socket is already connected");
            } else {
                _currentActiveSocket->_connect(socket);
                _listener->connected(this);
                return;
            }
        }

        // If we are here, the socket is not connected and is not locked to a
        // particular type.

        if (_digitalSocket->isCompatible(socket)) {
            _currentSocketType = SocketType::DIGITAL;
            _currentActiveSocket = _digitalSocket;
        } else if (_analogSocket->isCompatible(socket)) {
            _currentSocketType = SocketType::ANALOG;
            _currentActiveSocket = _analogSocket;
        } else if (_stringSocket->isCompatible(socket)) {
            _currentSocketType = SocketType::STRING;
            _currentActiveSocket = _stringSocket;
        } else {
            throw new IllegalArgumentException("Socket is not compatible");
        }
        _currentActiveSocket->_connect(socket);
        _listener->connected(this);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket::_disconnect() {
        if ((_currentActiveSocket != nullptr)
                && _currentActiveSocket->isConnected()) {

            _currentActiveSocket->_disconnect();
            _listener->disconnected(this);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DefaultFemaleGenericExpressionSocket::getConnectedSocket() {
        if (_currentActiveSocket != nullptr) {
            return _currentActiveSocket->getConnectedSocket();
        } else {
            return nullptr;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultFemaleGenericExpressionSocket::isConnected() {
        return (_currentActiveSocket != nullptr) && _currentActiveSocket->isConnected();
    }

    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket::connected(FemaleSocket* socket) {
        // Do nothing
    }

    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket::disconnected(FemaleSocket* socket) {
        if (_socketType == SocketType::GENERIC) {
            _currentActiveSocket = nullptr;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket::disposeMe() {
        // Do nothing
    }

