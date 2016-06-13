#ifndef CONDITIONALMANAGER_H
#define CONDITIONALMANAGER_H
#include "manager.h"
#include "conditional.h"

class ConditionalManager : public Manager
{
    Q_OBJECT
public:
    //explicit ConditionalManager(QObject *parent = 0);
    /**
     * Interface for obtaining Conditionals
     * <P>
     * This doesn't have a "new" method, since Conditionals are
     * separately implemented, instead of being system-specific.
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
    /**
     * Interface for obtaining Conditionals
     * <P>
     * This doesn't have a "new" method, since Conditionals are
     * separately implemented, instead of being system-specific.
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
    //public interface ConditionalManager extends Manager {

        // to free resources when no longer used
        virtual void dispose() const = 0;

        /**
         * Method to create a new Conditional if the Conditional does not exist
         *   Returns null if a Conditional with the same systemName or userName
         *       already exists, or if there is trouble creating a new Conditional
         *   If the parent Logix cannot be found, the userName cannot be checked, but
         *		the Conditional is still created. The scenario can happen when a Logix
         *      is loaded from a file after its Conditionals.
         */
        virtual Conditional* createNewConditional(QString /*systemName*/, QString /*userName*/) {return NULL;}

        /**
         * Parses the Conditional system name to get the parent Logix system name, then
         *    gets the parent Logix, and returns it.
         * @param name - system name of Conditional (must be trimmed and upper case)
         */
//        virtual Logix* getParentLogix(QString name) const = 0;

        /**
         * Method to get an existing Conditional.
         *	First looks up assuming that name is a User Name. Note: the parent Logix
         *		must be passed in x for user name lookup.
         *	If this fails, or if x == null, looks up assuming
         *      that name is a System Name.  If both fail, returns null.
         * @param x - parent Logix (may be null)
         * @param name - name to look up
         * @return null if no match found
         */
//        virtual Conditional* getConditional(Logix x,QString name) const = 0;
        virtual Conditional* getConditional(QString name) const = 0;

        virtual Conditional* getByUserName(QString s) const = 0;
//        virtual Conditional* getByUserName(Logix x,QString s) const = 0;
        virtual Conditional* getBySystemName(QString s) const = 0;

        /**
         * Get a list of all Conditional system names with the specified Logix parent
         */
//        virtual QStringList* getSystemNameListForLogix(Logix x) const = 0;

        /**
         * Delete Conditional by removing it from
         *     the manager.
         * The parent Logix must first be deactivated so it
         *     stops processing.
         */
        virtual void deleteConditional(Conditional* c) const = 0;


signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(ConditionalManager, "Conditional Manager")
#endif // CONDITIONALMANAGER_H
