#include "or.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "runtimeexception.h"
#include "vptr.h"

/**
 * Evaluates to True if any of the children expressions evaluate to true.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class Or extends AbstractDigitalExpression implements FemaleSocketListener {


/*public*/  Or::Or(QString sys, QString user, QObject* parent)
        /*throws BadUserNameException, BadSystemNameException*/ : AbstractDigitalExpression(sys, user, parent){
    //super(sys, user);
  setObjectName("Or");
    _expressionEntries
            .append(new ExpressionEntry(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName())));
}

/*public*/  Or::Or(QString sys, QString user, QList<QMap<QString, QString>> expressionSystemNames, QObject* parent)
        /*throws BadUserNameException, BadSystemNameException*/ : AbstractDigitalExpression(sys, user, parent)  {
    //super(sys, user);
    setObjectName("Or");

    setExpressionSystemNames(expressionSystemNames);
}

//@Override
/*public*/  Base* Or::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    Or* copy = new Or(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    copy->setNumSockets(getChildCount());
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*private*/ void Or::setExpressionSystemNames(QList<QMap<QString, QString>> systemNames) {
    if (!_expressionEntries.isEmpty()) {
        throw new RuntimeException("expression system names cannot be set more than once");
    }

    for (QMap<QString, QString> map : systemNames) {
     QMapIterator<QString, QString> entry(map);
     entry.next();
        FemaleDigitalExpressionSocket* socket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, entry.key());

        _expressionEntries.append(new ExpressionEntry(socket, entry.value()));
    }
}

/*public*/  QString Or::getExpressionSystemName(int index) {
    return _expressionEntries.at(index)->_socketSystemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* Or::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool Or::evaluate() /*throws JmriException*/ {
    bool result = false;
    for (ExpressionEntry* e : _expressionEntries) {
        if (e->_socket->isConnected() && e->_socket->evaluate()) {
            result = true;
        }
    }
    return result;
}

//@Override
/*public*/  FemaleSocket* Or::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    return _expressionEntries.at(index)->_socket;
}

//@Override
/*public*/  int Or::getChildCount() {
    return _expressionEntries.size();
}

//@Override
/*public*/  QString Or::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Or");
}

//@Override
/*public*/  QString Or::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Or");
}

// This method ensures that we have enough of children
/*private*/ void Or::setNumSockets(int num) {
    QList</*FemaleSocket**/QVariant> addList = QList</*FemaleSocket**/QVariant>();

    // Is there not enough children?
    while (_expressionEntries.size() < num) {
        FemaleDigitalExpressionSocket* socket =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void Or::checkFreeSocket() {
    bool hasFreeSocket = false;

    for (ExpressionEntry* entry : _expressionEntries) {
        hasFreeSocket |= !entry->_socket->isConnected();
    }
    if (!hasFreeSocket) {
        FemaleDigitalExpressionSocket* socket = (FemaleDigitalExpressionSocket*)((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));

        QList</*FemaleSocket*/QVariant> list = QList</*FemaleSocket*/QVariant>();
        list.append(VPtr<FemaleSocket>::asQVariant(socket));
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), list);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  bool Or::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
    switch (oper) {
        case FemaleSocketOperation::Remove:        // Possible if socket is not connected
            return ! getChild(index)->isConnected();
        case FemaleSocketOperation::InsertBefore:
            return true;    // Always possible
        case FemaleSocketOperation::InsertAfter:
            return true;    // Always possible
        case FemaleSocketOperation::MoveUp:
            return index > 0;   // Possible if not first socket
        case FemaleSocketOperation::MoveDown:
            return index+1 < getChildCount();   // Possible if not last socket
        default:
            throw new UnsupportedOperationException("Oper is unknown" +FemaleSocketOperation::toString( oper/*.name()*/));
    }
}

/*private*/ void Or::insertNewSocket(int index) {
    FemaleDigitalExpressionSocket* socket = (FemaleDigitalExpressionSocket*)((DefaultDigitalExpressionManager*)
            InstanceManager::getDefault("DigitalExpressionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName());
    _expressionEntries.insert(index, new ExpressionEntry(socket));

    QList</*FemaleSocket*/QVariant> addList = QList</*FemaleSocket*/QVariant>();
    addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void Or::removeSocket(int index) {
 QList</*FemaleSocket*/QVariant> removeList = QList</*FemaleSocket*/QVariant>();
    removeList.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    _expressionEntries.removeAt(index);
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, QVariant());
}

/*private*/ void Or::moveSocketDown(int index) {
    ExpressionEntry* temp = _expressionEntries.at(index);
    _expressionEntries.replace(index, _expressionEntries.at(index+1));
    _expressionEntries.replace(index+1, temp);

    QList</*FemaleSocket*/QVariant> list = QList</*FemaleSocket*/QVariant>();
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), list);
}

/** {@inheritDoc} */
//@Override
/*public*/  void Or::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
    switch (oper) {
        case FemaleSocketOperation::Remove:
            if (getChild(index)->isConnected()) throw new UnsupportedOperationException("Socket is connected");
            removeSocket(index);
            break;
        case FemaleSocketOperation::InsertBefore:
            insertNewSocket(index);
            break;
        case FemaleSocketOperation::InsertAfter:
            insertNewSocket(index+1);
            break;
        case FemaleSocketOperation::MoveUp:
            if (index == 0) throw new UnsupportedOperationException("cannot move up first child");
            moveSocketDown(index-1);
            break;
        case FemaleSocketOperation::MoveDown:
            if (index+1 == getChildCount()) throw new UnsupportedOperationException("cannot move down last child");
            moveSocketDown(index);
            break;
        default:
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper/*.name(*/));
    }
}

//@Override
/*public*/  void Or:: connected(FemaleSocket* socket) {
    if (disableCheckForUnconnectedSocket) return;

    for (ExpressionEntry* entry : _expressionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName =
                    socket->getConnectedSocket()->getSystemName();
        }
    }

    checkFreeSocket();
}

//@Override
/*public*/  void Or::disconnected(FemaleSocket* socket) {
    for (ExpressionEntry* entry : _expressionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName = "";
            break;
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void Or::setup() {
    // We don't want to check for unconnected sockets while setup sockets
    disableCheckForUnconnectedSocket = true;

    for (ExpressionEntry* ee : _expressionEntries) {
        try {
            if ( !ee->_socket->isConnected()
                    || ee->_socket->getConnectedSocket()->getSystemName()
                             !=(ee->_socketSystemName)) {

                QString socketSystemName = ee->_socketSystemName;
                ee->_socket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalExpressionManager*)
                            InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
                    if (maleSocket != nullptr) {
                        ee->_socket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                ee->_socket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    checkFreeSocket();

    disableCheckForUnconnectedSocket = false;
}


///* This class is /*public*/  since ExpressionOrXml needs to access it. */
///*private*/ static class ExpressionEntry {
//    /*private*/ String _socketSystemName;
//    /*private*/ final FemaleDigitalExpressionSocket _socket;

//    /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket socket, String socketSystemName) {
//        _socketSystemName = socketSystemName;
//        _socket = socket;
//    }

//    /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket socket) {
//        this._socket = socket;
//    }
//}

/** {@inheritDoc} */
//@Override
/*public*/  void Or::registerListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void Or::unregisterListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void Or::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* Or::log = LoggerFactory::getLogger("Or");
