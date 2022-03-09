#include "digitalbooleanmany.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "femalesocketoperation.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "vptr.h"
/**
 * Execute many Actions in a specific order.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DigitalBooleanMany extends AbstractDigitalBooleanAction
//        implements FemaleSocketListener {


/*public*/  DigitalBooleanMany::DigitalBooleanMany(QString sys, QString user, QObject* parent)
 : AbstractDigitalBooleanAction(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    setObjectName("DigitalBooleanMany");
    //super(sys, user);
    _actionEntries
            .append(new ActionEntry(((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName())));
}

/*public*/  DigitalBooleanMany::DigitalBooleanMany(QString sys, QString user, QList<QMap<QString, QString>> actionSystemNames, QObject* parent)
 : AbstractDigitalBooleanAction(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
 setObjectName("DigitalBooleanMany");

    setActionSystemNames(actionSystemNames);
}

//@Override
/*public*/  Base* DigitalBooleanMany::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
    DigitalBooleanActionManager* manager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
    QString sysName = systemNames.value(getSystemName());
    QString userName = userNames.value(getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    DigitalBooleanMany* copy = new DigitalBooleanMany(sysName, userName);
    copy->setComment(getComment());
    copy->setNumSockets(getChildCount());
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*private*/ void DigitalBooleanMany::setActionSystemNames(QList<QMap<QString, QString>> systemNames) {
    if (!_actionEntries.isEmpty()) {
        throw new RuntimeException("action system names cannot be set more than once");
    }

    for (QMap<QString, QString> map : systemNames) {
     QMapIterator<QString, QString> entry(map);
       while(entry.hasNext())
     {
        FemaleDigitalBooleanActionSocket* socket = ((DefaultDigitalBooleanActionManager*)
                InstanceManager::getDefault("DigitalBooleanActionManager"))
                        ->createFemaleSocket(this, this, entry.key());

        _actionEntries.append(new ActionEntry(socket, entry.value()));
     }
    }
}

/*public*/  QString DigitalBooleanMany::getActionSystemName(int index) {
    return _actionEntries.at(index)->_socketSystemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanMany::setup() {
    // We don't want to check for unconnected sockets while setup sockets
    disableCheckForUnconnectedSocket = true;

    for (ActionEntry* ae : _actionEntries) {
        try {
            if ( !ae->_socket->isConnected()
                    || ae->_socket->getConnectedSocket()->getSystemName()
                             != (ae->_socketSystemName)) {

                QString socketSystemName = ae->_socketSystemName;
                ae->_socket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalBooleanActionManager)
                            InstanceManager::getDefault("DigitalBooleanActionManager"))
                                    .getBySystemName(socketSystemName)->self();
                    if (maleSocket != nullptr) {
                        ae->_socket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital action " + socketSystemName);
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

//        checkFreeSocket();

    disableCheckForUnconnectedSocket = false;
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* DigitalBooleanMany::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanMany::execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ {
    for (ActionEntry* actionEntry : _actionEntries) {
        actionEntry->_socket->execute(hasChangedToTrue, hasChangedToFalse);
    }
}

//@Override
/*public*/  FemaleSocket* DigitalBooleanMany::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    return _actionEntries.at(index)->_socket;
}

//@Override
/*public*/  int DigitalBooleanMany::getChildCount() {
    return _actionEntries.size();
}

// This method ensures that we have enough of children
/*private*/ void DigitalBooleanMany::setNumSockets(int num) {
    QList<QVariant> addList = QList<QVariant>();

    // Is there not enough children?
    while (_actionEntries.size() < num) {
        FemaleDigitalBooleanActionSocket* socket = ((DefaultDigitalBooleanActionManager*)
                InstanceManager::getDefault("DigitalBooleanActionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _actionEntries.append(new ActionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void DigitalBooleanMany::checkFreeSocket() {
    bool hasFreeSocket = false;

    for (ActionEntry* entry : _actionEntries) {
        hasFreeSocket |= !entry->_socket->isConnected();
    }
    if (!hasFreeSocket) {
        FemaleDigitalBooleanActionSocket* socket =((DefaultDigitalBooleanActionManager*)
                InstanceManager::getDefault("DigitalBooleanActionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _actionEntries.append(new ActionEntry(socket));

        QList<QVariant> list = QList<QVariant>();
        list.append(VPtr<FemaleSocket>::asQVariant(socket));
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), list);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DigitalBooleanMany::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
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
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
    }
}

/*private*/ void DigitalBooleanMany::insertNewSocket(int index) {
    FemaleDigitalBooleanActionSocket* socket =((DefaultDigitalBooleanActionManager*)
            InstanceManager::getDefault("DigitalBooleanActionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName());
    _actionEntries.insert(index, new ActionEntry(socket));

    QList<QVariant> addList = QList<QVariant>();
    addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void DigitalBooleanMany::removeSocket(int index) {
    QList<QVariant> removeList = QList<QVariant>();
    removeList.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index)->_socket));
    _actionEntries.removeAt(index);
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, QVariant());
}

/*private*/ void DigitalBooleanMany::moveSocketDown(int index) {
    ActionEntry* temp = _actionEntries.at(index);
    _actionEntries.replace(index, _actionEntries.at(index+1));
    _actionEntries.replace(index+1, temp);

    QList<QVariant> list = QList<QVariant>();
    list.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index)->_socket));
    list.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index+1)->_socket));
    firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), list);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanMany::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
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
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
    }
}

//@Override
/*public*/  void DigitalBooleanMany::connected(FemaleSocket* socket) {
    if (disableCheckForUnconnectedSocket) return;

    for (ActionEntry* entry : _actionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName =
                    socket->getConnectedSocket()->getSystemName();
        }
    }

    checkFreeSocket();
}

//@Override
/*public*/  void DigitalBooleanMany::disconnected(FemaleSocket* socket) {
    for (ActionEntry* entry : _actionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName = "";
            break;
        }
    }
}

//@Override
/*public*/  QString DigitalBooleanMany::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Many");
}

//@Override
/*public*/  QString DigitalBooleanMany::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "Many");
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanMany::registerListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanMany::unregisterListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalBooleanMany::disposeMe() {
}




/*private*/ /*final*/ /*static*/ Logger* DigitalBooleanMany::log = LoggerFactory::getLogger("DigitalBooleanMany");
