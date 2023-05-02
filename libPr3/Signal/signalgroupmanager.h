#ifndef SIGNALGROUPMANAGER_H
#define SIGNALGROUPMANAGER_H

#include "abstractmanager.h"
#include "signalgroup.h"

/**
 * Interface for obtaining information about signal systems.
 * <p>
 * Each NamedBean here represents a single signal system.
 * The actual objects are SignalAspectTable objects; that's
 * a current anachronism, soon to be fixed.
 * <P>
 * See the common implementation for information on how loaded, etc.
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
 * @author   Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 17977 $
 */
/*public*/ /*interface*/class LIBPR3SHARED_EXPORT SignalGroupManager :  public Manager
{
 //Q_OBJECT
    Q_INTERFACES(Manager)
public:
    /*public*/ virtual SignalGroup* getSignalGroup(QString /*name*/) =0;

    /*public*/ virtual SignalGroup* getBySystemName(QString name)const =0;


    /*public*/ virtual SignalGroup* getByUserName(QString name)const =0;

    /**
     * Create a new Signal group if the group does not exist.
     * <p>
     * Intended for use with
     * User GUI, to allow the auto generation of systemNames, where the user can
     * optionally supply a username.
     *
     * @deprecated since 4.25.2, use #newSignalGroupWithUserName(@Nonnull String userName)
     * @param userName User name for the new group
     * @return a Signal Group with the same userName if already exists
     * @throws IllegalArgumentException if there is trouble creating a new Group
     */
    //@Deprecated // 4.25.2
    //@Nonnull
    QT_DEPRECATED /*public*/ virtual SignalGroup* newSignaGroupWithUserName(/*@Nonnull*/ QString userName) /*throws IllegalArgumentException*/=0;

    /**
     * Create a new Signal group if the group does not exist.
     * <p>
     * Intended for use with
     * User GUI, to allow the auto generation of systemNames, where the user can
     * optionally supply a username.
     *
     * @param userName User name for the new group
     * @return a Signal Group with the same userName if already exists
     * @throws IllegalArgumentException if there is trouble creating a new Group
     */
    //@Nonnull
    /*public*/ virtual SignalGroup* newSignalGroupWithUserName(/*@Nonnull*/ QString userName) /*throws IllegalArgumentException*/=0;

    /*public*/ virtual SignalGroup* provideSignalGroup(QString /*systemName*/, QString /*userName*/) {return NULL;}

    /*public*/ virtual QStringList getSystemNameList() =0;

    virtual void deleteSignalGroup(SignalGroup* /*s*/) =0;

    /*public*/ virtual QString getNamedBeanClass()const  {
        return "SignalGroup";
    }


};
Q_DECLARE_INTERFACE(SignalGroupManager, "SignalGroupManager")
#endif // SIGNALGROUPMANAGER_H
