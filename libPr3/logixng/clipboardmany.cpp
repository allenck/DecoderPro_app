#include "clipboardmany.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "femalesocket.h"
#include "defaultfemaleanysocket.h"
#include "logixng_manager.h"
#include "instancemanager.h"
#include "vptr.h"
#include "abstractmalesocket.h"

/**
 * Have many items of any type.
 * <P>
 * This class is used by the clipboard.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/ class ClipboardMany extends AbstractBase
//        implements FemaleSocketListener {


    /*public*/ ClipboardMany::ClipboardMany(QString sys, QString user, QObject *parent)
            /*throw (BadUserNameException, BadSystemNameException)*/ : AbstractBase(sys, user, parent) {
        //super(sys, user);
        _itemEntries.append(new ItemEntry(new DefaultFemaleAnySocket(this, this, getNewSocketName())));
    }

    /*public*/ ClipboardMany::ClipboardMany(QString sys, QString user, QList<ItemData*> itemSystemNames, QObject *parent)
             : AbstractBase(sys, user, parent) {
        //super(sys, user);
        setItemSystemNames(itemSystemNames);
    }

    /*private*/ void ClipboardMany::setItemSystemNames(QList<ItemData*> systemNamesAndClasses) {
        if (!_itemEntries.isEmpty()) {
            throw  RuntimeException("action system names cannot be set more than once");
        }

        for (ItemData* itemData : systemNamesAndClasses) {
            FemaleAnySocket* socket =
                    new DefaultFemaleAnySocket(this, this, itemData->_socketName);

            _itemEntries.append(new ItemEntry(socket, itemData->_className, itemData->_systemName));
        }
    }

    /*public*/ QString ClipboardMany::getItemSystemName(int index) {
        return _itemEntries.value(index)->_socketSystemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ClipboardMany::setup() {
        // We don't want to check for unconnected sockets while setup sockets
        disableCheckForUnconnectedSocket = true;

        for (ItemEntry* ae : _itemEntries) {
            try {
                if ( !ae->_socket->isConnected()
                        || ae->_socket->getConnectedSocket()->getSystemName()
                                 != (ae->_socketSystemName)) {

                    QString socketSystemName = ae->_socketSystemName;
                    ae->_socket->_disconnect();
                    if (socketSystemName != nullptr) {
                        NamedBean* namedBean = ((LogixNG_Manager*)
                                InstanceManager::getDefault("LogixNG_Manager"))
                                        ->getManager(ae->_itemManagerClass)->getBySystemName(socketSystemName);

                        if (namedBean != nullptr) {
                            if (qobject_cast<AbstractMaleSocket*>(namedBean->self())) {
                                AbstractMaleSocket* maleSocket = (AbstractMaleSocket*)namedBean;
                                ae->_socket->_connect(maleSocket);
                                maleSocket->setup();
                            } else {
                                log->error("item " + socketSystemName + " is not a male socket");
                            }
                        } else {
                            log->error("cannot load item " + socketSystemName);
                        }
                    }
                } else {
                    ae->_socket->getConnectedSocket()->setup();
                }
            } catch (SocketAlreadyConnectedException ex) {
                // This shouldn't happen and is a runtime error if it does.
                throw  RuntimeException("socket is already connected");
            }
        }

        disableCheckForUnconnectedSocket = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category* ClipboardMany::getCategory() {
        return Category::COMMON;
    }

    //@Override
    /*public*/ FemaleSocket* ClipboardMany::getChild(int index)  {
        return _itemEntries.value(index)->_socket;
    }

    //@Override
    /*public*/ int ClipboardMany::getChildCount() {
        return _itemEntries.size();
    }

    /*public*/ void ClipboardMany::ensureFreeSocketAtTop() {
        if (_itemEntries.at(0)->_socket->isConnected()) {
            DefaultFemaleAnySocket* socket =
                    new DefaultFemaleAnySocket(this, this, getNewSocketName());
            _itemEntries.insert(0, new ItemEntry(socket));

            QList<DefaultFemaleAnySocket*> list = QList<DefaultFemaleAnySocket*>();
            list.append(socket);
            firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), VPtr<QList<DefaultFemaleAnySocket*>>::asQVariant(&list));
        }
    }

    //@Override
    /*public*/ void ClipboardMany::connected(FemaleSocket* socket) {
        if (disableCheckForUnconnectedSocket) return;

        for (ItemEntry* entry : _itemEntries) {
            if (socket == entry->_socket) {
                entry->_socketSystemName =
                        socket->getConnectedSocket()->getSystemName();
            }
        }
    }

    //@Override
    /*public*/ void ClipboardMany::disconnected(FemaleSocket* socket) {
        for (int i=0; i < _itemEntries.size(); i++) {
            ItemEntry* entry = _itemEntries.at(i);
            if (socket == entry->_socket) {
                entry->_socketSystemName = "";

                // Remove socket if not the first socket
                if (i > 0) {
                    QList<FemaleSocket*> list = QList<FemaleSocket*>();
                    list.append(socket);
                    _itemEntries.removeAt(i);
                    firePropertyChange(Base::PROPERTY_CHILD_COUNT, VPtr<QList<FemaleSocket*>>::asQVariant(&list), QVariant());
                }
                break;
            }
        }
    }

    //@Override
    /*public*/ QString ClipboardMany::getShortDescription(QLocale locale) {
        return tr(/*locale, */"Many");
    }

    //@Override
    /*public*/ QString ClipboardMany::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Many");
    }

    //@Override
    /*public*/ void ClipboardMany::setState(int s) /*throw (JmriException)*/ {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ int ClipboardMany::getState() {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ QString ClipboardMany::getBeanType() {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ Base* ClipboardMany::getParent()const {
        return _parent;
    }

    //@Override
    /*public*/ void ClipboardMany::setParent(Base* parent) {
        _parent = parent;
    }

    //@Override
    /*public*/ Base* ClipboardMany::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) throw  (JmriException){
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ Base* ClipboardMany::deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/ {
        throw  UnsupportedOperationException("Not supported");
    }



    /** {@inheritDoc} */
    //@Override
    /*public*/ void ClipboardMany::registerListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ClipboardMany::unregisterListenersForThisClass() {
        // Do nothing
    }

    /*private*/ QString ClipboardMany::getNewSocketName() {
        int x = 1;
        while (x < 10000) {     // Protect from infinite loop
            bool validName = true;
            for (int i=0; i < getChildCount(); i++) {
//                String name = "*" + Integer.toString(x);
                QString name = "X" + QString::number(x);
                if (name ==(getChild(i)->getName())) {
                    validName = false;
                    break;
                }
            }
            if (validName) {
//                return "*" + Integer.toString(x);
                return "X" + QString::number(x);
            }
            x++;
        }
        throw  RuntimeException("Unable to find a new socket name");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ClipboardMany::disposeMe() {
    }

    /*private*/ /*final*/ /*static*/ Logger* ClipboardMany::log = LoggerFactory::getLogger("ClipboardMany");
