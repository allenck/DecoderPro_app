#ifndef IDTAGMANAGER_H
#define IDTAGMANAGER_H
#include "abstractmanager.h"
#include "defaultidtag.h"
/**
 * Locate an IdTag object representing a specific IdTag.
 *<P>
 * IdTag objects are obtained from an IdTagManager, which in turn is generally located
 * from the InstanceManager. A typical call
 * sequence might be:
 *<PRE>
 * IdTag tag = InstanceManager.idTagManagerInstance().newIdTag(null,"23");
 *</PRE>
 * <P>
 * Each IdTag has a two names.  The "user" name is entirely free form, and
 * can be used for any purpose.  The "system" name is provided by the system-specific
 * implementations, and provides a unique mapping to the layout control system
 * (e.g. LocoNet, NCE, etc) and address within that system.
 * <P>
 * Much of the book-keeping is implemented in the AbstractIdTagManager class, which
 * can form the basis for a system-specific implementation.
 *
 * <hr>
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
 *
 * @author      Bob Jacobsen    Copyright (C) 2001
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @see         jmri.IdTag
 * @see         jmri.InstanceManager
 * @since       2.11.4
 */
/*public*/ /*interface*/class IdTagManager : public AbstractManager {
 Q_OBJECT
public:
     IdTagManager(QObject* parent = 0) : AbstractManager(parent) {}
     IdTagManager(SystemConnectionMemo* memo, QObject *parent = nullptr) : AbstractManager(memo,parent) {}

    /**
     * Locate via tag ID, then user name, and finally
     * system name if needed.
     * If that fails, create a new IdTag. If the name
     * is a valid system name, it will be used for the new
     * IdTag.  Otherwise, the makeSystemName method
     * will attempt to turn it into a valid system name.
     *
     * @param name Tag ID, user name, system name, or address which
     *      can be promoted to system name
     * @return Never null
     * @throws IllegalArgumentException if IdTag doesn't
     * already exist and the manager cannot create the IdTag
     * due to e.g. an illegal name or name that can't be parsed.
     */
    /*public*/ virtual DefaultIdTag* provideIdTag(QString /*name*/) {return NULL;}

    /**
     * Locate via tag ID, then by user name, and finally system name if needed.
     * If that fails, return null
     *
     * @param name tag name being requested
     * @return null if no match found
     */
    /*public*/ virtual DefaultIdTag* getIdTag(QString /*name*/) {return NULL;}

    /**
     * Locate an instance based on a system name.  Returns null if no
     * instance already exists.
     * @param systemName system name being requested
     * @return requested IdTag object or null if none exists
     */
    /*public*/ virtual NamedBean* getBySystemName(QString /*systemName*/) const {return NULL;}

    /**
     * Locate an instance based on a user name.  Returns null if no
     * instance already exists.
     * @param userName user name being requested
     * @return requested IdTag object or null if none exists
     */
    /*public*/ virtual NamedBean* getByUserName(QString /*userName*/) const {return NULL;}

    /**
     * Locate an instance based on a tag ID.  Returns null if no
     * instance already exists.
     * @param tagID tag ID being requested
     * @return requested IdTag object or null if none exists
     */
    /*public*/ virtual DefaultIdTag* getByTagID(QString /*tagID*/) {return NULL;}

    /**
     * Return an instance with the specified system and user names.
     * Note that two calls with the same arguments will get the same instance;
     * there is only one IdTag object representing a given physical IdTag
     * and therefore only one with a specific system or user name.
     *<P>
     * This will always return a valid object reference; a new object will be
     * created if necessary. In that case:
     *<UL>
     *<LI>If a null reference is given for user name, no user name will be associated
     *    with the IdTag object created; a valid system name must be provided
     *<LI>If both are provided, the system name defines the
     *    hardware access of the desired IdTag, and the user address
     *    is associated with it. The system name must be valid.
     *</UL>
     * Note that it is possible to make an inconsistent request if both
     * addresses are provided, but the given values are associated with
     * different objects.  This is a problem, and we don't have a
     * good solution except to issue warnings.
     * This will mostly happen if you're creating RfidTags when you should
     * be looking them up.
     * @return requested IdTag object (never null)
     * @throws IllegalArgumentException if cannot create the IdTag
     * due to e.g. an illegal name or name that can't be parsed.
     */
    /*public*/ virtual DefaultIdTag* newIdTag(QString /*systemName*/, QString /*userName*/) {return NULL;}

//    /**
//     * Get a list of all IdTag's system names.
//     */
//    /*public*/ virtual QStringList getSystemNameList() {return QStringList();}

    /**
     * Get a list of all IdTags seen by a specified Reporter within a specific
     * time threshold from the most recently seen.
     * @param reporter Reporter to return list for (can be null)
     * @param threshold Time threshold (in ms)
     * @return List of matching IdTags
     */
    /*public*/ virtual QList<IdTag*>* getTagsForReporter(Reporter* /*reporter*/, long /*threshold*/) {return NULL;}

    /**
     * Define if the manager should persist details of when and where
     * all known IdTags were seen
     * @param state True to store; False to omit
     */
 /*public*/ virtual void setStateStored(bool /*state*/) {}

    /**
     * Determines if the state of known IdTags should be stored
     * @return True to store state; False to discard state
     */
    /*public*/ virtual bool isStateStored() {return false;}

    /**
     * Define if the manager should use the fast clock when setting the
     * times when a given IdTag was last seen
     * @param fastClock True to use the fast clock; False to use the system clock
     */
    /*public*/ virtual void setFastClockUsed(bool /*fastClock*/) {}

    /**
     * Determines if fast clock times should be recorded for when a given
     * IdTag was last seen
     * @return True to use the fast clock; False to use the system clock
     */
    /*public*/ virtual bool isFastClockUsed() {return false;}

    /**
     * Perform initialisation
     */
    /*public*/ virtual void init() const {}

    /**
     * Determines if the manager has been initialised
     * @return state of initialisation
     */
    /*public*/ virtual bool isInitialised() {return false;}
    virtual /*public*/ DefaultIdTag* provide(QString name) /*throw (IllegalArgumentException)*/ =0;

 friend class IdTagManagerXml;
};
//Q_DECLARE_INTERFACE(IdTagManager, "IdTagManager")
#endif // IDTAGMANAGER_H
