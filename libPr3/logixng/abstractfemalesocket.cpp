#include "abstractfemalesocket.h"
#include "loggerfactory.h"
#include "vptr.h"
#include "conditionalng.h"
#include "logixng.h"

/**
 * Abstract female socket.
 *
 * @author Daniel Bergqvist 2019
 */
///*public*/ abstract class AbstractFemaleSocket implements FemaleSocket {



    /*public*/ AbstractFemaleSocket::AbstractFemaleSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObject)
       : QObject(parentObject){
        if (!FemaleSocket::validateName(name)) {
            throw  IllegalArgumentException("the name is not valid: " + name);
        }
        if (listener == nullptr) throw  IllegalArgumentException("FemaleSocketListener is null");
        _parent = parent;
        _listener = listener;
        _name = name;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::setEnableListeners(bool enable) {
        _enableListeners = enable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool AbstractFemaleSocket::getEnableListeners() {
        return _enableListeners;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Base* AbstractFemaleSocket::getParent() const {
        return _parent;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::setParent(/*@Nonnull*/ Base* parent) {
        _parent = parent;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool AbstractFemaleSocket::setParentForAllChildren(QList<QString> errors) {
        if (isConnected()) {
            getConnectedSocket()->Base::setParent(this);
            return getConnectedSocket()->setParentForAllChildren(errors);
        }
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::_connect(MaleSocket* socket) /*throw (SocketAlreadyConnectedException)*/ {
        if (socket == nullptr) {
            throw  NullPointerException("socket cannot be null");
        }

        if (_listenersAreRegistered) {
            throw  UnsupportedOperationException("A socket must not be connected when listeners are registered");
        }

        if (isConnected()) {
            throw  SocketAlreadyConnectedException("Socket is already connected");
        }

        if (!isCompatible(socket)) {
            throw  IllegalArgumentException("Socket "+QString(socket->self()->metaObject()->className())+" is not compatible with "+ QString(this->self()->metaObject()->className()));
//            throw new IllegalArgumentException("Socket "+socket.getClass().getName()+" is not compatible with "+this.getClass().getName()+". Socket.getObject: "+socket.getObject().getClass().getName());
        }

        _socket = socket;
        _socket->Base::setParent(this);
        _listener->connected(this);
        pcs->firePropertyChange(new PropertyChangeEvent(this, Base::PROPERTY_SOCKET_CONNECTED, QVariant(), VPtr<MaleSocket>::asQVariant(_socket)));
//        pcs->firePropertyChange(Base.PROPERTY_SOCKET_CONNECTED, null, _socket);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::_disconnect() {
        MaleSocket* maleSocket = _socket;

        if (_socket == nullptr) {
            return;
        }

        if (_listenersAreRegistered) {
            throw  UnsupportedOperationException("A socket must not be disconnected when listeners are registered");
        }

        _socket->Base::setParent(nullptr);
        _socket = nullptr;
        _listener->disconnected(this);
        pcs->firePropertyChange(new PropertyChangeEvent(this, Base::PROPERTY_SOCKET_DISCONNECTED, VPtr<MaleSocket>::asQVariant(maleSocket), QVariant()));
//        pcs->firePropertyChange(Base.PROPERTY_SOCKET_DISCONNECTED, null, _socket);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* AbstractFemaleSocket::getConnectedSocket() {
        return _socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool AbstractFemaleSocket::isConnected() {
        return _socket != nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*final*/ bool AbstractFemaleSocket::validateName(QString name, bool ignoreDuplicateErrors) {
        // Empty name is not allowed
        if (name.isEmpty()) return false;

        // The name must start with a letter
        if (!name.at(0).isLetter()) return false;

        // The name must consist of letters, digits or underscore
        for (int i=0; i < name.length(); i++) {
            if (!name.at(i).isLetterOrNumber() && (name.at(i) != '_')) {
                return false;
            }
        }

        if (!ignoreDuplicateErrors && (_parent != nullptr)) {
            // Check that no other female socket of the parent has the same name
            for (int i=0; i < _parent->getChildCount(); i++) {
                FemaleSocket* child = _parent->getChild(i);
                if ((child != this) && name ==(child->getName())) return false;
            }
        }

        // The name is valid
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::setName(QString name, bool ignoreDuplicateErrors) {
        if (!validateName(name, ignoreDuplicateErrors)) {
            throw  IllegalArgumentException("the name is not valid: " + name);
        }
        _name = name;
        _listener->socketNameChanged(this);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString AbstractFemaleSocket::getName() {
        return _name;
    }

    //abstract /*public*/ void disposeMe();

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*final*/ void AbstractFemaleSocket::dispose() {
        if (_listenersAreRegistered) {
            throw new UnsupportedOperationException("This is not currently supported");
        }

        if (isConnected()) {
            MaleSocket* aSocket = getConnectedSocket();
            disconnect();
            aSocket->dispose();
        }
        disposeMe();
    }

    /**
     * Register listeners if this object needs that.
     * <P>
     * Important: This method may be called more than once. Methods overriding
     * this method must ensure that listeners are not registered more than once.
     */
    /*protected*/ void AbstractFemaleSocket::registerListenersForThisClass() {
        // Do nothing
    }

    /**
     * Unregister listeners if this object needs that.
     * <P>
     * Important: This method may be called more than once. Methods overriding
     * this method must ensure that listeners are not unregistered more than once.
     */
    /*protected*/ void AbstractFemaleSocket::unregisterListenersForThisClass() {
        // Do nothing
    }

    /**
     * Register listeners if this object needs that.
     */
    //@Override
    /*public*/ void AbstractFemaleSocket::registerListeners() {
        if (!_enableListeners) return;

        _listenersAreRegistered = true;
        registerListenersForThisClass();
        if (isConnected()) {
            getConnectedSocket()->registerListeners();
        }
    }

    /**
     * Register listeners if this object needs that.
     */
    //@Override
    /*public*/ void AbstractFemaleSocket::unregisterListeners() {
        if (!_enableListeners) return;

        unregisterListenersForThisClass();
        if (isConnected()) {
            getConnectedSocket()->unregisterListeners();
        }
        _listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*final*/ bool AbstractFemaleSocket::isActive() {
        return isEnabled() && ((_parent == nullptr) || _parent->isActive());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category* AbstractFemaleSocket::getCategory() {
        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ FemaleSocket* AbstractFemaleSocket::getChild(int index)  {
        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int AbstractFemaleSocket::getChildCount() {
        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString AbstractFemaleSocket::getUserName() const{
        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::setUserName(QString s)  {
        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString AbstractFemaleSocket::getComment() {
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::setComment(QString s) {
        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString AbstractFemaleSocket::getSystemName() const {
        return getParent()->getSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*final*/ ConditionalNG* AbstractFemaleSocket::getConditionalNG() {
        if (_parent == nullptr) return nullptr;
        return _parent->getConditionalNG();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*final*/ LogixNG* AbstractFemaleSocket::getLogixNG() {
        if (_parent == nullptr) return nullptr;
        return _parent->getLogixNG();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*final*/ Base* AbstractFemaleSocket::getRoot() {
        if (_parent == nullptr) return nullptr;
        return _parent->getRoot();
    }

    /*protected*/ void AbstractFemaleSocket::printTreeRow(
            PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString currentIndent,
            /*MutableInt*/int  lineNumber) {

        if (settings->_printLineNumbers) {
            writer->print(QString(PRINT_LINE_NUMBERS_FORMAT).arg(lineNumber/*.addAndGet(1)*/++));
        }
        writer->print(currentIndent);
        writer->print(getLongDescription(locale));
        writer->println();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::printTree(
            PrintTreeSettings* settings,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int  lineNumber) {

        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::printTree(
            PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int  lineNumber) {

        throw  UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::printTree(
            PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            QString currentIndent,
            /*MutableInt*/int  lineNumber) {

        printTreeRow(settings, locale, writer, currentIndent, lineNumber);

        if (isConnected()) {
            getConnectedSocket()->printTree(settings, locale, writer, indent, currentIndent+indent, lineNumber);
        } else {
            if (settings->_printLineNumbers) {
                writer->print(QString(PRINT_LINE_NUMBERS_FORMAT).arg(lineNumber/*.addAndGet(1)*/++));
            }
            writer->print(currentIndent);
            writer->print(indent);
            if (settings->_printNotConnectedSockets) writer->print("Socket not connected");
            writer->println();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
        log->debug(tr("** %1 :: %2").arg(level).arg(this->getLongDescription()));
        level++;

        if (isConnected()) {
            getConnectedSocket()->getUsageTree(level, bean, report, cdl);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::getUsageDetail(int /*level*/, NamedBean* /*bean*/, QList<NamedBeanUsageReport*> /*report*/, NamedBean* /*cdl*/) {
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::addPropertyChangeListener(PropertyChangeListener* listener) {
        pcs->SwingPropertyChangeSupport::addPropertyChangeListener(listener);
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
        pcs->SwingPropertyChangeSupport::addPropertyChangeListener(propertyName, listener);
    }

    //@Override
    /*public*/ QVector<PropertyChangeListener*> AbstractFemaleSocket::getPropertyChangeListeners() const{
        return pcs->getPropertyChangeListeners();
    }

    //@Override
    /*public*/ QVector<PropertyChangeListener*> AbstractFemaleSocket::getPropertyChangeListeners(QString propertyName) {
        return pcs->getPropertyChangeListeners(propertyName);
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::removePropertyChangeListener(PropertyChangeListener* listener) {
        pcs->removePropertyChangeListener(listener);
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
        pcs->removePropertyChangeListener(propertyName, listener);
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::addPropertyChangeListener(PropertyChangeListener* listener, QString name, QString listenerRef) {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener, QString name, QString listenerRef) {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::updateListenerRef(PropertyChangeListener* l, QString newName) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ void AbstractFemaleSocket::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ QString AbstractFemaleSocket::getListenerRef(PropertyChangeListener* l) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/QList<QString>AbstractFemaleSocket:: getListenerRefs() {
        throw  UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ int AbstractFemaleSocket::getNumPropertyChangeListeners() {
        return pcs->getPropertyChangeListeners().length();
    }

    //@Override
    /*public*/ QList<PropertyChangeListener*> AbstractFemaleSocket::getPropertyChangeListenersByReference(QString name) {
        throw  UnsupportedOperationException("Not supported");
     return QList<PropertyChangeListener*>();
    }

    /**
     * Do something on every item in the sub tree of this item.
     * @param r the action to do on all items.
     */
    //@Override
    /*public*/ void AbstractFemaleSocket::forEntireTree(RunnableWithBase* r) {
        r->run(this);
        if (isConnected()) getConnectedSocket()->forEntireTree(r);
    }

    //@Override
    /*public*/ Base* AbstractFemaleSocket::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/ {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/ Base* AbstractFemaleSocket::deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/ {
        throw  UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractFemaleSocket::getListenerRefsIncludingChildren(QList<QString> list) {
        if (isConnected()) {
            getConnectedSocket()->getListenerRefsIncludingChildren(list);
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* AbstractFemaleSocket::log = LoggerFactory::getLogger("AbstractFemaleSocket");
