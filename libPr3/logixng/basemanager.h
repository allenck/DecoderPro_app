#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include "manager.h"
#include "malesocket.h"

class MaleSocketFactory;
/**
 * Base interface for the LogixNG action and expression managers.
 *
 * @param <E> the type of NamedBean supported by this manager
 *
 * @author Daniel Bergqvist 2020
 */
/*public*/ /*interface*/class BaseManager : public Manager /*<E extends NamedBean> extends Manager<E>*/
{

    /**
     * Remember a NamedBean Object created outside the manager.
     * <p>
     * The non-system-specific SignalHeadManagers use this method extensively.
     *
     * @param maleSocket the bean
     * @return the registered bean with attached male sockets
     * @throws NamedBean.DuplicateSystemNameException if a different bean with the same
     *                                                system name is already registered in
     *                                                the manager
     */
    /*public*/virtual NamedBean* _registerBean(/*@Nonnull*/ /*E*/MaleSocket* maleSocket)=0;

    /**
     * Method for a UI to delete a bean.
     * <p>
     * The UI should first request a "CanDelete", this will return a list of
     * locations (and descriptions) where the bean is in use via throwing a
     * VetoException, then if that comes back clear, or the user agrees with the
     * actions, then a "DoDelete" can be called which inform the listeners to
     * delete the bean, then it will be deregistered and disposed of.
     * <p>
     * If a property name of "DoNotDelete" is thrown back in the VetoException
     * then the delete process should be aborted.
     *
     * @param maleSocket The MaleSocket to be deleted
     * @param property   The programmatic name of the request. "CanDelete" will
     *                   enquire with all listeners if the item can be deleted.
     *                   "DoDelete" tells the listener to delete the item
     * @throws java.beans.PropertyVetoException If the recipients wishes the
     *                                          delete to be aborted (see above)
     */
    /*public*/ virtual void deleteBean(/*@Nonnull*/ MaleSocket* maleSocket, /*@Nonnull*/ QString property) throw (PropertyVetoException)=0;

    /**
     * Get the default male socket class
     * @return the class
     */
    /*public*/ virtual Class/*<? extends MaleSocket>*/* getMaleSocketClass()=0;

    /**
     * Get the last item registered in the mananger.
     * @return the last item
     */
    /*public*/ virtual MaleSocket* getLastRegisteredMaleSocket()=0;

    /**
     * Register a male socket factory.
     * @param factory the factory
     */
    /*public*/ virtual void registerMaleSocketFactory(MaleSocketFactory/*<E>*/* factory)=0;

};
#endif // BASEMANAGER_H