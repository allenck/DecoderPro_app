#ifndef ANALOGACTIONMANAGER_H
#define ANALOGACTIONMANAGER_H
#include "basemanager.h"
#include "maleanalogactionsocket.h"
#include "femaleanalogactionsocket.h"
#include "femalesocketlistener.h"
#include "category.h"
/**
 * Manager for AnalogActionBean
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
/*public*/ /*interface*/ class AnalogActionManager : public BaseManager/*<MaleAnalogActionSocket>*/ {
     Q_INTERFACES(BaseManager)
 public:
    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleAnalogActionSocket for the action.
     *
     * @param action the bean
     * @return the male socket for this action
     * @throws IllegalArgumentException if the action has an invalid system name
     */
    /*public*/virtual  MaleAnalogActionSocket* registerAction(/*@Nonnull*/ AnalogActionBean* action)
            /*throws IllegalArgumentException*/;

    /**
     * Create a new system name for an AnalogActionBean.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName()=0;

    /*public*/ FemaleAnalogActionSocket* createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName);

    /**
     * Get a set of classes that implements the DigitalAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ QMap<Category*, QList</*Class<? extends Base>*/QString >* > getActionClasses();

    /*.*
     * Add an Action.
     *
     * @param action the action to add
     * @throws IllegalArgumentException if the action has an invalid system name
     */
//    public void addAction(Action action)
//            throws IllegalArgumentException;

    /*.*
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
//    public Action getAction(String name);

//    public Action getByUserName(String s);

//    public Action getBySystemName(String s);

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the AnalogActionManager is
     * {@link #getSystemNamePrefix() } and "AA";
     */
    //@Override
    /*public*/ /*default*/virtual QString getSubSystemNamePrefix()  {
        return getSystemNamePrefix() + "AA";
    }

    /**
     * Delete Action by removing it from the manager. The Action must first be
     * deactivated so it stops processing.
     *
     * @param x the Action to delete
     */
    /*public*/ virtual void deleteAnalogAction(MaleAnalogActionSocket* x) =0;

};
Q_DECLARE_INTERFACE(AnalogActionManager, "AnalogActionManager")
#endif // ANALOGACTIONMANAGER_H
