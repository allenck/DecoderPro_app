#ifndef DIGITALBOOLEANACTIONMANAGER_H
#define DIGITALBOOLEANACTIONMANAGER_H
#include "basemanager.h"
#include "maledigitalbooleanactionsocket.h"
#include "femaledigitalbooleanactionsocket.h"
#include "category.h"
#include "femalesocketlistener.h"

/**
 * Manager for DigitalBooleanActionBean
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
/*public*/ /*interface*/class  DigitalBooleanActionManager : public BaseManager/*<MaleDigitalBooleanActionSocket>*/ {
  Q_INTERFACES(BaseManager)
public:
    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleDigitalBooleanAction for the action.
     *
     * @param action the bean
     * @return the male socket for this action
     * @throws IllegalArgumentException if the action has an invalid system name
     */
    /*public*/ virtual MaleDigitalBooleanActionSocket* registerAction(/*@Nonnull*/ DigitalBooleanActionBean* action)
            /*throws IllegalArgumentException*/=0;

    /**
     * Create a new system name for an DigitalBooleanActionBean.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName()=0;

    /*public*/ virtual FemaleDigitalBooleanActionSocket* createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName)=0;

    /**
     * Get a set of classes that implements the DigitalBooleanActionBean interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QMap<Category*, QList<QString> > getActionClasses()=0;

    /*.*
     * Add an DigitalBooleanActionBean.
     *
     * @param action the action to add
     * @throws IllegalArgumentException if the action has an invalid system name
     */
//    public void addAction(DigitalBooleanActionBean action)
//            throws IllegalArgumentException;

    /*.*
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
//    public DigitalBooleanActionBean getAction(String name);

//    public DigitalBooleanActionBean getByUserName(String s);

//    public DigitalBooleanActionBean getBySystemName(String s);

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the DigitalActionManager is
     * {@link #getSystemNamePrefix() } and "DA";
     */
    //@Override
    /*public*/ /*default*/ QString getSubSystemNamePrefix() const override{
        return getSystemNamePrefix() + "DB";
    }

    /**
     * Delete DigitalBooleanAction by removing it from the manager. The DigitalBooleanActionBean must first be
     * deactivated so it stops processing.
     *
     * @param x the DigitalBooleanAction to delete
     */
    /*public*/ virtual void deleteDigitalBooleanAction(MaleDigitalBooleanActionSocket* x)=0;
    };
  Q_DECLARE_INTERFACE(DigitalBooleanActionManager, "DigitalBooleanActionManager")
#endif // DIGITALBOOLEANACTIONMANAGER_H
