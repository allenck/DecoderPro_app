#ifndef ADDRESSEDPROGRAMMERMANAGER_H
#define ADDRESSEDPROGRAMMERMANAGER_H

#include "libPr3_global.h"
#include "globalprogrammermanager.h"
#include "dcclocoaddress.h"

/**
 * Get access to available {@link Programmer} objects.
 * <P>
 * Programmers come in two types:
 * <UL>
 * <LI>Global, previously Service Mode, e.g. on a programming track. Request
 *      these from an instance of {@link GlobalProgrammerManager}.
 * <LI>Addressed, previously Ops Mode, e.g. "programming on the main". Request
 *      these from an instance of this interface.
 * </UL>
 * You get a {@link Programmer} object from a ProgrammerManager, which in turn can be located
 * from the {@link InstanceManager}.
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
class ProgrammingMode;
class AddressedProgrammer;
/*public*/ class LIBPR3SHARED_EXPORT AddressedProgrammerManager  //: public GlobalProgrammerManager
{
    //Q_OBJECT

public:
    //AddressedProgrammerManager(QObject* parent= 0) : GlobalProgrammerManager(parent) {}
    /**
     * Gain access to a Addressed Mode Programmer without reservation.
     * @param pLongAddress true if this is a long (14 bit) address, else false
     * @param pAddress Specific decoder address to use.
     * @return null only if there isn't an Ops Mode Programmer in the system
     */
    /*public*/ virtual AddressedProgrammer* getAddressedProgrammer(bool /*pLongAddress*/, int /*pAddress*/) =0;

    /**
      * Gain access to a Addressed Mode Programmer without reservation.
      *
      * @param address specific decoder address to use
      * @return null only if there isn't an Ops Mode Programmer in the system
      */
     //@CheckForNull
     /*public*/ virtual /*default*/ AddressedProgrammer* getAddressedProgrammer(/*@Nonnull*/ DccLocoAddress* address) {
         return this->getAddressedProgrammer(address->isLongAddress(), address->getNumber());
     }
    /**
     * Gain access to a (the) Addressed Mode Programmer, in the process
     * reserving it for yourself.
     * @param pLongAddress true if this is a long (14 bit) address, else false
     * @param pAddress Specific decoder address to use.
     * @return null if the address is in use by a reserved programmer
     */
    /*public*/ virtual AddressedProgrammer* reserveAddressedProgrammer(bool /*pLongAddress*/, int /*pAddress*/) =0;

    /**
     * Return access to an Addressed Mode Programmer, so that it can
     * be used elsewhere.
     */
    /*public*/ virtual void releaseAddressedProgrammer(AddressedProgrammer* /*p*/) =0;

    /**
     * Convenience method to check whether you'll be able to get
     * an Addressed Mode programmer.
     * @return false if there's no chance of getting one
     */
    /*public*/ virtual bool isAddressedModePossible() =0;

    /**
      * Convenience method to check whether you'll be able to get an Addressed
      * Mode programmer for a specific address
      *
      * @param address the address to get a programmer for
      * @return false if there's no chance of getting one
      */
    /*public*/ virtual bool isAddressedModePossible(/*@Nonnull*/ DccLocoAddress* address) =0;

    /**
     * Get the list of {@link ProgrammingMode} (generally) supported by
     * Programmers provided by this Manager.
     *<p>
     * Use this to enquire about modes before you're ready
     * to request a specific programmer.
     *<p>
     * If the order is significant, earlier modes are better.
     */
    /*public*/ virtual QList<QString> getDefaultModes() =0;
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
Q_DECLARE_INTERFACE(AddressedProgrammerManager, "AddressedProgrammerManager")
#endif // ADDRESSEDPROGRAMMERMANAGER_H
