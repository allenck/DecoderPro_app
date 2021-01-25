#ifndef LOGIXMANAGER_H
#define LOGIXMANAGER_H
#include "manager.h"
#include "abstractmanager.h"
class Logix;
class LogixManager : public AbstractManager
{
    //Q_OBJECT
public:
    explicit LogixManager(QObject *parent = 0)
        : AbstractManager(parent) {}
    /**
     * Interface for obtaining Logixs
     * <P>
     * This doesn't have a "new" method, since Logixs are
     * separately implemented, instead of being system-specific.
     *
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
     * @author      Dave Duchamp Copyright (C) 2007
     * @version	$Revision: 17977 $
     */
//    public interface LogixManager extends Manager {

        // to free resources when no longer used
//        virtual void dispose() {}

        /**
         * Method to create a new Logix if the Logix does not exist
         *   Returns null if a Logix with the same systemName or userName
         *       already exists, or if there is trouble creating a new Logix.
         */
        virtual Logix* createNewLogix(QString /*systemName*/, QString /*userName*/) = 0;

        /**
         * For use with User GUI, to allow the auto generation of systemNames,
         * where the user can optionally supply a username.
         *   Returns null if a Logix with the same userName
         *       already exists, or if there is trouble creating a new Logix.
         */
         virtual Logix* createNewLogix(QString /*userName*/) = 0;

        /**
         * Locate via user name, then system name if needed.
         * Does not create a new one if nothing found
         *
         * @param name
         * @return null if no match found
         */
        virtual Logix* getLogix(QString /*name*/) {return NULL;}

        virtual Logix* getByUserName(QString /*s*/) const =0;
        virtual Logix* getBySystemName(QString /*s*/)const =0;

        /**
         * Activate all Logixs that are not currently active
         * This method is called after a configuration file is loaded.
         */
        virtual void activateAllLogixs() = 0;


        /**
         * Delete Logix by removing it from
         *     the manager.
         * The Logix must first be deactivated so it
         *     stops processing.
         */
        virtual void deleteLogix(Logix* /*x*/)  = 0;

        /**
         * Support for loading Logixs in a disabled state to debug loops
         */
        virtual void setLoadDisabled(bool /*s*/) = 0;

signals:
    
public slots:
    
};

#endif // LOGIXMANAGER_H
