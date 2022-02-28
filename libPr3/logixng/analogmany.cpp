#include "analogmany.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultanalogactionmanager.h"
#include "vptr.h"
#include "runtimeexception.h"

/**
 * Execute many Actions in a specific order.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class AnalogMany extends AbstractAnalogAction
//        implements FemaleSocketListener {


/*public*/  AnalogMany::AnalogMany(QString sys, QString user, QObject* parent)
 : AbstractAnalogAction(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
    _actionEntries
            .append(new ActionEntry(((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName())));
}

/*public*/  AnalogMany::AnalogMany(QString sys, QString user, QList<QMap<QString, QString>> actionSystemNames, QObject* parent)
 : AbstractAnalogAction(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
    setActionSystemNames(actionSystemNames);
}

//@Override
/*public*/  Base* AnalogMany::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException */{
    AnalogActionManager* manager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
    QString sysName = systemNames.value(getSystemName());
    QString userName = userNames.value(getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    AnalogMany* copy = new AnalogMany(sysName, userName);
    copy->setComment(getComment());
    copy->setNumSockets(getChildCount());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*private*/ void AnalogMany::setActionSystemNames(QList<QMap<QString, QString>> systemNames) {
    if (!_actionEntries.isEmpty()) {
        throw new RuntimeException("action system names cannot be set more than once");
    }

    for (QMap<QString, QString> map : systemNames) {
     QMapIterator<QString, QString> entry(map);
     entry.next();
        FemaleAnalogActionSocket* socket =((DefaultAnalogActionManager*)
                InstanceManager::getDefault("AnalogActionManager"))
                        ->createFemaleSocket(this, this, entry.key());

        _actionEntries.append(new ActionEntry(socket, entry.value()));
    }
}

/*public*/  QString AnalogMany::getActionSystemName(int index) {
    return _actionEntries.at(index)->_socketSystemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::setup() {
    // We don't want to check for unconnected sockets while setup sockets
    disableCheckForUnconnectedSocket = true;

    for (ActionEntry* ae : _actionEntries) {
        try {
            if ( !ae->_socket->isConnected()
                    || ae->_socket->getConnectedSocket()->getSystemName()
                            !=(ae->_socketSystemName)) {

                QString socketSystemName = ae->_socketSystemName;
                ae->_socket->_disconnect();
                if (socketSystemName !="") {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultAnalogActionManager*)
                            InstanceManager::getDefault("AnalogActionManager"))
                                    ->getBySystemName(socketSystemName)->self();
                    if (maleSocket != nullptr) {
                        ae->_socket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load analog action " + socketSystemName);
                    }
                }
            } else {
                ae->_socket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    checkFreeSocket();

    disableCheckForUnconnectedSocket = false;
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* AnalogMany::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::setValue(double value) /*throws JmriException */{
    for (ActionEntry* actionEntry : _actionEntries) {
        actionEntry->_socket->setValue(value);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  FemaleSocket* AnalogMany::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    return _actionEntries.at(index)->_socket;
}

/** {@inheritDoc} */
//@Override
/*public*/  int AnalogMany::getChildCount() {
    return _actionEntries.size();
}

// This method ensures that we have enough of children
/*private*/ void AnalogMany::setNumSockets(int num) {
    QList</*FemaleSocket*/QVariant> addList = QList</*FemaleSocket*/QVariant>();

    // Is there not enough children?
    while (_actionEntries.size() < num) {
        FemaleAnalogActionSocket* socket = ((DefaultAnalogActionManager*)
                InstanceManager::getDefault("AnalogActionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _actionEntries.append(new ActionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void AnalogMany::checkFreeSocket() {
    bool hasFreeSocket = false;

    for (ActionEntry* entry : _actionEntries) {
        hasFreeSocket |= !entry->_socket->isConnected();
    }
    if (!hasFreeSocket) {
        FemaleAnalogActionSocket* socket = ((DefaultAnalogActionManager*)
                                            InstanceManager::getDefault("AnalogActionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _actionEntries.append(new ActionEntry(socket));

        QList</*FemaleSocket*/QVariant> list = QList</*FemaleSocket*/QVariant>();
        list.append(VPtr<FemaleSocket>::asQVariant(socket));
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), list);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  bool AnalogMany::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
    switch (oper) {
        case FemaleSocketOperation::Remove:    // Possible if socket is not connected and there are at least two sockets
            if (_actionEntries.size() == 1) return false;
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
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper/*.name(*/));
    }
}

/*private*/ void AnalogMany::insertNewSocket(int index) {
    FemaleAnalogActionSocket* socket = ((DefaultAnalogActionManager*)
                                         InstanceManager::getDefault("AnalogActionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName());
    _actionEntries.insert(index, new ActionEntry(socket));

    QList</*FemaleSocket*/QVariant> addList = QList</*FemaleSocket*/QVariant>();
    addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void AnalogMany::removeSocket(int index) {
    QList</*FemaleSocket*/QVariant> removeList = QList</*FemaleSocket*/QVariant>();
    removeList.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index)->_socket));
    _actionEntries.removeAt(index);
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, QVariant());
}

/*private*/ void AnalogMany::moveSocketDown(int index) {
    ActionEntry* temp = _actionEntries.at(index);
    _actionEntries.replace(index, _actionEntries.at(index+1));
    _actionEntries.replace(index+1, temp);

    QList</*FemaleSocket*/QVariant> list = QList</*FemaleSocket*/QVariant>();
    list.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index)->_socket));
    list.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index+1)->_socket));
    firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), list);
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
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

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::connected(FemaleSocket* socket) {
    if (disableCheckForUnconnectedSocket) return;

    for (ActionEntry* entry : _actionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName =
                    socket->getConnectedSocket()->getSystemName();
        }
    }

    checkFreeSocket();
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::disconnected(FemaleSocket* socket) {
    for (ActionEntry* entry : _actionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName = "";
            break;
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AnalogMany::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Many");
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AnalogMany::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Many");
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::registerListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::unregisterListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogMany::disposeMe() {
}




/*private*/ /*final*/ /*static*/ Logger* AnalogMany::log = LoggerFactory::getLogger("AnalogMany");
