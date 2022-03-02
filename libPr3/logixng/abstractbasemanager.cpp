#include "abstractbasemanager.h"
#include "femalesocket.h"
#include "abstractmalesocket.h"
#include "logixng_manager.h"
#include "malesocketfactory.h"
#include "vptr.h"

/**
 * Abstract partial implementation for the LogixNG action and expression managers.
 *
 * @param <E> the type of NamedBean supported by this manager
 *
 * @author Daniel Bergqvist 2020
 */
// /*public*/  abstract class AbstractBaseManager<E extends NamedBean> extends AbstractManager<E> implements BaseManager<E> {



    /**
     * Inform all registered listeners of a vetoable change.If the propertyName
     * is "CanDelete" ALL listeners with an interest in the bean will throw an
     * exception, which is recorded returned back to the invoking method, so
     * that it can be presented back to the user.However if a listener decides
     * that the bean can not be deleted then it should throw an exception with
     * a property name of "DoNotDelete", this is thrown back up to the user and
     * the delete process should be aborted.
     *
     * @param p   The programmatic name of the property that is to be changed.
     *            "CanDelete" will inquire with all listeners if the item can
     *            be deleted. "DoDelete" tells the listener to delete the item.
     * @param old The old value of the property.
     * @throws java.beans.PropertyVetoException If the recipients wishes the
     *                                          delete to be aborted (see above)
     */
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void AbstractBaseManager::fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException*/ {
        PropertyChangeEvent* evt = new PropertyChangeEvent(this, p, old, QVariant());
        for (VetoableChangeListener* vc : vetoableChangeSupport->getVetoableChangeListeners()) {
            vc->vetoableChange(evt);
        }
    }

    /**
     * Cast the maleSocket to E
     * This method is needed since SpotBugs @SuppressWarnings("unchecked")
     * does not work for the cast: (E)socket.
     * @param maleSocket the maleSocket to cast
     * @return the maleSocket as E
     */
    //protected abstract E castBean(MaleSocket maleSocket);

    /** {@inheritDoc} */
    //@Override
//    @OverridingMethodsMustInvokeSuper
    /*public*/  /*final*/ void AbstractBaseManager::deleteBean(/*@Nonnull*/NamedBean* n, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/ {
        this->deleteBean((MaleSocket*)n, property);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
//    @SuppressWarnings("unchecked")  // cast in "deregister((E)socket)" is nessesary and cannot be avoided
    /*public*/  void AbstractBaseManager::deleteBean(/*@Nonnull*/ MaleSocket* socket, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/ {
        for (int i=0; i < socket->getChildCount(); i++) {
            FemaleSocket* child = socket->getChild(i);
            if (child->isConnected()) {
                MaleSocket* maleSocket = child->getConnectedSocket();
                maleSocket->getManager()->deleteBean(maleSocket, property);
            }
        }

        // throws PropertyVetoException if vetoed
        fireVetoableChange(property, VPtr<MaleSocket>::asQVariant(socket));
        if (property == ("DoDelete")) { // NOI18N
            deregister(castBean(socket));
            socket->dispose();
        }
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void AbstractBaseManager::deregister(/*@Nonnull*/ NamedBean* s) {
        // A LogixNG action or expression is contained in one or more male
        // sockets. A male socket might be contained in another male socket.
        // In some cases, it seems that the male socket used in this call is
        // not the male socket that's registered in the manager. To resolve
        // this, we search for the registered bean with the system name and
        // then deregister the bean we have found.
        NamedBean*bean = AbstractManager::getBySystemName(s->getSystemName());
        if (bean == nullptr) {
            // This should never happen.
            throw new IllegalArgumentException(s->getSystemName() + " is not registered in manager");
        }
        AbstractManager::deregister(bean);
    }

    /**
     * Test if parameter is a properly formatted system name.
     *
     * @param systemName the system name
     * @return enum indicating current validity, which might be just as a prefix
     */
    //@Override
    /*public*/  /*final*/ Manager::NameValidity AbstractBaseManager::validSystemNameFormat(QString systemName) {
        return LogixNG_Manager::ng_validSystemNameFormat(
                getSubSystemNamePrefix(), systemName);
    }

    //@Override
    /*public*/  void AbstractBaseManager::Register(/*@Nonnull*/ NamedBean* s) {
        throw new RuntimeException("Use BaseManager.registerBean() instead");
    }

    //@Override
    /*public*/  NamedBean* AbstractBaseManager::registerBean(/*@Nonnull*/ NamedBean* s) {
        if(!s)
         throw new NullPointerException("required bean is null!");
        MaleSocket* bean = (AbstractMaleSocket*)s;
        for (MaleSocketFactory/*<E>*/* factory : _maleSocketFactories) {
            bean = factory->encapsulateMaleSocket(this, bean);
        }
        BaseManager::Register(s);
        return (NamedBean*)bean;
    }

    //@Override
    /*public*/  void AbstractBaseManager::registerMaleSocketFactory(MaleSocketFactory/*<E>*/* factory) {
        _maleSocketFactories.append(factory);
    }
