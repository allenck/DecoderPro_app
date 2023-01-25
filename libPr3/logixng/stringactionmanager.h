#ifndef STRINGACTIONMANAGER_H
#define STRINGACTIONMANAGER_H
#include "basemanager.h"
#include "category.h"

/**
 * Manager for StringActionBean
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */

class FemaleSocketListener;
class Base;
class StringActionBean;
class MaleStringActionSocket;
class FemaleStringActionSocket;
/*public*/  /*interface*/class StringActionManager : public virtual BaseManager/*<MaleStringActionSocket>*/ {
  Q_INTERFACES(BaseManager)
public:
    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleStringActionSocket for the action.
     *
     * @param action the bean
     * @return the male socket for this action
     * @throws IllegalArgumentException if the action has an invalid system name
     */
    /*public*/ virtual MaleStringActionSocket* registerAction(/*@Nonnull*/ StringActionBean* action)
            /*throws IllegalArgumentException*/=0;

    /**
     * Create a new system name for an StringActionBean.
     * @return a new system name
     */
  /*public*/ virtual QString getAutoSystemName() {return "?";}

    /*public*/ virtual FemaleStringActionSocket* createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName)=0;

    /**
     * Get a set of classes that implements the DigitalAction interface.
     *
     * @return a set of entries with category and class
     */
    /*public*/ virtual QHash<Category, QList</*Class<? extends Base>*/QString>> getActionClasses()=0;

    /*.*
     * Add an Action.
     *
     * @param action the action to add
     * @throws IllegalArgumentException if the action has an invalid system name
     */
//    /*public*/  void addAction(Action action)
//            throws IllegalArgumentException;

    /*.*
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
//    /*public*/  Action getAction(String name);

//    /*public*/  Action getByUserName(String s);

//    /*public*/  Action getBySystemName(String s);

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the StringActionManager is
     * {@link #getSystemNamePrefix() } and "SA";
     */
    //@Override
    /*public*/  /*default*/ QString getSubSystemNamePrefix() const override {
        return getSystemNamePrefix() + "SA";
    }

    /**
     * Delete StringAction by removing it from the manager. The Action must first be
     * deactivated so it stops processing.
     *
     * @param x the StringAction to delete
     */
    /*public*/ virtual void deleteStringAction(MaleStringActionSocket* x)=0;
    };
Q_DECLARE_INTERFACE(StringActionManager, "StringActionManager")
#endif // STRINGACTIONMANAGER_H
