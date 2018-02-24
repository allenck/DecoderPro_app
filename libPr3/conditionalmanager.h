#ifndef CONDITIONALMANAGER_H
#define CONDITIONALMANAGER_H
#include "abstractmanager.h"
#include "conditional.h"

class Logix;
class ConditionalManager : public AbstractManager
{
    Q_OBJECT
public:
 explicit ConditionalManager(QObject *parent = 0) : AbstractManager(parent) {}
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
 virtual void dispose() {}
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
 virtual Logix* getParentLogix(QString /*name*/) {return NULL;}

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
 virtual Conditional* getConditional(Logix* /*x*/,QString /*name*/) {return NULL;}
        virtual Conditional* getConditional(QString /*name*/) {return NULL;}
        virtual Conditional* getByUserName(QString /*s*/) {return NULL;}
        virtual Conditional* getByUserName(Logix* /*x*/,QString /*s*/) {return NULL;}
        virtual Conditional* getBySystemName(QString /*s*/) {return NULL;}

        /**
         * Get a list of all Conditional system names with the specified Logix parent
         */
 virtual QStringList getSystemNameListForLogix(Logix* /*x*/) { return QStringList();}

        /**
         * Delete Conditional by removing it from
         *     the manager.
         * The parent Logix must first be deactivated so it
         *     stops processing.
         */
        virtual void deleteConditional(Conditional* /*c*/) {}

     /**
      * Return a copy of the entire map.  Used by
      * {@link jmri.jmrit.beantable.LogixTableAction#buildWhereUsedListing}
      * @return a copy of the map
      * @since 4.7.4
      */
 /*public*/ virtual QMap<QString, QList<QString> > getWhereUsedMap() { return QMap<QString, QList<QString> >();}

     /**
      * Add a conditional reference to the array indicated by the target system name.
      * @since 4.7.4
      * @param target The system name for the target conditional
      * @param reference The system name of the conditional that contains the conditional reference
      */
 /*public*/ virtual void addWhereUsed(QString /*target*/, QString /*reference*/) {}

     /**
      * Get a list of conditional references for the indicated conditional
      * @since 4.7.4
      * @param target The target conditional for a conditional reference
      * @return an ArrayList or null if none
      */
 /*public*/ virtual QList<QString> getWhereUsed(QString /*target*/) {return QStringList();}

     /**
      * Remove a conditional reference from the array indicated by the target system name.
      * @since 4.7.4
      * @param target The system name for the target conditional
      * @param reference The system name of the conditional that contains the conditional reference
      */
 /*public*/ virtual void removeWhereUsed(QString /*target*/, QString /*reference*/) {}

     /**
      * Display the complete structure, used for debugging purposes.
      * @since 4.7.4
      */
 /*public*/ virtual void displayWhereUsed() {}

     /**
      * Get the target system names used by this conditional
      * @since 4.7.4
      * @param reference The system name of the conditional the refers to other conditionals.
      * @return a list of the target conditionals
      */
 /*public*/ QList<QString> getTargetList(QString /*reference*/) {return QStringList();}

signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(ConditionalManager, "Conditional Manager")
#endif // CONDITIONALMANAGER_H
