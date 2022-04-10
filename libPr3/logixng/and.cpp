#include "and.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "vptr.h"

/**
 * Evaluates to True if all of the children expressions evaluate to true.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class And extends AbstractDigitalExpression implements FemaleSocketListener {


/*public*/  And::And(QString sys, QString user, QObject *parent ) : AbstractDigitalExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
    setObjectName("And");
    _expressionEntries
            .append(new ExpressionEntry(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName())));
}

/*public*/  And::And(QString sys, QString user, QList<QMap<QString, QString>> expressionSystemNames,
                     QObject* parent) : AbstractDigitalExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
 setObjectName("And");

    setExpressionSystemNames(expressionSystemNames);
}

//@Override
/*public*/  Base* And::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    And* copy = new And(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    copy->setNumSockets(getChildCount());
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*private*/ void And::setExpressionSystemNames(QList<QMap<QString, QString>> systemNames) {
    if (!_expressionEntries.isEmpty()) {
        throw new RuntimeException("expression system names cannot be set more than once");
    }

    for (QMap<QString, QString> map : systemNames) {
     QMapIterator<QString, QString> entry(map);
     while(entry.hasNext())
     {
      entry.next();
        FemaleDigitalExpressionSocket* socket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, entry.key());

        _expressionEntries.append(new ExpressionEntry(socket, entry.value()));
     }
    }
}

/*public*/  QString And::getExpressionSystemName(int index) {
    return _expressionEntries.at(index)->_socketSystemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* And::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool And::evaluate() /*throws JmriException*/ {
    bool result = true;
    for (ExpressionEntry* e : _expressionEntries) {
        if (e->_socket->isConnected() && !e->_socket->evaluate()) {
            result = false;
        }
    }
    return result;
}

//@Override
/*public*/  FemaleSocket* And::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    return _expressionEntries.at(index)->_socket;
}

//@Override
/*public*/  int And::getChildCount() {
    return _expressionEntries.size();
}

//@Override
/*public*/  QString And::getShortDescription(QLocale locale) {
    return tr(/*locale, */"And");
}

//@Override
/*public*/  QString And::getLongDescription(QLocale locale) {
    return tr(/*locale,*/ "And");
}

// This method ensures that we have enough of children
/*private*/ void And::setNumSockets(int num) {
    QList<QVariant> addList = QList<QVariant>();

    // Is there not enough children?
    while (_expressionEntries.size() < num) {
        FemaleDigitalExpressionSocket* socket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void And::checkFreeSocket() {
    bool hasFreeSocket = false;

    for (ExpressionEntry* entry : _expressionEntries) {
        hasFreeSocket |= !entry->_socket->isConnected();
    }
    if (!hasFreeSocket) {
        FemaleDigitalExpressionSocket* socket =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));

        QList<QVariant> list = QList<QVariant>();
        list.append(VPtr<FemaleSocket>::asQVariant(socket));
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), list);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  bool And::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
    switch (oper) {
        case FemaleSocketOperation::Remove:        // Possible if socket is not connected
            return ! getChild(index)->isConnected();
        case FemaleSocketOperation::InsertBefore:
            return true;    // Always possible
        case FemaleSocketOperation::FemaleSocketOperation::InsertAfter:
            return true;    // Always possible
        case FemaleSocketOperation::MoveUp:
            return index > 0;   // Possible if not first socket
        case FemaleSocketOperation::MoveDown:
            return index+1 < getChildCount();   // Possible if not last socket
        default:
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
    }
}

/*private*/ void And::insertNewSocket(int index) {
    FemaleDigitalExpressionSocket* socket = ((DefaultDigitalExpressionManager*)
            InstanceManager::getDefault("DigitalExpressionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName());
    _expressionEntries.insert(index, new ExpressionEntry(socket));

    QVariantList addList = QVariantList();
    addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void And::removeSocket(int index) {
    QVariantList removeList = QVariantList();
    removeList.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    _expressionEntries.removeAt(index);
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, QVariant());
}

/*private*/ void And::moveSocketDown(int index) {
    ExpressionEntry* temp = _expressionEntries.at(index);
    _expressionEntries.insert(index, _expressionEntries.at(index+1));
    _expressionEntries.insert(index+1, temp);

    QVariantList list = QVariantList();
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.value(index)->_socket));
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.value(index)->_socket));
    firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), list);
}

/** {@inheritDoc} */
//@Override
/*public*/  void And::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
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
/*public*/  void And::connected(FemaleSocket* socket) {
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
/*public*/  void And::disconnected(FemaleSocket* socket) {
    for (ExpressionEntry* entry : _expressionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName = nullptr;
            break;
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void And::setup() {
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



/** {@inheritDoc} */
//@Override
/*public*/  void And::registerListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void And::unregisterListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void And::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* And::log = LoggerFactory::getLogger("And");
