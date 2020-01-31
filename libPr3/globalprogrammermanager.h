#ifndef GLOBALPROGRAMMERMANAGER_H
#define GLOBALPROGRAMMERMANAGER_H

#include <QObject>
#include "programmer.h"
/**
 * Get access to available {@link Programmer} objects.
 * <P>
 * Programmers come in two types:
 * <UL>
 * <LI>Global, previously Service Mode, e.g. on a programming track. Request
 *      these from an instance of this interface.
 * <LI>Addressed, previously Ops Mode, e.g. "programming on the main". Request
 *      these from an instance of {@link AddressedProgrammerManager}.
 * </UL>
* <P>
 * This interface also provides a reserve/release
 * system for tools that want to pretend they have exclusive use of a Programmer.
 * This is a cooperative reservation; both tools (first and second reserver) must
 * be using the reserve/release interface.
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @see             jmri.Programmer
 * @author			Bob Jacobsen Copyright (C) 2001, 2008, 2014
 * @since           3.9.6
 */
#include <QObject>

/*public*/ class GlobalProgrammerManager //: public QObject
{
    //Q_OBJECT
public:
    //GlobalProgrammerManager(QObject* parent = 0) : QObject(parent) {}
    /**
     * Gain access to the Global Mode Programmer without reservation.
     * @return null only if there isn't a Global Mode Programmer available
     * via this Manager.
     */
    /*public*/ virtual Programmer* getGlobalProgrammer() =0;

    /**
     * Gain access to the Global Mode Programmer, in the process reserving it
     * for yourself.
     * @return null if the existing Global Mode programmer is in use
     */
    /*public*/ virtual Programmer* reserveGlobalProgrammer() =0;

    /**
     * Return access to the Global Mode Programmer, so that it can
     * be used elsewhere.
     */
    /*public*/ virtual void releaseGlobalProgrammer(Programmer* /*p*/) =0;

    /**
     * Convenience method to check whether you'll be able to get
     * a Global Mode programmer.
     * @return false if there's no chance of getting one
     */
    /*public*/ virtual bool isGlobalProgrammerAvailable() =0;

    /**
     * Provides the human-readable
     * representation for including ProgrammerManagers
     * directly in e.g. JComboBoxes, so it should return a
     * user-provided name for this particular one.
     */
    /*public*/ virtual QString getUserName() =0;

    /**
     * toString() provides the human-readable
     * representation for including ProgrammerManagers
     * directly in e.g. JComboBoxes, so it should return a
     * user-provided name for this particular one.
     */
    /*public*/ virtual QString toString() =0;

    virtual QObject* self() =0;

};
Q_DECLARE_INTERFACE(GlobalProgrammerManager, "GlobalProgrammerManager")
#endif // GLOBALPROGRAMMERMANAGER_H
