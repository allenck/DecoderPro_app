#ifndef PROXYMANAGER_H
#define PROXYMANAGER_H
#include "manager.h"

#endif // PROXYMANAGER_H
/**
 * Interface for Managers of NamedBeans that are proxies for a collection of
 * Managers for the same type of NamedBean.
 *
 * @author Randall Wood Copyright 2019
 * @param <B> type of supported NamedBean
 */
template<class B>
/*public*/ class  ProxyManager/*<B /*extends NamedBean>*/ : public Manager<B> {

    /**
     * Add a Manager to the collection of Managers.
     *
     * @param manager the Manager to add; if manager has already been added, it
     *                will not be added again
     */
 /*public*/ virtual void addManager(/*@Nonnull*/ Manager<B> manager) {}

    /**
     * Get the default manager or the internal manager if no default manager has
     * been set.
     *
     * @return the default manager or the internal manager
     */
    /*@Nonnull*/
 /*public*/ virtual Manager<B> getDefaultManager() {return Manager<B>();}

    /**
     * Returns a list of all managers, including the internal manager. This is
     * not a live list, but it is in alpha order (don't assume default is at
     * front)
     *
     * @return the list of managers
     */
 /*public*/ virtual QList<Manager<B>> getManagerList() {return QList<Manager<B>>();}

    /**
     * Get a list of all managers, with the default as the first item and internal
     * default as the last item.
     *
     * @return the list of managers
     */
    /*public*/ virtual QList<Manager<B>> getDisplayOrderManagerList() {return QList<Manager<B>>();}
};
