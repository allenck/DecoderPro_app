#ifndef CONDITIONALNG_MANAGER_H
#define CONDITIONALNG_MANAGER_H
#include "../../appslib/manager.h"
#include "logixng.h"

/**
 * Manager for ConditionalNG
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 * @author Dave Sand          Copyright (C) 2021
 */
/*public*/ /*interface*/class ConditionalNG_Manager : public Manager/*<ConditionalNG>*/ {
 Q_INTERFACES(Manager)
 public:
    /**
     * Create a new ConditionalNG if the ConditionalNG does not exist.
     *
     * @param logixNG    The parent LogixNG
     * @param systemName The system name
     * @param userName   The user name
     * @return a new ConditionalNG or null if unable to create
     */
    /*public*/virtual  ConditionalNG* createConditionalNG(LogixNG* logixNG, QString systemName, QString userName)
            throw (IllegalArgumentException)=0;

    /**
     * For use with User GUI, to allow the auto generation of systemNames, where
     * the user can optionally supply a username.
     *
     * @param logixNG  The parent LogixNG
     * @param userName The user name
     * @return a new ConditionalNG or null if unable to create
     */
    /*public*/virtual ConditionalNG* createConditionalNG(LogixNG* logixNG, QString userName)
            throw (IllegalArgumentException);

    /**
     * Create a new ConditionalNG if the ConditionalNG does not exist.
     *
     * @param logixNG    The parent LogixNG
     * @param systemName The system name
     * @param userName   The user name
     * @param threadID   The thread ID that this ConditionalNG will execute on
     * @return a new ConditionalNG or null if unable to create
     */
    /*public*/virtual ConditionalNG* createConditionalNG(
            LogixNG* logixNG, QString systemName, QString userName, int threadID)
            throw (IllegalArgumentException)=0;

    /**
     * For use with User GUI, to allow the auto generation of systemNames, where
     * the user can optionally supply a username.
     *
     * @param logixNG   The parent LogixNG
     * @param userName  The user name
     * @param threadID  The thread ID that this ConditionalNG will execute on
     * @return a new ConditionalNG or null if unable to create
     */
    /*public*/virtual ConditionalNG* createConditionalNG(LogixNG* logixNG, QString userName, int threadID)
            throw (IllegalArgumentException)=0;

    /**
     * Locate via user name using the LogixNG, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param logixNG The LogixNG for the user name match.  If null, only do a system name match.
     * @param name User name or system name to match
     * @return null if no match found
     */
    /*public*/ virtual ConditionalNG* getConditionalNG(LogixNG* logixNG, QString name)=0;

    /**
     * Find the LogixNG which has the ConditionalNG system name in its ConditionalNG_Entry list.
     * @param systemName The ConditionalNG system name.
     * @return the parent LogixNG or null if none found.
     */
    /*public*/ virtual LogixNG* getParentLogixNG(QString systemName)=0;

    /**
     * Find the ConditionalNG which is a member of the LogixNG with the supplied user name.
     * @param logixNG The LogixNG that contains the requested ConditionalNG.
     * @param name    The requested ConditionalNG user name.
     * @return the ConditionalNG or null if none found.
     */
    /*public*/ virtual ConditionalNG* getByUserName(LogixNG* logixNG, QString name)=0;

    /** {@inheritDoc} */
    //@Override
    /*public*/ NamedBean* getByUserName(QString name)  override;

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*ConditionalNG*/NamedBean* getBySystemName(QString name) override;

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the ConditionalNG_Manager is
     * {@link #getSystemNamePrefix() } and "C";
     */
    //@Override
    /*public*/ /*default*/ QString getSubSystemNamePrefix() {
        return getSystemNamePrefix() + "C";
    }

    /**
     * Create a new system name for a ConditionalNG.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName()=0;

    /**
     * Delete ConditionalNG by removing it from the manager. The ConditionalNG must first
     * be deactivated so it stops processing.
     *
     * @param x the ConditionalNG to delete
     */
    virtual void deleteConditionalNG(ConditionalNG* x)=0;

    /**
     * Support for loading ConditionalNGs in a disabled state
     *
     * @param s true if ConditionalNG should be disabled when loaded
     */
    /*public*/ virtual void setLoadDisabled(bool s)=0;

    /**
     * Set whenether execute() should run on the GUI thread at once or should
     * dispatch the call until later, for all ConditionalNGs registered in this
     * manager.
     * Most tests turns off the delay to simplify the tests.
     * @param value true if execute() should run on GUI thread delayed,
     * false otherwise.
     */
    /*public*/virtual  void setRunOnGUIDelayed(bool value)=0;

};

#endif // CONDITIONALNG_MANAGER_H
