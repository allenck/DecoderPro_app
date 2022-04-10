#ifndef DIGITALACTIONMANAGER_H
#define DIGITALACTIONMANAGER_H
#include "basemanager.h"
#include "maledigitalactionsocket.h"
#include "femaledigitalactionsocket.h"
#include "femalesocketlistener.h"
#include "category.h"

/**
 * Manager for DigitalActionBean
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
/*public*/ /*interface*/ class DigitalActionManager : public virtual BaseManager/*<MaleDigitalActionSocket>*/ {

 public:
    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleDigitalActionSocket for the action.
     *
     * @param action the bean
     * @return the male socket for this action
     * @throws IllegalArgumentException if the action has an invalid system name
     */
    /*public*/ virtual MaleDigitalActionSocket* registerAction(/*@Nonnull*/ DigitalActionBean* action)
            /*throws IllegalArgumentException*/=0;

    /**
     * Create a new system name for an DigitalActionBean.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName() {return "";}

    /*public*/ virtual FemaleDigitalActionSocket* createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName)=0;

    /**
     * Get a set of classes that implements the DigitalActionBean interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QHash<Category*, QList</*Class<? extends Base>*/QString> > getActionClasses()=0;

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the DigitalActionManager is
     * {@link #getSystemNamePrefix() } and "DA";
     */
    //@Override
    /*public*/ /*default*/ virtual QString getSubSystemNamePrefix() const{
        return getSystemNamePrefix() + "DA";
    }

    /**
     * Delete DigitalActionBean by removing it from the manager. The DigitalActionBean must first be
     * deactivated so it stops processing.
     *
     * @param x the DigitalActionBean to delete
     */
    /*public*/ virtual void deleteDigitalAction(MaleDigitalActionSocket* x)=0;

};
Q_DECLARE_INTERFACE(DigitalActionManager, "DigitalActionManager")
#endif // DIGITALACTIONMANAGER_H
