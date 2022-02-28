#include "digitalmany.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "digitalactionmanager.h"
#include "runtimeexception.h"
#include "vptr.h"
#include "defaultdigitalactionmanager.h"

/**
 * Execute many Actions in a specific order.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DigitalMany extends AbstractDigitalAction
//        implements FemaleSocketListener {


    /*public*/  DigitalMany::DigitalMany(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
     setObjectName("DigitalMany");
        //super(sys, user);
        _actionEntries
                .append(new ActionEntry(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName())));
    }

    /*public*/  DigitalMany::DigitalMany(QString sys, QString user, QList<QMap<QString, QString>> actionSystemNames, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/
      : AbstractDigitalAction(sys, user, parent)
    {
        //super(sys, user);
       setObjectName("DigitalMany"); setActionSystemNames(actionSystemNames);
    }

    //@Override
    /*public*/  Base* DigitalMany::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames.value(AbstractBase::getSystemName());
        QString userName = userNames.value(AbstractBase::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        DigitalMany* copy = new DigitalMany(sysName, userName);
        copy->AbstractBase::setComment(AbstractBase::getComment());
        copy->setNumSockets(getChildCount());
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*private*/ void DigitalMany::setActionSystemNames(QList<QMap<QString, QString>> systemNames) {
        if (!_actionEntries.isEmpty()) {
            throw new RuntimeException("action system names cannot be set more than once");
        }

        for (QMap<QString, QString> map : systemNames) {
         QMapIterator<QString, QString> entry(map);
         entry.next();
            FemaleDigitalActionSocket* socket = ((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->createFemaleSocket(this, this, entry.key());

            _actionEntries.append(new ActionEntry(socket, entry.value()));
        }
    }

    /*public*/  QString DigitalMany::getActionSystemName(int index) {
        return _actionEntries.at(index)->_socketSystemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalMany::setup() {
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
                        MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalActionManager*)
                                InstanceManager::getDefault("DigitalActionManager"))
                                        ->getBySystemName(socketSystemName);
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
    /*public*/  Category* DigitalMany::getCategory() {
        return Category::COMMON;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalMany::execute() /*throws JmriException*/  {
        for (ActionEntry* actionEntry : _actionEntries) {
            actionEntry->_socket->execute();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleSocket* DigitalMany::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        return _actionEntries.at(index)->_socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int DigitalMany::getChildCount() {
        return _actionEntries.size();
    }

    // This method ensures that we have enough of children
    /*private*/ void DigitalMany::setNumSockets(int num) {
        QList</*FemaleSocket**/QVariant> addList =QList</*FemaleSocket**/QVariant>();

        // Is there not enough children?
        while (_actionEntries.size() < num) {
            FemaleDigitalActionSocket* socket = (FemaleDigitalActionSocket*)((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->createFemaleSocket(this, this, getNewSocketName());
            _actionEntries.append(new ActionEntry(socket));
            addList.append(VPtr<FemaleSocket>::asQVariant(socket));
        }
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
    }

    /*private*/ void DigitalMany::checkFreeSocket() {
        bool hasFreeSocket = false;

        for (ActionEntry* entry : _actionEntries) {
            hasFreeSocket |= !entry->_socket->isConnected();
        }
        if (!hasFreeSocket) {
            FemaleDigitalActionSocket* socket = ((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->createFemaleSocket(this, this, getNewSocketName());
            _actionEntries.append(new ActionEntry(socket));

            QList</*FemaleSocket**/QVariant> list = QList</*FemaleSocket**/QVariant>();
            list.append(VPtr<FemaleSocket>::asQVariant(socket));
            firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), list);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DigitalMany::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
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
                throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString( oper/*.name()*/));
        }
    }

    /*private*/ void DigitalMany::insertNewSocket(int index) {
        FemaleDigitalActionSocket* socket = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _actionEntries.insert(index, new ActionEntry(socket));

        QList</*FemaleSocket**/QVariant> addList = QList</*FemaleSocket**/QVariant>();
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
    }

    /*private*/ void DigitalMany::removeSocket(int index) {
        QList</*FemaleSocket**/QVariant> removeList = QList</*FemaleSocket**/QVariant>();
        removeList.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index)->_socket));
        _actionEntries.removeAt(index);
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, QVariant());
    }

    /*private*/ void DigitalMany::moveSocketDown(int index) {
        ActionEntry* temp = _actionEntries.at(index);
        _actionEntries.replace(index, _actionEntries.at(index+1));
        _actionEntries.replace(index+1, temp);

        QList</*FemaleSocket**/QVariant> list = QList</*FemaleSocket**/QVariant>();
        list.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index)->_socket));
        list.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(index+1)->_socket));
        firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), list);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalMany::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
        switch (oper) {
            case FemaleSocketOperation::TYPES::Remove:
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
                throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString( oper/*.name()*/));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalMany::connected(FemaleSocket* socket) {
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
    /*public*/  void DigitalMany::disconnected(FemaleSocket* socket) {
        for (ActionEntry* entry : _actionEntries) {
            if (socket == entry->_socket) {
                entry->_socketSystemName = "";
                break;
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DigitalMany::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Many");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DigitalMany::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Many");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalMany::registerListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalMany::unregisterListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalMany::disposeMe() {
    }




    /*private*/ /*final*/ /*static*/ Logger* DigitalMany::log = LoggerFactory::getLogger("DigitalMany");
